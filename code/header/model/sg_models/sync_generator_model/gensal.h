#ifndef GENSAL_H
#define GENSAL_H

#include "header/model/sg_models/sync_generator_model/sync_generator_model.h"
#include "header/block/integral_block.h"


class GENSAL : public SYNC_GENERATOR_MODEL
{
    public:
        GENSAL(STEPS& toolkit);
        GENSAL(const GENSAL& model);
        virtual ~GENSAL();
        virtual GENSAL& operator=(const GENSAL& model);

        virtual string get_model_name() const;

        virtual void update_source_impedance();

        virtual bool setup_model_with_steps_string_vector(vector<string>& data);
        virtual bool setup_model_with_psse_string(string data);
        virtual bool setup_model_with_bpa_string(string data);

        virtual void prepare_model_data_table();
        virtual void prepare_model_internal_variable_table();

        virtual void initialize();
        virtual void initialize_rotor_angle();
        virtual void run(DYNAMIC_MODE mode);
        virtual complex<double> get_source_Norton_equivalent_complex_current_in_pu_in_xy_axis_based_on_sbase();
        virtual complex<double> get_terminal_complex_current_in_pu_in_dq_axis_based_on_mbase();
        virtual complex<double> get_terminal_complex_current_in_pu_in_xy_axis_based_on_mbase();
        virtual complex<double> get_terminal_complex_current_in_pu_in_xy_axis_based_on_sbase();
        virtual double get_terminal_current_in_pu_based_on_mbase();
        virtual double get_terminal_current_in_pu_based_on_sbase();

        virtual void check();
        virtual void clear();
        virtual void report();
        virtual void save();
        virtual string get_standard_psse_string() const;

        virtual double get_model_data_with_name(string par_name) const;
        virtual void set_model_data_with_name(string par_name, double value);
        virtual double get_minimum_nonzero_time_constant_in_s();
        virtual double get_model_internal_variable_with_name(string var_name);

        virtual double get_air_gap_power_in_pu_based_on_mbase();
        virtual double get_air_gap_power_in_MW();
        virtual double get_air_gap_torque_in_pu_based_on_mbase();
        virtual double get_accelerating_power_in_pu_based_on_mbase();
        virtual double get_accelerating_power_in_MW();
        virtual complex<double> get_terminal_complex_power_in_pu_based_on_mbase();
        virtual complex<double> get_terminal_complex_power_in_MVA();
        virtual double get_terminal_active_power_in_pu_based_on_mbase();
        virtual double get_terminal_active_power_in_MW();
        virtual double get_terminal_reactive_power_in_pu_based_on_mbase();
        virtual double get_terminal_reactive_power_in_MVar();
        virtual double get_field_current_in_pu_based_on_mbase();

        virtual double get_rotor_angle_in_rad();
        virtual double get_rotor_angle_in_deg();
        virtual double get_rotor_speed_deviation_in_pu();
        virtual double get_rotor_speed_in_pu();
        virtual complex<double> get_internal_voltage_in_pu_in_dq_axis();
        virtual complex<double> get_internal_voltage_in_pu_in_xy_axis();

        virtual string get_dynamic_data_in_psse_format() const;
        virtual string get_dynamic_data_in_bpa_format() const;
        virtual string get_dynamic_data_in_steps_format() const;
    public:
        // the following two functions are used to model GENSAL as ideal voltage source
        // with set_excitation_voltage_in_pu(), GENSAL is user controllable.
        void set_rotor_angle_in_deg(double angle);
        void set_rotor_speed_deviation_in_pu(double speed);
    private:
        void copy_from_const_model(const GENSAL& model);

        /*INTEGRAL_BLOCK transient_block_d_axis, subtransient_block_d_axis;
        INTEGRAL_BLOCK subtransient_block_q_axis;
        INTEGRAL_BLOCK rotor_angle_block, rotor_speed_block;*/
};


#endif // GENERATOR_MODEL_H
