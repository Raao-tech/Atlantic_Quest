/**
 * @brief It defines the graphic engine interface (Raylib + raygui)
 *
 * @file graphic_engine.h
 * @author Rafael
 * @version 1
 * @date 02-05-2026
 * @copyright GNU Public License
 */
#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"
#include "types.h"

/* Limites del cache interno de texturas. Ajusta si superas el tope. */
#define MAX_SPACE_TEX  16   /* 1 textura por space  */
#define MAX_PLAYER_TEX 4    /* 1 textura por player */
#define MAX_NUMEN_TEX  16   /* 1 textura por numen  */

typedef struct _Graphic_engine Graphic_engine;

/* ----------------------------------------------------------------------
 * Out  (codigo de retorno del menu inicial — sin cambios)
 * ---------------------------------------------------------------------- */
typedef enum
{
    OUT_ERR = -1,
    NEW_GAME,
    LOAD_GAME,
    EXIT_Q
} Out;

typedef struct _MenuResult
{
    Out  menu_out;
    char data_name[WORD_SIZE + 1];
    Id   init_numen;
} MenuResult;

Graphic_engine* graphic_engine_create  (void);
void            graphic_engine_destroy (Graphic_engine* ge);
MenuResult      graphic_engine_init    (Graphic_engine* ge);

/**
 * @brief Carga las texturas del juego una vez tras cargar el .dat
 * @author Rafael
 *
 * Recorre los spaces/players/numens del Game y carga sus PNGs desde:
 *   - space:  ./img_src/background/<space_name>.png  (o el path del gdesc del space si tiene uno)
 *   - player: ./img_src/sprites/players/<name>.png
 *   - numen:  ./img_src/sprites/numens/<name>.png
 *
 * Si una imagen no existe, raylib carga su default (1x1) y nuestro
 * paint_game pinta un fallback de color para que el juego siga
 * funcionando sin crashear.
 *
 * Esta funcion debe llamarse DESPUES de que el game este cargado del .dat
 * y ANTES del primer paint_game.
 */
Status graphic_engine_load_textures (Graphic_engine* ge, Game* game);

void graphic_engine_paint_game     (Graphic_engine* ge, Game* game);
void graphic_engine_handle_ui_input (Graphic_engine* ge, Game* game);

#endif