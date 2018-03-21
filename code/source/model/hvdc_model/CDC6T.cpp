#include "header/model/hvdc_model/CDC6T.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include <cstdio>
#include <iostream>

using namespace std;

static vector<string> MODEL_VARIABLE_TABLE{ "EXCITATION VOLTAGE",      //0
                                            "VOLTAGE REFERENCE",      //1
                                            "COMPENSATED VOLTAGE",      //2
                                            "STABILIZING SIGNAL",      //3
                                            "STATE@SENSOR",     //4
                                            "STATE@REGULATOR",     //5
                                            "STATE@FEEDBACKER",     //6
                                            "STATE@EXCITER"     //7
                                            };

CDC6T::CDC6T()
{
    clear();
}

CDC6T::~CDC6T()
{
    ;
}

void CDC6T::clear()
{
    set_converter_dynamic_max_alpha_or_gamma_in_deg(RECTIFIER, 90.0);
    set_converter_dynamic_max_alpha_or_gamma_in_deg(INVERTER, 90.0);
    inverter_dc_voltage_sensor.set_limiter_type(NO_LIMITER);
    inverter_dc_voltage_sensor.set_K(1.0);
    dc_current_sensor.set_limiter_type(NO_LIMITER);
    dc_current_sensor.set_K(1.0);


    //time_when_rectifier_ac_voltage_below_delayed_blocking_voltage = INFINITE_THRESHOLD;
    //time_when_rectifier_ac_voltage_above_delayed_unblocking_voltage = INFINITE_THRESHOLD;
    //time_when_inverter_ac_voltage_below_instataneous_blocking_voltage = INFINITE_THRESHOLD;
    //time_when_inverter_ac_voltage_above_instataneous_unblocking_voltage = INFINITE_THRESHOLD;
    //time_when_inverter_ac_unblocking_signal_is_sent = INFINITE_THRESHOLD;

    //time_when_inverter_ac_voltage_below_delayed_bypassing_voltage = INFINITE_THRESHOLD;
    //time_when_inverter_ac_voltage_above_delayed_unbypassing_voltage = INFINITE_THRESHOLD;
}

void CDC6T::copy_from_const_model(const CDC6T& model)
{
    clear();
    this->set_inverter_dc_voltage_sensor_T_in_s(model.get_inverter_dc_voltage_sensor_T_in_s());
    this->set_rectifier_dc_voltage_sensor_T_in_s(model.get_rectifier_dc_voltage_sensor_T_in_s());
    this->set_dc_current_sensor_T_in_s(model.get_dc_current_sensor_T_in_s());
    this->set_converter_dynamic_min_alpha_or_gamma_in_deg(RECTIFIER,model.get_converter_dynamic_min_alpha_or_gamma_in_deg(RECTIFIER));
    this->set_converter_dynamic_min_alpha_or_gamma_in_deg(INVERTER,model.get_converter_dynamic_min_alpha_or_gamma_in_deg(INVERTER));
    this->set_rectifier_ac_instantaneous_blocking_voltage_in_pu(model.get_rectifier_ac_instantaneous_blocking_voltage_in_pu());
    this->set_rectifier_ac_delayed_blocking_voltage_in_pu(model.get_rectifier_ac_delayed_blocking_voltage_in_pu());
    this->set_rectifier_ac_delayed_blocking_time_in_s(model.get_rectifier_ac_delayed_blocking_time_in_s());
    this->set_inverter_ac_instantenous_blocking_voltage_in_pu(model.get_inverter_ac_instantenous_blocking_voltage_in_pu());
    this->set_communication_delay_between_converters_in_s(model.get_communication_delay_between_converters_in_s());
    this->set_rectifier_ac_delayed_unblocking_voltage_in_pu(model.get_rectifier_ac_delayed_unblocking_voltage_in_pu());
    this->set_rectifier_ac_delayed_unblocking_time_in_s(model.get_rectifier_ac_delayed_unblocking_time_in_s());
    this->set_inverter_ac_delayed_unblocking_time_in_s(model.get_inverter_ac_delayed_unblocking_time_in_s());
    this->set_mininum_blocking_time_in_s(model.get_mininum_blocking_time_in_s());
    this->set_inverter_dc_instantaneous_bypassing_voltage_in_kV(model.get_inverter_dc_instantenous_bypassing_voltage_in_kV());
    this->set_inverter_ac_delayed_bypassing_voltage_in_pu(model.get_inverter_ac_delayed_bypassing_voltage_in_pu());
    this->set_inverter_ac_delayed_bypassing_time_in_s(model.get_inverter_ac_delayed_bypassing_time_in_s());
    this->set_inverter_ac_delayed_unbypassing_voltage_in_pu(model.get_inverter_ac_delayed_unbypassing_voltage_in_pu());
    this->set_inverter_ac_delayed_unbypassing_time_in_s(model.get_inverter_ac_delayed_unbypassing_time_in_s());
    this->set_mininum_bypassing_time_in_s(model.get_mininum_bypassing_time_in_s());
    this->set_minimum_dc_voltage_in_kV_following_unblocking_and_unbypassing(model.get_minimum_dc_voltage_in_kV_following_unblocking_and_unbypassing());
    this->set_minimum_dc_current_in_kA_following_unblocking(model.get_minimum_dc_current_in_kA_following_unblocking());
    this->set_dc_voltage_command_recovery_rate_in_pu_per_second(model.get_dc_voltage_command_recovery_rate_in_pu_per_second());
    this->set_dc_current_command_recovery_rate_in_pu_per_second(model.get_dc_current_command_recovery_rate_in_pu_per_second());
    this->set_minimum_dc_current_command_in_kA(model.get_minimum_dc_current_command_in_kA());
    this->set_VDCOL(model.get_VDCOL());
    this->set_minimum_time_in_switched_mode_in_s(model.get_minimum_time_in_switched_mode_in_s());
}

CDC6T::CDC6T(const CDC6T& model) : HVDC_MODEL()
{
    copy_from_const_model(model);
}

CDC6T& CDC6T::operator=(const CDC6T& model)
{
    if(this==(&model)) return *this;

    copy_from_const_model(model);

    return (*this);
}

string CDC6T::get_model_name() const
{
    return "CDC6T";
}


void CDC6T::set_inverter_dc_voltage_sensor_T_in_s(double t)
{
    inverter_dc_voltage_sensor.set_T_in_s(t);
}

void CDC6T::set_rectifier_dc_voltage_sensor_T_in_s(double t)
{
    rectifier_dc_voltage_sensor.set_T_in_s(t);
}

void CDC6T::set_dc_current_sensor_T_in_s(double t)
{
    dc_current_sensor.set_T_in_s(t);
}

void CDC6T::set_rectifier_ac_instantaneous_blocking_voltage_in_pu(double v)
{
    rectifier_ac_instantaneous_blocking_voltage_in_pu = v;
}

void CDC6T::set_rectifier_ac_delayed_blocking_voltage_in_pu(double v)
{
    rectifier_ac_delayed_blocking_voltage_in_pu = v;
}

void CDC6T::set_rectifier_ac_delayed_blocking_time_in_s(double t)
{
    rec_ac_blocking_timer.set_timer_interval_in_s(t);
}

void CDC6T::set_inverter_ac_instantenous_blocking_voltage_in_pu(double v)
{
    inverter_ac_instantaneous_blocking_voltage_in_pu = v;
}

void CDC6T::set_communication_delay_between_converters_in_s(double t)
{
    inv_ac_blocking_signal_transmitting_timer.set_timer_interval_in_s(t);
    inv_ac_unblocking_signal_transmitting_timer.set_timer_interval_in_s(t);
}

void CDC6T::set_rectifier_ac_delayed_unblocking_voltage_in_pu(double v)
{
    rectifier_ac_delayed_unblocking_voltage_in_pu = v;
}

void CDC6T::set_rectifier_ac_delayed_unblocking_time_in_s(double t)
{
    rec_ac_unblocking_timer.set_timer_interval_in_s(t);
}

void CDC6T::set_inverter_ac_delayed_unblocking_time_in_s(double t)
{
    inv_ac_unblocking_timer.set_timer_interval_in_s(t);
}

void CDC6T::set_inverter_dc_instantaneous_bypassing_voltage_in_kV(double v)
{
    inverter_dc_instantaneous_bypassing_voltage_in_kV = v;
}

void CDC6T::set_inverter_ac_delayed_bypassing_voltage_in_pu(double v)
{
    inverter_ac_delayed_bypassing_voltage_in_pu = v;
}

void CDC6T::set_inverter_ac_delayed_bypassing_time_in_s(double t)
{
    inv_ac_bypassing_timer.set_timer_interval_in_s(t);
}

void CDC6T::set_inverter_ac_delayed_unbypassing_voltage_in_pu(double v)
{
    inverter_ac_delayed_unbypassing_voltage_in_pu = v;
}

void CDC6T::set_inverter_ac_delayed_unbypassing_time_in_s(double t)
{
    inv_ac_unbypassing_timer.set_timer_interval_in_s(t);
}

double CDC6T::get_inverter_dc_voltage_sensor_T_in_s() const
{
    return inverter_dc_voltage_sensor.get_T_in_s();
}

double CDC6T::get_rectifier_dc_voltage_sensor_T_in_s() const
{
    return rectifier_dc_voltage_sensor.get_T_in_s();
}

double CDC6T::get_dc_current_sensor_T_in_s() const
{
    return dc_current_sensor.get_T_in_s();
}

double CDC6T::get_rectifier_ac_instantaneous_blocking_voltage_in_pu() const
{
    return rectifier_ac_instantaneous_blocking_voltage_in_pu;
}

double CDC6T::get_rectifier_ac_delayed_blocking_voltage_in_pu() const
{
    return rectifier_ac_delayed_blocking_voltage_in_pu;
}

double CDC6T::get_rectifier_ac_delayed_blocking_time_in_s() const
{
    return rec_ac_blocking_timer.get_timer_interval_in_s();
}

double CDC6T::get_inverter_ac_instantenous_blocking_voltage_in_pu() const
{
    return inverter_ac_instantaneous_blocking_voltage_in_pu;
}

double CDC6T::get_communication_delay_between_converters_in_s() const
{
    return inv_ac_blocking_signal_transmitting_timer.get_timer_interval_in_s();
}

double CDC6T::get_rectifier_ac_delayed_unblocking_voltage_in_pu() const
{
    return rectifier_ac_delayed_unblocking_voltage_in_pu;
}

double CDC6T::get_rectifier_ac_delayed_unblocking_time_in_s() const
{
    return rec_ac_unblocking_timer.get_timer_interval_in_s();
}

double CDC6T::get_inverter_ac_delayed_unblocking_time_in_s() const
{
    return inv_ac_unblocking_timer.get_timer_interval_in_s();
}

double CDC6T::get_inverter_dc_instantenous_bypassing_voltage_in_kV() const
{
    return inverter_dc_instantaneous_bypassing_voltage_in_kV;
}

double CDC6T::get_inverter_ac_delayed_bypassing_voltage_in_pu() const
{
    return inverter_ac_delayed_bypassing_voltage_in_pu;
}

double CDC6T::get_inverter_ac_delayed_bypassing_time_in_s() const
{
    return inv_ac_bypassing_timer.get_timer_interval_in_s();
}

double CDC6T::get_inverter_ac_delayed_unbypassing_voltage_in_pu() const
{
    return inverter_ac_delayed_unbypassing_voltage_in_pu;
}

double CDC6T::get_inverter_ac_delayed_unbypassing_time_in_s() const
{
    return inv_ac_unbypassing_timer.get_timer_interval_in_s();;
}

bool CDC6T::setup_model_with_steps_string(string data)
{
    return false;
}

bool CDC6T::setup_model_with_psse_string(string data)
{
    bool is_successful = false;
    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<24)
        return is_successful;

    string model_name = get_string_data(dyrdata[1],"");
    if(model_name!="CDC6T")
        return is_successful;


    // iblcok iunblock for instantenous block or unblock
    // dblcok dunblock for delayed block or unblock
    // ibupass iunbupass for instantenous bupass or unbupass
    // dbupass dunbupass for delayed bupass or unbupass
    double min_alpha, min_gamma, tvdci, tidc, vac_iblock, vac_dunblock, t_block,
           vdc_ibypass, vac_dunbypass, t_bypass,
           vdcmin_unblock, idcmin_unblock, vdc_ramp, idc_ramp,
           c0, v1, c1, v2, c2, v3, c3,  t_switched,
           vac_dblock, t_dblock, t_dunblock,
           vaci_iblock, t_comm,
           vac_dbypass, t_dbypass, ti_dunblock,
           t_dunbypass, tvdcr;


    size_t i=2;
    min_alpha = get_double_data(dyrdata[i],"0.0"); i++;
    min_gamma = get_double_data(dyrdata[i],"0.0"); i++;
    tvdci = get_double_data(dyrdata[i],"0.0"); i++;
    tidc = get_double_data(dyrdata[i],"0.0"); i++;
    vac_iblock = get_double_data(dyrdata[i],"0.0"); i++;
    vac_dunblock = get_double_data(dyrdata[i],"0.0"); i++;
    t_block = get_double_data(dyrdata[i],"0.0"); i++;
    vdc_ibypass = get_double_data(dyrdata[i],"0.0"); i++;
    vac_dunbypass = get_double_data(dyrdata[i],"0.0"); i++;
    t_bypass = get_double_data(dyrdata[i],"0.0"); i++;
    vdcmin_unblock = get_double_data(dyrdata[i],"0.0"); i++;
    idcmin_unblock = get_double_data(dyrdata[i],"0.0"); i++;
    vdc_ramp = get_double_data(dyrdata[i],"0.0"); i++;
    idc_ramp = get_double_data(dyrdata[i],"0.0"); i++;
    c0 = get_double_data(dyrdata[i],"0.0"); i++;
    v1 = get_double_data(dyrdata[i],"0.0"); i++;
    c1 = get_double_data(dyrdata[i],"0.0"); i++;
    v2 = get_double_data(dyrdata[i],"0.0"); i++;
    c2 = get_double_data(dyrdata[i],"0.0"); i++;
    v3 = get_double_data(dyrdata[i],"0.0"); i++;
    c3 = get_double_data(dyrdata[i],"0.0"); i++;
    t_switched = get_double_data(dyrdata[i],"0.0"); i++;

   vac_dblock = get_double_data(dyrdata[i],"0.0"); i++;
   t_dblock = get_double_data(dyrdata[i],"0.0"); i++;
   t_dunblock = get_double_data(dyrdata[i],"0.0"); i++;
   vaci_iblock = get_double_data(dyrdata[i],"0.0"); i++;
   t_comm = get_double_data(dyrdata[i],"0.0"); i++;
   vac_dbypass = get_double_data(dyrdata[i],"0.0"); i++;
   t_dbypass = get_double_data(dyrdata[i],"0.0"); i++;
   ti_dunblock = get_double_data(dyrdata[i],"0.0"); i++;
   t_dunbypass = get_double_data(dyrdata[i],"0.0"); i++;
   tvdcr = get_double_data(dyrdata[i],"0.0"); i++;

    set_converter_dynamic_min_alpha_or_gamma_in_deg(RECTIFIER, min_alpha);
    set_converter_dynamic_min_alpha_or_gamma_in_deg(INVERTER, min_gamma);
    set_inverter_dc_voltage_sensor_T_in_s(tvdci);
    set_dc_current_sensor_T_in_s(tidc);
    set_rectifier_ac_instantaneous_blocking_voltage_in_pu(vac_iblock);
    set_rectifier_ac_delayed_unblocking_voltage_in_pu(vac_dunblock);
    set_mininum_blocking_time_in_s(t_block);
    set_inverter_dc_instantaneous_bypassing_voltage_in_kV(vdc_ibypass);
    set_inverter_ac_delayed_unbypassing_voltage_in_pu(vac_dunbypass);
    set_mininum_bypassing_time_in_s(t_bypass);
    set_minimum_dc_voltage_in_kV_following_unblocking_and_unbypassing(vdcmin_unblock);
    set_minimum_dc_current_in_kA_following_unblocking(idcmin_unblock);
    set_dc_voltage_command_recovery_rate_in_pu_per_second(vdc_ramp);
    set_dc_current_command_recovery_rate_in_pu_per_second(idc_ramp);
    set_minimum_dc_current_command_in_kA(c0*0.001);

    VDCOL limiter;
    limiter.append_vdcol_point_in_kV_kA(v1, c1*0.001);
    limiter.append_vdcol_point_in_kV_kA(v2, c2*0.001);
    limiter.append_vdcol_point_in_kV_kA(v3, c3*0.001);
    set_VDCOL(limiter);

    set_minimum_time_in_switched_mode_in_s(t_switched);

    set_rectifier_ac_delayed_blocking_voltage_in_pu(vac_dblock);
    set_rectifier_ac_delayed_blocking_time_in_s(t_dblock);
    set_rectifier_ac_delayed_unblocking_time_in_s(t_dunblock);
    set_inverter_ac_instantenous_blocking_voltage_in_pu(vaci_iblock);
    set_communication_delay_between_converters_in_s(t_comm);
    set_inverter_ac_delayed_bypassing_voltage_in_pu(vac_dbypass);
    set_inverter_ac_delayed_bypassing_time_in_s(t_dbypass);
    set_inverter_ac_delayed_unblocking_time_in_s(ti_dunblock);
    set_inverter_ac_delayed_unbypassing_time_in_s(t_dunbypass);
    set_rectifier_dc_voltage_sensor_T_in_s(tvdcr);

    is_successful = true;

    return is_successful;
}

bool CDC6T::setup_model_with_bpa_string(string data)
{
    return false;
}

void CDC6T::initialize()
{
    if(is_model_initialized())
        return;

    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc==NULL)
        return;

    rec_ac_blocking_timer.set_attached_device(hvdc);
    inv_ac_bypassing_timer.set_attached_device(hvdc);
    set_attached_device_of_common_meters();

    double Vdcr = hvdc->get_converter_dc_voltage_in_kV(RECTIFIER);
    rectifier_dc_voltage_sensor.set_output(Vdcr);
    rectifier_dc_voltage_sensor.initialize();

    double Vdci = hvdc->get_converter_dc_voltage_in_kV(INVERTER);
    inverter_dc_voltage_sensor.set_output(Vdci);
    inverter_dc_voltage_sensor.initialize();

    double Idc = hvdc->get_line_dc_current_in_kA();
    dc_current_sensor.set_output(Idc);
    dc_current_sensor.initialize();

    set_flag_model_initialized_as_true();
}

void CDC6T::run(DYNAMIC_MODE mode)
{
    ostringstream sstream;

    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc==NULL)
        return;

    //solve_hvdc_model_without_integration();

    double Vdcr = hvdc->get_converter_dc_voltage_in_kV(RECTIFIER);
    rectifier_dc_voltage_sensor.set_input(Vdcr);
    rectifier_dc_voltage_sensor.run(mode);
    double Vdcr_sensed = rectifier_dc_voltage_sensor.get_output();

    double Vdci = hvdc->get_converter_dc_voltage_in_kV(INVERTER);
    inverter_dc_voltage_sensor.set_input(Vdci);
    inverter_dc_voltage_sensor.run(mode);
    double Vdci_sensed = inverter_dc_voltage_sensor.get_output();

    double Idc = hvdc->get_line_dc_current_in_kA();
    dc_current_sensor.set_input(Idc);
    dc_current_sensor.run(mode);
    double Idc_sensed = dc_current_sensor.get_output();

    //cout<<"Ecomp="<<Ecomp<<", Vref="<<Vref<<", Vs="<<Vs<<", Efd="<<exciter.get_output()<<endl;

    if(mode == UPDATE_MODE)
        set_flag_model_updated_as_true();
}

void CDC6T::solve_hvdc_model_without_integration()
{
    ostringstream sstream;

    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc==NULL)
        return;

    check_blocking_logic();
    check_bypassing_logic();
    check_mode_switching_logic();

    if(not is_blocked())
    {
        double Vdci_measured = inverter_dc_voltage_sensor.get_output();
        double Idc_measured = dc_current_sensor.get_output();
        double Icommand = get_rectifier_dc_current_command_in_kA(Vdci_measured, Idc_measured);
        double Vcommand = get_inverter_dc_voltage_command_in_kV(Icommand);
        solve_hvdc_model_without_line_dynamics(Icommand, Vcommand);
    }
}

void CDC6T::check_blocking_logic()
{
    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc==NULL)
        return;

    if(is_manual_blocked())
        return;

    double TIME = hvdc->get_dynamic_simulator_time_in_s();

    ostringstream sstream;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    size_t bus_r = hvdc->get_converter_bus(RECTIFIER);
    size_t bus_i = hvdc->get_converter_bus(INVERTER);
    double vac_r = psdb->get_bus_voltage_in_pu(bus_r);
    double vac_i = psdb->get_bus_voltage_in_pu(bus_i);

    if(not is_blocked())
    {
        double vacr_iblock = get_rectifier_ac_instantaneous_blocking_voltage_in_pu();
        double vacr_dblock = get_rectifier_ac_delayed_blocking_voltage_in_pu();
        double tr_dblock = get_rectifier_ac_delayed_blocking_time_in_s();
        double vaci_iblock = get_inverter_ac_instantenous_blocking_voltage_in_pu();
        double t_comm = get_communication_delay_between_converters_in_s();

        bool block_flag = false;

        if(vac_r<vacr_iblock) // rectifier instantaneous blcok
        {
            sstream<<hvdc->get_device_name()<<" will be blocked at time "<<TIME<<" s due to instantaneous drop of rectifier AC voltage."<<endl;
            sstream<<"Rectifier AC voltage is "<<vac_r<<" pu, and rectifier AC blocking voltage threshold is "<<vacr_iblock<<" pu.";
            show_information_with_leading_time_stamp(sstream);

            block_flag = true;
        }

        if(not rec_ac_blocking_timer.is_started()) // set or clear rectifier delay block time
        {
            if(vac_r<vacr_dblock)
            {
                rec_ac_blocking_timer.start();

                sstream<<hvdc->get_device_name()<<" rectifier AC blocking timer is started at time "<<TIME<<" s due to drop of rectifier AC voltage."<<endl;
                sstream<<"Rectifier AC voltage is "<<vac_r<<" pu, and rectifier AC delayed blocking voltage threshold is "<<vacr_dblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);
            }
        }
        else
        {
            if(vac_r>vacr_dblock)
            {
                rec_ac_blocking_timer.reset();

                sstream<<hvdc->get_device_name()<<" rectifier AC blocking timer is reset at time "<<TIME<<" s due to recovery of rectifier AC voltage."<<endl;
                sstream<<"Rectifier AC voltage is "<<vac_r<<" pu, and rectifier AC delayed blocking voltage threshold is "<<vacr_dblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);
            }
        }

        if(rec_ac_blocking_timer.is_started()) // check rectifier delayed blocked logic
        {
            if(rec_ac_blocking_timer.is_timed_out())
            {
                sstream<<hvdc->get_device_name()<<" rectifier AC blocking timer is timed out and will be blocked at time "<<TIME<<" s due to remaining drop of rectifier AC voltage for "<<tr_dblock<<" s."<<endl;
                sstream<<"Rectifier AC voltage is "<<vac_r<<" pu, and AC delayed blocking voltage threshold is "<<vacr_dblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                block_flag = true;
            }
        }

        if(not inv_ac_blocking_signal_transmitting_timer.is_started())
        {
            if(vac_i<vaci_iblock) // set inverter instantaneous block time
            {
                sstream<<hvdc->get_device_name()<<" inverter AC blocking timer is started and block signal is sent to rectifier at time "<<TIME<<" s due to drop of inverter AC voltage"<<endl;
                sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC instantaneous blocking voltage threshold is "<<vaci_iblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                inv_ac_blocking_signal_transmitting_timer.start();
            }
        }
        if(inv_ac_blocking_signal_transmitting_timer.is_started()) // check inverter block logic
        {
            if(inv_ac_blocking_signal_transmitting_timer.is_timed_out())
            {
                sstream<<hvdc->get_device_name()<<" inverter AC blocking timer is timed out and will be blocked at time "<<TIME<<" s due to drop of inverter AC voltage after "<<t_comm<<" s."<<endl;
                sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC instantaneous blocking voltage threshold is "<<vaci_iblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                block_flag = true;
            }
        }

        if(block_flag) // ready to block hvdc
        {
            block_hvdc();
            rec_ac_blocking_timer.reset();
            inv_ac_blocking_signal_transmitting_timer.reset();

            rec_ac_unblocking_timer.reset();

            inv_ac_unblocking_timer.reset();
            inv_ac_unblocking_signal_transmitting_timer.reset();
        }
    }
    else
    {
        double vacr_dunblock = get_rectifier_ac_delayed_unblocking_voltage_in_pu();
        double tr_dunblock = get_rectifier_ac_delayed_unblocking_time_in_s();
        double vaci_dunblock = get_inverter_ac_delayed_unbypassing_voltage_in_pu();
        double ti_dunblock = get_inverter_ac_delayed_unblocking_time_in_s();
        double t_comm = get_communication_delay_between_converters_in_s();

        bool rectifier_unblock_logic = false;
        bool inverter_unblock_logic = false;
        bool timer_unblock_logic = false;

        if(not rec_ac_unblocking_timer.is_started())
        {
            if(vac_r >= vacr_dunblock)
            {
                sstream<<hvdc->get_device_name()<<" rectifier AC unblocking timer is started at time "<<TIME<<" s due to recovery of rectifier AC voltage."<<endl;
                sstream<<"Rectifier AC voltage is "<<vac_r<<" pu, and rectifier AC delayed unblocking voltage threshold is "<<vacr_dunblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                rec_ac_unblocking_timer.start();
            }
        }
        else
        {
            if(vac_r < vacr_dunblock)
            {
                sstream<<hvdc->get_device_name()<<" rectifier AC unblocking timer is reset at time "<<TIME<<" s due to drop of rectifier AC voltage."<<endl;
                sstream<<"Rectifier AC voltage is "<<vac_r<<" pu, and rectifier AC delayed unblocking voltage threshold is "<<vacr_dunblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                rec_ac_unblocking_timer.reset();
            }
        }

        if(not inv_ac_unblocking_signal_transmitting_timer.is_started()) // signal not set
        {
            if(not inv_ac_unblocking_timer.is_started())
            {
                if(vac_i >= vaci_dunblock)
                {
                    sstream<<hvdc->get_device_name()<<" inverter AC unblocking timer is started at time "<<TIME<<" s due to recovery of inverter AC voltage."<<endl;
                    sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC delayed unblocking voltage threshold is "<<vaci_dunblock<<" pu.";
                    show_information_with_leading_time_stamp(sstream);

                    inv_ac_unblocking_timer.start();
                }
            }
            else
            {
                if(vac_i < vaci_dunblock)
                {
                    sstream<<hvdc->get_device_name()<<" inverter AC unblocking timer is reset at time "<<TIME<<" s due to drop of inverter AC voltage."<<endl;
                    sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC delayed unblocking voltage threshold is "<<vaci_dunblock<<" pu.";
                    show_information_with_leading_time_stamp(sstream);

                    inv_ac_unblocking_timer.reset();
                }
                else
                {
                    if(inv_ac_unblocking_timer.is_timed_out())
                    {
                        sstream<<hvdc->get_device_name()<<" inverter AC unblocking timer is timed out and unblocking signal is sent to rectifier side at time "<<TIME<<" s since inverter unblocking timer is timed out."<<endl;
                        sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC delayed unblocking voltage threshold is "<<vaci_dunblock<<" pu.";
                        show_information_with_leading_time_stamp(sstream);

                        inv_ac_unblocking_timer.reset();
                        inv_ac_unblocking_signal_transmitting_timer.start();
                    }
                }
            }
        }

        if(rec_ac_unblocking_timer.is_started() and inv_ac_unblocking_signal_transmitting_timer.is_started())
        {
            if(is_block_timer_timed_out() and rec_ac_unblocking_timer.is_timed_out() and inv_ac_unblocking_signal_transmitting_timer.is_timed_out())
            {
                sstream<<hvdc->get_device_name()<<" block timer, rectifier AC unblocking timer, and inverter AC unblocking signal transmitting timer are timed out, and will be unblocked at time "<<TIME<<" s due to recovery of rectifier and inverter AC voltage for at least "<<tr_dunblock<<" s"<<endl
                  <<"Rectifier AC voltage is "<<vac_r<<" pu, and rectifier AC unblocking voltage threshold is "<<vacr_dunblock<<" pu."<<endl
                  <<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC unblocking voltage threshold is "<<vaci_dunblock<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                unblock_hvdc();
                rec_ac_unblocking_timer.reset();
                inv_ac_unblocking_signal_transmitting_timer.reset();
            }
        }
    }
}

void CDC6T::check_bypassing_logic()
{
    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc==NULL)
        return;

    if(is_blocked())
        return;

    if(is_manual_bypassed())
        return;

    double TIME = hvdc->get_dynamic_simulator_time_in_s();

    POWER_SYSTEM_DATABASE* psdb = hvdc->get_power_system_database();
    ostringstream sstream;

    if(not is_bypassed())
    {
        double t_unblock = get_unblocking_time();
        if(fabs(t_unblock - INFINITE_THRESHOLD)>FLOAT_EPSILON)
            return;

        double t_unbypass = get_unbypassing_time();
        if(t_unbypass==INFINITE_THRESHOLD) // not unbypassing
        {
            double vdc_i = get_converter_dc_voltage_in_kV(INVERTER);
            double vdc_ibypass = get_inverter_dc_instantenous_bypassing_voltage_in_kV();
            bool bypass_logic = false;
            if(vdc_i<vdc_ibypass)
            {
                sstream<<hvdc->get_device_name()<<" will be bypassed at time "<<TIME<<" s due to instantaneous drop of inverter DC voltage."<<endl;
                sstream<<"Inverter DC voltage is "<<vdc_i<<" kV, and inverter DC bypassing voltage threshold is "<<vdc_ibypass<<" kV.";
                show_information_with_leading_time_stamp(sstream);

                bypass_logic = true;
            }

            double vac_i = psdb->get_bus_voltage_in_pu(hvdc->get_converter_bus(INVERTER));
            double vaci_dbypass = get_inverter_ac_delayed_bypassing_voltage_in_pu();
            double ti_dbypass = get_inverter_ac_delayed_bypassing_time_in_s();
            if(not inv_ac_bypassing_timer.is_started())
            {
                if(vac_i<=vaci_dbypass)
                {
                    sstream<<hvdc->get_device_name()<<" inverter AC bypassing timer is started at time "<<TIME<<" s due to drop of inverter AC voltage."<<endl;
                    sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC bypassing voltage threshold is "<<vaci_dbypass<<" pu.";
                    show_information_with_leading_time_stamp(sstream);

                    inv_ac_bypassing_timer.start();
                }
            }
            else
            {
                if(vac_i>vaci_dbypass)
                {
                    sstream<<hvdc->get_device_name()<<" inverter AC bypassing timer is reset at time "<<TIME<<" s due to recovery of inverter AC voltage."<<endl;
                    sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC bypassing voltage threshold is "<<vaci_dbypass<<" pu.";
                    show_information_with_leading_time_stamp(sstream);

                    inv_ac_bypassing_timer.reset();
                }
                else
                {
                    if(inv_ac_bypassing_timer.is_timed_out())
                    {
                        sstream<<hvdc->get_device_name()<<" inverter AC bypassing timer is timed out and will be bypassed at time "<<TIME<<" s due to timed out timer of inverter AC voltage drop."<<endl;
                        sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC bypassing voltage threshold is "<<vaci_dbypass<<" pu.";
                        show_information_with_leading_time_stamp(sstream);

                        bypass_logic = true;
                    }
                }
            }
            if(bypass_logic==true)
            {
                bypass_hvdc();
                inv_ac_bypassing_timer.reset(); // clear timer
            }
        }
    }
    else
    {
        POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
        size_t bus_i = hvdc->get_converter_bus(INVERTER);
        double vac_i = psdb->get_bus_voltage_in_pu(bus_i);

        double vac_dunbypass = get_inverter_ac_delayed_unbypassing_voltage_in_pu();
        double t_dunbypass = get_inverter_ac_delayed_unbypassing_time_in_s();
        if(not inv_ac_unbypassing_timer.is_started())
        {
            if(vac_i>vac_dunbypass)
            {
                sstream<<hvdc->get_device_name()<<" inverter AC unbypassing timer is started at time "<<TIME<<" s due to recovery of inverter AC voltage."<<endl;
                sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and AC unbypassing voltage threshold is "<<vac_dunbypass<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                inv_ac_unbypassing_timer.start();
            }
        }
        else
        {
            if(vac_i<vac_dunbypass)
            {
                sstream<<hvdc->get_device_name()<<" inverter AC unbypassing timer is reset at time "<<TIME<<" s due to drop of inverter AC voltage."<<endl;
                sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and AC unbypassing voltage threshold is "<<vac_dunbypass<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                inv_ac_unbypassing_timer.reset();
            }
        }

        if(inv_ac_unbypassing_timer.is_started())
        {
            if(is_bypass_timer_timed_out() and inv_ac_unbypassing_timer.is_timed_out())
            {
                sstream<<hvdc->get_device_name()<<" bypass timer and inverter AC unbypassing timer are timed out, and will be unbypassed at time "<<TIME<<" s due to recovery of inverter AC voltage."<<endl;
                sstream<<"Inverter AC voltage is "<<vac_i<<" pu, and inverter AC unbypassing voltage threshold is "<<vac_dunbypass<<" pu.";
                show_information_with_leading_time_stamp(sstream);

                unbypass_hvdc();
                inv_ac_unbypassing_timer.reset();
            }
        }
    }
}

void CDC6T::check_mode_switching_logic()
{
    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc==NULL)
        return;

    if(is_blocked() or is_bypassed())
        return;

    double TIME = hvdc->get_dynamic_simulator_time_in_s();

    double t_unblock = get_unblocking_time();
    double t_unbypass = get_unbypassing_time();
    if(fabs(t_unblock-INFINITE_THRESHOLD)>FLOAT_EPSILON or fabs(t_unbypass-INFINITE_THRESHOLD)>FLOAT_EPSILON) // unblocking or unbypassing
        return;

    double vdc_i = hvdc->get_converter_dc_voltage_in_kV(INVERTER);
    double vmode = hvdc->get_threshold_dc_voltage_for_constant_power_and_constant_current_mode_in_kV();
    if(not is_mode_switched())
    {
        if(hvdc->get_converter_operation_mode(RECTIFIER)==RECTIFIER_CONSTANT_POWER)
        {
            if(vdc_i<vmode)
            {
                ostringstream sstream;
                sstream<<hvdc->get_device_name()<<" will switch mode from holding DC power to holding DC current at time "<<TIME<<" s due to drop of inverter DC voltage."<<endl;
                sstream<<"Inverter DC voltage is "<<vdc_i<<" kV, and DC mode switch voltage threshold is "<<vmode<<" kV.";
                show_information_with_leading_time_stamp(sstream);

                switch_hvdc_mode();
            }
        }
    }
    else
    {
        if(is_mode_switch_timer_timed_out() and vdc_i> vmode)
        {
            ostringstream sstream;
            sstream<<hvdc->get_device_name()<<" mode switch timer is timed out, and will switch back to DC power control mode at time "<<TIME<<" s due to recovery of inverter DC voltage."<<endl;
            sstream<<"Inverter DC voltage is "<<vdc_i<<" pu, andDC mode switch voltage threshold is "<<vmode<<" pu.";
            show_information_with_leading_time_stamp(sstream);

            switch_hvdc_mode_back();
        }
    }
}

void CDC6T::check()
{
    ;
}

void CDC6T::report()
{
    ostringstream sstream;
    sstream<<get_standard_model_string();
    show_information_with_leading_time_stamp(sstream);
}

void CDC6T::save()
{
    ;
}

string CDC6T::get_standard_model_string() const
{
    ostringstream sstream;

    HVDC* hvdc = (HVDC*) get_device_pointer();
    size_t rbus = hvdc->get_converter_bus(RECTIFIER);
    size_t ibus = hvdc->get_converter_bus(INVERTER);
    string dcname = hvdc->get_name();

    VDCOL vdcol_limiter = get_VDCOL();

    sstream<<"\""<<dcname<<"\", \"CDC6T\", ";
    sstream<<setw(8)<<setprecision(4)<<get_converter_dynamic_min_alpha_or_gamma_in_deg(RECTIFIER)<<", "
           <<setw(8)<<setprecision(4)<<get_converter_dynamic_min_alpha_or_gamma_in_deg(INVERTER)<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_dc_voltage_sensor_T_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_dc_current_sensor_T_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_rectifier_ac_instantaneous_blocking_voltage_in_pu()<<", "
           <<setw(8)<<setprecision(4)<<get_rectifier_ac_delayed_unblocking_voltage_in_pu()<<", "
           <<setw(8)<<setprecision(4)<<get_mininum_blocking_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_dc_instantenous_bypassing_voltage_in_kV()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_ac_delayed_unbypassing_voltage_in_pu()<<", "
           <<setw(8)<<setprecision(4)<<get_mininum_bypassing_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_minimum_dc_voltage_in_kV_following_unblocking_and_unbypassing()<<", "
           <<setw(8)<<setprecision(4)<<get_minimum_dc_current_in_kA_following_unblocking()*1000.0<<", "
           <<setw(8)<<setprecision(4)<<get_dc_voltage_command_recovery_rate_in_pu_per_second()<<", "
           <<setw(8)<<setprecision(4)<<get_dc_current_command_recovery_rate_in_pu_per_second()<<", "
           <<setw(8)<<setprecision(4)<<get_minimum_dc_current_command_in_kA()*1000.0<<", "
           <<setw(8)<<setprecision(4)<<vdcol_limiter.get_vdcol_voltage_of_point_in_kV(0)<<", "
           <<setw(8)<<setprecision(4)<<vdcol_limiter.get_vdcol_current_of_point_in_kA(0)*1000.0<<", "
           <<setw(8)<<setprecision(4)<<vdcol_limiter.get_vdcol_voltage_of_point_in_kV(1)<<", "
           <<setw(8)<<setprecision(4)<<vdcol_limiter.get_vdcol_current_of_point_in_kA(1)*1000.0<<", "
           <<setw(8)<<setprecision(4)<<vdcol_limiter.get_vdcol_voltage_of_point_in_kV(2)<<", "
           <<setw(8)<<setprecision(4)<<vdcol_limiter.get_vdcol_current_of_point_in_kA(2)*1000.0<<", "
           <<setw(8)<<setprecision(4)<<get_minimum_time_in_switched_mode_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_rectifier_ac_delayed_blocking_voltage_in_pu()<<", "
           <<setw(8)<<setprecision(4)<<get_rectifier_ac_delayed_blocking_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_rectifier_ac_delayed_unblocking_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_ac_instantenous_blocking_voltage_in_pu()<<", "
           <<setw(8)<<setprecision(4)<<get_communication_delay_between_converters_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_ac_delayed_bypassing_voltage_in_pu()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_ac_delayed_bypassing_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_ac_delayed_unblocking_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_inverter_ac_delayed_unbypassing_time_in_s()<<", "
           <<setw(8)<<setprecision(4)<<get_rectifier_dc_voltage_sensor_T_in_s()<<"  /";

    return sstream.str();
}


size_t CDC6T::get_variable_index_from_variable_name(string var_name)
{
    return MODEL::get_variable_index_from_variable_name(var_name, MODEL_VARIABLE_TABLE);
}

string CDC6T::get_variable_name_from_variable_index(size_t var_index)
{
    return MODEL::get_variable_name_from_variable_index(var_index, MODEL_VARIABLE_TABLE);
}

double CDC6T::get_variable_with_index(size_t var_index)
{
    string var_name = get_variable_name_from_variable_index(var_index);
    return get_variable_with_name(var_name);
}

double CDC6T::get_variable_with_name(string var_name)
{
    /*
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

    if(var_name == "STATE@REGULATOR")
        return regulator.get_state();

    if(var_name == "STATE@FEEDBACKER")
        return feedbacker.get_state();

    if(var_name == "STATE@EXCITER")
        return exciter.get_state();
    */
    return 0.0;
}



string CDC6T::get_dynamic_data_in_psse_format() const
{
    return "";
}

string CDC6T::get_dynamic_data_in_bpa_format() const
{
    return get_dynamic_data_in_psse_format();
}

string CDC6T::get_dynamic_data_in_steps_format() const
{
    return get_dynamic_data_in_psse_format();
}