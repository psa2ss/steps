#ifndef WT3T0_H
#define WT3T0_H

#include "header/model/wtg_models/wt_turbine_model/wt_turbine_model.h"
#include "header/block/integral_block.h"

class WT3T0 : public WT_TURBINE_MODEL
{
    public:
        WT3T0();
        WT3T0(const WT3T0& model);
        virtual ~WT3T0();
        virtual WT3T0& operator=(const WT3T0& model);
    public: // specific model level
        virtual string get_model_name() const;

        void set_Hturbine_in_s(double H);
        void set_Hgenerator_in_s(double H);
        void set_Kshaft_in_pu(double f);
        void set_Dshaft_in_pu(double D);

        double get_Hturbine_in_s() const;
        double get_Hgenerator_in_s() const;
        double get_Kshaft_in_pu() const;
        double get_Dshaft_in_pu() const;

    public:
        virtual double get_model_data_with_index(size_t index) const;
        virtual double get_model_data_with_name(string par_name) const;
        virtual void set_model_data_with_index(size_t index, double value);
        virtual void set_model_data_with_name(string par_name, double value);

        virtual bool setup_model_with_steps_string(string data);
        virtual bool setup_model_with_psse_string(string data);
        virtual bool setup_model_with_bpa_string(string data);

        virtual void initialize();
        virtual void run(DYNAMIC_MODE mode);
        virtual double get_turbine_speed_in_pu() const;
        virtual double get_generator_speed_in_pu() const;
        virtual double get_rotor_angle_in_deg() const;
        virtual double get_rotor_angle_in_rad() const;
        virtual void check();
        virtual void clear();
        virtual void report();
        virtual void save();
        virtual string get_standard_model_string() const;

        virtual double get_variable_with_name(string var_name);

        virtual string get_dynamic_data_in_psse_format() const;
        virtual string get_dynamic_data_in_bpa_format() const;
        virtual string get_dynamic_data_in_steps_format() const;
    private:
        void copy_from_const_model(const WT3T0& model);
        virtual void prepare_model_variable_table();

        INTEGRAL_BLOCK shaft_twist_block;
        INTEGRAL_BLOCK turbine_inertia_block;
        INTEGRAL_BLOCK generator_inertia_block;
        INTEGRAL_BLOCK generator_rotor_angle_block;

        double Dshaft;
};

#endif // WT3T0_H
