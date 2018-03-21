#include "header/power_system_database_test.h"
#include "header/basic/utility.h"
#include "header/prepare_for_tests/prepare_models_for_test.h"
#include "header/data_imexporter/psse_imexporter.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;


POWER_SYSTEM_DATABASE_TEST::POWER_SYSTEM_DATABASE_TEST()
{
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_bus_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_generator_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_pe_source_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_load_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_fixed_shunt_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_line_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_transformer_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_hvdc_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_equivalent_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_area_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_zone_capacity);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_owner_capacity);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_system_name);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_allowed_max_bus_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_bus_in_allowed_range);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_system_base_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_set_get_system_base_frequency);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_bus_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_generator);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_pe_source);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_load);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_line);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_transformer);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_fixed_shunt);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_hvdc);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_equivalent_device);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_append_and_get_owner);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_generator_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_pe_source_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_load_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_line_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_transformer_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_fixed_shunt_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_hvdc_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_equivalent_device_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_area_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_zone_exist);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_is_owner_exist);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_change_bus_number);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generators_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_sources_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_loads_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_lines_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformers_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_connecting_to_bus);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generators_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_sources_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_loads_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_lines_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformers_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_device_id_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_device_id_connecting_to_bus);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_buses_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generators_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_sources_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_loads_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_lines_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformers_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_in_area);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_buses_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generators_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_sources_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_loads_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_lines_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformers_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_device_id_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_device_id_in_area);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_buses_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generators_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_sources_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_loads_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_lines_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformers_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_in_zone);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_buses_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generators_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_sources_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_loads_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_lines_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformers_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_device_id_in_zone);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_device_id_in_zone);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_buses);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_in_service_buses);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_generators);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_pe_sources);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_sources);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_loads);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_lines);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_transformers);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_fixed_shunts);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_hvdcs);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_equivalent_devices);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_areas);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_zones);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_owners);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_buses_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_in_service_buses_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_generators_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_pe_sources_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_sources_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_loads_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_lines_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_transformers_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_fixed_shunts_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_hvdcs_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_equivalent_devices_device_id);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_areas_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_zones_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_all_owners_number);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_bus_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_in_service_bus_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generator_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_source_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_source_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_load_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_line_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformer_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunt_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdc_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_device_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_area_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_zone_count);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_owner_count);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_bus_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_generator_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_pe_source_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_load_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_line_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_transformer_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunt_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_hvdc_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_device_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_area_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_zone_index);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_owner_index);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_bus_name2bus_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_area_name2area_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_zone_name2zone_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_owner_name2owner_number);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_bus_number2bus_name);


    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_load_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_all_load_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_load_power_at_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_load_power_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_load_power_in_zone);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_source_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_all_source_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_source_power_at_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_source_power_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_source_power_in_zone);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_all_generator_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power_at_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power_in_zone);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_all_pe_source_power);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power_at_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power_in_area);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power_in_zone);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_database);
    //TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_buses);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_generator);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_generators_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_generators);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_pe_source);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_pe_sources_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_pe_sources);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_sources_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_sources);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_load);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_loads_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_loads);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_line);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_lines_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_lines);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_transformer);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_transformers_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_transformers);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_fixed_shunt);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_fixed_shunts_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_fixed_shunts);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_hvdc);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_hvdcs_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_hvdcs);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_equivalent_device);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_equivalent_devices_connecting_to_bus);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_equivalent_devices);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_areas);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_zones);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_clear_all_owners);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_bus_complex_voltage);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_bus_base_voltage);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_bus_voltage);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_bus_angle);

    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_voltage_to_regulate_of_physical_bus_in_pu);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_regulatable_q_max_at_physical_bus_in_MVar);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_regulatable_q_min_at_physical_bus_in_MVar);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_total_regulating_p_generation_at_physical_bus_in_MW);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_total_regulating_q_generation_at_physical_bus_in_MVar);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_total_p_generation_of_sources_at_physical_bus_in_MW);
    TEST_ADD(POWER_SYSTEM_DATABASE_TEST::test_get_total_q_generation_of_sources_at_physical_bus_in_MVar);
}

void POWER_SYSTEM_DATABASE_TEST::setup()
{
    db = new POWER_SYSTEM_DATABASE;
}

void POWER_SYSTEM_DATABASE_TEST::tear_down()
{
    delete db;

    show_test_end_information();
}


void POWER_SYSTEM_DATABASE_TEST::prepare_database_for_test()
{
    // all devices in the test database are:
    // Bus: 1, 2, 3
    // Generator: 1-#1, 1-#2, 2-#1, 2-#2, 3-#1, 3-#2
    // PE Source: 1-#1, 1-#2, 2-#1, 2-#2, 3-#1, 3-#2
    // Load: 1-#1, 1-#2, 2-#1, 2-#2, 3-#1, 3-#2
    // Fixed shunt: 1-#1, 1-#2, 2-#1, 2-#2, 3-#1, 3-#2
    // Line: 1-2-#1, 1-2-#2, 2-3-#1, 2-3-#2, 1-3-#1, 1-3-#2,
    // Transformer: 1-2-#1, 1-2-#2, 2-3-#1, 2-3-#2, 1-3-#1, 1-3-#2, 1-2-3-#1, 1-2-3-#2
    // Hvdc: 1-2-#1, 1-2-#2, 2-3-#1, 2-3-#2, 1-3-#1, 1-3-#2,
    // Equivalent device: 1-#1, 1-#2, 2-#1, 2-#2, 3-#1, 3-#2
    // Area: 1, 2, 3
    // Zone: 1, 2, 3
    // Owner: 1, 2, 3
    db->set_allowed_max_bus_number(100);

    {
        BUS bus(db);
        bus.set_bus_number(1);
        bus.set_bus_name("BUS A");
        bus.set_base_voltage_in_kV(110.0);
        bus.set_bus_type(SLACK_TYPE);
        bus.set_area_number(1);
        bus.set_zone_number(1);
        db->append_bus(bus);

        bus.set_bus_number(2);
        bus.set_bus_name("BUS B");
        bus.set_base_voltage_in_kV(220.0);
        bus.set_bus_type(PQ_TYPE);
        bus.set_area_number(2);
        bus.set_zone_number(2);
        db->append_bus(bus);

        bus.set_bus_number(3);
        bus.set_bus_name("BUS C");
        bus.set_base_voltage_in_kV(330.0);
        bus.set_bus_type(PV_TYPE);
        bus.set_area_number(3);
        bus.set_zone_number(3);
        db->append_bus(bus);
    }

    {
        GENERATOR generator(db);
        generator.set_generator_bus(1);
        generator.set_identifier("#1");
        generator.set_status(true);
        generator.set_p_generation_in_MW(10.0);
        generator.set_q_generation_in_MVar(10.0);
        generator.set_p_max_in_MW(110.0);
        generator.set_p_min_in_MW(-110.0);
        generator.set_q_max_in_MVar(110.0);
        generator.set_q_min_in_MVar(-110.0);
        generator.set_regulating_mode(REGULATING_VA);
        db->append_generator(generator);

        generator.set_identifier("#2");
        generator.set_status(true);
        generator.set_p_generation_in_MW(10.0);
        generator.set_q_generation_in_MVar(20.0);
        generator.set_p_max_in_MW(120.0);
        generator.set_p_min_in_MW(-120.0);
        generator.set_q_max_in_MVar(120.0);
        generator.set_q_min_in_MVar(-120.0);
        db->append_generator(generator);

        generator.set_generator_bus(2);
        generator.set_identifier("#1");
        generator.set_status(true);
        generator.set_p_generation_in_MW(20.0);
        generator.set_q_generation_in_MVar(10.0);
        generator.set_p_max_in_MW(210.0);
        generator.set_p_min_in_MW(-210.0);
        generator.set_q_max_in_MVar(210.0);
        generator.set_q_min_in_MVar(-210.0);
        generator.set_regulating_mode(REGULATING_PV);
        db->append_generator(generator);

        generator.set_identifier("#2");
        generator.set_status(true);
        generator.set_p_generation_in_MW(20.0);
        generator.set_q_generation_in_MVar(20.0);
        generator.set_p_max_in_MW(220.0);
        generator.set_p_min_in_MW(-220.0);
        generator.set_q_max_in_MVar(220.0);
        generator.set_q_min_in_MVar(-220.0);
        db->append_generator(generator);

        generator.set_generator_bus(3);
        generator.set_identifier("#1");
        generator.set_status(true);
        generator.set_p_generation_in_MW(30.0);
        generator.set_q_generation_in_MVar(10.0);
        generator.set_p_max_in_MW(310.0);
        generator.set_p_min_in_MW(-310.0);
        generator.set_q_max_in_MVar(310.0);
        generator.set_q_min_in_MVar(-310.0);
        generator.set_regulating_mode(REGULATING_PQ);
        db->append_generator(generator);

        generator.set_identifier("#2");
        generator.set_status(true);
        generator.set_p_generation_in_MW(30.0);
        generator.set_q_generation_in_MVar(20.0);
        generator.set_p_max_in_MW(320.0);
        generator.set_p_min_in_MW(-320.0);
        generator.set_q_max_in_MVar(320.0);
        generator.set_q_min_in_MVar(-320.0);
        db->append_generator(generator);
    }

    {
        PE_SOURCE pesource(db);
        pesource.set_source_bus(1);
        pesource.set_identifier("#1");
        pesource.set_status(true);
        pesource.set_p_generation_in_MW(10.0);
        pesource.set_q_generation_in_MVar(10.0);
        pesource.set_p_max_in_MW(101.0);
        pesource.set_p_min_in_MW(-101.0);
        pesource.set_q_max_in_MVar(101.0);
        pesource.set_q_min_in_MVar(-101.0);
        pesource.set_regulating_mode(REGULATING_VA);
        db->append_pe_source(pesource);

        pesource.set_identifier("#2");
        pesource.set_status(true);
        pesource.set_p_generation_in_MW(10.0);
        pesource.set_q_generation_in_MVar(20.0);
        pesource.set_p_max_in_MW(102.0);
        pesource.set_p_min_in_MW(-102.0);
        pesource.set_q_max_in_MVar(102.0);
        pesource.set_q_min_in_MVar(-102.0);
        db->append_pe_source(pesource);

        pesource.set_source_bus(2);
        pesource.set_identifier("#1");
        pesource.set_status(true);
        pesource.set_p_generation_in_MW(20.0);
        pesource.set_q_generation_in_MVar(10.0);
        pesource.set_p_max_in_MW(201.0);
        pesource.set_p_min_in_MW(-201.0);
        pesource.set_q_max_in_MVar(201.0);
        pesource.set_q_min_in_MVar(-201.0);
        pesource.set_regulating_mode(REGULATING_PV);
        db->append_pe_source(pesource);

        pesource.set_identifier("#2");
        pesource.set_status(true);
        pesource.set_p_generation_in_MW(20.0);
        pesource.set_q_generation_in_MVar(20.0);
        pesource.set_p_max_in_MW(202.0);
        pesource.set_p_min_in_MW(-202.0);
        pesource.set_q_max_in_MVar(202.0);
        pesource.set_q_min_in_MVar(-202.0);
        db->append_pe_source(pesource);

        pesource.set_source_bus(3);
        pesource.set_identifier("#1");
        pesource.set_status(true);
        pesource.set_p_generation_in_MW(30.0);
        pesource.set_q_generation_in_MVar(10.0);
        pesource.set_p_max_in_MW(301.0);
        pesource.set_p_min_in_MW(-301.0);
        pesource.set_q_max_in_MVar(301.0);
        pesource.set_q_min_in_MVar(-301.0);
        pesource.set_regulating_mode(REGULATING_PQ);
        db->append_pe_source(pesource);

        pesource.set_identifier("#2");
        pesource.set_status(true);
        pesource.set_p_generation_in_MW(30.0);
        pesource.set_q_generation_in_MVar(20.0);
        pesource.set_p_max_in_MW(302.0);
        pesource.set_p_min_in_MW(-302.0);
        pesource.set_q_max_in_MVar(302.0);
        pesource.set_q_min_in_MVar(-302.0);
        db->append_pe_source(pesource);
    }

    {
        LOAD load(db);
        load.set_load_bus(1);
        load.set_identifier("#1");
        load.set_status(true);
        load.set_area_number(1);
        load.set_zone_number(1);
        load.set_nominal_constant_power_load_in_MVA(complex<double>(10.0, 10.0));
        db->append_load(load);

        load.set_identifier("#2");
        load.set_nominal_constant_power_load_in_MVA(complex<double>(10.0, 20.0));
        db->append_load(load);

        load.set_load_bus(2);
        load.set_identifier("#1");
        load.set_area_number(2);
        load.set_zone_number(2);
        load.set_nominal_constant_power_load_in_MVA(complex<double>(20.0, 10.0));
        db->append_load(load);

        load.set_identifier("#2");
        load.set_nominal_constant_power_load_in_MVA(complex<double>(20.0, 20.0));
        db->append_load(load);

        load.set_load_bus(3);
        load.set_identifier("#1");
        load.set_area_number(3);
        load.set_zone_number(3);
        load.set_nominal_constant_power_load_in_MVA(complex<double>(30.0, 10.0));
        db->append_load(load);

        load.set_identifier("#2");
        load.set_nominal_constant_power_load_in_MVA(complex<double>(30.0, 20.0));
        db->append_load(load);
    }

    {
        FIXED_SHUNT shunt(db);
        shunt.set_shunt_bus(1);
        shunt.set_identifier("#1");
        db->append_fixed_shunt(shunt);

        shunt.set_identifier("#2");
        db->append_fixed_shunt(shunt);

        shunt.set_shunt_bus(2);
        shunt.set_identifier("#1");
        db->append_fixed_shunt(shunt);

        shunt.set_identifier("#2");
        db->append_fixed_shunt(shunt);

        shunt.set_shunt_bus(3);
        shunt.set_identifier("#1");
        db->append_fixed_shunt(shunt);

        shunt.set_identifier("#2");
        db->append_fixed_shunt(shunt);
    }

    {
        LINE line(db);
        line.set_sending_side_bus(1);
        line.set_receiving_side_bus(2);
        line.set_identifier("#1");
        db->append_line(line);

        line.set_identifier("#2");
        db->append_line(line);

        line.set_sending_side_bus(2);
        line.set_receiving_side_bus(3);
        line.set_identifier("#1");
        db->append_line(line);

        line.set_identifier("#2");
        db->append_line(line);

        line.set_sending_side_bus(1);
        line.set_receiving_side_bus(3);
        line.set_identifier("#1");
        db->append_line(line);

        line.set_identifier("#2");
        db->append_line(line);
    }

    {
        TRANSFORMER transformer(db);
        transformer.set_winding_bus(PRIMARY_SIDE, 1);
        transformer.set_winding_bus(SECONDARY_SIDE, 2);
        transformer.set_identifier("#1");
        db->append_transformer(transformer);

        transformer.set_identifier("#2");
        db->append_transformer(transformer);

        transformer.set_winding_bus(PRIMARY_SIDE, 2);
        transformer.set_winding_bus(SECONDARY_SIDE, 3);
        transformer.set_identifier("#1");
        db->append_transformer(transformer);
        transformer.set_identifier("#2");
        db->append_transformer(transformer);

        transformer.set_winding_bus(PRIMARY_SIDE, 1);
        transformer.set_winding_bus(SECONDARY_SIDE, 3);
        transformer.set_identifier("#1");
        db->append_transformer(transformer);
        transformer.set_identifier("#2");
        db->append_transformer(transformer);

        transformer.set_winding_bus(PRIMARY_SIDE, 1);
        transformer.set_winding_bus(SECONDARY_SIDE, 2);
        transformer.set_winding_bus(TERTIARY_SIDE, 3);
        transformer.set_identifier("#1");
        db->append_transformer(transformer);
        transformer.set_identifier("#2");
        db->append_transformer(transformer);
    }

    {
        HVDC hvdc(db);
        hvdc.set_converter_bus(RECTIFIER, 1);
        hvdc.set_converter_bus(INVERTER, 2);
        hvdc.set_identifier("#1");
        hvdc.set_name("HVDC A");
        db->append_hvdc(hvdc);

        hvdc.set_identifier("#2");
        hvdc.set_name("HVDC B");
        db->append_hvdc(hvdc);

        hvdc.set_converter_bus(RECTIFIER, 2);
        hvdc.set_converter_bus(INVERTER, 3);
        hvdc.set_identifier("#1");
        hvdc.set_name("HVDC C");
        db->append_hvdc(hvdc);

        hvdc.set_identifier("#2");
        hvdc.set_name("HVDC D");
        db->append_hvdc(hvdc);

        hvdc.set_converter_bus(RECTIFIER, 1);
        hvdc.set_converter_bus(INVERTER, 3);
        hvdc.set_identifier("#1");
        hvdc.set_name("HVDC E");
        db->append_hvdc(hvdc);

        hvdc.set_identifier("#2");
        hvdc.set_name("HVDC F");
        db->append_hvdc(hvdc);
    }

    {
        EQUIVALENT_DEVICE edevice(db);
        edevice.set_equivalent_device_bus(1);
        edevice.set_identifier("#1");
        edevice.set_status(true);
        db->append_equivalent_device(edevice);

        edevice.set_identifier("#2");
        edevice.set_status(false);
        db->append_equivalent_device(edevice);

        edevice.set_equivalent_device_bus(2);
        edevice.set_identifier("#1");
        edevice.set_status(true);
        db->append_equivalent_device(edevice);

        edevice.set_identifier("#2");
        edevice.set_status(false);
        db->append_equivalent_device(edevice);

        edevice.set_equivalent_device_bus(3);
        edevice.set_identifier("#1");
        edevice.set_status(true);
        db->append_equivalent_device(edevice);

        edevice.set_identifier("#2");
        edevice.set_status(false);
        db->append_equivalent_device(edevice);
    }

    {
        AREA area(db);
        area.set_area_number(1);
        area.set_area_name("AREA A");
        area.set_area_swing_bus(1);
        db->append_area(area);

        area.set_area_number(2);
        area.set_area_name("AREA B");
        area.set_area_swing_bus(1);
        db->append_area(area);

        area.set_area_number(3);
        area.set_area_name("AREA C");
        area.set_area_swing_bus(1);
        db->append_area(area);
    }

    {
        ZONE zone(db);
        zone.set_zone_number(1);
        zone.set_zone_name("ZONE A");
        db->append_zone(zone);

        zone.set_zone_number(2);
        zone.set_zone_name("ZONE B");
        db->append_zone(zone);

        zone.set_zone_number(3);
        zone.set_zone_name("ZONE C");
        db->append_zone(zone);
    }

    {
        OWNER owner(db);
        owner.set_owner_number(1);
        owner.set_owner_name("OWNER A");
        db->append_owner(owner);

        owner.set_owner_number(2);
        owner.set_owner_name("OWNER B");
        db->append_owner(owner);

        owner.set_owner_number(3);
        owner.set_owner_name("OWNER C");
        db->append_owner(owner);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_bus_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_bus_capacity(10000);
    TEST_ASSERT(db->get_bus_capacity()==10000);

    db->set_bus_capacity(1000);
    TEST_ASSERT(db->get_bus_capacity()==10000);

    db->set_bus_capacity(20000);
    TEST_ASSERT(db->get_bus_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_generator_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_generator_capacity(10000);
    TEST_ASSERT(db->get_generator_capacity()==10000);

    db->set_generator_capacity(1000);
    TEST_ASSERT(db->get_generator_capacity()==10000);

    db->set_generator_capacity(20000);
    TEST_ASSERT(db->get_generator_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_pe_source_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_pe_source_capacity(10000);
    TEST_ASSERT(db->get_pe_source_capacity()==10000);

    db->set_pe_source_capacity(1000);
    TEST_ASSERT(db->get_pe_source_capacity()==10000);

    db->set_pe_source_capacity(20000);
    TEST_ASSERT(db->get_pe_source_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_load_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_load_capacity(10000);
    TEST_ASSERT(db->get_load_capacity()==10000);

    db->set_load_capacity(1000);
    TEST_ASSERT(db->get_load_capacity()==10000);

    db->set_load_capacity(20000);
    TEST_ASSERT(db->get_load_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_fixed_shunt_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_fixed_shunt_capacity(10000);
    TEST_ASSERT(db->get_fixed_shunt_capacity()==10000);

    db->set_fixed_shunt_capacity(1000);
    TEST_ASSERT(db->get_fixed_shunt_capacity()==10000);

    db->set_fixed_shunt_capacity(20000);
    TEST_ASSERT(db->get_fixed_shunt_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_line_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_line_capacity(10000);
    TEST_ASSERT(db->get_line_capacity()==50000);

    db->set_line_capacity(1000);
    TEST_ASSERT(db->get_line_capacity()==50000);

    db->set_line_capacity(60000);
    TEST_ASSERT(db->get_line_capacity()==60000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_transformer_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_transformer_capacity(10000);
    TEST_ASSERT(db->get_transformer_capacity()==10000);

    db->set_transformer_capacity(1000);
    TEST_ASSERT(db->get_transformer_capacity()==10000);

    db->set_transformer_capacity(60000);
    TEST_ASSERT(db->get_transformer_capacity()==60000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_hvdc_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_hvdc_capacity(10000);
    TEST_ASSERT(db->get_hvdc_capacity()==10000);

    db->set_hvdc_capacity(1000);
    TEST_ASSERT(db->get_hvdc_capacity()==10000);

    db->set_hvdc_capacity(20000);
    TEST_ASSERT(db->get_hvdc_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_equivalent_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_equivalent_device_capacity(10000);
    TEST_ASSERT(db->get_equivalent_device_capacity()==10000);

    db->set_equivalent_device_capacity(1000);
    TEST_ASSERT(db->get_equivalent_device_capacity()==10000);

    db->set_equivalent_device_capacity(20000);
    TEST_ASSERT(db->get_equivalent_device_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_area_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_area_capacity(10000);
    TEST_ASSERT(db->get_area_capacity()==10000);

    db->set_area_capacity(1000);
    TEST_ASSERT(db->get_area_capacity()==10000);

    db->set_area_capacity(20000);
    TEST_ASSERT(db->get_area_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_zone_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_zone_capacity(10000);
    TEST_ASSERT(db->get_zone_capacity()==10000);

    db->set_zone_capacity(1000);
    TEST_ASSERT(db->get_zone_capacity()==10000);

    db->set_zone_capacity(20000);
    TEST_ASSERT(db->get_zone_capacity()==20000);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_owner_capacity()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_owner_capacity(10000);
    TEST_ASSERT(db->get_owner_capacity()==10000);

    db->set_owner_capacity(1000);
    TEST_ASSERT(db->get_owner_capacity()==10000);

    db->set_owner_capacity(20000);
    TEST_ASSERT(db->get_owner_capacity()==20000);
}


void POWER_SYSTEM_DATABASE_TEST::test_set_get_system_name()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_system_name("System Test");
    TEST_ASSERT(db->get_system_name()=="System Test");
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_allowed_max_bus_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);
    TEST_ASSERT(db->get_allowed_max_bus_number()==100);
    db->set_allowed_max_bus_number(10000);
    TEST_ASSERT(db->get_allowed_max_bus_number()==10000);
}

void POWER_SYSTEM_DATABASE_TEST::test_is_bus_in_allowed_range()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);
    TEST_ASSERT(db->is_bus_in_allowed_range(0)==false);
    TEST_ASSERT(db->is_bus_in_allowed_range(1)==true);
    TEST_ASSERT(db->is_bus_in_allowed_range(100)==true);
    TEST_ASSERT(db->is_bus_in_allowed_range(101)==false);
}


void POWER_SYSTEM_DATABASE_TEST::test_set_get_system_base_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_system_base_power_in_MVA(100.0);
    TEST_ASSERT(fabs(db->get_system_base_power_in_MVA()-100.0)<FLOAT_EPSILON);
    db->set_system_base_power_in_MVA(1000.0);
    TEST_ASSERT(fabs(db->get_system_base_power_in_MVA()-1000.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_set_get_system_base_frequency()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_system_base_frequency_in_Hz(50.0);
    TEST_ASSERT(fabs(db->get_system_base_frequency_in_Hz()-50.0)<FLOAT_EPSILON);
    db->set_system_base_frequency_in_Hz(60.0);
    TEST_ASSERT(fabs(db->get_system_base_frequency_in_Hz()-60.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);

    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(110.0);
    bus.set_voltage_in_pu(1.05);
    bus.set_angle_in_rad(0.5);

    db->append_bus(bus);

    bus.set_bus_number(2);
    bus.set_base_voltage_in_kV(220.0);
    bus.set_voltage_in_pu(0.95);
    bus.set_angle_in_rad(0.25);
    db->append_bus(bus);

    TEST_ASSERT(db->get_bus_count()==2);

    BUS* pbus;

    pbus = db->get_bus(1);
    TEST_ASSERT(pbus!=NULL);
    TEST_ASSERT(pbus->get_bus_number()==1);
    TEST_ASSERT(fabs(pbus->get_base_voltage_in_kV()-110.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_voltage_in_pu()-1.05)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_angle_in_rad()-0.5)<FLOAT_EPSILON);

    DEVICE_ID did;
    did.set_device_type("BUS");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);

    pbus = db->get_bus(did);
    TEST_ASSERT(pbus!=NULL);
    TEST_ASSERT(pbus->get_bus_number()==1);
    TEST_ASSERT(fabs(pbus->get_base_voltage_in_kV()-110.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_voltage_in_pu()-1.05)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_angle_in_rad()-0.5)<FLOAT_EPSILON);

    pbus = db->get_bus(2);
    TEST_ASSERT(pbus!=NULL);
    TEST_ASSERT(pbus->get_bus_number()==2);
    TEST_ASSERT(fabs(pbus->get_base_voltage_in_kV()-220.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_voltage_in_pu()-0.95)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_angle_in_rad()-0.25)<FLOAT_EPSILON);

    did.set_device_type("BUS");
    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);

    pbus = db->get_bus(did);
    TEST_ASSERT(pbus!=NULL);
    TEST_ASSERT(pbus->get_bus_number()==2);
    TEST_ASSERT(fabs(pbus->get_base_voltage_in_kV()-220.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_voltage_in_pu()-0.95)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(pbus->get_angle_in_rad()-0.25)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_generator()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(18.0);
    bus.set_voltage_in_pu(1.0);
    db->append_bus(bus);

    GENERATOR generator(db);
    generator.set_generator_bus(1);
    generator.set_identifier("#1");
    generator.set_status(true);

    db->append_generator(generator);

    generator.set_generator_bus(1);
    generator.set_identifier("#2");
    generator.set_status(false);

    db->append_generator(generator);

    TEST_ASSERT(db->get_generator_count()==2);

    GENERATOR* pgenerator;
    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    pgenerator = db->get_generator(did);

    TEST_ASSERT(pgenerator!=NULL);
    TEST_ASSERT(pgenerator->get_generator_bus()==1);
    TEST_ASSERT(pgenerator->get_identifier()=="#1");
    TEST_ASSERT(pgenerator->get_status()==true);

    did.set_device_identifier("#2");

    pgenerator = db->get_generator(did);

    TEST_ASSERT(pgenerator!=NULL);
    TEST_ASSERT(pgenerator->get_generator_bus()==1);
    TEST_ASSERT(pgenerator->get_identifier()=="#2");
    TEST_ASSERT(pgenerator->get_status()==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_pe_source()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(18.0);
    bus.set_voltage_in_pu(1.0);
    db->append_bus(bus);

    PE_SOURCE pesource(db);
    pesource.set_source_bus(1);
    pesource.set_identifier("#1");
    pesource.set_status(true);

    db->append_pe_source(pesource);

    pesource.set_source_bus(1);
    pesource.set_identifier("#2");
    pesource.set_status(false);

    db->append_pe_source(pesource);

    TEST_ASSERT(db->get_pe_source_count()==2);

    PE_SOURCE* ppesource;
    DEVICE_ID did;
    did.set_device_type("PE SOURCE");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    ppesource = db->get_pe_source(did);

    TEST_ASSERT(ppesource!=NULL);
    TEST_ASSERT(ppesource->get_source_bus()==1);
    TEST_ASSERT(ppesource->get_identifier()=="#1");
    TEST_ASSERT(ppesource->get_status()==true);

    did.set_device_identifier("#2");

    ppesource = db->get_pe_source(did);

    TEST_ASSERT(ppesource!=NULL);
    TEST_ASSERT(ppesource->get_source_bus()==1);
    TEST_ASSERT(ppesource->get_identifier()=="#2");
    TEST_ASSERT(ppesource->get_status()==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_load()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(35.0);
    bus.set_voltage_in_pu(1.0);
    db->append_bus(bus);

    LOAD load(db);
    load.set_load_bus(1);
    load.set_identifier("#1");
    load.set_status(true);

    db->append_load(load);

    load.set_load_bus(1);
    load.set_identifier("#2");
    load.set_status(false);

    db->append_load(load);

    TEST_ASSERT(db->get_load_count()==2);

    LOAD* pload;
    DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    pload = db->get_load(did);

    TEST_ASSERT(pload!=NULL);
    TEST_ASSERT(pload->get_load_bus()==1);
    TEST_ASSERT(pload->get_identifier()=="#1");
    TEST_ASSERT(pload->get_status()==true);

    did.set_device_identifier("#2");

    pload = db->get_load(did);

    TEST_ASSERT(pload!=NULL);
    TEST_ASSERT(pload->get_load_bus()==1);
    TEST_ASSERT(pload->get_identifier()=="#2");
    TEST_ASSERT(pload->get_status()==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_line()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(110.0);
    db->append_bus(bus);

    bus.set_bus_number(2);
    bus.set_base_voltage_in_kV(110.0);
    db->append_bus(bus);

    LINE line(db);
    line.set_sending_side_bus(1);
    line.set_receiving_side_bus(2);
    line.set_identifier("#1");
    line.set_sending_side_breaker_status(true);
    line.set_receiving_side_breaker_status(true);

    db->append_line(line);

    line.set_sending_side_bus(1);
    line.set_receiving_side_bus(2);
    line.set_identifier("#2");
    line.set_sending_side_breaker_status(true);
    line.set_receiving_side_breaker_status(false);

    db->append_line(line);

    TEST_ASSERT(db->get_line_count()==2);

    LINE* pline;
    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    pline = db->get_line(did);

    TEST_ASSERT(pline!=NULL);
    TEST_ASSERT(pline->get_sending_side_bus()==1);
    TEST_ASSERT(pline->get_receiving_side_bus()==2);
    TEST_ASSERT(pline->get_identifier()=="#1");
    TEST_ASSERT(pline->get_sending_side_breaker_status()==true);
    TEST_ASSERT(pline->get_receiving_side_breaker_status()==true);

    did.set_device_identifier("#2");

    pline = db->get_line(did);

    TEST_ASSERT(pline!=NULL);
    TEST_ASSERT(pline->get_sending_side_bus()==1);
    TEST_ASSERT(pline->get_receiving_side_bus()==2);
    TEST_ASSERT(pline->get_identifier()=="#2");
    TEST_ASSERT(pline->get_sending_side_breaker_status()==true);
    TEST_ASSERT(pline->get_receiving_side_breaker_status()==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_transformer()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(525.0);
    db->append_bus(bus);

    bus.set_bus_number(2);
    bus.set_base_voltage_in_kV(230.0);
    db->append_bus(bus);

    bus.set_bus_number(3);
    bus.set_base_voltage_in_kV(35.0);
    db->append_bus(bus);

    TRANSFORMER transformer(db);
    transformer.set_winding_bus(PRIMARY_SIDE, 1);
    transformer.set_winding_bus(SECONDARY_SIDE, 2);
    transformer.set_winding_bus(TERTIARY_SIDE, 0);
    transformer.set_identifier("#1");
    transformer.set_winding_breaker_status(PRIMARY_SIDE, true);
    transformer.set_winding_breaker_status(SECONDARY_SIDE, true);

    db->append_transformer(transformer);

    transformer.set_winding_bus(PRIMARY_SIDE, 1);
    transformer.set_winding_bus(SECONDARY_SIDE, 2);
    transformer.set_winding_bus(TERTIARY_SIDE, 3);
    transformer.set_identifier("#2");
    transformer.set_winding_breaker_status(PRIMARY_SIDE, true);
    transformer.set_winding_breaker_status(SECONDARY_SIDE, true);
    transformer.set_winding_breaker_status(TERTIARY_SIDE, true);

    db->append_transformer(transformer);

    TEST_ASSERT(db->get_transformer_count()==2);

    TRANSFORMER* ptransformer;
    DEVICE_ID did;
    did.set_device_type("TRANSFORMER");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    ptransformer = db->get_transformer(did);

    TEST_ASSERT(ptransformer!=NULL);
    TEST_ASSERT(ptransformer->is_two_winding_transformer()==true);
    TEST_ASSERT(ptransformer->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(ptransformer->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(ptransformer->get_identifier()=="#1");
    TEST_ASSERT(ptransformer->get_winding_breaker_status(PRIMARY_SIDE)==true);
    TEST_ASSERT(ptransformer->get_winding_breaker_status(SECONDARY_SIDE)==true);

    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#2");

    ptransformer = db->get_transformer(did);

    TEST_ASSERT(ptransformer!=NULL);
    TEST_ASSERT(ptransformer->is_three_winding_transformer()==true);
    TEST_ASSERT(ptransformer->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(ptransformer->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(ptransformer->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(ptransformer->get_identifier()=="#2");
    TEST_ASSERT(ptransformer->get_winding_breaker_status(PRIMARY_SIDE)==true);
    TEST_ASSERT(ptransformer->get_winding_breaker_status(SECONDARY_SIDE)==true);
    TEST_ASSERT(ptransformer->get_winding_breaker_status(TERTIARY_SIDE)==true);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_fixed_shunt()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(110.0);
    db->append_bus(bus);

    FIXED_SHUNT shunt(db);
    shunt.set_shunt_bus(1);
    shunt.set_identifier("#1");
    shunt.set_status(true);

    db->append_fixed_shunt(shunt);

    shunt.set_shunt_bus(1);
    shunt.set_identifier("#2");
    shunt.set_status(false);

    db->append_fixed_shunt(shunt);

    TEST_ASSERT(db->get_fixed_shunt_count()==2);

    FIXED_SHUNT* pshunt;
    DEVICE_ID did;
    did.set_device_type("FIXED SHUNT");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    pshunt = db->get_fixed_shunt(did);

    TEST_ASSERT(pshunt!=NULL);
    TEST_ASSERT(pshunt->get_shunt_bus()==1);
    TEST_ASSERT(pshunt->get_identifier()=="#1");
    TEST_ASSERT(pshunt->get_status()==true);

    did.set_device_identifier("#2");

    pshunt = db->get_fixed_shunt(did);

    TEST_ASSERT(pshunt!=NULL);
    TEST_ASSERT(pshunt->get_shunt_bus()==1);
    TEST_ASSERT(pshunt->get_identifier()=="#2");
    TEST_ASSERT(pshunt->get_status()==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_hvdc()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(525.0);
    db->append_bus(bus);

    bus.set_bus_number(2);
    bus.set_base_voltage_in_kV(525.0);
    db->append_bus(bus);

    HVDC hvdc(db);
    hvdc.set_name("DC1");
    hvdc.set_converter_bus(RECTIFIER, 1);
    hvdc.set_converter_bus(INVERTER, 2);
    hvdc.set_identifier("#1");
    hvdc.set_status(true);

    db->append_hvdc(hvdc);

    hvdc.set_name("DC2");
    hvdc.set_converter_bus(RECTIFIER, 1);
    hvdc.set_converter_bus(INVERTER, 2);
    hvdc.set_identifier("#2");
    hvdc.set_status(false);

    db->append_hvdc(hvdc);

    TEST_ASSERT(db->get_hvdc_count()==2);

    HVDC* phvdc;
    DEVICE_ID did;
    did.set_device_type("HVDC");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    phvdc = db->get_hvdc(did);

    TEST_ASSERT(phvdc!=NULL);
    TEST_ASSERT(phvdc->get_name()=="DC1");
    TEST_ASSERT(phvdc->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(phvdc->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(phvdc->get_identifier()=="#1");
    TEST_ASSERT(phvdc->get_status()==true);

    did.set_device_identifier("#2");
    phvdc = db->get_hvdc(did);

    TEST_ASSERT(phvdc!=NULL);
    TEST_ASSERT(phvdc->get_name()=="DC2");
    TEST_ASSERT(phvdc->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(phvdc->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(phvdc->get_identifier()=="#2");
    TEST_ASSERT(phvdc->get_status()==false);
}


void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_equivalent_device()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_base_voltage_in_kV(525.0);
    db->append_bus(bus);

    EQUIVALENT_DEVICE edevice(db);
    edevice.set_equivalent_device_bus(1);
    edevice.set_identifier("#1");
    edevice.set_status(true);

    db->append_equivalent_device(edevice);

    edevice.set_identifier("#2");
    edevice.set_status(false);

    db->append_equivalent_device(edevice);

    TEST_ASSERT(db->get_equivalent_device_count()==2);

    EQUIVALENT_DEVICE* pedevice;
    DEVICE_ID did;
    did.set_device_type("EQUIVALENT DEVICE");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    pedevice = db->get_equivalent_device(did);

    TEST_ASSERT(pedevice!=NULL);
    TEST_ASSERT(pedevice->get_equivalent_device_bus()==1);
    TEST_ASSERT(pedevice->get_identifier()=="#1");
    TEST_ASSERT(pedevice->get_status()==true);

    did.set_device_identifier("#2");
    pedevice = db->get_equivalent_device(did);

    TEST_ASSERT(pedevice!=NULL);
    TEST_ASSERT(pedevice->get_equivalent_device_bus()==1);
    TEST_ASSERT(pedevice->get_identifier()=="#2");
    TEST_ASSERT(pedevice->get_status()==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    BUS bus(db);
    bus.set_bus_number(1);
    bus.set_area_number(1);
    bus.set_base_voltage_in_kV(525.0);
    bus.set_bus_type(SLACK_TYPE);
    db->append_bus(bus);

    bus.set_bus_number(2);
    bus.set_area_number(2);
    bus.set_base_voltage_in_kV(525.0);
    bus.set_bus_type(SLACK_TYPE);
    db->append_bus(bus);

    AREA area(db);
    area.set_area_number(1);
    area.set_area_name("area 1");
    area.set_area_swing_bus(1);
    area.set_expected_power_leaving_area_in_MW(20.0);
    db->append_area(area);

    TEST_ASSERT(db->get_area_count()==1);

    AREA* parea;

    parea = db->get_area(1);

    TEST_ASSERT(parea!=NULL);
    TEST_ASSERT(parea->get_area_number()==1);
    TEST_ASSERT(parea->get_area_name()=="area 1");
    TEST_ASSERT(parea->get_area_swing_bus()==1);
    TEST_ASSERT(fabs(parea->get_expected_power_leaving_area_in_MW()-20.0)<FLOAT_EPSILON);


    area.set_area_number(2);
    area.set_area_name("area 2");
    area.set_area_swing_bus(2);
    area.set_expected_power_leaving_area_in_MW(20.0);
    db->append_area(area);

    TEST_ASSERT(db->get_area_count()==2);

    parea = db->get_area(2);

    TEST_ASSERT(parea!=NULL);
    TEST_ASSERT(parea->get_area_number()==2);
    TEST_ASSERT(parea->get_area_name()=="area 2");
    TEST_ASSERT(parea->get_area_swing_bus()==2);
    TEST_ASSERT(fabs(parea->get_expected_power_leaving_area_in_MW()-20.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    ZONE zone(db);
    zone.set_zone_number(1);
    zone.set_zone_name("zone 1");
    db->append_zone(zone);

    TEST_ASSERT(db->get_zone_count()==1);

    ZONE* pzone;

    pzone = db->get_zone(1);

    TEST_ASSERT(pzone!=NULL);
    TEST_ASSERT(pzone->get_zone_number()==1);
    TEST_ASSERT(pzone->get_zone_name()=="zone 1");

    zone.set_zone_number(2);
    zone.set_zone_name("zone 2");
    db->append_zone(zone);

    TEST_ASSERT(db->get_zone_count()==2);

    pzone = db->get_zone(2);

    TEST_ASSERT(pzone!=NULL);
    TEST_ASSERT(pzone->get_zone_number()==2);
    TEST_ASSERT(pzone->get_zone_name()=="zone 2");
}

void POWER_SYSTEM_DATABASE_TEST::test_append_and_get_owner()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    db->set_allowed_max_bus_number(100);

    OWNER owner(db);
    owner.set_owner_number(1);
    owner.set_owner_name("owner 1");
    db->append_owner(owner);

    TEST_ASSERT(db->get_owner_count()==1);

    OWNER* powner;

    powner = db->get_owner(1);

    TEST_ASSERT(powner!=NULL);
    TEST_ASSERT(powner->get_owner_number()==1);
    TEST_ASSERT(powner->get_owner_name()=="owner 1");

    owner.set_owner_number(2);
    owner.set_owner_name("owner 2");
    db->append_owner(owner);

    TEST_ASSERT(db->get_owner_count()==2);

    powner = db->get_owner(2);

    TEST_ASSERT(powner!=NULL);
    TEST_ASSERT(powner->get_owner_number()==2);
    TEST_ASSERT(powner->get_owner_name()=="owner 2");
}


void POWER_SYSTEM_DATABASE_TEST::test_is_bus_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->is_bus_exist(1)==true);
    TEST_ASSERT(db->is_bus_exist(2)==true);
    TEST_ASSERT(db->is_bus_exist(3)==true);
    TEST_ASSERT(db->is_bus_exist(4)==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_is_generator_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(db->is_generator_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_generator_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_generator_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_pe_source_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("PE SOURCE");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");
        TEST_ASSERT(db->is_pe_source_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_pe_source_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_pe_source_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_load_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(db->is_load_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_load_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_load_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_line_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        if(i==1)
        {
            terminal.append_bus(1);
            terminal.append_bus(2);
        }
        if(i==2)
        {
            terminal.append_bus(2);
            terminal.append_bus(3);
        }
        if(i==3)
        {
            terminal.append_bus(1);
            terminal.append_bus(3);
        }
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(db->is_line_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_line_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_line_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_transformer_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("TRANSFORMER");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        if(i==1)
        {
            terminal.append_bus(1);
            terminal.append_bus(2);
        }
        if(i==2)
        {
            terminal.append_bus(2);
            terminal.append_bus(3);
        }
        if(i==3)
        {
            terminal.append_bus(1);
            terminal.append_bus(3);
        }
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");
        TEST_ASSERT(db->is_transformer_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_transformer_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_transformer_exist(did)==false);
    }

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_transformer_exist(did)==true);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->is_transformer_exist(did)==true);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->is_transformer_exist(did)==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_is_fixed_shunt_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("FIXED SHUNT");
    TERMINAL terminal;
    for(size_t i=1; i!=4; i++)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(db->is_fixed_shunt_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_fixed_shunt_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_hvdc_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("HVDC");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        if(i==1)
        {
            terminal.append_bus(1);
            terminal.append_bus(2);
        }
        if(i==2)
        {
            terminal.append_bus(2);
            terminal.append_bus(3);
        }
        if(i==3)
        {
            terminal.append_bus(1);
            terminal.append_bus(3);
        }
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(db->is_hvdc_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_hvdc_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_hvdc_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_equivalent_device_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("EQUIVALENT DEVICE");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(db->is_equivalent_device_exist(did)==true);

        did.set_device_identifier("#2");
        TEST_ASSERT(db->is_equivalent_device_exist(did)==true);

        did.set_device_identifier("#3");
        TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_is_area_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    for(size_t i=1; i!=4; ++i)
        TEST_ASSERT(db->is_area_exist(i)==true);

    TEST_ASSERT(db->is_area_exist(4)==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_is_zone_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    for(size_t i=1; i!=4; ++i)
        TEST_ASSERT(db->is_zone_exist(i)==true);
    TEST_ASSERT(db->is_zone_exist(4)==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_is_owner_exist()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    for(size_t i=1; i!=4; ++i)
        TEST_ASSERT(db->is_owner_exist(i)==true);
    TEST_ASSERT(db->is_owner_exist(4)==false);
}

void POWER_SYSTEM_DATABASE_TEST::test_change_bus_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");
    ostringstream sstream;
    sstream<<"Known bug of change_bus_number(): only terminal bus can be changed. buses for additional control, i.e., generator control bus is not changed.";
    show_information_with_leading_time_stamp(sstream);

    prepare_database_for_test();

    TEST_ASSERT(db->is_bus_exist(1)==true);
    TEST_ASSERT(db->is_bus_exist(2)==true);
    TEST_ASSERT(db->is_bus_exist(3)==true);
    TEST_ASSERT(db->is_bus_exist(4)==false);

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_generator_exist(did)==true);

    did.set_device_type("LOAD");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_load_exist(did)==true);

    did.set_device_type("FIXED SHUNT");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==true);

    did.set_device_type("LINE");
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_line_exist(did)==true);

    did.set_device_type("HVDC");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_hvdc_exist(did)==true);

    did.set_device_type("TRANSFORMER");
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_transformer_exist(did)==true);

    db->change_bus_number(1, 4);

    TEST_ASSERT(db->is_bus_exist(1)==false);
    TEST_ASSERT(db->is_bus_exist(2)==true);
    TEST_ASSERT(db->is_bus_exist(3)==true);
    TEST_ASSERT(db->is_bus_exist(4)==true);

    did.set_device_type("GENERATOR");
    terminal.clear();
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_generator_exist(did)==false);

    did.set_device_type("LOAD");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_load_exist(did)==false);

    did.set_device_type("FIXED SHUNT");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);

    did.set_device_type("LINE");
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_line_exist(did)==false);

    did.set_device_type("HVDC");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_hvdc_exist(did)==false);

    did.set_device_type("TRANSFORMER");
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_transformer_exist(did)==false);

    did.set_device_type("GENERATOR");
    terminal.clear();
    terminal.append_bus(4);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_generator_exist(did)==true);

    did.set_device_type("LOAD");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_load_exist(did)==true);

    did.set_device_type("FIXED SHUNT");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==true);

    did.set_device_type("LINE");
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_line_exist(did)==true);

    did.set_device_type("HVDC");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_hvdc_exist(did)==true);

    did.set_device_type("TRANSFORMER");
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_transformer_exist(did)==true);

    db->change_bus_number(2, 1);

    TEST_ASSERT(db->is_bus_exist(1)==true);
    TEST_ASSERT(db->is_bus_exist(2)==false);
    TEST_ASSERT(db->is_bus_exist(3)==true);
    TEST_ASSERT(db->is_bus_exist(4)==true);

    did.set_device_type("GENERATOR");
    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_generator_exist(did)==false);

    did.set_device_type("LOAD");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_load_exist(did)==false);

    did.set_device_type("FIXED SHUNT");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);

    did.set_device_type("LINE");
    terminal.append_bus(4);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_line_exist(did)==false);

    did.set_device_type("HVDC");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_hvdc_exist(did)==false);

    did.set_device_type("TRANSFORMER");
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_transformer_exist(did)==false);

    did.set_device_type("GENERATOR");
    terminal.clear();
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_generator_exist(did)==true);

    did.set_device_type("LOAD");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_load_exist(did)==true);

    did.set_device_type("FIXED SHUNT");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==true);

    did.set_device_type("LINE");
    terminal.append_bus(4);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_line_exist(did)==true);

    did.set_device_type("HVDC");
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_hvdc_exist(did)==true);

    did.set_device_type("TRANSFORMER");
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->is_transformer_exist(did)==true);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generators_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> device;

    for(size_t i=1; i!=4; ++i)
    {
        device = db->get_generators_connecting_to_bus(i);

        TEST_ASSERT(device.size()==2);

        TEST_ASSERT(device[0]->get_generator_bus()==i);
        TEST_ASSERT(device[0]->get_identifier()=="#1");
        TEST_ASSERT(device[1]->get_generator_bus()==i);
        TEST_ASSERT(device[1]->get_identifier()=="#2");
    }

    device = db->get_generators_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> device;
    for(size_t i=1; i!=4; ++i)
    {
        device = db->get_pe_sources_connecting_to_bus(i);

        TEST_ASSERT(device.size()==2);

        TEST_ASSERT(device[0]->get_source_bus()==i);
        TEST_ASSERT(device[0]->get_identifier()=="#1");
        TEST_ASSERT(device[1]->get_source_bus()==i);
        TEST_ASSERT(device[1]->get_identifier()=="#2");
    }

    device = db->get_pe_sources_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_sources_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> device;
    for(size_t i=1; i!=4; ++i)
    {
        device = db->get_sources_connecting_to_bus(i);

        TEST_ASSERT(device.size()==4);

        TEST_ASSERT(device[0]->get_source_bus()==i);
        TEST_ASSERT(device[0]->get_identifier()=="#1");
        TEST_ASSERT(device[1]->get_source_bus()==i);
        TEST_ASSERT(device[1]->get_identifier()=="#2");
        TEST_ASSERT(device[2]->get_source_bus()==i);
        TEST_ASSERT(device[2]->get_identifier()=="#1");
        TEST_ASSERT(device[3]->get_source_bus()==i);
        TEST_ASSERT(device[3]->get_identifier()=="#2");
    }

    device = db->get_sources_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_loads_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> device;
    for(size_t i=1; i!=4; ++i)
    {
        device = db->get_loads_connecting_to_bus(i);

        TEST_ASSERT(device.size()==2);

        TEST_ASSERT(device[0]->get_load_bus()==i);
        TEST_ASSERT(device[0]->get_identifier()=="#1");
        TEST_ASSERT(device[1]->get_load_bus()==i);
        TEST_ASSERT(device[1]->get_identifier()=="#2");
    }

    device = db->get_loads_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_lines_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LINE*> device = db->get_lines_connecting_to_bus(1);

    TEST_ASSERT(device.size()==4);

    TEST_ASSERT(device[0]->get_sending_side_bus()==1);
    TEST_ASSERT(device[0]->get_receiving_side_bus()==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_sending_side_bus()==1);
    TEST_ASSERT(device[1]->get_receiving_side_bus()==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_sending_side_bus()==1);
    TEST_ASSERT(device[2]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_sending_side_bus()==1);
    TEST_ASSERT(device[3]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");

    device = db->get_lines_connecting_to_bus(2);

    TEST_ASSERT(device.size()==4);

    TEST_ASSERT(device[0]->get_sending_side_bus()==1);
    TEST_ASSERT(device[0]->get_receiving_side_bus()==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_sending_side_bus()==1);
    TEST_ASSERT(device[1]->get_receiving_side_bus()==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_sending_side_bus()==2);
    TEST_ASSERT(device[2]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_sending_side_bus()==2);
    TEST_ASSERT(device[3]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");

    device = db->get_lines_connecting_to_bus(3);
    TEST_ASSERT(device.size()==4);

    TEST_ASSERT(device[0]->get_sending_side_bus()==2);
    TEST_ASSERT(device[0]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_sending_side_bus()==2);
    TEST_ASSERT(device[1]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_sending_side_bus()==1);
    TEST_ASSERT(device[2]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_sending_side_bus()==1);
    TEST_ASSERT(device[3]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");

    device = db->get_lines_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformers_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<TRANSFORMER*> device = db->get_transformers_connecting_to_bus(1);

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[0]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[0]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[1]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[1]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[2]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[2]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[3]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[3]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[4]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[4]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[4]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[5]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[5]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[5]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");

    device = db->get_transformers_connecting_to_bus(2);

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[0]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[0]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[1]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[1]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[2]->get_winding_bus(PRIMARY_SIDE)==2);
    TEST_ASSERT(device[2]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[3]->get_winding_bus(PRIMARY_SIDE)==2);
    TEST_ASSERT(device[3]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[4]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[4]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[4]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[5]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[5]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[5]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");

    device = db->get_transformers_connecting_to_bus(3);

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[0]->get_winding_bus(PRIMARY_SIDE)==2);
    TEST_ASSERT(device[0]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[1]->get_winding_bus(PRIMARY_SIDE)==2);
    TEST_ASSERT(device[1]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[2]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[2]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[3]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[3]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[4]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[4]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[4]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[5]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[5]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[5]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");

    device = db->get_transformers_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<FIXED_SHUNT*> device;
    for(size_t i=1; i!=4; ++i)
    {
        device = db->get_fixed_shunts_connecting_to_bus(i);

        TEST_ASSERT(device.size()==2);

        TEST_ASSERT(device[0]->get_shunt_bus()==i);
        TEST_ASSERT(device[0]->get_identifier()=="#1");
        TEST_ASSERT(device[1]->get_shunt_bus()==i);
        TEST_ASSERT(device[1]->get_identifier()=="#2");
    }

    device = db->get_fixed_shunts_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<HVDC*> device = db->get_hvdcs_connecting_to_bus(1);

    TEST_ASSERT(device.size()==4);

    TEST_ASSERT(device[0]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[0]->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[1]->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[2]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[3]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");

    device = db->get_hvdcs_connecting_to_bus(2);

    TEST_ASSERT(device.size()==4);

    TEST_ASSERT(device[0]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[0]->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[1]->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_converter_bus(RECTIFIER)==2);
    TEST_ASSERT(device[2]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_converter_bus(RECTIFIER)==2);
    TEST_ASSERT(device[3]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");

    device = db->get_hvdcs_connecting_to_bus(3);

    TEST_ASSERT(device.size()==4);

    TEST_ASSERT(device[0]->get_converter_bus(RECTIFIER)==2);
    TEST_ASSERT(device[0]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_converter_bus(RECTIFIER)==2);
    TEST_ASSERT(device[1]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[2]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[3]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");

    device = db->get_hvdcs_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<EQUIVALENT_DEVICE*> device;
    for(size_t i=1; i!=4; ++i)
    {
        device = db->get_equivalent_devices_connecting_to_bus(i);

        TEST_ASSERT(device.size()==2);

        TEST_ASSERT(device[0]->get_equivalent_device_bus()==i);
        TEST_ASSERT(device[0]->get_identifier()=="#1");
        TEST_ASSERT(device[1]->get_equivalent_device_bus()==i);
        TEST_ASSERT(device[1]->get_identifier()=="#2");
    }

    device = db->get_equivalent_devices_connecting_to_bus(4);
    TEST_ASSERT(device.size()==0);
}



void POWER_SYSTEM_DATABASE_TEST::test_get_generators_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_generators_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="GENERATOR");
            TEST_ASSERT(db->get_generator(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_pe_sources_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="PE SOURCE");
            TEST_ASSERT(db->get_pe_source(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_sources_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_sources_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="GENERATOR" or dids[j].get_device_type()=="PE SOURCE" );
            TEST_ASSERT(db->get_source(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_loads_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_loads_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="LOAD");
            TEST_ASSERT(db->get_load(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_lines_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_lines_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="LINE");
            TEST_ASSERT(db->get_line(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformers_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_transformers_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==6);
        for(size_t j=0; j!=6; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="TRANSFORMER");
            TEST_ASSERT(db->get_transformer(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_fixed_shunts_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="FIXED SHUNT");
            TEST_ASSERT(db->get_fixed_shunt(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_hvdcs_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="HVDC");
            TEST_ASSERT(db->get_hvdc(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_device_id_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> dids;

    for(size_t i=1; i!=4; ++i)
    {
        dids = db->get_equivalent_devices_device_id_connecting_to_bus(i);
        TEST_ASSERT(dids.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(dids[j].get_device_type()=="EQUIVALENT DEVICE");
            TEST_ASSERT(db->get_equivalent_device(dids[j])->is_connected_to_bus(i)==true);
        }
    }
}


void POWER_SYSTEM_DATABASE_TEST::test_get_buses_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<BUS*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_buses_in_area(i);
        TEST_ASSERT(devices.size()==1);
        for(size_t j=0; j!=1; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="BUS");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generators_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_generators_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="GENERATOR");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_pe_sources_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="PE SOURCE");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_sources_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_sources_in_area(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="GENERATOR" or devices[j]->get_device_id().get_device_type()=="PE SOURCE");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_loads_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_loads_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="LOAD");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_lines_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LINE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_lines_in_area(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="LINE");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformers_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<TRANSFORMER*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_transformers_in_area(i);
        TEST_ASSERT(devices.size()==6);
        for(size_t j=0; j!=6; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="TRANSFORMER");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<FIXED_SHUNT*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_fixed_shunts_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="FIXED SHUNT");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<HVDC*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_hvdcs_in_area(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="HVDC");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<EQUIVALENT_DEVICE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_equivalent_devices_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="EQUIVALENT DEVICE");
            TEST_ASSERT(devices[j]->is_in_area(i)==true);
        }
    }
}


void POWER_SYSTEM_DATABASE_TEST::test_get_buses_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_buses_device_id_in_area(i);
        TEST_ASSERT(devices.size()==1);
        for(size_t j=0; j!=1; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="BUS");
            TEST_ASSERT(db->get_bus(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generators_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_generators_device_id_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="GENERATOR");
            TEST_ASSERT(db->get_generator(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_pe_sources_device_id_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="PE SOURCE");
            TEST_ASSERT(db->get_pe_source(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_sources_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_sources_device_id_in_area(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="GENERATOR" or devices[j].get_device_type()=="PE SOURCE");
            TEST_ASSERT(db->get_source(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_loads_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_loads_device_id_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="LOAD");
            TEST_ASSERT(db->get_load(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_lines_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_lines_device_id_in_area(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="LINE");
            TEST_ASSERT(db->get_line(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformers_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_transformers_device_id_in_area(i);
        TEST_ASSERT(devices.size()==6);
        for(size_t j=0; j!=6; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="TRANSFORMER");
            TEST_ASSERT(db->get_transformer(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_fixed_shunts_device_id_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="FIXED SHUNT");
            TEST_ASSERT(db->get_fixed_shunt(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_hvdcs_device_id_in_area(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="HVDC");
            TEST_ASSERT(db->get_hvdc(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_device_id_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_equivalent_devices_device_id_in_area(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="EQUIVALENT DEVICE");
            TEST_ASSERT(db->get_equivalent_device(devices[j])->is_in_area(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_buses_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<BUS*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_buses_in_zone(i);
        TEST_ASSERT(devices.size()==1);
        for(size_t j=0; j!=1; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="BUS");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generators_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_generators_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="GENERATOR");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_pe_sources_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="PE SOURCE");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_sources_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_sources_in_zone(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="GENERATOR" or devices[j]->get_device_id().get_device_type()=="PE SOURCE");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_loads_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_loads_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="LOAD");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_lines_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LINE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_lines_in_zone(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="LINE");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformers_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<TRANSFORMER*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_transformers_in_zone(i);
        TEST_ASSERT(devices.size()==6);
        for(size_t j=0; j!=6; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="TRANSFORMER");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<FIXED_SHUNT*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_fixed_shunts_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="FIXED SHUNT");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<HVDC*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_hvdcs_in_zone(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="HVDC");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<EQUIVALENT_DEVICE*> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_equivalent_devices_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j]->get_device_id().get_device_type()=="EQUIVALENT DEVICE");
            TEST_ASSERT(devices[j]->is_in_zone(i)==true);
        }
    }
}


void POWER_SYSTEM_DATABASE_TEST::test_get_buses_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_buses_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==1);
        for(size_t j=0; j!=1; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="BUS");
            TEST_ASSERT(db->get_bus(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generators_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_generators_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="GENERATOR");
            TEST_ASSERT(db->get_generator(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_sources_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_pe_sources_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="PE SOURCE");
            TEST_ASSERT(db->get_pe_source(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_sources_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_sources_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="GENERATOR" or devices[j].get_device_type()=="PE SOURCE");
            TEST_ASSERT(db->get_source(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_loads_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_loads_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="LOAD");
            TEST_ASSERT(db->get_load(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_lines_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_lines_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="LINE");
            TEST_ASSERT(db->get_line(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformers_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_transformers_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==6);
        for(size_t j=0; j!=6; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="TRANSFORMER");
            TEST_ASSERT(db->get_transformer(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunts_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_fixed_shunts_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="FIXED SHUNT");
            TEST_ASSERT(db->get_fixed_shunt(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdcs_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_hvdcs_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==4);
        for(size_t j=0; j!=4; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="HVDC");
            TEST_ASSERT(db->get_hvdc(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_devices_device_id_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> devices;

    for(size_t i=1; i!=3; ++i)
    {
        devices = db->get_equivalent_devices_device_id_in_zone(i);
        TEST_ASSERT(devices.size()==2);
        for(size_t j=0; j!=2; ++j)
        {
            TEST_ASSERT(devices[j].get_device_type()=="EQUIVALENT DEVICE");
            TEST_ASSERT(db->get_equivalent_device(devices[j])->is_in_zone(i)==true);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_buses()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<BUS*> device = db->get_all_buses();

    TEST_ASSERT(device.size()==3);
    TEST_ASSERT(device[0]->get_bus_number()==1);
    TEST_ASSERT(device[1]->get_bus_number()==2);
    TEST_ASSERT(device[2]->get_bus_number()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_in_service_buses()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<BUS*> device = db->get_all_in_service_buses();

    TEST_ASSERT(device.size()==3);
    TEST_ASSERT(device[0]->get_bus_number()==1);
    TEST_ASSERT(device[1]->get_bus_number()==2);
    TEST_ASSERT(device[2]->get_bus_number()==3);

    BUS* bus = db->get_bus(2);
    bus->set_bus_type(OUT_OF_SERVICE);

    device = db->get_all_in_service_buses();

    TEST_ASSERT(device.size()==2);
    TEST_ASSERT(device[0]->get_bus_number()==1);
    TEST_ASSERT(device[1]->get_bus_number()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_generators()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> device = db->get_all_generators();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_generator_bus()==1);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_generator_bus()==1);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_generator_bus()==2);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_generator_bus()==2);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_generator_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_generator_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_pe_sources()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> device = db->get_all_pe_sources();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_source_bus()==1);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_source_bus()==1);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_source_bus()==2);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_source_bus()==2);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_source_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_source_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_sources()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> device = db->get_all_sources();

    TEST_ASSERT(device.size()==12);

    TEST_ASSERT(device[0]->get_source_bus()==1);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_source_bus()==1);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_source_bus()==2);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_source_bus()==2);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_source_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_source_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
    TEST_ASSERT(device[6]->get_source_bus()==1);
    TEST_ASSERT(device[6]->get_identifier()=="#1");
    TEST_ASSERT(device[7]->get_source_bus()==1);
    TEST_ASSERT(device[7]->get_identifier()=="#2");
    TEST_ASSERT(device[8]->get_source_bus()==2);
    TEST_ASSERT(device[8]->get_identifier()=="#1");
    TEST_ASSERT(device[9]->get_source_bus()==2);
    TEST_ASSERT(device[9]->get_identifier()=="#2");
    TEST_ASSERT(device[10]->get_source_bus()==3);
    TEST_ASSERT(device[10]->get_identifier()=="#1");
    TEST_ASSERT(device[11]->get_source_bus()==3);
    TEST_ASSERT(device[11]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_loads()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> device = db->get_all_loads();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_load_bus()==1);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_load_bus()==1);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_load_bus()==2);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_load_bus()==2);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_load_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_load_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_lines()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LINE*> device = db->get_all_lines();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_sending_side_bus()==1);
    TEST_ASSERT(device[0]->get_receiving_side_bus()==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_sending_side_bus()==1);
    TEST_ASSERT(device[1]->get_receiving_side_bus()==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_sending_side_bus()==2);
    TEST_ASSERT(device[2]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_sending_side_bus()==2);
    TEST_ASSERT(device[3]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_sending_side_bus()==1);
    TEST_ASSERT(device[4]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_sending_side_bus()==1);
    TEST_ASSERT(device[5]->get_receiving_side_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_transformers()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<TRANSFORMER*> device = db->get_all_transformers();

    TEST_ASSERT(device.size()==8);

    TEST_ASSERT(device[0]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[0]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[0]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[1]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[1]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[2]->get_winding_bus(PRIMARY_SIDE)==2);
    TEST_ASSERT(device[2]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[3]->get_winding_bus(PRIMARY_SIDE)==2);
    TEST_ASSERT(device[3]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[4]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[4]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->is_two_winding_transformer()==true);
    TEST_ASSERT(device[5]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[5]->get_winding_bus(SECONDARY_SIDE)==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
    TEST_ASSERT(device[6]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[6]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[6]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[6]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[6]->get_identifier()=="#1");
    TEST_ASSERT(device[7]->is_three_winding_transformer()==true);
    TEST_ASSERT(device[7]->get_winding_bus(PRIMARY_SIDE)==1);
    TEST_ASSERT(device[7]->get_winding_bus(SECONDARY_SIDE)==2);
    TEST_ASSERT(device[7]->get_winding_bus(TERTIARY_SIDE)==3);
    TEST_ASSERT(device[7]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_fixed_shunts()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<FIXED_SHUNT*> device = db->get_all_fixed_shunts();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_shunt_bus()==1);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_shunt_bus()==1);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_shunt_bus()==2);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_shunt_bus()==2);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_shunt_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_shunt_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_hvdcs()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<HVDC*> device = db->get_all_hvdcs();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[0]->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[1]->get_converter_bus(INVERTER)==2);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_converter_bus(RECTIFIER)==2);
    TEST_ASSERT(device[2]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_converter_bus(RECTIFIER)==2);
    TEST_ASSERT(device[3]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[4]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_converter_bus(RECTIFIER)==1);
    TEST_ASSERT(device[5]->get_converter_bus(INVERTER)==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_equivalent_devices()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<EQUIVALENT_DEVICE*> device = db->get_all_equivalent_devices();

    TEST_ASSERT(device.size()==6);

    TEST_ASSERT(device[0]->get_equivalent_device_bus()==1);
    TEST_ASSERT(device[0]->get_identifier()=="#1");
    TEST_ASSERT(device[1]->get_equivalent_device_bus()==1);
    TEST_ASSERT(device[1]->get_identifier()=="#2");
    TEST_ASSERT(device[2]->get_equivalent_device_bus()==2);
    TEST_ASSERT(device[2]->get_identifier()=="#1");
    TEST_ASSERT(device[3]->get_equivalent_device_bus()==2);
    TEST_ASSERT(device[3]->get_identifier()=="#2");
    TEST_ASSERT(device[4]->get_equivalent_device_bus()==3);
    TEST_ASSERT(device[4]->get_identifier()=="#1");
    TEST_ASSERT(device[5]->get_equivalent_device_bus()==3);
    TEST_ASSERT(device[5]->get_identifier()=="#2");
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_areas()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<AREA*> areas = db->get_all_areas();

    TEST_ASSERT(areas.size()==3);

    TEST_ASSERT(areas[0]->get_area_number()==1);
    TEST_ASSERT(areas[1]->get_area_number()==2);
    TEST_ASSERT(areas[2]->get_area_number()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_zones()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<ZONE*> zones = db->get_all_zones();

    TEST_ASSERT(zones.size()==3);

    TEST_ASSERT(zones[0]->get_zone_number()==1);
    TEST_ASSERT(zones[1]->get_zone_number()==2);
    TEST_ASSERT(zones[2]->get_zone_number()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_owners()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<OWNER*> owners = db->get_all_owners();

    TEST_ASSERT(owners.size()==3);

    TEST_ASSERT(owners[0]->get_owner_number()==1);
    TEST_ASSERT(owners[1]->get_owner_number()==2);
    TEST_ASSERT(owners[2]->get_owner_number()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_buses_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<size_t> buses = db->get_all_buses_number();

    TEST_ASSERT(buses.size()==3);
    TEST_ASSERT(buses[0]==1);
    TEST_ASSERT(buses[1]==2);
    TEST_ASSERT(buses[2]==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_in_service_buses_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<size_t> buses = db->get_all_in_service_buses_number();

    TEST_ASSERT(buses.size()==3);
    TEST_ASSERT(buses[0]==1);
    TEST_ASSERT(buses[1]==2);
    TEST_ASSERT(buses[2]==3);

    BUS* bus = db->get_bus(2);
    bus->set_bus_type(OUT_OF_SERVICE);

    buses = db->get_all_in_service_buses_number();

    TEST_ASSERT(buses.size()==2);
    TEST_ASSERT(buses[0]==1);
    TEST_ASSERT(buses[1]==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_generators_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_generators_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_pe_sources_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_pe_sources_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("PE SOURCE");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_sources_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_sources_device_id();

    TEST_ASSERT(device.size()==12);

    DEVICE_ID did;
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        did.set_device_type("GENERATOR");
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);

        did.set_device_type("PE SOURCE");
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[6+2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[6+2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_loads_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_loads_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_lines_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_lines_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        if(i==1)
        {
            terminal.append_bus(1);
            terminal.append_bus(2);
        }
        if(i==2)
        {
            terminal.append_bus(2);
            terminal.append_bus(3);
        }
        if(i==3)
        {
            terminal.append_bus(1);
            terminal.append_bus(3);
        }
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_transformers_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_transformers_device_id();

    TEST_ASSERT(device.size()==8);

    DEVICE_ID did;
    did.set_device_type("TRANSFORMER");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        if(i==1)
        {
            terminal.append_bus(1);
            terminal.append_bus(2);
        }
        if(i==2)
        {
            terminal.append_bus(2);
            terminal.append_bus(3);
        }
        if(i==3)
        {
            terminal.append_bus(1);
            terminal.append_bus(3);
        }
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(device[6]==did);
    did.set_device_identifier("#2");
    TEST_ASSERT(device[7]==did);

}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_fixed_shunts_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_fixed_shunts_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("FIXED SHUNT");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_hvdcs_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_hvdcs_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("HVDC");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        if(i==1)
        {
            terminal.append_bus(1);
            terminal.append_bus(2);
        }
        if(i==2)
        {
            terminal.append_bus(2);
            terminal.append_bus(3);
        }
        if(i==3)
        {
            terminal.append_bus(1);
            terminal.append_bus(3);
        }
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_equivalent_devices_device_id()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<DEVICE_ID> device = db->get_all_equivalent_devices_device_id();

    TEST_ASSERT(device.size()==6);

    DEVICE_ID did;
    did.set_device_type("EQUIVALENT DEVICE");
    TERMINAL terminal;
    for(size_t i=1; i!=4; ++i)
    {
        terminal.clear();
        terminal.append_bus(i);
        did.set_device_terminal(terminal);
        did.set_device_identifier("#1");

        TEST_ASSERT(device[2*(i-1)]==did);

        did.set_device_identifier("#2");
        TEST_ASSERT(device[2*(i-1)+1]==did);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_areas_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<size_t> areas = db->get_all_areas_number();

    TEST_ASSERT(areas.size()==3);

    TEST_ASSERT(areas[0]==1);
    TEST_ASSERT(areas[1]==2);
    TEST_ASSERT(areas[2]==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_zones_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<size_t> zones = db->get_all_zones_number();

    TEST_ASSERT(zones.size()==3);

    TEST_ASSERT(zones[0]==1);
    TEST_ASSERT(zones[1]==2);
    TEST_ASSERT(zones[2]==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_all_owners_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<size_t> owners = db->get_all_owners_number();

    TEST_ASSERT(owners.size()==3);

    TEST_ASSERT(owners[0]==1);
    TEST_ASSERT(owners[1]==2);
    TEST_ASSERT(owners[2]==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_bus_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_bus_count()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_in_service_bus_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_in_service_bus_count()==3);

    db->trip_bus(2);
    TEST_ASSERT(db->get_in_service_bus_count()==2);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generator_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_generator_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_source_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_pe_source_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_source_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_source_count()==12);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_load_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_load_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_line_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_line_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformer_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_transformer_count()==8);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunt_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_fixed_shunt_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdc_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_hvdc_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_device_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_equivalent_device_count()==6);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_area_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_area_count()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_zone_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_zone_count()==3);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_owner_count()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_owner_count()==3);
}


void POWER_SYSTEM_DATABASE_TEST::test_get_bus_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_bus_index(1)==0);
    TEST_ASSERT(db->get_bus_index(2)==1);
    TEST_ASSERT(db->get_bus_index(3)==2);
    TEST_ASSERT(db->get_bus_index(4)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_generator_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    TEST_ASSERT(db->get_generator_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_generator_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    TEST_ASSERT(db->get_generator_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_generator_index(did)==3);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    TEST_ASSERT(db->get_generator_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_generator_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_generator_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_pe_source_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("PE SOURCE");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_pe_source_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_pe_source_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_pe_source_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_pe_source_index(did)==3);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_pe_source_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_pe_source_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_pe_source_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_load_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_load_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_load_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_load_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_load_index(did)==3);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_load_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_load_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_load_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_line_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_line_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_line_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_line_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_line_index(did)==3);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_line_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_line_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_line_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_transformer_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("TRANSFORMER");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_transformer_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_transformer_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_transformer_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_transformer_index(did)==3);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_transformer_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_transformer_index(did)==5);

    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_transformer_index(did)==6);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_transformer_index(did)==7);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_transformer_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_fixed_shunt_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("FIXED SHUNT");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==3);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_fixed_shunt_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_hvdc_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("HVDC");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_hvdc_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_hvdc_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_hvdc_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_hvdc_index(did)==3);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_hvdc_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_hvdc_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_hvdc_index(did)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_equivalent_device_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("EQUIVALENT DEVICE");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_equivalent_device_index(did)==0);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_equivalent_device_index(did)==1);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_equivalent_device_index(did)==2);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_equivalent_device_index(did)==3);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    TEST_ASSERT(db->get_equivalent_device_index(did)==4);

    did.set_device_identifier("#2");
    TEST_ASSERT(db->get_equivalent_device_index(did)==5);

    did.set_device_identifier("#3");
    TEST_ASSERT(db->get_equivalent_device_index(did)==INDEX_NOT_EXIST);
}


void POWER_SYSTEM_DATABASE_TEST::test_get_area_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_area_index(1)==0);
    TEST_ASSERT(db->get_area_index(2)==1);
    TEST_ASSERT(db->get_area_index(3)==2);
    TEST_ASSERT(db->get_area_index(4)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_zone_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_zone_index(1)==0);
    TEST_ASSERT(db->get_zone_index(2)==1);
    TEST_ASSERT(db->get_zone_index(3)==2);
    TEST_ASSERT(db->get_zone_index(4)==INDEX_NOT_EXIST);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_owner_index()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_owner_index(1)==0);
    TEST_ASSERT(db->get_owner_index(2)==1);
    TEST_ASSERT(db->get_owner_index(3)==2);
    TEST_ASSERT(db->get_owner_index(4)==INDEX_NOT_EXIST);
}


void POWER_SYSTEM_DATABASE_TEST::test_bus_name2bus_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->bus_name2bus_number("BUS A")==1);
    TEST_ASSERT(db->bus_name2bus_number("BUS B")==2);
    TEST_ASSERT(db->bus_name2bus_number("BUS C")==3);
    TEST_ASSERT(db->bus_name2bus_number("BUS D")==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_area_name2area_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->area_name2area_number("AREA A")==1);
    TEST_ASSERT(db->area_name2area_number("AREA B")==2);
    TEST_ASSERT(db->area_name2area_number("AREA C")==3);
    TEST_ASSERT(db->area_name2area_number("AREA D")==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_zone_name2zone_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->zone_name2zone_number("ZONE A")==1);
    TEST_ASSERT(db->zone_name2zone_number("ZONE B")==2);
    TEST_ASSERT(db->zone_name2zone_number("ZONE C")==3);
    TEST_ASSERT(db->zone_name2zone_number("ZONE D")==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_owner_name2owner_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->owner_name2owner_number("OWNER A")==1);
    TEST_ASSERT(db->owner_name2owner_number("OWNER B")==2);
    TEST_ASSERT(db->owner_name2owner_number("OWNER C")==3);
    TEST_ASSERT(db->owner_name2owner_number("OWNER D")==0);

}

void POWER_SYSTEM_DATABASE_TEST::test_bus_number2bus_name()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->bus_number2bus_name(1)=="BUS A");
    TEST_ASSERT(db->bus_number2bus_name(2)=="BUS B");
    TEST_ASSERT(db->bus_number2bus_name(3)=="BUS C");
    TEST_ASSERT(db->bus_number2bus_name(4)=="");
}


void POWER_SYSTEM_DATABASE_TEST::test_area_number2area_name()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->area_number2area_name(1)=="AREA A");
    TEST_ASSERT(db->area_number2area_name(2)=="AREA B");
    TEST_ASSERT(db->area_number2area_name(3)=="AREA C");
    TEST_ASSERT(db->area_number2area_name(4)=="");
}

void POWER_SYSTEM_DATABASE_TEST::test_zone_number2zone_name()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->zone_number2zone_name(1)=="ZONE A");
    TEST_ASSERT(db->zone_number2zone_name(2)=="ZONE B");
    TEST_ASSERT(db->zone_number2zone_name(3)=="ZONE C");
    TEST_ASSERT(db->zone_number2zone_name(4)=="");
}

void POWER_SYSTEM_DATABASE_TEST::test_owner_number2owner_name()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->owner_number2owner_name(1)=="OWNER A");
    TEST_ASSERT(db->owner_number2owner_name(2)=="OWNER B");
    TEST_ASSERT(db->owner_number2owner_name(3)=="OWNER C");
    TEST_ASSERT(db->owner_number2owner_name(4)=="");
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_load_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    LOAD* load;
    complex<double> S;

    DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;

    terminal.clear();
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    load = db->get_load(did);
    S = load->get_nominal_constant_power_load_in_MVA();

    db->scale_load_power(did, 0.1);

    TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S*(1.0+0.1))<FLOAT_EPSILON);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#2");

    load = db->get_load(did);
    S = load->get_nominal_constant_power_load_in_MVA();

    db->scale_load_power(did, -0.1);

    TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S*(1.0-0.1))<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_all_load_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> loads = db->get_all_loads();
    vector< complex<double> > S0_P, S0_I, S0_Z;
    size_t n=loads.size();
    LOAD* load;
    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        S0_P.push_back(load->get_nominal_constant_power_load_in_MVA());
        S0_I.push_back(load->get_nominal_constant_current_load_in_MVA());
        S0_Z.push_back(load->get_nominal_constant_impedance_load_in_MVA());
    }

    db->scale_all_loads_power(0.1);

    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i]*1.1)<FLOAT_EPSILON);
        TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i]*1.1)<FLOAT_EPSILON);
        TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i]*1.1)<FLOAT_EPSILON);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_load_power_at_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> loads = db->get_all_loads();
    vector< complex<double> > S0_P, S0_I, S0_Z;
    size_t n=loads.size();
    LOAD* load;
    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        S0_P.push_back(load->get_nominal_constant_power_load_in_MVA());
        S0_I.push_back(load->get_nominal_constant_current_load_in_MVA());
        S0_Z.push_back(load->get_nominal_constant_impedance_load_in_MVA());
    }

    db->scale_loads_power_at_bus(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        if(load->is_connected_to_bus(1))
        {
            TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i]*1.1)<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i]*1.1)<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i])<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i])<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i])<FLOAT_EPSILON);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_load_power_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> loads = db->get_all_loads();
    vector< complex<double> > S0_P, S0_I, S0_Z;
    size_t n=loads.size();
    LOAD* load;
    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        S0_P.push_back(load->get_nominal_constant_power_load_in_MVA());
        S0_I.push_back(load->get_nominal_constant_current_load_in_MVA());
        S0_Z.push_back(load->get_nominal_constant_impedance_load_in_MVA());
    }

    db->scale_loads_power_in_area(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        if(load->is_in_area(1))
        {
            TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i]*1.1)<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i]*1.1)<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i])<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i])<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i])<FLOAT_EPSILON);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_load_power_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<LOAD*> loads = db->get_all_loads();
    vector< complex<double> > S0_P, S0_I, S0_Z;
    size_t n=loads.size();
    LOAD* load;
    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        S0_P.push_back(load->get_nominal_constant_power_load_in_MVA());
        S0_I.push_back(load->get_nominal_constant_current_load_in_MVA());
        S0_Z.push_back(load->get_nominal_constant_impedance_load_in_MVA());
    }

    db->scale_loads_power_in_zone(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        load = loads[i];
        if(load->is_in_zone(1))
        {
            TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i]*1.1)<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i]*1.1)<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(load->get_nominal_constant_power_load_in_MVA()-S0_P[i])<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_current_load_in_MVA()-S0_I[i])<FLOAT_EPSILON);
            TEST_ASSERT(abs(load->get_nominal_constant_impedance_load_in_MVA()-S0_Z[i])<FLOAT_EPSILON);
        }
    }
}


void POWER_SYSTEM_DATABASE_TEST::test_scale_source_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    SOURCE* source;
    complex<double> S;

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;

    terminal.clear();
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    source = db->get_generator(did);
    S = source->get_complex_generation_in_MVA();

    db->scale_source_power(did, 0.1);

    TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S*(1.0+0.1))<FLOAT_EPSILON);

    did.set_device_type("PE SOURCE");
    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#2");

    source = db->get_pe_source(did);
    S = source->get_complex_generation_in_MVA();

    db->scale_source_power(did, -0.1);

    TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S*(1.0-0.1))<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_all_source_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> sources = db->get_all_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_all_sources_power(0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_source_power_at_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> sources = db->get_all_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_sources_power_at_bus(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_connected_to_bus(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_source_power_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> sources = db->get_all_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_sources_power_in_area(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_in_area(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }

}

void POWER_SYSTEM_DATABASE_TEST::test_scale_source_power_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<SOURCE*> sources = db->get_all_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_sources_power_in_zone(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_in_zone(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }
}


void POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    GENERATOR* gen;
    complex<double> S;

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;

    terminal.clear();
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    gen = db->get_generator(did);
    S = gen->get_complex_generation_in_MVA();

    db->scale_generator_power(did, 0.1);

    TEST_ASSERT(abs(gen->get_complex_generation_in_MVA()-S*(1.0+0.1))<FLOAT_EPSILON);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#2");

    gen = db->get_generator(did);
    S = gen->get_complex_generation_in_MVA();

    db->scale_generator_power(did, -0.1);

    TEST_ASSERT(abs(gen->get_complex_generation_in_MVA()-S*(1.0-0.1))<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_all_generator_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> sources = db->get_all_generators();
    vector< complex<double> > S0;
    size_t n=sources.size();
    GENERATOR* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_all_generators_power(0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power_at_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> sources = db->get_all_generators();
    vector< complex<double> > S0;
    size_t n=sources.size();
    GENERATOR* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_generators_power_at_bus(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_connected_to_bus(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> sources = db->get_all_generators();
    vector< complex<double> > S0;
    size_t n=sources.size();
    GENERATOR* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_generators_power_in_area(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_in_area(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_generator_power_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<GENERATOR*> sources = db->get_all_generators();
    vector< complex<double> > S0;
    size_t n=sources.size();
    GENERATOR* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_generators_power_in_zone(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_in_zone(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }
}


void POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    PE_SOURCE* source;
    complex<double> S;

    DEVICE_ID did;
    did.set_device_type("PE SOURCE");
    TERMINAL terminal;

    terminal.clear();
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    source = db->get_pe_source(did);
    S = source->get_complex_generation_in_MVA();

    db->scale_generator_power(did, 0.1);

    TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S*(1.0+0.1))<FLOAT_EPSILON);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#2");

    source = db->get_pe_source(did);
    S = source->get_complex_generation_in_MVA();

    db->scale_generator_power(did, -0.1);

    TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S*(1.0-0.1))<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_all_pe_source_power()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> sources = db->get_all_pe_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    PE_SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_all_pe_sources_power(0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power_at_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> sources = db->get_all_pe_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    PE_SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_pe_sources_power_at_bus(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_connected_to_bus(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }

}

void POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power_in_area()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> sources = db->get_all_pe_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    PE_SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_pe_sources_power_in_area(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_in_area(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }

}

void POWER_SYSTEM_DATABASE_TEST::test_scale_pe_source_power_in_zone()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<PE_SOURCE*> sources = db->get_all_pe_sources();
    vector< complex<double> > S0;
    size_t n=sources.size();
    PE_SOURCE* source;
    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        S0.push_back(source->get_complex_generation_in_MVA());
    }

    db->scale_pe_sources_power_in_zone(1, 0.1);

    for(size_t i=0; i!=n; ++i)
    {
        source = sources[i];
        if(source->is_in_zone(1))
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i]*1.1)<FLOAT_EPSILON);
        }
        else
        {
            TEST_ASSERT(abs(source->get_complex_generation_in_MVA()-S0[i])<FLOAT_EPSILON);
        }
    }
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_bus_count()==3);
    TEST_ASSERT(db->is_bus_exist(1)==true);
    TEST_ASSERT(db->is_bus_exist(2)==true);
    TEST_ASSERT(db->is_bus_exist(3)==true);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==2);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==4);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==4);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==4);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==6);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==6);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==6);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==2);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==4);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==4);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==4);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==2);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==2);


    db->clear_bus(1);
    TEST_ASSERT(db->get_bus_count()==2);
    TEST_ASSERT(db->is_bus_exist(1)==false);
    TEST_ASSERT(db->is_bus_exist(2)==true);
    TEST_ASSERT(db->is_bus_exist(3)==true);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==2);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==2);


    db->clear_bus(3);
    TEST_ASSERT(db->get_bus_count()==1);
    TEST_ASSERT(db->is_bus_exist(1)==false);
    TEST_ASSERT(db->is_bus_exist(2)==true);
    TEST_ASSERT(db->is_bus_exist(3)==false);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==0);

    db->clear_bus(2);
    TEST_ASSERT(db->get_bus_count()==0);
    TEST_ASSERT(db->is_bus_exist(1)==false);
    TEST_ASSERT(db->is_bus_exist(2)==false);
    TEST_ASSERT(db->is_bus_exist(3)==false);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_database()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_database();

    TEST_ASSERT(db->get_bus_count()==0);
    TEST_ASSERT(db->get_generator_count()==0);
    TEST_ASSERT(db->get_pe_source_count()==0);
    TEST_ASSERT(db->get_load_count()==0);
    TEST_ASSERT(db->get_line_count()==0);
    TEST_ASSERT(db->get_transformer_count()==0);
    TEST_ASSERT(db->get_fixed_shunt_count()==0);
    TEST_ASSERT(db->get_hvdc_count()==0);
    TEST_ASSERT(db->get_equivalent_device_count()==0);
    TEST_ASSERT(db->get_area_count()==0);
    TEST_ASSERT(db->get_zone_count()==0);
    TEST_ASSERT(db->get_owner_count()==0);
}


void POWER_SYSTEM_DATABASE_TEST::test_clear_all_buses()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_buses();

    TEST_ASSERT(db->get_bus_count()==0);
    TEST_ASSERT(db->get_generator_count()==0);
    TEST_ASSERT(db->get_pe_source_count()==0);
    TEST_ASSERT(db->get_load_count()==0);
    TEST_ASSERT(db->get_line_count()==0);
    TEST_ASSERT(db->get_transformer_count()==0);
    TEST_ASSERT(db->get_fixed_shunt_count()==0);
    TEST_ASSERT(db->get_hvdc_count()==0);
    TEST_ASSERT(db->get_equivalent_device_count()==0);
    TEST_ASSERT(db->get_area_count()==0);
    TEST_ASSERT(db->get_zone_count()==0);
    TEST_ASSERT(db->get_owner_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_generator()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_generator_count()==6);

    vector<GENERATOR*> gens;

    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_generator(did);
    TEST_ASSERT(db->is_generator_exist(did)==false);
    TEST_ASSERT(db->get_generator_count()==5);

    did.set_device_identifier("#2");
    db->clear_generator(did);
    TEST_ASSERT(db->is_generator_exist(did)==false);
    TEST_ASSERT(db->get_generator_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    db->clear_generator(did);
    TEST_ASSERT(db->is_generator_exist(did)==false);
    TEST_ASSERT(db->get_generator_count()==3);

    did.set_device_identifier("#2");
    db->clear_generator(did);
    TEST_ASSERT(db->is_generator_exist(did)==false);
    TEST_ASSERT(db->get_generator_count()==2);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");
    db->clear_generator(did);
    TEST_ASSERT(db->is_generator_exist(did)==false);
    TEST_ASSERT(db->get_generator_count()==1);

    did.set_device_identifier("#2");
    db->clear_generator(did);
    TEST_ASSERT(db->is_generator_exist(did)==false);
    TEST_ASSERT(db->get_generator_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_generators_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_generators_connecting_to_bus(1);

    TEST_ASSERT(db->get_generator_count()==4);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==2);

    db->clear_generators_connecting_to_bus(2);

    TEST_ASSERT(db->get_generator_count()==2);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==2);

    db->clear_generators_connecting_to_bus(3);

    TEST_ASSERT(db->get_generator_count()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_generators_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_generators()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_generators();

    TEST_ASSERT(db->get_generator_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_pe_source()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_pe_source_count()==6);

    vector<PE_SOURCE*> pesources;

    DEVICE_ID did;
    did.set_device_type("PE SOURCE");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_pe_source(did);
    TEST_ASSERT(db->is_pe_source_exist(did)==false);
    TEST_ASSERT(db->get_pe_source_count()==5);

    did.set_device_identifier("#2");

    db->clear_pe_source(did);
    TEST_ASSERT(db->is_pe_source_exist(did)==false);
    TEST_ASSERT(db->get_pe_source_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_pe_source(did);
    TEST_ASSERT(db->is_pe_source_exist(did)==false);
    TEST_ASSERT(db->get_pe_source_count()==3);

    did.set_device_identifier("#2");

    db->clear_pe_source(did);
    TEST_ASSERT(db->is_pe_source_exist(did)==false);
    TEST_ASSERT(db->get_pe_source_count()==2);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_pe_source(did);
    TEST_ASSERT(db->is_pe_source_exist(did)==false);
    TEST_ASSERT(db->get_pe_source_count()==1);

    did.set_device_identifier("#2");

    db->clear_pe_source(did);
    TEST_ASSERT(db->is_pe_source_exist(did)==false);
    TEST_ASSERT(db->get_pe_source_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_pe_sources_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_pe_sources_connecting_to_bus(1);

    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==2);

    db->clear_pe_sources_connecting_to_bus(3);

    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==0);

    db->clear_pe_sources_connecting_to_bus(2);

    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_pe_sources_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_pe_sources()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_pe_sources();

    TEST_ASSERT(db->get_pe_source_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_sources_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_source_count()==12);

    db->clear_sources_connecting_to_bus(1);

    TEST_ASSERT(db->get_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_sources_connecting_to_bus(2).size()==4);
    TEST_ASSERT(db->get_sources_connecting_to_bus(3).size()==4);

    db->clear_sources_connecting_to_bus(2);

    TEST_ASSERT(db->get_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_sources_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_sources_connecting_to_bus(3).size()==4);

    db->clear_sources_connecting_to_bus(3);

    TEST_ASSERT(db->get_sources_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_sources_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_sources_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_sources()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_sources();
    TEST_ASSERT(db->get_source_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_load()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_load(did);

    TEST_ASSERT(db->is_load_exist(did)==false);
    TEST_ASSERT(db->get_load_count()==5);

    did.set_device_identifier("#2");
    db->clear_load(did);

    TEST_ASSERT(db->is_load_exist(did)==false);
    TEST_ASSERT(db->get_load_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_load(did);
    TEST_ASSERT(db->is_load_exist(did)==false);
    TEST_ASSERT(db->get_load_count()==3);

    did.set_device_identifier("#2");

    db->clear_load(did);
    TEST_ASSERT(db->is_load_exist(did)==false);
    TEST_ASSERT(db->get_load_count()==2);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_load(did);
    TEST_ASSERT(db->is_load_exist(did)==false);
    TEST_ASSERT(db->get_load_count()==1);

    did.set_device_identifier("#2");

    db->clear_load(did);
    TEST_ASSERT(db->is_load_exist(did)==false);
    TEST_ASSERT(db->get_load_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_loads_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_loads_connecting_to_bus(1);

    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==2);

    db->clear_loads_connecting_to_bus(2);

    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==2);

    db->clear_loads_connecting_to_bus(3);

    TEST_ASSERT(db->get_loads_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_loads_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_loads()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_loads();

    TEST_ASSERT(db->get_load_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_line()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(db->get_line_count()==6);

    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_line(did);
    TEST_ASSERT(db->is_line_exist(did)==false);
    TEST_ASSERT(db->get_line_count()==5);

    did.set_device_identifier("#2");

    db->clear_line(did);
    TEST_ASSERT(db->is_line_exist(did)==false);
    TEST_ASSERT(db->get_line_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_line(did);
    TEST_ASSERT(db->is_line_exist(did)==false);
    TEST_ASSERT(db->get_line_count()==3);

    did.set_device_identifier("#2");

    db->clear_line(did);
    TEST_ASSERT(db->is_line_exist(did)==false);
    TEST_ASSERT(db->get_line_count()==2);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_line(did);
    TEST_ASSERT(db->is_line_exist(did)==false);
    TEST_ASSERT(db->get_line_count()==1);

    did.set_device_identifier("#2");

    db->clear_line(did);
    TEST_ASSERT(db->is_line_exist(did)==false);
    TEST_ASSERT(db->get_line_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_lines_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_lines_connecting_to_bus(1);

    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==2);

    db->clear_lines_connecting_to_bus(2);

    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==0);

    db->clear_lines_connecting_to_bus(3);

    TEST_ASSERT(db->get_lines_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_lines_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_lines()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_lines();

    TEST_ASSERT(db->get_line_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_transformer()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("TRANSFORMER");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==7);

    did.set_device_identifier("#2");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==6);

    terminal.clear();
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==5);

    did.set_device_identifier("#2");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==4);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==3);

    did.set_device_identifier("#2");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==2);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==1);

    did.set_device_identifier("#2");

    db->clear_transformer(did);
    TEST_ASSERT(db->is_transformer_exist(did)==false);
    TEST_ASSERT(db->get_transformer_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_transformers_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_transformers_connecting_to_bus(1);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==2);

    db->clear_transformers_connecting_to_bus(2);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==0);

    db->clear_transformers_connecting_to_bus(3);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_transformers_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_transformers()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_transformers();

    TEST_ASSERT(db->get_transformer_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_fixed_shunt()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");
    ostringstream sstream;
    sstream<<"ALEEEEEEEEEEERT! clear_fixed_shunt is not functioning if using the vector::erase function.";
    show_information_with_leading_time_stamp(sstream);

    prepare_database_for_test();

    DEVICE_ID did;
    did.set_device_type("FIXED SHUNT");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_fixed_shunt(did);
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    TEST_ASSERT(db->get_fixed_shunt_count()==5);

    did.set_device_identifier("#2");

    db->clear_fixed_shunt(did);
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    TEST_ASSERT(db->get_fixed_shunt_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_fixed_shunt(did);
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    TEST_ASSERT(db->get_fixed_shunt_count()==3);

    did.set_device_identifier("#2");

    db->clear_fixed_shunt(did);
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    TEST_ASSERT(db->get_fixed_shunt_count()==2);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_fixed_shunt(did);
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    TEST_ASSERT(db->get_fixed_shunt_count()==1);

    did.set_device_identifier("#2");

    db->clear_fixed_shunt(did);
    TEST_ASSERT(db->is_fixed_shunt_exist(did)==false);
    TEST_ASSERT(db->get_fixed_shunt_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_fixed_shunts_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_fixed_shunts_connecting_to_bus(1);

    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==2);

    db->clear_fixed_shunts_connecting_to_bus(2);

    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==2);

    db->clear_fixed_shunts_connecting_to_bus(3);

    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_fixed_shunts_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_fixed_shunts()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_fixed_shunts();

    TEST_ASSERT(db->get_fixed_shunt_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_hvdc()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<HVDC*> hvdcs;

    DEVICE_ID did;
    did.set_device_type("HVDC");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_hvdc(did);
    TEST_ASSERT(db->is_hvdc_exist(did)==false);
    TEST_ASSERT(db->get_hvdc_count()==5);

    did.set_device_identifier("#2");

    db->clear_hvdc(did);
    TEST_ASSERT(db->is_hvdc_exist(did)==false);
    TEST_ASSERT(db->get_hvdc_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_hvdc(did);
    TEST_ASSERT(db->is_hvdc_exist(did)==false);
    TEST_ASSERT(db->get_hvdc_count()==3);

    did.set_device_identifier("#2");

    db->clear_hvdc(did);
    TEST_ASSERT(db->is_hvdc_exist(did)==false);
    TEST_ASSERT(db->get_hvdc_count()==2);

    terminal.clear();
    terminal.append_bus(1);
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_hvdc(did);
    TEST_ASSERT(db->is_hvdc_exist(did)==false);
    TEST_ASSERT(db->get_hvdc_count()==1);

    did.set_device_identifier("#2");

    db->clear_hvdc(did);
    TEST_ASSERT(db->is_hvdc_exist(did)==false);
    TEST_ASSERT(db->get_hvdc_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_hvdcs_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_hvdcs_connecting_to_bus(1);

    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==2);

    db->clear_hvdcs_connecting_to_bus(2);

    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==0);

    db->clear_hvdcs_connecting_to_bus(3);

    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_hvdcs_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_hvdcs()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_hvdcs();

    TEST_ASSERT(db->get_hvdc_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_equivalent_device()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    vector<EQUIVALENT_DEVICE*> edevices;

    DEVICE_ID did;
    did.set_device_type("EQUIVALENT DEVICE");
    TERMINAL terminal;
    terminal.append_bus(1);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_equivalent_device(did);
    TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    TEST_ASSERT(db->get_equivalent_device_count()==5);

    did.set_device_identifier("#2");

    db->clear_equivalent_device(did);
    TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    TEST_ASSERT(db->get_equivalent_device_count()==4);

    terminal.clear();
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_equivalent_device(did);
    TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    TEST_ASSERT(db->get_equivalent_device_count()==3);

    did.set_device_identifier("#2");

    db->clear_equivalent_device(did);
    TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    TEST_ASSERT(db->get_equivalent_device_count()==2);

    terminal.clear();
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    db->clear_equivalent_device(did);
    TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    TEST_ASSERT(db->get_equivalent_device_count()==1);

    did.set_device_identifier("#2");

    db->clear_equivalent_device(did);
    TEST_ASSERT(db->is_equivalent_device_exist(did)==false);
    TEST_ASSERT(db->get_equivalent_device_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_equivalent_devices_connecting_to_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_equivalent_devices_connecting_to_bus(1);

    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==2);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==2);

    db->clear_equivalent_devices_connecting_to_bus(2);

    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==2);

    db->clear_equivalent_devices_connecting_to_bus(3);

    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(1).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(2).size()==0);
    TEST_ASSERT(db->get_equivalent_devices_connecting_to_bus(3).size()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_equivalent_devices()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_equivalent_devices();

    TEST_ASSERT(db->get_equivalent_device_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_areas()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_areas();

    TEST_ASSERT(db->get_area_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_zones()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_zones();

    TEST_ASSERT(db->get_zone_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_clear_all_owners()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    db->clear_all_owners();

    TEST_ASSERT(db->get_owner_count()==0);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_bus_complex_voltage()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    BUS* bus = db->get_bus(1);
    bus->set_voltage_in_pu(1.05);
    bus->set_angle_in_rad(0.5);

    complex<double> V(1.05*cos(0.5), 1.05*sin(0.5));
    TEST_ASSERT(abs(db->get_bus_complex_voltage_in_pu(1)-V)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_bus_base_voltage()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    TEST_ASSERT(fabs(db->get_bus_base_voltage_in_kV(1)-110.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_bus_voltage()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    BUS* bus = db->get_bus(1);
    bus->set_voltage_in_pu(1.05);


    TEST_ASSERT(fabs(db->get_bus_voltage_in_pu(1)-1.05)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_bus_voltage_in_kV(1)-1.05*110.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_bus_angle()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();

    BUS* bus = db->get_bus(1);
    bus->set_angle_in_rad(0.5);

    TEST_ASSERT(fabs(db->get_bus_angle_in_rad(1)-0.5)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_bus_angle_in_deg(1)-(0.5/PI*180.0))<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_voltage_to_regulate_of_physical_bus_in_pu()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");


    prepare_database_for_test();

    BUS* bus = db->get_bus(1);
    bus->set_voltage_in_pu(1.05);
    bus->set_voltage_to_regulate_in_pu(1.05);

    TEST_ASSERT(fabs(db->get_voltage_to_regulate_of_physical_bus_in_pu(1)-1.05)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_regulatable_p_max_at_physical_bus_in_MW()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                       2                     3
    // VA                      PV                    PQ
    // 110/-110   120/-120     210/-210 220/-220     310/-310 320/-320
    // 101/-101   102/-102     201/-201 202/-202     301/-301 302/-302

    TEST_ASSERT(fabs(db->get_regulatable_p_max_at_physical_bus_in_MW(1)-433.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_p_max_at_physical_bus_in_MW(2)-0.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_p_max_at_physical_bus_in_MW(3)-0.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_regulatable_p_min_at_physical_bus_in_MW()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                       2                     3
    // VA                      PV                    PQ
    // 110/-110   120/-120     210/-210 220/-220     310/-310 320/-320
    // 101/-101   102/-102     201/-201 202/-202     301/-301 302/-302

    TEST_ASSERT(fabs(db->get_regulatable_p_min_at_physical_bus_in_MW(1)-(-433.0))<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_p_min_at_physical_bus_in_MW(2)-0.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_p_min_at_physical_bus_in_MW(3)-0.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_regulatable_q_max_at_physical_bus_in_MVar()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                       2                     3
    // VA                      PV                    PQ
    // 110/-110   120/-120     210/-210 220/-220     310/-310 320/-320
    // 101/-101   102/-102     201/-201 202/-202     301/-301 302/-302

    TEST_ASSERT(fabs(db->get_regulatable_q_max_at_physical_bus_in_MVar(1)-433.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_q_max_at_physical_bus_in_MVar(2)-833.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_q_max_at_physical_bus_in_MVar(3)-0.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_regulatable_q_min_at_physical_bus_in_MVar()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                       2                     3
    // VA                      PV                    PQ
    // 110/-110   120/-120     210/-210 220/-220     310/-310 320/-320
    // 101/-101   102/-102     201/-201 202/-202     301/-301 302/-302

    TEST_ASSERT(fabs(db->get_regulatable_q_min_at_physical_bus_in_MVar(1)-(-433.0))<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_q_min_at_physical_bus_in_MVar(2)-(-833.0))<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_regulatable_q_min_at_physical_bus_in_MVar(3)-0.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_total_regulating_p_generation_at_physical_bus_in_MW()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                 2                  3
    // VA                PV                 PQ
    // 10/10   10/20     20/10   20/20     30/10   30/20

    TEST_ASSERT(fabs(db->get_total_regulating_p_generation_at_physical_bus_in_MW(1)-40.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_regulating_p_generation_at_physical_bus_in_MW(2)-0.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_regulating_p_generation_at_physical_bus_in_MW(3)-0.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_total_regulating_q_generation_at_physical_bus_in_MVar()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                 2                  3
    // VA                PV                 PQ
    // 10/10   10/20     20/10   20/20     30/10   30/20

    TEST_ASSERT(fabs(db->get_total_regulating_q_generation_at_physical_bus_in_MVar(1)-60.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_regulating_q_generation_at_physical_bus_in_MVar(2)-60.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_regulating_q_generation_at_physical_bus_in_MVar(3)-0.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_total_p_generation_of_sources_at_physical_bus_in_MW()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                 2                  3
    // VA                PV                 PQ
    // 10/10   10/20     20/10   20/20     30/10   30/20

    TEST_ASSERT(fabs(db->get_total_p_generation_at_physical_bus_in_MW(1)-40.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_p_generation_at_physical_bus_in_MW(2)-80.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_p_generation_at_physical_bus_in_MW(3)-120.0)<FLOAT_EPSILON);
}

void POWER_SYSTEM_DATABASE_TEST::test_get_total_q_generation_of_sources_at_physical_bus_in_MVar()
{
    show_test_information_for_function_of_class(__FUNCTION__,"POWER_SYSTEM_DATABASE_TEST");

    prepare_database_for_test();
    // 1                 2                  3
    // VA                PV                 PQ
    // 10/10   10/20     20/10   20/20     30/10   30/20
    TEST_ASSERT(fabs(db->get_total_q_generation_at_physical_bus_in_MVar(1)-60.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_q_generation_at_physical_bus_in_MVar(2)-60.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(db->get_total_q_generation_at_physical_bus_in_MVar(3)-60.0)<FLOAT_EPSILON);
}