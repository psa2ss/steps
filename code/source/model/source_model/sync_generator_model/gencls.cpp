#include "header/model/source_model/sync_generator_model/gencls.h"
#include "header/basic/utility.h"
#include <cstdio>
#include <iostream>
using namespace std;

static vector<string> MODEL_VARIABLE_TABLE{ "GENERATOR ROTOR ANGLE IN DEG",      //0
                                            "GENERATOR ROTOR SPEED DEVIATION IN PU",      //1
                                            "GENERATOR AIR GAP POWER IN PU",      //2
                                            "GENERATOR AIR GAP POWER IN MW",      //3
                                            "GENERATOR TERMINAL P IN PU",      //4
                                            "GENERATOR TERMINAL P IN MW",      //5
                                            "GENERATOR TERMINAL Q IN PU",      //6
                                            "GENERATOR TERMINAL Q IN MVAR",      //7
                                            "GENERATOR TERMINAL S IN PU",      //8
                                            "GENERATOR TERMINAL S IN MVA",      //9
                                            "GENERATOR MECHANICAL POWER IN PU",      //10
                                            "GENERATOR MECHANICAL POWER IN MW",      //11
                                            "GENERATOR EXCITATION VOLTAGE IN PU",      //12
                                            "GENERATOR INTERNAL VOLTAGE IN PU",      //13
                                            "GENERATOR TERMINAL CURRENT IN PU",      //14
                                            "GENERATOR TERMINAL CURRENT IN KA",      //15
                                            "STATE@ROTOR ANGLE BLOCK",     //16
                                            "STATE@ROTOR SPEED BLOCK"    //17
                                            };


GENCLS::GENCLS()
{
    clear();
}

GENCLS::~GENCLS()
{
    clear();
}

void GENCLS::clear()
{
    ;
}
void GENCLS::copy_from_const_model(const GENCLS& model)
{
    clear();

    this->set_Tj_in_s(model.get_Tj_in_s());
    this->set_D(model.get_D());
    this->set_Rs(model.get_Rs());
    this->set_Xdp(model.get_Xdp());

}
GENCLS::GENCLS(const GENCLS& model):SYNC_GENERATOR_MODEL()
{
    copy_from_const_model(model);
}

GENCLS& GENCLS::operator=(const GENCLS& model)
{
    if(this==&model)
        return *this;

    copy_from_const_model(model);

    return (*this);
}

string GENCLS::get_model_name() const
{
    return "GENCLS";
}


void GENCLS::update_source_impedance()
{
    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    if(generator!=NULL)
    {
        complex<double> Zs = generator->get_source_impedance_in_pu();
        double rs = Zs.real();
        double xs = Zs.imag();
        set_Rs(rs);
        set_Xdp(xs);
    }
}


bool GENCLS::setup_model_with_steps_string(string data)
{
    return false;
}

bool GENCLS::setup_model_with_psse_string(string data)
{
    bool is_successful = false;
    vector<string> dyrdata = split_string(data,",");

    if(dyrdata.size()<5)
        return is_successful;

    string model_name = get_string_data(dyrdata[1],"");
    if(model_name!="GENCLS")
        return is_successful;

    double H, D;

    size_t i=3;
    H = get_double_data(dyrdata[i],"0.0"); i++;
    D = get_double_data(dyrdata[i],"0.0");

    set_H_in_s(H);
    set_D(D);

    is_successful = true;

    return is_successful;
}

bool GENCLS::setup_model_with_bpa_string(string data)
{
    return false;
}

void GENCLS::initialize()
{
    update_source_impedance();

    // rotor angle and speed
    initialize_rotor_angle();

    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();

    double speed = 0.0;
    rotor_speed_block->set_output(speed);
    rotor_speed_block->initialize();

    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    double mbase = get_mbase_in_MVA();

    double rs = get_Rs();
    double xdp = get_Xdp();
    complex<double> Zsource(rs, xdp);

    double P = generator->get_p_generation_in_MW();
    double Q = generator->get_q_generation_in_MVar();
    complex<double> S(P/mbase,Q/mbase);

    complex<double> Vxy = get_terminal_complex_voltage_in_pu();

    // mechanical power
    complex<double> Ixy = conj(S/Vxy);
    double I = abs(Ixy);
    double pmech0 = S.real()+I*I*rs;
    set_initial_mechanical_power_in_pu_based_on_mbase(pmech0);
    // excitation voltage
    complex<double> Exy = Vxy+Ixy*Zsource;
    double efd0 = abs(Exy);
    set_initial_excitation_voltage_in_pu(efd0);
}

void GENCLS::initialize_rotor_angle()
{
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    double rs = get_Rs();
    double xdp = get_Xdp();
    complex<double> Z(rs, xdp);

    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    double P = generator->get_p_generation_in_MW();
    double Q = generator->get_q_generation_in_MVar();
    double mbase = get_mbase_in_MVA();

    complex<double> S(P/mbase,Q/mbase);

    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Ixy = conj(S/Vxy);

    complex<double> Exy = Vxy+Ixy*Z;

    double rotor_angle = arg(Exy/Vxy)+arg(Vxy);

    rotor_angle_block->set_output(rotor_angle);
    rotor_angle_block->initialize();

    set_flag_model_initialized_as_true();
}

void GENCLS::run(DYNAMIC_MODE mode)
{
    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double fbase = psdb->get_system_base_frequency_in_Hz();

    double damping = get_D();

    double pmech = get_mechanical_power_in_pu_based_on_mbase();
    double speed = get_rotor_speed_deviation_in_pu();
    double omega = get_rotor_speed_in_pu();
    double tmech = pmech/omega;

    //double pelec = get_air_gap_power_in_pu_based_on_mbase();
    double telec = get_air_gap_torque_in_pu_based_on_mbase();

    double delta_torque = tmech-telec-damping*speed;
    //double input = pmech-pelec - D*speed;
    rotor_speed_block->set_input(delta_torque);
    rotor_speed_block->run(mode);

    speed = get_rotor_speed_deviation_in_pu();

    speed = 2.0*PI*fbase*speed;
    rotor_angle_block->set_input(speed);
    rotor_angle_block->run(mode);

    if(mode==UPDATE_MODE)
        set_flag_model_updated_as_true();
}

complex<double> GENCLS::get_source_Norton_equivalent_complex_current_in_pu_in_xy_axis_based_on_sbase()
{
    complex<double> Exy = get_internal_voltage_in_pu_in_xy_axis();
    complex<double> Z(get_Rs(), get_Xdp());
    double mbase = get_mbase_in_MVA();
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double sbase = psdb->get_system_base_power_in_MVA();

    return Exy/Z*mbase/sbase;
}

complex<double> GENCLS::get_terminal_complex_current_in_pu_in_dq_axis_based_on_mbase()
{
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();

    double angle = get_rotor_angle_in_rad();

    return xy2dq_with_angle_in_rad(Ixy, angle);
}

complex<double> GENCLS::get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase()
{
    complex<double> Exy = get_internal_voltage_in_pu_in_xy_axis();
    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Zsource(get_Rs(), get_Xdp());
    complex<double> Ixy = (Exy-Vxy)/Zsource;

    return Ixy;
}

complex<double> GENCLS::get_terminal_complex_current_in_pu_in_xy_axis_based_on_sbase()
{
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();
    double mbase = get_mbase_in_MVA();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double sbase = psdb->get_system_base_power_in_MVA();

    return Ixy*mbase/sbase;
}

double GENCLS::get_terminal_current_in_pu_based_on_mbase()
{
    return abs(get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase());
}

double GENCLS::get_terminal_current_in_pu_based_on_sbase()
{
    double I = get_terminal_current_in_pu_based_on_mbase();
    double mbase = get_mbase_in_MVA();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double sbase = psdb->get_system_base_power_in_MVA();

    return I*mbase/sbase;
}


void GENCLS::check()
{
    ;
}

void GENCLS::report()
{
    ostringstream sstream;
    sstream<< get_standard_model_string();
    show_information_with_leading_time_stamp(sstream);
}

void GENCLS::save()
{
    ;
}

string GENCLS::get_standard_model_string() const
{
    ostringstream sstream;
    DEVICE_ID did = get_device_id();
    size_t bus = did.get_device_terminal().get_buses()[0];
    string identifier = did.get_device_identifier();

    sstream<<setw(8)<<bus<<", "
      <<"'"<<get_model_name()<<"', "
      <<"'"<<identifier<<"', "
      <<setw(8)<<setprecision(6)<<get_H_in_s()<<", "
      <<setw(8)<<setprecision(6)<<get_D()<<"  /";
    return sstream.str();
}

size_t GENCLS::get_variable_index_from_variable_name(string var_name)
{
    return MODEL::get_variable_index_from_variable_name(var_name, MODEL_VARIABLE_TABLE);
}

string GENCLS::get_variable_name_from_variable_index(size_t var_index)
{
    return MODEL::get_variable_name_from_variable_index(var_index, MODEL_VARIABLE_TABLE);
}

double GENCLS::get_variable_with_index(size_t var_index)
{
    string var_name = get_variable_name_from_variable_index(var_index);
    return get_variable_with_name(var_name);
}

double GENCLS::get_variable_with_name(string var_name)
{
    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    var_name = string2upper(var_name);
    if(var_name == "GENERATOR ROTOR ANGLE IN DEG")
        return get_rotor_angle_in_deg();
    if(var_name == "GENERATOR ROTOR SPEED DEVIATION IN PU")
        return get_rotor_speed_deviation_in_pu();
    if(var_name == "GENERATOR AIR GAP POWER IN PU")
        return get_air_gap_power_in_pu_based_on_mbase();
    if(var_name == "GENERATOR AIR GAP POWER IN MW")
        return get_air_gap_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
    if(var_name == "GENERATOR TERMINAL P IN PU")
        return get_terminal_active_power_in_pu_based_on_mbase();
    if(var_name == "GENERATOR TERMINAL P IN MW")
        return get_terminal_active_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
    if(var_name == "GENERATOR TERMINAL Q IN PU")
        return get_terminal_reactive_power_in_pu_based_on_mbase();
    if(var_name == "GENERATOR TERMINAL Q IN MW")
        return get_terminal_reactive_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
    if(var_name == "GENERATOR TERMINAL S IN PU")
        return abs(get_terminal_complex_power_in_pu_based_on_mbase());
    if(var_name == "GENERATOR TERMINAL S IN MVA")
        return abs(get_terminal_complex_power_in_pu_based_on_mbase())*get_mbase_in_MVA();
    if(var_name == "GENERATOR MECHANICAL POWER IN PU")
        return get_mechanical_power_in_pu_based_on_mbase();
    if(var_name == "GENERATOR MECHANICAL POWER IN MW")
        return get_mechanical_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
    if(var_name == "GENERATOR EXCITATION VOLTAGE IN PU")
        return get_excitation_voltage_in_pu();
    if(var_name == "GENERATOR INTERNAL VOLTAGE IN PU")
        return abs(get_internal_voltage_in_pu_in_xy_axis());
    if(var_name == "GENERATOR TERMINAL CURRENT IN PU")
        return get_terminal_current_in_pu_based_on_mbase();
    if(var_name == "GENERATOR TERMINAL CURRENT IN KA")
    {
        POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
        GENERATOR* generator = (GENERATOR*) get_device_pointer();
        size_t bus = generator->get_generator_bus();
        double vbase = psdb->get_bus_base_voltage_in_kV(bus);
        double mbase = generator->get_mbase_in_MVA();
        double ibase = mbase/sqrt(3.0)/vbase;
        return get_terminal_current_in_pu_based_on_mbase()*ibase;
    }
    if(var_name == "STATE@ROTOR ANGLE BLOCK")
        return rotor_angle_block->get_state();
    if(var_name == "STATE@ROTOR SPEED BLOCK")
        return rotor_speed_block->get_state();

    return 0.0;
}

double GENCLS::get_air_gap_power_in_pu_based_on_mbase()
{
    complex<double> Exy = get_internal_voltage_in_pu_in_xy_axis();
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();

    complex<double> S = Exy*conj(Ixy);
    return S.real();
}

double GENCLS::get_air_gap_power_in_MW()
{
    return get_air_gap_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
}

double GENCLS::get_air_gap_torque_in_pu_based_on_mbase()
{
    double P = get_air_gap_power_in_pu_based_on_mbase();
    double omega = get_rotor_speed_in_pu();

    return P/omega;
}


double GENCLS::get_accelerating_power_in_pu_based_on_mbase()
{
    return get_mechanical_power_in_pu_based_on_mbase()-get_air_gap_power_in_pu_based_on_mbase();
}


double GENCLS::get_accelerating_power_in_MW()
{
    return get_accelerating_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
}


complex<double> GENCLS::get_terminal_complex_power_in_pu_based_on_mbase()
{
    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();

    complex<double> S = Vxy*conj(Ixy);
    return S;
}

complex<double> GENCLS::get_terminal_complex_power_in_MVA()
{
    return get_terminal_complex_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
}

double GENCLS::get_terminal_active_power_in_pu_based_on_mbase()
{
    return get_terminal_complex_power_in_pu_based_on_mbase().real();
}

double GENCLS::get_terminal_active_power_in_MW()
{
    return get_terminal_complex_power_in_MVA().real();
}

double GENCLS::get_terminal_reactive_power_in_pu_based_on_mbase()
{
    return get_terminal_complex_power_in_pu_based_on_mbase().imag();
}

double GENCLS::get_terminal_reactive_power_in_MVar()
{
    return get_terminal_complex_power_in_MVA().imag();
}

double GENCLS::get_field_current_in_pu_based_on_mbase()
{
    return 0.0;
}

double GENCLS::get_rotor_angle_in_rad()
{
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    return rotor_angle_block->get_output();
}

double GENCLS::get_rotor_angle_in_deg()
{
    return rad2deg(get_rotor_angle_in_rad());
}

double GENCLS::get_rotor_speed_deviation_in_pu()
{
    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();

    return rotor_speed_block->get_output();
}

double GENCLS::get_rotor_speed_in_pu()
{
    return 1.0+get_rotor_speed_deviation_in_pu();
}

complex<double> GENCLS::get_internal_voltage_in_pu_in_dq_axis()
{
    double Efd = get_excitation_voltage_in_pu();

    return complex<double>(0.0, Efd);
}

complex<double> GENCLS::get_internal_voltage_in_pu_in_xy_axis()
{
    complex<double> Edq = get_internal_voltage_in_pu_in_dq_axis();

    double angle = get_rotor_angle_in_rad();

    return dq2xy_with_angle_in_rad(Edq, angle);
}



void GENCLS::set_rotor_angle_in_deg(double angle)
{
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    rotor_angle_block->set_output(deg2rad(angle));
    rotor_angle_block->initialize(); // the initialize function is used to update STORE
}

void GENCLS::set_rotor_speed_deviation_in_pu(double speed)
{
    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();

    rotor_speed_block->set_output(speed);
    rotor_speed_block->initialize();
}



string GENCLS::get_dynamic_data_in_psse_format() const
{
    return "";
}

string GENCLS::get_dynamic_data_in_bpa_format() const
{
    return get_dynamic_data_in_psse_format();
}

string GENCLS::get_dynamic_data_in_steps_format() const
{
    return get_dynamic_data_in_psse_format();
}
