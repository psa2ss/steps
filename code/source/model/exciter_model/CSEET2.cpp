#include "header/model/exciter_model/CSEET2.h"
#include "header/basic/utility.h"
#include <cstdio>
#include <iostream>

using namespace std;

static vector<string> MODEL_VARIABLE_TABLE{ "EXCITATION VOLTAGE",      //0
                                            "VOLTAGE REFERENCE",      //1
                                            "COMPENSATED VOLTAGE",      //2
                                            "STABILIZING SIGNAL",      //3
                                            "STATE@SENSOR",     //4
                                            "STATE@TUNER1",     //5
                                            "STATE@TUNER2",     //5
                                            "STATE@REGULATOR",     //5
                                            "STATE@FEEDBACKER",     //6
                                            };

CSEET2::CSEET2()
{
    clear();
}

void CSEET2::clear()
{
    set_stabilizer_slot(AT_VOLTAGE_ERROR);
    set_excitation_source(SEPARATE_EXCITATION);
    set_tuner_type(SERIAL_TUNER);

    sensor.set_limiter_type(NO_LIMITER);
    sensor.set_K(1.0);

    set_serial_tuner_KV(true);

    serial_tuner1_lead_lag.set_limiter_type(NON_WINDUP_LIMITER);
    serial_tuner1_lead_lag.set_upper_limit(999.0);
    serial_tuner1_lead_lag.set_lower_limit(-999.0);

    serial_tuner1_pi.set_limiter_type(NON_WINDUP_LIMITER);
    serial_tuner1_pi.set_upper_limit(999.0);
    serial_tuner1_pi.set_lower_limit(-999.0);

    serial_tuner2.set_limiter_type(NO_LIMITER);

    parallel_integral.set_limiter_type(NON_WINDUP_LIMITER);
    parallel_integral.set_upper_limit(999.0);
    parallel_integral.set_lower_limit(-999.0);

    parallel_differential.set_limiter_type(NON_WINDUP_LIMITER);
    parallel_differential.set_upper_limit(999.0);
    parallel_differential.set_lower_limit(-999.0);

    regulator.set_limiter_type(NON_WINDUP_LIMITER);

    feedbacker.set_limiter_type(NO_LIMITER);

    set_VRmax_in_pu(0.0);
    set_VRmin_in_pu(0.0);

    set_KC(0.0);
}
void CSEET2::copy_from_const_model(const CSEET2& model)
{
    clear();

    this->set_excitation_source(model.get_excitation_source());
    this->set_stabilizer_slot(model.get_stabilizer_slot());
    this->set_tuner_type(model.get_tuner_type());

    this->set_TR_in_s(model.get_TR_in_s());
    if(get_tuner_type()==SERIAL_TUNER)
    {
        this->set_serial_tuner_KV(model.get_serial_tuner_KV());
        this->set_serial_tuner_K(model.get_serial_tuner_K());
        this->set_serial_tuner_T1_in_s(model.get_serial_tuner_T1_in_s());
        this->set_serial_tuner_T2_in_s(model.get_serial_tuner_T2_in_s());
        this->set_serial_tuner_VA1max_in_pu(model.get_serial_tuner_VA1max_in_pu());
        this->set_serial_tuner_VA1min_in_pu(model.get_serial_tuner_VA1min_in_pu());
        this->set_serial_tuner_T3_in_s(model.get_serial_tuner_T3_in_s());
        this->set_serial_tuner_T4_in_s(model.get_serial_tuner_T4_in_s());
    }
    else
    {
        this->set_parallel_tuner_KP(model.get_parallel_tuner_KP());
        this->set_parallel_tuner_KI(model.get_parallel_tuner_KI());
        this->set_parallel_tuner_VImax_in_pu(model.get_parallel_tuner_VImax_in_pu());
        this->set_parallel_tuner_VImin_in_pu(model.get_parallel_tuner_VImin_in_pu());
        this->set_parallel_tuner_KD(model.get_parallel_tuner_KD());
        this->set_parallel_tuner_TD_in_s(model.get_parallel_tuner_TD_in_s());
        this->set_parallel_tuner_VDmax_in_pu(model.get_parallel_tuner_VDmax_in_pu());
        this->set_parallel_tuner_VDmin_in_pu(model.get_parallel_tuner_VDmin_in_pu());
    }
    this->set_KA(model.get_KA());
    this->set_TA_in_s(model.get_TA_in_s());
    this->set_VAmax_in_pu(model.get_VAmax_in_pu());
    this->set_VAmin_in_pu(model.get_VAmin_in_pu());
    this->set_KF(model.get_KF());
    this->set_TF_in_s(model.get_TF_in_s());
    this->set_VRmax_in_pu(model.get_VRmax_in_pu());
    this->set_VRmin_in_pu(model.get_VRmin_in_pu());
    this->set_KC(model.get_KC());
}

CSEET2::~CSEET2()
{
    ;
}

CSEET2::CSEET2(const CSEET2& model) : EXCITER_MODEL()
{
    copy_from_const_model(model);
}

CSEET2& CSEET2::operator=(const CSEET2& model)
{
    if(this==(&model)) return (*this);

    copy_from_const_model(model);

    return (*this);
}

string CSEET2::get_model_name() const
{
    return "CSEET2";
}

void CSEET2::set_excitation_source(AVR_EXCITATION_SOURCE source)
{
    excitation_source = source;
}

void CSEET2::set_stabilizer_slot(AVR_FEEDBACK_SLOT slot)
{
    stabilizer_slot = slot;
}

void CSEET2::set_tuner_type(AVR_TUNER_TYPE type)
{
    tuner_type = type;
}

void CSEET2::set_TR_in_s(double T)
{
    sensor.set_T_in_s(T);
}

void CSEET2::set_serial_tuner_KV(bool K)
{
    KV = K;
}

void CSEET2::set_serial_tuner_K(double K)
{
    serial_tuner1_lead_lag.set_K(K);
}

void CSEET2::set_serial_tuner_T1_in_s(double T)
{
    serial_tuner1_lead_lag.set_T1_in_s(T);
}

void CSEET2::set_serial_tuner_T2_in_s(double T)
{
    serial_tuner1_lead_lag.set_T2_in_s(T);
}

void CSEET2::set_serial_tuner_VA1max_in_pu(double vmax)
{
    serial_tuner1_lead_lag.set_upper_limit(vmax);
}

void CSEET2::set_serial_tuner_VA1min_in_pu(double vmin)
{
    serial_tuner1_lead_lag.set_lower_limit(vmin);
}

void CSEET2::set_serial_tuner_T3_in_s(double T)
{
    serial_tuner2.set_T1_in_s(T);
}

void CSEET2::set_serial_tuner_T4_in_s(double T)
{
    serial_tuner2.set_T2_in_s(T);
}

void CSEET2::set_parallel_tuner_KP(double K)
{
    KP = K;
}

void CSEET2::set_parallel_tuner_KI(double K)
{
    parallel_integral.set_T_in_s(1.0/K);
}

void CSEET2::set_parallel_tuner_VImax_in_pu(double vmax)
{
    parallel_integral.set_upper_limit(vmax);
}

void CSEET2::set_parallel_tuner_VImin_in_pu(double vmin)
{
    parallel_integral.set_lower_limit(vmin);
}

void CSEET2::set_parallel_tuner_KD(double K)
{
    parallel_differential.set_K(K);
}

void CSEET2::set_parallel_tuner_TD_in_s(double T)
{
    parallel_differential.set_T_in_s(T);
}

void CSEET2::set_parallel_tuner_VDmax_in_pu(double vmax)
{
    parallel_differential.set_upper_limit(vmax);
}

void CSEET2::set_parallel_tuner_VDmin_in_pu(double vmin)
{
    parallel_differential.set_lower_limit(vmin);
}

void CSEET2::set_KA(double K)
{
    regulator.set_K(K);
}

void CSEET2::set_TA_in_s(double T)
{
    regulator.set_T_in_s(T);
}

void CSEET2::set_VAmax_in_pu(double vmax)
{
    regulator.set_upper_limit(vmax);
}

void CSEET2::set_VAmin_in_pu(double vmin)
{
    regulator.set_lower_limit(vmin);
}

void CSEET2::set_KF(double K)
{
    feedbacker.set_K(K);
}

void CSEET2::set_TF_in_s(double T)
{
    feedbacker.set_T_in_s(T);
}

void CSEET2::set_VRmax_in_pu(double vmax)
{
    VRmax = vmax;
}

void CSEET2::set_VRmin_in_pu(double vmin)
{
    VRmin = vmin;
}

void CSEET2::set_KC(double K)
{
    this->KC = K;
}

AVR_EXCITATION_SOURCE CSEET2::get_excitation_source() const
{
    return excitation_source;
}

AVR_FEEDBACK_SLOT CSEET2::get_stabilizer_slot() const
{
    return stabilizer_slot;
}

AVR_TUNER_TYPE CSEET2::get_tuner_type() const
{
    return tuner_type;
}

double CSEET2::get_TR_in_s() const
{
    return sensor.get_T_in_s();
}

bool CSEET2::get_serial_tuner_KV() const
{
    return KV;
}

double CSEET2::get_serial_tuner_K() const
{
    return serial_tuner1_lead_lag.get_K();
}

double CSEET2::get_serial_tuner_T1_in_s() const
{
    return serial_tuner1_lead_lag.get_T1_in_s();
}

double CSEET2::get_serial_tuner_T2_in_s() const
{
    return serial_tuner1_lead_lag.get_T2_in_s();
}

double CSEET2::get_serial_tuner_VA1max_in_pu() const
{
    return serial_tuner1_lead_lag.get_upper_limit();
}

double CSEET2::get_serial_tuner_VA1min_in_pu() const
{
    return serial_tuner1_lead_lag.get_lower_limit();
}

double CSEET2::get_serial_tuner_T3_in_s() const
{
    return serial_tuner2.get_T1_in_s();
}

double CSEET2::get_serial_tuner_T4_in_s() const
{
    return serial_tuner2.get_T2_in_s();
}

double CSEET2::get_parallel_tuner_KP() const
{
    return KP;
}

double CSEET2::get_parallel_tuner_KI() const
{
    return 1.0/parallel_integral.get_T_in_s();
}

double CSEET2::get_parallel_tuner_VImax_in_pu() const
{
    return parallel_integral.get_upper_limit();
}

double CSEET2::get_parallel_tuner_VImin_in_pu() const
{
    return parallel_integral.get_lower_limit();
}

double CSEET2::get_parallel_tuner_KD() const
{
    return parallel_differential.get_K();
}

double CSEET2::get_parallel_tuner_TD_in_s() const
{
    return parallel_differential.get_T_in_s();
}

double CSEET2::get_parallel_tuner_VDmax_in_pu() const
{
    return parallel_differential.get_upper_limit();
}

double CSEET2::get_parallel_tuner_VDmin_in_pu() const
{
    return parallel_differential.get_lower_limit();
}

double CSEET2::get_KA() const
{
    return regulator.get_K();
}

double CSEET2::get_TA_in_s() const
{
    return regulator.get_T_in_s();
}

double CSEET2::get_VAmax_in_pu() const
{
    return regulator.get_upper_limit();
}

double CSEET2::get_VAmin_in_pu() const
{
    return regulator.get_lower_limit();
}

double CSEET2::get_KF() const
{
    return feedbacker.get_K();
}

double CSEET2::get_TF_in_s() const
{
    return feedbacker.get_T_in_s();
}

double CSEET2::get_VRmax_in_pu() const
{
    return VRmax;
}

double CSEET2::get_VRmin_in_pu() const
{
    return VRmin;
}

double CSEET2::get_KC() const
{
    return this->KC;
}


bool CSEET2::setup_model_with_steps_string(string data)
{
    return false;
}

bool CSEET2::setup_model_with_psse_string(string data)
{
    bool is_successful = false;
    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<21)
        return is_successful;

    string model_name = get_string_data(dyrdata[1],"");
    if(model_name!="CSEET2")
        return is_successful;

    size_t excitation_source, stabilizer_slot, tuner_type;
    double tr;
    // serial
    double serial_k;
    size_t serial_kv;
    double t1, t2, va1max, va1min, t3, t4;
    // parallel
    double parallel_kp, parallel_ki, vimax, vimin, parallel_kd, parallel_td, vdmax, vdmin;
    // common
    double ka, ta, vamax, vamin, kf, tf, vrmax, vrmin, kc;

    size_t i=3;
    excitation_source = get_integer_data(dyrdata[i],"0"); i++; if(excitation_source!=0) excitation_source = 1;
    stabilizer_slot = get_integer_data(dyrdata[i],"0"); i++; if(stabilizer_slot!=0) stabilizer_slot = 1;
    tuner_type = get_integer_data(dyrdata[i],"0"); i++; if(tuner_type!=0) tuner_type = 1;
    tr = get_double_data(dyrdata[i],"1.0"); i++;

    if(excitation_source==0)
        set_excitation_source(SELF_EXCITATION);
    else
        set_excitation_source(SEPARATE_EXCITATION);

    if(stabilizer_slot==0)
        set_stabilizer_slot(AT_VOLTAGE_ERROR);
    else
        set_stabilizer_slot(AT_REGULATOR);

    if(tuner_type==0)
        set_tuner_type(SERIAL_TUNER);
    else
        set_tuner_type(PARALLEL_TUNER);

    set_TR_in_s(tr);


    if(tuner_type==0) // serial
    {
        serial_k = get_double_data(dyrdata[i],"1.0"); i++;
        serial_kv = get_integer_data(dyrdata[i],"1"); i++;
        t1 = get_double_data(dyrdata[i],"1.0"); i++;
        t2 = get_double_data(dyrdata[i],"1.0"); i++;
        va1max = get_double_data(dyrdata[i],"999.0"); i++;
        va1min = get_double_data(dyrdata[i],"-999.0"); i++;
        t3 = get_double_data(dyrdata[i],"1.0"); i++;
        t4 = get_double_data(dyrdata[i],"1.0"); i++;

        set_serial_tuner_K(serial_k);
        set_serial_tuner_KV(serial_kv);
        set_serial_tuner_T1_in_s(t1);
        set_serial_tuner_T2_in_s(t2);
        set_serial_tuner_VA1max_in_pu(va1max);
        set_serial_tuner_VA1min_in_pu(va1min);
        set_serial_tuner_T3_in_s(t3);
        set_serial_tuner_T4_in_s(t4);
    }
    else
    {
        parallel_kp = get_double_data(dyrdata[i],"1.0"); i++;
        parallel_ki = get_double_data(dyrdata[i],"1.0"); i++;
        vimax = get_double_data(dyrdata[i],"999.0"); i++;
        vimin = get_double_data(dyrdata[i],"-999.0"); i++;
        parallel_kd = get_double_data(dyrdata[i],"1.0"); i++;
        parallel_td = get_double_data(dyrdata[i],"1.0"); i++;
        vdmax = get_double_data(dyrdata[i],"999.0"); i++;
        vdmin = get_double_data(dyrdata[i],"-999.0"); i++;

        set_parallel_tuner_KP(parallel_kp);
        set_parallel_tuner_KI(parallel_ki);
        set_parallel_tuner_VImax_in_pu(vimax);
        set_parallel_tuner_VImin_in_pu(vimin);
        set_parallel_tuner_KD(parallel_kd);
        set_parallel_tuner_TD_in_s(parallel_td);
        set_parallel_tuner_VDmax_in_pu(vdmax);
        set_parallel_tuner_VDmin_in_pu(vdmin);
    }

    ka = get_double_data(dyrdata[i],"1.0"); i++;
    ta = get_double_data(dyrdata[i],"0.0"); i++;
    vamax = get_double_data(dyrdata[i],"0.0"); i++;
    vamin = get_double_data(dyrdata[i],"0.0"); i++;
    kf = get_double_data(dyrdata[i],"0.0"); i++;
    tf = get_double_data(dyrdata[i],"0.0"); i++;
    vrmax = get_double_data(dyrdata[i],"0.0"); i++;
    vrmin = get_double_data(dyrdata[i],"0.0"); i++;
    kc = get_double_data(dyrdata[i],"0.0"); i++;

    set_KA(ka);
    set_TA_in_s(ta);
    set_VAmax_in_pu(vamax);
    set_VAmin_in_pu(vamin);
    set_KF(kf);
    set_TF_in_s(tf);
    set_VRmax_in_pu(vrmax);
    set_VRmin_in_pu(vrmin);
    set_KC(kc);

    is_successful = true;

    return is_successful;
}

bool CSEET2::setup_model_with_bpa_string(string data)
{
    return false;
}


void CSEET2::initialize()
{
    if(is_model_initialized())
        return;

    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    if(generator==NULL)
        return;

    SYNC_GENERATOR_MODEL* gen_model = generator->get_sync_generator_model();
    if(gen_model==NULL)
        return;

    if(not gen_model->is_model_initialized())
        gen_model->initialize();

    if(get_tuner_type()==SERIAL_TUNER)
    {
        if(get_serial_tuner_KV()==false)
        {
            double K = get_serial_tuner_K();
            double T1 = get_serial_tuner_T1_in_s();
            double T2 = get_serial_tuner_T2_in_s();

            serial_tuner1_pi.set_Kp(K*T1/T2);
            serial_tuner1_pi.set_Ki(K/T2);
        }
    }

    double Efd =  get_initial_excitation_voltage_in_pu_from_sync_generator_model();
    double Ifd = gen_model->get_field_current_in_pu_based_on_mbase();
    double Kc = get_KC();

    double Vr = Efd + Kc*Ifd;

    regulator.set_output(Vr);
    regulator.initialize();

    feedbacker.set_input(Vr);
    feedbacker.initialize();

    double output = regulator.get_input();

    if(get_tuner_type()==SERIAL_TUNER)
    {
        serial_tuner2.set_output(output);
        serial_tuner2.initialize();

        output = serial_tuner2.get_input();
        if(get_serial_tuner_KV()==true)
        {
            serial_tuner1_lead_lag.set_output(output);
            serial_tuner1_lead_lag.initialize();
            output = serial_tuner1_lead_lag.get_input();
        }
        else
        {
            serial_tuner1_pi.set_output(output);
            serial_tuner1_pi.initialize();
            output = serial_tuner1_pi.get_input();
        }
    }
    else // parallel tuner
    {
        parallel_integral.set_output(output);
        parallel_integral.initialize();

        parallel_differential.set_input(0.0);
        parallel_differential.initialize();

        output = 0.0;
    }

    double Ecomp = get_compensated_voltage_in_pu();
    sensor.set_output(Ecomp);
    sensor.initialize();

    double Vref = Ecomp+output;
    set_voltage_reference_in_pu(Vref);

    set_flag_model_initialized_as_true();
}

void CSEET2::run(DYNAMIC_MODE mode)
{
    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    if(generator==NULL)
        return;

    SYNC_GENERATOR_MODEL* gen_model = generator->get_sync_generator_model();
    if(gen_model==NULL)
        return;

    double Ecomp = get_compensated_voltage_in_pu();
    double Vref = get_voltage_reference_in_pu();
    double Vs = get_stabilizing_signal_in_pu();

    double input;
    sensor.set_input(Ecomp);
    sensor.run(mode);

    input = Vref-sensor.get_output();
    if(get_stabilizer_slot()==AT_VOLTAGE_ERROR)
        input += Vs;

    if(get_tuner_type()==SERIAL_TUNER)
    {
        if(get_serial_tuner_KV()==true)
        {
            serial_tuner1_lead_lag.set_input(input);
            serial_tuner1_lead_lag.run(mode);
            input = serial_tuner1_lead_lag.get_output();
        }
        else
        {
            serial_tuner1_pi.set_input(input);
            serial_tuner1_pi.run(mode);
            input = serial_tuner1_pi.get_output();
        }
        serial_tuner2.set_input(input);
        serial_tuner2.run(mode);
        input = serial_tuner2.get_output();
    }
    else // parallel tuner
    {
        parallel_integral.set_input(input);
        parallel_integral.run(mode);

        parallel_differential.set_input(input);
        parallel_differential.run(mode);

        input = get_parallel_tuner_KP()*input+parallel_integral.get_output()+parallel_differential.get_output();
    }


    input -= feedbacker.get_output();
    if(get_stabilizer_slot()==AT_REGULATOR)
        input += Vs;

    regulator.set_input(input);
    regulator.run(mode);
    input = regulator.get_output();

    feedbacker.set_input(input);
    feedbacker.run(mode);

    //cout<<"Ecomp="<<Ecomp<<", Vref="<<Vref<<", Vs="<<Vs<<", Efd="<<exciter.get_output()<<endl;

    if(mode == UPDATE_MODE)
        set_flag_model_updated_as_true();
}

double CSEET2::get_excitation_voltage_in_pu() const
{
    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    if(generator==NULL)
        return 0.0;

    SYNC_GENERATOR_MODEL* gen_model = generator->get_sync_generator_model();
    if(gen_model==NULL)
        return 0.0;

    double Ifd = gen_model->get_field_current_in_pu_based_on_mbase();

    double Efd = regulator.get_output();
    double Vrmax = get_VRmax_in_pu();
    double Vrmin = get_VRmin_in_pu();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    size_t bus = generator->get_generator_bus();
    double Vt = psdb->get_bus_voltage_in_pu(bus);

    if(get_excitation_source()==SELF_EXCITATION)
    {
        Vrmax *= Vt;
        Vrmin *= Vt;
    }

    if(Efd>Vrmax)
        Efd = Vrmax;

    if(Efd<Vrmin)
        Efd = Vrmin;

    double Kc = get_KC();
    Efd -= Kc*Ifd;

    return Efd;
}
void CSEET2::check()
{
    ;
}

void CSEET2::report()
{
    ostringstream sstream;
    sstream<<get_standard_model_string();
    show_information_with_leading_time_stamp(sstream);
}

void CSEET2::save()
{
    ;
}

string CSEET2::get_standard_model_string() const
{
    ostringstream sstream;
    GENERATOR* gen = (GENERATOR*) get_device_pointer();
    size_t bus = gen->get_generator_bus();
    string identifier= gen->get_identifier();

    size_t source_index = 0;
    switch(get_excitation_source())
    {
        case SELF_EXCITATION:
            source_index = 0;
            break;
        default:
            source_index = 1;
            break;
    }
    size_t stabilizer_index = 0;
    switch(get_stabilizer_slot())
    {
        case AT_VOLTAGE_ERROR:
            stabilizer_index = 0;
            break;
        default:
            stabilizer_index = 1;
            break;
    }

    size_t tuner_type = 0;
    switch(get_tuner_type())
    {
        case SERIAL_TUNER:
            tuner_type = 0;
            break;
        default:
            tuner_type = 1;
            break;
    }
    double TR = get_TR_in_s();

    sstream<<setw(8)<<bus<<", "
      <<"'"<<get_model_name()<<"', "
      <<"'"<<identifier<<"', "
      <<setw(4)<<source_index<<", "
      <<setw(4)<<stabilizer_index<<", "
      <<setw(4)<<tuner_type<<", "
      <<setw(8)<<setprecision(6)<<TR<<", ";

    if(get_tuner_type()==SERIAL_TUNER)
    {
        bool KV = get_serial_tuner_KV();
        size_t selector = 0;
        if(KV) selector = 1;
        double K = get_serial_tuner_K();
        double T1 = get_serial_tuner_T1_in_s();
        double T2 = get_serial_tuner_T2_in_s();
        double VA1max = get_serial_tuner_VA1max_in_pu();
        double VA1min = get_serial_tuner_VA1min_in_pu();
        double T3 = get_serial_tuner_T3_in_s();
        double T4 = get_serial_tuner_T4_in_s();

        sstream<<setw(4)<<selector<<", "
          <<setw(8)<<setprecision(6)<<K<<", "
          <<setw(8)<<setprecision(6)<<T1<<", "
          <<setw(8)<<setprecision(6)<<T2<<", "
          <<setw(8)<<setprecision(6)<<VA1max<<", "
          <<setw(8)<<setprecision(6)<<VA1min<<", "
          <<setw(8)<<setprecision(6)<<T3<<", "
          <<setw(8)<<setprecision(6)<<T4<<", ";
    }
    else
    {
        double KP = get_parallel_tuner_KP();
        double KI = get_parallel_tuner_KI();
        double Vimax = get_parallel_tuner_VImax_in_pu();
        double Vimin = get_parallel_tuner_VImin_in_pu();
        double KD = get_parallel_tuner_KD();
        double TD = get_parallel_tuner_TD_in_s();
        double Vdmax = get_parallel_tuner_VDmax_in_pu();
        double Vdmin = get_parallel_tuner_VDmin_in_pu();

        sstream<<setw(8)<<setprecision(6)<<KP<<", "
          <<setw(8)<<setprecision(6)<<KI<<", "
          <<setw(8)<<setprecision(6)<<Vimax<<", "
          <<setw(8)<<setprecision(6)<<Vimin<<", "
          <<setw(8)<<setprecision(6)<<KD<<", "
          <<setw(8)<<setprecision(6)<<TD<<", "
          <<setw(8)<<setprecision(6)<<Vdmax<<", "
          <<setw(8)<<setprecision(6)<<Vdmin<<", ";
    }

    double KA = get_KA();
    double TA = get_TA_in_s();
    double VAmax = get_VAmax_in_pu();
    double VAmin = get_VAmin_in_pu();
    double KF = get_KF();
    double TF = get_TF_in_s();
    double VRmax = get_VRmax_in_pu();
    double VRmin = get_VRmin_in_pu();
    double KC = get_KC();

    sstream<<setw(8)<<setprecision(6)<<KA<<", "
      <<setw(8)<<setprecision(6)<<TA<<", "
      <<setw(8)<<setprecision(6)<<VAmax<<", "
      <<setw(8)<<setprecision(6)<<VAmin<<", "
      <<setw(8)<<setprecision(6)<<KF<<", "
      <<setw(8)<<setprecision(6)<<TF<<", "
      <<setw(8)<<setprecision(6)<<VRmax<<", "
      <<setw(8)<<setprecision(6)<<VRmin<<", "
      <<setw(8)<<setprecision(6)<<KC<<"  /";

    return sstream.str();
}


size_t CSEET2::get_variable_index_from_variable_name(string var_name)
{
    return MODEL::get_variable_index_from_variable_name(var_name, MODEL_VARIABLE_TABLE);
}

string CSEET2::get_variable_name_from_variable_index(size_t var_index)
{
    return MODEL::get_variable_name_from_variable_index(var_index, MODEL_VARIABLE_TABLE);
}

double CSEET2::get_variable_with_index(size_t var_index)
{
    string var_name = get_variable_name_from_variable_index(var_index);
    return get_variable_with_name(var_name);
}

double CSEET2::get_variable_with_name(string var_name)
{
    if(var_name == "EXCITATION VOLTAGE")
        return get_excitation_voltage_in_pu();

    if(var_name == "VOLTAGE REFERENCE")
        return get_voltage_reference_in_pu();

    if(var_name == "COMPENSATED VOLTAGE")
        return get_compensated_voltage_in_pu();

    if(var_name == "STABILIZING SIGNAL")
        return get_stabilizing_signal_in_pu();

    if(var_name == "STATE@SENSOR")
        return sensor.get_state();

    if(var_name == "STATE@TUNER1")
    {
        if(get_tuner_type()==SERIAL_TUNER)
        {
            if(get_serial_tuner_KV()==true)
                return serial_tuner1_lead_lag.get_state();
            else
                return serial_tuner1_pi.get_state();
        }
        else
            return parallel_integral.get_state();
    }

    if(var_name == "STATE@TUNER2")
    {
        if(get_tuner_type()==SERIAL_TUNER)
            return serial_tuner2.get_state();
        else
            return parallel_differential.get_state();
    }

    if(var_name == "STATE@REGULATOR")
        return regulator.get_state();

    if(var_name == "STATE@FEEDBACKER")
        return feedbacker.get_state();

    return 0.0;
}



string CSEET2::get_dynamic_data_in_psse_format() const
{
    return "";
}

string CSEET2::get_dynamic_data_in_bpa_format() const
{
    return get_dynamic_data_in_psse_format();
}

string CSEET2::get_dynamic_data_in_steps_format() const
{
    return get_dynamic_data_in_psse_format();
}