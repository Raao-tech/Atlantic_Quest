/**
 * @brief Unit Testing for the Set Module (I2)
 * @file test_set.c
 * @date 14.3.2026 (Happy Math's day!!)
 * @author Rafael y Violeta
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"


void print_test(char *msg, int result) {
    printf("Test: %-50s [%s]\n", msg, result ? VERDE"PASS"RESET : ROJO"FAIL"RESET);
}

int main() {
    Set *s = NULL;
    Status st;

    printf("--- STARTING SET MODULE TESTS (I2) ---\n\n");

    /* ========== 1. set_creat ========== */
    s = set_creat();
    print_test("1A: set_creat (pointer not NULL)", s != NULL);
    print_test("1B: set_creat (n_ids == 0)", set_get_n_ids(s) == 0);

    /* ========== 2. set_add ========== */
    st = set_add(s, 100);
    print_test("2A: set_add (valid ID returns OK)", st == OK);
    print_test("2B: set_add (n_ids == 1 after add)", set_get_n_ids(s) == 1);
    st = set_add(NULL, 200);
    print_test("2C: set_add (NULL set returns ERROR)", st == ERROR);
    st = set_add(s, NO_ID);
    print_test("2D: set_add (NO_ID returns ERROR)", st == ERROR);
    st = set_add(s, 100);
    print_test("2E: set_add (duplicate returns OK, no change)", st == OK && set_get_n_ids(s) == 1);

    /* ========== 3. set_contains_id ========== */
    print_test("3A: set_contains_id (existing ID)", set_contains_id(s, 100) == TRUE);
    print_test("3B: set_contains_id (non-existing ID)", set_contains_id(s, 999) == FALSE);
    print_test("3C: set_contains_id (NULL set)", set_contains_id(NULL, 100) == FALSE);

    /* ========== 4. set_get_n_ids ========== */
    print_test("4A: set_get_n_ids (1 element)", set_get_n_ids(s) == 1);
    set_add(s, 200);
    set_add(s, 300);
    print_test("4B: set_get_n_ids (3 elements)", set_get_n_ids(s) == 3);
    print_test("4C: set_get_n_ids (NULL set returns -1)", set_get_n_ids(NULL) == -1);

    /* ========== 5. set_delete_id ========== */
    st = set_delete_id(s, 200);
    print_test("5A: set_delete_id (existing ID returns OK)", st == OK);
    print_test("5B: set_delete_id (n_ids decreased)", set_get_n_ids(s) == 2);
    print_test("5C: set_delete_id (ID no longer in set)", set_contains_id(s, 200) == FALSE);
    st = set_delete_id(s, 999);
    print_test("5D: set_delete_id (non-existing returns ERROR)", st == ERROR);
    st = set_delete_id(NULL, 100);
    print_test("5E: set_delete_id (NULL set returns ERROR)", st == ERROR);
    st = set_delete_id(s, NO_ID);
    print_test("5F: set_delete_id (NO_ID returns ERROR)", st == ERROR);

    /* Delete remaining to test single-element case */
    set_delete_id(s, 100);
    st = set_delete_id(s, 300);
    print_test("5G: set_delete_id (last element)", st == OK && set_get_n_ids(s) == 0);

    /* ========== 6. set_destroy ========== */
    print_test("6A: set_destroy (valid pointer)", set_destroy(s) == OK);
    print_test("6B: set_destroy (NULL pointer safety)", set_destroy(NULL) == ERROR);

    /* ========== 7. Stress test ========== */
    printf("\n--- Stress Testing ---\n");
    s = set_creat();
    int i, count = 0;
    for (i = 1; i <= 10; i++) {
        if (set_add(s, (Id)i) == OK) count++;
    }
    print_test("7A: Stress add (10 elements)", count == 10 && set_get_n_ids(s) == 10);

    /* Delete even numbers */
    for (i = 2; i <= 10; i += 2) {
        set_delete_id(s, (Id)i);
    }
    print_test("7B: Stress delete (5 evens removed)", set_get_n_ids(s) == 5);
    print_test("7C: Contains 3 after stress", set_contains_id(s, 3) == TRUE);
    print_test("7D: Does not contain 4 after stress", set_contains_id(s, 4) == FALSE);

    /* Clean up remaining */
    for (i = 1; i <= 10; i += 2) {
        set_delete_id(s, (Id)i);
    }
    print_test("7E: Set empty after full cleanup", set_get_n_ids(s) == 0);

    set_destroy(s);

    /* ========== 8. Visual check ========== */
    printf("\n--- Visual Check (set_print) ---\n");
    s = set_creat();
    set_add(s, 42);
    set_add(s, 77);
    set_add(s, 13);
    set_print(stdout, s);
    set_destroy(s);

    printf("\n--- ALL SET TESTS COMPLETED ---\n");
    printf("Run with: valgrind --leak-check=full ./test_set\n");
    return 0;
}