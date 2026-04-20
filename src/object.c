/**
 * @brief It implements the object struct
 *
 * @file object.c
 * @author Violeta, Rafael, Javier Jarque and Salvador Alcalá
 * @version 3
 * @date 18-04-2026
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Object
 *
 * This struct stores all the information of an object.
 */
struct _Object {
  Entity  *e_obj;
  Bool movable;                       /*!< Whether the object can be taken or not */
  Id open;                            /*!< Id of the link that this object can open (for use command) */
  Id dependency;                      /*!< Id of the object that this object depends on (for use command) */
};

/* ========== Create / Destroy ========== */

Object *obj_create() {
  Object *newObj = NULL;

  newObj = (Object *)calloc(1, sizeof(Object));
  if (newObj == NULL) return NULL;

  newObj->e_obj = entity_create();
  if(!newObj->e_obj){
    free(newObj);
    return NULL;
  }

  newObj->movable = FALSE;
  newObj->open = NO_ID;
  newObj->dependency = NO_ID;
  return newObj;
}

Status obj_destroy(Object *obj) {
  if (obj->e_obj) free(obj->e_obj);
  if (obj) free(obj);
  return OK;
}

/* ========== Id ========== */

Status obj_set_id(Object *obj, Id id) {
  if (!obj) return ERROR;
  return entity_set_id(obj->e_obj);
}

Id obj_get_id(Object *obj) {
  if (!obj) return NO_ID;
  return entity_get_id(obj->e_obj);
}

/* ========== Name ========== */

Status obj_set_name(Object *obj, char *name) {
  if (!obj || !name) return ERROR;
  return entity_set_name(obj->e_obj);
}

Bool obj_has_name(Object *obj, char *name) {
  if (!obj || !name) return FALSE;
  return entity_has_name(obj->e_obj);
}

char *obj_get_name(Object *obj) {
  if (!obj) return NULL;
  return entity_get_name(obj->e_obj);
}

/* ========== Description ========== */

Status obj_set_description(Object *obj, char *description) {
  if (!obj || !description) return ERROR;
  return entity_set_message(obj->e_obj, description);
}

char *obj_get_description(Object *obj) {
  if (!obj) return NULL;
  return entity_get_message(obj->e_obj);
}
/* ========== Health ========== */
Status obj_set_health(Object *obj, int health) {
  if (!obj) return ERROR;
  obj->health = health;
  return OK;
}

int obj_get_health(Object *obj) {
  if (!obj) return 0;
  return obj->health;
}
/* ========== Movable ========== */

Status obj_set_movable(Object *obj, Bool movable) {
  if (!obj) return ERROR;
  obj->movable = movable;
  return OK;
}

Bool obj_get_movable(Object *obj) {
  if (!obj) return FALSE;
  return obj->movable;
}

/* ========== Open ========== */
Status obj_set_open(Object *obj, Id open) {
  if (!obj) return ERROR;
  obj->open = open;
  return OK;
}

Id obj_get_open(Object *obj) {
  if (!obj) return NO_ID;
  return obj->open;
}

/* ========== Dependency ========== */

Status obj_set_dependency(Object *obj, Id dependency) {
  if (!obj) return ERROR;
  obj->dependency = dependency;
  return OK;
}

Id obj_get_dependency(Object *obj) {
  if (!obj) return NO_ID;
  return obj->dependency;
}

/* ========== Print ========== */

Status obj_print(Object *obj) {
  if (!obj) return ERROR;

  fprintf(stdout, "--> Object (Id: %ld; Name: %s; Desc: %s; Health: %d; Movable: %s; Open: %ld; Dependency: %ld)\n",
          obj->id, obj->name, obj->description, obj->health, obj->movable ? "Yes" : "No", obj->open , obj->dependency );

  return OK;
}