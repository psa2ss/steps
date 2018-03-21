#include "header/model/turbine_governor_model/IEEEG2_test.h"
#include "header/basic/utility.h"
using namespace std;

IEEEG2_TEST::IEEEG2_TEST()
{
    TEST_ADD(IEEEG2_TEST::test_get_model_type);
    TEST_ADD(IEEEG2_TEST::test_get_model_name);
    TEST_ADD(IEEEG2_TEST::test_set_get_parameters);
    TEST_ADD(IEEEG2_TEST::test_initialize);
    TEST_ADD(IEEEG2_TEST::test_set_get_mechanical_power_reference);
    TEST_ADD(IEEEG2_TEST::test_set_get_mechanical_power_upper_limit);
    TEST_ADD(IEEEG2_TEST::test_set_get_mechanical_power_lower_limit);
    TEST_ADD(IEEEG2_TEST::test_step_response);

}

void IEEEG2_TEST::setup()
{
    TURBINE_GOVERNOR_MODEL_TEST::setup();

    IEEEG2 model;

    GENERATOR* genptr = get_generator();

    model.set_K(20.0);
    model.set_T1_in_s(0.1);
    model.set_T2_in_s(0.5);
    model.set_T3_in_s(0.2);
    model.set_Pmax_in_pu(1.0);
    model.set_Pmin_in_pu(0.0);
    model.set_T4_in_s(2.0);

    genptr->set_model(&model);
}

void IEEEG2_TEST::tear_down()
{
    TURBINE_GOVERNOR_MODEL_TEST::tear_down();
}

void IEEEG2_TEST::test_get_model_type()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");

    GENERATOR* genptr = get_generator();
    TURBINE_GOVERNOR_MODEL* model = genptr->get_turbine_governor_model();

    TEST_ASSERT(model->get_model_type()=="TURBINE GOVERNOR");
}

void IEEEG2_TEST::test_get_model_name()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");

    GENERATOR* genptr = get_generator();
    TURBINE_GOVERNOR_MODEL* model = genptr->get_turbine_governor_model();

    TEST_ASSERT(model->get_model_name()=="IEEEG2");
}

void IEEEG2_TEST::test_set_get_parameters()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");

    GENERATOR* genptr = get_generator();
    IEEEG2* model = (IEEEG2*) genptr->get_turbine_governor_model();

    TEST_ASSERT(fabs(model->get_K()-20.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(model->get_T1_in_s()-0.1)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(model->get_T2_in_s()-0.5)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(model->get_T3_in_s()-0.2)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(model->get_Pmax_in_pu()-1.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(model->get_Pmin_in_pu()-0.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(model->get_T4_in_s()-2.0)<FLOAT_EPSILON);
}

void IEEEG2_TEST::test_initialize()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");

    GENERATOR* genptr = get_generator();
    SYNC_GENERATOR_MODEL* genmodel = genptr->get_sync_generator_model();
    genmodel->initialize();

    double Pmech0 = genmodel->get_initial_mechanical_power_in_pu_based_on_mbase();

    IEEEG2* model = (IEEEG2*) genptr->get_turbine_governor_model();

    model->set_Pmax_in_pu(1.2);

    model->initialize();
    double Pref = Pmech0;

    TEST_ASSERT(fabs(model->get_mechanical_power_in_pu_based_on_mbase()-Pmech0)<FLOAT_EPSILON);

    TEST_ASSERT(fabs(model->get_mechanical_power_reference_in_pu_based_on_mbase()-Pref)<FLOAT_EPSILON);
}

void IEEEG2_TEST::test_set_get_mechanical_power_reference()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");

    GENERATOR* genptr = get_generator();
    IEEEG2* model = (IEEEG2*) genptr->get_turbine_governor_model();

    model->set_mechanical_power_reference_in_pu_based_on_mbase(1.5);
    TEST_ASSERT(fabs(model->get_mechanical_power_reference_in_pu_based_on_mbase()-1.5)<FLOAT_EPSILON);
}

void IEEEG2_TEST::test_set_get_mechanical_power_upper_limit()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG1_TEST");

    GENERATOR* genptr = get_generator();
    IEEEG2* model = (IEEEG2*) genptr->get_turbine_governor_model();

    model->set_Pmax_in_pu(1.5);
    TEST_ASSERT(fabs(model->get_mechanical_power_upper_limit_in_pu_based_on_mbase()-1.5)<FLOAT_EPSILON);
}

void IEEEG2_TEST::test_set_get_mechanical_power_lower_limit()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG1_TEST");

    GENERATOR* genptr = get_generator();
    IEEEG2* model = (IEEEG2*) genptr->get_turbine_governor_model();

    model->set_Pmin_in_pu(0.5);
    TEST_ASSERT(fabs(model->get_mechanical_power_lower_limit_in_pu_based_on_mbase()-0.5)<FLOAT_EPSILON);
}
void IEEEG2_TEST::test_step_response()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");

    redirect_stdout_to_file("test_log/step_response_of_IEEEG2_model.txt");

    GENERATOR* genptr = get_generator();
    IEEEG2* model = (IEEEG2*) genptr->get_turbine_governor_model();

    model->set_Pmax_in_pu(1.5);

    run_step_response_of_turbine_govnernor_model();

    recover_stdout();

}

void IEEEG2_TEST::test_get_standard_model_string()
{
    show_test_information_for_function_of_class(__FUNCTION__,"IEEEG2_TEST");
}


