#include <stdlib.h>
#include "graphic_engine.h"
#include "raylib.h"

/* ------------------------------------------------------------------ */
/*  Tipos privados                                                      */
/* ------------------------------------------------------------------ */

typedef struct {
  int width;
  int height;
} Collider;            

typedef struct _Entity_graphic {
  Vector2  position;
  Collider collider;              
  char    *img;
} Entity_ge;

struct _Graphic_engine {
  Entity_ge  player;
  Entity_ge *obj;
  Entity_ge *spc;
  Entity_ge *numens;
};

/* ------------------------------------------------------------------ */
/*  Funciones privadas                                                  */
/* ------------------------------------------------------------------ */

static Entity_ge *entity_ge_create(void) {
  Entity_ge *e = (Entity_ge *) malloc(sizeof(Entity_ge)); 
  if (!e) return NULL;

  e->img          = NULL;
  e->position.x   = -1.0f;        /* posición inválida inicial */
  e->position.y   = -1.0f;
  e->collider.width  = 0;
  e->collider.height = 0;
  return e;
}

static void entity_ge_destroy(Entity_ge *entity) {
  if (!entity) return;
  if (entity->img) free(entity->img);
  free(entity);
}

/* ------------------------------------------------------------------ */
/*  API pública                                                         */
/* ------------------------------------------------------------------ */

Graphic_engine *graphic_engine_create(void) {
  Graphic_engine *gp = (Graphic_engine *) malloc(sizeof(Graphic_engine)); /* ← sizeof(struct), NO sizeof(puntero) */
  if (!gp) return NULL;


  gp->player.img          = NULL;
  gp->player.position.x   = -1.0f;
  gp->player.position.y   = -1.0f;
  gp->player.collider.width  = 0;
  gp->player.collider.height = 0;


  gp->spc = entity_ge_create();
  if (!gp->spc) {
    free(gp);
    return NULL;
  }

  gp->obj = entity_ge_create();
  if (!gp->obj) {
    entity_ge_destroy(gp->spc); 
    free(gp);
    return NULL;
  }

  gp->numens = entity_ge_create();
  if (!gp->numens) {
    entity_ge_destroy(gp->obj);
    entity_ge_destroy(gp->spc);
    free(gp);
    return NULL;
  }

  return gp; 
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;
  entity_ge_destroy(ge->numens);
  entity_ge_destroy(ge->obj);
  entity_ge_destroy(ge->spc);
  if (ge->player.img) free(ge->player.img);
  free(ge);
}


void graphic_engine_menu_init(Graphic_engine *ge, Game *game) {
  Bool menu_active = TRUE;

  int w_boton     = 250;
  int h_boton     = 50;
  int intra_space = 10;

  if (!ge || !game) return;

  /* La ventana ya está abierta desde game_loop */
  while (!WindowShouldClose() && menu_active) {
    BeginDrawing();
      ClearBackground(RAYWHITE);

      /* Fondo del área de trabajo */
      DrawRectangle(MARGIN_WIDHT, MARGIN_HIGHT,
                    WIDHT_SCREEN - MARGIN_WIDHT,
                    HIGHT_SCREEN - MARGIN_HIGHT, SKYBLUE);

      /* Botón New Game */
      DrawRectangle(MARGIN_WIDHT + intra_space,
                    MARGIN_HIGHT + intra_space,
                    w_boton, h_boton, LIGHTGRAY);
      DrawText("New Game",
               MARGIN_WIDHT + intra_space + 10,
               MARGIN_HIGHT + intra_space + 15, 20, BLACK);

      /* Botón Load Game */
      DrawRectangle(MARGIN_WIDHT + intra_space,
                    MARGIN_HIGHT + intra_space * 2 + h_boton,
                    w_boton, h_boton, LIGHTGRAY);
      DrawText("Load Game",
               MARGIN_WIDHT + intra_space + 10,
               MARGIN_HIGHT + intra_space * 2 + h_boton + 15, 20, BLACK);

      /* Botón Exit */
      DrawRectangle(MARGIN_WIDHT + intra_space,
                    MARGIN_HIGHT + intra_space * 3 + h_boton * 2,
                    w_boton, h_boton, RED);
      DrawText("Exit",
               MARGIN_WIDHT + intra_space + 10,
               MARGIN_HIGHT + intra_space * 3 + h_boton * 2 + 15, 20, WHITE);

    EndDrawing();

    /* Detección de clicks — por ahora, cualquier click inicia el juego */
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      menu_active = FALSE;
    }
  }
  /* Al salir del while, el control regresa a game_loop que seguirá con su bucle */
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  if (!ge || !game) return;

  BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Atlantic Quest", 20, 20, 30, GOLD);
    /* Aquí irá el render completo del juego en siguientes iteraciones */
  EndDrawing();
}