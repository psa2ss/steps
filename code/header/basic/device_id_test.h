#ifndef DEVICE_ID_TEST_H
#define DEVICE_ID_TEST_H

#include <iostream>

#ifdef _MSC_VER
	#pragma warning (disable: 4290)
#endif

#include "thirdparty/cpptest/cpptest.h"

#include "header/basic/device_id.h"

using namespace std;

class DEVICE_ID_TEST : public Test::Suite
{
    public:
        DEVICE_ID_TEST();
    protected:
        virtual void setup();
        virtual void tear_down();
    private:
        void test_constructor_and_get_device_type_generator();

        void test_constructor_and_get_device_type_pe_source();

        void test_constructor_and_get_device_type_load();

        void test_constructor_and_get_device_type_fixedshunt();

        void test_constructor_and_get_device_type_switchedshunt();

        void test_constructor_and_get_device_type_equivalent_device();

        void test_constructor_and_get_device_type_line();

        void test_constructor_and_get_device_type_transformer();

        void test_constructor_and_get_device_type_hvdc();

        void test_constructor_and_get_device_type_vschvdc();

        void test_constructor_and_get_device_type_facts();

        void test_constructor_and_get_device_type_multidc();

        void test_constructor_and_get_device_type_arbitrary();

        void test_set_get_device_identifier();

        void test_get_device_name();

        void test_is_valid();

        void test_clear();
        void test_copy_with_operator_equal();
        void test_compare_less();
        void test_compare_equal_not_equal();

    private:
        DEVICE_ID* device_id;
        TERMINAL terminal_1_bus, terminal_2_bus, terminal_3_bus, terminal_4_bus, terminal_100_bus, terminal_101_bus;
};

#endif //DEVICE_ID_TEST_H