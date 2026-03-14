/**
 * @brief It declares the tests for the space module
 *
 * @file space_test.h
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/* space_create */
void test1_space_create();
void test2_space_create();

/* space_destroy */
void test1_space_destroy();
void test2_space_destroy();

/* space_set_id / get_id */
void test1_space_set_id();
void test2_space_set_id();
void test1_space_get_id();
void test2_space_get_id();

/* space_set_name / get_name */
void test1_space_set_name();
void test2_space_set_name();
void test3_space_set_name();
void test1_space_get_name();
void test2_space_get_name();

/* space_set_north / get_north */
void test1_space_set_north();
void test2_space_set_north();
void test1_space_get_north();
void test2_space_get_north();

/* space_set_south / get_south */
void test1_space_set_south();
void test2_space_set_south();
void test1_space_get_south();
void test2_space_get_south();

/* space_set_east / get_east */
void test1_space_set_east();
void test2_space_set_east();
void test1_space_get_east();
void test2_space_get_east();

/* space_set_west / get_west */
void test1_space_set_west();
void test2_space_set_west();
void test1_space_get_west();
void test2_space_get_west();

/* space_set_object / contains_object / remove_object / get_n_objects */
void test1_space_set_object();
void test2_space_set_object();
void test1_space_contains_object();
void test2_space_contains_object();
void test3_space_contains_object();
void test1_space_remove_object();
void test2_space_remove_object();
void test1_space_get_n_objects();
void test2_space_get_n_objects();

/* space_set_character / contains_character / remove_character / get_n_characters */
void test1_space_set_character();
void test2_space_set_character();
void test1_space_contains_character();
void test2_space_contains_character();
void test1_space_remove_character();
void test2_space_remove_character();
void test1_space_get_n_characters();
void test2_space_get_n_characters();

/* space_set_gdesc_line / get_gdesc */
void test1_space_set_gdesc_line();
void test2_space_set_gdesc_line();
void test3_space_set_gdesc_line();
void test1_space_get_gdesc();
void test2_space_get_gdesc();

#endif
