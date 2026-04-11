/**
 * @brief It tests the links module
 *
 * @file links_test.c
 * @author Salvador 
 * @version 1
 * @date 11-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "links.h"
#include "links_test.h"
#include "test.h"

#define MAX_TESTS 40

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Links:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_link_create();

/* Id */
if (all || test == 2)  test1_link_set_id();
if (all || test == 3)  test2_link_set_id();
if (all || test == 4)  test3_link_set_id();
if (all || test == 5)  test1_link_get_id();
if (all || test == 6)  test2_link_get_id();

/* Name */
if (all || test == 7)  test1_link_set_name();
if (all || test == 8)  test2_link_set_name();
if (all || test == 9)  test3_link_set_name();
if (all || test == 10) test1_link_get_name();
if (all || test == 11) test2_link_get_name();

/* Status */
if (all || test == 12) test1_link_set_status();
if (all || test == 13) test2_link_set_status();
if (all || test == 14) test1_link_get_status();
if (all || test == 15) test2_link_get_status();

/* Origin */
if (all || test == 16) test1_link_set_origin_id();
if (all || test == 17) test2_link_set_origin_id();
if (all || test == 18) test3_link_set_origin_id();
if (all || test == 19) test1_link_get_origin_id();
if (all || test == 20) test2_link_get_origin_id();

/* Destination */
if (all || test == 21) test1_link_set_destination_id();
if (all || test == 22) test2_link_set_destination_id();
if (all || test == 23) test3_link_set_destination_id();
if (all || test == 24) test1_link_get_destination_id();
if (all || test == 25) test2_link_get_destination_id();

/* Open dest → origin */
if (all || test == 26) test1_link_set_open_dest_to_origin();
if (all || test == 27) test2_link_set_open_dest_to_origin();
if (all || test == 28) test1_link_get_open_dest_to_origin();
if (all || test == 29) test2_link_get_open_dest_to_origin();

/* Open origin → dest */
if (all || test == 30) test1_link_set_open_origin_to_dest();
if (all || test == 31) test2_link_set_open_origin_to_dest();
if (all || test == 32) test1_link_get_open_origin_to_dest();
if (all || test == 33) test2_link_get_open_origin_to_dest();

/* Direction */
if (all || test == 34) test1_link_set_direction();
if (all || test == 35) test2_link_set_direction();
if (all || test == 36) test3_link_set_direction();
if (all || test == 37) test1_link_get_direction();
if (all || test == 38) test2_link_get_direction();
if (all || test == 39) test1_link_get_opposite_direction();
if (all || test == 40) test2_link_get_opposite_direction();
  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ============== link_create ============== */
void test1_link_create() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link != NULL);
  link_destroy(link);
}

/* ============== link_set_id / link_get_id ============== */
void test1_link_set_id() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_id(link, 20) == OK);
  link_destroy(link);
}

void test2_link_set_id() {
  PRINT_TEST_RESULT(link_set_id(NULL, 20) == ERROR);
}

void test3_link_set_id() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_id(link, NO_ID) == ERROR);
  link_destroy(link);
}

void test1_link_get_id() {
  Links *link = link_create();
  link_set_id(link, 20);
  PRINT_TEST_RESULT(link_get_id(link) == 20);
  link_destroy(link);
}

void test2_link_get_id() {
  PRINT_TEST_RESULT(link_get_id(NULL) == NO_ID);
}

/* ============== link_set_name / link_get_name ============== */
void test1_link_set_name() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_name(link, "north") == OK);
  link_destroy(link);
}

void test2_link_set_name() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
  link_destroy(link);
}

void test3_link_set_name() {
  PRINT_TEST_RESULT(link_set_name(NULL, "north") == ERROR);
}

void test1_link_get_name() {
  Links *link = link_create();
  char *name = NULL;

  link_set_name(link, "north");
  name = link_get_name(link);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "north") == 0);
  free(name);
  link_destroy(link);
}

void test2_link_get_name() {
  PRINT_TEST_RESULT(link_get_name(NULL) == NULL);
}

/* ============== link_set_status / link_get_status ============== */
void test1_link_set_status() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_status(link, TRUE) == OK);
  link_destroy(link);
}

void test2_link_set_status() {
  PRINT_TEST_RESULT(link_set_status(NULL, TRUE) == ERROR);
}

void test1_link_get_status() {
  Links *link = link_create();
  link_set_status(link, TRUE);
  PRINT_TEST_RESULT(link_get_status(link) == TRUE);
  link_destroy(link);
}

void test2_link_get_status() {
  PRINT_TEST_RESULT(link_get_status(NULL) == FALSE);
}

/* ============== link_set_origin_id / link_get_origin_id ============== */
void test1_link_set_origin_id() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_origin_id(link, 10) == OK);
  link_destroy(link);
}

void test2_link_set_origin_id() {
  PRINT_TEST_RESULT(link_set_origin_id(NULL, 10) == ERROR);
}

void test3_link_set_origin_id() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_origin_id(link, NO_ID) == ERROR);
  link_destroy(link);
}

void test1_link_get_origin_id() {
  Links *link = link_create();
  link_set_origin_id(link, 10);
  PRINT_TEST_RESULT(link_get_origin_id(link) == 10);
  link_destroy(link);
}

void test2_link_get_origin_id() {
  PRINT_TEST_RESULT(link_get_origin_id(NULL) == NO_ID);
}

/* ============== link_set_destination_id / link_get_destination_id ============== */
void test1_link_set_destination_id() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_destination_id(link, 11) == OK);
  link_destroy(link);
}

void test2_link_set_destination_id() {
  PRINT_TEST_RESULT(link_set_destination_id(NULL, 11) == ERROR);
}

void test3_link_set_destination_id() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_destination_id(link, NO_ID) == ERROR);
  link_destroy(link);
}

void test1_link_get_destination_id() {
  Links *link = link_create();
  link_set_destination_id(link, 11);
  PRINT_TEST_RESULT(link_get_destination_id(link) == 11);
  link_destroy(link);
}

void test2_link_get_destination_id() {
  PRINT_TEST_RESULT(link_get_destination_id(NULL) == NO_ID);
}

/* ============== link_set_open_dest_to_origin / link_get_open_dest_to_origin ============== */
void test1_link_set_open_dest_to_origin() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_open_dest_to_origin(link, FALSE) == OK);
  link_destroy(link);
}

void test2_link_set_open_dest_to_origin() {
  PRINT_TEST_RESULT(link_set_open_dest_to_origin(NULL, TRUE) == ERROR);
}

void test1_link_get_open_dest_to_origin() {
  Links *link = link_create();
  link_set_open_dest_to_origin(link, FALSE);
  PRINT_TEST_RESULT(link_get_open_dest_to_origin(link) == FALSE);
  link_destroy(link);
}

void test2_link_get_open_dest_to_origin() {
  PRINT_TEST_RESULT(link_get_open_dest_to_origin(NULL) == FALSE);
}

/* ============== link_set_open_origin_to_dest / link_get_open_origin_to_dest ============== */
void test1_link_set_open_origin_to_dest() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_open_origin_to_dest(link, FALSE) == OK);
  link_destroy(link);
}

void test2_link_set_open_origin_to_dest() {
  PRINT_TEST_RESULT(link_set_open_origin_to_dest(NULL, TRUE) == ERROR);
}

void test1_link_get_open_origin_to_dest() {
  Links *link = link_create();
  link_set_open_origin_to_dest(link, FALSE);
  PRINT_TEST_RESULT(link_get_open_origin_to_dest(link) == FALSE);
  link_destroy(link);
}

void test2_link_get_open_origin_to_dest() {
  PRINT_TEST_RESULT(link_get_open_origin_to_dest(NULL) == FALSE);
}

/* ============== link_set_direction / link_get_direction ============== */
void test1_link_set_direction() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_direction(link, E) == OK);
  link_destroy(link);
}

void test2_link_set_direction() {
  PRINT_TEST_RESULT(link_set_direction(NULL, E) == ERROR);
}

void test3_link_set_direction() {
  Links *link = link_create();
  PRINT_TEST_RESULT(link_set_direction(link, U) == ERROR);
  link_destroy(link);
}

void test1_link_get_direction() {
  Links *link = link_create();
  link_set_direction(link, E);
  PRINT_TEST_RESULT(link_get_direction(link) == E);
  link_destroy(link);
}

void test2_link_get_direction() {
  PRINT_TEST_RESULT(link_get_direction(NULL) == U);
}

void test1_link_get_opposite_direction() {
  Links *link = link_create();
  link_set_direction(link, N);
  PRINT_TEST_RESULT(link_get_opposite_direction(link) == S);
  link_destroy(link);
}

void test2_link_get_opposite_direction() {
  PRINT_TEST_RESULT(link_get_opposite_direction(NULL) == U);
}

