/**
 * @brief It tests the set module
 *
 * @file set_test.c
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 20

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_set_creat();
  if (all || test == 2)  test2_set_creat();
  if (all || test == 3)  test1_set_destroy();
  if (all || test == 4)  test2_set_destroy();
  if (all || test == 5)  test1_set_add();
  if (all || test == 6)  test2_set_add();
  if (all || test == 7)  test3_set_add();
  if (all || test == 8)  test4_set_add();
  if (all || test == 9)  test1_set_delete_id();
  if (all || test == 10) test2_set_delete_id();
  if (all || test == 11) test3_set_delete_id();
  if (all || test == 12) test4_set_delete_id();
  if (all || test == 13) test1_set_contains_id();
  if (all || test == 14) test2_set_contains_id();
  if (all || test == 15) test3_set_contains_id();
  if (all || test == 16) test1_set_get_n_ids();
  if (all || test == 17) test2_set_get_n_ids();
  if (all || test == 18) test3_set_get_n_ids();
  if (all || test == 19) test1_set_print();
  if (all || test == 20) test2_set_print();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== set_creat ========== */
void test1_set_creat() {
  Set *s = set_creat();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

void test2_set_creat() {
  Set *s = set_creat();
  PRINT_TEST_RESULT(set_get_n_ids(s) == 0);
  set_destroy(s);
}

/* ========== set_destroy ========== */
void test1_set_destroy() {
  Set *s = set_creat();
  PRINT_TEST_RESULT(set_destroy(s) == OK);
}

void test2_set_destroy() {
  PRINT_TEST_RESULT(set_destroy(NULL) == ERROR);
}

/* ========== set_add ========== */
void test1_set_add() {
  Set *s = set_creat();
  PRINT_TEST_RESULT(set_add(s, 100) == OK);
  set_destroy(s);
}

void test2_set_add() {
  PRINT_TEST_RESULT(set_add(NULL, 100) == ERROR);
}

void test3_set_add() {
  Set *s = set_creat();
  PRINT_TEST_RESULT(set_add(s, NO_ID) == ERROR);
  set_destroy(s);
}

/* Duplicado: no añade pero devuelve OK */
void test4_set_add() {
  Set *s = set_creat();
  set_add(s, 100);
  PRINT_TEST_RESULT(set_add(s, 100) == OK && set_get_n_ids(s) == 1);
  set_destroy(s);
}

/* ========== set_delete_id ========== */
void test1_set_delete_id() {
  Set *s = set_creat();
  set_add(s, 100);
  PRINT_TEST_RESULT(set_delete_id(s, 100) == OK);
  set_destroy(s);
}

void test2_set_delete_id() {
  Set *s = set_creat();
  set_add(s, 100);
  set_delete_id(s, 100);
  PRINT_TEST_RESULT(set_get_n_ids(s) == 0);
  set_destroy(s);
}

/* Id no existente */
void test3_set_delete_id() {
  Set *s = set_creat();
  set_add(s, 100);
  PRINT_TEST_RESULT(set_delete_id(s, 999) == ERROR);
  set_destroy(s);
}

void test4_set_delete_id() {
  PRINT_TEST_RESULT(set_delete_id(NULL, 100) == ERROR);
}

/* ========== set_contains_id ========== */
void test1_set_contains_id() {
  Set *s = set_creat();
  set_add(s, 100);
  PRINT_TEST_RESULT(set_contains_id(s, 100) == TRUE);
  set_destroy(s);
}

void test2_set_contains_id() {
  Set *s = set_creat();
  set_add(s, 100);
  PRINT_TEST_RESULT(set_contains_id(s, 999) == FALSE);
  set_destroy(s);
}

void test3_set_contains_id() {
  PRINT_TEST_RESULT(set_contains_id(NULL, 100) == FALSE);
}

/* ========== set_get_n_ids ========== */
void test1_set_get_n_ids() {
  Set *s = set_creat();
  PRINT_TEST_RESULT(set_get_n_ids(s) == 0);
  set_destroy(s);
}

void test2_set_get_n_ids() {
  Set *s = set_creat();
  set_add(s, 10);
  set_add(s, 20);
  set_add(s, 30);
  PRINT_TEST_RESULT(set_get_n_ids(s) == 3);
  set_destroy(s);
}

void test3_set_get_n_ids() {
  PRINT_TEST_RESULT(set_get_n_ids(NULL) == -1);
}

/* ========== set_print ========== */
void test1_set_print() {
  Set *s = set_creat();
  set_add(s, 42);
  PRINT_TEST_RESULT(set_print(stdout, s) == OK);
  set_destroy(s);
}

void test2_set_print() {
  PRINT_TEST_RESULT(set_print(stdout, NULL) == ERROR);
}
