/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG and Javier Jarque
 * @version 2
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include "command.h"
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>



Status command_raylib_get_input(void)
{
    if(IsKeyPressed(D))
    return OK;
}