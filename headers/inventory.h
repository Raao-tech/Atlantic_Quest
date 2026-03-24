#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"

typedef struct _Inventory Inventory;

Inventory* inventroy_create();

Status inventory_destroy(Inventory* inventory);

Status inventory_add(Inventory* inventory, Id new_id);

Status inventory_contains_object(Inventory* inventory, Id* obj);

Status inventory_delete_object(Inventory* inventory, Id* obj);

Status inventory_set_max_objs(Inventory *inventory, int max);

int inventory_get_max_objs(Inventory* inventory);

Status inventory_print(Inventory *inventory);


#endif