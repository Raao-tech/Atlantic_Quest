/**
 * @brief It tests the entity module
 *
 * @file entity_test.c
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entity.h"
#include "entity_test.h"
#include "test.h"

#define MAX_TESTS 30

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Entity:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_entity_create();
  if (all || test == 2)  test2_entity_create();
  if (all || test == 3)  test1_entity_destroy();
  if (all || test == 4)  test2_entity_destroy();
  if (all || test == 5)  test1_entity_set_id();
  if (all || test == 6)  test2_entity_set_id();
  if (all || test == 7)  test1_entity_get_id();
  if (all || test == 8)  test2_entity_get_id();
  if (all || test == 9)  test1_entity_set_name();
  if (all || test == 10) test2_entity_set_name();
  if (all || test == 11) test3_entity_set_name();
  if (all || test == 12) test1_entity_get_name();
  if (all || test == 13) test2_entity_get_name();
  if (all || test == 14) test1_entity_set_gdesc();
  if (all || test == 15) test2_entity_set_gdesc();
  if (all || test == 16) test1_entity_get_gdesc();
  if (all || test == 17) test2_entity_get_gdesc();
  if (all || test == 18) test1_entity_set_message();
  if (all || test == 19) test2_entity_set_message();
  if (all || test == 20) test1_entity_get_message();
  if (all || test == 21) test2_entity_get_message();
  if (all || test == 22) test1_entity_set_health();
  if (all || test == 23) test2_entity_set_health();
  if (all || test == 24) test3_entity_set_health();
  if (all || test == 25) test1_entity_get_health();
  if (all || test == 26) test2_entity_get_health();
  if (all || test == 27) test1_entity_set_attack();
  if (all || test == 28) test2_entity_set_attack();
  if (all || test == 29) test1_entity_get_attack();
  if (all || test == 30) test2_entity_get_attack();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== entity_create ========== */
void test1_entity_create() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(e != NULL);
  entity_destroy(e);
}

void test2_entity_create() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_get_health(e) == 0);
  entity_destroy(e);
}

/* ========== entity_destroy ========== */
void test1_entity_destroy() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_destroy(e) == OK);
}

void test2_entity_destroy() {
  PRINT_TEST_RESULT(entity_destroy(NULL) == ERROR);
}

/* ========== entity_set_id / get_id ========== */
void test1_entity_set_id() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_id(e, 42) == OK);
  entity_destroy(e);
}

void test2_entity_set_id() {
  PRINT_TEST_RESULT(entity_set_id(NULL, 42) == ERROR);
}

void test1_entity_get_id() {
  Entity *e = entity_create();
  entity_set_id(e, 42);
  PRINT_TEST_RESULT(entity_get_id(e) == 42);
  entity_destroy(e);
}

void test2_entity_get_id() {
  PRINT_TEST_RESULT(entity_get_id(NULL) == ERROR);
}

/* ========== entity_set_name / get_name ========== */
void test1_entity_set_name() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_name(e, "Warrior") == OK);
  entity_destroy(e);
}

void test2_entity_set_name() {
  PRINT_TEST_RESULT(entity_set_name(NULL, "Warrior") == ERROR);
}

void test3_entity_set_name() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_name(e, NULL) == ERROR);
  entity_destroy(e);
}

void test1_entity_get_name() {
  Entity *e = entity_create();
  char *name;
  entity_set_name(e, "Warrior");
  name = entity_get_name(e);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Warrior") == 0);
  free(name);
  entity_destroy(e);
}

void test2_entity_get_name() {
  PRINT_TEST_RESULT(entity_get_name(NULL) == NULL);
}

/* ========== entity_set_gdesc / get_gdesc ========== */
void test1_entity_set_gdesc() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_gdesc(e, "^C>") == OK);
  entity_destroy(e);
}

void test2_entity_set_gdesc() {
  PRINT_TEST_RESULT(entity_set_gdesc(NULL, "^C>") == ERROR);
}

void test1_entity_get_gdesc() {
  Entity *e = entity_create();
  char *gdesc;
  entity_set_gdesc(e, "^C>");
  gdesc = entity_get_gdesc(e);
  PRINT_TEST_RESULT(gdesc != NULL && strcmp(gdesc, "^C>") == 0);
  free(gdesc);
  entity_destroy(e);
}

void test2_entity_get_gdesc() {
  PRINT_TEST_RESULT(entity_get_gdesc(NULL) == NULL);
}

/* ========== entity_set_message / get_message ========== */
void test1_entity_set_message() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_message(e, "Hello traveler!") == OK);
  entity_destroy(e);
}

void test2_entity_set_message() {
  PRINT_TEST_RESULT(entity_set_message(NULL, "Hello") == ERROR);
}

void test1_entity_get_message() {
  Entity *e = entity_create();
  char *msg;
  entity_set_message(e, "Hello traveler!");
  msg = entity_get_message(e);
  PRINT_TEST_RESULT(msg != NULL && strcmp(msg, "Hello traveler!") == 0);
  free(msg);
  entity_destroy(e);
}

void test2_entity_get_message() {
  PRINT_TEST_RESULT(entity_get_message(NULL) == NULL);
}

/* ========== entity_set_health / get_health ========== */
void test1_entity_set_health() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_health(e, 5) == OK);
  entity_destroy(e);
}

/* Out of bounds: MAX_LIFE + 1 */
void test2_entity_set_health() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_health(e, MAX_LIFE + 1) == ERROR);
  entity_destroy(e);
}

/* Out of bounds: MIN_LIFE - 1 */
void test3_entity_set_health() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_health(e, MIN_LIFE - 1) == ERROR);
  entity_destroy(e);
}

void test1_entity_get_health() {
  Entity *e = entity_create();
  entity_set_health(e, 7);
  PRINT_TEST_RESULT(entity_get_health(e) == 7);
  entity_destroy(e);
}

void test2_entity_get_health() {
  PRINT_TEST_RESULT(entity_get_health(NULL) == ERROR_LIFE);
}

/* ========== entity_set_attack / get_attack ========== */
void test1_entity_set_attack() {
  Entity *e = entity_create();
  PRINT_TEST_RESULT(entity_set_attack(e, 3) == OK);
  entity_destroy(e);
}

void test2_entity_set_attack() {
  PRINT_TEST_RESULT(entity_set_attack(NULL, 3) == ERROR);
}

void test1_entity_get_attack() {
  Entity *e = entity_create();
  entity_set_attack(e, 3);
  PRINT_TEST_RESULT(entity_get_attack(e) == 3);
  entity_destroy(e);
}

void test2_entity_get_attack() {
  PRINT_TEST_RESULT(entity_get_attack(NULL) == ERROR_ATTACK);
}
