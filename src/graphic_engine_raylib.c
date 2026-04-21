/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine_raylib.h
 * @author Rafael
 * @version 3
 * @date 08-04-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"
#include "raylib.h"


/*<! Definimos La estrcutra de las colisiones de una entidad. A este se le suam a la psotion*/
struct Collider
{
  int     widht;
  int     height;
};
/*<! Definimos el tipo de dato Entity_grafico que contine toda la info relacionada con los graficos*/
typedef struct _Entity_graphic
{
  Vector2 position;         /*<! Determina la posicion inical del persoanje*/
  struct  Collider;
  char*   img;              /**/

}Entity_ge;

struct _Graphic_engine
{
    Entity_ge  player;
    Entity_ge  *obj;
    Entity_ge  *spc;
    Entity_ge  *numens;
};


/*===================== Private Funtion ==============================*/
Entity_ge* entity_ge_create();
void entity_ge_destroy(Entity_ge* entity);






/*==================================================================== */
Graphic_engine *graphic_engine_create(){
    Graphic_engine* gp =(Graphic_engine*)malloc(sizeof(gp));
    if(!gp) return NULL;

    gp->player.position.x = ERROR_POSITION;
    gp->player.position.y = ERROR_POSITION;
    gp->spc = entity_ge_create();
    if(!gp->spc){
        return NULL;
    }
    gp->obj = entity_ge_create();
    if(!gp->obj){
        free(gp->spc);
        return NULL;
    }
    gp->numens = entity_ge_create();
    if(!gp->numens){
        free(gp->obj);
        free(gp->spc);
        return NULL;
    }

}

void graphic_engine_destroy(Graphic_engine *ge);

void graphic_engine_paint_game(Graphic_engine *ge, Game *game);


/*=========== IMPLEMENTATION FUNTION =====================*/

Entity_ge* entity_ge_create(){
    Entity_ge* e = (Entity_ge*)malloc(sizeof(Entity_ge));
    if(!e) return NULL;

    e->img = NULL;
    e->position.x = ERROR_POSITION;
    e->position.y = ERROR_POSITION;
    
    return e;
}

void entity_ge_destroy(Entity_ge* entity){free()}
