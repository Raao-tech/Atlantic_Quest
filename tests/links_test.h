/**
 * @brief It defines the links.c tests
 *
 * @file links_test.h
 * @author Salvador
 * @version 1
 * @date 11-04-2026
 * @copyright GNU Public License
 */

#ifndef LINKS_TEST_H
#define LINKS_TEST_H

/* ============== (Create/Destroy)  Link ====================== */
void test1_link_create();

/* ============== (set/get)  Id ====================== */
void test1_link_set_id();
void test2_link_set_id();
void test3_link_set_id();
void test1_link_get_id();
void test2_link_get_id();

/* ============== (set/get)  Name ====================== */
void test1_link_set_name();
void test2_link_set_name();
void test3_link_set_name();
void test1_link_get_name();
void test2_link_get_name();

/* ============== (set/get) status ====================== */
void test1_link_set_status();
void test2_link_set_status();

void test1_link_get_status();
void test2_link_get_status();

/* ============== (set/get) origin/destination ====================== */
void test1_link_set_origin_id();
void test2_link_set_origin_id();
void test3_link_set_origin_id();
void test1_link_get_origin_id();
void test2_link_get_origin_id();

void test1_link_set_destination_id();
void test2_link_set_destination_id();
void test3_link_set_destination_id();
void test1_link_get_destination_id();
void test2_link_get_destination_id();

/* ============== (set/get) status (dest_to_origin/ origin_to_dest) ====================== */
void test1_link_set_open_dest_to_origin();
void test2_link_set_open_dest_to_origin();
void test1_link_get_open_dest_to_origin();
void test2_link_get_open_dest_to_origin();

void test1_link_set_open_origin_to_dest();
void test2_link_set_open_origin_to_dest();
void test1_link_get_open_origin_to_dest();
void test2_link_get_open_origin_to_dest();

/* ============== (set/get/opposite) direction ====================== */
void test1_link_set_direction();
void test2_link_set_direction();
void test3_link_set_direction();
void test1_link_get_direction();
void test2_link_get_direction();
void test1_link_get_opposite_direction();
void test2_link_get_opposite_direction();

#endif