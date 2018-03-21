#include "header/basic/utility_test.h"
#include "header/steps_namespace.h"
#include "header/prepare_for_tests/prepare_models_for_test.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

UTILITY_TEST::UTILITY_TEST()
{
    //TEST_ADD(UTILITY_TEST::test_num2str);
    TEST_ADD(UTILITY_TEST::test_str2int);
    TEST_ADD(UTILITY_TEST::test_str2double);
    TEST_ADD(UTILITY_TEST::test_string2upper);

    TEST_ADD(UTILITY_TEST::test_get_integer_data);
    TEST_ADD(UTILITY_TEST::test_get_double_data);
    TEST_ADD(UTILITY_TEST::test_get_string_data);

    TEST_ADD(UTILITY_TEST::test_rad2deg);
    TEST_ADD(UTILITY_TEST::test_deg2rad);

    TEST_ADD(UTILITY_TEST::test_trim_string);
    TEST_ADD(UTILITY_TEST::test_replace_string_contents);
    TEST_ADD(UTILITY_TEST::test_shrink_sucessive_blanks);
    TEST_ADD(UTILITY_TEST::test_string2csv);
    TEST_ADD(UTILITY_TEST::test_split_string);

    TEST_ADD(UTILITY_TEST::test_redirect_and_recover_stdout);

    TEST_ADD(UTILITY_TEST::test_get_built_in_power_system_database_of_number);
    TEST_ADD(UTILITY_TEST::test_reset_power_system_database);

    TEST_ADD(UTILITY_TEST::test_is_file_exist);
    TEST_ADD(UTILITY_TEST::test_set_get_dynamic_simulation_time_step);
}

void UTILITY_TEST::setup()
{
    db = new POWER_SYSTEM_DATABASE;
}

void UTILITY_TEST::tear_down()
{
    delete db;

    show_test_end_information();
}

void UTILITY_TEST::test_num2str()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(num2str(123)=="123"); // integer
    TEST_ASSERT(num2str(123.45)=="123.45"); // float
    TEST_ASSERT(num2str(123456.7)=="123456.7");
    cout<<get_system_time_stamp_string()<<" "<<num2str(123456.7)<<endl;
    TEST_ASSERT(num2str(1000000)=="1E+6");
    cout<<get_system_time_stamp_string()<<" "<<num2str(1000000)<<endl;
}

void UTILITY_TEST::test_str2int()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(str2int("123")==123);
    TEST_ASSERT(str2int("123.45")==123);
    TEST_ASSERT(str2int("123.5")==124);
}
void UTILITY_TEST::test_str2double()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(fabs(str2double("123.0")-123)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(str2double("123.45")-123.45)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(str2double("1.23e3")-1230)<FLOAT_EPSILON);
}


void UTILITY_TEST::test_get_integer_data()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(get_integer_data("10","2")==10);
    TEST_ASSERT(get_integer_data("","2")==2);
}

void UTILITY_TEST::test_get_double_data()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(fabs(get_double_data("10.0","100.0")-10.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(get_double_data("","100.0")-100.0)<FLOAT_EPSILON);
}

void UTILITY_TEST::test_get_string_data()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(get_string_data("AB","DEF")=="AB");
    TEST_ASSERT(get_string_data("'AB'","DEF")=="AB");
    TEST_ASSERT(get_string_data("","DEF")=="DEF");
    TEST_ASSERT(get_string_data("1","1")=="1");
}


void UTILITY_TEST::test_string2upper()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(string2upper("abc DeF.")=="ABC DEF.");
}

void UTILITY_TEST::test_rad2deg()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    double angle = 0.234;
    double angle2 = angle/PI*180.0;
    TEST_ASSERT(fabs(rad2deg(angle)-angle2)<FLOAT_EPSILON);
}

void UTILITY_TEST::test_deg2rad()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    double angle = 23.45;
    double angle2 = angle/180.0*PI;
    TEST_ASSERT(fabs(deg2rad(angle)-angle2)<FLOAT_EPSILON);
}

void UTILITY_TEST::test_trim_string()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    string str=" \t  \n \t\nA\tB C\nD\n\t  \t \n";
    TEST_ASSERT(trim_string(str)=="A\tB C\nD");

}
void UTILITY_TEST::test_replace_string_contents()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    string str="abAB12''\"\"";
    TEST_ASSERT(replace_string_contents(str, "ab", "AB")=="ABAB12''\"\"");
    TEST_ASSERT(replace_string_contents(str, "12", "21")=="abAB21''\"\"");
    TEST_ASSERT(replace_string_contents(str, "'", "\"")=="abAB12\"\"\"\"");
    TEST_ASSERT(replace_string_contents(str, "\"", "'")=="abAB12''''");
    TEST_ASSERT(replace_string_contents(str, "c", "C")=="abAB12''\"\"");

}
void UTILITY_TEST::test_shrink_sucessive_blanks()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    string str="a    bc  \t d";
    TEST_ASSERT(shrink_sucessive_blanks(str)=="a bc d");
}
void UTILITY_TEST::test_string2csv()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");
    string str="1 2  3,4 ,5, 6 , 7 '8 9' \" 0 1\"";
    str = string2csv(str);
    TEST_ASSERT(str=="1,2,3,4,5,6,7,\"8 9\",\" 0 1\"");

}
void UTILITY_TEST::test_split_string()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

}

void UTILITY_TEST::test_redirect_and_recover_stdout()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    redirect_stdout_to_file("test_log/test_redirect_stdout.dat");
    show_information_with_leading_time_stamp("This is a test line for redirecting stdout to this file.");
    show_information_with_leading_time_stamp("This is the second test line for redirecting stdout to this file.");

    recover_stdout();
    show_information_with_leading_time_stamp("This line should be outputted to stdout.");
}

void UTILITY_TEST::test_get_built_in_power_system_database_of_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    POWER_SYSTEM_DATABASE* psdb = get_built_in_power_system_database_of_number(0);

    TEST_ASSERT(psdb->get_allowed_max_bus_number()==100);

    psdb->set_allowed_max_bus_number(1000);
    TEST_ASSERT(psdb->get_allowed_max_bus_number()==1000);
}

void UTILITY_TEST::test_reset_power_system_database()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(db->get_bus_count()==0);

    db->set_allowed_max_bus_number(1000);
    TEST_ASSERT(db->get_allowed_max_bus_number()==1000);

    reset_power_system_database();
    TEST_ASSERT(db->get_bus_count()==0);
}

void UTILITY_TEST::test_is_file_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    TEST_ASSERT(is_file_exist("sample.raw")==true);
    TEST_ASSERT(is_file_exist("sample2.raw")==false);
}

void UTILITY_TEST::test_set_get_dynamic_simulation_time_step()
{
    show_test_information_for_function_of_class(__FUNCTION__,"UTILITY_TEST");

    set_dynamic_simulation_time_step_in_s(0.01);
    TEST_ASSERT(fabs(get_dynamic_simulation_time_step_in_s()-0.01)<FLOAT_EPSILON);

    set_dynamic_simulation_time_step_in_s(0.02);
    TEST_ASSERT(fabs(get_dynamic_simulation_time_step_in_s()-0.02)<FLOAT_EPSILON);
}