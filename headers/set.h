/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @author Rafael
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */
#ifndef SET_H
#define SET_H

#include "types.h"

typedef struct _Set Set;

Set*    set_creat();
Status  set_destroy(Set *pset);
Bool    set_contains_id(Set *pset, Id ref_id);
Status  set_add(Set *pset, Id new_id);
Status  set_delete_id(Set *pset, Id trash_id);
int     set_get_n_ids(Set *pset);

/**
 * @brief Returns the ID at a given position in the set (for iteration from outside)
 * @author Rafael
 *
 * @param pset Pointer to the set
 * @param position Index in the internal array (0 to n_ids-1)
 * @return The Id at that position, or NO_ID if out of range or pset is NULL
 */
Id      set_get_id_at(Set *pset, int position);

Status  set_print(FILE *output, Set *pset);

#endif
