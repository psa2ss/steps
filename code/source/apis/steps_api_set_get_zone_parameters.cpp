#include "header/apis/steps_api.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include "header/data_imexporter/psse_imexporter.h"
#include "header/data_imexporter/bpa_imexporter.h"


int api_get_zone_integer_data(size_t zone, char* parameter_name)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);
        if(PARAMETER_NAME=="ZONE" or PARAMETER_NAME=="ZONE NUMBER")
            return zoneptr->get_zone_number();

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
        return 0;
    }
    else
    {
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
        return 0;
    }
}

void api_set_zone_integer_data(size_t zone, char* parameter_name, int value)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);
        if(PARAMETER_NAME=="ZONE" or PARAMETER_NAME=="ZONE NUMBER")
            return zoneptr->set_zone_number(value);

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
    }
    else
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
}


double api_get_zone_float_data(size_t zone, char* parameter_name)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
        return 0.0;
    }
    else
    {
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
        return 0.0;
    }
}

void api_set_zone_float_data(size_t zone, char* parameter_name, double value)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
    }
    else
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
}

const char* api_get_zone_string_data(size_t zone, char* parameter_name)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    string BLANK = "";
    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);
        if(PARAMETER_NAME=="NAME" or PARAMETER_NAME=="ZONE NAME")
            return zoneptr->get_zone_name().c_str();

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
        return BLANK.c_str();
    }
    else
    {
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
        return BLANK.c_str();
    }
}


void api_set_zone_string_data(size_t zone, char* parameter_name, char* value)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    string BLANK = "";
    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);
        if(PARAMETER_NAME=="NAME" or PARAMETER_NAME=="ZONE NAME")
            return zoneptr->set_zone_name(value);

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
    }
    else
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
}

bool api_get_zone_boolean_data(size_t zone, char* parameter_name)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
        return false;
    }
    else
    {
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
        return false;
    }
}


void api_set_zone_boolean_data(size_t zone, char* parameter_name, bool value)
{
    POWER_SYSTEM_DATABASE* psdb = api_get_default_power_system_database();

    ZONE* zoneptr = psdb->get_zone(zone);
    if(zoneptr!=NULL)
    {
        string PARAMETER_NAME = string2upper(parameter_name);

        show_parameter_not_supported_for_area_zone_owner_with_api(PARAMETER_NAME, zone, __FUNCTION__);
        return;
    }
    else
    {
        show_area_zone_owner_not_exist_with_api(zone, __FUNCTION__);
        return;
    }
}
