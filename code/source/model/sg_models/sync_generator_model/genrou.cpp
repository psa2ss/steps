#include "header/model/sg_models/sync_generator_model/genrou.h"
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
                                            "FIELD CURRENT IN PU",      //12
                                            "GENERATOR INTERNAL VOLTAGE IN PU",      //13
                                            "GENERATOR TERMINAL CURRENT IN PU",      //14
                                            "GENERATOR TERMINAL CURRENT IN KA",      //15
                                            "STATE@ROTOR ANGLE BLOCK",     //16
                                            "STATE@ROTOR SPEED BLOCK",    //17
                                            "STATE@D-AXIS TRANSIENT BLOCK",    //18
                                            "STATE@Q-AXIS TRANSIENT BLOCK",    //19
                                            "STATE@D-AXIS SUBTRANSIENT BLOCK",    //20
                                            "STATE@Q-AXIS SUBTRANSIENT BLOCK",    //21
                                            };
GENROU::GENROU() : SYNC_GENERATOR_MODEL()
{
    clear();
}

GENROU::~GENROU()
{
    clear();
}
void GENROU::clear()
{
    ;
}
void GENROU::copy_from_const_model(const GENROU& model)
{
    clear();

    //this->set_power_system_database(model.get_power_system_database());
    //this->set_device_id(model.get_device_id());

    this->set_Rs(model.get_Rs());
    this->set_Xd(model.get_Xd());
    this->set_Xq(model.get_Xq());
    this->set_Xdp(model.get_Xdp());
    this->set_Xqp(model.get_Xqp());
    this->set_Xpp(model.get_Xpp());
    this->set_Xl(model.get_Xl());
    this->set_Td0p_in_s(model.get_Td0p_in_s());
    this->set_Td0pp_in_s(model.get_Td0pp_in_s());
    this->set_Tq0p_in_s(model.get_Tq0p_in_s());
    this->set_Tq0pp_in_s(model.get_Tq0pp_in_s());
    this->set_Tj_in_s(model.get_Tj_in_s());
    this->set_D(model.get_D());
}
GENROU::GENROU(const GENROU& model):SYNC_GENERATOR_MODEL()
{
    copy_from_const_model(model);
}

GENROU& GENROU::operator=(const GENROU& model)
{
    if(this==&model)
        return *this;

    copy_from_const_model(model);

    return (*this);
}

string GENROU::get_model_name() const
{
    return "GENROU";
}

double GENROU::get_double_data_with_index(size_t index) const
{
    return 0.0;
}

double GENROU::get_double_data_with_name(string par_name) const
{
    par_name = string2upper(par_name);
    if(par_name=="")
        return 0.0;

    return 0.0;
}

void GENROU::set_double_data_with_index(size_t index, double value)
{
    if(index==0)
        return;
}

void GENROU::set_double_data_with_name(string par_name, double value)
{
    par_name = string2upper(par_name);
    if(par_name=="")
        return;
}

void GENROU::update_source_impedance()
{
    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    if(generator!=NULL)
    {
        complex<double> Z(get_Rs(),get_Xpp());
        complex<double> Zsource = generator->get_source_impedance_in_pu();
        if(Zsource.imag()!=Z.imag())
        {
            ostringstream sstream;
            sstream<<"Warning. The subtransient reactance ("<<get_Xpp()<<") is not equal to generator source reactance ("<<Zsource.imag()<<") for '"<<get_model_name()<<"' of "<<get_device_name()<<"."<<endl
              <<"Source reactance will be updated with subtransient reactance.";
            show_information_with_leading_time_stamp(sstream);
            Zsource = complex<double>(Zsource.real(), Z.imag());
            generator->set_source_impedance_in_pu(Zsource);
        }
        set_Rs(Zsource.real());
    }
}

bool GENROU::setup_model_with_steps_string(string data)
{
    return false;
}

bool GENROU::setup_model_with_psse_string(string data)
{
    bool is_successful = false;
    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<17)
        return is_successful;

    string model_name = get_string_data(dyrdata[1],"");
    if(model_name!=get_model_name())
        return is_successful;


    double xd, xq, xdp, xqp, xpp, xl, td0p, tq0p, td0pp, tq0pp;
    double H, D;
    double s1, s1p2;

    size_t i=3;
    td0p = get_double_data(dyrdata[i],"0.0"); i++;
    td0pp = get_double_data(dyrdata[i],"0.0"); i++;
    tq0p = get_double_data(dyrdata[i],"0.0"); i++;
    tq0pp = get_double_data(dyrdata[i],"0.0"); i++;
    H = get_double_data(dyrdata[i],"0.0"); i++;
    D = get_double_data(dyrdata[i],"0.0"); i++;
    xd = get_double_data(dyrdata[i],"0.0"); i++;
    xq = get_double_data(dyrdata[i],"0.0"); i++;
    xdp = get_double_data(dyrdata[i],"0.0"); i++;
    xqp = get_double_data(dyrdata[i],"0.0"); i++;
    xpp = get_double_data(dyrdata[i],"0.0"); i++;
    xl = get_double_data(dyrdata[i],"0.0"); i++;
    s1 = get_double_data(dyrdata[i],"0.0"); i++;
    s1p2 = get_double_data(dyrdata[i],"0.0");

    set_Xd(xd);
    set_Xq(xq);
    set_Xdp(xdp);
    set_Xqp(xqp);
    set_Xdpp(xpp);
    set_Xqpp(xpp);
    set_Xl(xl);
    set_Td0p_in_s(td0p);
    set_Td0pp_in_s(td0pp);
    set_Tq0p_in_s(tq0p);
    set_Tq0pp_in_s(tq0pp);
    set_H_in_s(H);
    set_D(D);
    set_saturation_at_1(s1);
    set_saturation_at_1p2(s1p2);

    is_successful = true;

    return is_successful;
}

bool GENROU::setup_model_with_bpa_string(string data)
{
    return false;
}

void GENROU::initialize()
{
    update_source_impedance();

    initialize_rotor_angle();

    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();
    double speed = 0.0;
    rotor_speed_block->set_output(speed);
    rotor_speed_block->initialize();

    double rotor_angle = get_rotor_angle_in_rad();

    INTEGRAL_BLOCK* transient_block_d_axis = get_d_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_d_axis = get_d_axis_subtransient_block();
    INTEGRAL_BLOCK* transient_block_q_axis = get_q_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_q_axis = get_q_axis_subtransient_block();


    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    double mbase = get_mbase_in_MVA();

    complex<double> Zsource(get_Rs(), get_Xpp());

    double P = generator->get_p_generation_in_MW();
    double Q = generator->get_q_generation_in_MVar();
    complex<double> S(P/mbase,Q/mbase);

    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Ixy = conj(S/Vxy);
    complex<double> Exy = Vxy+Ixy*Zsource;

    complex<double> Idq = xy2dq_with_angle_in_rad(Ixy, rotor_angle);
    complex<double> Edq = xy2dq_with_angle_in_rad(Exy, rotor_angle);
    complex<double> Flux_dq = Edq*complex<double>(0.0, -1.0);
    double Flux = abs(Flux_dq);
    double delta_XadIfd = get_saturation_with_flux(Flux)*Flux;

    // d axis
    double xd = get_Xd();
    double xdp = get_Xdp();
    double xpp = get_Xpp();
    double xl = get_Xl();
    // sp*(Xd"-Xl)/(Xd'-Xl)+spp*(Xd'-Xd")/(Xd'-Xl)=Fd
    // sp-spp-Id*(Xd'-Xl)=0.0
    // or
    // sp+spp*(Xd'-Xd")/(Xd"-Xl)=Fd*(Xd'-Xl)/(Xd"-Xl)
    // -sp+spp=-Id*(Xd'-Xl)
    // or
    //spp*(Xd'-Xd")/(Xd"-Xl)+spp=Fd*(Xd'-Xl)/(Xd"-Xl)-Id*(Xd'-Xl)
    // or
    //spp*(Xd'-Xl)/(Xd"-Xl)=Fd*(Xd'-Xl)/(Xd"-Xl)-Id*(Xd'-Xl)
    // or
    //spp/(Xd"-Xl)=Fd/(Xd"-Xl)-Id
    // or
    //spp=Fd-Id*(Xd"-Xl)

    //spp = Flux_dq.real()-Idq.real()*(xpp-xl);
    //sp  = spp+Idq.real()*(xdp-xl);

    // A*sp + B*spp = fluxd
    // sp - spp = id*(xdp-xl)
    // sp = spp + id*(xdp-xl)
    // (A+B)*spp + A*id*(xdp-xl) = fluxd
    double A = (xpp-xl)/(xdp-xl), B = (xdp-xpp)/(xdp-xl);
    double sdp, sdpp; // state of transient, and subtransient
    sdpp = (Flux_dq.real()-A*Idq.real()*(xdp-xl))/(A+B);
    sdp = sdpp + Idq.real()*(xdp-xl);

    transient_block_d_axis->set_output(sdp);
    transient_block_d_axis->initialize();

    subtransient_block_d_axis->set_output(sdpp);
    subtransient_block_d_axis->initialize();

    // excitation voltage
    double efd0 = sdp+Idq.real()*(xd-xdp)+Flux_dq.real()*delta_XadIfd/Flux;
    set_initial_excitation_voltage_in_pu(efd0);

    // q axis
    double xqp = get_Xqp();
    /*double xqp = get_Xqp();
    // sp*(Xq"-Xl)/(Xq'-Xl)+spp*(Xq'-Xq")/(Xq'-Xl)=-Fq
    // sp-spp+Iq*(Xq'-Xl)=0.0
    // or
    // sp+spp*(Xq'-Xq")/(Xq"-Xl)=-Fq*(Xq'-Xl)/(Xq"-Xl)
    // -sp+spp=Iq*(Xq'-Xl)
    // or
    // spp*(Xq'-Xq")/(Xq"-Xl)+spp=-Fq*(Xq'-Xl)/(Xq"-Xl)+Iq*(Xq'-Xl)
    // or
    // spp*(Xq'-Xl)/(Xq"-Xl)=-Fq*(Xq'-Xl)/(Xq"-Xl)+Iq*(Xq'-Xl)
    // or
    // spp=-Fq+Iq*(Xq"-Xl)
    spp = -Flux_dq.imag()+Idq.imag()*(xpp-xl);
    sp  = spp-Idq.imag()*(xqp-xl);
    transient_block_q_axis->set_output(sp);
    subtransient_block_q_axis->set_output(spp);

    sp = Idq.imag()*(xq-xqp)+Flux_dq.imag()*delta_XadIfd*(xq-xl)/(xd-xl)/Flux;
    spp = sp+Idq.imag()*(xqp-xl);*/

    A = (xpp-xl)/(xqp-xl); B = (xqp-xpp)/(xqp-xl);
    // sp*A+spp*B = -fluxq
    //sp - spp + iq*(xqp-xl) = 0
    // sp = spp - iq*(xqp-xl)
    // (A+B)*spp -A*iq*(xqp-xl) = -fluxq
    double sqp, sqpp; // state of transient, and subtransient
    sqpp = (-Flux_dq.imag()+A*Idq.imag()*(xqp-xl))/(A+B);
    sqp = sqpp - Idq.imag()*(xqp-xl);

    transient_block_q_axis->set_output(sqp);
    transient_block_q_axis->initialize();

    subtransient_block_q_axis->set_output(sqpp);
    subtransient_block_q_axis->initialize();

    //cout<<"init Efd = "<<efd0<<", Flux_dq = "<<Flux_dq<<", Edq="<<Edq<<", Ed0'="<<sdp<<", Ed0''="<<sdpp<<", Eq0'="<<sqp<<", Eq0''="<<sqpp<<endl;
    //cout<<"init Flux="<<abs(Flux)<<", E''="<<abs(Edq)<<", "<<abs(Exy)<<endl;

    // mechanical power
    double I = abs(Ixy);
    double pmech0 = S.real()+I*I*get_Rs();
    set_initial_mechanical_power_in_pu_based_on_mbase(pmech0);

    set_flag_model_initialized_as_true();
}

void GENROU::initialize_rotor_angle()
{
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    double mbase = get_mbase_in_MVA();

    complex<double> Zsource(get_Rs(), get_Xpp());

    double P = generator->get_p_generation_in_MW();
    double Q = generator->get_q_generation_in_MVar();
    complex<double> S(P/mbase,Q/mbase);

    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Ixy = conj(S/Vxy);
    complex<double> Exy = Vxy+Ixy*Zsource;
    double Ex = Exy.real(), Ey = Exy.imag();
    double Ix = Ixy.real(), Iy = Ixy.imag();

    double rs = get_Rs();
    double xd = get_Xd();
    double xq = get_Xq();
    double xqp = get_Xqp();
    double xqpp = get_Xqpp();
    double xl = get_Xl();

    double Flux = abs(Exy);
    double delta_XadIfd = get_saturation_with_flux(Flux)*Flux;

    double A = (xq-xqp)*(xqpp-xl)/(xqp-xl)+(xq-xl)*(xqp-xqpp)/(xqp-xl);
    double B = (xq-xl)/(xd-xl)*delta_XadIfd/Flux;

    double C = -Ex*(1.0+B)+A*Iy, D = -A*Ix-(1.0+B)*Ey;

    complex<double> Zq(rs, xq);
    complex<double> EQ = Vxy+Ixy*Zq;

    double rotor_angle_EQ = arg(EQ/Vxy) + arg(Vxy);
    double rotor_angle = 0.0;
    if(C == 0.0)
        rotor_angle = PI*0.5;
    else
        rotor_angle = atan(D/C);

    while(true)
    {
        if(fabs(rotor_angle-rotor_angle_EQ)>PI*0.5)
        {
            if(rotor_angle>rotor_angle_EQ)
                rotor_angle -= PI;
            else
                rotor_angle += PI;
        }
        else
            break;
    }

    rotor_angle_block->set_output(rotor_angle);
    rotor_angle_block->initialize();
}

void GENROU::run(DYNAMIC_MODE mode)
{
    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();
    INTEGRAL_BLOCK* transient_block_d_axis = get_d_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_d_axis = get_d_axis_subtransient_block();
    INTEGRAL_BLOCK* transient_block_q_axis = get_q_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_q_axis = get_q_axis_subtransient_block();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double fbase = psdb->get_system_base_frequency_in_Hz();

    double xd = get_Xd();
    double xdp = get_Xdp();
    double xpp = get_Xpp();
    double xq = get_Xq();
    double xqp = get_Xqp();
    double xl = get_Xl();

    double fluxd = transient_block_d_axis->get_output()*(xpp-xl)/(xdp-xl) + subtransient_block_d_axis->get_output()*(xdp-xpp)/(xdp-xl);
    double fluxq = transient_block_q_axis->get_output()*(xpp-xl)/(xqp-xl) + subtransient_block_q_axis->get_output()*(xqp-xpp)/(xqp-xl);
    fluxq = -fluxq;
    complex<double> Flux_dq(fluxd, fluxq);
    double Flux = abs(Flux_dq);
    double delta_XadIfd = get_saturation_with_flux(Flux)*Flux;

    complex<double> Idq = get_terminal_complex_current_in_pu_in_dq_axis_based_on_mbase();

    double input;
    // d-axis
    input = transient_block_d_axis->get_output()-subtransient_block_d_axis->get_output()-Idq.real()*(xdp-xl);
    input = get_excitation_voltage_in_pu()-transient_block_d_axis->get_output()-(xd-xdp)*(Idq.real()+input*(xdp-xpp)/((xdp-xl)*(xdp-xl)))-
            Flux_dq.real()*delta_XadIfd/Flux;
    transient_block_d_axis->set_input(input);
    transient_block_d_axis->run(mode);

    input = transient_block_d_axis->get_output()-subtransient_block_d_axis->get_output()-Idq.real()*(xdp-xl);
    subtransient_block_d_axis->set_input(input);
    subtransient_block_d_axis->run(mode);

    // q-axis
    input = transient_block_q_axis->get_output()-subtransient_block_q_axis->get_output()+Idq.imag()*(xqp-xl);
    input = -transient_block_q_axis->get_output()+(xq-xqp)*(Idq.imag()-input*(xqp-xpp)/((xqp-xl)*(xqp-xl)))+
            Flux_dq.imag()*(xq-xl)/(xd-xl)*delta_XadIfd/Flux;
    transient_block_q_axis->set_input(input);
    transient_block_q_axis->run(mode);

    input = transient_block_q_axis->get_output()-subtransient_block_q_axis->get_output()+Idq.imag()*(xqp-xl);
    subtransient_block_q_axis->set_input(input);
    subtransient_block_q_axis->run(mode);

    double damping = get_D();

    double pmech = get_mechanical_power_in_pu_based_on_mbase();
    double speed = get_rotor_speed_deviation_in_pu();
    double omega = get_rotor_speed_in_pu();
    double tmech = pmech/omega;

    double telec = get_air_gap_torque_in_pu_based_on_mbase();

    double delta_torque = tmech-telec-damping*speed/omega;

    rotor_speed_block->set_input(delta_torque);
    rotor_speed_block->run(mode);

    speed = get_rotor_speed_deviation_in_pu();

    speed = 2.0*PI*fbase*speed;
    rotor_angle_block->set_input(speed);
    rotor_angle_block->run(mode);

    if(mode==UPDATE_MODE)
        set_flag_model_updated_as_true();
}


complex<double> GENROU::get_source_Norton_equivalent_complex_current_in_pu_in_xy_axis_based_on_sbase()
{
    complex<double> Exy = get_internal_voltage_in_pu_in_xy_axis();
    complex<double> Z(get_Rs(), get_Xpp());
    double mbase = get_mbase_in_MVA();
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double sbase = psdb->get_system_base_power_in_MVA();

    return Exy/Z*mbase/sbase;
}

complex<double> GENROU::get_terminal_complex_current_in_pu_in_dq_axis_based_on_mbase()
{
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();
    double angle = get_rotor_angle_in_rad();

    return xy2dq_with_angle_in_rad(Ixy, angle);
}


complex<double> GENROU::get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase()
{
    complex<double> Exy = get_internal_voltage_in_pu_in_xy_axis();
    complex<double> Vxy = get_terminal_complex_voltage_in_pu();

    complex<double> Zsource(get_Rs(), get_Xpp());

    complex<double> Ixy = (Exy-Vxy)/Zsource;

    //cout<<"Exy = "<<Exy<<", Vxy = "<<Vxy<<", Z = "<<Zsource<<", Ixy = "<<Ixy<<endl;

    return Ixy;
}

complex<double> GENROU::get_terminal_complex_current_in_pu_in_xy_axis_based_on_sbase()
{
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();
    double mbase = get_mbase_in_MVA();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double sbase = psdb->get_system_base_power_in_MVA();

    return Ixy*mbase/sbase;
}

double GENROU::get_terminal_current_in_pu_based_on_mbase()
{
    return abs(get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase());
}

double GENROU::get_terminal_current_in_pu_based_on_sbase()
{
    double I = get_terminal_current_in_pu_based_on_mbase();
    double mbase = get_mbase_in_MVA();

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    double sbase = psdb->get_system_base_power_in_MVA();

    return I*mbase/sbase;
}


void GENROU::check()
{
    ;
}

void GENROU::report()
{
    ostringstream sstream;
    sstream<<get_standard_model_string();
    show_information_with_leading_time_stamp(sstream);
}

void GENROU::save()
{
    ;
}

string GENROU::get_standard_model_string() const
{
    ostringstream sstream;
    DEVICE_ID did = get_device_id();
    size_t bus = did.get_device_terminal().get_buses()[0];
    string identifier = did.get_device_identifier();

    sstream<<setw(8)<<bus<<", "
      <<"'"<<get_model_name()<<"', "
      <<"'"<<identifier<<"', "
      <<setw(8)<<setprecision(6)<<get_Td0p_in_s()<<", "
      <<setw(8)<<setprecision(6)<<get_Td0pp_in_s()<<", "
      <<setw(8)<<setprecision(6)<<get_Tq0p_in_s()<<", "
      <<setw(8)<<setprecision(6)<<get_Tq0pp_in_s()<<", "
      <<setw(8)<<setprecision(6)<<get_H_in_s()<<", "
      <<setw(8)<<setprecision(6)<<get_D()<<", "
      <<setw(8)<<setprecision(6)<<get_Xd()<<", "
      <<setw(8)<<setprecision(6)<<get_Xq()<<", "
      <<setw(8)<<setprecision(6)<<get_Xdp()<<", "
      <<setw(8)<<setprecision(6)<<get_Xqp()<<", "
      <<setw(8)<<setprecision(6)<<get_Xpp()<<", "
      <<setw(8)<<setprecision(6)<<get_Xl()<<", "
      <<setw(8)<<setprecision(6)<<get_saturation_at_1()<<", "
      <<setw(8)<<setprecision(6)<<get_saturation_at_1p2()<<"  /";

    return sstream.str();
}

size_t GENROU::get_variable_index_from_variable_name(string var_name)
{
    return MODEL::get_variable_index_from_variable_name(var_name, MODEL_VARIABLE_TABLE);
}

string GENROU::get_variable_name_from_variable_index(size_t var_index)
{
    return MODEL::get_variable_name_from_variable_index(var_index, MODEL_VARIABLE_TABLE);
}

double GENROU::get_variable_with_index(size_t var_index)
{
    string var_name = get_variable_name_from_variable_index(var_index);
    return get_variable_with_name(var_name);
}

double GENROU::get_variable_with_name(string var_name)
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
    if(var_name == "FIELD CURRENT IN PU")
        return get_field_current_in_pu_based_on_mbase();
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

double GENROU::get_air_gap_power_in_pu_based_on_mbase()
{
    complex<double> Exy = get_internal_voltage_in_pu_in_xy_axis();
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();

    complex<double> S = Exy*conj(Ixy);

    return S.real();
}

double GENROU::get_air_gap_power_in_MW()
{
    return get_air_gap_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
}

double GENROU::get_air_gap_torque_in_pu_based_on_mbase()
{
    // since omega is ignored when converting from flux to voltage
    // the air gap torch is equal to air gap power
    // double omega = get_rotor_speed_in_pu();
    return get_air_gap_power_in_pu_based_on_mbase();
}

double GENROU::get_accelerating_power_in_pu_based_on_mbase()
{
    return get_mechanical_power_in_pu_based_on_mbase()-get_air_gap_power_in_pu_based_on_mbase();
}

double GENROU::get_accelerating_power_in_MW()
{
    return get_accelerating_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
}

complex<double> GENROU::get_terminal_complex_power_in_pu_based_on_mbase()
{
    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Ixy = get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();

    complex<double> S = Vxy*conj(Ixy);
    return S;
}

complex<double> GENROU::get_terminal_complex_power_in_MVA()
{
    return get_terminal_complex_power_in_pu_based_on_mbase()*get_mbase_in_MVA();
}

double GENROU::get_terminal_active_power_in_pu_based_on_mbase()
{
    return get_terminal_complex_power_in_pu_based_on_mbase().real();
}

double GENROU::get_terminal_active_power_in_MW()
{
    return get_terminal_complex_power_in_MVA().real();
}

double GENROU::get_terminal_reactive_power_in_pu_based_on_mbase()
{
    return get_terminal_complex_power_in_pu_based_on_mbase().imag();
}

double GENROU::get_terminal_reactive_power_in_MVar()
{
    return get_terminal_complex_power_in_MVA().imag();
}

double GENROU::get_field_current_in_pu_based_on_mbase()
{
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();
    INTEGRAL_BLOCK* transient_block_d_axis = get_d_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_d_axis = get_d_axis_subtransient_block();
    INTEGRAL_BLOCK* transient_block_q_axis = get_q_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_q_axis = get_q_axis_subtransient_block();

    double angle = rotor_angle_block->get_output();

    double xd = get_Xd();
    double xdp = get_Xdp();
    double xpp = get_Xpp();
    double xqp = get_Xqp();
    double xl = get_Xl();

    double fluxd = transient_block_d_axis->get_output()*(xpp-xl)/(xdp-xl) + subtransient_block_d_axis->get_output()*(xdp-xpp)/(xdp-xl);
    double fluxq = transient_block_q_axis->get_output()*(xpp-xl)/(xqp-xl) + subtransient_block_q_axis->get_output()*(xqp-xpp)/(xqp-xl);
    fluxq = -fluxq;
    complex<double> Flux_dq(fluxd, fluxq);
    double Flux = abs(Flux_dq);

    complex<double> Edq = get_internal_voltage_in_pu_in_dq_axis();
    complex<double> Vxy = get_terminal_complex_voltage_in_pu();
    complex<double> Vdq = xy2dq_with_angle_in_rad(Vxy, angle);
    complex<double> Zsource(get_Rs(), get_Xpp());
    complex<double> Idq = (Edq-Vdq)/Zsource;

    double delta_XadIfd = get_saturation_with_flux(Flux)*Flux;

    double xadifd;
    // d-axis
    // input to subtransient block
    xadifd = transient_block_d_axis->get_output()-subtransient_block_d_axis->get_output()-Idq.real()*(xdp-xl);

    xadifd = transient_block_d_axis->get_output()+(xd-xdp)*(Idq.real()+xadifd*(xdp-xpp)/((xdp-xl)*(xdp-xl)))+
            Flux_dq.real()*delta_XadIfd/Flux;

    return xadifd/(xd-xl);
}

double GENROU::get_rotor_angle_in_rad()
{
    INTEGRAL_BLOCK* rotor_angle_block = get_rotor_angle_block();

    return rotor_angle_block->get_output();
}

double GENROU::get_rotor_angle_in_deg()
{
    return rad2deg(get_rotor_angle_in_rad());
}

double GENROU::get_rotor_speed_deviation_in_pu()
{
    INTEGRAL_BLOCK* rotor_speed_block = get_rotor_speed_block();

    return rotor_speed_block->get_output();
}

double GENROU::get_rotor_speed_in_pu()
{
    return 1.0+get_rotor_speed_deviation_in_pu();
}

complex<double> GENROU::get_internal_voltage_in_pu_in_dq_axis()
{
    INTEGRAL_BLOCK* transient_block_d_axis = get_d_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_d_axis = get_d_axis_subtransient_block();
    INTEGRAL_BLOCK* transient_block_q_axis = get_q_axis_transient_block();
    INTEGRAL_BLOCK* subtransient_block_q_axis = get_q_axis_subtransient_block();

    double flux_d = transient_block_d_axis->get_output()*(get_Xpp()-get_Xl())+subtransient_block_d_axis->get_output()*(get_Xdp()-get_Xpp());
    flux_d /= (get_Xdp()-get_Xl());

    double flux_q = transient_block_q_axis->get_output()*(get_Xpp()-get_Xl())+subtransient_block_q_axis->get_output()*(get_Xqp()-get_Xpp());
    flux_q /= (get_Xqp()-get_Xl());
    flux_q = -flux_q;

    complex<double> Flux_dq(flux_d, flux_q);
    complex<double> Edq = Flux_dq/complex<double>(0.0, -1.0);  // omega is ignored when converting from flux to voltage
    //cout<<"Flux_dq = "<<Flux_dq<<", Edq = "<<Edq<<", Eq0'="<<transient_block_q_axis->get_output()<<", Eq0''="<<subtransient_block_q_axis->get_output()<<endl;

    return Edq;
}


complex<double> GENROU::get_internal_voltage_in_pu_in_xy_axis()
{
    complex<double> Edq = get_internal_voltage_in_pu_in_dq_axis();

    double angle = get_rotor_angle_in_rad();
    complex<double> Exy = dq2xy_with_angle_in_rad(Edq, angle);

    //cout<<"Edq = "<<Edq<<", angle = "<<angle<<"Exy = "<<Exy<<endl;

    return Exy;
}

string GENROU::get_dynamic_data_in_psse_format() const
{
    return "";
}

string GENROU::get_dynamic_data_in_bpa_format() const
{
    return get_dynamic_data_in_psse_format();
}

string GENROU::get_dynamic_data_in_steps_format() const
{
    return get_dynamic_data_in_psse_format();
}