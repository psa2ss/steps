#include "header/meter/meter.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include <map>
#include <vector>
#include <iostream>


using namespace std;

vector<string> bus_meters{  "BUS VOLTAGE IN PU",             "BUS VOLTAGE IN KV",
                            "BUS ANGLE IN DEG",              "BUS ANGLE IN RAD",
                            "BUS FREQUENCY IN PU",           "BUS FREQUENCY IN HZ",
                            "BUS FREQUENCY DEVIATION IN PU", "BUS FREQUENCY DEVIATION IN HZ",
                            "BUS ROCOV IN PU/S",             "BUS ROCOV IN KV/S",
                            "BUS ROCOF IN PU/S",             "BUS ROCOF IN HZ/S"};


vector<string> line_meters{ "LINE CURRENT AT SENDING SIDE IN KA",                    "LINE CURRENT AT RECEIVING SIDE IN KA",
                            "LINE ACTIVE POWER AT SENDING SIDE IN MW",               "LINE ACTIVE POWER AT RECEIVING SIDE IN MW",
                            "LINE REACTIVE POWER AT SENDING SIDE IN MVAR",           "LINE REACTIVE POWER AT RECEIVING SIDE IN MVAR",
                            "LINE APPARENT IMPEDANCE AT SENDING SIDE IN OHM",        "LINE APPARENT IMPEDANCE AT RECEIVING SIDE IN OHM",
                            "LINE APPARENT IMPEDANCE ANGLE AT SENDING SIDE IN DEG",  "LINE APPARENT IMPEDANCE ANGLE AT RECEIVING SIDE IN DEG",
                            "LINE CURRENT IN KA",
                            "LINE ACTIVE POWER IN MW",
                            "LINE REACTIVE POWER IN MVAR",
                            "LINE APPARENT IMPEDANCE IN OHM",
                            "LINE APPARENT IMPEDANCE ANGLE IN DEG",
                            "LINE CURRENT IN PU",
                            "LINE ACTIVE POWER IN PU",
                            "LINE REACTIVE POWER IN PU",
                            "LINE APPARENT IMPEDANCE IN PU",
                            "LINE APPARENT IMPEDANCE ANGLE IN RAD"};


vector<string> transformer_meters{ "TRANSFORMER CURRENT AT PRIMARY WINDING IN KA",  "TRANSFORMER CURRENT AT SECONDARY WINDING IN KA",
                                   "TRANSFORMER CURRENT AT TERTIARY WINDING IN KA",
                                   "TRANSFORMER ACTIVE POWER AT PRIMARY WINDING IN MW",    "TRANSFORMER ACTIVE POWER AT SECONDARY WINDING IN MW",
                                   "TRANSFORMER ACTIVE POWER AT TERTIARY WINDING IN MW",
                                   "TRANSFORMER REACTIVE POWER AT PRIMARY WINDING IN MVAR", "TRANSFORMER REACTIVE POWER AT SECONDARY WINDING IN MVAR",
                                   "TRANSFORMER REACTIVE POWER AT TERTIARY WINDING IN MVAR",
                                   "TRANSFORMER CURRENT IN KA",
                                   "TRANSFORMER ACTIVE POWER IN MW",
                                   "TRANSFORMER REACTIVE POWER IN MVAR",
                                   "TRANSFORMER CURRENT IN PU",
                                   "TRANSFORMER ACTIVE POWER IN PU",
                                   "TRANSFORMER REACTIVE POWER IN PU"};


vector<string> load_meters{ "LOAD CURRENT IN KA",
                            "LOAD CURRENT IN PU",
                            "LOAD ACTIVE POWER IN MW", "LOAD REACTIVE POWER IN MVAR",
                            "LOAD ACTIVE POWER IN PU", "LOAD REACTIVE POWER IN PU",
                            "LOAD LOAD MODEL INTERNAL VARIABLE",
                            "LOAD FREQUENCY RELAY MODEL INTERNAL VARIABLE",
                            "LOAD VOLTAGE RELAY MODEL INTERNAL VARIABLE",
                            "LOAD SHED SCALE IN PU"};

vector<string> generator_meters{    "GENERATOR ROTOR ANGLE IN DEG",
                                    "GENERATOR ROTOR SPEED IN PU",               "GENERATOR ROTOR SPEED IN HZ",
                                    "GENERATOR ROTOR SPEED DEVIATION IN PU",     "GENERATOR ROTOR SPEED DEVIATION IN HZ",
                                    "GENERATOR INTERNAL VOLTAGE IN PU",
                                    "GENERATOR TERMINAL CURRENT IN PU ON MBASE", "GENERATOR TERMINAL CURRENT IN PU ON SBASE",
                                    "GENERATOR TERMINAL CURRENT IN KA",
                                    "GENERATOR TERMINAL ACTIVE POWER IN PU ON MBASE", "GENERATOR TERMINAL ACTIVE POWER IN PU ON SBASE",
                                    "GENERATOR TERMINAL ACTIVE POWER IN MW",
                                    "GENERATOR TERMINAL REACTIVE POWER IN PU ON MBASE", "GENERATOR TERMINAL REACTIVE POWER IN PU ON SBASE",
                                    "GENERATOR TERMINAL REACTIVE POWER IN MVAR",
                                    "GENERATOR AIRGAP POWER IN PU ON MBASE", "GENERATOR AIRGAP POWER IN PU ON SBASE",
                                    "GENERATOR AIRGAP POWER IN MW",
                                    "GENERATOR ACCELERATING POWER IN PU ON MBASE", "GENERATOR ACCELERATING POWER IN PU ON SBASE",
                                    "GENERATOR ACCELERATING POWER IN MW",
                                    "GENERATOR MECHANICAL POWER IN PU ON MBASE",  "GENERATOR MECHANICAL POWER IN PU ON SBASE",
                                    "GENERATOR MECHANICAL POWER IN MW",
                                    "GENERATOR COMPENSATED VOLTAGE IN PU",
                                    "GENERATOR STABILIZING SIGNAL IN PU",
                                    "GENERATOR EXCITATION VOLTAGE IN PU",
                                    "GENERATOR SYNC GENERATOR MODEL INTERNAL VARIABLE",
                                    "GENERATOR COMPENSATOR MODEL INTERNAL VARIABLE",
                                    "GENERATOR EXCITER MODEL INTERNAL VARIABLE",
                                    "GENERATOR STABILIZER MODEL INTERNAL VARIABLE",
                                    "GENERATOR TURBINE GOVERNOR MODEL INTERNAL VARIABLE"};

vector<string> pe_source_meters{  "PE SOURCE ROTOR SPEED DEVIATION IN PU", "PE SOURCE ROTOR SPEED DEVIATION IN HZ",
                                  "PE SOURCE ROTOR SPEED IN PU",           "PE SOURCE ROTOR SPEED IN HZ",
                                  "PE SOURCE TERMINAL CURRENT IN KA",
                                  "PE SOURCE TERMINAL ACTIVE POWER IN MW",
                                  "PE SOURCE TERMINAL REACTIVE POWER IN MVAR",
                                  "PE SOURCE MECHANICAL POWER IN MW",
                                  "WIND TURBINE PITCH ANGLE IN DEG",
                                  "PE SOURCE MODEL INTERNAL VARIABLE",
                                  "WIND TURBINE ELECTRICAL CONTROL MODEL INTERNAL VARIABLE",
                                  "WIND TURBINE MECHANICAL MODEL INTERNAL VARIABLE",
                                  "WIND TURBINE PITCH CONTROL MODEL INTERNAL VARIABLE"};

vector<string> hvdc_meters{ "HVDC DC CURRENT IN KA",
                            "HVDC RECTIFIER DC CURRENT IN KA",   "HVDC INVERTER DC CURRENT IN KA",
                            "HVDC RECTIFIER AC CURRENT IN KA",   "HVDC INVERTER AC CURRENT IN KA",
                            "HVDC RECTIFIER ALPHA IN DEG",       "HVDC INVERTER GAMMA IN DEG",
                            "HVDC RECTIFIER MU IN DEG",          "HVDC INVERTER MU IN DEG",
                            "HVDC RECTIFIER DC VOLTAGE IN KV",   "HVDC INVERTER DC VOLTAGE IN KV",
                            "HVDC RECTIFIER AC VOLTAGE IN PU",   "HVDC INVERTER AC VOLTAGE IN PU",
                            "HVDC RECTIFIER DC POWER IN MW",     "HVDC INVERTER DC POWER IN MW",
                            "HVDC RECTIFIER AC ACTIVE POWER IN MW","HVDC INVERTER AC ACTIVE POWER IN MW",
                            "HVDC RECTIFIER AC REACTIVE POWER IN MVAR","HVDC INVERTER AC REACTIVE POWER IN MVAR",
                            "HVDC MODEL INTERNAL VARIABLE"};

vector<string> equivalent_device_meters{"EQUIVALENT DEVICE VOLTAGE SOURCE VOLTAGE IN PU",
                                        "EQUIVALENT DEVICE VOLTAGE SOURCE VOLTAGE ANGLE IN DEG",
                                        "EQUIVALENT DEVICE VOLTAGE SOURCE RESISTANCE IN PU",
                                        "EQUIVALENT DEVICE VOLTAGE SOURCE REACTANCE IN PU",
                                        "EQUIVALENT DEVICE ACTIVE CONSTANT POWER LOAD IN MW",
                                        "EQUIVALENT DEVICE REACTIVE CONSTANT POWER LOAD IN MVAR",
                                        "EQUIVALENT DEVICE ACTIVE CONSTANT CURRENT LOAD IN MW",
                                        "EQUIVALENT DEVICE REACTIVE CONSTANT CURRENT LOAD IN MVAR",
                                        "EQUIVALENT DEVICE ACTIVE CONSTANT IMPEDANCE LOAD IN MW",
                                        "EQUIVALENT DEVICE REACTIVE CONSTANT IMPEDANCE LOAD IN MVAR",
                                        "EQUIVALENT DEVICE ACTIVE POWER GENERATION IN MW",
                                        "EQUIVALENT DEVICE REACTIVE POWER GENERATION IN MVAR",
                                        "EQUIVALENT DEVICE ACTIVE POWER LOAD IN MW",
                                        "EQUIVALENT DEVICE REACTIVE POWER LOAD IN MVAR",
                                        "EQUIVALENT DEVICE ACTIVE POWER NET LOAD IN MW",
                                        "EQUIVALENT DEVICE REACTIVE POWER NET LOAD IN MVAR",
                                        "EQUIVALENT DEVICE ACTIVE CONSTANT POWER LOAD IN PU",
                                        "EQUIVALENT DEVICE REACTIVE CONSTANT POWER LOAD IN PU",
                                        "EQUIVALENT DEVICE ACTIVE CONSTANT CURRENT LOAD IN PU",
                                        "EQUIVALENT DEVICE REACTIVE CONSTANT CURRENT LOAD IN PU",
                                        "EQUIVALENT DEVICE ACTIVE CONSTANT IMPEDANCE LOAD IN PU",
                                        "EQUIVALENT DEVICE REACTIVE CONSTANT IMPEDANCE LOAD IN PU",
                                        "EQUIVALENT DEVICE ACTIVE POWER GENERATION IN PU",
                                        "EQUIVALENT DEVICE REACTIVE POWER GENERATION IN PU",
                                        "EQUIVALENT DEVICE ACTIVE POWER LOAD IN PU",
                                        "EQUIVALENT DEVICE REACTIVE POWER LOAD IN PU",
                                        "EQUIVALENT DEVICE ACTIVE POWER NET LOAD IN PU",
                                        "EQUIVALENT DEVICE REACTIVE POWER NET LOAD IN PU"};

map<string, vector<string>> SUPPORTED_METERS{   {"BUS",         bus_meters},
                                                {"LINE",        line_meters},
                                                {"TRANSFORMER", transformer_meters},
                                                {"LOAD",        load_meters},
                                                {"GENERATOR",   generator_meters},
                                                {"PE SOURCE",    pe_source_meters},
                                                {"HVDC", hvdc_meters},
                                                {"EQUIVALENT DEVICE", equivalent_device_meters}};

METER::METER(POWER_SYSTEM_DATABASE* psdb)
{
    ostringstream sstream;
    if(psdb==NULL)
    {
        sstream<<"Error. METER object cannot be constructed since NULL power system database is given."<<endl
          <<"Operations on the object is unpredictable.";
        show_information_with_leading_time_stamp(sstream);
    }
    set_power_system_database(psdb);
    clear();
}

METER::METER()
{
    clear();
}

void METER::copy_from_const_meter(const METER& meter)
{
    clear();

    set_power_system_database(meter.get_power_system_database());
    set_buffer_size(meter.get_buffer_size());
    set_device_id(meter.get_device_id());
    set_meter_type(meter.get_meter_type(), meter.get_internal_variable_index());
    set_meter_side_bus(meter.get_meter_side_bus());

    if(meter.get_device_pointer()!=NULL)
        set_device_pointer();
}

METER::METER(const METER& meter)
{
    copy_from_const_meter(meter);
}

METER& METER::operator=(const METER& meter)
{
    if(this==&meter)
        return *this;

    copy_from_const_meter(meter);

    return *this;
}


METER::~METER()
{
    ;
}

void METER::set_device_id(const DEVICE_ID& did)
{
    if(not did.is_valid())
    {
        ostringstream sstream;
        sstream<<"Warning. Device id is invalid for setting up meter.";
        show_information_with_leading_time_stamp(sstream);
    }
    this->device_id =did;
    set_device_pointer();
}

void METER::set_meter_type(string meter_type, size_t internal_variable_index)
{
    ostringstream sstream;
    if(not device_id.is_valid())
    {
        sstream<<"Warning. Device id is invalid for setting up meter type. Set up proper device id first.";
        show_information_with_leading_time_stamp(sstream);
        return;
    }

    meter_type = string2upper(meter_type);

    if(is_valid_meter_type(meter_type))
    {
        this->meter_type = meter_type;
        if(meter_type.find("INTERNAL VARIABLE") != string::npos)
            this->internal_variable_index = internal_variable_index;
        else
            this->internal_variable_index = 0;
    }
    else
    {
        sstream<<"Warning, Invalid meter type '"<<meter_type<<"' is not supported for setting up meter type of "<<device_id.get_device_name()<<".";
        show_information_with_leading_time_stamp(sstream);
        this->meter_type = "";
    }
}
void METER::set_meter_side_bus(size_t meter_side)
{
    DEVICE* device = get_device_pointer();
    if(device->is_connected_to_bus(meter_side))
        meter_side_bus = meter_side;
    else
        meter_side_bus = 0;
}


void METER::change_device_id(DEVICE_ID did)
{
    set_device_id(did);
}

void METER::change_meter_type(string meter_type)
{
    this->meter_type = meter_type;
}

void METER::check()
{
    ;// method to disable BASE::check()
}
bool METER::is_valid_meter_type(string meter_type) const
{
    if(not device_id.is_valid())
        return false;

    string device_type = device_id.get_device_type();
    meter_type = string2upper(meter_type);

    return is_valid_meter_type_of_device(meter_type, device_type);
}

bool METER::is_valid_meter_type_of_device(string meter_type, string device_type) const
{
    ostringstream sstream;

    device_type = string2upper(device_type);
    map<string, vector<string> >::const_iterator it = SUPPORTED_METERS.find(device_type);
    if(it==SUPPORTED_METERS.end())
    {
        sstream<<"Warning. Device type "<<device_type<<" is not supported for setting up meter.";
        show_information_with_leading_time_stamp(sstream);
        return false;
    }
    else
    {
        vector<string> supported_meters = it->second;
        size_t n = supported_meters.size();
        bool flag_valid = false;
        for(size_t i=0; i!=n; ++i)
        {
            if(meter_type == supported_meters[i])
            {
                flag_valid = true;
                break;
            }
        }
        return flag_valid;
    }
}

DEVICE_ID METER::get_device_id() const
{
    return device_id;
}

string METER::get_meter_type() const
{
    return meter_type;
}

size_t METER::get_meter_side_bus() const
{
    return meter_side_bus;
}

string METER::get_device_type() const
{
    return device_id.get_device_type();
}

size_t METER::get_internal_variable_index() const
{
    return internal_variable_index;
}

DEVICE* METER::get_device_pointer() const
{
    return device_pointer;
}

string METER::get_meter_name() const
{
    string name;
    string meter_type = get_meter_type();
    if(meter_type=="")
        return "";
    else
    {
        name = get_meter_type();
        if(meter_type.find("INTERNAL VARIABLE")!=string::npos)
            name += " " + num2str(get_internal_variable_index());

        //name += " OF "+get_device_id().get_device_name()+" IN PS "+get_power_system_database()->get_system_name();
        name += " @ "+get_device_id().get_device_name();

        string device_type = get_device_type();
        if(device_type=="LINE" or device_type=="TRANSFORMER" )
            name += " @ SIDE "+num2str(get_meter_side_bus());

        name = trim_string(name);
        return name;
    }
}

bool METER::is_valid() const
{
    if(device_id.is_valid() and meter_type!="")
    {
        string device_type = device_id.get_device_type();
        if(device_type=="LINE" or device_type=="TRANSFORMER")
        {
            if(get_meter_side_bus()!=0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

void METER::clear()
{
    device_id.clear();
    device_pointer = NULL;
    meter_type = "";
    meter_side_bus = 0;
    internal_variable_index = 0;

    set_buffer_size(1);
    buffer.clear();
}


bool METER::operator==(const METER& meter)
{
    if(this->get_power_system_database()==meter.get_power_system_database() and
       this->get_device_id() == meter.get_device_id() and
       this->get_meter_type() == meter.get_meter_type())
    {
        if(this->get_meter_type().find("INTERNAL VARIABLE") == string::npos)
            return true;
        else
        {
            if(this->get_internal_variable_index() == meter.get_internal_variable_index())
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

bool METER::operator!=(const METER& meter)
{
    return not ((*this)==meter);
}

void METER::set_device_pointer()
{
    ostringstream sstream;

    if(not device_id.is_valid())
    {
        device_pointer = NULL;
        return;
    }

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();

    if(psdb==NULL)
    {
        sstream<<"No power system database is set for METER."<<endl
          <<"Device pointer will be set as NULL to disable the meter.";
        show_information_with_leading_time_stamp(sstream);
        device_pointer = NULL;
        return;
    }

    string device_type = device_id.get_device_type();
    DEVICE* deviceptr = NULL;
    if(device_type=="BUS")
    {
        TERMINAL terminal = device_id.get_device_terminal();
        vector<size_t> tbuses = terminal.get_buses();
        deviceptr = (DEVICE*) psdb->get_bus(tbuses[0]);
    }
    if(device_type=="LINE")
        deviceptr = (DEVICE*) psdb->get_line(device_id);

    if(device_type=="TRANSFORMER")
        deviceptr = (DEVICE*) psdb->get_transformer(device_id);

    if(device_type=="LOAD")
        deviceptr = (DEVICE*) psdb->get_load(device_id);

    if(device_type=="GENERATOR")
        deviceptr = (DEVICE*) psdb->get_generator(device_id);

    if(device_type=="PE SOURCE")
        deviceptr = (DEVICE*) psdb->get_pe_source(device_id);

    if(device_type=="HVDC")
        deviceptr = (DEVICE*) psdb->get_hvdc(device_id);

    if(device_type=="EQUIVALENT DEVICE")
        deviceptr = (DEVICE*) psdb->get_equivalent_device(device_id);

    this->device_pointer = deviceptr;
    if(deviceptr==NULL)
    {
        ostringstream sstream;
        sstream<<"Device cannot be found in database for setting meter. Device is "<<device_id.get_device_name();
        show_information_with_leading_time_stamp(sstream);
    }
}

void METER::set_buffer_size(size_t bsize)
{
    buffer.set_buffer_size(bsize);
}

size_t METER::get_buffer_size() const
{
    return buffer.get_buffer_size();
}

void METER::initialize_meter_buffer()
{
    if(get_device_pointer()==NULL)
        set_device_pointer();

    double current_time = get_device_pointer()->get_dynamic_simulator_time_in_s();

    double value = get_meter_value();
    buffer.initialize_buffer(current_time, value);
}

void METER::update_meter_buffer()
{
    if(get_device_pointer()==NULL)
        set_device_pointer();

    double current_time = get_device_pointer()->get_dynamic_simulator_time_in_s();

    buffer.append_data(current_time, get_meter_value());
}


double METER::get_meter_value_from_buffer_with_delay(size_t index) const
{
    return buffer.get_buffer_value_at_delay_index(index);
}

double METER::get_meter_value_from_buffer_at_time(double time) const
{
    return buffer.get_buffer_value_at_time(time);
}

size_t METER::get_delay_index_of_time(double time) const
{
    return buffer.get_delay_index_of_time(time);
}

double METER::get_meter_value() const
{
    if(get_device_pointer()==NULL)
        return 0.0;

    string device_type = get_device_type();
    if(device_type=="BUS")
        return get_meter_value_as_a_bus();
    if(device_type=="LINE")
        return get_meter_value_as_a_line();
    if(device_type=="TRANSFORMER")
        return get_meter_value_as_a_transformer();
    if(device_type=="LOAD")
        return get_meter_value_as_a_load();
    if(device_type=="GENERATOR")
        return get_meter_value_as_a_generator();
    if(device_type=="HVDC")
        return get_meter_value_as_an_hvdc();
    if(device_type=="EQUIVALENT DEVICE")
        return get_meter_value_as_an_equivalent_device();

    return 0.0;
}


double METER::get_meter_value_as_a_bus() const
{
    BUS* bus = (BUS*) get_device_pointer();
    if(bus->get_bus_type()==OUT_OF_SERVICE)
        return 0.0;

    if(meter_type=="BUS VOLTAGE IN PU")
        return bus->get_voltage_in_pu();
    if(meter_type=="BUS VOLTAGE IN KV")
        return bus->get_voltage_in_pu();
    if(meter_type=="BUS ANGLE IN DEG")
        return bus->get_angle_in_deg();
    if(meter_type=="BUS FREQUENCY DEVIATION IN PU")
        return bus->get_frequency_deviation_in_pu();
    if(meter_type=="BUS FREQUENCY DEVIATION IN HZ")
        return bus->get_frequency_deviation_in_Hz();
    if(meter_type=="BUS FREQUENCY IN PU")
        return 1.0+bus->get_frequency_deviation_in_pu();
    if(meter_type=="BUS FREQUENCY IN HZ")
        return bus->get_power_system_database()->get_system_base_frequency_in_Hz()+bus->get_frequency_deviation_in_Hz();

    return 0.0;
}

double METER::get_meter_value_as_a_line() const
{
    LINE* line = (LINE*) get_device_pointer();
    if(line == NULL)
        return 0.0;

    if(line->get_sending_side_breaker_status()==false and line->get_receiving_side_breaker_status()==false)
        return 0.0;

    size_t metered_bus = get_meter_side_bus();
    if(meter_type=="LINE CURRENT IN KA")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return abs(line->get_line_complex_current_at_sending_side_in_kA());
        else
            return abs(line->get_line_complex_current_at_receiving_side_in_kA());
    }
    if(meter_type=="LINE CURRENT IN PU")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return abs(line->get_line_complex_current_at_sending_side_in_pu());
        else
            return abs(line->get_line_complex_current_at_receiving_side_in_pu());
    }

    if(meter_type=="LINE ACTIVE POWER IN MW")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return (line->get_line_complex_power_at_sending_side_in_MVA()).real();
        else
            return (line->get_line_complex_power_at_receiving_side_in_MVA()).real();
    }

    if(meter_type=="LINE ACTIVE POWER IN PU")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return (line->get_line_complex_power_at_sending_side_in_pu()).real();
        else
            return (line->get_line_complex_power_at_receiving_side_in_pu()).real();
    }

    if(meter_type=="LINE REACTIVE POWER IN MVAR")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return (line->get_line_complex_power_at_sending_side_in_MVA()).imag();
        else
            return (line->get_line_complex_power_at_receiving_side_in_MVA()).imag();
    }

    if(meter_type=="LINE REACTIVE POWER IN PU")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return (line->get_line_complex_power_at_sending_side_in_pu()).imag();
        else
            return (line->get_line_complex_power_at_receiving_side_in_pu()).imag();
    }

    if(meter_type=="LINE APPARENT IMPEDANCE IN OHM")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return abs(line->get_line_complex_apparent_impedance_at_sending_side_in_ohm());
        else
            return abs(line->get_line_complex_apparent_impedance_at_receiving_side_in_ohm());
    }

    if(meter_type=="LINE APPARENT IMPEDANCE IN PU")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return abs(line->get_line_complex_apparent_impedance_at_sending_side_in_pu());
        else
            return abs(line->get_line_complex_apparent_impedance_at_receiving_side_in_pu());
    }

    if(meter_type=="LINE APPARENT IMPEDANCE ANGLE IN DEG")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return rad2deg(arg(line->get_line_complex_apparent_impedance_at_sending_side_in_ohm()));
        else
            return rad2deg(arg(line->get_line_complex_apparent_impedance_at_receiving_side_in_ohm()));
    }

    if(meter_type=="LINE APPARENT IMPEDANCE ANGLE IN RAD")
    {
        if(metered_bus!=line->get_receiving_side_bus())
            return arg(line->get_line_complex_apparent_impedance_at_sending_side_in_ohm());
        else
            return arg(line->get_line_complex_apparent_impedance_at_receiving_side_in_ohm());
    }


    if(meter_type=="LINE CURRENT AT SENDING SIDE IN KA")
        return abs(line->get_line_complex_current_at_sending_side_in_kA());
    if(meter_type=="LINE ACTIVE POWER AT SENDING SIDE IN MW")
        return (line->get_line_complex_power_at_sending_side_in_MVA()).real();
    if(meter_type=="LINE REACTIVE POWER AT SENDING SIDE IN MVAR")
        return (line->get_line_complex_power_at_sending_side_in_MVA()).imag();
    if(meter_type=="LINE CURRENT AT RECEIVING SIDE IN KA")
        return abs(line->get_line_complex_current_at_receiving_side_in_kA());
    if(meter_type=="LINE ACTIVE POWER AT RECEIVING SIDE IN MW")
        return (line->get_line_complex_power_at_receiving_side_in_MVA()).real();
    if(meter_type=="LINE REACTIVE POWER AT RECEIVING SIDE IN MVAR")
        return (line->get_line_complex_power_at_receiving_side_in_MVA()).imag();

    if(meter_type=="LINE APPARENT IMPEDANCE AT SENDING SIDE IN OHM")
        return abs(line->get_line_complex_apparent_impedance_at_sending_side_in_ohm());
    if(meter_type=="LINE APPARENT IMPEDANCE ANGLE AT SENDING SIDE IN DEG")
        return rad2deg(arg(line->get_line_complex_apparent_impedance_at_sending_side_in_ohm()));
    if(meter_type=="LINE APPARENT IMPEDANCE AT RECEIVING SIDE IN OHM")
        return abs(line->get_line_complex_apparent_impedance_at_receiving_side_in_ohm());
    if(meter_type=="LINE APPARENT IMPEDANCE ANGLE AT RECEIVING SIDE IN DEG")
        return rad2deg(arg(line->get_line_complex_apparent_impedance_at_receiving_side_in_ohm()));

    return 0.0;
}

double METER::get_meter_value_as_a_transformer() const
{
    TRANSFORMER* trans = (TRANSFORMER*) get_device_pointer();
    if(trans == NULL)
        return 0.0;
    size_t metered_bus = get_meter_side_bus();
    if(trans->is_two_winding_transformer())
    {
        if(meter_type=="TRANSFORMER CURRENT IN KA")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE))
                return abs(trans->get_winding_complex_current_in_kA(PRIMARY_SIDE));
            else
                return abs(trans->get_winding_complex_current_in_kA(SECONDARY_SIDE));
        }

        if(meter_type=="TRANSFORMER CURRENT IN PU")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE))
                return abs(trans->get_winding_complex_current_in_pu(PRIMARY_SIDE));
            else
                return abs(trans->get_winding_complex_current_in_pu(SECONDARY_SIDE));
        }

        if(meter_type=="TRANSFORMER ACTIVE POWER IN MW")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE))
                return (trans->get_winding_complex_power_in_MVA(PRIMARY_SIDE)).real();
            else
                return (trans->get_winding_complex_power_in_MVA(SECONDARY_SIDE)).real();
        }

        if(meter_type=="TRANSFORMER ACTIVE POWER IN PU")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE))
                return (trans->get_winding_complex_power_in_pu(PRIMARY_SIDE)).real();
            else
                return (trans->get_winding_complex_power_in_pu(SECONDARY_SIDE)).real();
        }

        if(meter_type=="TRANSFORMER REACTIVE POWER IN MVAR")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE))
                return (trans->get_winding_complex_power_in_MVA(PRIMARY_SIDE)).imag();
            else
                return (trans->get_winding_complex_power_in_MVA(SECONDARY_SIDE)).imag();
        }

        if(meter_type=="TRANSFORMER REACTIVE POWER IN PU")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE))
                return (trans->get_winding_complex_power_in_pu(PRIMARY_SIDE)).imag();
            else
                return (trans->get_winding_complex_power_in_pu(SECONDARY_SIDE)).imag();
        }
    }
    else
    {
        if(meter_type=="TRANSFORMER CURRENT IN KA")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE) and metered_bus!=trans->get_winding_bus(TERTIARY_SIDE))
                return abs(trans->get_winding_complex_current_in_kA(PRIMARY_SIDE));
            else
            {
                if(metered_bus==trans->get_winding_bus(SECONDARY_SIDE))
                    return abs(trans->get_winding_complex_current_in_kA(SECONDARY_SIDE));
                else
                    return abs(trans->get_winding_complex_current_in_kA(TERTIARY_SIDE));
            }
        }

        if(meter_type=="TRANSFORMER CURRENT IN PU")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE) and metered_bus!=trans->get_winding_bus(TERTIARY_SIDE))
                return abs(trans->get_winding_complex_current_in_pu(PRIMARY_SIDE));
            else
            {
                if(metered_bus==trans->get_winding_bus(SECONDARY_SIDE))
                    return abs(trans->get_winding_complex_current_in_pu(SECONDARY_SIDE));
                else
                    return abs(trans->get_winding_complex_current_in_pu(TERTIARY_SIDE));
            }
        }

        if(meter_type=="TRANSFORMER ACTIVE POWER IN MW")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE) and metered_bus!=trans->get_winding_bus(TERTIARY_SIDE))
                return (trans->get_winding_complex_power_in_MVA(PRIMARY_SIDE)).real();
            else
            {
                if(metered_bus==trans->get_winding_bus(SECONDARY_SIDE))
                    return (trans->get_winding_complex_power_in_MVA(SECONDARY_SIDE)).real();
                else
                    return (trans->get_winding_complex_power_in_MVA(TERTIARY_SIDE)).real();
            }
        }

        if(meter_type=="TRANSFORMER ACTIVE POWER IN PU")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE) and metered_bus!=trans->get_winding_bus(TERTIARY_SIDE))
                return (trans->get_winding_complex_power_in_pu(PRIMARY_SIDE)).real();
            else
            {
                if(metered_bus==trans->get_winding_bus(SECONDARY_SIDE))
                    return (trans->get_winding_complex_power_in_pu(SECONDARY_SIDE)).real();
                else
                    return (trans->get_winding_complex_power_in_pu(TERTIARY_SIDE)).real();
            }
        }

        if(meter_type=="TRANSFORMER REACTIVE POWER IN MVAR")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE) and metered_bus!=trans->get_winding_bus(TERTIARY_SIDE))
                return (trans->get_winding_complex_power_in_MVA(PRIMARY_SIDE)).imag();
            else
            {
                if(metered_bus==trans->get_winding_bus(SECONDARY_SIDE))
                    return (trans->get_winding_complex_power_in_MVA(SECONDARY_SIDE)).imag();
                else
                    return (trans->get_winding_complex_power_in_MVA(TERTIARY_SIDE)).imag();
            }
        }

        if(meter_type=="TRANSFORMER REACTIVE POWER IN PU")
        {
            if(metered_bus!=trans->get_winding_bus(SECONDARY_SIDE) and metered_bus!=trans->get_winding_bus(TERTIARY_SIDE))
                return (trans->get_winding_complex_power_in_pu(PRIMARY_SIDE)).imag();
            else
            {
                if(metered_bus==trans->get_winding_bus(SECONDARY_SIDE))
                    return (trans->get_winding_complex_power_in_pu(SECONDARY_SIDE)).imag();
                else
                    return (trans->get_winding_complex_power_in_pu(TERTIARY_SIDE)).imag();
            }
        }
    }



    if(meter_type=="TRANSFORMER CURRENT AT PRIMARY WINDING IN KA")
        return abs(trans->get_winding_complex_current_in_kA(PRIMARY_SIDE));
    if(meter_type=="TRANSFORMER CURRENT AT SECONDARY WINDING IN KA")
        return abs(trans->get_winding_complex_current_in_kA(SECONDARY_SIDE));
    if(meter_type=="TRANSFORMER CURRENT AT TERTIARY WINDING IN KA")
        return abs(trans->get_winding_complex_current_in_kA(TERTIARY_SIDE));
    if(meter_type=="TRANSFORMER ACTIVE POWER AT PRIMARY WINDING IN MW")
        return (trans->get_winding_complex_power_in_MVA(PRIMARY_SIDE)).real();
    if(meter_type=="TRANSFORMER ACTIVE POWER AT SECONDARY WINDING IN MW")
        return (trans->get_winding_complex_power_in_MVA(SECONDARY_SIDE)).real();
    if(meter_type=="TRANSFORMER ACTIVE POWER AT TERTIARY WINDING IN MW")
        return (trans->get_winding_complex_power_in_MVA(TERTIARY_SIDE)).real();
    if(meter_type=="TRANSFORMER REACTIVE POWER AT PRIMARY WINDING IN MVAR")
        return (trans->get_winding_complex_power_in_MVA(PRIMARY_SIDE)).imag();
    if(meter_type=="TRANSFORMER REACTIVE POWER AT SECONDARY WINDING IN MVAR")
        return (trans->get_winding_complex_power_in_MVA(SECONDARY_SIDE)).imag();
    if(meter_type=="TRANSFORMER REACTIVE POWER AT TERTIARY WINDING IN MVAR")
        return (trans->get_winding_complex_power_in_MVA(TERTIARY_SIDE)).imag();

    return 0.0;
}

double METER::get_meter_value_as_a_load() const
{
    LOAD* load = (LOAD*) get_device_pointer();
    if(load==NULL)
        return 0.0;
    if(load->get_status()==false)
        return 0.0;

    if(meter_type=="LOAD ACTIVE POWER IN MW")
        return (load->get_dynamic_load_in_MVA()).real();

    if(meter_type=="LOAD ACTIVE POWER IN PU")
        return (load->get_dynamic_load_in_pu()).real();

    if(meter_type=="LOAD REACTIVE POWER IN MVAR")
        return (load->get_dynamic_load_in_MVA()).imag();

    if(meter_type=="LOAD REACTIVE POWER IN PU")
        return (load->get_dynamic_load_in_pu()).imag();

    if(meter_type=="LOAD CURRENT IN KA")
    {
        POWER_SYSTEM_DATABASE* psdb = load->get_power_system_database();
        double sbase = psdb->get_system_base_power_in_MVA();
        double vbase = psdb->get_bus_base_voltage_in_kV(load->get_load_bus());
        double ibase = sbase/(sqrt(3.0)*vbase);
        return ibase*abs(load->get_dynamics_load_current_in_pu_based_on_system_base_power());
    }


    if(meter_type=="LOAD CURRENT IN PU")
    {
        return abs(load->get_dynamics_load_current_in_pu_based_on_system_base_power());
    }

    if(meter_type=="LOAD LOAD MODEL INTERNAL VARIABLE")
    {
        LOAD_MODEL* model = load->get_load_model();
        if(model==NULL)
            return 0.0;
        else
            return model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="LOAD FREQUENCY RELAY MODEL INTERNAL VARIABLE")
    {
        LOAD_FREQUENCY_RELAY_MODEL* model = load->get_load_frequency_relay_model();
        if(model==NULL)
            return 0.0;
        else
            return model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="LOAD VOLTAGE RELAY MODEL INTERNAL VARIABLE")
    {
        LOAD_VOLTAGE_RELAY_MODEL* model = load->get_load_voltage_relay_model();
        if(model==NULL)
            return 0.0;
        else
            return model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="LOAD SHED SCALE IN PU")
    {
        return load->get_load_shed_scale_factor_in_pu();
    }
    return 0.0;
}
double METER::get_meter_value_as_a_generator() const
{
    GENERATOR* generator = (GENERATOR*) get_device_pointer();
    if(generator == NULL)
        return 0.0;

    if(generator->get_status()==false)
        return 0.0;

    POWER_SYSTEM_DATABASE* psdb = generator->get_power_system_database();
    double fbase = psdb->get_system_base_frequency_in_Hz();
    double sbase = psdb->get_system_base_power_in_MVA();
    double mbase = generator->get_mbase_in_MVA();

    SYNC_GENERATOR_MODEL* gen_model = generator->get_sync_generator_model();
    COMPENSATOR_MODEL* comp_model = generator->get_compensator_model();
    STABILIZER_MODEL* stabilizer_model = generator->get_stabilizer_model();
    EXCITER_MODEL* exciter_model = generator->get_exciter_model();
    TURBINE_GOVERNOR_MODEL* turbine_governor_model = generator->get_turbine_governor_model();

    if(meter_type=="GENERATOR ROTOR ANGLE IN DEG")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_rotor_angle_in_deg();
    }
    if(meter_type =="GENERATOR ROTOR SPEED IN PU")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_rotor_speed_in_pu();
    }
    if(meter_type =="GENERATOR ROTOR SPEED IN HZ")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return fbase*gen_model->get_rotor_speed_in_pu();
    }
    if(meter_type =="GENERATOR ROTOR SPEED DEVIATION IN PU")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_rotor_speed_deviation_in_pu();
    }
    if(meter_type =="GENERATOR ROTOR SPEED DEVIATION IN HZ")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return fbase*gen_model->get_rotor_speed_deviation_in_pu();
    }
    if(meter_type =="GENERATOR INTERNAL VOLTAGE IN PU")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return abs(gen_model->get_internal_voltage_in_pu_in_dq_axis());
    }
    if(meter_type =="GENERATOR TERMINAL CURRENT IN PU ON MBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_current_in_pu_based_on_mbase();
    }
    if(meter_type =="GENERATOR TERMINAL CURRENT IN PU ON SBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_current_in_pu_based_on_sbase();
    }
    if(meter_type =="GENERATOR TERMINAL CURRENT IN KA")
    {
        if(gen_model == NULL)
            return 0.0;
        else
        {
            double vbase = psdb->get_bus_base_voltage_in_kV(generator->get_generator_bus());
            double ibase = sbase/(sqrt(3.0)*vbase);
            return ibase*gen_model->get_terminal_current_in_pu_based_on_sbase();
        }
    }
    if(meter_type =="GENERATOR TERMINAL ACTIVE POWER IN PU ON MBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_active_power_in_MW()/mbase;
    }
    if(meter_type =="GENERATOR TERMINAL ACTIVE POWER IN PU ON SBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_active_power_in_MW()/sbase;
    }
    if(meter_type =="GENERATOR TERMINAL ACTIVE POWER IN MW")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_active_power_in_MW();
    }
    if(meter_type =="GENERATOR TERMINAL REACTIVE POWER IN PU ON MBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_reactive_power_in_MVar()/mbase;
    }
    if(meter_type =="GENERATOR TERMINAL REACTIVE POWER IN PU ON SBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_reactive_power_in_MVar()/sbase;
    }
    if(meter_type =="GENERATOR TERMINAL REACTIVE POWER IN MVAR")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_terminal_reactive_power_in_MVar();
    }
    if(meter_type =="GENERATOR AIRGAP POWER IN PU ON MBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_air_gap_power_in_pu_based_on_mbase();
    }
    if(meter_type =="GENERATOR AIRGAP POWER IN PU ON SBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_air_gap_power_in_MW()/sbase;
    }
    if(meter_type =="GENERATOR AIRGAP POWER IN MW")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_air_gap_power_in_MW();
    }
    if(meter_type =="GENERATOR ACCELERATING POWER IN PU ON MBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_accelerating_power_in_pu_based_on_mbase();
    }
    if(meter_type =="GENERATOR ACCELERATING POWER IN PU ON SBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_accelerating_power_in_MW()/sbase;
    }
    if(meter_type =="GENERATOR ACCELERATING POWER IN MW")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_accelerating_power_in_MW();
    }
    if(meter_type =="GENERATOR MECHANICAL POWER IN PU ON MBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_mechanical_power_in_pu_based_on_mbase();
    }
    if(meter_type =="GENERATOR MECHANICAL POWER IN PU ON SBASE")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_mechanical_power_in_MW()/sbase;
    }
    if(meter_type =="GENERATOR MECHANICAL POWER IN MW")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_mechanical_power_in_MW();
    }
    if(meter_type =="GENERATOR COMPENSATED VOLTAGE IN PU")
    {
        if(exciter_model == NULL)
            return 0.0;
        else
            return exciter_model->get_compensated_voltage_in_pu();
    }
    if(meter_type =="GENERATOR STABILIZING SIGNAL IN PU")
    {
        if(exciter_model == NULL)
            return 0.0;
        else
            return exciter_model->get_stabilizing_signal_in_pu();
    }
    if(meter_type =="GENERATOR EXCITATION VOLTAGE IN PU")
    {
        if(gen_model == NULL)
            return 0.0;
        else
            return gen_model->get_excitation_voltage_in_pu();
    }
    if(meter_type=="GENERATOR SYNC GENERATOR MODEL INTERNAL VARIABLE")
    {
        if(gen_model==NULL)
            return 0.0;
        else
            return gen_model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="GENERATOR COMPENSATOR MODEL INTERNAL VARIABLE")
    {
        if(comp_model==NULL)
            return 0.0;
        else
            return comp_model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="GENERATOR STABILIZER MODEL INTERNAL VARIABLE")
    {
        if(stabilizer_model==NULL)
            return 0.0;
        else
            return stabilizer_model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="GENERATOR EXCITER MODEL INTERNAL VARIABLE")
    {
        if(exciter_model==NULL)
            return 0.0;
        else
            return exciter_model->get_variable_with_index(internal_variable_index);
    }
    if(meter_type=="GENERATOR TURBINE GOVERNOR MODEL INTERNAL VARIABLE")
    {
        if(turbine_governor_model==NULL)
            return 0.0;
        else
            return turbine_governor_model->get_variable_with_index(internal_variable_index);
    }

    return 0.0;
}
double METER::get_meter_value_as_an_hvdc() const
{
    HVDC* hvdc = (HVDC*) get_device_pointer();
    if(hvdc == NULL)
        return 0.0;

    if(hvdc->get_status()==false)
        return 0.0;

    POWER_SYSTEM_DATABASE* psdb = hvdc->get_power_system_database();
    double fbase = psdb->get_system_base_frequency_in_Hz();
    double sbase = psdb->get_system_base_power_in_MVA();

    HVDC_MODEL* hvdc_model = hvdc->get_hvdc_model();

    if(meter_type=="HVDC DC CURRENT IN KA")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_current_in_kA(RECTIFIER);
    }

    if(meter_type=="HVDC RECTIFIER DC CURRENT IN KA")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_current_in_kA(RECTIFIER);
    }

    if(meter_type=="HVDC RECTIFIER AC CURRENT IN KA")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return abs(hvdc_model->get_converter_ac_current_in_kA(RECTIFIER));
    }

    if(meter_type=="HVDC INVERTER DC CURRENT IN KA")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_current_in_kA(INVERTER);
    }
    if(meter_type=="HVDC INVERTER AC CURRENT IN KA")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return abs(hvdc_model->get_converter_ac_current_in_kA(INVERTER));
    }

    if(meter_type=="HVDC RECTIFIER ALPHA IN DEG")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_alpha_or_gamma_in_deg(RECTIFIER);
    }

    if(meter_type=="HVDC INVERTER GAMMA IN DEG")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_alpha_or_gamma_in_deg(INVERTER);
    }

    if(meter_type=="HVDC RECTIFIER MU IN DEG")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_commutation_overlap_angle_in_deg(RECTIFIER);
    }

    if(meter_type=="HVDC INVERTER MU IN DEG")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_commutation_overlap_angle_in_deg(INVERTER);
    }

    if(meter_type=="HVDC RECTIFIER DC VOLTAGE IN KV")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_voltage_in_kV(RECTIFIER);
    }

    if(meter_type=="HVDC INVERTER DC VOLTAGE IN KV")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_voltage_in_kV(INVERTER);
    }

    if(meter_type=="HVDC RECTIFIER AC VOLTAGE IN PU")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return abs(hvdc_model->get_converter_ac_voltage_in_pu(RECTIFIER));
    }

    if(meter_type=="HVDC INVERTER AC VOLTAGE IN PU")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return abs(hvdc_model->get_converter_ac_voltage_in_pu(INVERTER));
    }

    if(meter_type=="HVDC RECTIFIER DC POWER IN MW")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_power_in_MW(RECTIFIER);
    }

    if(meter_type=="HVDC INVERTER DC POWER IN MW")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_dc_power_in_MW(INVERTER);
    }

    if(meter_type=="HVDC RECTIFIER AC ACTIVE POWER IN MW")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_ac_complex_power_in_MVA(RECTIFIER).real();
    }

    if(meter_type=="HVDC INVERTER AC ACTIVE POWER IN MW")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_ac_complex_power_in_MVA(INVERTER).real();
    }

    if(meter_type=="HVDC RECTIFIER AC REACTIVE POWER IN MVAR")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_ac_complex_power_in_MVA(RECTIFIER).imag();
    }

    if(meter_type=="HVDC INVERTER AC REACTIVE POWER IN MVAR")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_converter_ac_complex_power_in_MVA(INVERTER).imag();
    }

    if(meter_type=="HVDC MODEL INTERNAL VARIABLE")
    {
        if(hvdc_model == NULL)
            return 0.0;
        else
            return hvdc_model->get_variable_with_index(internal_variable_index);
    }

    return 0.0;
}

double METER::get_meter_value_as_an_equivalent_device() const
{
    EQUIVALENT_DEVICE* edevice = (EQUIVALENT_DEVICE*) get_device_pointer();
    if(edevice == NULL)
        return 0.0;

    if(meter_type=="EQUIVALENT DEVICE VOLTAGE SOURCE VOLTAGE IN PU")
    {
        return abs(edevice->get_equivalent_voltage_source_voltage_in_pu());
        if(edevice->get_equivalent_voltage_source_status()==false)
            return 0.0;
        else
            return abs(edevice->get_equivalent_voltage_source_voltage_in_pu());
    }

    if(meter_type=="EQUIVALENT DEVICE VOLTAGE SOURCE VOLTAGE ANGLE IN DEG")
    {
        return rad2deg(arg(edevice->get_equivalent_voltage_source_voltage_in_pu()));
        if(edevice->get_equivalent_voltage_source_status()==false)
            return 0.0;
        else
            return rad2deg(arg(edevice->get_equivalent_voltage_source_voltage_in_pu()));
    }

    if(meter_type=="EQUIVALENT DEVICE VOLTAGE SOURCE RESISTANCE IN PU")
    {
        return edevice->get_equivalent_voltage_source_impedance_in_pu().real();
        if(edevice->get_equivalent_voltage_source_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_voltage_source_impedance_in_pu().real();
    }

    if(meter_type=="EQUIVALENT DEVICE VOLTAGE SOURCE REACTANCE IN PU")
    {
        return edevice->get_equivalent_voltage_source_impedance_in_pu().imag();
        if(edevice->get_equivalent_voltage_source_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_voltage_source_impedance_in_pu().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE CONSTANT POWER LOAD IN MW")
    {
        return edevice->get_equivalent_nominal_constant_power_load_in_MVA().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_power_load_in_MVA().real();
    }

    if(meter_type=="EQUIVALENT DEVICE REACTIVE CONSTANT POWER LOAD IN MVAR")
    {
        return edevice->get_equivalent_nominal_constant_power_load_in_MVA().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_power_load_in_MVA().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE CONSTANT CURRENT LOAD IN MW")
    {
        return edevice->get_equivalent_nominal_constant_current_load_in_MVA().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_current_load_in_MVA().real();
    }

    if(meter_type=="EQUIVALENT DEVICE REACTIVE CONSTANT CURRENT LOAD IN MVAR")
    {
        return edevice->get_equivalent_nominal_constant_current_load_in_MVA().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_current_load_in_MVA().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE CONSTANT IMPEDANCE LOAD IN MW")
    {
        return edevice->get_equivalent_nominal_constant_impedance_load_in_MVA().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_impedance_load_in_MVA().real();
    }

    if(meter_type=="EQUIVALENT DEVICE REACTIVE CONSTANT IMPEDANCE LOAD IN MVAR")
    {
        return edevice->get_equivalent_nominal_constant_impedance_load_in_MVA().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_impedance_load_in_MVA().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE POWER GENERATION IN MW")
    {
        return edevice->get_equivalent_generation_in_MVA().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_generation_in_MVA().real();
    }
    if(meter_type=="EQUIVALENT DEVICE REACTIVE POWER GENERATION IN MVAR")
    {
        return edevice->get_equivalent_generation_in_MVA().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_generation_in_MVA().imag();
    }
    if(meter_type=="EQUIVALENT DEVICE ACTIVE POWER LOAD IN MW")
    {
        return edevice->get_equivalent_load_in_MVA().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_load_in_MVA().real();
    }
    if(meter_type=="EQUIVALENT DEVICE REACTIVE POWER LOAD IN MVAR")
    {
        return edevice->get_equivalent_load_in_MVA().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_load_in_MVA().imag();
    }
    if(meter_type=="EQUIVALENT DEVICE ACTIVE POWER NET LOAD IN MW")
    {
        return edevice->get_total_equivalent_power_as_load_in_MVA().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_total_equivalent_power_as_load_in_MVA().real();
    }
    if(meter_type=="EQUIVALENT DEVICE REACTIVE POWER NET LOAD IN MVAR")
    {
        return edevice->get_total_equivalent_power_as_load_in_MVA().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_total_equivalent_power_as_load_in_MVA().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE CONSTANT POWER LOAD IN PU")
    {
        return edevice->get_equivalent_nominal_constant_power_load_in_pu().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_power_load_in_pu().real();
    }

    if(meter_type=="EQUIVALENT DEVICE REACTIVE CONSTANT POWER LOAD IN PU")
    {
        return edevice->get_equivalent_nominal_constant_power_load_in_pu().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_power_load_in_pu().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE CONSTANT CURRENT LOAD IN PU")
    {
        return edevice->get_equivalent_nominal_constant_current_load_in_pu().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_current_load_in_pu().real();
    }

    if(meter_type=="EQUIVALENT DEVICE REACTIVE CONSTANT CURRENT LOAD IN PU")
    {
        return edevice->get_equivalent_nominal_constant_current_load_in_pu().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_current_load_in_pu().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE CONSTANT IMPEDANCE LOAD IN PU")
    {
        return edevice->get_equivalent_nominal_constant_impedance_load_in_pu().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_impedance_load_in_pu().real();
    }

    if(meter_type=="EQUIVALENT DEVICE REACTIVE CONSTANT IMPEDANCE LOAD IN PU")
    {
        return edevice->get_equivalent_nominal_constant_impedance_load_in_pu().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_nominal_constant_impedance_load_in_pu().imag();
    }

    if(meter_type=="EQUIVALENT DEVICE ACTIVE POWER GENERATION IN PU")
    {
        return edevice->get_equivalent_generation_in_pu().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_generation_in_pu().real();
    }
    if(meter_type=="EQUIVALENT DEVICE REACTIVE POWER GENERATION IN PU")
    {
        return edevice->get_equivalent_generation_in_pu().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_generation_in_pu().imag();
    }
    if(meter_type=="EQUIVALENT DEVICE ACTIVE POWER LOAD IN PU")
    {
        return edevice->get_equivalent_load_in_pu().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_load_in_pu().real();
    }
    if(meter_type=="EQUIVALENT DEVICE REACTIVE POWER LOAD IN PU")
    {
        return edevice->get_equivalent_load_in_pu().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_equivalent_load_in_pu().imag();
    }
    if(meter_type=="EQUIVALENT DEVICE ACTIVE POWER NET LOAD IN PU")
    {
        return edevice->get_total_equivalent_power_as_load_in_pu().real();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_total_equivalent_power_as_load_in_pu().real();
    }
    if(meter_type=="EQUIVALENT DEVICE REACTIVE POWER NET LOAD IN PU")
    {
        return edevice->get_total_equivalent_power_as_load_in_pu().imag();
        if(edevice->get_equivalent_load_status()==false)
            return 0.0;
        else
            return edevice->get_total_equivalent_power_as_load_in_pu().imag();
    }

    return 0.0;
}