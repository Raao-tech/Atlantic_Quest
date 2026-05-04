/**
 * @brief It declares the tests for the numen module
 *
 * @file numen_test.h
 * @author Javier Jarque
 * @version 1.0
 * @date 30-04-2026
 * @copyright GNU Public License
 */

#ifndef NUMEN_TEST_H
#define NUMEN_TEST_H

/* numen_create */
void test1_numen_create();
void test2_numen_create();

/* numen_destroy */
void test1_numen_destroy();
void test2_numen_destroy();

/* numen_set_id / numen_get_id */
void test1_numen_set_id();
void test2_numen_set_id();
void test1_numen_get_id();
void test2_numen_get_id();

/* numen_set_name / numen_get_name / numen_has_name */
void test1_numen_set_name();
void test2_numen_set_name();
void test3_numen_set_name();
void test1_numen_get_name();
void test2_numen_get_name();
void test1_numen_has_name();
void test2_numen_has_name();
void test3_numen_has_name();

/* numen_set_gdesc / numen_get_gdesc */
void test1_numen_set_gdesc();
void test2_numen_set_gdesc();
void test3_numen_set_gdesc();
void test1_numen_get_gdesc();
void test2_numen_get_gdesc();

/* numen_set_position / numen_set_pos_x / numen_get_pos_x / numen_set_pos_y / numen_get_pos_y */
void test1_numen_set_position();
void test2_numen_set_position();
void test1_numen_set_pos_x();
void test2_numen_set_pos_x();
void test1_numen_get_pos_x();
void test2_numen_get_pos_x();
void test1_numen_set_pos_y();
void test2_numen_set_pos_y();
void test1_numen_get_pos_y();
void test2_numen_get_pos_y();

/* numen_set_health / numen_get_health */
void test1_numen_set_health();
void test2_numen_set_health();
void test1_numen_get_health();
void test2_numen_get_health();

/* numen_set_attack / numen_get_attack */
void test1_numen_set_attack();
void test2_numen_set_attack();
void test1_numen_get_attack();
void test2_numen_get_attack();

/* numen_set_energy / numen_get_energy */
void test1_numen_set_energy();
void test2_numen_set_energy();
void test1_numen_get_energy();
void test2_numen_get_energy();

/* numen_set_speed / numen_get_speed */
void test1_numen_set_speed();
void test2_numen_set_speed();
void test1_numen_get_speed();
void test2_numen_get_speed();

/* numen_set_following / numen_get_following / numen_is_errant */
void test1_numen_set_following();
void test2_numen_set_following();
void test1_numen_get_following();
void test2_numen_get_following();
void test1_numen_is_errant();
void test2_numen_is_errant();

/* numen_set_corrupt / numen_get_corrupt */
void test1_numen_set_corrupt();
void test2_numen_set_corrupt();
void test1_numen_get_corrupt();
void test2_numen_get_corrupt();

/* numen skills */
void test1_numen_add_skill();
void test2_numen_add_skill();
void test1_numen_get_skill_by_id();
void test2_numen_get_skill_by_id();
void test1_numen_get_skill_by_index();
void test2_numen_get_skill_by_index();

/* numen_print */
void test1_numen_print();
void test2_numen_print();

#endif
