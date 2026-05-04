/**
 * @brief It tests the numen module
 *
 * @file numen_test.c
 * @author Javier Jarque
 * @version 1.0
 * @date 30-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numen.h"
#include "numen_test.h"
#include "test.h"

/*
 * These functions are implemented in the current numen.c, but they are not
 * declared in the current numen.h. They are declared here only so this test
 * file can compile without modifying the module.
 */
Status numen_add_skill(Numen *numen, Id skill_id);
Id numen_get_skill_by_id(Numen *numen, Id skill_id);
Skills_id numen_get_skill_by_index(Numen *numen, int skill_indx);

#define MAX_TESTS 65

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Numen:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_numen_create();
  if (all || test == 2)  test2_numen_create();
  if (all || test == 3)  test1_numen_destroy();
  if (all || test == 4)  test2_numen_destroy();
  if (all || test == 5)  test1_numen_set_id();
  if (all || test == 6)  test2_numen_set_id();
  if (all || test == 7)  test1_numen_get_id();
  if (all || test == 8)  test2_numen_get_id();
  if (all || test == 9)  test1_numen_set_name();
  if (all || test == 10) test2_numen_set_name();
  if (all || test == 11) test3_numen_set_name();
  if (all || test == 12) test1_numen_get_name();
  if (all || test == 13) test2_numen_get_name();
  if (all || test == 14) test1_numen_has_name();
  if (all || test == 15) test2_numen_has_name();
  if (all || test == 16) test3_numen_has_name();
  if (all || test == 17) test1_numen_set_gdesc();
  if (all || test == 18) test2_numen_set_gdesc();
  if (all || test == 19) test3_numen_set_gdesc();
  if (all || test == 20) test1_numen_get_gdesc();
  if (all || test == 21) test2_numen_get_gdesc();
  if (all || test == 22) test1_numen_set_position();
  if (all || test == 23) test2_numen_set_position();
  if (all || test == 24) test1_numen_set_pos_x();
  if (all || test == 25) test2_numen_set_pos_x();
  if (all || test == 26) test1_numen_get_pos_x();
  if (all || test == 27) test2_numen_get_pos_x();
  if (all || test == 28) test1_numen_set_pos_y();
  if (all || test == 29) test2_numen_set_pos_y();
  if (all || test == 30) test1_numen_get_pos_y();
  if (all || test == 31) test2_numen_get_pos_y();
  if (all || test == 32) test1_numen_set_health();
  if (all || test == 33) test2_numen_set_health();
  if (all || test == 34) test1_numen_get_health();
  if (all || test == 35) test2_numen_get_health();
  if (all || test == 36) test1_numen_set_attack();
  if (all || test == 37) test2_numen_set_attack();
  if (all || test == 38) test1_numen_get_attack();
  if (all || test == 39) test2_numen_get_attack();
  if (all || test == 40) test1_numen_set_energy();
  if (all || test == 41) test2_numen_set_energy();
  if (all || test == 42) test1_numen_get_energy();
  if (all || test == 43) test2_numen_get_energy();
  if (all || test == 44) test1_numen_set_speed();
  if (all || test == 45) test2_numen_set_speed();
  if (all || test == 46) test1_numen_get_speed();
  if (all || test == 47) test2_numen_get_speed();
  if (all || test == 48) test1_numen_set_following();
  if (all || test == 49) test2_numen_set_following();
  if (all || test == 50) test1_numen_get_following();
  if (all || test == 51) test2_numen_get_following();
  if (all || test == 52) test1_numen_is_errant();
  if (all || test == 53) test2_numen_is_errant();
  if (all || test == 54) test1_numen_set_corrupt();
  if (all || test == 55) test2_numen_set_corrupt();
  if (all || test == 56) test1_numen_get_corrupt();
  if (all || test == 57) test2_numen_get_corrupt();
  if (all || test == 58) test1_numen_add_skill();
  if (all || test == 59) test2_numen_add_skill();
  if (all || test == 60) test1_numen_get_skill_by_id();
  if (all || test == 61) test2_numen_get_skill_by_id();
  if (all || test == 62) test1_numen_get_skill_by_index();
  if (all || test == 63) test2_numen_get_skill_by_index();
  if (all || test == 64) test1_numen_print();
  if (all || test == 65) test2_numen_print();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== numen_create ========== */
void test1_numen_create() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(n != NULL);
  numen_destroy(n);
}

void test2_numen_create() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_get_id(n) == NO_ID);
  numen_destroy(n);
}

/* ========== numen_destroy ========== */
void test1_numen_destroy() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_destroy(n) == OK);
}

void test2_numen_destroy() {
  PRINT_TEST_RESULT(numen_destroy(NULL) == ERROR);
}

/* ========== numen_set_id / numen_get_id ========== */
void test1_numen_set_id() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_id(n, 50) == OK);
  numen_destroy(n);
}

void test2_numen_set_id() {
  PRINT_TEST_RESULT(numen_set_id(NULL, 50) == ERROR);
}

void test1_numen_get_id() {
  Numen *n = numen_create();
  numen_set_id(n, 50);
  PRINT_TEST_RESULT(numen_get_id(n) == 50);
  numen_destroy(n);
}

void test2_numen_get_id() {
  PRINT_TEST_RESULT(numen_get_id(NULL) == NO_ID);
}

/* ========== numen_set_name / numen_get_name / numen_has_name ========== */
void test1_numen_set_name() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_name(n, "Eidon") == OK);
  numen_destroy(n);
}

void test2_numen_set_name() {
  PRINT_TEST_RESULT(numen_set_name(NULL, "Eidon") == ERROR);
}

void test3_numen_set_name() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_name(n, NULL) == ERROR);
  numen_destroy(n);
}

void test1_numen_get_name() {
  Numen *n = numen_create();
  char *name;

  numen_set_name(n, "Eidon");
  name = numen_get_name(n);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Eidon") == 0);
  free(name);
  numen_destroy(n);
}

void test2_numen_get_name() {
  PRINT_TEST_RESULT(numen_get_name(NULL) == NULL);
}

void test1_numen_has_name() {
  Numen *n = numen_create();
  numen_set_name(n, "Eidon");
  PRINT_TEST_RESULT(numen_has_name(n, "Eidon") == TRUE);
  numen_destroy(n);
}

void test2_numen_has_name() {
  Numen *n = numen_create();
  numen_set_name(n, "Eidon");
  PRINT_TEST_RESULT(numen_has_name(n, "Other") == FALSE);
  numen_destroy(n);
}

void test3_numen_has_name() {
  PRINT_TEST_RESULT(numen_has_name(NULL, "Eidon") == FALSE);
}

/* ========== numen_set_gdesc / numen_get_gdesc ========== */
void test1_numen_set_gdesc() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_gdesc(n, "^N>") == OK);
  numen_destroy(n);
}

void test2_numen_set_gdesc() {
  PRINT_TEST_RESULT(numen_set_gdesc(NULL, "^N>") == ERROR);
}

void test3_numen_set_gdesc() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_gdesc(n, NULL) == ERROR);
  numen_destroy(n);
}

void test1_numen_get_gdesc() {
  Numen *n = numen_create();
  char *gdesc;

  numen_set_gdesc(n, "^N>");
  gdesc = numen_get_gdesc(n);
  PRINT_TEST_RESULT(gdesc != NULL && strcmp(gdesc, "^N>") == 0);
  free(gdesc);
  numen_destroy(n);
}

void test2_numen_get_gdesc() {
  PRINT_TEST_RESULT(numen_get_gdesc(NULL) == NULL);
}

/* ========== position ========== */
void test1_numen_set_position() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_position(n, 1, 2) == OK);
  numen_destroy(n);
}

void test2_numen_set_position() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_position(n, -1, 2) == ERROR);
  numen_destroy(n);
}

void test1_numen_set_pos_x() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_pos_x(n, 3) == OK);
  numen_destroy(n);
}

void test2_numen_set_pos_x() {
  PRINT_TEST_RESULT(numen_set_pos_x(NULL, 3) == ERROR);
}

void test1_numen_get_pos_x() {
  Numen *n = numen_create();
  numen_set_pos_x(n, 3);
  PRINT_TEST_RESULT(numen_get_pos_x(n) == 3);
  numen_destroy(n);
}

void test2_numen_get_pos_x() {
  PRINT_TEST_RESULT(numen_get_pos_x(NULL) == -1);
}

void test1_numen_set_pos_y() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_pos_y(n, 4) == OK);
  numen_destroy(n);
}

void test2_numen_set_pos_y() {
  PRINT_TEST_RESULT(numen_set_pos_y(NULL, 4) == ERROR);
}

void test1_numen_get_pos_y() {
  Numen *n = numen_create();
  numen_set_pos_y(n, 4);
  PRINT_TEST_RESULT(numen_get_pos_y(n) == 4);
  numen_destroy(n);
}

void test2_numen_get_pos_y() {
  PRINT_TEST_RESULT(numen_get_pos_y(NULL) == -1);
}

/* ========== health ========== */
void test1_numen_set_health() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_health(n, 5) == OK);
  numen_destroy(n);
}

void test2_numen_set_health() {
  PRINT_TEST_RESULT(numen_set_health(NULL, 5) == ERROR);
}

void test1_numen_get_health() {
  Numen *n = numen_create();
  numen_set_health(n, 5);
  PRINT_TEST_RESULT(numen_get_health(n) == 5);
  numen_destroy(n);
}

void test2_numen_get_health() {
  PRINT_TEST_RESULT(numen_get_health(NULL) == ERROR_LIFE);
}

/* ========== attack ========== */
void test1_numen_set_attack() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_attack(n, 2) == OK);
  numen_destroy(n);
}

void test2_numen_set_attack() {
  PRINT_TEST_RESULT(numen_set_attack(NULL, 2) == ERROR);
}

void test1_numen_get_attack() {
  Numen *n = numen_create();
  numen_set_attack(n, 2);
  PRINT_TEST_RESULT(numen_get_attack(n) == 2);
  numen_destroy(n);
}

void test2_numen_get_attack() {
  PRINT_TEST_RESULT(numen_get_attack(NULL) == ERROR_ATTACK);
}

/* ========== energy ========== */
void test1_numen_set_energy() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_energy(n, 7) == OK);
  numen_destroy(n);
}

void test2_numen_set_energy() {
  PRINT_TEST_RESULT(numen_set_energy(NULL, 7) == ERROR);
}

void test1_numen_get_energy() {
  Numen *n = numen_create();
  numen_set_energy(n, 7);
  PRINT_TEST_RESULT(numen_get_energy(n) == 7);
  numen_destroy(n);
}

void test2_numen_get_energy() {
  PRINT_TEST_RESULT(numen_get_energy(NULL) == ERROR_ENGY);
}

/* ========== speed ========== */
void test1_numen_set_speed() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_speed(n, 4) == OK);
  numen_destroy(n);
}

void test2_numen_set_speed() {
  PRINT_TEST_RESULT(numen_set_speed(NULL, 4) == ERROR);
}

void test1_numen_get_speed() {
  Numen *n = numen_create();
  numen_set_speed(n, 4);
  PRINT_TEST_RESULT(numen_get_speed(n) == 4);
  numen_destroy(n);
}

void test2_numen_get_speed() {
  PRINT_TEST_RESULT(numen_get_speed(NULL) == 0);
}

/* ========== following / is_errant ========== */
void test1_numen_set_following() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_following(n, 10) == OK);
  numen_destroy(n);
}

void test2_numen_set_following() {
  PRINT_TEST_RESULT(numen_set_following(NULL, 10) == ERROR);
}

void test1_numen_get_following() {
  Numen *n = numen_create();
  numen_set_following(n, 10);
  PRINT_TEST_RESULT(numen_get_following(n) == 10);
  numen_destroy(n);
}

void test2_numen_get_following() {
  PRINT_TEST_RESULT(numen_get_following(NULL) == NO_ID);
}

void test1_numen_is_errant() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_is_errant(n) == TRUE);
  numen_destroy(n);
}

void test2_numen_is_errant() {
  Numen *n = numen_create();
  numen_set_following(n, 10);
  PRINT_TEST_RESULT(numen_is_errant(n) == FALSE);
  numen_destroy(n);
}

/* ========== corrupt ========== */
void test1_numen_set_corrupt() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_set_corrupt(n, TRUE) == OK);
  numen_destroy(n);
}

void test2_numen_set_corrupt() {
  PRINT_TEST_RESULT(numen_set_corrupt(NULL, TRUE) == ERROR);
}

void test1_numen_get_corrupt() {
  Numen *n = numen_create();
  numen_set_corrupt(n, TRUE);
  PRINT_TEST_RESULT(numen_get_corrupt(n) == TRUE);
  numen_destroy(n);
}

void test2_numen_get_corrupt() {
  PRINT_TEST_RESULT(numen_get_corrupt(NULL) == FALSE);
}

/* ========== skills ========== */
void test1_numen_add_skill() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_add_skill(n, TAKLE) == OK);
  numen_destroy(n);
}

void test2_numen_add_skill() {
  PRINT_TEST_RESULT(numen_add_skill(NULL, TAKLE) == ERROR);
}

void test1_numen_get_skill_by_id() {
  Numen *n = numen_create();
  numen_add_skill(n, TAKLE);
  PRINT_TEST_RESULT(numen_get_skill_by_id(n, TAKLE) == TAKLE);
  numen_destroy(n);
}

void test2_numen_get_skill_by_id() {
  PRINT_TEST_RESULT(numen_get_skill_by_id(NULL, TAKLE) == NO_ID);
}

void test1_numen_get_skill_by_index() {
  Numen *n = numen_create();
  numen_add_skill(n, TAKLE);
  PRINT_TEST_RESULT(numen_get_skill_by_index(n, 0) == TAKLE);
  numen_destroy(n);
}

void test2_numen_get_skill_by_index() {
  PRINT_TEST_RESULT(numen_get_skill_by_index(NULL, 0) == NO_SKILL);
}

/* ========== print ========== */
void test1_numen_print() {
  Numen *n = numen_create();
  PRINT_TEST_RESULT(numen_print(n) == OK);
  numen_destroy(n);
}

void test2_numen_print() {
  PRINT_TEST_RESULT(numen_print(NULL) == ERROR);
}
