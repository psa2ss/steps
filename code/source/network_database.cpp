#include "header/network_database.h"
#include "header/network/y_matrix_builder.h"
#include "header/basic/utility.h"
#include <fstream>

class SUBLINE
{
    public:
        SUBLINE()
        {
            from_loc = 0.0;
            to_loc = 1.0;
        }
        double from_loc;
        double to_loc;
};


NETWORK_DATABASE::NETWORK_DATABASE(POWER_SYSTEM_DATABASE* psdb)
{
    set_power_system_database(psdb);
    clear_database();
}


NETWORK_DATABASE::~NETWORK_DATABASE()
{
    clear_database();
}

void NETWORK_DATABASE::clear_database()
{
    network_Y_matrix.clear();
    network_BP_matrix.clear();
    network_BQ_matrix.clear();
    inphno.clear();
}

bool NETWORK_DATABASE::is_power_system_database_set() const
{
    if(get_power_system_database()!=NULL)
        return true;
    else
    {
        ostringstream sstream;
        sstream<<"Error. Network database is not connected to any power system database."<<endl
          <<"No operation on the network database will work.";
        show_information_with_leading_time_stamp(sstream);
        return false;
    }
}

void NETWORK_DATABASE::build_network_matrix()
{
    if(not is_power_system_database_set())
        return;

    if(inphno.empty())
        initialize_physical_internal_bus_pair();

    network_Y_matrix.clear();

    add_lines_to_network();
    add_transformers_to_network();
    add_fixed_shunts_to_network();

    network_Y_matrix.compress_and_merge_duplicate_entries();
}

SPARSE_MATRIX& NETWORK_DATABASE::get_network_matrix()
{
    if(not is_power_system_database_set())
    {
        network_Y_matrix.clear();
        return network_Y_matrix;
    }

    if(network_Y_matrix.matrix_in_triplet_form())
        build_network_matrix();

    return network_Y_matrix;
}

void NETWORK_DATABASE::build_decoupled_network_matrix()
{
    if(not is_power_system_database_set())
        return;

    if(inphno.empty())
        initialize_physical_internal_bus_pair();

    network_BP_matrix.clear();
    network_BQ_matrix.clear();

    add_lines_to_decoupled_network();
    add_transformers_to_decoupled_network();
    add_fixed_shunts_to_decoupled_network();

    network_BP_matrix.compress_and_merge_duplicate_entries();
    network_BQ_matrix.compress_and_merge_duplicate_entries();
}

SPARSE_MATRIX& NETWORK_DATABASE::get_decoupled_network_BP_matrix()
{
    if(not is_power_system_database_set())
    {
        network_BP_matrix.clear();
        return network_BP_matrix;
    }

    if(network_BP_matrix.matrix_in_triplet_form())
        build_decoupled_network_matrix();

    return network_BP_matrix;
}

SPARSE_MATRIX& NETWORK_DATABASE::get_decoupled_network_BQ_matrix()
{
    if(not is_power_system_database_set())
    {
        network_BQ_matrix.clear();
        return network_BQ_matrix;
    }

    if(network_BP_matrix.matrix_in_triplet_form())
        build_decoupled_network_matrix();

    return network_BQ_matrix;
}


void NETWORK_DATABASE::build_dynamic_network_matrix()
{
    if(not is_power_system_database_set())
        return;

    if(inphno.empty())
        initialize_physical_internal_bus_pair();

    network_Y_matrix.clear();

    add_bus_fault_to_dynamic_network();
    add_lines_to_dynamic_network();
    add_transformers_to_network();
    add_fixed_shunts_to_network();
    add_generators_to_dynamic_network();

    network_Y_matrix.compress_and_merge_duplicate_entries();
}

SPARSE_MATRIX& NETWORK_DATABASE::get_dynamic_network_matrix()
{
    if(network_Y_matrix.matrix_in_triplet_form())
        build_dynamic_network_matrix();

    return network_Y_matrix;
}

void NETWORK_DATABASE::add_lines_to_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<LINE*> lines = psdb->get_all_lines();

    size_t n = lines.size();

    for(size_t i = 0; i!=n; ++i)
        add_line_to_network(*(lines[i]));
}


void NETWORK_DATABASE::add_line_to_network(const LINE& line)
{
    if(line.get_sending_side_breaker_status()==false and line.get_receiving_side_breaker_status()==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding line '%s' connecting to bus %u and %u to network Y matrix.", line.get_identifier().c_str(),
                  line.get_sending_side_bus(), line.get_receiving_side_bus());
    show_information_with_leading_time_stamp(sstream);
    */

    size_t sending_bus = line.get_sending_side_bus();
    size_t receiving_bus = line.get_receiving_side_bus();

    size_t i = inphno.get_internal_bus_number_of_physical_bus_number(sending_bus);
    size_t j = inphno.get_internal_bus_number_of_physical_bus_number(receiving_bus);

    complex<double> Zline = line.get_line_positive_sequence_z_in_pu();
    complex<double> Yline = line.get_line_positive_sequence_y_in_pu();
    complex<double> Yshunt_sending = line.get_shunt_positive_sequence_y_at_sending_side_in_pu();
    complex<double> Yshunt_receiving = line.get_shunt_positive_sequence_y_at_receiving_side_in_pu();

    complex<double> Y, Z;
    if(line.get_sending_side_breaker_status()==true and line.get_receiving_side_breaker_status()==true)
    {
        Y = 1.0/Zline;

        network_Y_matrix.add_entry(i,j, -Y);
        network_Y_matrix.add_entry(j,i, -Y);
        network_Y_matrix.add_entry(i,i, Y+0.5*Yline+Yshunt_sending);
        network_Y_matrix.add_entry(j,j, Y+0.5*Yline+Yshunt_receiving);

        return;
    }

    if(line.get_sending_side_breaker_status()==true and line.get_receiving_side_breaker_status()==false)
    {
        Y = 0.5*Yline+Yshunt_receiving;
        Z = Zline + 1.0/Y;
        Y = 1.0/Z + 0.5*Yline+Yshunt_sending;
        network_Y_matrix.add_entry(i,i, Y);
        return;
    }

    if(line.get_sending_side_breaker_status()==false and line.get_receiving_side_breaker_status()==true)
    {
        Y = 0.5*Yline+Yshunt_sending;
        Z = Zline + 1.0/Y;
        Y = 1.0/Z + 0.5*Yline+Yshunt_receiving;
        network_Y_matrix.add_entry(j,j, Y);
        return;
    }
}

void NETWORK_DATABASE::add_transformers_to_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<TRANSFORMER*> transformers = psdb->get_all_transformers();

    size_t n = transformers.size();

    for(size_t i = 0; i!=n; ++i)
        add_transformer_to_network(*(transformers[i]));
}

void NETWORK_DATABASE::add_transformer_to_network(const TRANSFORMER& trans)
{
    if(trans.is_two_winding_transformer())
        add_two_winding_transformer_to_network_v2(trans);
    else
        add_three_winding_transformer_to_network(trans);
}

void NETWORK_DATABASE::add_two_winding_transformer_to_network(const TRANSFORMER& trans)
{
    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and trans.get_winding_breaker_status(SECONDARY_SIDE)==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding two-winding transformer '%s' connecting to bus %u and %u to network Y matrix.", trans.get_identifier().c_str(),
                  trans.get_winding_bus(PRIMARY_SIDE), trans.get_winding_bus(SECONDARY_SIDE));
    show_information_with_leading_time_stamp(sstream);
    */

    size_t primary_bus = trans.get_winding_bus(PRIMARY_SIDE);
    size_t secondary_bus = trans.get_winding_bus(SECONDARY_SIDE);

    size_t p = inphno.get_internal_bus_number_of_physical_bus_number(primary_bus);
    size_t s = inphno.get_internal_bus_number_of_physical_bus_number(secondary_bus);

    complex<double> Zps = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, SECONDARY_SIDE);
    complex<double> Ym = trans.get_magnetizing_admittance_based_on_winding_norminal_voltage_and_system_base_power_in_pu();

    complex<double> Zp, Zs;
    Zp = 0.5*Zps; Zs = Zp;

    double tap_primary = trans.get_winding_off_nominal_turn_ratio_in_pu(PRIMARY_SIDE);
    double angle_primary = trans.get_winding_angle_shift_in_deg(PRIMARY_SIDE);
    angle_primary = deg2rad(angle_primary);
    double tap_secondary = trans.get_winding_off_nominal_turn_ratio_in_pu(SECONDARY_SIDE);
    double angle_secondary = trans.get_winding_angle_shift_in_deg(SECONDARY_SIDE);
    angle_secondary = deg2rad(angle_secondary);

    complex<double> kp(tap_primary*cos(angle_primary),tap_primary*sin(angle_primary)),
                    ks(tap_secondary*cos(angle_secondary),tap_secondary*sin(angle_secondary));


    complex<double> V, I, Vstar;
    complex<double> ypp, yps, ysp, yss, Yeq, Zeq;

    complex<double> kp_store, ks_store, Ym_store;
    kp_store = kp;
    ks_store = ks;
    Ym_store = Ym;

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and trans.get_winding_breaker_status(SECONDARY_SIDE)==true)
    {
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_Y_matrix.add_entry(p,p,ypp);
        network_Y_matrix.add_entry(p,s,yps);
        network_Y_matrix.add_entry(s,p,ysp);
        network_Y_matrix.add_entry(s,s,yss);


        kp = kp/abs(kp);
        ks = ks/abs(ks);
        Ym = 0.0;

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_BP_matrix.add_entry(p,p,ypp);
        network_BP_matrix.add_entry(p,s,yps);
        network_BP_matrix.add_entry(s,p,ysp);
        network_BP_matrix.add_entry(s,s,yss);


        kp = kp_store;
        ks = ks_store;

        kp = abs(kp);
        ks = abs(ks);
        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_BQ_matrix.add_entry(p,p,ypp);
        network_BQ_matrix.add_entry(p,s,yps);
        network_BQ_matrix.add_entry(s,p,ysp);
        network_BQ_matrix.add_entry(s,s,yss);


        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and trans.get_winding_breaker_status(SECONDARY_SIDE)==false)
    {
        V = 1.0;
        V = V/kp;
        Zeq = Zp + 1.0/Ym;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        network_Y_matrix.add_entry(p,p,ypp);

        network_BP_matrix.add_entry(p,p,0.0);

        kp = abs(kp);

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/kp;
        Zeq = Zp + 1.0/Ym;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        network_BQ_matrix.add_entry(p,p,ypp);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and trans.get_winding_breaker_status(SECONDARY_SIDE)==true)
    {
        V = 1.0;
        V = V/ks;
        Zeq = Zs + 1.0/Ym;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        network_Y_matrix.add_entry(s,s,yss);

        network_BP_matrix.add_entry(s,s,0.0);

        ks = abs(ks);

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/ks;
        Zeq = Zs + 1.0/Ym;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        network_BQ_matrix.add_entry(s,s,yss);
        return;
    }
}

void NETWORK_DATABASE::add_three_winding_transformer_to_network(const TRANSFORMER& trans)
{
    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding three-winding transformer '%s' connecting to bus %u, %u, and %u to network Y matrix.", trans.get_identifier().c_str(),
                  trans.get_winding_bus(PRIMARY_SIDE), trans.get_winding_bus(SECONDARY_SIDE), trans.get_winding_bus(TERTIARY_SIDE));
    show_information_with_leading_time_stamp(sstream);
    */

    size_t primary_bus = trans.get_winding_bus(PRIMARY_SIDE);
    size_t secondary_bus = trans.get_winding_bus(SECONDARY_SIDE);
    size_t tertiary_bus = trans.get_winding_bus(TERTIARY_SIDE);

    size_t p = inphno.get_internal_bus_number_of_physical_bus_number(primary_bus);
    size_t s = inphno.get_internal_bus_number_of_physical_bus_number(secondary_bus);
    size_t t = inphno.get_internal_bus_number_of_physical_bus_number(tertiary_bus);

    complex<double> Zps = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, SECONDARY_SIDE);
    complex<double> Zst = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(SECONDARY_SIDE, TERTIARY_SIDE);
    complex<double> Zpt = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, TERTIARY_SIDE);
    complex<double> Ym = trans.get_magnetizing_admittance_based_on_winding_norminal_voltage_and_system_base_power_in_pu();

    complex<double> Zp = 0.5*(Zps+Zpt-Zst),
                    Zs = 0.5*(Zps+Zst-Zpt),
                    Zt = 0.5*(Zpt+Zst-Zps);

    double tap_primary = trans.get_winding_off_nominal_turn_ratio_in_pu(PRIMARY_SIDE);
    double angle_primary = trans.get_winding_angle_shift_in_deg(PRIMARY_SIDE);
    angle_primary = deg2rad(angle_primary);
    double tap_secondary = trans.get_winding_off_nominal_turn_ratio_in_pu(SECONDARY_SIDE);
    double angle_secondary = trans.get_winding_angle_shift_in_deg(SECONDARY_SIDE);
    angle_secondary = deg2rad(angle_secondary);
    double tap_tertiary = trans.get_winding_off_nominal_turn_ratio_in_pu(TERTIARY_SIDE);
    double angle_tertiary = trans.get_winding_angle_shift_in_deg(TERTIARY_SIDE);
    angle_tertiary = deg2rad(angle_tertiary);

    complex<double> kp(tap_primary*cos(angle_primary),tap_primary*sin(angle_primary)),
                    ks(tap_secondary*cos(angle_secondary),tap_secondary*sin(angle_secondary)),
                    kt(tap_tertiary*cos(angle_tertiary),tap_tertiary*sin(angle_tertiary));

    complex<double> V, I, Vstar;
    complex<double> ypp, yps, ypt, ysp, yss, yst, ytp, yts, ytt, Yeq, Zeq;

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        // voltage at primary side.
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        I = -Vstar/Zt;
        I /= conj(kt);
        ytp = I;

        // voltage at secondary side
        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp + 1.0/Zt;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        I = -Vstar/Zt;
        I /= conj(kt);
        yts = I;

        // voltage at tertiary side
        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zp + 1.0/Zs;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        ypt = I;

        I = -Vstar/Zs;
        I /= conj(ks);
        yst = I;

        network_Y_matrix.add_entry(p,p,ypp);
        network_Y_matrix.add_entry(p,s,yps);
        network_Y_matrix.add_entry(p,t,ypt);
        network_Y_matrix.add_entry(s,p,ysp);
        network_Y_matrix.add_entry(s,s,yss);
        network_Y_matrix.add_entry(s,t,yst);
        network_Y_matrix.add_entry(t,p,ytp);
        network_Y_matrix.add_entry(t,s,yts);
        network_Y_matrix.add_entry(t,t,ytt);
        return;
    }


    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
    {
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_Y_matrix.add_entry(p,p,ypp);
        network_Y_matrix.add_entry(p,s,yps);
        network_Y_matrix.add_entry(s,p,ysp);
        network_Y_matrix.add_entry(s,s,yss);
        return;
    }


    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zt;
        I /= conj(kt);
        ytp = I;

        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        ypt = I;

        network_Y_matrix.add_entry(p,p,ypp);
        network_Y_matrix.add_entry(p,t,ypt);
        network_Y_matrix.add_entry(t,p,ytp);
        network_Y_matrix.add_entry(t,t,ytt);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zt;
        I /= conj(kt);
        yts = I;

        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        yst = I;

        network_Y_matrix.add_entry(s,s,yss);
        network_Y_matrix.add_entry(s,t,yst);
        network_Y_matrix.add_entry(t,s,yts);
        network_Y_matrix.add_entry(t,t,ytt);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
    {
        V = 1.0;
        V = V/kp;
        Zeq = Zp + 1.0/Ym;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        network_Y_matrix.add_entry(p,p,ypp);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
    {
        V = 1.0;
        V = V/ks;
        Zeq = Zs + 1.0/Ym;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        network_Y_matrix.add_entry(s,s,yss);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        V = 1.0;
        V = V/kt;
        Zeq = Zt + 1.0/Ym;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        network_Y_matrix.add_entry(t,t,ytt);
        return;
    }
}

void NETWORK_DATABASE::add_two_winding_transformer_to_network_v2(const TRANSFORMER& trans)
{
    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and trans.get_winding_breaker_status(SECONDARY_SIDE)==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding two-winding transformer '%s' connecting to bus %u and %u to network Y matrix.", trans.get_identifier().c_str(),
                  trans.get_winding_bus(PRIMARY_SIDE), trans.get_winding_bus(SECONDARY_SIDE));
    show_information_with_leading_time_stamp(sstream);
    */

    size_t primary_bus = trans.get_winding_bus(PRIMARY_SIDE);
    size_t secondary_bus = trans.get_winding_bus(SECONDARY_SIDE);

    size_t p = inphno.get_internal_bus_number_of_physical_bus_number(primary_bus);
    size_t s = inphno.get_internal_bus_number_of_physical_bus_number(secondary_bus);

    complex<double> Zps = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, SECONDARY_SIDE);
    complex<double> Ym = trans.get_magnetizing_admittance_based_on_winding_norminal_voltage_and_system_base_power_in_pu();

    complex<double> Zp, Zs;
    Zp = 0.5*Zps; Zs = Zp;

    double tap_primary = trans.get_winding_off_nominal_turn_ratio_in_pu(PRIMARY_SIDE);
    double angle_primary = trans.get_winding_angle_shift_in_deg(PRIMARY_SIDE);
    angle_primary = deg2rad(angle_primary);
    double tap_secondary = trans.get_winding_off_nominal_turn_ratio_in_pu(SECONDARY_SIDE);
    double angle_secondary = trans.get_winding_angle_shift_in_deg(SECONDARY_SIDE);
    angle_secondary = deg2rad(angle_secondary);

    complex<double> kp(tap_primary*cos(angle_primary),tap_primary*sin(angle_primary)),
                    ks(tap_secondary*cos(angle_secondary),tap_secondary*sin(angle_secondary));


    complex<double> V, I, Vstar;
    complex<double> ypp, yps, ysp, yss, Yeq, Zeq;

    complex<double> kp_store, ks_store, Ym_store;
    kp_store = kp;
    ks_store = ks;
    Ym_store = Ym;

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and trans.get_winding_breaker_status(SECONDARY_SIDE)==true)
    {
        Ym = 0.0;
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_Y_matrix.add_entry(p,p,ypp);
        network_Y_matrix.add_entry(p,s,yps);
        network_Y_matrix.add_entry(s,p,ysp);
        network_Y_matrix.add_entry(s,s,yss);

        Ym = Ym_store;
        network_Y_matrix.add_entry(p,p,Ym);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and trans.get_winding_breaker_status(SECONDARY_SIDE)==false)
    {
        network_Y_matrix.add_entry(p,p,Ym);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and trans.get_winding_breaker_status(SECONDARY_SIDE)==true)
    {
        V = 1.0;
        V = V/ks;
        Ym = trans.get_magnetizing_admittance_based_on_winding_norminal_voltage_and_system_base_power_in_pu();
        Zeq = Zps + 1.0/Ym;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        network_Y_matrix.add_entry(s,s,yss);
        return;
    }
}


void NETWORK_DATABASE::add_fixed_shunts_to_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<FIXED_SHUNT*> shunts = psdb->get_all_fixed_shunts();

    size_t n = shunts.size();

    for(size_t i = 0; i!=n; ++i)
        add_fixed_shunt_to_network(*(shunts[i]));
}

void NETWORK_DATABASE::add_fixed_shunt_to_network(const FIXED_SHUNT& shunt)
{
    if(shunt.get_status()==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding fixed shunt '%s' at bus %u to network Y matrix.", shunt.get_identifier().c_str(),
                  shunt.get_shunt_bus());
    show_information_with_leading_time_stamp(sstream);
    */

    size_t bus = shunt.get_shunt_bus();

    size_t i = inphno.get_internal_bus_number_of_physical_bus_number(bus);

    complex<double> Yshunt = shunt.get_nominal_admittance_shunt_in_pu();

    network_Y_matrix.add_entry(i,i, Yshunt);
    return;
}

void NETWORK_DATABASE::add_lines_to_decoupled_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<LINE*> lines = psdb->get_all_lines();

    size_t n = lines.size();

    for(size_t i = 0; i!=n; ++i)
        add_line_to_decoupled_network(*(lines[i]));
}

void NETWORK_DATABASE::add_line_to_decoupled_network(const LINE& line)
{
    if(line.get_sending_side_breaker_status()==false and line.get_receiving_side_breaker_status()==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding line '%s' connecting to bus %u and %u to network Y matrix.", line.get_identifier().c_str(),
                  line.get_sending_side_bus(), line.get_receiving_side_bus());
    show_information_with_leading_time_stamp(sstream);
    */

    size_t sending_bus = line.get_sending_side_bus();
    size_t receiving_bus = line.get_receiving_side_bus();

    size_t i = inphno.get_internal_bus_number_of_physical_bus_number(sending_bus);
    size_t j = inphno.get_internal_bus_number_of_physical_bus_number(receiving_bus);

    complex<double> Zline = line.get_line_positive_sequence_z_in_pu();
    complex<double> Yline = line.get_line_positive_sequence_y_in_pu();
    complex<double> Yshunt_sending = line.get_shunt_positive_sequence_y_at_sending_side_in_pu();
    complex<double> Yshunt_receiving = line.get_shunt_positive_sequence_y_at_receiving_side_in_pu();

    complex<double> Y, Z;
    if(line.get_sending_side_breaker_status()==true and line.get_receiving_side_breaker_status()==true)
    {
        Y = 1.0/Zline;

        network_BP_matrix.add_entry(i,j, -Y);
        network_BP_matrix.add_entry(j,i, -Y);
        network_BP_matrix.add_entry(i,i, Y);
        network_BP_matrix.add_entry(j,j, Y);

        Zline = complex<double>(0.0, Zline.imag());
        Y = 1.0/Zline;
        Yline = complex<double>(0.0, Yline.imag());
        Yshunt_sending = complex<double>(0.0, Yshunt_sending.imag());
        Yshunt_receiving = complex<double>(0.0, Yshunt_receiving.imag());

        network_BQ_matrix.add_entry(i,j, -Y);
        network_BQ_matrix.add_entry(j,i, -Y);
        network_BQ_matrix.add_entry(i,i, Y+0.5*Yline+Yshunt_sending);
        network_BQ_matrix.add_entry(j,j, Y+0.5*Yline+Yshunt_receiving);

        return;
    }

    if(line.get_sending_side_breaker_status()==true and line.get_receiving_side_breaker_status()==false)
    {
        network_BP_matrix.add_entry(i,i, 0.0);

        Zline = complex<double>(0.0, Zline.imag());
        Yline = complex<double>(0.0, Yline.imag());
        Yshunt_sending = complex<double>(0.0, Yshunt_sending.imag());
        Yshunt_receiving = complex<double>(0.0, Yshunt_receiving.imag());

        Y = 0.5*Yline+Yshunt_receiving;
        Z = Zline + 1.0/Y;
        Y = 1.0/Z + 0.5*Yline+Yshunt_sending;

        network_BQ_matrix.add_entry(i,i, Y);
        return;
    }

    if(line.get_sending_side_breaker_status()==false and line.get_receiving_side_breaker_status()==true)
    {
        network_BP_matrix.add_entry(j,j, 0.0);

        Zline = complex<double>(0.0, Zline.imag());
        Yline = complex<double>(0.0, Yline.imag());
        Yshunt_sending = complex<double>(0.0, Yshunt_sending.imag());
        Yshunt_receiving = complex<double>(0.0, Yshunt_receiving.imag());

        Y = 0.5*Yline+Yshunt_sending;
        Z = Zline + 1.0/Y;
        Y = 1.0/Z + 0.5*Yline+Yshunt_receiving;
        network_Y_matrix.add_entry(j,j, Y);

        network_BQ_matrix.add_entry(j,j, Y);
        return;
    }
}


void NETWORK_DATABASE::add_transformers_to_decoupled_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<TRANSFORMER*> transformers = psdb->get_all_transformers();

    size_t n = transformers.size();

    for(size_t i = 0; i!=n; ++i)
        add_transformer_to_decoupled_network(*(transformers[i]));
}

void NETWORK_DATABASE::add_transformer_to_decoupled_network(const TRANSFORMER& trans)
{
    if(trans.is_two_winding_transformer())
        add_two_winding_transformer_to_decoupled_network_v2(trans);
    else
        add_three_winding_transformer_to_decoupled_network(trans);
}

void NETWORK_DATABASE::add_three_winding_transformer_to_decoupled_network(const TRANSFORMER& trans)
{
    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding three-winding transformer '%s' connecting to bus %u, %u, and %u to network Y matrix.", trans.get_identifier().c_str(),
                  trans.get_winding_bus(PRIMARY_SIDE), trans.get_winding_bus(SECONDARY_SIDE), trans.get_winding_bus(TERTIARY_SIDE));
    show_information_with_leading_time_stamp(sstream);
    */

    size_t primary_bus = trans.get_winding_bus(PRIMARY_SIDE);
    size_t secondary_bus = trans.get_winding_bus(SECONDARY_SIDE);
    size_t tertiary_bus = trans.get_winding_bus(TERTIARY_SIDE);

    size_t p = inphno.get_internal_bus_number_of_physical_bus_number(primary_bus);
    size_t s = inphno.get_internal_bus_number_of_physical_bus_number(secondary_bus);
    size_t t = inphno.get_internal_bus_number_of_physical_bus_number(tertiary_bus);

    complex<double> Zps = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, SECONDARY_SIDE);
    complex<double> Zst = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(SECONDARY_SIDE, TERTIARY_SIDE);
    complex<double> Zpt = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, TERTIARY_SIDE);
    complex<double> Ym = trans.get_magnetizing_admittance_based_on_winding_norminal_voltage_and_system_base_power_in_pu();

    complex<double> Zp = 0.5*(Zps+Zpt-Zst),
                    Zs = 0.5*(Zps+Zst-Zpt),
                    Zt = 0.5*(Zpt+Zst-Zps);

    double tap_primary = trans.get_winding_off_nominal_turn_ratio_in_pu(PRIMARY_SIDE);
    double angle_primary = trans.get_winding_angle_shift_in_deg(PRIMARY_SIDE);
    angle_primary = deg2rad(angle_primary);
    double tap_secondary = trans.get_winding_off_nominal_turn_ratio_in_pu(SECONDARY_SIDE);
    double angle_secondary = trans.get_winding_angle_shift_in_deg(SECONDARY_SIDE);
    angle_secondary = deg2rad(angle_secondary);
    double tap_tertiary = trans.get_winding_off_nominal_turn_ratio_in_pu(TERTIARY_SIDE);
    double angle_tertiary = trans.get_winding_angle_shift_in_deg(TERTIARY_SIDE);
    angle_tertiary = deg2rad(angle_tertiary);

    complex<double> kp(tap_primary*cos(angle_primary),tap_primary*sin(angle_primary)),
                    ks(tap_secondary*cos(angle_secondary),tap_secondary*sin(angle_secondary)),
                    kt(tap_tertiary*cos(angle_tertiary),tap_tertiary*sin(angle_tertiary));

    complex<double> V, I, Vstar;
    complex<double> ypp, yps, ypt, ysp, yss, yst, ytp, yts, ytt, Yeq, Zeq;


    complex<double> kp_store = kp, ks_store = ks, kt_store = kt;
    complex<double> Ym_store = Ym;

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        // voltage at primary side.
        kp = kp/abs(kp);
        ks = ks/abs(ks);
        kt = kt/abs(kt);

        Ym = 0.0;

        // voltage at primary side.
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        I = -Vstar/Zt;
        I /= conj(kt);
        ytp = I;

        // voltage at secondary side
        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp + 1.0/Zt;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        I = -Vstar/Zt;
        I /= conj(kt);
        yts = I;

        // voltage at tertiary side
        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zp + 1.0/Zs;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        ypt = I;

        I = -Vstar/Zs;
        I /= conj(ks);
        yst = I;

        network_BP_matrix.add_entry(p,p,ypp);
        network_BP_matrix.add_entry(p,s,yps);
        network_BP_matrix.add_entry(p,t,ypt);
        network_BP_matrix.add_entry(s,p,ysp);
        network_BP_matrix.add_entry(s,s,yss);
        network_BP_matrix.add_entry(s,t,yst);
        network_BP_matrix.add_entry(t,p,ytp);
        network_BP_matrix.add_entry(t,s,yts);
        network_BP_matrix.add_entry(t,t,ytt);

        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        // voltage at primary side.
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        I = -Vstar/Zt;
        I /= conj(kt);
        ytp = I;

        // voltage at secondary side
        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp + 1.0/Zt;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        I = -Vstar/Zt;
        I /= conj(kt);
        yts = I;

        // voltage at tertiary side
        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zp + 1.0/Zs;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        ypt = I;

        I = -Vstar/Zs;
        I /= conj(ks);
        yst = I;

        network_BQ_matrix.add_entry(p,p,ypp);
        network_BQ_matrix.add_entry(p,s,yps);
        network_BQ_matrix.add_entry(p,t,ypt);
        network_BQ_matrix.add_entry(s,p,ysp);
        network_BQ_matrix.add_entry(s,s,yss);
        network_BQ_matrix.add_entry(s,t,yst);
        network_BQ_matrix.add_entry(t,p,ytp);
        network_BQ_matrix.add_entry(t,s,yts);
        network_BQ_matrix.add_entry(t,t,ytt);

        return;
    }


    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
    {
        kp = kp/abs(kp);
        ks = ks/abs(ks);
        kt = kt/abs(kt);

        Ym = 0.0;

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_BP_matrix.add_entry(p,p,ypp);
        network_BP_matrix.add_entry(p,s,yps);
        network_BP_matrix.add_entry(s,p,ysp);
        network_BP_matrix.add_entry(s,s,yss);


        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_BQ_matrix.add_entry(p,p,ypp);
        network_BQ_matrix.add_entry(p,s,yps);
        network_BQ_matrix.add_entry(s,p,ysp);
        network_BQ_matrix.add_entry(s,s,yss);
        return;
    }


    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        kp = kp/abs(kp);
        ks = ks/abs(ks);
        kt = kt/abs(kt);

        Ym = 0.0;

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zt;
        I /= conj(kt);
        ytp = I;

        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        ypt = I;

        network_BP_matrix.add_entry(p,p,ypp);
        network_BP_matrix.add_entry(p,t,ypt);
        network_BP_matrix.add_entry(t,p,ytp);
        network_BP_matrix.add_entry(t,t,ytt);


        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zt;
        I /= conj(kt);
        ytp = I;

        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        ypt = I;

        network_BQ_matrix.add_entry(p,p,ypp);
        network_BQ_matrix.add_entry(p,t,ypt);
        network_BQ_matrix.add_entry(t,p,ytp);
        network_BQ_matrix.add_entry(t,t,ytt);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        kp = kp/abs(kp);
        ks = ks/abs(ks);
        kt = kt/abs(kt);

        Ym = 0.0;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zt;
        I /= conj(kt);
        yts = I;

        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        yst = I;

        network_BP_matrix.add_entry(s,s,yss);
        network_BP_matrix.add_entry(s,t,yst);
        network_BP_matrix.add_entry(t,s,yts);
        network_BP_matrix.add_entry(t,t,ytt);


        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zt;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zt;
        I /= conj(kt);
        yts = I;

        V = 1.0;
        V = V/kt;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zt + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        yst = I;

        network_BQ_matrix.add_entry(s,s,yss);
        network_BQ_matrix.add_entry(s,t,yst);
        network_BQ_matrix.add_entry(t,s,yts);
        network_BQ_matrix.add_entry(t,t,ytt);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
    {
        network_BP_matrix.add_entry(p,p,0.0);

        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/kp;
        Zeq = Zp + 1.0/Ym;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        network_BQ_matrix.add_entry(p,p,ypp);


        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==true and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==false)
    {
        network_BP_matrix.add_entry(s,s,0.0);


        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/ks;
        Zeq = Zs + 1.0/Ym;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        network_BQ_matrix.add_entry(s,s,yss);

        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and
       trans.get_winding_breaker_status(SECONDARY_SIDE)==false and
       trans.get_winding_breaker_status(TERTIARY_SIDE)==true)
    {
        network_BP_matrix.add_entry(t,t,0.0);


        kp = abs(kp_store);
        ks = abs(ks_store);
        kt = abs(kt_store);

        Ym = Ym_store;

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());
        Zt = complex<double>(0.0, Zt.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/kt;
        Zeq = Zt + 1.0/Ym;
        I = V/Zeq;
        I /= conj(kt);
        ytt = I;

        network_BQ_matrix.add_entry(t,t,ytt);
        return;
    }
}

void NETWORK_DATABASE::add_two_winding_transformer_to_decoupled_network_v2(const TRANSFORMER& trans)
{
    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and trans.get_winding_breaker_status(SECONDARY_SIDE)==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding two-winding transformer '%s' connecting to bus %u and %u to network Y matrix.", trans.get_identifier().c_str(),
                  trans.get_winding_bus(PRIMARY_SIDE), trans.get_winding_bus(SECONDARY_SIDE));
    show_information_with_leading_time_stamp(sstream);
    */

    size_t primary_bus = trans.get_winding_bus(PRIMARY_SIDE);
    size_t secondary_bus = trans.get_winding_bus(SECONDARY_SIDE);

    size_t p = inphno.get_internal_bus_number_of_physical_bus_number(primary_bus);
    size_t s = inphno.get_internal_bus_number_of_physical_bus_number(secondary_bus);

    complex<double> Zps = trans.get_leakage_impedance_between_windings_based_on_system_base_power_in_pu(PRIMARY_SIDE, SECONDARY_SIDE);
    complex<double> Ym = trans.get_magnetizing_admittance_based_on_winding_norminal_voltage_and_system_base_power_in_pu();

    complex<double> Zp, Zs;
    Zp = 0.5*Zps; Zs = Zp;

    double tap_primary = trans.get_winding_off_nominal_turn_ratio_in_pu(PRIMARY_SIDE);
    double angle_primary = trans.get_winding_angle_shift_in_deg(PRIMARY_SIDE);
    angle_primary = deg2rad(angle_primary);
    double tap_secondary = trans.get_winding_off_nominal_turn_ratio_in_pu(SECONDARY_SIDE);
    double angle_secondary = trans.get_winding_angle_shift_in_deg(SECONDARY_SIDE);
    angle_secondary = deg2rad(angle_secondary);

    complex<double> kp(tap_primary*cos(angle_primary),tap_primary*sin(angle_primary)),
                    ks(tap_secondary*cos(angle_secondary),tap_secondary*sin(angle_secondary));


    complex<double> V, I, Vstar;
    complex<double> ypp, yps, ysp, yss, Yeq, Zeq;

    complex<double> kp_store, ks_store, Ym_store;
    kp_store = kp;
    ks_store = ks;
    Ym_store = Ym;

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and trans.get_winding_breaker_status(SECONDARY_SIDE)==true)
    {
        kp = kp/abs(kp);
        ks = ks/abs(ks);
        Ym = 0.0;

        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_BP_matrix.add_entry(p,p,ypp);
        network_BP_matrix.add_entry(p,s,yps);
        network_BP_matrix.add_entry(s,p,ysp);
        network_BP_matrix.add_entry(s,s,yss);


        kp = kp_store;
        ks = ks_store;

        kp = abs(kp);
        ks = abs(ks);

        Zp = complex<double>(0.0, Zp.imag());
        Zs = complex<double>(0.0, Zs.imag());

        Ym = 0.0;
        V = 1.0;
        V = V/kp;
        Yeq = Ym + 1.0/Zs;
        Zeq = Zp + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(kp);
        ypp = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zs;
        I /= conj(ks);
        ysp = I;

        V = 1.0;
        V = V/ks;
        Yeq = Ym + 1.0/Zp;
        Zeq = Zs + 1.0/Yeq;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        Vstar = V*(1.0/Yeq)/Zeq;
        I = -Vstar/Zp;
        I /= conj(kp);
        yps = I;

        network_BQ_matrix.add_entry(p,p,ypp);
        network_BQ_matrix.add_entry(p,s,yps);
        network_BQ_matrix.add_entry(s,p,ysp);
        network_BQ_matrix.add_entry(s,s,yss);

        Ym = Ym_store;
        Ym = complex<double>(0.0, Ym.imag());
        network_BQ_matrix.add_entry(p,p,Ym);

        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==true and trans.get_winding_breaker_status(SECONDARY_SIDE)==false)
    {
        network_BP_matrix.add_entry(p,p,0.0);

        Ym = complex<double>(0.0, Ym.imag());

        network_BQ_matrix.add_entry(p,p,Ym);
        return;
    }

    if(trans.get_winding_breaker_status(PRIMARY_SIDE)==false and trans.get_winding_breaker_status(SECONDARY_SIDE)==true)
    {
        network_BP_matrix.add_entry(s,s,0.0);

        ks = abs(ks);

        Zps = complex<double>(0.0, Zps.imag());
        Ym = complex<double>(0.0, Ym.imag());

        V = 1.0;
        V = V/ks;
        Zeq = Zps + 1.0/Ym;
        I = V/Zeq;
        I /= conj(ks);
        yss = I;

        network_BQ_matrix.add_entry(s,s,yss);
        return;
    }
}

void NETWORK_DATABASE::add_fixed_shunts_to_decoupled_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<FIXED_SHUNT*> shunts = psdb->get_all_fixed_shunts();

    size_t n = shunts.size();

    for(size_t i = 0; i!=n; ++i)
        add_fixed_shunt_to_decoupled_network(*(shunts[i]));
}


void NETWORK_DATABASE::add_fixed_shunt_to_decoupled_network(const FIXED_SHUNT& shunt)
{
    if(shunt.get_status()==false)
        return;

    /*ostringstream sstream;
    sstream<<"Adding fixed shunt '%s' at bus %u to network Y matrix.", shunt.get_identifier().c_str(),
                  shunt.get_shunt_bus());
    show_information_with_leading_time_stamp(sstream);
    */

    size_t bus = shunt.get_shunt_bus();

    size_t i = inphno.get_internal_bus_number_of_physical_bus_number(bus);

    complex<double> Yshunt = shunt.get_nominal_admittance_shunt_in_pu();

    network_BP_matrix.add_entry(i,i, 0.0);
    network_BQ_matrix.add_entry(i,i, Yshunt);
    return;
}


void NETWORK_DATABASE::add_bus_fault_to_dynamic_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<BUS*> buses = psdb->get_all_buses();

    size_t n = buses.size();

    BUS* bus;

    for(size_t i = 0; i!=n; ++i)
    {
        bus = buses[i];
        if(bus->get_bus_type()==OUT_OF_SERVICE)
            continue;

        if(bus->is_faulted())
        {
            FAULT fault = bus->get_fault();
            complex<double> y = fault.get_fault_shunt_in_pu();
            size_t j = inphno.get_internal_bus_number_of_physical_bus_number(bus->get_bus_number());
            network_Y_matrix.add_entry(j,j, y);
        }
    }
}


void NETWORK_DATABASE::add_lines_to_dynamic_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<LINE*> lines = psdb->get_all_lines();

    size_t n = lines.size();

    for(size_t i = 0; i!=n; ++i)
    {
        if(not lines[i]->is_faulted())
           add_line_to_network(*(lines[i]));
        else
           add_faulted_line_to_dynamic_network(*(lines[i]));
    }
}

void NETWORK_DATABASE::add_faulted_line_to_dynamic_network(const LINE& line)
{
    if(line.get_sending_side_breaker_status()==false and line.get_receiving_side_breaker_status()==false)
        return;

    if(not line.is_faulted())
    {
        add_line_to_network(line);
        return;
    }

    /*ostringstream sstream;
    sstream<<"Adding line '%s' connecting to bus %u and %u to network Y matrix.", line.get_identifier().c_str(),
                  line.get_sending_side_bus(), line.get_receiving_side_bus());
    show_information_with_leading_time_stamp(sstream);*/

    size_t sending_bus = line.get_sending_side_bus();
    size_t receiving_bus = line.get_receiving_side_bus();

    size_t i = inphno.get_internal_bus_number_of_physical_bus_number(sending_bus);
    size_t j = inphno.get_internal_bus_number_of_physical_bus_number(receiving_bus);

    complex<double> Zline = line.get_line_positive_sequence_z_in_pu();
    complex<double> Yline = line.get_line_positive_sequence_y_in_pu();
    complex<double> Yshunt_sending = line.get_shunt_positive_sequence_y_at_sending_side_in_pu();
    complex<double> Yshunt_receiving = line.get_shunt_positive_sequence_y_at_receiving_side_in_pu();

    size_t nfault = line.get_fault_count();
    // take care of fault at two ends
    FAULT fault = line.get_fault_at_location(line.get_sending_side_bus(), 0.0);
    Yshunt_sending += fault.get_fault_shunt_in_pu();

    fault = line.get_fault_at_location(line.get_sending_side_bus(), 1.0);
    Yshunt_receiving += fault.get_fault_shunt_in_pu();

    vector<SUBLINE> sublines;

    double starting_fault_location;
    size_t n;

    for(size_t k=0; k!=nfault; ++k)
    {
        double this_fault_location = line.get_fault_location_of_fault(k);
        if(this_fault_location == 0.0 or this_fault_location == 1.0)
            continue;

        n = sublines.size();
        if(n==0)
            starting_fault_location = 0.0;
        else
            starting_fault_location = sublines[n-1].to_loc;

        SUBLINE sl;
        sl.from_loc = starting_fault_location;
        sl.to_loc = this_fault_location;
        sublines.push_back(sl);
    }
    n = sublines.size();
    if(n==0)
        starting_fault_location = 0.0;
    else
        starting_fault_location = sublines[n-1].to_loc;

    SUBLINE sl;
    sl.from_loc = starting_fault_location;
    sl.to_loc = 1.0;
    sublines.push_back(sl);

    complex<double> V, Y, Z, y, z, I;
    if(line.get_sending_side_breaker_status()==true and line.get_receiving_side_breaker_status()==true)
    {
        V = 1.0; // source at sending side, receiving side shorted
        Y = 0.0; Z = 0;
        n = sublines.size();
        double line_length = sublines[n-1].to_loc - sublines[n-1].from_loc;
        y = Yline*line_length; z = Zline*line_length;
        Z = z; Y = 1.0/Z+y*0.5;
        for(int k=n-2; k>=0; k--)
        {
            double fault_location = sublines[k].to_loc;
            line_length = sublines[k].to_loc - sublines[k].from_loc;
            fault = line.get_fault_at_location(line.get_sending_side_bus(), fault_location);
            complex<double> yfault = fault.get_fault_shunt_in_pu();
            y = Yline*line_length; z = Zline*line_length;
            Y = Y+y*0.5+yfault; Z = z+1.0/Y;
            Y = 1.0/Z+y*0.5;
        }
        Y = Y+Yshunt_sending;
        I = V*Y;
        network_Y_matrix.add_entry(i,i, I);
        Y = Yshunt_sending;
        I = I-V*Y;
        for(size_t k=0; k!=n; ++k)
        {
            double fault_location = sublines[k].to_loc;
            line_length = sublines[k].to_loc - sublines[k].from_loc;
            y = Yline*line_length; z = Zline*line_length;
            I = I-V*y*0.5;
            V = V-I*z;
            if(fault_location!=1.0)
            {
                I = I - V*y*0.5;
                fault = line.get_fault_at_location(line.get_sending_side_bus(), fault_location);
                complex<double> yfault = fault.get_fault_shunt_in_pu();
                I = I - V*yfault;
            }
        }
        network_Y_matrix.add_entry(j,i, -I);
        network_Y_matrix.add_entry(i,j, -I);

        V = 1.0; // source at receiving side, sending side shorted

        n = sublines.size();
        line_length = sublines[0].to_loc - sublines[0].from_loc;
        y = Yline*line_length; z = Zline*line_length;
        Z = z; Y = 1.0/Z+y*0.5;
        for(size_t k=1; k!=n; ++k)
        {
            double fault_location = sublines[k].from_loc;
            line_length = sublines[k].to_loc - sublines[k].from_loc;
            y = Yline*line_length; z = Zline*line_length;
            fault = line.get_fault_at_location(line.get_sending_side_bus(), fault_location);
            complex<double> yfault = fault.get_fault_shunt_in_pu();
            Y = Y+y*0.5+yfault; Z = z+1.0/Y;
            Y = 1.0/Z+y*0.5;
        }
        Y = Y+Yshunt_receiving;
        I = V*Y;
        network_Y_matrix.add_entry(j,j, I);
        return;
    }

    if(line.get_sending_side_breaker_status()==true and line.get_receiving_side_breaker_status()==false)
    {
        V = 1.0; // source at sending side
        Y = Yshunt_receiving; Z = 0;
        n = sublines.size();
        for(int k=n-1; k>=0; k--)
        {
            double fault_location = sublines[k].from_loc;
            double line_length = sublines[k].to_loc - sublines[k].from_loc;
            complex<double> yfault = 0.0;
            if(fault_location!=0.0)
            {
                fault = line.get_fault_at_location(line.get_sending_side_bus(), fault_location);
                yfault = fault.get_fault_shunt_in_pu();
            }
            y = Yline*line_length; z = Zline*line_length;
            Y = Y+y*0.5; Z = z+1.0/Y;
            Y = 1.0/Z+y*0.5+yfault;
        }
        Y = Y+Yshunt_sending;
        I = V*Y;
        network_Y_matrix.add_entry(i,i, I);
        return;
    }

    if(line.get_sending_side_breaker_status()==false and line.get_receiving_side_breaker_status()==true)
    {
        V = 1.0; // source at receiving side
        Y = Yshunt_sending; Z = 0;
        n = sublines.size();
        int nint = int(n);
        for(int k=0; k!=nint; ++k)
        {
            double fault_location = sublines[k].to_loc;
            double line_length = sublines[k].to_loc - sublines[k].from_loc;
            complex<double> yfault = 0.0;
            if(fault_location!=1.0)
            {
                fault = line.get_fault_at_location(line.get_sending_side_bus(), fault_location);
                yfault = fault.get_fault_shunt_in_pu();
            }
            y = Yline*line_length; z = Zline*line_length;
            Y = Y+y*0.5; Z = z+1.0/Y;
            Y = 1.0/Z+y*0.5+yfault;
        }
        Y = Y+Yshunt_receiving;
        I = V*Y;
        network_Y_matrix.add_entry(j,j, I);
        return;
    }

}

void NETWORK_DATABASE::add_generators_to_dynamic_network()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    vector<GENERATOR*> generators = psdb->get_all_generators();

    size_t n= generators.size();

    for(size_t i=0; i!=n; ++i)
        add_generator_to_dynamic_network(*(generators[i]));
}

void NETWORK_DATABASE::add_generator_to_dynamic_network(const GENERATOR& gen)
{
    if(gen.get_status()==false)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    complex<double> Z = gen.get_source_impedance_in_pu();
    double mbase = gen.get_mbase_in_MVA();
    double mvabase = psdb->get_system_base_power_in_MVA();
    Z = Z/mbase*mvabase;

    size_t bus = gen.get_generator_bus();
    size_t i = inphno.get_internal_bus_number_of_physical_bus_number(bus);
    network_Y_matrix.add_entry(i,i,1.0/Z);
}

void NETWORK_DATABASE::optimize_network_ordering()
{
    if(not is_power_system_database_set())
        return;

    initialize_physical_internal_bus_pair();

    build_network_matrix();

    reorder_physical_internal_bus_pair();
}

bool NETWORK_DATABASE::is_condition_ok() const
{
    return true;
}

void NETWORK_DATABASE::initialize_physical_internal_bus_pair()
{
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    psdb->check_device_status_for_out_of_service_buses();
    vector<BUS*> buses = psdb->get_all_buses();

    size_t nbus = buses.size();

    if(nbus==0)
        return;

    inphno.clear();

    size_t bus_number;
    size_t internal_bus_number = 0;
    for(size_t i=0; i!=nbus; ++i)
    {
        if(buses[i]->get_bus_type()==OUT_OF_SERVICE)
            continue;
        bus_number = buses[i]->get_bus_number();
        inphno.set_physical_internal_bus_number_pair(bus_number, internal_bus_number);
        internal_bus_number ++;
    }
}

void NETWORK_DATABASE::reorder_physical_internal_bus_pair()
{
    vector<size_t> permutation = network_Y_matrix.get_reorder_permutation();
    inphno.update_with_new_internal_bus_permutation(permutation);

    ostringstream sstream;
    sstream<<"Network internal bus numbers are optimized.";
    show_information_with_leading_time_stamp(sstream);

    /*os<<"After optimizing the network with network optimizer, the internal buses are listed as follows");
    show_information_with_leading_time_stamp(sstream);

    sstream<<"internal   physical   storage");
    show_information_with_leading_time_stamp(sstream);

    size_t bus, index, nbus;

    nbus = get_in_service_bus_count();

    for(size_t i=0; i!=nbus; ++i)
    {
        bus = get_physical_bus_number_of_internal_bus(i);
        index = get_bus_index(bus);
        sstream<<"%-10u %-10u %-10u",i, bus, index);
        show_information_with_leading_time_stamp(sstream);
    }*/

    /*os<<"Permutation for reorder internal bus:");
    show_information_with_leading_time_stamp(sstream);

    size_t nperm = permutation.size();
    for(size_t i=0; i!=nperm; ++i)
    {
        sstream<<"%u ---> %u",i,permutation[i]);
        show_information_with_leading_time_stamp(sstream);
    }
    */

}

void NETWORK_DATABASE::check_newtork_connectivity()
{
    if(not is_power_system_database_set())
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();

    vector< vector<size_t> > islands = get_islands_with_physical_bus_number();

    size_t nislands = islands.size();

    ostringstream sstream;
    sstream<<"There are "<<nislands<<" islands.";
    show_information_with_leading_time_stamp(sstream);

    size_t physical_bus;
    bool there_is_slack_bus_in_island;
    BUS* bus;
    for(size_t i=0; i!=nislands; ++i)
    {
        sstream<<"Physical buses in island "<<i<<":";
        show_information_with_leading_time_stamp(sstream);
        there_is_slack_bus_in_island = false;
        size_t nbus = islands[i].size();
        for(size_t j=0; j!=nbus; ++j)
        {
            physical_bus = islands[i][j];
            bus = psdb->get_bus(physical_bus);
            if(bus->get_bus_type()==SLACK_TYPE)
            {
                sstream<<physical_bus<<" (Slack bus)";
                show_information_with_leading_time_stamp(sstream);
                there_is_slack_bus_in_island = true;
            }
            else
            {
                sstream<<physical_bus;
                show_information_with_leading_time_stamp(sstream);
            }
        }
        if(not there_is_slack_bus_in_island)
        {
            sstream<<"No slack bus is found in island "<<i<<".";
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

vector< vector<size_t> > NETWORK_DATABASE::get_islands_with_internal_bus_number()
{
    vector< vector<size_t> > islands;

    if(not is_power_system_database_set())
        return islands;

    if(inphno.empty())
        initialize_physical_internal_bus_pair();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();

    build_network_matrix();
    network_Y_matrix.report_brief();

    size_t nbus = psdb->get_in_service_bus_count();

    vector<bool> bus_searched_flag;
    bus_searched_flag.reserve(nbus);

    for(size_t i=0; i!=nbus; ++i)
    {
        size_t physical_bus = get_physical_bus_number_of_internal_bus(i);
        if(physical_bus!=INDEX_NOT_EXIST)
            bus_searched_flag.push_back(false);
        else
            bus_searched_flag.push_back(true);
    }

    while(true)
    {
        bool new_island_found = false;
        size_t first_bus_in_new_island;

        for(size_t i=0; i!=nbus; ++i)
        {
            if(bus_searched_flag[i]==false)
            {
                new_island_found = true;
                first_bus_in_new_island = i;
                break;
            }
        }

        if(new_island_found==false)
            break;

        vector<size_t> this_island;
        this_island.reserve(nbus);

        this_island.push_back(first_bus_in_new_island);
        bus_searched_flag[first_bus_in_new_island] = true;

        int searching_bus=0;
        size_t nbus_in_island = this_island.size();
        for(size_t i=0; i!=nbus_in_island; ++i)
        {
            searching_bus = this_island[i];
            int k_start = network_Y_matrix.get_starting_index_of_column(searching_bus);
            int k_end = network_Y_matrix.get_starting_index_of_column(searching_bus+1);
            int row_bus;
            for(int k=k_start; k!=k_end; ++k)
            {
                row_bus = network_Y_matrix.get_row_number_of_entry_index(k);
                if(row_bus!=searching_bus)
                {
                    if(bus_searched_flag[row_bus]==false)
                    {
                        this_island.push_back(row_bus);
                        nbus_in_island = this_island.size();
                        bus_searched_flag[row_bus] = true;
                    }
                }
            }
        }
        islands.push_back(this_island);
    }

    return islands;
}


vector< vector<size_t> > NETWORK_DATABASE::get_islands_with_physical_bus_number()
{
    vector< vector<size_t> > islands = get_islands_with_internal_bus_number();

    size_t nislands = islands.size();
    for(size_t i=0; i!= nislands; ++i)
    {
        size_t nbus_in_island = islands[i].size();
        for(size_t j=0; j!=nbus_in_island; ++j)
            islands[i][j] = get_physical_bus_number_of_internal_bus(islands[i][j]);
    }

    return islands;
}

size_t NETWORK_DATABASE::get_internal_bus_number_of_physical_bus(size_t bus) const
{
    if(not is_power_system_database_set())
        return INDEX_NOT_EXIST;

    return inphno.get_internal_bus_number_of_physical_bus_number(bus);
}

size_t NETWORK_DATABASE::get_physical_bus_number_of_internal_bus(size_t bus) const
{
    if(is_power_system_database_set())
        return inphno.get_physical_bus_number_of_internal_bus_number(bus);
    else
        return INDEX_NOT_EXIST;
}

void NETWORK_DATABASE::report_network_matrix() const
{
    if(not is_power_system_database_set())
        return;

    ostringstream sstream;

    sstream<<"Network Y matrix lists begin:";
    show_information_with_leading_time_stamp(sstream);

    report_network_matrix_common();
}

void NETWORK_DATABASE::report_decoupled_network_matrix() const
{
    if(not is_power_system_database_set())
        return;

    ostringstream sstream;

    sstream<<"Network decoupled B matrix lists begin:";
    show_information_with_leading_time_stamp(sstream);

    sstream<<"row   [  bus  ]  column[  bus  ]     BP       BQ";
    show_information_with_leading_time_stamp(sstream);

    size_t i, ibus, jbus;
    size_t n = network_BP_matrix.get_matrix_size();
    int k_starting, k_ending;
    k_starting = 0;
    complex<double> y;
    double bp, bq;
    for(size_t j=0; j!=n; ++j)
    {
        k_ending = network_BP_matrix.get_starting_index_of_column(j+1);
        for(int k=k_starting; k!=k_ending; ++k)
        {
            y = network_BP_matrix.get_entry_value(k);
            bp = y.real();
            y = network_BQ_matrix.get_entry_value(k);
            bq = y.real();
            i = network_BP_matrix.get_row_number_of_entry_index(k);
            ibus = get_physical_bus_number_of_internal_bus(i);
            jbus = get_physical_bus_number_of_internal_bus(j);

            sstream<<setw(6)<<i<<"["
              <<setw(7)<<ibus<<"]  "
              <<setw(6)<<j<<"["
              <<setw(7)<<jbus<<"]  "
              <<setw(10)<<setprecision(6)<<fixed<<bp<<", "
              <<setw(10)<<setprecision(6)<<fixed<<bq<<endl;

            show_information_with_leading_time_stamp(sstream);
        }
        k_starting = k_ending;
    }
    sstream<<"Network decoupled B matrix lists finished.";
    show_information_with_leading_time_stamp(sstream);
}

void NETWORK_DATABASE::report_dynamic_network_matrix() const
{
    if(not is_power_system_database_set())
        return;

    ostringstream sstream;

    sstream<<"Network dynamic Y matrix lists begin:";
    show_information_with_leading_time_stamp(sstream);

	report_network_matrix_common();
}

void NETWORK_DATABASE::report_network_matrix_common() const
{
    ostringstream sstream;

    sstream<<"row   [  bus  ]  column[  bus  ]     real       imaginary";
    show_information_with_leading_time_stamp(sstream);

    size_t i, ibus, jbus;
    size_t n = network_Y_matrix.get_matrix_size();
    int k_starting, k_ending;
    k_starting = 0;
    complex<double> y;
    for(size_t j=0; j!=n; ++j)
    {
        k_ending = network_Y_matrix.get_starting_index_of_column(j+1);
        for(int k=k_starting; k!=k_ending; ++k)
        {
            y = network_Y_matrix.get_entry_value(k);
            i = network_Y_matrix.get_row_number_of_entry_index(k);
            ibus = get_physical_bus_number_of_internal_bus(i);
            jbus = get_physical_bus_number_of_internal_bus(j);

            sstream<<setw(6)<<i<<"["
              <<setw(7)<<ibus<<"]  "
              <<setw(6)<<j<<"["
              <<setw(7)<<jbus<<"]  "
              <<setw(10)<<setprecision(6)<<fixed<<y.real()<<", "
              <<setw(10)<<setprecision(6)<<fixed<<y.imag()<<endl;
            show_information_with_leading_time_stamp(sstream);
        }
        k_starting = k_ending;
    }
    sstream<<"Network matrix lists finished.";
    show_information_with_leading_time_stamp(sstream);
}

void NETWORK_DATABASE::save_network_matrix_to_file(string filename) const
{
    ostringstream sstream;

    ofstream file(filename);
    if(not file.is_open())
    {
        sstream<<"File '"<<filename<<"' cannot be opened for saving network matrix to file."<<endl
          <<"No network matrix will be exported.";
        show_information_with_leading_time_stamp(sstream);
        return;
    }

    file<<"ROW,ROW_BUS,COLUMN,COLUMN_BUS,REAL,IMAGINARY"<<endl;

    size_t i, ibus, jbus;
    size_t n = network_Y_matrix.get_matrix_size();
    int k_starting, k_ending;
    k_starting = 0;
    complex<double> y;
    for(size_t j=0; j!=n; ++j)
    {
        k_ending = network_Y_matrix.get_starting_index_of_column(j+1);
        for(int k=k_starting; k!=k_ending; ++k)
        {
            y = network_Y_matrix.get_entry_value(k);
            i = network_Y_matrix.get_row_number_of_entry_index(k);
            ibus = get_physical_bus_number_of_internal_bus(i);
            jbus = get_physical_bus_number_of_internal_bus(j);

            file<<i<<","<<ibus<<","<<j<<","<<jbus<<","
                <<setprecision(6)<<fixed<<y.real()<<","
                <<setprecision(6)<<fixed<<y.imag()<<endl;
        }
        k_starting = k_ending;
    }
    file.close();
}

void NETWORK_DATABASE::report_physical_internal_bus_number_pair() const
{
    if(not is_power_system_database_set())
        return;

    inphno.report();
}




bool NETWORK_DATABASE::is_valid() const
{
    return true; // disabled.
}
void NETWORK_DATABASE::check()
{
    ;// disabled.
}
void NETWORK_DATABASE::clear()
{
    ; // disabled
}