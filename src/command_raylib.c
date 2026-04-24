/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Rafael
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


/**
 * Command_raylib_get_input()
 * 
 * La funcion se encarga de escuchar los comandos pasados por teclado cada 60  frame por segundo.
 */
Status command_raylib_get_input(void)
{
    Bool key_pressed = GetKeyPressed();
    switch (key_pressed)
    {
    case KEY_UP expression:
        /* code */
        break;
    
    default:
        break;
    }
    {
        /* code */
    }
    
    
    return OK;
}