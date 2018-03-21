#ifndef WT3G2_H
#define WT3G2_H

#include "header/model/source_model/pe_source_model/pe_source_model.h"
#include "header/model/source_model/pe_source_model/lvpl.h"
#include "header/block/integral_block.h"
#include "header/block/first_order_block.h"

class WT3G2 : public PE_SOURCE_MODEL
{
    public:
        WT3G2();
        WT3G2(const WT3G2& model);
        virtual ~WT3G2();
        virtual WT3G2& operator=(const WT3G2&);

        void set_number_of_lumped_wind_turbines(size_t n);
        void set_converter_activer_current_command_T_in_s(double t);
        void set_converter_reactiver_voltage_command_T_in_s(double t);
        void set_KPLL(double K);
        void set_KIPLL(double K);
        void set_PLLmax(double pmax);
        void set_turbine_rated_power_in_MW(double P);
        void set_LVPL(const LVPL& lvpl);
        void set_HVRC_voltage_in_pu(double v);
        void set_HVRC_current_in_pu(double i);
        void set_LVPL_max_rate_of_active_current_change(double rate);
        void set_LVPL_voltage_sensor_T_in_s(double t);

        size_t get_number_of_lumped_wind_turbines() const;
        double get_converter_activer_current_command_T_in_s() const;
        double get_converter_reactiver_voltage_command_T_in_s() const;
        double get_KPLL() const;
        double get_KIPLL() const;
        double get_PLLmax() const;
        double get_turbine_rated_power_in_MW() const;
        LVPL get_LVPL() const;
        double get_HVRC_voltage_in_pu() const;
        double get_HVRC_current_in_pu() const;
        double get_LVPL_max_rate_of_active_current_change() const;
        double get_LVPL_voltage_sensor_T_in_s() const;


        virtual string get_model_name() const;

        virtual bool setup_model_with_steps_string(string data);
        virtual bool setup_model_with_psse_string(string data);
        virtual bool setup_model_with_bpa_string(string data);

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
        virtual string get_standard_model_string() const;

        virtual size_t get_variable_index_from_variable_name(string var_name);
        virtual string get_variable_name_from_variable_index(size_t var_index);
        virtual double get_variable_with_index(size_t var_index);
        virtual double get_variable_with_name(string var_name);

        virtual complex<double> get_terminal_complex_power_in_pu_based_on_mbase();
        virtual complex<double> get_terminal_complex_power_in_MVA();
        virtual double get_terminal_active_power_in_pu_based_on_mbase();
        virtual double get_terminal_active_power_in_MW();
        virtual double get_terminal_reactive_power_in_pu_based_on_mbase();
        virtual double get_terminal_reactive_power_in_MVar();

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
    public:
        // the following function are used to model WT3G2 as ideal voltage source
        void set_pll_angle_in_deg(double angle);
    private:
        void copy_from_const_model(const WT3G2& model);

        size_t number_of_lumped_wind_turbines;
        double KPLL, KIPLL, PLLmax, Pnominal_MW;
        LVPL lvpl;
        double LVPL_active_power_change_rate;
        double HVRCR_voltage, HVRCR_current;

        INTEGRAL_BLOCK active_current_commander;
        FIRST_ORDER_BLOCK reactive_voltage_commander;
        INTEGRAL_BLOCK PLL_frequency_integrator, PLL_angle_integrator;
        FIRST_ORDER_BLOCK LVPL_voltage_sensor;

};

#endif // GENERATOR_MODEL_H