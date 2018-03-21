#include "header/data_imexporter/psse_imexporter.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"
#include "header/model/all_supported_models.h"
#include <cstdio>
#include <iostream>
using namespace std;

void PSSE_IMEXPORTER::load_dynamic_data(string file)
{
    if(not is_power_system_database_set())
        return;

    ostringstream sstream;
    sstream<<"Loading dynamic data from PSS/E file: "<<file;
    show_information_with_leading_time_stamp(sstream);

    file = string2upper(file);
    load_dynamic_data_into_ram(file);
    load_all_models();

    sstream<<"Done loading dynamic data.";
    show_information_with_leading_time_stamp(sstream);
}

void PSSE_IMEXPORTER::load_dynamic_data_into_ram(string file)
{
    ostringstream sstream;

    dyr_data_in_ram.clear();

    FILE* fid = fopen(file.c_str(),"rt");
    if(fid == NULL)
    {
        sstream<<"PSS/E dyr file '"<<file<<"' is not accessible. Loading PSS/E dyr data is failed.";
        show_information_with_leading_time_stamp(sstream);
        return;
    }

    char buffer[10240];
    string sbuffer;

    string data_of_one_type;
    data_of_one_type.clear();
    while(true)
    {
        if(fgets(buffer, 1024, fid)==NULL)
        {
            if(data_of_one_type.size()!=0)
            {
                data_of_one_type = string2csv(data_of_one_type);
                dyr_data_in_ram.push_back(data_of_one_type);
                data_of_one_type.clear();
            }
            break;
        }
        sbuffer = buffer;
        size_t index_of_slash = sbuffer.find('/');
        if(index_of_slash==string::npos)
        {
            sbuffer = trim_string(sbuffer);
            data_of_one_type = data_of_one_type +" "+sbuffer;
        }
        else
        {
            sbuffer = trim_psse_comment(buffer);
            sbuffer = trim_string(sbuffer);
            data_of_one_type = data_of_one_type +" "+sbuffer;

            data_of_one_type = string2csv(data_of_one_type);
            dyr_data_in_ram.push_back(data_of_one_type);
            data_of_one_type.clear();
        }
    }
    fclose(fid);

    //for(size_t i=0; i<dyr_data_in_ram.size(); ++i)
    //    cout<<dyr_data_in_ram[i]<<endl;
}

void PSSE_IMEXPORTER::load_all_models()
{
    size_t n = dyr_data_in_ram.size();
    for(size_t i=0; i!=n; ++i)
        load_one_model(dyr_data_in_ram[i]);

}

void PSSE_IMEXPORTER::load_one_model(string data)
{
    ostringstream sstream;
    //sstream<< "Now go parsing dynamic data: "<<data;
    //show_information_with_leading_time_stamp(sstream);

    string model_name = get_dynamic_model_name(data);
    if(model_name=="")
        return;
    if(model_name=="GENCLS") { add_GENCLS_model(data); return;}
    if(model_name=="GENROU") { add_GENROU_model(data); return;}
    if(model_name=="GENSAL") { add_GENSAL_model(data); return;}

    if(model_name=="COMP") { add_COMP_model(data); return;}

    if(model_name=="SEXS") { add_SEXS_model(data); return;}
    if(model_name=="IEEET1") { add_IEEET1_model(data); return;}
    if(model_name=="PSASPE1") { add_PSASPE1_model(data); return;}
    if(model_name=="PSASPE2") { add_PSASPE2_model(data); return;}
    if(model_name=="CSEET1") { add_CSEET1_model(data); return;}
    if(model_name=="CSEET2") { add_CSEET2_model(data); return;}
    if(model_name=="PSASPE13") { add_PSASPE13_model(data); return;}

    if(model_name=="TGOV1") { add_TGOV1_model(data); return;}
    if(model_name=="IEEEG1") { add_IEEEG1_model(data); return;}
    if(model_name=="IEEEG2") { add_IEEEG2_model(data); return;}
    if(model_name=="IEEEG3") { add_IEEEG3_model(data); return;}
    if(model_name=="IEESGO") { add_IEESGO_model(data); return;}


    if(model_name=="IEELAL" or model_name=="IEELAR" or model_name=="IEELZN" or
       model_name=="IEELOW" or model_name=="IEELBL") { add_IEEL_model(data); return;}

    if(model_name=="UFLSAL" or model_name=="UFLSAR" or model_name=="UFLSZN" or
       model_name=="UFLSOW" or model_name=="UFLSBL") { add_UFLS_model(data); return;}
    if(model_name=="PUFLSAL" or model_name=="PUFLSAR" or model_name=="PUFLSZN" or
       model_name=="PUFLSOW" or model_name=="PUFLSBL") { add_PUFLS_model(data); return;}

    if(model_name=="CDC4T") { add_CDC4T_model(data); return;}
    if(model_name=="CDC6T") { add_CDC6T_model(data); return;}


    sstream<<"Warning. Dynamic model '"<<model_name<<"' is not supported. Check line "<<__LINE__<<" in file "<<__FILE__;
    show_information_with_leading_time_stamp(sstream);

}
string PSSE_IMEXPORTER::get_dynamic_model_name(string data)
{
    vector<string> splitted_data = split_string(data, ",");
    if(splitted_data.size()>=2)
    {
        string model_name = splitted_data[1];
        model_name = get_string_data(model_name, "");
        return model_name;
    }
    else
        return "";
}

DEVICE_ID PSSE_IMEXPORTER::get_generator_device_id_from_string(string data)
{
    DEVICE_ID did;
    did.set_device_type("GENERATOR");

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return did;

    size_t bus;
    string identifier;

    size_t i=0;
    bus = get_integer_data(dyrdata[i], "0"); i++; i++;
    identifier = get_string_data(dyrdata[i],"");

    TERMINAL terminal;
    terminal.append_bus(bus);
    did.set_device_terminal(terminal);
    did.set_device_identifier(identifier);

    return did;
}

DEVICE_ID PSSE_IMEXPORTER::get_load_device_id_from_string(string data)
{
    DEVICE_ID did;
    did.set_device_type("LOAD");

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return did;

    size_t bus;
    string identifier;

    size_t i=0;
    bus = get_integer_data(dyrdata[i], "0"); i++; i++;
    identifier = get_string_data(dyrdata[i],"");

    TERMINAL terminal;
    terminal.append_bus(bus);
    did.set_device_terminal(terminal);
    did.set_device_identifier(identifier);

    return did;
}

DEVICE_ID PSSE_IMEXPORTER::get_line_device_id_from_string(string data)
{
    DEVICE_ID did;
    did.set_device_type("LINE");

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<4)
        return did;

    size_t ibus, jbus;
    string identifier;

    size_t i=0;
    ibus = get_integer_data(dyrdata[i], "0"); i++; i++;
    jbus = get_integer_data(dyrdata[i], "0"); i++;
    identifier = get_string_data(dyrdata[i],"");

    TERMINAL terminal;
    terminal.append_bus(ibus);
    terminal.append_bus(jbus);
    did.set_device_terminal(terminal);
    did.set_device_identifier(identifier);

    return did;
}
DEVICE_ID PSSE_IMEXPORTER::get_hvdc_device_id_from_string(string data)
{
    DEVICE_ID did;
    did.set_device_type("HVDC");

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<2)
        return did;

    string hvdc_name;

    size_t i=0;
    hvdc_name = get_string_data(dyrdata[i], "0");

    size_t n = psdb->get_hvdc_count();
    vector<HVDC*> hvdcs = psdb->get_all_hvdcs();
    for(size_t i=0; i!=n; ++i)
    {
        if(hvdc_name == hvdcs[i]->get_name())
        {
            TERMINAL terminal;
            terminal.append_bus(hvdcs[i]->get_converter_bus(RECTIFIER));
            terminal.append_bus(hvdcs[i]->get_converter_bus(INVERTER));
            did.set_device_terminal(terminal);
            did.set_device_identifier(hvdcs[i]->get_identifier());
            break;
        }
    }

    return did;
}
DEVICE_ID PSSE_IMEXPORTER::get_transformer_device_id_from_string(string data)
{
    DEVICE_ID did;
    did.set_device_type("TRANSFORMER");

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<4)
        return did;

    size_t ibus, jbus, kbus;
    string identifier;

    size_t i=0;
    ibus = get_integer_data(dyrdata[i], "0"); i++; i++;
    jbus = get_integer_data(dyrdata[i], "0"); i++;
    kbus = get_integer_data(dyrdata[i], "0"); i++;
    identifier = get_string_data(dyrdata[i],"");

    TERMINAL terminal;
    terminal.append_bus(ibus);
    terminal.append_bus(jbus);
    terminal.append_bus(kbus);
    did.set_device_terminal(terminal);
    did.set_device_identifier(identifier);

    return did;
}

void PSSE_IMEXPORTER::add_GENCLS_model(string data)
{
    if(get_dynamic_model_name(data) != "GENCLS")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        GENCLS model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid GENCLS model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_GENROU_model(string data)
{
    if(get_dynamic_model_name(data) != "GENROU")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        GENROU model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid GENROU model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_GENSAL_model(string data)
{
    if(get_dynamic_model_name(data) != "GENSAL")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        GENSAL model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid GENSAL model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_COMP_model(string data)
{
    if(get_dynamic_model_name(data) != "COMP")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        COMP model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid COMP model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_IEE2ST_model(string data)
{
    if(get_dynamic_model_name(data) != "IEE2ST")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        IEE2ST model;
        model.set_power_system_database(psdb);
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid IEE2ST model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_SEXS_model(string data)
{
    if(get_dynamic_model_name(data) != "SEXS")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        SEXS model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid SEXS model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_IEEET1_model(string data)
{
    if(get_dynamic_model_name(data) != "IEEET1")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        IEEET1 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid IEEET1 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_PSASPE1_model(string data)
{
    if(get_dynamic_model_name(data) != "PSASPE1")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        PSASPE1 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid PSASPE1 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_PSASPE2_model(string data)
{
    if(get_dynamic_model_name(data) != "PSASPE2")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        PSASPE2 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid PSASPE2 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_CSEET1_model(string data)
{
    if(get_dynamic_model_name(data) != "CSEET1")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        CSEET1 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid CSEET1 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_CSEET2_model(string data)
{
    if(get_dynamic_model_name(data) != "CSEET2")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        CSEET2 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid CSEET2 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_PSASPE13_model(string data)
{
    if(get_dynamic_model_name(data) != "PSASPE13")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        PSASPE13 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid PSASPE13 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_TGOV1_model(string data)
{
    if(get_dynamic_model_name(data) != "TGOV1")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        TGOV1 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid TGOV1 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_IEEEG1_model(string data)
{
    if(get_dynamic_model_name(data) != "IEEEG1")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        IEEEG1 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid IEEEG1 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_IEEEG2_model(string data)
{
    if(get_dynamic_model_name(data) != "IEEEG2")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        IEEEG2 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid IEEEG2 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

void PSSE_IMEXPORTER::add_IEEEG3_model(string data)
{
    if(get_dynamic_model_name(data) != "IEEEG3")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        IEEEG3 model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid IEEEG3 model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}


void PSSE_IMEXPORTER::add_IEESGO_model(string data)
{
    if(get_dynamic_model_name(data) != "IEESGO")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_generator_device_id_from_string(data);

    GENERATOR* generator = psdb->get_generator(did);
    if(generator != NULL)
    {
        IEESGO model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            generator->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid IEESGO model is built, but will not be set for "<<generator->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }
}

vector<LOAD*> PSSE_IMEXPORTER::get_all_loads_of(string data)
{
    vector<LOAD*> loads;

    string model_name = get_dynamic_model_name(data);
    if(model_name!="IEELAL" and model_name!="IEELAR" and model_name!="IEELZN" and
       model_name!="IEELBL" and
       model_name!="CIM5AL" and model_name!="CIM5AR" and model_name!="CIM5ZN" and
       model_name!="CIM5BL" and
       model_name!="UFLSAL" and model_name!="UFLSAR" and model_name!="UFLSZN" and
       model_name!="UFLSBL" and
       model_name!="PUFLSAL" and model_name!="PUFLSAR" and model_name!="PUFLSZN" and
       model_name!="PUFLSBL"
       )
        return loads;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return loads;

    size_t subsystem_number;
    string identifier;

    size_t i=0;
    subsystem_number = get_integer_data(dyrdata[i], "0");  i++; i++;
    identifier = get_string_data(dyrdata[i],""); i++;

    size_t model_name_size = model_name.size();
    string model_subsystem_type = model_name.substr(model_name_size-2,2);

    if(model_subsystem_type=="AL")
    {
        loads = psdb->get_all_loads();
        loads = remove_loads_with_different_identifier(loads, identifier);
        return loads;
    }
    if(model_subsystem_type=="AR")
    {
        size_t area_no = subsystem_number;
        loads = psdb->get_all_loads();
        for(vector<LOAD*>::iterator iter=loads.end(); iter!=loads.begin(); )
        {
            iter--;
            size_t area = (*iter)->get_area_number();
            if(area!=area_no)
                loads.erase(iter);
        }
        loads = remove_loads_with_different_identifier(loads, identifier);
        return loads;
    }
    if(model_subsystem_type=="ZN")
    {
        size_t zone_no = subsystem_number;
        loads = psdb->get_all_loads();
        for(vector<LOAD*>::iterator iter=loads.end(); iter!=loads.begin(); )
        {
            iter--;
            size_t zone = (*iter)->get_zone_number();
            if(zone!=zone_no)
                loads.erase(iter);
        }
        loads = remove_loads_with_different_identifier(loads, identifier);
        return loads;
    }
    if(model_subsystem_type=="BL")
    {
        size_t bus_no = subsystem_number;
        loads = psdb->get_loads_connecting_to_bus(bus_no);
        loads = remove_loads_with_different_identifier(loads, identifier);
        return loads;
    }
    return loads;
}

vector<LOAD*> PSSE_IMEXPORTER::remove_loads_with_different_identifier(vector<LOAD*> loads, string identifier)
{
    if(identifier=="*")
        return loads;

    for(vector<LOAD*>::iterator iter=loads.end(); iter!=loads.begin(); )
    {
        iter--;
        string load_id = (*iter)->get_identifier();
        if(load_id!=identifier)
            loads.erase(iter);
    }
    return loads;
}

void PSSE_IMEXPORTER::add_IEEL_model(string data)
{
    string model_name = get_dynamic_model_name(data);
    if(model_name!="IEELAL" and model_name!="IEELAR" and model_name!="IEELZN" and
       model_name!="IEELBL")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    IEEL model;
    bool successful = model.setup_model_with_psse_string(data);
    if(successful)
    {
        vector<LOAD*> loads = get_all_loads_of(data);
        size_t n = loads.size();
        for(size_t i=0; i!=n; ++i)
            loads[i]->set_model(&model);
    }
}

void PSSE_IMEXPORTER::add_UFLS_model(string data)
{
    string model_name = get_dynamic_model_name(data);
    if(model_name!="UFLSAL" and model_name!="UFLSAR" and model_name!="UFLSZN" and
       model_name!="UFLSBL")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    UFLS model;

    bool successful = model.setup_model_with_psse_string(data);

    if(successful)
    {
        vector<LOAD*> loads = get_all_loads_of(data);
        size_t n = loads.size();
        for(size_t i=0; i!=n; ++i)
            loads[i]->set_model(&model);
    }
}

void PSSE_IMEXPORTER::add_PUFLS_model(string data)
{
    string model_name = get_dynamic_model_name(data);
    if(model_name!="PUFLSAL" and model_name!="PUFLSAR" and model_name!="PUFLSZN" and
       model_name!="PUFLSBL")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<3)
        return;

    PUFLS model;
    bool successful = model.setup_model_with_psse_string(data);
    if(successful)
    {
        vector<LOAD*> loads = get_all_loads_of(data);
        size_t n = loads.size();
        for(size_t i=0; i!=n; ++i)
            loads[i]->set_model(&model);
    }
}

void PSSE_IMEXPORTER::add_CDC4T_model(string data)
{
    if(get_dynamic_model_name(data) != "CDC4T")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<24)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_hvdc_device_id_from_string(data);

    HVDC* hvdc = psdb->get_hvdc(did);
    if(hvdc != NULL)
    {
        CDC4T model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            hvdc->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid CDC4T model is built, but will not be set for "<<hvdc->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }

}


void PSSE_IMEXPORTER::add_CDC6T_model(string data)
{
    if(get_dynamic_model_name(data) != "CDC6T")
        return;

    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<34)
        return;

    POWER_SYSTEM_DATABASE* psdb = get_power_system_database();
    DEVICE_ID did = get_hvdc_device_id_from_string(data);

    HVDC* hvdc = psdb->get_hvdc(did);
    if(hvdc != NULL)
    {
        CDC6T model;
        bool successful = model.setup_model_with_psse_string(data);
        if(successful)
            hvdc->set_model(&model);
        else
        {
            ostringstream sstream;
            sstream<<"Waring. Invalid CDC6T model is built, but will not be set for "<<hvdc->get_device_name();
            show_information_with_leading_time_stamp(sstream);
        }
    }

}


void PSSE_IMEXPORTER::export_dynamic_data(string file)
{
    return;
}