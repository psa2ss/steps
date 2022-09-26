#include "header/data_imexporter/steps_imexporter.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include <cstdio>
#include <istream>
#include <iostream>
#include <algorithm>
using namespace std;


void STEPS_IMEXPORTER::load_sequence_data_from_steps_vector(vector<vector<vector<string> > >& data)
{
    splitted_sseq_data_in_ram = data;
    if(splitted_sseq_data_in_ram.size()==0)
    {
        ostringstream osstream;
        osstream<<"No data in the given STEPS sequence vector <splitted_sseq_data_in_ram>."<<endl
                <<"Please check if the vector contents exist or not.";
        STEPS& toolkit = get_toolkit();
        toolkit.show_information_with_leading_time_stamp(osstream);

        return;
    }
    load_all_seq_data_to_devices();
}

void STEPS_IMEXPORTER::load_sequence_data(string sq_source)
{
    sq_source = string2upper(sq_source);
}

void STEPS_IMEXPORTER::load_all_seq_data_to_devices()
{
    load_change_code_data();
    load_source_seq_data();
    load_load_seq_data();
    load_zero_seq_non_transformer_branch_data();
    load_zero_seq_mutual_impedance_data();
    load_zero_seq_transformer_data();
    load_zero_seq_swithed_shunt_data();
    load_zero_seq_fixed_shunt_data();
    load_induction_machine_seq_data();
}

void STEPS_IMEXPORTER::load_change_code_data()
{
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();
    unsigned int IC;
    string REV;

    if(splitted_sseq_data_in_ram.size()<1)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[0];
    vector<string> data = DATA[0];

    if(data.size()>0)
    {
        IC = get_integer_data(data[0], "0");
        data.erase(data.begin());
    }

    if(data.size()>0)
    {
        REV = get_integer_data(data[0], "31");
        data.erase(data.begin());
    }
}

void STEPS_IMEXPORTER::load_source_seq_data()
{
    ostringstream osstream;

    if(splitted_sseq_data_in_ram.size()<2)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[1];
    vector<string> data;

    unsigned int ndata = DATA.size();

    unsigned int SOURCE_TYPE_INDEX = 13;
    for(unsigned int i=0; i!=ndata; ++i)
    {
        data = DATA[i];

        unsigned int n = data.size();

        SOURCE_TYPE source_type = SYNC_GENERATOR_SOURCE;
        if(n>SOURCE_TYPE_INDEX)
        {
            int type = get_integer_data(data[SOURCE_TYPE_INDEX],"0");
            switch(type)
            {
                case 0:
                    source_type = SYNC_GENERATOR_SOURCE;
                    break;
                case 1:
                    source_type = WT_GENERATOR_SOURCE;
                    break;
                case 2:
                    source_type = PV_UNIT_SOURCE;
                    break;
                case 3:
                    source_type = ENERGY_STORAGE_SOURCE;
                    break;
                default:
                    source_type = SYNC_GENERATOR_SOURCE;
                    break;
            }
        }
        switch(source_type)
        {
            case SYNC_GENERATOR_SOURCE:
            {
                load_generator_seq_data(data);
                break;
            }
            case WT_GENERATOR_SOURCE:
            {
                load_wt_generator_seq_data(data);
                break;
            }
            case PV_UNIT_SOURCE:
            {
                load_pv_unit_seq_data(data);
                break;
            }
            case ENERGY_STORAGE_SOURCE:
            {
                load_energy_storage_data(data);
                break;
            }
            default:
            {
                char buffer[STEPS_MAX_TEMP_CHAR_BUFFER_SIZE];
                snprintf(buffer, STEPS_MAX_TEMP_CHAR_BUFFER_SIZE, "Invalid source type is detected in seq file of line:\n%s",string_vector2csv(data).c_str());
                STEPS& toolkit = get_toolkit();
                toolkit.show_information_with_leading_time_stamp(buffer);
                break;
            }
        }
    }
}
void STEPS_IMEXPORTER::load_generator_seq_data(vector<string>& data)
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    unsigned int bus;
    string ID;
    double R_pos = 0.0, X_pos_subtransient = 0.0, X_pos_transient = 0.0, X_pos_sync = 0.0;
    double R_neg = 0.0, X_neg = 0.0;
    double R_zero = 0.0, X_zero = 0.0;
    unsigned int unit_of_grounding_Z;
    double R_ground = 0.0, X_ground = 0.0;
    unsigned int n = 0;

    if(data.size()>0)
    {
        bus = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        ID = get_string_data(data[n], "1");
        data.erase(data.begin());
    }
    DEVICE_ID did = get_generator_device_id(bus, ID);
    GENERATOR* generator = psdb.get_generator(did);
    if(generator ==  NULL)
    {
        osstream<<"Generator "<<ID<<" is not exist on bus "<<bus<<"."<<endl
                <<"Please check seq file.";
        toolkit.show_information_with_leading_time_stamp(osstream);
        return;
    }

    if(data.size()>0)
    {
        R_pos = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(R_pos == 0.0)
        R_pos = generator->get_source_impedance_in_pu().real();
    generator->set_positive_sequence_resistance_in_pu(R_pos);

    if(data.size()>0)
    {
        X_pos_subtransient = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(X_pos_subtransient == 0.0)
        X_pos_subtransient = generator->get_source_impedance_in_pu().imag();
    generator->set_positive_sequence_subtransient_reactance_in_pu(X_pos_subtransient);

    if(data.size()>0)
    {
        X_pos_transient = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    generator->set_positive_sequence_transient_reactance_in_pu(X_pos_transient);

    if(data.size()>0)
    {
        X_pos_sync = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    generator->set_positive_sequence_syncronous_reactance_in_pu(X_pos_sync);

    if(data.size()>0)
    {
        R_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    generator->set_negative_sequence_resistance_in_pu(R_neg);

    if(data.size()>0)
    {
        X_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    generator->set_negative_sequence_reactance_in_pu(X_neg);

    if(data.size()>0)
    {
        R_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    generator->set_zero_sequence_resistance_in_pu(R_zero);

    if(data.size()>0)
    {
        X_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    generator->set_zero_sequence_reactance_in_pu(X_zero);

    if(data.size()>0)
    {
        unit_of_grounding_Z = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        R_ground = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X_ground = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    if(unit_of_grounding_Z == 1)
    {
        generator->set_grounding_resistance_in_pu(R_ground);
        generator->set_grounding_reactance_in_pu(X_ground);
    }
    else if(unit_of_grounding_Z == 2)
    {
        double mbase = generator->get_mbase_in_MVA();
        double U = psdb.get_bus_base_voltage_in_kV(generator->get_generator_bus());
        double Zbase = U*U/mbase;
        generator->set_grounding_resistance_in_pu(R_ground/Zbase);
        generator->set_grounding_reactance_in_pu(X_ground/Zbase);
    }
}
void STEPS_IMEXPORTER::load_wt_generator_seq_data(vector<string>& data)
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    unsigned int bus;
    string ID;
    double R_pos = 0.0, X_pos_subtransient = 0.0, X_pos_transient = 0.0, X_pos_sync = 0.0;
    double R_neg = 0.0, X_neg = 0.0;
    double R_zero = 0.0, X_zero = 0.0;
    unsigned int unit_of_grounding_Z;
    double R_ground = 0.0, X_ground = 0.0;
    unsigned int n = 0;

    if(data.size()>0)
    {
        bus = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        ID = get_string_data(data[n], "1");
        data.erase(data.begin());
    }
    DEVICE_ID did = get_wt_generator_device_id(bus, ID);
    WT_GENERATOR* wt_generator = psdb.get_wt_generator(did);
    if(wt_generator == NULL)
    {
        osstream<<"WT generator "<<ID<<" is not exist on bus "<<bus<<"."<<endl
                <<"Please check seq file.";
        toolkit.show_information_with_leading_time_stamp(osstream);
        return;
    }

    if(data.size()>0)
    {
        R_pos = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(R_pos == 0.0)
        R_pos = wt_generator->get_source_impedance_in_pu().real();
    wt_generator->set_positive_sequence_resistance_in_pu(R_pos);

    if(data.size()>0)
    {
        X_pos_subtransient = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(X_pos_subtransient == 0.0)
        X_pos_subtransient = wt_generator->get_source_impedance_in_pu().imag();
    wt_generator->set_positive_sequence_subtransient_reactance_in_pu(X_pos_subtransient);

    if(data.size()>0)
    {
        X_pos_transient = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    wt_generator->set_positive_sequence_transient_reactance_in_pu(X_pos_transient);

    if(data.size()>0)
    {
        X_pos_sync = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    wt_generator->set_positive_sequence_syncronous_reactance_in_pu(X_pos_sync);

    if(data.size()>0)
    {
        R_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    wt_generator->set_negative_sequence_resistance_in_pu(R_neg);

    if(data.size()>0)
    {
        X_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    wt_generator->set_negative_sequence_reactance_in_pu(X_neg);

    if(data.size()>0)
    {
        R_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    wt_generator->set_zero_sequence_resistance_in_pu(R_zero);

    if(data.size()>0)
    {
        X_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    wt_generator->set_zero_sequence_reactance_in_pu(X_zero);

    if(data.size()>0)
    {
        unit_of_grounding_Z = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        R_ground = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X_ground = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    if(unit_of_grounding_Z == 1)
    {
        wt_generator->set_grounding_resistance_in_pu(R_ground);
        wt_generator->set_grounding_reactance_in_pu(X_ground);
    }
    else if(unit_of_grounding_Z == 2)
    {
        double mbase = wt_generator->get_mbase_in_MVA();
        double U = psdb.get_bus_base_voltage_in_kV(wt_generator->get_source_bus());
        double Zbase = U*U/mbase;
        wt_generator->set_grounding_resistance_in_pu(R_ground/Zbase);
        wt_generator->set_grounding_reactance_in_pu(X_ground/Zbase);
    }
}

void STEPS_IMEXPORTER::load_pv_unit_seq_data(vector<string>& data)
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    unsigned int bus;
    string ID;
    double R_pos = 0.0, X_pos = 0.0;
    double R_neg = 0.0, X_neg = 0.0;
    double R_zero = 0.0, X_zero = 0.0;
     unsigned int unit_of_grounding_Z;
     double R_ground = 0.0, X_ground = 0.0;
    unsigned int n = 0;

    if(data.size()>0)
    {
        bus = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        ID = get_string_data(data[n], "1");
        data.erase(data.begin());
    }
    DEVICE_ID did = get_pv_unit_device_id(bus, ID);
    PV_UNIT* pv_unit = psdb.get_pv_unit(did);
    if(pv_unit == NULL)
    {
        osstream<<"PV_UNIT "<<ID<<" is not exist on bus "<<bus<<"."<<endl
                <<"Please check seq file.";
        toolkit.show_information_with_leading_time_stamp(osstream);
        return;
    }

    if(data.size()>0)
    {
        R_pos = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(R_pos == 0.0)
        R_pos = pv_unit->get_source_impedance_in_pu().real();
    pv_unit->set_positive_sequence_resistance_in_pu(R_pos);

    if(data.size()>0)
    {
        X_pos = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(X_pos == 0.0)
        X_pos = pv_unit->get_source_impedance_in_pu().imag();
    pv_unit->set_positive_sequence_reactance_in_pu(X_pos);

    if(data.size()>0)
        data.erase(data.begin());
    if(data.size()>0)
        data.erase(data.begin());

    if(data.size()>0)
    {
        R_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    pv_unit->set_negative_sequence_resistance_in_pu(R_neg);

    if(data.size()>0)
    {
        X_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    pv_unit->set_negative_sequence_reactance_in_pu(X_neg);

    if(data.size()>0)
    {
        R_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    pv_unit->set_zero_sequence_resistance_in_pu(R_zero);

    if(data.size()>0)
    {
        X_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    pv_unit->set_zero_sequence_reactance_in_pu(X_zero);

    if(data.size()>0)
    {
        unit_of_grounding_Z = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        R_ground = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X_ground = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    if(unit_of_grounding_Z == 1)
    {
        pv_unit->set_grounding_resistance_in_pu(R_ground);
        pv_unit->set_grounding_reactance_in_pu(X_ground);
    }
    else if(unit_of_grounding_Z == 2)
    {
        double mbase = pv_unit->get_mbase_in_MVA();
        double U = psdb.get_bus_base_voltage_in_kV(pv_unit->get_source_bus());
        double Zbase = U*U/mbase;
        pv_unit->set_grounding_resistance_in_pu(R_ground/Zbase);
        pv_unit->set_grounding_reactance_in_pu(X_ground/Zbase);
    }
}

void STEPS_IMEXPORTER::load_load_seq_data()
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    if(splitted_sseq_data_in_ram.size()<3)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[2];
    vector<string> data;

    unsigned int ndata = DATA.size();

    unsigned int n = 0;
    unsigned int bus;
    string ID;
//    double P_neg = 0.0, Q_neg = 0.0;
//    unsigned int ground_flag = 0;
//    double P_zero = 0.0, Q_zero = 0.0;

    for(unsigned int i=0; i!=ndata; ++i)
    {
        data = DATA[i];

        if(data.size()>0)
        {
            bus = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ID = get_string_data(data[n], "1");
            data.erase(data.begin());
        }
        DEVICE_ID did = get_load_device_id(bus, ID);
        LOAD* loadptr = psdb.get_load(did);

        if(loadptr == NULL)
        {
            osstream<<"Load "<<ID<<" is not exist on bus "<<bus<<"."<<endl
                    <<"Please check seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        load_static_load_seq_data(*loadptr, data);
        if(data.size()>0)
            load_motor_load_seq_data(*loadptr, data);
        else
            loadptr->set_ratio_of_motor_active_power(0.0);
//        if(data.size()>0)
//        {
//            P_neg = get_double_data(data[n], "0.0");
//            data.erase(data.begin());
//        }
//        if(data.size()>0)
//        {
//            Q_neg = get_double_data(data[n], "0.0");
//            data.erase(data.begin());
//        }
//        if(P_neg<DOUBLE_EPSILON)
//            P_neg = loadptr->get_nominal_constant_power_load_in_MVA().real();
//        if(Q_neg<DOUBLE_EPSILON)
//            Q_neg = loadptr->get_nominal_constant_power_load_in_MVA().imag();
//        loadptr->set_negative_sequence_load_in_MVA(complex<double>(P_neg, Q_neg));
//
//        if(data.size()>0)
//        {
//            ground_flag = get_integer_data(data[n], "0");
//            data.erase(data.begin());
//        }
//        loadptr->set_grounding_flag(ground_flag);
//
//        if(data.size()>0)
//        {
//            P_zero = get_double_data(data[n], "0.0");
//            data.erase(data.begin());
//        }
//        if(data.size()>0)
//        {
//            Q_zero = get_double_data(data[n], "0.0");
//            data.erase(data.begin());
//        }
//        loadptr->set_zero_sequence_load_in_MVA(complex<double>(P_zero, Q_zero));
    }
}

void STEPS_IMEXPORTER::load_static_load_seq_data(LOAD& load, vector<string>& data)
{
    unsigned int n=0;
    double P_neg=0.0, Q_neg=0.0, P_zero=0.0, Q_zero=0.0;
    unsigned int ground_flag;
    if(data.size()>0)
    {
        P_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Q_neg = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(P_neg<DOUBLE_EPSILON)
        P_neg = load.get_nominal_constant_power_load_in_MVA().real();
    if(Q_neg<DOUBLE_EPSILON)
        Q_neg = load.get_nominal_constant_power_load_in_MVA().imag();
    load.set_negative_sequence_load_in_MVA(complex<double>(P_neg, Q_neg));

    if(data.size()>0)
    {
        ground_flag = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    load.set_grounding_flag(ground_flag);

    if(data.size()>0)
    {
        P_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Q_zero = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_zero_sequence_load_in_MVA(complex<double>(P_zero, Q_zero));
}

void STEPS_IMEXPORTER::load_motor_load_seq_data(LOAD& load, vector<string>& data)
{
    double ratio_of_motor_active_power = 0.0;
    unsigned int mbase_code = 0;
    double mbase = 0.0;
    double rated_voltage = 0.0;
    double Ra=0.0, Xa=0.0, Xm=0.0, R1=0.0, X1=0.0, R2=0.0, X2=0.0;
    double R_zero_seq=0.0, X_zero_seq=0.0;

    unsigned int n=0;

    if(data.size()>0)
    {
        ratio_of_motor_active_power = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_ratio_of_motor_active_power(ratio_of_motor_active_power);

    if(data.size()>0)
    {
        mbase_code = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    switch(mbase_code)
    {
        case 0:
            load.set_mbase_code(DEFAULT_RATIO_OF_ACTUAL_MACHINE_POWER);break;
        case 1:
            load.set_mbase_code(MACHINE_BASE_POWER);break;
        case 2:
            load.set_mbase_code(CUSTOM_RATIO_OF_ACTUAL_MACHINE_POWER);break;
        default:
            load.set_mbase_code(DEFAULT_RATIO_OF_ACTUAL_MACHINE_POWER);
    }

    if(data.size()>0)
    {
        mbase = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_mbase_in_MVA(mbase);

    if(data.size()>0)
    {
        rated_voltage = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_rated_voltage_in_kV(rated_voltage);

    if(data.size()>0)
    {
        Ra = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_Ra_in_pu(Ra);

    if(data.size()>0)
    {
        Xa = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_Xa_in_pu(Xa);

    if(data.size()>0)
    {
        Xm = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_Xm_in_pu(Xm);

    if(data.size()>0)
    {
        R1 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_R1_in_pu(R1);

    if(data.size()>0)
    {
        X1 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_X1_in_pu(X1);

    if(data.size()>0)
    {
        R2 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_R2_in_pu(R2);

    if(data.size()>0)
    {
        X2 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_X2_in_pu(X2);

    if(data.size()>0)
    {
        R_zero_seq = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X_zero_seq = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    load.set_motor_zero_sequence_impedance_in_pu(complex<double>(R_zero_seq, X_zero_seq));
}


void STEPS_IMEXPORTER::load_zero_seq_non_transformer_branch_data()
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    if(splitted_sseq_data_in_ram.size()<4)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[3];
    vector<string> data;

    unsigned int ndata = DATA.size();

    unsigned int n = 0;
    unsigned int bus_i = 0, bus_j = 0;
    string ID = "1";
    double R_zero = 0.0, X_zero = 0.0;
    double B = 0.0;
    double G_i = 0.0, B_i = 0.0;
    double G_j = 0.0, B_j = 0.0;
    double IPR = 0.0;
    unsigned int SCTYP = 0;

    for(unsigned int i=0; i!=ndata; ++i)
    {
        data = DATA[i];

        if(data.size()>0)
        {
            bus_i = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            bus_j = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ID = get_string_data(data[n], "1");
            data.erase(data.begin());
        }
        DEVICE_ID did = get_line_device_id(bus_i, bus_j, ID);
        LINE* lineptr = psdb.get_line(did);

        if(lineptr == NULL)
        {
            osstream<<"Line ["<<lineptr->get_compound_device_name()<<"]"<<" is not exist."<<endl
                    <<"Please check seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(data.size()>0)
        {
            R_zero = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            X_zero = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        lineptr->set_line_zero_sequence_z_in_pu(complex<double>(R_zero, X_zero));

        if(data.size()>0)
        {
            B = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        lineptr->set_line_zero_sequence_y_in_pu(complex<double>(0.0, B));

        if(data.size()>0)
        {
            G_i = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            B_i = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        lineptr->set_shunt_zero_sequence_y_at_sending_side_in_pu(complex<double>(G_i, B_i));

        if(data.size()>0)
        {
            G_j = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            B_j = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        lineptr->set_shunt_zero_sequence_y_at_receiving_side_in_pu(complex<double>(G_j, B_j));

        if(data.size()>0)
        {
            IPR = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            SCTYP = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
    }
}

void STEPS_IMEXPORTER::load_zero_seq_mutual_impedance_data()
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    if(splitted_sseq_data_in_ram.size()<5)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[4];
    vector<string> data;

    unsigned int ndata = DATA.size();

    unsigned int n = 0;
    unsigned int bus_i=0, bus_j=0, bus_p=0, bus_q=0;
    string ICKT1="1", ICKT2="1";
    double Rm, Xm;
    double starting_location_of_line_ij=0.0, ending_location_of_line_ij=1.0;
    double starting_location_of_line_pq=0.0, ending_location_of_line_pq=1.0;

    for(unsigned int i=0; i!=ndata; ++i)
    {
        data = DATA[i];

        if(data.size()>0)
        {
            bus_i = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            bus_j = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ICKT1 = get_string_data(data[n], "1");
            data.erase(data.begin());
        }
        DEVICE_ID did1 = get_line_device_id(bus_i, bus_j, ICKT1);
        LINE* lineptr_ij = psdb.get_line(did1);

        if(lineptr_ij == NULL)
        {
            osstream<<"Line ["<<lineptr_ij->get_compound_device_name()<<"]"<<" is not exist."<<endl
                    <<"Please check mutual impedance data in seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(data.size()>0)
        {
            bus_p = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            bus_q = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ICKT2 = get_string_data(data[n], "1");
            data.erase(data.begin());
        }
        DEVICE_ID did2 = get_line_device_id(bus_p, bus_q, ICKT2);
        LINE* lineptr_pq = psdb.get_line(did2);

        if(lineptr_pq == NULL)
        {
            osstream<<"Line ["<<lineptr_pq->get_compound_device_name()<<"]"<<" is not exist."<<endl
                    <<"Please check mutual impedance data in seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(data.size()>0)
        {
            Rm = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            Xm = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(abs(complex<double>(Rm,Xm)-0.0)<FLOAT_EPSILON)
        {
            osstream<<"Zero sequence mutual impedance can not be zero. Please check mutual impedance in seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(data.size()>0)
        {
            starting_location_of_line_ij = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ending_location_of_line_ij = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(starting_location_of_line_ij > ending_location_of_line_ij)
        {
            osstream<<"Starting location of mutual coupling must be less than ending."<<endl
                    <<" Please check mutual impedance in seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(data.size()>0)
        {
            starting_location_of_line_pq = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ending_location_of_line_pq = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(starting_location_of_line_pq > ending_location_of_line_pq)
        {
            osstream<<"Starting location of mutual coupling must be less than ending."<<endl
                    <<" Please check mutual impedance data in seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        MUTUAL_DATA mutual_data(toolkit);
        mutual_data.set_first_line_pointer(lineptr_ij);
        mutual_data.set_second_line_pointer(lineptr_pq);

        if((lineptr_ij->get_sending_side_bus()==bus_i and lineptr_pq->get_sending_side_bus()==bus_p) or
           (lineptr_ij->get_sending_side_bus()==bus_j and lineptr_pq->get_sending_side_bus()==bus_q))
        {
            mutual_data.set_mutual_impedance(complex<double>(Rm,Xm));
        }
        else
        {
            mutual_data.set_mutual_impedance(-complex<double>(Rm,Xm));
        }

        if(lineptr_ij->get_sending_side_bus()==bus_i)
        {
            mutual_data.set_starting_location_of_first_line(starting_location_of_line_ij);
            mutual_data.set_ending_location_of_first_line(ending_location_of_line_ij);
        }
        else
        {
            mutual_data.set_starting_location_of_first_line(1.0-ending_location_of_line_ij);
            mutual_data.set_ending_location_of_first_line(1.0-starting_location_of_line_ij);
        }

        if(lineptr_pq->get_sending_side_bus()==bus_p)
        {
            mutual_data.set_starting_location_of_second_line(starting_location_of_line_pq);
            mutual_data.set_ending_location_of_second_line(ending_location_of_line_pq);
        }
        else
        {
            mutual_data.set_starting_location_of_second_line(1.0-ending_location_of_line_pq);
            mutual_data.set_ending_location_of_second_line(1.0-starting_location_of_line_pq);
        }
        psdb.append_mutual_data(mutual_data);
        lineptr_ij->set_is_mutual_logic(true);
        lineptr_pq->set_is_mutual_logic(true);
    }
}

void STEPS_IMEXPORTER::load_zero_seq_transformer_data()
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    if(splitted_sseq_data_in_ram.size()<6)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[5];
    vector<string> data;

    unsigned int ndata = DATA.size();

    unsigned int n = 0;
    unsigned int bus_i = 0, bus_j = 0, bus_k = 0;
    string ID = "1";

    for(unsigned int i=0; i!=ndata; ++i)
    {
        data = DATA[i];

        if(data.size()>0)
        {
            bus_i = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            bus_j = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            bus_k = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ID = get_string_data(data[n], "1");
            data.erase(data.begin());
        }
        DEVICE_ID did = get_transformer_device_id(bus_i, bus_j, bus_k, ID);
        TRANSFORMER* transptr = psdb.get_transformer(did);

        if(transptr == NULL)
        {
            osstream<<"Transformer ["<<transptr->get_compound_device_name()<<"]"<<" is not exist."<<endl
                    <<"Please check seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(transptr->is_two_winding_transformer())
            load_two_winding_transformer_zero_seq_data(*transptr, data);
        if(transptr->is_three_winding_transformer())
            load_three_winding_transformer_zero_seq_data(*transptr, data);
    }
}

void STEPS_IMEXPORTER::load_two_winding_transformer_zero_seq_data(TRANSFORMER& trans, vector<string> data)
{
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    double sbase = psdb.get_system_base_power_in_MVA();
    double s_winding_base_primary2secondary = trans.get_winding_nominal_capacity_in_MVA(PRIMARY_SIDE, SECONDARY_SIDE);
    double Ubase_primary = trans.get_winding_nominal_voltage_in_kV(PRIMARY_SIDE);
    double Ubase_secondary = trans.get_winding_nominal_voltage_in_kV(SECONDARY_SIDE);

    unsigned int units_of_non_grounding_impedance, units_of_grounding_impedance, connection_code;
    double Rg1, Xg1, R12, X12, Rg2, Xg2, R02, X02, Rnutrl, Xnutrl;
    unsigned int n = 0;

    if(data.size()>0)
    {
        units_of_non_grounding_impedance = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        units_of_grounding_impedance = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        connection_code = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    unsigned int primary_cc, secondary_cc;
    primary_cc = connection_code/10;
    secondary_cc = connection_code - primary_cc*10;
    switch(primary_cc)
    {
        case 1: trans.set_winding_connection_type(PRIMARY_SIDE, WYE_CONNECTION);break;
        case 2: trans.set_winding_connection_type(PRIMARY_SIDE, DELTA_CONNECTION);break;
        case 3: trans.set_winding_connection_type(PRIMARY_SIDE, WYE_N_CONNECTION);break;
        default:break;
    }
    switch(secondary_cc)
    {
        case 1: trans.set_winding_connection_type(SECONDARY_SIDE, WYE_CONNECTION);break;
        case 2: trans.set_winding_connection_type(SECONDARY_SIDE, DELTA_CONNECTION);break;
        case 3: trans.set_winding_connection_type(SECONDARY_SIDE, WYE_N_CONNECTION);break;
        default:break;
    }

    if(data.size()>0)
    {
        Rg1 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xg1 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    if(data.size()>0)
    {
        R12 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X12 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    if(data.size()>0)
    {
        Rg2 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xg2 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    //
    if(data.size()>0)
    {
        R02 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X02 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    if(data.size()>0)
    {
        Rnutrl = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xnutrl = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    switch(units_of_grounding_impedance)
    {
        case 1:
            Rg1 = Rg1 / sbase * s_winding_base_primary2secondary;
            Xg1 = Xg1 / sbase * s_winding_base_primary2secondary;

            Rg2 = Rg2 / sbase * s_winding_base_primary2secondary;
            Xg2 = Xg2 / sbase * s_winding_base_primary2secondary;

            Rnutrl = Rnutrl / sbase * s_winding_base_primary2secondary;
            Xnutrl = Xnutrl / sbase * s_winding_base_primary2secondary;
            break;
        case 2:
            break;
        case 3:
            Rg1 = Rg1 / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);
            Xg1 = Xg1 / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);

            Rg2 = Rg2 / (Ubase_secondary*Ubase_secondary/s_winding_base_primary2secondary);
            Xg2 = Xg2 / (Ubase_secondary*Ubase_secondary/s_winding_base_primary2secondary);

            // POM P5-104 and POM P5-93
            Rnutrl = Rnutrl / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);
            Xnutrl = Xnutrl / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);
            break;
    }
    trans.set_winding_zero_sequence_impedance_based_on_winding_nominals_in_pu(PRIMARY_SIDE, complex<double>(Rg1, Xg1));
    trans.set_winding_zero_sequence_impedance_based_on_winding_nominals_in_pu(SECONDARY_SIDE, complex<double>(Rg2, Xg2));
    trans.set_common_zero_sequence_nutural_grounding_impedance_based_on_winding_nominals_in_pu(complex<double>(Rnutrl, Xnutrl));

    switch(units_of_non_grounding_impedance)
    {
        case 1:
            R12 = R12 / sbase * s_winding_base_primary2secondary;
            X12 = X12 / sbase * s_winding_base_primary2secondary;
            break;
        case 2:
            break;
    }
    trans.set_zero_sequence_impedance_between_windings_based_on_winding_nominals_in_pu(PRIMARY_SIDE, SECONDARY_SIDE, complex<double>(R12, X12));
}
void STEPS_IMEXPORTER::load_three_winding_transformer_zero_seq_data(TRANSFORMER & trans, vector<string> data)
{
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    double sbase = psdb.get_system_base_power_in_MVA();
    double s_winding_base_primary2secondary = trans.get_winding_nominal_capacity_in_MVA(PRIMARY_SIDE, SECONDARY_SIDE);
    double s_winding_base_secondary2tertiary = trans.get_winding_nominal_capacity_in_MVA(SECONDARY_SIDE, TERTIARY_SIDE);
    double s_winding_base_tertiary2primary = trans.get_winding_nominal_capacity_in_MVA(TERTIARY_SIDE, PRIMARY_SIDE);

    double Ubase_primary = trans.get_winding_nominal_voltage_in_kV(PRIMARY_SIDE);
    double Ubase_secondary = trans.get_winding_nominal_voltage_in_kV(SECONDARY_SIDE);
    double Ubase_tertiary = trans.get_winding_nominal_voltage_in_kV(TERTIARY_SIDE);

    unsigned int units_of_non_grounding_impedance, units_of_grounding_impedance, connection_code;
    double Rg1, Xg1, R01, X01, Rg2, Xg2, R02, X02, Rg3, Xg3, R03, X03, Rnutrl, Xnutrl;
    unsigned int n = 0;

    if(data.size()>0)
    {
        units_of_non_grounding_impedance = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        units_of_grounding_impedance = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        connection_code = get_integer_data(data[n], "0");
        data.erase(data.begin());
    }

    unsigned int primary_cc, secondary_cc, tertiary_cc;
    primary_cc = connection_code/100;
    secondary_cc = (connection_code - primary_cc*100)/10;
    tertiary_cc = connection_code - primary_cc*100 - secondary_cc*10;

    switch(primary_cc)
    {
        case 1: trans.set_winding_connection_type(PRIMARY_SIDE, WYE_CONNECTION);break;
        case 2: trans.set_winding_connection_type(PRIMARY_SIDE, DELTA_CONNECTION);break;
        case 3: trans.set_winding_connection_type(PRIMARY_SIDE, WYE_N_CONNECTION);break;
    }
    switch(secondary_cc)
    {
        case 1: trans.set_winding_connection_type(SECONDARY_SIDE, WYE_CONNECTION);break;
        case 2: trans.set_winding_connection_type(SECONDARY_SIDE, DELTA_CONNECTION);break;
        case 3: trans.set_winding_connection_type(SECONDARY_SIDE, WYE_N_CONNECTION);break;
    }
    switch(tertiary_cc)
    {
        case 1: trans.set_winding_connection_type(TERTIARY_SIDE, WYE_CONNECTION);break;
        case 2: trans.set_winding_connection_type(TERTIARY_SIDE, DELTA_CONNECTION);break;
        case 3: trans.set_winding_connection_type(TERTIARY_SIDE, WYE_N_CONNECTION);break;
    }


    if(data.size()>0)
    {
        Rg1 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xg1 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        R01 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X01 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Rg2 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xg2 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        R02 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X02 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Rg3 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xg3 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        R03 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        X03 = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Rnutrl = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }
    if(data.size()>0)
    {
        Xnutrl = get_double_data(data[n], "0.0");
        data.erase(data.begin());
    }

    switch(units_of_grounding_impedance)
    {
        case 1:     // POM P5-93 and POM
            Rg1 = Rg1 / sbase * s_winding_base_primary2secondary;
            Xg1 = Xg1 / sbase * s_winding_base_primary2secondary;

            Rg2 = Rg2 / sbase * s_winding_base_secondary2tertiary;
            Xg2 = Xg2 / sbase * s_winding_base_secondary2tertiary;

            Rg3 = Rg3 / sbase * s_winding_base_tertiary2primary;
            Xg3 = Xg3 / sbase * s_winding_base_tertiary2primary;

            Rnutrl = Rnutrl / sbase * s_winding_base_primary2secondary;
            Xnutrl = Xnutrl / sbase * s_winding_base_primary2secondary;
            break;
        case 2:
            break;
        case 3:
            Rg1 = Rg1 / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);
            Xg1 = Xg1 / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);

            Rg2 = Rg2 / (Ubase_secondary*Ubase_secondary/s_winding_base_secondary2tertiary);
            Xg2 = Xg2 / (Ubase_secondary*Ubase_secondary/s_winding_base_secondary2tertiary);

            Rg3 = Rg3 / (Ubase_tertiary*Ubase_tertiary/s_winding_base_tertiary2primary);
            Xg3 = Xg3 / (Ubase_tertiary*Ubase_tertiary/s_winding_base_tertiary2primary);

            // POM P5-104 and POM P5-93
            Rnutrl = Rnutrl / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);
            Xnutrl = Xnutrl / (Ubase_primary*Ubase_primary/s_winding_base_primary2secondary);
            break;
    }
    trans.set_winding_zero_sequence_impedance_based_on_winding_nominals_in_pu(PRIMARY_SIDE, complex<double>(Rg1, Xg1));
    trans.set_winding_zero_sequence_impedance_based_on_winding_nominals_in_pu(SECONDARY_SIDE, complex<double>(Rg2, Xg2));
    trans.set_winding_zero_sequence_impedance_based_on_winding_nominals_in_pu(TERTIARY_SIDE, complex<double>(Rg3, Xg3));
    trans.set_common_zero_sequence_nutural_grounding_impedance_based_on_winding_nominals_in_pu(complex<double>(Rnutrl, Xnutrl));

    switch(units_of_non_grounding_impedance)
    {
        case 1:

            // POM P5-95
            R01 = R01 / sbase * s_winding_base_primary2secondary;
            X01 = X01 / sbase * s_winding_base_primary2secondary;

            R02 = R02 / sbase * s_winding_base_secondary2tertiary;
            X02 = X02 / sbase * s_winding_base_secondary2tertiary;

            R03 = R03 / sbase * s_winding_base_tertiary2primary;
            X03 = X03 / sbase * s_winding_base_tertiary2primary;
            break;
        case 2:
            break;
    }
    trans.set_zero_sequence_impedance_between_windings_based_on_winding_nominals_in_pu(PRIMARY_SIDE, SECONDARY_SIDE, complex<double>(R01, X01));
    trans.set_zero_sequence_impedance_between_windings_based_on_winding_nominals_in_pu(SECONDARY_SIDE, TERTIARY_SIDE, complex<double>(R02, X02));
    trans.set_zero_sequence_impedance_between_windings_based_on_winding_nominals_in_pu(TERTIARY_SIDE, PRIMARY_SIDE, complex<double>(R03, X03));
}

void STEPS_IMEXPORTER::load_zero_seq_swithed_shunt_data()
{
    ;
}
void STEPS_IMEXPORTER::load_zero_seq_fixed_shunt_data()
{
    ostringstream osstream;
    STEPS& toolkit = get_toolkit();
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    if(splitted_sseq_data_in_ram.size()<8)
        return;
    vector<vector<string> >DATA = splitted_sseq_data_in_ram[7];
    vector<string> data;

    unsigned int ndata = DATA.size();

    unsigned int n = 0;
    unsigned int bus;
    string ID = "1";
    double P0 = 0.0, Q0=0.0;

    for(unsigned int i=0; i!=ndata; ++i)
    {
        data = DATA[i];
        if(data.size()>0)
        {
            bus = get_integer_data(data[n], "0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            ID = get_string_data(data[n], "1");
            data.erase(data.begin());
        }
        DEVICE_ID did = get_fixed_shunt_device_id(bus, ID);
        FIXED_SHUNT* shuntptr = psdb.get_fixed_shunt(did);

        if(shuntptr == NULL)
        {
            osstream<<"Fixed shunt ["<<"ID:"<<ID<<"]"<<" is not exist on bus "<<"bus"<<"."<<endl
                    <<"Please check seq file.";
            toolkit.show_information_with_leading_time_stamp(osstream);
            continue;
        }

        if(data.size()>0)
        {
            P0 = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        if(data.size()>0)
        {
            Q0 = get_double_data(data[n], "0.0");
            data.erase(data.begin());
        }
        shuntptr->set_nominal_zero_sequence_impedance_shunt_in_MVA(complex<double>(P0,-Q0));
    }
}
void STEPS_IMEXPORTER::load_induction_machine_seq_data()
{
    ;
}
