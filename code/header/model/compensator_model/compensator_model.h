#ifndef COMPENSATOR_MODEL_H
#define COMPENSATOR_MODEL_H

#include "header/model/model.h"
#include "header/block/integral_block.h"
#include <complex>

class COMPENSATOR_MODEL : public MODEL
{
    /*
    Compensator model
    Inputs:
        Generator terminal voltage
        Generator terminal current
    Output:
        Compensated voltage
    */
    public:
        COMPENSATOR_MODEL();
        virtual ~COMPENSATOR_MODEL();
    public: // compensator common
        virtual string get_model_type() const;
        // common inputs
        complex<double> get_generator_terminal_voltage_in_pu() const;
        complex<double> get_generator_terminal_current_in_pu() const;
    public: // specific compensator
        virtual string get_model_name() const = 0;

        virtual bool setup_model_with_steps_string(string data) = 0;
        virtual bool setup_model_with_psse_string(string data) = 0;
        virtual bool setup_model_with_bpa_string(string data) = 0;

        virtual void initialize() = 0;
        virtual void run(DYNAMIC_MODE mode) = 0;
        virtual double get_compensated_voltage_in_pu() const = 0; // output
        virtual void check() = 0;
        virtual void clear() = 0;
        virtual void report() = 0;
        virtual void save() = 0;
        virtual string get_standard_model_string() const = 0;

        virtual size_t get_variable_index_from_variable_name(string var_name)= 0;
        virtual string get_variable_name_from_variable_index(size_t var_index)= 0;
        virtual double get_variable_with_index(size_t var_index)= 0;
        virtual double get_variable_with_name(string var_name)= 0;

        virtual string get_dynamic_data_in_psse_format() const = 0;
        virtual string get_dynamic_data_in_bpa_format() const = 0;
        virtual string get_dynamic_data_in_steps_format() const = 0;
    private:
        double ecomp;
};

#endif // COMPENSATOR_MODEL_H