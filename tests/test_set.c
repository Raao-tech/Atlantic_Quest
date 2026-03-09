#include <stdio.h>
#include <stdlib.h>
#include "set.h"


int main() {
    Set *pset = NULL;
    Id id_out;
    Status st;

    printf("--- Starting Set Module Tests ---\n\n");

    /* 1. Test Creation */
    printf("Test 1: Create Set... ");
    pset = set_creat();
    if (pset != NULL) printf(VERDE "PASS" RESET "\n");
    else { printf(ROJO "FAIL" RESET "\n"); return 1; }

    /* 2. Test Is Empty */
    printf("Test 2: Is Empty (New Set)... ");
    if (set_is_empty(pset) == TRUE) printf(VERDE "PASS" RESET "\n");
    else printf(ROJO "FAIL" RESET "\n");

    /* 3. Test Add elements */
    printf("Test 3: Adding IDs (10, 20, 30)... ");
    st = set_add(pset, 10);
    st = set_add(pset, 20);
    st = set_add(pset, 30);
    if (st == OK) printf(VERDE "PASS" RESET "\n");
    else printf(ROJO "FAIL" RESET "\n");

    /* 4. Printing Set */
    printf("\n--- Current Set Status ---\n");
    set_print(stdout, pset);
    printf("--------------------------\n\n");

    /* 5. Test Pop (LIFO behavior) */
    printf("Test 4: Popping last ID (Expected 30)... ");
    id_out = set_pop(pset);
    if (id_out == 30) printf(VERDE "PASS (%ld)" RESET "\n", id_out);
    else printf(ROJO "FAIL (Got %ld)" RESET "\n", id_out);

    /* 6. Test sequence of pops until empty */
    printf("Test 5: Popping remaining elements... ");
    set_pop(pset); // Pops 20
    id_out = set_pop(pset); // Pops 10
    if (id_out == 10 && set_is_empty(pset) == TRUE) printf(VERDE "PASS" RESET "\n");
    else printf(ROJO "FAIL" RESET "\n");

    /* 7. Test Underflow */
    printf("Test 6: Popping from empty set... ");
    id_out = set_pop(pset);
    if (id_out == NO_ID) printf(VERDE "PASS (Returned NO_ID)" RESET "\n");
    else printf(ROJO "FAIL" RESET "\n");

    /* 8. Final Destruction */
    printf("Test 7: Destroying Set... ");
    if (set_destroy(pset) == OK) printf(VERDE "PASS" RESET "\n");
    else printf(ROJO "FAIL" RESET "\n");

    printf("\n--- All Tests Completed ---\n");

    return 0;
}
