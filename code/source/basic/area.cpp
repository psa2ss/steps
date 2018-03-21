#include "header/basic/area.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"

#include <iostream>
#include <cstdio>

using namespace std;

AREA::AREA(POWER_SYSTEM_DATABASE* psdb)
{
    set_power_system_database(psdb);
    clear();
}

AREA::~AREA()
{
    clear();
}

void AREA::set_area_number(size_t number)
{
    if(number!=0)
        this->area_number = number;
    else
    {
        ostringstream sstream;
        string info("Error. 0 is not allowed for setting area number.  0 will be set to indicate invalid area.");
        show_information_with_leading_time_stamp(sstream);
        this->area_number = 0;
    }
}

void AREA::set_area_name(string name)
{
    this->area_name = trim_string(name);
}

void AREA::set_area_swing_bus(size_t bus)
{
    if(bus==0)
    {
        set_area_swing_bus_with_zero_input();
        return;
    }

    ostringstream sstream;
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    if(psdb==NULL)
    {
        sstream<<"Area "<<get_area_number()<<" is not assigned to any power system database."<<endl
          <<"Its area swing bus will be set as input.";
        show_information_with_leading_time_stamp(sstream);

        area_swing_bus = bus;
        return;
    }

    if(psdb->is_bus_exist(bus))
        set_area_swing_bus_with_existing_bus(bus);
    else
    {
        sstream<<"Error. Bus "<<bus<<" does not exist in power system database "<<psdb->get_system_name()<<" when setting area swing bus number of area "<<get_area_number()<<"."<<endl
          <<"Bus 0 will be set to indicate invalid area.";
        show_information_with_leading_time_stamp(sstream);

        area_swing_bus = 0;
    }
}

void AREA::set_area_swing_bus_with_zero_input()
{
    ostringstream sstream;
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    if(psdb==NULL)
    {
        sstream<<"Area "<<get_area_number()<<" is not assigned to any power system database."<<endl
          <<"Bus 0 will be set as area swing bus to indicate invalid area.";
        show_information_with_leading_time_stamp(sstream);
        area_swing_bus = 0;
        return;
    }

    bool found_slack_bus_in_this_area = false;

    vector<BUS*> buses = psdb->get_all_buses();
    size_t n = buses.size();
    for(size_t i=0; i!=n; ++i)
    {
        if(buses[i]->get_bus_type() == SLACK_TYPE and buses[i]->get_area_number()==get_area_number())
        {
            area_swing_bus = buses[i]->get_bus_number();
            found_slack_bus_in_this_area = true;
            break;
        }
    }
    if(not found_slack_bus_in_this_area)
    {
        sstream<<"Warning. Bus 0 is given for setting area swing bus, however no swing bus is found in area "<<get_area_number()<<"."<<endl
          <<"Bus 0 will be set as area swing bus to indicate area without swing bus.";
        show_information_with_leading_time_stamp(sstream);
        area_swing_bus = 0;
    }
}

void AREA::set_area_swing_bus_with_existing_bus(size_t bus)
{
    ostringstream sstream;
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();

    BUS* busptr = psdb->get_bus(bus);

    BUS_TYPE bus_type = busptr->get_bus_type();

    size_t bus_area_number = busptr->get_area_number();

    if((bus_type == PV_TYPE or bus_type == SLACK_TYPE) and bus_area_number == get_area_number())
        area_swing_bus = bus;
    else
    {
        if(bus_type != PV_TYPE and bus_type != SLACK_TYPE)
        {
            sstream<<"Error. Existing bus "<<bus<<" is given to set up area swing bus number of area "<<get_area_number()<<" in power system database "<<psdb->get_system_name()<<"."<<endl
              <<"However, bus "<<bus<<" is of neither PV type nor SLACK type. It is actually of type "<<(bus_type==PQ_TYPE?"PQ_TYPE":"OUT_OF_SERVICE");
            show_information_with_leading_time_stamp(sstream);
        }
        if(bus_area_number != get_area_number())
        {
            sstream<<"Error. Existing bus "<<bus<<" is given to set up area swing bus number of area "<<get_area_number()<<" in power system database "<<psdb->get_system_name()<<"."<<endl
              <<"However, bus "<<bus<<" is actually in area "<<bus_area_number;
            show_information_with_leading_time_stamp(sstream);
        }
        area_swing_bus = 0;
    }
}

void AREA::set_expected_power_leaving_area_in_MW(double P)
{
    this->expected_power_leaving_area_in_MW = P;
}

void AREA::set_area_power_mismatch_tolerance_in_MW(double P)
{
    if(P>0.0)
        this->area_power_mismatch_tolerance_in_MW = P;
    else
    {
        ostringstream sstream;
        sstream<<"Warning. Non-positive area power mismatch tolerance ("<<P<<" MW) is not allowed for setting up area "<<get_area_number()<<"."<<endl
          <<"10.0MW will be set automatically.";
        show_information_with_leading_time_stamp(sstream);
        this->area_power_mismatch_tolerance_in_MW = 10.0;
    }
}

size_t AREA::get_area_number() const
{
    return area_number;
}

string AREA::get_area_name() const
{
    return area_name;
}

size_t AREA::get_area_swing_bus() const
{
    return area_swing_bus;
}

double AREA::get_expected_power_leaving_area_in_MW() const
{
    return expected_power_leaving_area_in_MW;
}

double AREA::get_area_power_mismatch_tolerance_in_MW() const
{
    return area_power_mismatch_tolerance_in_MW;
}


bool AREA::is_valid() const
{
    if(get_area_number()>0 and get_area_swing_bus()>=0)
        return true;
    else
        return false;
}

void AREA::check()
{
    ;
}

void AREA::clear()
{
    area_number = 0;
    set_area_name("");
    area_swing_bus = 0;
    set_expected_power_leaving_area_in_MW(0.0);
    set_area_power_mismatch_tolerance_in_MW(10.0);
}

void AREA::report() const
{
    ostringstream sstream;

    size_t bus = get_area_swing_bus();
    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    string busname = "";
    BUS* busptr = psdb->get_bus(bus);
    if(busptr==NULL)
        busname = "NO SUCH BUS";
    else
        busname = busptr->get_bus_name();

    sstream<<"Area "<<get_area_number()<<" ("<<get_area_name()<<"): Expected leaving power = "
      <<setprecision(2)<<fixed<<get_expected_power_leaving_area_in_MW()<<" MW, tolerance = "
      <<setprecision(2)<<fixed<<get_area_power_mismatch_tolerance_in_MW()<<" MW, swing bus = "
      <<get_area_swing_bus()<<" ("<<busname<<").";
    show_information_with_leading_time_stamp(sstream);
}

AREA& AREA::operator=(const AREA& area)
{
    if(this==(&area)) return *this;

    set_power_system_database(area.get_power_system_database());

    if(area.get_area_number()!=0)
        set_area_number(area.get_area_number());

    set_area_name(area.get_area_name());

    if(area.get_area_swing_bus()!=0)
        set_area_swing_bus(area.get_area_swing_bus());

    set_expected_power_leaving_area_in_MW(area.get_expected_power_leaving_area_in_MW());
    set_area_power_mismatch_tolerance_in_MW(area.get_area_power_mismatch_tolerance_in_MW());

    return *this;
}
