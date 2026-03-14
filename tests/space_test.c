/**
 * @brief It tests the space module
 *
 * @file space_test.c
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 50

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_space_create();
  if (all || test == 2)  test2_space_create();
  if (all || test == 3)  test1_space_destroy();
  if (all || test == 4)  test2_space_destroy();
  if (all || test == 5)  test1_space_set_id();
  if (all || test == 6)  test2_space_set_id();
  if (all || test == 7)  test1_space_get_id();
  if (all || test == 8)  test2_space_get_id();
  if (all || test == 9)  test1_space_set_name();
  if (all || test == 10) test2_space_set_name();
  if (all || test == 11) test3_space_set_name();
  if (all || test == 12) test1_space_get_name();
  if (all || test == 13) test2_space_get_name();
  if (all || test == 14) test1_space_set_north();
  if (all || test == 15) test2_space_set_north();
  if (all || test == 16) test1_space_get_north();
  if (all || test == 17) test2_space_get_north();
  if (all || test == 18) test1_space_set_south();
  if (all || test == 19) test2_space_set_south();
  if (all || test == 20) test1_space_get_south();
  if (all || test == 21) test2_space_get_south();
  if (all || test == 22) test1_space_set_east();
  if (all || test == 23) test2_space_set_east();
  if (all || test == 24) test1_space_get_east();
  if (all || test == 25) test2_space_get_east();
  if (all || test == 26) test1_space_set_west();
  if (all || test == 27) test2_space_set_west();
  if (all || test == 28) test1_space_get_west();
  if (all || test == 29) test2_space_get_west();
  if (all || test == 30) test1_space_set_object();
  if (all || test == 31) test2_space_set_object();
  if (all || test == 32) test1_space_contains_object();
  if (all || test == 33) test2_space_contains_object();
  if (all || test == 34) test3_space_contains_object();
  if (all || test == 35) test1_space_remove_object();
  if (all || test == 36) test2_space_remove_object();
  if (all || test == 37) test1_space_get_n_objects();
  if (all || test == 38) test2_space_get_n_objects();
  if (all || test == 39) test1_space_set_character();
  if (all || test == 40) test2_space_set_character();
  if (all || test == 41) test1_space_contains_character();
  if (all || test == 42) test2_space_contains_character();
  if (all || test == 43) test1_space_remove_character();
  if (all || test == 44) test2_space_remove_character();
  if (all || test == 45) test1_space_get_n_characters();
  if (all || test == 46) test2_space_get_n_characters();
  if (all || test == 47) test1_space_set_gdesc_line();
  if (all || test == 48) test2_space_set_gdesc_line();
  if (all || test == 49) test3_space_set_gdesc_line();
  if (all || test == 50) test1_space_get_gdesc();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== space_create ========== */
void test1_space_create() {
  Space *s = space_create();
  PRINT_TEST_RESULT(s != NULL);
  space_destroy(s);
}

void test2_space_create() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
  space_destroy(s);
}

/* ========== space_destroy ========== */
void test1_space_destroy() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_destroy(s) == OK);
}

void test2_space_destroy() {
  PRINT_TEST_RESULT(space_destroy(NULL) == ERROR);
}

/* ========== space_set_id / get_id ========== */
void test1_space_set_id() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_id(s, 25) == OK);
  space_destroy(s);
}

void test2_space_set_id() {
  PRINT_TEST_RESULT(space_set_id(NULL, 25) == ERROR);
}

void test1_space_get_id() {
  Space *s = space_create();
  space_set_id(s, 25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

void test2_space_get_id() {
  PRINT_TEST_RESULT(space_get_id(NULL) == NO_ID);
}

/* ========== space_set_name / get_name ========== */
void test1_space_set_name() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_name(s, "Entry") == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  PRINT_TEST_RESULT(space_set_name(NULL, "Entry") == ERROR);
}

void test3_space_set_name() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_get_name() {
  Space *s = space_create();
  space_set_name(s, "Entry");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "Entry") == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  PRINT_TEST_RESULT(space_get_name(NULL) == NULL);
}

/* ========== space_set_north / get_north ========== */
void test1_space_set_north() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_north(s, 4) == OK);
  space_destroy(s);
}

void test2_space_set_north() {
  PRINT_TEST_RESULT(space_set_north(NULL, 4) == ERROR);
}

void test1_space_get_north() {
  Space *s = space_create();
  space_set_north(s, 4);
  PRINT_TEST_RESULT(space_get_north(s) == 4);
  space_destroy(s);
}

void test2_space_get_north() {
  PRINT_TEST_RESULT(space_get_north(NULL) == NO_ID);
}

/* ========== space_set_south / get_south ========== */
void test1_space_set_south() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_south(s, 2) == OK);
  space_destroy(s);
}

void test2_space_set_south() {
  PRINT_TEST_RESULT(space_set_south(NULL, 2) == ERROR);
}

void test1_space_get_south() {
  Space *s = space_create();
  space_set_south(s, 2);
  PRINT_TEST_RESULT(space_get_south(s) == 2);
  space_destroy(s);
}

void test2_space_get_south() {
  PRINT_TEST_RESULT(space_get_south(NULL) == NO_ID);
}

/* ========== space_set_east / get_east ========== */
void test1_space_set_east() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_east(s, 1) == OK);
  space_destroy(s);
}

void test2_space_set_east() {
  PRINT_TEST_RESULT(space_set_east(NULL, 1) == ERROR);
}

void test1_space_get_east() {
  Space *s = space_create();
  space_set_east(s, 1);
  PRINT_TEST_RESULT(space_get_east(s) == 1);
  space_destroy(s);
}

void test2_space_get_east() {
  PRINT_TEST_RESULT(space_get_east(NULL) == NO_ID);
}

/* ========== space_set_west / get_west ========== */
void test1_space_set_west() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_west(s, 6) == OK);
  space_destroy(s);
}

void test2_space_set_west() {
  PRINT_TEST_RESULT(space_set_west(NULL, 6) == ERROR);
}

void test1_space_get_west() {
  Space *s = space_create();
  space_set_west(s, 6);
  PRINT_TEST_RESULT(space_get_west(s) == 6);
  space_destroy(s);
}

void test2_space_get_west() {
  PRINT_TEST_RESULT(space_get_west(NULL) == NO_ID);
}

/* ========== space_set_object / contains / remove / get_n ========== */
void test1_space_set_object() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_object(s, 21) == OK);
  space_destroy(s);
}

void test2_space_set_object() {
  PRINT_TEST_RESULT(space_set_object(NULL, 21) == ERROR);
}

void test1_space_contains_object() {
  Space *s = space_create();
  space_set_object(s, 21);
  PRINT_TEST_RESULT(space_contains_object(s, 21) == TRUE);
  space_destroy(s);
}

void test2_space_contains_object() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_contains_object(s, 999) == FALSE);
  space_destroy(s);
}

void test3_space_contains_object() {
  PRINT_TEST_RESULT(space_contains_object(NULL, 21) == FALSE);
}

void test1_space_remove_object() {
  Space *s = space_create();
  space_set_object(s, 21);
  PRINT_TEST_RESULT(space_remove_object(s, 21) == OK && space_contains_object(s, 21) == FALSE);
  space_destroy(s);
}

void test2_space_remove_object() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_remove_object(s, 999) == ERROR);
  space_destroy(s);
}

void test1_space_get_n_objects() {
  Space *s = space_create();
  space_set_object(s, 21);
  space_set_object(s, 22);
  PRINT_TEST_RESULT(space_get_n_objects(s) == 2);
  space_destroy(s);
}

void test2_space_get_n_objects() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_get_n_objects(s) == 0);
  space_destroy(s);
}

/* ========== space_set_character / contains / remove / get_n ========== */
void test1_space_set_character() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_character(s, 50) == OK);
  space_destroy(s);
}

void test2_space_set_character() {
  PRINT_TEST_RESULT(space_set_character(NULL, 50) == ERROR);
}

void test1_space_contains_character() {
  Space *s = space_create();
  space_set_character(s, 50);
  PRINT_TEST_RESULT(space_contains_character(s, 50) == TRUE);
  space_destroy(s);
}

void test2_space_contains_character() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_contains_character(s, 999) == FALSE);
  space_destroy(s);
}

void test1_space_remove_character() {
  Space *s = space_create();
  space_set_character(s, 50);
  PRINT_TEST_RESULT(space_remove_character(s, 50) == OK && space_contains_character(s, 50) == FALSE);
  space_destroy(s);
}

void test2_space_remove_character() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_remove_character(s, 999) == ERROR);
  space_destroy(s);
}

void test1_space_get_n_characters() {
  Space *s = space_create();
  space_set_character(s, 50);
  space_set_character(s, 51);
  PRINT_TEST_RESULT(space_get_n_characters(s) == 2);
  space_destroy(s);
}

void test2_space_get_n_characters() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_get_n_characters(s) == 0);
  space_destroy(s);
}

/* ========== space_set_gdesc_line / get_gdesc ========== */
void test1_space_set_gdesc_line() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_gdesc_line(s, 0, "  _ !#") == OK);
  space_destroy(s);
}

void test2_space_set_gdesc_line() {
  PRINT_TEST_RESULT(space_set_gdesc_line(NULL, 0, "  _ !#") == ERROR);
}

/* Line out of range */
void test3_space_set_gdesc_line() {
  Space *s = space_create();
  PRINT_TEST_RESULT(space_set_gdesc_line(s, MAX_LINE, "test") == ERROR);
  space_destroy(s);
}

void test1_space_get_gdesc() {
  Space *s = space_create();
  space_set_gdesc_line(s, 0, "  _ !#");
  PRINT_TEST_RESULT(space_get_gdesc(s, 0) != NULL && strcmp(space_get_gdesc(s, 0), "  _ !#") == 0);
  space_destroy(s);
}

void test2_space_get_gdesc() {
  PRINT_TEST_RESULT(space_get_gdesc(NULL, 0) == NULL);
}
