/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Rafael y Violeta
 * @version 1
 * @date 12-04-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/* obj_create */
void test1_obj_create();
void test2_obj_create();

/* obj_destroy */
void test1_obj_destroy();
void test2_obj_destroy();

/* obj_set_id / get_id */
void test1_obj_set_id();
void test2_obj_set_id();
void test1_obj_get_id();
void test2_obj_get_id();

/* obj_set_name / get_name / has_name */
void test1_obj_set_name();
void test2_obj_set_name();
void test3_obj_set_name();
void test1_obj_get_name();
void test2_obj_get_name();
void test1_obj_has_name();
void test2_obj_has_name();
void test3_obj_has_name();

/* obj_set_description / get_description / has_description */
void test1_obj_set_description();
void test2_obj_set_description();
void test3_obj_set_description();
void test1_obj_get_description();
void test2_obj_get_description();
void test1_obj_has_description();
void test2_obj_has_description();
void test3_obj_has_description();

/* obj_print */
void test1_obj_print();
void test2_obj_print();

#endif