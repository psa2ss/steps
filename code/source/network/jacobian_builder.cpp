#include "header/network/jacobian_builder.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"

#include <iostream>
#include <fstream>

using namespace std;

JACOBIAN_BUILDER::JACOBIAN_BUILDER()
{
    network_db = NULL;
}

JACOBIAN_BUILDER::~JACOBIAN_BUILDER()
{
    jacobian_delta_p_over_angle.clear();
    jacobian_delta_p_over_voltage.clear();
    jacobian_delta_q_over_angle.clear();
    jacobian_delta_q_over_voltage.clear();
}


void JACOBIAN_BUILDER::set_network_database(NETWORK_DATABASE* ndb)
{
    if(ndb!=NULL)
        this->network_db = ndb;
    else
    {
        ostringstream sstream;
        sstream<<"Error. Invalid network database (NULL) is given. Failed to connect JACOBIAN_BUILDER to NETWORK_DATABASE.";
        show_information_with_leading_time_stamp(sstream);
    }
}


NETWORK_DATABASE* JACOBIAN_BUILDER::get_network_database() const
{
    return network_db;
}


bool JACOBIAN_BUILDER::is_network_database_set() const
{
    if(get_network_database()!=NULL)
        return true;
    else
    {
        ostringstream sstream;
        sstream<<"Error. Jacobian builder is not connected to any network database."<<endl
          <<"No operation on the jacobian builder will work.";
        show_information_with_leading_time_stamp(sstream);
        return false;
    }
}

void JACOBIAN_BUILDER::build_seprate_jacobians()
{
    if(not is_network_database_set())
        return;

    jacobian_delta_p_over_angle.clear();
    jacobian_delta_p_over_voltage.clear();
    jacobian_delta_q_over_angle.clear();
    jacobian_delta_q_over_voltage.clear();

    double der;

    NETWORK_DATABASE* nw_db = get_network_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    int n = Y.get_matrix_entry_count();
    int row, column;
    for(int k=0; k!=n; ++k)
    {
        row = Y.get_row_number_of_entry_index(k);
        column = Y.get_column_number_of_entry_index(k);
        der = get_jacobian_delta_p_over_angle_of_internal_bus(row,column);
        jacobian_delta_p_over_angle.add_entry(row,column, der);
        der = get_jacobian_delta_p_over_voltage_of_internal_bus(row,column);
        jacobian_delta_p_over_voltage.add_entry(row,column, der);
        der = get_jacobian_delta_q_over_angle_of_internal_bus(row,column);
        jacobian_delta_q_over_angle.add_entry(row,column, der);
        der = get_jacobian_delta_q_over_voltage_of_internal_bus(row,column);
        jacobian_delta_q_over_voltage.add_entry(row,column, der);
    }
    jacobian_delta_p_over_angle.compress_and_merge_duplicate_entries();
    jacobian_delta_p_over_voltage.compress_and_merge_duplicate_entries();
    jacobian_delta_q_over_angle.compress_and_merge_duplicate_entries();
    jacobian_delta_q_over_voltage.compress_and_merge_duplicate_entries();

    ostringstream sstream;
    sstream<<"Done building separate jacobian matrix.";
    show_information_with_leading_time_stamp(sstream);
    return;
}

void JACOBIAN_BUILDER::update_seprate_jacobians()
{
    if(not is_network_database_set())
        return;

    update_jacobian_delta_p_over_angle();
    update_jacobian_delta_p_over_voltage();
    update_jacobian_delta_q_over_angle();
    update_jacobian_delta_q_over_voltage();
}

void JACOBIAN_BUILDER::update_jacobian_delta_p_over_angle()
{
    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    size_t nbus = db->get_in_service_bus_count();
    double der;
    complex<double> y;
    int k_start, k_end;
    k_start = 0;
    size_t ibus;
    for(size_t jbus = 0; jbus!=nbus; jbus++)
    {
        k_end = Y.get_starting_index_of_column(jbus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            ibus = Y.get_row_number_of_entry_index(k);
            if(ibus>jbus)
                break;
            if(ibus==jbus)
            {
                der = get_jacobian_delta_p_over_angle_of_internal_bus(jbus,jbus);
                jacobian_delta_p_over_angle.change_entry_value(jbus,jbus, der);
            }
            else
            {
                der = get_jacobian_delta_p_over_angle_of_internal_bus(ibus,jbus);
                jacobian_delta_p_over_angle.change_entry_value(ibus,jbus, der);
                der = get_jacobian_delta_p_over_angle_of_internal_bus(jbus,ibus);
                jacobian_delta_p_over_angle.change_entry_value(jbus,ibus, der);
            }
        }
        k_start = k_end;
    }
    return;

    for(size_t i=0; i!=nbus; ++i)
    {
        for(size_t j=0; j!=nbus; ++j)
        {
            if(i==j)
            {
                der = get_jacobian_delta_p_over_angle_of_internal_bus(i,i);
                jacobian_delta_p_over_angle.change_entry_value(i,i, der);
            }
            else
            {
                y = Y.get_entry_value(i,j);
                if(y!=0.0)
                {
                    der = get_jacobian_delta_p_over_angle_of_internal_bus(i,j);
                    jacobian_delta_p_over_angle.change_entry_value(i,j,der);
                }
            }
        }
    }
}

void JACOBIAN_BUILDER::update_jacobian_delta_p_over_voltage()
{
    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    size_t nbus = db->get_in_service_bus_count();
    double der;
    complex<double> y;
    int k_start, k_end;
    k_start = 0;
    size_t ibus;
    for(size_t jbus = 0; jbus!=nbus; jbus++)
    {
        k_end = Y.get_starting_index_of_column(jbus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            ibus = Y.get_row_number_of_entry_index(k);
            if(ibus>jbus)
                break;
            if(ibus==jbus)
            {
                der = get_jacobian_delta_p_over_voltage_of_internal_bus(jbus,jbus);
                jacobian_delta_p_over_voltage.change_entry_value(jbus,jbus, der);
            }
            else
            {
                der = get_jacobian_delta_p_over_voltage_of_internal_bus(ibus,jbus);
                jacobian_delta_p_over_voltage.change_entry_value(ibus,jbus, der);
                der = get_jacobian_delta_p_over_voltage_of_internal_bus(jbus,ibus);
                jacobian_delta_p_over_voltage.change_entry_value(jbus,ibus, der);
            }
        }
        k_start = k_end;
    }
    return;


    for(size_t i=0; i!=nbus; ++i)
    {
        for(size_t j=0; j!=nbus; ++j)
        {
            if(i==j)
            {
                der = get_jacobian_delta_p_over_voltage_of_internal_bus(i,i);
                jacobian_delta_p_over_voltage.change_entry_value(i,i, der);
            }
            else
            {
                y = Y.get_entry_value(i,j);
                if(y!=0.0)
                {
                    der = get_jacobian_delta_p_over_voltage_of_internal_bus(i,j);
                    jacobian_delta_p_over_voltage.change_entry_value(i,j, der);
                }
            }
        }
    }
}

void JACOBIAN_BUILDER::update_jacobian_delta_q_over_angle()
{
    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    size_t nbus = db->get_in_service_bus_count();
    double der;
    complex<double> y;

    int k_start, k_end;
    k_start = 0;
    size_t ibus;
    for(size_t jbus = 0; jbus!=nbus; jbus++)
    {
        k_end = Y.get_starting_index_of_column(jbus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            ibus = Y.get_row_number_of_entry_index(k);
            if(ibus>jbus)
                break;
            if(ibus==jbus)
            {
                der = get_jacobian_delta_q_over_angle_of_internal_bus(jbus,jbus);
                jacobian_delta_q_over_angle.change_entry_value(jbus,jbus, der);
            }
            else
            {
                der = get_jacobian_delta_q_over_angle_of_internal_bus(ibus,jbus);
                jacobian_delta_q_over_angle.change_entry_value(ibus,jbus, der);
                der = get_jacobian_delta_q_over_angle_of_internal_bus(jbus,ibus);
                jacobian_delta_q_over_angle.change_entry_value(jbus,ibus, der);
            }
        }
        k_start = k_end;
    }
    return;

    for(size_t i=0; i!=nbus; ++i)
    {
        for(size_t j=0; j!=nbus; ++j)
        {
            if(i==j)
            {
                der = get_jacobian_delta_q_over_angle_of_internal_bus(i,i);
                jacobian_delta_q_over_angle.change_entry_value(i,i, der);
            }
            else
            {
                y = Y.get_entry_value(i,j);
                if(y!=0.0)
                {
                    der = get_jacobian_delta_q_over_angle_of_internal_bus(i,j);
                    jacobian_delta_q_over_angle.change_entry_value(i,j, der);
                }
            }
        }
    }
}

void JACOBIAN_BUILDER::update_jacobian_delta_q_over_voltage()
{
    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    size_t nbus = db->get_in_service_bus_count();
    double der;
    complex<double> y;


    int k_start, k_end;
    k_start = 0;
    size_t ibus;
    for(size_t jbus = 0; jbus!=nbus; jbus++)
    {
        k_end = Y.get_starting_index_of_column(jbus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            ibus = Y.get_row_number_of_entry_index(k);
            if(ibus>jbus)
                break;
            if(ibus==jbus)
            {
                der = get_jacobian_delta_q_over_voltage_of_internal_bus(jbus,jbus);
                jacobian_delta_q_over_voltage.change_entry_value(jbus,jbus, der);
            }
            else
            {
                der = get_jacobian_delta_q_over_voltage_of_internal_bus(ibus,jbus);
                jacobian_delta_q_over_voltage.change_entry_value(ibus,jbus, der);
                der = get_jacobian_delta_q_over_voltage_of_internal_bus(jbus,ibus);
                jacobian_delta_q_over_voltage.change_entry_value(jbus,ibus, der);
            }
        }
        k_start = k_end;
    }
    return;

    for(size_t i=0; i!=nbus; ++i)
    {
        for(size_t j=0; j!=nbus; ++j)
        {
            if(i==j)
            {
                der = get_jacobian_delta_q_over_voltage_of_internal_bus(i,i);
                jacobian_delta_q_over_voltage.change_entry_value(i,i, der);
            }
            else
            {
                y = Y.get_entry_value(i,j);
                if(y!=0.0)
                {
                    der = get_jacobian_delta_q_over_voltage_of_internal_bus(i,j);
                    jacobian_delta_q_over_voltage.change_entry_value(i,j, der);
                }
            }
        }
    }
}

double JACOBIAN_BUILDER::get_jacobian_delta_p_over_angle_of_internal_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    size_t IBUS = nw_db->get_physical_bus_number_of_internal_bus(ibus), JBUS;
    complex<double> Vi = db->get_bus_complex_voltage_in_pu(IBUS), Vj;
    complex<double> y;
    double g, b;
    double Vim, Vjm, anglei, anglej, dangle;

    Vim = abs(Vi);
    anglei = arg(Vi);

    double der = 0.0;

    if(ibus!=jbus)
    {
        y = Y.get_entry_value(ibus, jbus);
        if(y!=0.0)
        {
            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;
            der = -Vim*Vjm*(g*sin(dangle)-b*cos(dangle));
        }
    }
    else
    {
        int k_start = Y.get_starting_index_of_column(ibus);
        int k_end = Y.get_starting_index_of_column(ibus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            jbus = Y.get_row_number_of_entry_index(k);

            y = Y.get_entry_value(ibus, jbus);
            if(y==0.0)
                continue;

            if(ibus == jbus)
                continue;

            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;
            der += Vjm*(g*sin(dangle)-b*cos(dangle));
        }
        der *= Vim;
    }
    return der;
}

double JACOBIAN_BUILDER::get_jacobian_delta_p_over_voltage_of_internal_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    size_t IBUS = nw_db->get_physical_bus_number_of_internal_bus(ibus), JBUS;
    complex<double> Vi = db->get_bus_complex_voltage_in_pu(IBUS), Vj;
    complex<double> y;
    double g, b;
    double Vim, Vjm, anglei, anglej, dangle;

    Vim = abs(Vi);
    anglei = arg(Vi);

    double der = 0.0;

    if(ibus!=jbus)
    {
        y = Y.get_entry_value(ibus, jbus);
        if(y!=0.0)
        {
            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;
            der = -Vim*(g*cos(dangle)+b*sin(dangle));
        }
    }
    else
    {
        int k_start = Y.get_starting_index_of_column(ibus);
        int k_end = Y.get_starting_index_of_column(ibus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            jbus = Y.get_row_number_of_entry_index(k);

            y = Y.get_entry_value(ibus, jbus);
            if(y==0.0)
                continue;

            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;

            if(ibus == jbus)
                der -= 2.0*Vim*g;
            else
                der -= Vjm*(g*cos(dangle)+b*sin(dangle));
        }
    }
    return der;
}

double JACOBIAN_BUILDER::get_jacobian_delta_q_over_angle_of_internal_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    size_t IBUS = nw_db->get_physical_bus_number_of_internal_bus(ibus), JBUS;
    complex<double> Vi = db->get_bus_complex_voltage_in_pu(IBUS), Vj;
    complex<double> y;
    double g, b;
    double Vim, Vjm, anglei, anglej, dangle;

    Vim = abs(Vi);
    anglei = arg(Vi);

    double der = 0.0;

    if(ibus!=jbus)
    {
        y = Y.get_entry_value(ibus, jbus);
        if(y!=0.0)
        {
            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;
            der = Vim*Vjm*(g*cos(dangle)+b*sin(dangle));
        }
    }
    else
    {
        int k_start = Y.get_starting_index_of_column(ibus);
        int k_end = Y.get_starting_index_of_column(ibus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            jbus = Y.get_row_number_of_entry_index(k);

            y = Y.get_entry_value(ibus, jbus);
            if(y==0.0)
                continue;

            if(ibus == jbus)
                continue;

            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;
            der -= Vjm*(g*cos(dangle)+b*sin(dangle));
        }
        der *= Vim;
    }
    return der;
}

double JACOBIAN_BUILDER::get_jacobian_delta_q_over_voltage_of_internal_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();

    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    size_t IBUS = nw_db->get_physical_bus_number_of_internal_bus(ibus), JBUS;
    complex<double> Vi = db->get_bus_complex_voltage_in_pu(IBUS), Vj;
    complex<double> y;
    double g, b;
    double Vim, Vjm, anglei, anglej, dangle;

    Vim = abs(Vi);
    anglei = arg(Vi);

    double der = 0.0;

    if(ibus!=jbus)
    {
        y = Y.get_entry_value(ibus, jbus);
        if(y!=0.0)
        {
            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;
            der = -Vim*(g*sin(dangle)-b*cos(dangle));
        }
    }
    else
    {
        int k_start = Y.get_starting_index_of_column(ibus);
        int k_end = Y.get_starting_index_of_column(ibus+1);
        for(int k=k_start; k!=k_end; ++k)
        {
            jbus = Y.get_row_number_of_entry_index(k);

            y = Y.get_entry_value(ibus, jbus);
            if(y==0.0)
                continue;

            JBUS = nw_db->get_physical_bus_number_of_internal_bus(jbus);
            Vj = db->get_bus_complex_voltage_in_pu(JBUS);
            Vjm = abs(Vj);
            anglej = arg(Vj);
            g = y.real();
            b = y.imag();
            dangle = anglei - anglej;

            if(ibus == jbus)
                der += 2.0*Vim*b;
            else
                der -= Vjm*(g*sin(dangle)-b*cos(dangle));
        }
    }
    return der;
}

double JACOBIAN_BUILDER::get_jacobian_delta_p_over_angle_of_physical_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    if(db->is_bus_exist(ibus) and db->is_bus_exist(jbus))
    {
        size_t ibus_internal = nw_db->get_internal_bus_number_of_physical_bus(ibus);
        size_t jbus_internal = nw_db->get_internal_bus_number_of_physical_bus(jbus);

        return get_jacobian_delta_p_over_angle_of_internal_bus(ibus_internal, jbus_internal);
    }
    else
    {
        ostringstream sstream;
        sstream<<"Either physical bus "<<ibus<<" or "<<jbus<<" doesn't exist when getting jacobian of delta P over bus angle.";
        show_information_with_leading_time_stamp(sstream);

        return 0.0;
    }
}

double JACOBIAN_BUILDER::get_jacobian_delta_p_over_voltage_of_physical_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    if(db->is_bus_exist(ibus) and db->is_bus_exist(jbus))
    {
        size_t ibus_internal = nw_db->get_internal_bus_number_of_physical_bus(ibus);
        size_t jbus_internal = nw_db->get_internal_bus_number_of_physical_bus(jbus);

        return get_jacobian_delta_p_over_voltage_of_internal_bus(ibus_internal, jbus_internal);
    }
    else
    {
        ostringstream sstream;
        sstream<<"Either physical bus "<<ibus<<" or "<<jbus<<" doesn't exist when getting jacobian of delta P over bus voltage.";
        show_information_with_leading_time_stamp(sstream);

        return 0.0;
    }
}

double JACOBIAN_BUILDER::get_jacobian_delta_q_over_angle_of_physical_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    if(db->is_bus_exist(ibus) and db->is_bus_exist(jbus))
    {
        size_t ibus_internal = nw_db->get_internal_bus_number_of_physical_bus(ibus);
        size_t jbus_internal = nw_db->get_internal_bus_number_of_physical_bus(jbus);

        return get_jacobian_delta_q_over_angle_of_internal_bus(ibus_internal, jbus_internal);
    }
    else
    {
        ostringstream sstream;
        sstream<<"Either physical bus "<<ibus<<" or "<<jbus<<" doesn't exist when getting jacobian of delta Q over bus angle.";
        show_information_with_leading_time_stamp(sstream);

        return 0.0;
    }
}

double JACOBIAN_BUILDER::get_jacobian_delta_q_over_voltage_of_physical_bus(size_t ibus, size_t jbus)
{
    if(not is_network_database_set())
        return 0.0;

    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    if(db->is_bus_exist(ibus) and db->is_bus_exist(jbus))
    {
        size_t ibus_internal = nw_db->get_internal_bus_number_of_physical_bus(ibus);
        size_t jbus_internal = nw_db->get_internal_bus_number_of_physical_bus(jbus);

        return get_jacobian_delta_q_over_voltage_of_internal_bus(ibus_internal, jbus_internal);
    }
    else
    {
        ostringstream sstream;
        sstream<<"Either physical bus "<<ibus<<" or "<<jbus<<" doesn't exist when getting jacobian of delta Q over bus voltage.";
        show_information_with_leading_time_stamp(sstream);

        return 0.0;
    }
}

SPARSE_MATRIX& JACOBIAN_BUILDER::get_full_coupled_jacobian_with_P_and_Q_equation_internal_buses(
                                                                const vector<size_t> internal_P_equation_buses,
                                                                const vector<size_t> internal_Q_equation_buses)
{
    ostringstream sstream;
    if(not is_network_database_set())
    {
        sstream<<"Full decoupled jacobian matrix will not be returned.";
        show_information_with_leading_time_stamp(sstream);
    }

    //sstream<<"go forming the full jacobian matrix.";
    //show_information_with_leading_time_stamp(sstream);

    NETWORK_DATABASE* nw_db = get_network_database();
    const SPARSE_MATRIX& Y = nw_db->get_network_matrix();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    size_t n_internal_P_equation_buses = internal_P_equation_buses.size(),
           n_internal_Q_equation_buses = internal_Q_equation_buses.size();

    vector<bool> is_a_P_equation_bus, is_a_Q_equation_bus;
    vector<size_t> index_of_a_P_equation_bus, index_of_a_Q_equation_bus;
    size_t n = db->get_in_service_bus_count();
    is_a_P_equation_bus.reserve(n);
    is_a_Q_equation_bus.reserve(n);
    index_of_a_P_equation_bus.reserve(n);
    index_of_a_Q_equation_bus.reserve(n);
    for(size_t i=0; i!=n; ++i)
    {
        is_a_P_equation_bus.push_back(false);
        is_a_Q_equation_bus.push_back(false);
        index_of_a_P_equation_bus.push_back(INDEX_NOT_EXIST);
        index_of_a_Q_equation_bus.push_back(INDEX_NOT_EXIST);
    }
    size_t bus;
    for(size_t i=0; i!=n_internal_P_equation_buses; ++i)
    {
        bus = internal_P_equation_buses[i];
        is_a_P_equation_bus[bus] = true;
        index_of_a_P_equation_bus[bus] = i;
    }
    for(size_t i=0; i!=n_internal_Q_equation_buses; ++i)
    {
        bus = internal_Q_equation_buses[i];
        is_a_Q_equation_bus[bus] = true;
        index_of_a_Q_equation_bus[bus] = i;
    }


    static SPARSE_MATRIX full_jacobian;

    full_jacobian.clear();

    complex<double> cvalue;
    double rvalue;
    size_t ibus, jbus;

    size_t i,j;

    int nentry = Y.get_matrix_entry_count();

    for(int k=0; k!=nentry; ++k)
    {
        ibus = Y.get_row_number_of_entry_index(k);
        jbus = Y.get_column_number_of_entry_index(k);
        if(is_a_P_equation_bus[ibus])
        {
            i = index_of_a_P_equation_bus[ibus];
            if(is_a_P_equation_bus[jbus])
            {
                j = index_of_a_P_equation_bus[jbus];
                cvalue = jacobian_delta_p_over_angle.get_entry_value(ibus,jbus);
                rvalue = cvalue.real();
                full_jacobian.add_entry(i,j,rvalue);
            }
            if(is_a_Q_equation_bus[jbus])
            {
                j = index_of_a_Q_equation_bus[jbus];
                cvalue = jacobian_delta_p_over_voltage.get_entry_value(ibus,jbus);
                rvalue = cvalue.real();
                full_jacobian.add_entry(i,j+n_internal_P_equation_buses,rvalue);
            }
        }
        if(is_a_Q_equation_bus[ibus])
        {
            i = index_of_a_Q_equation_bus[ibus];
            if(is_a_P_equation_bus[jbus])
            {
                j = index_of_a_P_equation_bus[jbus];
                cvalue = jacobian_delta_q_over_angle.get_entry_value(ibus,jbus);
                rvalue = cvalue.real();
                full_jacobian.add_entry(i+n_internal_P_equation_buses,j,rvalue);
            }
            if(is_a_Q_equation_bus[jbus])
            {
                j = index_of_a_Q_equation_bus[jbus];
                cvalue = jacobian_delta_q_over_voltage.get_entry_value(ibus,jbus);
                rvalue = cvalue.real();
                full_jacobian.add_entry(i+n_internal_P_equation_buses,j+n_internal_P_equation_buses,rvalue);
            }
        }
    }

    full_jacobian.compress_and_merge_duplicate_entries();

    //sstream<<"done forming the full jacobian matrix.\nnow returning the matrix.";
    //show_information_with_leading_time_stamp(sstream);
    return full_jacobian;

    /*
    size_t n_internal_P_equation_buses = internal_P_equation_buses.size(),
           n_internal_Q_equation_buses = internal_Q_equation_buses.size();
    size_t row, col;
    complex<double>cvalue;
    double rvalue;

    static SPARSE_MATRIX full_jacobian;

    full_jacobian.clear();

    for(size_t i=0; i!=n_internal_P_equation_buses; ++i)
    {
        row = internal_P_equation_buses[i];
        for(size_t j=0; j!=n_internal_P_equation_buses; ++j)
        {
            col = internal_P_equation_buses[j];
            cvalue = jacobian_delta_p_over_angle.get_entry_value(row,col);
            rvalue = cvalue.real();
            if(rvalue != 0.0)
                full_jacobian.add_entry(i,j,rvalue);
        }
    }

    for(size_t i=0; i!=n_internal_P_equation_buses; ++i)
    {
        row = internal_P_equation_buses[i];
        for(size_t j=0; j!=n_internal_Q_equation_buses; ++j)
        {
            col = internal_Q_equation_buses[j];
            cvalue = jacobian_delta_p_over_voltage.get_entry_value(row,col);
            rvalue = cvalue.real();
            if(rvalue != 0.0)
                full_jacobian.add_entry(i,j+n_internal_P_equation_buses,rvalue);
        }
    }

    for(size_t i=0; i!=n_internal_Q_equation_buses; ++i)
    {
        row = internal_Q_equation_buses[i];
        for(size_t j=0; j!=n_internal_P_equation_buses; ++j)
        {
            col = internal_P_equation_buses[j];
            cvalue = jacobian_delta_q_over_angle.get_entry_value(row,col);
            rvalue = cvalue.real();
            if(rvalue != 0.0)
                full_jacobian.add_entry(i+n_internal_P_equation_buses,j,rvalue);
        }
    }

    for(size_t i=0; i!=n_internal_Q_equation_buses; ++i)
    {
        row = internal_Q_equation_buses[i];
        for(size_t j=0; j!=n_internal_Q_equation_buses; ++j)
        {
            col = internal_Q_equation_buses[j];
            cvalue = jacobian_delta_q_over_voltage.get_entry_value(row,col);
            rvalue = cvalue.real();
            if(rvalue != 0.0)
                full_jacobian.add_entry(i+n_internal_P_equation_buses,j+n_internal_P_equation_buses,rvalue);
        }
    }
    full_jacobian.compress_and_merge_duplicate_entries();
    return full_jacobian;
    */
}

SPARSE_MATRIX& JACOBIAN_BUILDER::get_decoupled_B_jacobian_with_P_equation_internal_buses(const vector<size_t> internal_P_equation_buses)
{
    ostringstream sstream;
    if(not is_network_database_set())
    {
        sstream<<"Decoupled BP matrix will not be returned.";
        show_information_with_leading_time_stamp(sstream);
    }

    sstream<<"Building BP matrix for active power solution.";
    show_information_with_leading_time_stamp(sstream);

    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    const SPARSE_MATRIX& BP = nw_db->get_decoupled_network_BP_matrix();

    size_t n_internal_P_equation_buses = internal_P_equation_buses.size();

    vector<bool> is_a_P_equation_bus;
    vector<size_t> index_of_a_P_equation_bus;
    size_t n = db->get_in_service_bus_count();
    is_a_P_equation_bus.reserve(n);
    index_of_a_P_equation_bus.reserve(n);
    for(size_t i=0; i!=n; ++i)
    {
        is_a_P_equation_bus.push_back(false);
        index_of_a_P_equation_bus.push_back(INDEX_NOT_EXIST);
    }
    size_t bus;
    for(size_t i=0; i!=n_internal_P_equation_buses; ++i)
    {
        bus = internal_P_equation_buses[i];
        is_a_P_equation_bus[bus] = true;
        index_of_a_P_equation_bus[bus] = i;
    }


    static SPARSE_MATRIX B_jacobian;

    B_jacobian.clear();

    complex<double> cvalue;
    double rvalue;
    size_t ibus, jbus;

    size_t i,j;

    int nentry = BP.get_matrix_entry_count();

    for(int k=0; k!=nentry; ++k)
    {
        ibus = BP.get_row_number_of_entry_index(k);
        jbus = BP.get_column_number_of_entry_index(k);
        if(is_a_P_equation_bus[ibus] and is_a_P_equation_bus[jbus])
        {
            i = index_of_a_P_equation_bus[ibus];
            j = index_of_a_P_equation_bus[jbus];
            cvalue = BP.get_entry_value(ibus,jbus);
            rvalue = cvalue.imag();
            B_jacobian.add_entry(i,j,rvalue);
        }
    }

    B_jacobian.compress_and_merge_duplicate_entries();

    sstream<<"Done building BP matrix for active power solution.";
    show_information_with_leading_time_stamp(sstream);

    return B_jacobian;
}

SPARSE_MATRIX& JACOBIAN_BUILDER::get_decoupled_B_jacobian_with_Q_equation_internal_buses(const vector<size_t> internal_Q_equation_buses)
{
    ostringstream sstream;
    if(not is_network_database_set())
    {
        sstream<<"Decoupled BQ matrix will not be returned.";
        show_information_with_leading_time_stamp(sstream);
    }

    sstream<<"Building BQ matrix for active power solution.";
    show_information_with_leading_time_stamp(sstream);

    NETWORK_DATABASE* nw_db = get_network_database();
    POWER_SYSTEM_DATABASE* db = nw_db->get_power_system_database();

    const SPARSE_MATRIX& BQ = nw_db->get_decoupled_network_BQ_matrix();

    size_t n_internal_Q_equation_buses = internal_Q_equation_buses.size();

    vector<bool> is_a_Q_equation_bus;
    vector<size_t> index_of_a_Q_equation_bus;
    size_t n = db->get_in_service_bus_count();
    is_a_Q_equation_bus.reserve(n);
    index_of_a_Q_equation_bus.reserve(n);
    for(size_t i=0; i!=n; ++i)
    {
        is_a_Q_equation_bus.push_back(false);
        index_of_a_Q_equation_bus.push_back(INDEX_NOT_EXIST);
    }
    size_t bus;
    for(size_t i=0; i!=n_internal_Q_equation_buses; ++i)
    {
        bus = internal_Q_equation_buses[i];
        is_a_Q_equation_bus[bus] = true;
        index_of_a_Q_equation_bus[bus] = i;
    }


    static SPARSE_MATRIX B_jacobian;

    B_jacobian.clear();

    complex<double> cvalue;
    double rvalue;
    size_t ibus, jbus;

    size_t i,j;

    int nentry = BQ.get_matrix_entry_count();

    for(int k=0; k!=nentry; ++k)
    {
        ibus = BQ.get_row_number_of_entry_index(k);
        jbus = BQ.get_column_number_of_entry_index(k);
        if(is_a_Q_equation_bus[ibus] and is_a_Q_equation_bus[jbus])
        {
            i = index_of_a_Q_equation_bus[ibus];
            j = index_of_a_Q_equation_bus[jbus];
            cvalue = BQ.get_entry_value(ibus,jbus);
            rvalue = cvalue.imag();
            B_jacobian.add_entry(i,j,rvalue);
        }
    }

    B_jacobian.compress_and_merge_duplicate_entries();


    sstream<<"Done building BP matrix for active power solution.";
    show_information_with_leading_time_stamp(sstream);

    return B_jacobian;
}

void JACOBIAN_BUILDER::show_seprate_jacobians()
{
    if(not is_network_database_set())
        return;

    NETWORK_DATABASE* nw_db = get_network_database();

    size_t MAX_ENTRIES_TO_SHOW = 50;

    ostringstream sstream;
    int row, col;
    size_t row_bus, col_bus;
    complex<double> cvalue;
    double rvalue;

    int nentry = jacobian_delta_p_over_angle.get_matrix_entry_count();
    size_t entries_to_show = MAX_ENTRIES_TO_SHOW;
    if(entries_to_show > size_t(nentry))
        entries_to_show = size_t(nentry);
    if(entries_to_show == 1)
        entries_to_show = 0;

    sstream<<"The first "<<entries_to_show<<" JACOBIAN_BUILDER entries of P over angle are:"<<endl
      <<"row      row_bus  column   col_bus  value";
    show_information_with_leading_time_stamp(sstream);

    for(size_t k=0; k!=entries_to_show; ++k)
    {
        row = jacobian_delta_p_over_angle.get_row_number_of_entry_index(k);
        col = jacobian_delta_p_over_angle.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_p_over_angle.get_entry_value(k);
        rvalue = cvalue.real();

        sstream<<setw(8)<<row<<" "
          <<setw(8)<<row_bus<<" "
          <<setw(8)<<col<<" "
          <<setw(8)<<col_bus<<" "
          <<setw(10)<<setprecision(6)<<fixed<<rvalue;
        show_information_with_leading_time_stamp(sstream);
    }

    nentry = jacobian_delta_p_over_voltage.get_matrix_entry_count();
    entries_to_show = MAX_ENTRIES_TO_SHOW;
    if(entries_to_show > size_t(nentry))
        entries_to_show = size_t(nentry);
    if(entries_to_show == 1)
        entries_to_show = 0;

    sstream<<"The first "<<entries_to_show<<" JACOBIAN_BUILDER entries of P over voltage are:"<<endl
      <<"row      row_bus  column   col_bus  value";
    show_information_with_leading_time_stamp(sstream);

    for(size_t k=0; k!=entries_to_show; ++k)
    {
        row = jacobian_delta_p_over_voltage.get_row_number_of_entry_index(k);
        col = jacobian_delta_p_over_voltage.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_p_over_voltage.get_entry_value(k);
        rvalue = cvalue.real();

        sstream<<setw(8)<<row<<" "
          <<setw(8)<<row_bus<<" "
          <<setw(8)<<col<<" "
          <<setw(8)<<col_bus<<" "
          <<setw(10)<<setprecision(6)<<fixed<<rvalue;
        show_information_with_leading_time_stamp(sstream);
    }

    nentry = jacobian_delta_q_over_angle.get_matrix_entry_count();
    entries_to_show = MAX_ENTRIES_TO_SHOW;
    if(entries_to_show > size_t(nentry))
        entries_to_show = size_t(nentry);
    if(entries_to_show == 1)
        entries_to_show = 0;

    sstream<<"The first "<<entries_to_show<<" JACOBIAN_BUILDER entries of Q over angle are:"<<endl
      <<"row      row_bus  column   col_bus  value";
    show_information_with_leading_time_stamp(sstream);

    for(size_t k=0; k!=entries_to_show; ++k)
    {
        row = jacobian_delta_q_over_angle.get_row_number_of_entry_index(k);
        col = jacobian_delta_q_over_angle.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_q_over_angle.get_entry_value(k);
        rvalue = cvalue.real();

        sstream<<setw(8)<<row<<" "
          <<setw(8)<<row_bus<<" "
          <<setw(8)<<col<<" "
          <<setw(8)<<col_bus<<" "
          <<setw(10)<<setprecision(6)<<fixed<<rvalue;
        show_information_with_leading_time_stamp(sstream);
    }

    nentry = jacobian_delta_q_over_voltage.get_matrix_entry_count();
    entries_to_show = MAX_ENTRIES_TO_SHOW;
    if(entries_to_show > size_t(nentry))
        entries_to_show = size_t(nentry);
    if(entries_to_show == 1)
        entries_to_show = 0;

    sstream<<"The first "<<entries_to_show<<" JACOBIAN_BUILDER entries of Q over voltage are:"<<endl
      <<"row      row_bus  column   col_bus  value";
    show_information_with_leading_time_stamp(sstream);

    for(size_t k=0; k!=entries_to_show; ++k)
    {
        row = jacobian_delta_q_over_voltage.get_row_number_of_entry_index(k);
        col = jacobian_delta_q_over_voltage.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_q_over_voltage.get_entry_value(k);
        rvalue = cvalue.real();

        sstream<<setw(8)<<row<<" "
          <<setw(8)<<row_bus<<" "
          <<setw(8)<<col<<" "
          <<setw(8)<<col_bus<<" "
          <<setw(10)<<setprecision(6)<<fixed<<rvalue;
        show_information_with_leading_time_stamp(sstream);
    }
}

void JACOBIAN_BUILDER::save_jacobian_matrix_to_file(string filename) const
{
    if(not is_network_database_set())
        return;

    ofstream file;
    ostringstream sstream;

    file.open(filename);
    if(not file.is_open())
    {
        sstream<<"File '"<<filename<<"' cannot be opened for saving jacobian matrix."<<endl
          <<"No jacobian matrix will be exported.";
        show_information_with_leading_time_stamp(sstream);
        return;
    }

    file<<"ROW_TYPE,COLUMN_TYPE,ROW,ROW_BUS,COLUMN,COLUMN_BUS,VALUE"<<endl;

    NETWORK_DATABASE* nw_db = get_network_database();

    int row, col;
    size_t row_bus, col_bus;
    complex<double> cvalue;
    double rvalue;

    int nentry = jacobian_delta_p_over_angle.get_matrix_entry_count();
    for(size_t k=0; k!=nentry; ++k)
    {
        row = jacobian_delta_p_over_angle.get_row_number_of_entry_index(k);
        col = jacobian_delta_p_over_angle.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_p_over_angle.get_entry_value(k);
        rvalue = cvalue.real();

        file<<"P,A,"<<row<<","<<row_bus<<","<<col<<","<<col_bus<<","
            <<setprecision(6)<<fixed<<rvalue<<endl;
    }

    nentry = jacobian_delta_p_over_voltage.get_matrix_entry_count();
    for(size_t k=0; k!=nentry; ++k)
    {
        row = jacobian_delta_p_over_voltage.get_row_number_of_entry_index(k);
        col = jacobian_delta_p_over_voltage.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_p_over_voltage.get_entry_value(k);
        rvalue = cvalue.real();

        file<<"P,V,"<<row<<","<<row_bus<<","<<col<<","<<col_bus<<","
            <<setprecision(6)<<fixed<<rvalue<<endl;
    }

    nentry = jacobian_delta_q_over_angle.get_matrix_entry_count();
    for(size_t k=0; k!=nentry; ++k)
    {
        row = jacobian_delta_q_over_angle.get_row_number_of_entry_index(k);
        col = jacobian_delta_q_over_angle.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_q_over_angle.get_entry_value(k);
        rvalue = cvalue.real();

        file<<"Q,A,"<<row<<","<<row_bus<<","<<col<<","<<col_bus<<","
            <<setprecision(6)<<fixed<<rvalue<<endl;
    }

    nentry = jacobian_delta_q_over_voltage.get_matrix_entry_count();
    for(size_t k=0; k!=nentry; ++k)
    {
        row = jacobian_delta_q_over_voltage.get_row_number_of_entry_index(k);
        col = jacobian_delta_q_over_voltage.get_column_number_of_entry_index(k);

        row_bus = nw_db->get_physical_bus_number_of_internal_bus(row);
        col_bus = nw_db->get_physical_bus_number_of_internal_bus(col);

        cvalue = jacobian_delta_q_over_voltage.get_entry_value(k);
        rvalue = cvalue.real();

        file<<"Q,V,"<<row<<","<<row_bus<<","<<col<<","<<col_bus<<","
            <<setprecision(6)<<fixed<<rvalue<<endl;
    }
    file.close();
}
