/**
 * @brief It declares the tests for the entity module
 *
 * @file entity_test.h
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#ifndef ENTITY_TEST_H
#define ENTITY_TEST_H

/* entity_create */
void test1_entity_create();
void test2_entity_create();

/* entity_destroy */
void test1_entity_destroy();
void test2_entity_destroy();

/* entity_set_id / get_id */
void test1_entity_set_id();
void test2_entity_set_id();
void test1_entity_get_id();
void test2_entity_get_id();

/* entity_set_name / get_name */
void test1_entity_set_name();
void test2_entity_set_name();
void test3_entity_set_name();
void test1_entity_get_name();
void test2_entity_get_name();

/* entity_set_gdesc / get_gdesc */
void test1_entity_set_gdesc();
void test2_entity_set_gdesc();
void test1_entity_get_gdesc();
void test2_entity_get_gdesc();

/* entity_set_message / get_message */
void test1_entity_set_message();
void test2_entity_set_message();
void test1_entity_get_message();
void test2_entity_get_message();

/* entity_set_health / get_health */
void test1_entity_set_health();
void test2_entity_set_health();
void test3_entity_set_health();
void test1_entity_get_health();
void test2_entity_get_health();

/* entity_set_attack / get_attack */
void test1_entity_set_attack();
void test2_entity_set_attack();
void test1_entity_get_attack();
void test2_entity_get_attack();

/* overwrite strings (memory cleanup) */
void test1_entity_overwrite_name();

#endif
