/**
 * @brief It tests the skill module
 *
 * @file skill_test.c
 * @author Javier
 * @version 1
 * @date 30-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skills.h"
#include "skill_test.h"
#include "test.h"

#define MAX_TESTS 11

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Skill:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_skill_active();
  if (all || test == 2)  test2_skill_active();
  if (all || test == 3)  test3_skill_active();
  if (all || test == 4)  test4_skill_active();
  if (all || test == 5)  test1_skill_get_name();
  if (all || test == 6)  test2_skill_get_name();
  if (all || test == 7)  test3_skill_get_name();
  if (all || test == 8)  test1_skill_get_radio();
  if (all || test == 9)  test2_skill_get_radio();
  if (all || test == 10) test3_skill_get_radio();
  if (all || test == 11) test4_skill_get_radio();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== skill_active ========== */
void test1_skill_active() {
  PRINT_TEST_RESULT(skill_active(NULL, (Numen *)1, TAKLE, 3, NULL, NULL) == ERROR);
}

void test2_skill_active() {
  PRINT_TEST_RESULT(skill_active((Numen *)1, NULL, TAKLE, 3, NULL, NULL) == ERROR);
}

void test3_skill_active() {
  PRINT_TEST_RESULT(skill_active((Numen *)1, (Numen *)1, NO_SKILL, 3, NULL, NULL) == ERROR);
}

void test4_skill_active() {
  PRINT_TEST_RESULT(skill_active((Numen *)1, (Numen *)1, TAKLE, -1, NULL, NULL) == ERROR);
}

/* ========== skill_get_name ========== */
void test1_skill_get_name() {
  char *name = skill_get_name(NO_SKILL);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Ninguna") == 0);
}

void test2_skill_get_name() {
  char *name = skill_get_name(TAKLE);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Tackle") == 0);
}

void test3_skill_get_name() {
  char *name = skill_get_name(FIRE_BALL_A);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Fire Ball Area") == 0);
}

/* ========== skill_get_radio ========== */
void test1_skill_get_radio() {
  PRINT_TEST_RESULT(skill_get_radio(NO_SKILL) == 0);
}

void test2_skill_get_radio() {
  PRINT_TEST_RESULT(skill_get_radio(TAKLE) == 3);
}

void test3_skill_get_radio() {
  PRINT_TEST_RESULT(skill_get_radio(QUICK_ATTACK) == 2);
}

void test4_skill_get_radio() {
  PRINT_TEST_RESULT(skill_get_radio((Skills_id)-1) == -1);
}
