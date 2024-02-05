#ifndef WT3GX_H
#define WT3GX_H

#include "header/model/wtg_models/wt_generator_model/wt_generator_model.h"
#include "header/model/wtg_models/wt_generator_model/lvpl.h"
#include "header/model/converter_common_models/vsg_model/vsg0.h"
#include "header/block/integral_block.h"
#include "header/block/first_order_block.h"

class WT3GX : public WT_GENERATOR_MODEL
{
    public:
        WT3GX(STEPS& toolkit);
        WT3GX(const WT3GX& model);
        virtual ~WT3GX();
        virtual WT3GX& operator=(const WT3GX&);

        void set_converter_activer_current_command_T_in_s(double t);
        void set_converter_reactiver_voltage_command_T_in_s(double t);
        void set_LVPL(const LVPL& lvpl);
        void set_HVRC_voltage_in_pu(double v);
        void set_HVRC_current_in_pu(double i);
        void set_LVPL_max_rate_of_active_current_change(double rate);
        void set_LVPL_voltage_sensor_T_in_s(double t);
        void set_Tj_in_s(double T);
        void set_D(double D);
        void set_Ku(double Ku);
        void set_Te_in_s(double T);

        double get_converter_activer_current_command_T_in_s() const;
        double get_converter_reactiver_voltage_command_T_in_s() const;
        LVPL get_LVPL() const;
        double get_HVRC_voltage_in_pu() const;
        double get_HVRC_current_in_pu() const;
        double get_LVPL_max_rate_of_active_current_change() const;
        double get_LVPL_voltage_sensor_T_in_s() const;
        double get_Tj_in_s() const;
        double get_D() const;
        double get_Ku() const;
        double get_Te_in_s() const;


        virtual string get_model_name() const;

        virtual bool setup_model_with_steps_string_vector(vector<string>& data);
        virtual bool setup_model_with_psse_string(string data);
        virtual bool setup_model_with_bpa_string(string data);

        virtual void prepare_model_data_table();
        virtual void prepare_model_internal_variable_table();

        virtual void setup_block_toolkit_and_parameters();

        virtual void initialize();
        virtual void run(DYNAMIC_MODE mode);
        virtual complex<double> get_source_Norton_equivalent_complex_current_in_pu_in_xy_axis_based_on_sbase();
        virtual complex<double> get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();
        virtual complex<double> get_terminal_complex_current_in_pu_in_xy_axis_based_on_sbase();
        virtual double get_terminal_current_in_pu_based_on_mbase();
        virtual double get_terminal_current_in_pu_based_on_sbase();

        virtual void check();
        virtual void clear();
        virtual void report();
        virtual void save();
        virtual string get_standard_psse_string(bool export_internal_bus_number=false) const;

        virtual double get_model_data_with_name(string par_name) const;
        virtual void set_model_data_with_name(string par_name, double value);
        virtual double get_minimum_nonzero_time_constant_in_s();
        virtual double get_model_internal_variable_with_name(string var_name);

        virtual complex<double> get_terminal_complex_power_in_pu_based_on_mbase();
        virtual complex<double> get_terminal_complex_power_in_MVA();
        virtual double get_terminal_active_power_in_pu_based_on_mbase();
        virtual double get_terminal_active_power_in_MW();
        virtual double get_terminal_reactive_power_in_pu_based_on_mbase();
        virtual double get_terminal_reactive_power_in_MVar();
        virtual double get_active_power_generation_including_stator_loss_in_pu_based_on_mbase();
        virtual double get_active_power_generation_including_stator_loss_in_MW();

        virtual double get_pll_angle_in_rad();
        virtual double get_pll_angle_in_deg();
        virtual double get_pll_frequency_deviation_in_pu();
        virtual double get_pll_frequency_deviation_in_Hz();
        virtual double get_pll_frequency_in_pu();
        virtual double get_pll_frequency_in_Hz();
        virtual complex<double> get_internal_voltage_in_pu_in_xy_axis();

        virtual string get_dynamic_data_in_psse_format() const;
        virtual string get_dynamic_data_in_bpa_format() const;
        virtual string get_dynamic_data_in_steps_format() const;
    private:
        void copy_from_const_model(const WT3GX& model);

        INTEGRAL_BLOCK active_current_commander;
        double LVPL_active_power_change_rate;
        FIRST_ORDER_BLOCK LVPL_voltage_sensor;
        LVPL lvpl;

        FIRST_ORDER_BLOCK reactive_voltage_commander;
        double HVRCR_voltage, HVRCR_current;

        VSG0 vsg;
};

#endif // GENERATOR_MODEL_H
