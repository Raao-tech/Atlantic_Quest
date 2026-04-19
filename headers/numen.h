/**
 * @brief It defines the numen module interface
 *
 * @file Numens.h
 * @author Rafa
 * @version 0
 * @date 18-04-2026
 * @copyright GNU Public License
 */

#ifndef NUMEN_H
#define NUMEN_H

#include "headers/character.h"
#include "headers/types.h"

typedef struct _Numen Numen;

/*======== (Creat/Destroy) Numen ================*/

Numen* numen_creat();
Status numen_destroy(Numen* numen);

/*======== (set/get) name (char*)================*/
Status numen_set_name(Numen* numen, char* name);
char*  numen_get_name(Numen* numen);
/*======== (set/get) is_errante (Bool)================*/
Status numen_set_is_errant(Numen* numen, Bool errant);
Bool  numen_get_is_errant(Numen* numen);
/*======== (set/get) space ================*/
/*======== (set/get) corrupt(friendly or not friendly) ================*/
Status numen_set_is_errant(Numen* numen, Bool errant);
Bool  numen_get_is_errant(Numen* numen);
/*======== (set/get) position ================*/
/*======== (set/get) collider ================*/
/*======== (set/get) gdesc() ================*/

#endif