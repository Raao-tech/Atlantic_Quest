/**
 * @brief It tests the player module
 *
 * @file player_test.c
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 50

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_player_create();
  if (all || test == 2)  test2_player_create();
  if (all || test == 3)  test1_player_destroy();
  if (all || test == 4)  test2_player_destroy();
  if (all || test == 5)  test1_player_set_id();
  if (all || test == 6)  test2_player_set_id();
  if (all || test == 7)  test1_player_get_id();
  if (all || test == 8)  test2_player_get_id();
  if (all || test == 9)  test1_player_set_name();
  if (all || test == 10) test2_player_set_name();
  if (all || test == 11) test3_player_set_name();
  if (all || test == 12) test1_player_get_name();
  if (all || test == 13) test2_player_get_name();
  if (all || test == 14) test1_player_has_name();
  if (all || test == 15) test2_player_has_name();
  if (all || test == 16) test3_player_has_name();
  if (all || test == 17) test1_player_set_health();
  if (all || test == 18) test2_player_set_health();
  if (all || test == 19) test1_player_get_health();
  if (all || test == 20) test2_player_get_health();
  if (all || test == 21) test1_player_set_max_objects();
  if (all || test == 22) test2_player_set_max_objects();
  if (all || test == 23) test3_player_set_max_objects();
  if (all || test == 24) test1_player_set_attack();
  if (all || test == 25) test2_player_set_attack();
  if (all || test == 26) test1_player_get_attack();
  if (all || test == 27) test2_player_get_attack();
  if (all || test == 28) test1_player_add_object();
  if (all || test == 29) test2_player_add_object();
  if (all || test == 30) test1_player_add_object_full_inventory();
  if (all || test == 31) test1_player_contains_object();
  if (all || test == 32) test2_player_contains_object();
  if (all || test == 33) test3_player_contains_object();
  if (all || test == 34) test1_player_delete_object();
  if (all || test == 35) test2_player_delete_object();
  if (all || test == 36) test1_player_get_n_objects();
  if (all || test == 37) test2_player_get_n_objects();
  if (all || test == 38) test1_player_empty_inventory();
  if (all || test == 39) test1_player_set_location();
  if (all || test == 40) test2_player_set_location();
  if (all || test == 41) test3_player_set_location();
  if (all || test == 42) test1_player_get_location();
  if (all || test == 43) test2_player_get_location();
  if (all || test == 44) test1_player_set_gdesc();
  if (all || test == 45) test2_player_set_gdesc();
  if (all || test == 46) test1_player_get_gdesc();
  if (all || test == 47) test2_player_get_gdesc();
  if (all || test == 48) test1_player_set_message();
  if (all || test == 49) test2_player_set_message();
  if (all || test == 50) test1_player_get_message();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* ========== player_create ========== */
void test1_player_create() {
  Player *p = player_create();
  PRINT_TEST_RESULT(p != NULL);
  player_destroy(p);
}

void test2_player_create() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
  player_destroy(p);
}

/* ========== player_destroy ========== */
void test1_player_destroy() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_destroy(p) == OK);
}

void test2_player_destroy() {
  PRINT_TEST_RESULT(player_destroy(NULL) == ERROR);
}

/* ========== player_set_id / get_id ========== */
void test1_player_set_id() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_id(p, 1) == OK);
  player_destroy(p);
}

void test2_player_set_id() {
  PRINT_TEST_RESULT(player_set_id(NULL, 1) == ERROR);
}

void test1_player_get_id() {
  Player *p = player_create();
  player_set_id(p, 1);
  PRINT_TEST_RESULT(player_get_id(p) == 1);
  player_destroy(p);
}

void test2_player_get_id() {
  PRINT_TEST_RESULT(player_get_id(NULL) == NO_ID);
}

/* ========== player_set_name / get_name ========== */
void test1_player_set_name() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_name(p, "Hero") == OK);
  player_destroy(p);
}

void test2_player_set_name() {
  PRINT_TEST_RESULT(player_set_name(NULL, "Hero") == ERROR);
}

void test3_player_set_name() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
  player_destroy(p);
}

void test1_player_get_name() {
  Player *p = player_create();
  char *name;
  player_set_name(p, "Hero");
  name = player_get_name(p);
  PRINT_TEST_RESULT(name != NULL && strcmp(name, "Hero") == 0);
  free(name);
  player_destroy(p);
}

void test2_player_get_name() {
  PRINT_TEST_RESULT(player_get_name(NULL) == NULL);
}

/* ========== player_has_name ========== */
void test1_player_has_name() {
  Player *p = player_create();
  player_set_name(p, "Hero");
  PRINT_TEST_RESULT(player_has_name(p, "Hero") == TRUE);
  player_destroy(p);
}

void test2_player_has_name() {
  Player *p = player_create();
  player_set_name(p, "Hero");
  PRINT_TEST_RESULT(player_has_name(p, "Villain") == FALSE);
  player_destroy(p);
}

void test3_player_has_name() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_has_name(p, NULL) == FALSE && player_has_name(NULL, "Hero") == FALSE);
  player_destroy(p);
}

/* ========== player_set_health / get_health ========== */
void test1_player_set_health() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_health(p, 5) == OK);
  player_destroy(p);
}

void test2_player_set_health() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_health(p, MAX_LIFE + 1) == ERROR);
  player_destroy(p);
}

void test1_player_get_health() {
  Player *p = player_create();
  player_set_health(p, 7);
  PRINT_TEST_RESULT(player_get_health(p) == 7);
  player_destroy(p);
}

void test2_player_get_health() {
  PRINT_TEST_RESULT(player_get_health(NULL) == ERROR_LIFE);
}

/* ========== player_set_max_objects ========== */
void test1_player_set_max_objects() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_max_objects(p, 1) == OK);
  player_destroy(p);
}

void test2_player_set_max_objects() {
  PRINT_TEST_RESULT(player_set_max_objects(NULL, 1) == ERROR);
}

void test3_player_set_max_objects() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_max_objects(p, -1) == ERROR);
  player_destroy(p);
}

/* ========== player_set_attack / get_attack ========== */
void test1_player_set_attack() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_attack(p, 3) == OK);
  player_destroy(p);
}

void test2_player_set_attack() {
  PRINT_TEST_RESULT(player_set_attack(NULL, 3) == ERROR);
}

void test1_player_get_attack() {
  Player *p = player_create();
  player_set_attack(p, 3);
  PRINT_TEST_RESULT(player_get_attack(p) == 3);
  player_destroy(p);
}

void test2_player_get_attack() {
  PRINT_TEST_RESULT(player_get_attack(NULL) == ERROR_ATTACK);
}

/* ========== player_add_object / contains / delete / get_n ========== */
void test1_player_add_object() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_add_object(p, 21) == OK);
  player_destroy(p);
}

void test2_player_add_object() {
  PRINT_TEST_RESULT(player_add_object(NULL, 21) == ERROR);
}

void test1_player_add_object_full_inventory() {
  Player *p = player_create();
  player_set_max_objects(p, 1);
  player_add_object(p, 21);
  PRINT_TEST_RESULT(player_add_object(p, 22) == ERROR);
  player_destroy(p);
}

void test1_player_contains_object() {
  Player *p = player_create();
  player_add_object(p, 21);
  PRINT_TEST_RESULT(player_contains_object(p, 21) == TRUE);
  player_destroy(p);
}

void test2_player_contains_object() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_contains_object(p, 999) == FALSE);
  player_destroy(p);
}

void test3_player_contains_object() {
  PRINT_TEST_RESULT(player_contains_object(NULL, 21) == FALSE);
}

void test1_player_delete_object() {
  Player *p = player_create();
  player_add_object(p, 21);
  PRINT_TEST_RESULT(player_delete_object(p, 21) == OK && player_contains_object(p, 21) == FALSE);
  player_destroy(p);
}

void test2_player_delete_object() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_delete_object(p, 999) == ERROR);
  player_destroy(p);
}

void test1_player_get_n_objects() {
  Player *p = player_create();
  player_add_object(p, 21);
  player_add_object(p, 22);
  PRINT_TEST_RESULT(player_get_n_objects(p) == 2);
  player_destroy(p);
}

void test2_player_get_n_objects() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_get_n_objects(p) == 0);
  player_destroy(p);
}

void test1_player_empty_inventory() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_get_n_objects(p) == 0 && player_contains_object(p, 21) == FALSE && player_delete_object(p, 21) == ERROR);
  player_destroy(p);
}

/* ========== player_set_location / get_location ========== */
void test1_player_set_location() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_location(p, 11) == OK);
  player_destroy(p);
}

void test2_player_set_location() {
  PRINT_TEST_RESULT(player_set_location(NULL, 11) == ERROR);
}

void test3_player_set_location() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_location(p, NO_ID) == ERROR);
  player_destroy(p);
}

void test1_player_get_location() {
  Player *p = player_create();
  player_set_location(p, 11);
  PRINT_TEST_RESULT(player_get_location(p) == 11);
  player_destroy(p);
}

void test2_player_get_location() {
  PRINT_TEST_RESULT(player_get_location(NULL) == NO_ID);
}

/* ========== player_set_gdesc / get_gdesc ========== */
void test1_player_set_gdesc() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_gdesc(p, ">8D") == OK);
  player_destroy(p);
}

void test2_player_set_gdesc() {
  PRINT_TEST_RESULT(player_set_gdesc(NULL, ">8D") == ERROR);
}

void test1_player_get_gdesc() {
  Player *p = player_create();
  char *gdesc;
  player_set_gdesc(p, ">8D");
  gdesc = player_get_gdesc(p);
  PRINT_TEST_RESULT(gdesc != NULL && strcmp(gdesc, ">8D") == 0);
  free(gdesc);
  player_destroy(p);
}

void test2_player_get_gdesc() {
  PRINT_TEST_RESULT(player_get_gdesc(NULL) == NULL);
}

/* ========== player_set_message / get_message ========== */
void test1_player_set_message() {
  Player *p = player_create();
  PRINT_TEST_RESULT(player_set_message(p, "Ready for adventure!") == OK);
  player_destroy(p);
}

void test2_player_set_message() {
  PRINT_TEST_RESULT(player_set_message(NULL, "Hello") == ERROR);
}

void test1_player_get_message() {
  Player *p = player_create();
  char *msg;
  player_set_message(p, "Ready for adventure!");
  msg = player_get_message(p);
  PRINT_TEST_RESULT(msg != NULL && strcmp(msg, "Ready for adventure!") == 0);
  free(msg);
  player_destroy(p);
}

void test2_player_get_message() {
  PRINT_TEST_RESULT(player_get_message(NULL) == NULL);
}
