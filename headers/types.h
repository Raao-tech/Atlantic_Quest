/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */


#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Consts to numbers */
#define WORD_SIZE 1000
#define NO_ID -1

/* Colors to prints */
#define ROJO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define RESET   "\x1b[0m"

typedef long Id;

typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef enum
{
    ERROR,
    OK
} Status;

typedef enum
{
    N,
    S,
    E,
    W
} Direction;

#endif
