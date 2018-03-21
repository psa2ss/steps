#include "header/block/pd_block.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include <iostream>

using namespace std;

PD_BLOCK::PD_BLOCK()
{
    set_Kp(1.0);
    set_Kd(1.0);
}

PD_BLOCK::~PD_BLOCK()
{
    ;
}

void PD_BLOCK::set_Kp(double K)
{
    if(K==0)
    {
        ostringstream sstream;
        sstream<<"Error. Zero amplifier Kp of PROPORTIONAL_BLOCK part is not allowed for PD_BLOCK.";
        show_information_with_leading_time_stamp(sstream);
        return;
    }
    p_block.set_K(K);
}

double PD_BLOCK::get_Kp() const
{
    return p_block.get_K();
}

void PD_BLOCK::set_Kd(double K)
{
    d_block.set_K(K);
}

double PD_BLOCK::get_Kd() const
{
    return d_block.get_K();
}

void PD_BLOCK::set_Td_in_s(double T)
{
    if(T<=0.0)
    {
        ostringstream sstream;
        sstream<<"Error. Non-positive time constant Td is not allowed for PD_BLOCK.";
        show_information_with_leading_time_stamp(sstream);
        return;
    }
    d_block.set_T_in_s(T);
}

double PD_BLOCK::get_Td_in_s() const
{
    return d_block.get_T_in_s();
}


void PD_BLOCK::set_input(double x)
{
    p_block.set_input(x);
    d_block.set_input(x);
}

void PD_BLOCK::set_output(double y)
{
    p_block.set_output(y);
    d_block.set_input(0.0);
}

double PD_BLOCK::get_input() const
{
    return p_block.get_input();
}

double PD_BLOCK::get_output() const
{
    LIMITER_TYPE limiter = get_limiter_type();
    double vmax = get_upper_limit();
    double vmin = get_lower_limit();

    double y = p_block.get_output() + d_block.get_output();
    if(limiter != NO_LIMITER)
    {
        if(y>vmax)
            y = vmax;
        else
        {
            if(y<vmin)
                y = vmin;
        }
    }
    return y;
}


double PD_BLOCK::get_differentiator_state() const
{
    return d_block.get_state();
}

double PD_BLOCK::get_differentiator_new_state() const
{
    return d_block.get_new_state();
}

double PD_BLOCK::get_differentiator_dstate() const
{
    return d_block.get_dstate();
}

double PD_BLOCK::get_differentiator_store() const
{
    return d_block.get_store();
}

void PD_BLOCK::initialize()
{
    p_block.initialize();
    d_block.initialize();
}

void PD_BLOCK::run(DYNAMIC_MODE mode)
{
    if(mode==INTEGRATE_MODE)
        integrate();
    else
        update();
}

void PD_BLOCK::integrate()
{
    p_block.run(INTEGRATE_MODE);
    d_block.run(INTEGRATE_MODE);
}

void PD_BLOCK::update()
{
    p_block.run(UPDATE_MODE);
    d_block.run(UPDATE_MODE);
}

void PD_BLOCK::check()
{
    check_limiter();
}