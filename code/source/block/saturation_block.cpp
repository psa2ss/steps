#include "header/block/saturation_block.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include <iostream>

using namespace std;

SATURATION_BLOCK::SATURATION_BLOCK()
{
    set_saturation_type(QUADRATIC_SATURATION_TYPE);
    set_S1(0.0);
    set_S2(0.0);
}

SATURATION_BLOCK::~SATURATION_BLOCK()
{
    ;
}

void SATURATION_BLOCK::set_saturation_type(SATURATION_TYPE sat_type)
{
    this->type = sat_type;
}

void SATURATION_BLOCK::set_V1(double V)
{
    this->V1 = V;
}

void SATURATION_BLOCK::set_V2(double V)
{
    this->V2 = V;
}
void SATURATION_BLOCK::set_S1(double S)
{
    this->S1 = S;
}

void SATURATION_BLOCK::set_S2(double S)
{
    this->S2 = S;
}


SATURATION_TYPE SATURATION_BLOCK::get_saturation_type() const
{
    return type;
}

double SATURATION_BLOCK::get_V1() const
{
    return V1;
}

double SATURATION_BLOCK::get_V2() const
{
    return V2;
}

double SATURATION_BLOCK::get_S1() const
{
    return S1;
}

double SATURATION_BLOCK::get_S2() const
{
    return S2;
}

bool SATURATION_BLOCK::is_saturation_considered() const
{
    if(get_S1()==0.0 and get_S2()==0.0)
        return false;
    else
        return true;
}

double SATURATION_BLOCK::get_saturation(double V) const
{
    if(not is_saturation_considered())
        return 0.0;

    double S = 0.0;

    double V1 = get_V1();
    double V2 = get_V2();
    double S1 = get_S1();
    double S2 = get_S2();
    switch(get_saturation_type())
    {
        case QUADRATIC_SATURATION_TYPE:
        {
            // S = B*(V-A)^2/V
            // S1 = B*(V1-A)^2/V1
            // S2 = B*(V2-A)^2/V2
            // division:
            // S1/S2 = ((V1-A)/(V2-A))^2*(V2/V1)
            // ((V1-A)/(V2-A))^2 = (S1/S2)/(V2/V1) = (S1*V1)/(S2*V2) = C2
            double C2 = (S1*V1)/(S2*V2);
            double C = sqrt(C2);
            // V1-A = C*(V2-A)  or V1-A = -C*(V2-A)
            // A = (C*V2-V1)/(C-1) or A = (V1+C*V2)/(1+C)
            // to make sure S function is increasing with V, A must be less than min(V1, V2)
            // if V1<V2 (and S1<S2, C<1)
            // if we choose A = (V1+C*V2)/(1+C), we should have
            // (V1+C*V2)/(1+C)<V1, or V2<V1, which is wrong;
            // if we choose A = (C*V2-V1)/(C-1), we should have
            // (C*V2-V1)/(C-1)<V1, or V2>V1, which is correct.

            // if V1>V2 (and S1>S2, C>1)
            // if we choose A = (V1+C*V2)/(1+C), we should have
            // (V1+C*V2)/(1+C)<V2, or V1<V2, which is wrong;
            // if we choose A = (C*V2-V1)/(C-1), we should have
            // (C*V2-V1)/(C-1)<V2, or V1>V2, which is correct.
            double A;
            /*if(C>=1.0)
                A = (V1+C*V2)/(1.0+C);
            else
                A = (C*V2-V1)/(C-1.0);*/
            A = (C*V2-V1)/(C-1.0);
            // B=S1*V1/(V1-A)^2
            double B = S1*V1/((V1-A)*(V1-A));


            if(V>A)
                S = B*(V-A)*(V-A)/V;
            else
                S = 0.0;

            break;
        }
        default:
        {
            //S=A*V^X
            //S1=A*V1^X
            //S2=A*V2^X
            // division
            // S1/S2 = (V1/V2)^X
            double X = log(S1/S2)/log(V1/V2);
            double A = S1/pow(V1,X);

            S=A*pow(V,X);
            break;
        }
    }

    return S;
}


void SATURATION_BLOCK::check()
{
    ostringstream sstream;
    if( (V1<V2 and S1>S2) or (V1>V2 and S1<S2) )
    {
        sstream<<"Warning. Saturation with greater input should not be less. Saturation block is not properly set."<<endl
          <<"V1="<<setprecision(3)<<fixed<<V1<<", "
          <<"S1="<<setprecision(6)<<fixed<<S1<<", "
          <<"V2="<<setprecision(3)<<fixed<<V2<<", "
          <<"S2="<<setprecision(6)<<fixed<<S2;
        show_information_with_leading_time_stamp(sstream);
    }
}


