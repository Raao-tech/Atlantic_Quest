/**
 * @brief It implements the player struct
 *
 * @file player.c
 * @author Violeta, Rafael y Salvador
 * @version 1
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"

typedef struct _Inventory Inventory;

Inventory* inventory_create();

Status inventory_destroy(Inventory* inventory);

Status inventory_add(Inventory* inventory, Id new_id);

Status inventory_delete_obj(Inventory *inventory, Id trash_id);

Bool inventory_contains_object(Inventory* inventory, Id* obj);

Status inventory_set_max_objs(Inventory *inventory, int max);

int inventory_get_max_objs(Inventory* inventory);

int inventory_get_n_ids(Inventory *inventory);

Id	inventory_get_id_at(Inventory *inventory, int position);

Status inventory_print(Inventory *inventory);


#endif