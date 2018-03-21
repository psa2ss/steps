#ifndef WT3G2_TEST_H
#define WT3G2_TEST_H


#include <cstdlib>
#include <cstring>
#include <iostream>

#ifdef _MSC_VER
	#pragma warning (disable: 4290)
#endif

#include "header/model/source_model/pe_source_model/pe_source_model_test.h"

#include "header/model/source_model/pe_source_model/wt3g2.h"


using namespace std;

class WT3G2_TEST : public PE_SOURCE_MODEL_TEST
{
    public:
        WT3G2_TEST();
    protected:
        virtual void setup();
        virtual void tear_down();
    protected:
        virtual void test_get_model_name();
        virtual void test_set_get_parameters();
        virtual void test_initialize_and_get_initialized_inputs();
        void test_set_get_pll_angle();
    private:
};

#endif//WT3G2_TEST_H
