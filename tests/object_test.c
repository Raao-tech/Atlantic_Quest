/**
 * @brief It tests the object module
 *
 * @file object_test.c
 * @author Rafael y Violeta
 * @version 1
 * @date 12-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 24

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  /* obj_create */
  if (all || test == 1)  test1_obj_create();
  if (all || test == 2)  test2_obj_create();

  /* obj_destroy */
  if (all || test == 3)  test1_obj_destroy();
  if (all || test == 4)  test2_obj_destroy();

  /* obj_set_id / get_id */
  if (all || test == 5)  test1_obj_set_id();
  if (all || test == 6)  test2_obj_set_id();
  if (all || test == 7)  test1_obj_get_id();
  if (all || test == 8)  test2_obj_get_id();

  /* obj_set_name / get_name / has_name */
  if (all || test == 9)  test1_obj_set_name();
  if (all || test == 10) test2_obj_set_name();
  if (all || test == 11) test3_obj_set_name();
  if (all || test == 12) test1_obj_get_name();
  if (all || test == 13) test2_obj_get_name();
  if (all || test == 14) test1_obj_has_name();
  if (all || test == 15) test2_obj_has_name();
  if (all || test == 16) test3_obj_has_name();

  /* obj_set_description / get_description / has_description */
  if (all || test == 17) test1_obj_set_description();
  if (all || test == 18) test2_obj_set_description();
  if (all || test == 19) test3_obj_set_description();
  if (all || test == 20) test1_obj_get_description();
  if (all || test == 21) test2_obj_get_description();
  if (all || test == 22) test1_obj_has_description();
  if (all || test == 23) test2_obj_has_description();
  if (all || test == 24) test3_obj_has_description();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}


/* ========== obj_create ========== */

/* Test 1: create returns non-NULL */
void test1_obj_create() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(o != NULL);
  obj_destroy(o);
}

/* Test 2: create initializes id to NO_ID */
void test2_obj_create() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_get_id(o) == NO_ID);
  obj_destroy(o);
}


/* ========== obj_destroy ========== */

/* Test 1: destroy valid object returns OK */
void test1_obj_destroy() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_destroy(o) == OK);
}

/* Test 2: destroy NULL returns ERROR */
void test2_obj_destroy() {
  PRINT_TEST_RESULT(obj_destroy(NULL) == ERROR);
}


/* ========== obj_set_id / obj_get_id ========== */

/* Test 1: set_id with valid object returns OK */
void test1_obj_set_id() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_set_id(o, 21) == OK);
  obj_destroy(o);
}

/* Test 2: set_id with NULL returns ERROR */
void test2_obj_set_id() {
  PRINT_TEST_RESULT(obj_set_id(NULL, 21) == ERROR);
}

/* Test 1: get_id returns the value that was set */
void test1_obj_get_id() {
  Object *o = obj_create();
  obj_set_id(o, 42);
  PRINT_TEST_RESULT(obj_get_id(o) == 42);
  obj_destroy(o);
}

/* Test 2: get_id with NULL returns NO_ID */
void test2_obj_get_id() {
  PRINT_TEST_RESULT(obj_get_id(NULL) == NO_ID);
}


/* ========== obj_set_name / obj_get_name / obj_has_name ========== */

/* Test 1: set_name with valid params returns OK */
void test1_obj_set_name() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_set_name(o, "Sword") == OK);
  obj_destroy(o);
}

/* Test 2: set_name with NULL object returns ERROR */
void test2_obj_set_name() {
  PRINT_TEST_RESULT(obj_set_name(NULL, "Sword") == ERROR);
}

/* Test 3: set_name with NULL name returns ERROR */
void test3_obj_set_name() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_set_name(o, NULL) == ERROR);
  obj_destroy(o);
}

/* Test 1: get_name returns the name that was set */
void test1_obj_get_name() {
  Object *o = obj_create();
  obj_set_name(o, "Sword");
  PRINT_TEST_RESULT(strcmp(obj_get_name(o), "Sword") == 0);
  obj_destroy(o);
}

/* Test 2: get_name with NULL returns NULL */
void test2_obj_get_name() {
  PRINT_TEST_RESULT(obj_get_name(NULL) == NULL);
}

/* Test 1: has_name returns TRUE for matching name */
void test1_obj_has_name() {
  Object *o = obj_create();
  obj_set_name(o, "Sword");
  PRINT_TEST_RESULT(obj_has_name(o, "Sword") == TRUE);
  obj_destroy(o);
}

/* Test 2: has_name returns FALSE for different name */
void test2_obj_has_name() {
  Object *o = obj_create();
  obj_set_name(o, "Sword");
  PRINT_TEST_RESULT(obj_has_name(o, "Shield") == FALSE);
  obj_destroy(o);
}

/* Test 3: has_name with NULL returns FALSE */
void test3_obj_has_name() {
  PRINT_TEST_RESULT(obj_has_name(NULL, "Sword") == FALSE);
}


/* ========== obj_set_description / obj_get_description / obj_has_description ========== */

/* Test 1: set_description with valid params returns OK */
void test1_obj_set_description() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_set_description(o, "A sharp blade") == OK);
  obj_destroy(o);
}

/* Test 2: set_description with NULL object returns ERROR */
void test2_obj_set_description() {
  PRINT_TEST_RESULT(obj_set_description(NULL, "A sharp blade") == ERROR);
}

/* Test 3: set_description with NULL description returns ERROR */
void test3_obj_set_description() {
  Object *o = obj_create();
  PRINT_TEST_RESULT(obj_set_description(o, NULL) == ERROR);
  obj_destroy(o);
}

/* Test 1: get_description returns what was set */
void test1_obj_get_description() {
  Object *o = obj_create();
  obj_set_description(o, "A sharp blade");
  PRINT_TEST_RESULT(strcmp(obj_get_description(o), "A sharp blade") == 0);
  obj_destroy(o);
}

/* Test 2: get_description with NULL returns NULL */
void test2_obj_get_description() {
  PRINT_TEST_RESULT(obj_get_description(NULL) == NULL);
}

/* Test 1: has_description returns TRUE for matching description */
void test1_obj_has_description() {
  Object *o = obj_create();
  obj_set_description(o, "A sharp blade");
  PRINT_TEST_RESULT(obj_has_description(o, "A sharp blade") == TRUE);
  obj_destroy(o);
}

/* Test 2: has_description returns FALSE for different description */
void test2_obj_has_description() {
  Object *o = obj_create();
  obj_set_description(o, "A sharp blade");
  PRINT_TEST_RESULT(obj_has_description(o, "A wooden shield") == FALSE);
  obj_destroy(o);
}

/* Test 3: has_description with NULL returns FALSE */
void test3_obj_has_description() {
  PRINT_TEST_RESULT(obj_has_description(NULL, "A sharp blade") == FALSE);
}