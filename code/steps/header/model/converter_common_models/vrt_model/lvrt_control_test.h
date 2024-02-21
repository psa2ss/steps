#ifndef LVRT_CONTROL_TEST_H
#define LVRT_CONTROL_TEST_H

#include <istream>
#include <cstdlib>
#include <cstring>
#include <iostream>

#ifdef _MSC_VER
	#pragma warning (disable: 4290)
#endif

#include "cpptest.h"

#include "header/power_system_database.h"
#include "header/STEPS.h"
#include "header/model/converter_common_models/vrt_model/lvrt_control.h"
using namespace std;

class LVRT_CONTROL_TEST : public Test::Suite
{
    public:
        LVRT_CONTROL_TEST();
    protected:
        virtual void setup();
        virtual void tear_down();
        virtual void test_get_bus();
        virtual void test_get_device();
        virtual void test_get_bus_voltage();
        virtual void test_set_get_vrt_voltage_threshold();
        virtual void test_set_vrt_prepare2recover_delay_time_in_s();
        virtual void test_set_get_vrt_status();

        virtual void test_set_get_time_when_vrt_enter_during_status();
        virtual void test_set_get_time_when_vrt_enter_prepare2recover_status();
        virtual void test_set_get_time_when_vrt_enter_recover_status();
        virtual void test_set_get_Ip0_vrt_activated_in_pu();
        virtual void test_set_get_Iq0_vrt_activated_in_pu();
        virtual void test_set_get_P0_vrt_activated_in_pu_based_on_mbase();
        virtual void test_set_get_Q0_vrt_activated_in_pu_based_on_mbase();
        virtual void test_set_get_Ip0_vrt_prepare2recover_activated_in_pu();
        virtual void test_set_get_Iq0_vrt_prepare2recover_activated_in_pu();
        virtual void test_set_get_P0_vrt_prepare2recover_activated_in_pu_based_on_mbase();
        virtual void test_set_get_Q0_vrt_prepare2recover_activated_in_pu_based_on_mbase();
        virtual void test_set_get_Ip0_vrt_recover_activated_in_pu();
        virtual void test_set_get_Iq0_vrt_recover_activated_in_pu();
        virtual void test_set_get_P0_vrt_recover_activated_in_pu_based_on_mbase();
        virtual void test_set_get_Q0_vrt_recover_activated_in_pu_based_on_mbase();


        virtual void test_set_get_PQ_vrt_during_mode();
        virtual void test_set_get_kP();
        virtual void test_set_get_P_set_in_pu();
        virtual void test_set_get_k1_Ip();
        virtual void test_set_get_k2_Ip();
        virtual void test_set_get_Ip_set_in_pu();
        virtual void test_set_get_LVPL_low_voltage_in_pu();
        virtual void test_set_get_LVPL_high_voltage_in_pu();
        virtual void test_set_get_LVPL_gain_at_high_voltage();
        virtual void test_check_vrt_status_basic();
        virtual void test_check_vrt_status_comprehensive();


    private:
        LVRT_CONTROL* lvrt;
};

#endif//LVRT_CONTROL_TEST_H
