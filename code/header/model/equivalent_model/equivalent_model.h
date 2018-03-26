#ifndef EQUIVALENT_MODEL_H
#define EQUIVALENT_MODEL_H

#include "header/model/model.h"
#include <complex>


class EQUIVALENT_MODEL : public MODEL
{
    public:
        EQUIVALENT_MODEL();
        virtual ~EQUIVALENT_MODEL();
        // common equivalent model
        virtual string get_model_type() const;

    public: // specific model level
        virtual string get_model_name() const = 0;

        virtual double get_double_data_with_index(size_t index) const = 0;
        virtual double get_double_data_with_name(string par_name) const = 0;
        virtual void set_double_data_with_index(size_t index, double value) = 0;
        virtual void set_double_data_with_name(string par_name, double value) = 0;

        virtual bool setup_model_with_steps_string(string data) = 0;
        virtual bool setup_model_with_psse_string(string data) = 0;
        virtual bool setup_model_with_bpa_string(string data) = 0;

        virtual void initialize() = 0;
        virtual void run(DYNAMIC_MODE mode) = 0;
        virtual void update_meters_buffer() = 0;
        virtual void update_equivalent_outputs() = 0;
        virtual complex<double> get_equivalent_voltage_source_voltage_in_pu() const = 0;
        virtual complex<double> get_equivalent_voltage_source_impedance_in_pu() const = 0;
        virtual complex<double> get_equivalent_nominal_constant_power_load_in_MVA() const = 0;
        virtual complex<double> get_equivalent_nominal_constant_current_load_in_MVA() const = 0;
        virtual complex<double> get_equivalent_nominal_constant_impedance_load_in_MVA() const = 0;
        virtual void check() = 0;
        virtual void report() = 0;
        virtual void save() = 0;
        virtual string get_standard_model_string() const = 0;
        virtual void switch_output_to_equivalent_device() = 0;

        virtual size_t get_variable_index_from_variable_name(string var_name)= 0;
        virtual string get_variable_name_from_variable_index(size_t var_index)= 0;
        virtual double get_variable_with_index(size_t var_index)= 0;
        virtual double get_variable_with_name(string var_name)= 0;

        virtual string get_dynamic_data_in_psse_format() const = 0;
        virtual string get_dynamic_data_in_bpa_format() const = 0;
        virtual string get_dynamic_data_in_steps_format() const = 0;

};
#endif // EQUIVALENT_MODEL_H
