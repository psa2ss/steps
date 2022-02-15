#ifndef VSC_HVDC_CONVERTER_MODEL_H_INCLUDED
#define VSC_HVDC_CONVERTER_MODEL_H_INCLUDED

#include "header/model/vsc_hvdc_model/vsc_hvdc_model.h"

class VSC_HVDC_CONVERTER_MODEL: public VSC_HVDC_MODEL
{
    public:
        VSC_HVDC_CONVERTER_MODEL(STEPS& toolkit);
        virtual ~VSC_HVDC_CONVERTER_MODEL();
    public: // model type
        virtual string get_model_type() const;

        void set_converter_name(string name);
        string get_converter_name() const;
        unsigned int get_converter_name_index() const;
        unsigned int get_converter_index() const;
        unsigned int get_converter_bus() const;

        void set_as_voltage_source();
        void set_as_current_source();
        bool is_voltage_source() const;

        void set_converter_active_control_mode(VSC_HVDC_CONVERTER_ACTIVE_POWER_DYNAMIC_CONTROL_MODE active_control_mode);
        void set_converter_reactive_control_mode(VSC_HVDC_CONVERTER_REACTIVE_POWER_DYNAMIC_CONTROL_MODE reactive_control_mode);

        VSC_HVDC_CONVERTER_ACTIVE_POWER_DYNAMIC_CONTROL_MODE get_converter_active_control_mode() const;
        VSC_HVDC_CONVERTER_REACTIVE_POWER_DYNAMIC_CONTROL_MODE get_converter_reactive_control_mode() const;

    public:
        // specific model
        virtual string get_model_name() const = 0;

        virtual bool setup_model_with_steps_string_vector(vector<string>& data) = 0;
        virtual bool setup_model_with_psse_string(string data) = 0;
        virtual bool setup_model_with_bpa_string(string data) = 0;

        virtual void setup_block_toolkit_and_parameters() = 0;

        virtual void initialize() = 0;
        virtual void run(DYNAMIC_MODE mode) = 0;
        virtual void check() = 0;
        virtual void clear() = 0;
        virtual void report() = 0;
        virtual void save() = 0;
        virtual string get_standard_psse_string(bool export_internal_bus_number=false) const = 0;

        virtual void prepare_model_data_table() = 0;
        virtual double get_model_data_with_name(string par_name) const = 0;
        virtual void set_model_data_with_name(string par_name, double value) = 0;
        virtual double get_minimum_nonzero_time_constant_in_s() = 0;

        virtual void prepare_model_internal_variable_table() = 0;
        virtual double get_model_internal_variable_with_name(string var_name)= 0;

        virtual string get_dynamic_data_in_psse_format() const = 0;
        virtual string get_dynamic_data_in_bpa_format() const = 0;
        virtual string get_dynamic_data_in_steps_format() const = 0;
    public:
        virtual complex<double> get_converter_voltage_in_dq_axis_in_pu() = 0;
        virtual complex<double> get_converter_voltage_in_xy_axis_in_pu() = 0;
        virtual complex<double> get_converter_current_in_dq_axis_in_pu() = 0;
        virtual complex<double> get_converter_current_in_xy_axis_in_pu() = 0;
        virtual complex<double> get_converter_Norton_current_in_xy_axis_in_pu_based_on_SBASE() = 0;

    public:
        void initialize_current_or_voltage_source_equivalent_scale();
        complex<double> get_current_source_equivalent_scale() const;
        complex<double> get_voltage_source_equivalent_admittance() const;
    private:
        unsigned int converter_index;
        unsigned int converter_name_index;
        bool voltage_source_flag;

        unsigned int control_mode; // change to enum, dynamic version.
        VSC_HVDC_CONVERTER_ACTIVE_POWER_DYNAMIC_CONTROL_MODE active_power_control_mode;
        VSC_HVDC_CONVERTER_REACTIVE_POWER_DYNAMIC_CONTROL_MODE reactive_power_control_mode;

        complex<double> current_or_voltage_equivalent_scale;
};

#endif // VSC_HVDC_CONVERTER_MODEL_H_INCLUDED