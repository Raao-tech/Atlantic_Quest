/**
 * @brief It tests the character module
 *
 * @file character_test.c
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"

#define MAX_TESTS 34

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_character_create();
  if (all || test == 2)  test2_character_create();
  if (all || test == 3)  test1_character_destroy();
  if (all || test == 4)  test2_character_destroy();
  if (all || test == 5)  test1_character_set_id();
  if (all || test == 6)  test2_character_set_id();
  if (all || test == 7)  test1_character_get_id();
  if (all || test == 8)  test2_character_get_id();
  if (all || test == 9)  test1_character_set_name();
  if (all || test == 10) test2_character_set_name();
  if (all || test == 11) test3_character_set_name();
  if (all || test == 12) test1_character_get_name();
  if (all || test == 13) test2_character_get_name();
  if (all || test == 14) test1_character_set_gdesc();
  if (all || test == 15) test2_character_set_gdesc();
  if (all || test == 16) test1_character_get_gdesc();
  if (all || test == 17) test2_character_get_gdesc();
  if (all || test == 18) test1_character_set_message();
  if (all || test == 19) test2_character_set_message();
  if (all || test == 20) test1_character_get_message();
  if (all || test == 21) test2_character_get_message();
  if (all || test == 22) test1_character_set_health();
  if (all || test == 23) test2_character_set_health();
  if (all || test == 24) test1_character_get_health();
  if (all || test == 25) test2_character_get_health();
  if (all || test == 26) test1_character_set_attack();
  if (all || test == 27) test2_character_set_attack();
  if (all || test == 28) test1_character_get_attack();
  if (all || test == 29) test2_character_get_attack();
  if (all || test == 30) test1_character_set_friendly();
  if (all || test == 31) test2_character_set_friendly();
  if (all || test == 32) test1_character_get_friendly();
  if (all || test == 33) test2_character_get_friendly();
  if (all || test == 34) test2_character_get_friendly();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== character_create ========== */
void test1_character_create() {
  Character *c = character_create();
  PRINT_TEST_RESULT(c != NULL);
  character_destroy(c);
}

void test2_character_create() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}

/* ========== character_destroy ========== */
void test1_character_destroy() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_destroy(c) == OK);
}

void test2_character_destroy() {
  PRINT_TEST_RESULT(character_destroy(NULL) == ERROR);
}

/* ========== character_set_id / get_id ========== */
void test1_character_set_id() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_id(c, 50) == OK);
  character_destroy(c);
}

void test2_character_set_id() {
  PRINT_TEST_RESULT(character_set_id(NULL, 50) == ERROR);
}

void test1_character_get_id() {
  Character *c = character_create();
  character_set_id(c, 50);
  PRINT_TEST_RESULT(character_get_id(c) == 50);
  character_destroy(c);
}

void test2_character_get_id() {
  PRINT_TEST_RESULT(character_get_id(NULL) == NO_ID);
}

/* ========== character_set_name / get_name ========== */
void test1_character_set_name() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_name(c, "Goblin") == OK);
  character_destroy(c);
}

void test2_character_set_name() {
  PRINT_TEST_RESULT(character_set_name(NULL, "Goblin") == ERROR);
}

void test3_character_set_name() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_name(c, NULL) == ERROR);
  character_destroy(c);
}

void test1_character_get_name() {
  Character *c = character_create();
  char *name;
  character_set_name(c, "Goblin");
  name = character_get_name(c);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Goblin") == 0);
  free(name);
  character_destroy(c);
}

void test2_character_get_name() {
  PRINT_TEST_RESULT(character_get_name(NULL) == NULL);
}

/* ========== character_set_gdesc / get_gdesc ========== */
void test1_character_set_gdesc() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_gdesc(c, "^C>") == OK);
  character_destroy(c);
}

void test2_character_set_gdesc() {
  PRINT_TEST_RESULT(character_set_gdesc(NULL, "^C>") == ERROR);
}

void test1_character_get_gdesc() {
  Character *c = character_create();
  char *gdesc;
  character_set_gdesc(c, "^C>");
  gdesc = character_get_gdesc(c);
  PRINT_TEST_RESULT(gdesc != NULL && strcmp(gdesc, "^C>") == 0);
  free(gdesc);
  character_destroy(c);
}

void test2_character_get_gdesc() {
  PRINT_TEST_RESULT(character_get_gdesc(NULL) == NULL);
}

/* ========== character_set_message / get_message ========== */
void test1_character_set_message() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_message(c, "Welcome!") == OK);
  character_destroy(c);
}

void test2_character_set_message() {
  PRINT_TEST_RESULT(character_set_message(NULL, "Welcome!") == ERROR);
}

void test1_character_get_message() {
  Character *c = character_create();
  char *msg;
  character_set_message(c, "Welcome!");
  msg = character_get_message(c);
  PRINT_TEST_RESULT(msg != NULL && strcmp(msg, "Welcome!") == 0);
  free(msg);
  character_destroy(c);
}

void test2_character_get_message() {
  PRINT_TEST_RESULT(character_get_message(NULL) == NULL);
}

/* ========== character_set_health / get_health ========== */
void test1_character_set_health() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_health(c, 5) == OK);
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_health(c, MAX_LIFE + 1) == ERROR);
  character_destroy(c);
}

void test1_character_get_health() {
  Character *c = character_create();
  character_set_health(c, 5);
  PRINT_TEST_RESULT(character_get_health(c) == 5);
  character_destroy(c);
}

void test2_character_get_health() {
  PRINT_TEST_RESULT(character_get_health(NULL) == ERROR_LIFE);
}

/* ========== character_set_attack / get_attack ========== */
void test1_character_set_attack() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_attack(c, 2) == OK);
  character_destroy(c);
}

void test2_character_set_attack() {
  PRINT_TEST_RESULT(character_set_attack(NULL, 2) == ERROR);
}

void test1_character_get_attack() {
  Character *c = character_create();
  character_set_attack(c, 2);
  PRINT_TEST_RESULT(character_get_attack(c) == 2);
  character_destroy(c);
}

void test2_character_get_attack() {
  PRINT_TEST_RESULT(character_get_attack(NULL) == ERROR_ATTACK);
}

/* ========== character_set_friendly / get_friendly ========== */
void test1_character_set_friendly() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_set_friendly(c, FALSE) == OK);
  character_destroy(c);
}

void test2_character_set_friendly() {
  PRINT_TEST_RESULT(character_set_friendly(NULL, FALSE) == ERROR);
}

void test1_character_get_friendly() {
  Character *c = character_create();
  character_set_friendly(c, FALSE);
  PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
  character_destroy(c);
}

/* Default is TRUE */
void test2_character_get_friendly() {
  Character *c = character_create();
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}
