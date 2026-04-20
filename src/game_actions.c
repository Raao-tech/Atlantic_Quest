/**
 * @brief It implements the entity struct
 *
 * @file character.c
 * @author Violeta
 * @version 0
 * @date 04-02-2025
 * @copyright GNU Public License
 */

#include "entity.h"

/**
 * @brief Entity
 *
 * This struct stores all the information of a Entity.
 */
struct _Entity{
  Id    id;                   /*!< Id number of the object, it must be unique */
  char  *gdesc;               /*!< General description of the entity */
  char  *message;             /*!< Message associated with the entity */
  char  *name;                /*!< Name of the entity */
  Stats stats;                /*!< Stats of entity*/
  Position position;          /*!< Stats of entity*/
};
struct _Stats{
  int health;   /*!< Salud: puede ser positiva o negativa */
  int attack;   /*!< Poder de ataque */
  int energy;   /*!< Puntos de energía o maná */
  int speed;   /*!< Puntos de velocidad */
};
struct _Position{
  int pos_x;   /*!< Posicion x en el space*/
  int pos_y;   /*!< Posicion y en el space*/
};


/* create or destroy */
Entity *entity_create(){
  Entity *newEntity = NULL;

  newEntity = (Entity *)malloc(sizeof(Entity));
  if (!newEntity) return NULL;

  /* Initialization of an empty character*/
  newEntity->id =       NO_ID;
  newEntity->gdesc =    NULL;
  newEntity->name =     NULL;
  newEntity->message =  NULL;
  newEntity->position.pos_x = 0;
  newEntity->position.pos_y = 0;
  newEntity->stats.attack= MIN_ENGY;
  newEntity->stats.speed = 0;
  newEntity->stats.health= MIN_LIFE;
  newEntity->stats.energy= MIN_ENGY;
  return newEntity;
}
Status entity_destroy(Entity *entity){
  if (!entity) return ERROR;

  free(entity->gdesc);
  free(entity->name);
  free(entity->message);
  free(entity);

  return OK;
}


/* id */
Status  entity_set_id(Entity *entity, Id new_id){
  if(!entity) return ERROR;

  entity->id = new_id;
  return OK;
}
Id  entity_get_id(Entity *entity){
  if(!entity) return ERROR;

  return entity->id;
}


/* name */
Status  entity_set_name(Entity *entity, char*  name){
  int   length_name;

  if(!entity || !name) return  ERROR;

  /* Calculamos el tamaño del name sin el \0  */
  length_name = strlen(name);

  /*  Si existe name, liberalo*/
  if(entity->name){
    free  (entity->name);
    entity->name = NULL;
  }

  /* Reservamos memoria (4 + 1 = 5 bytes para "Hola\0") */
  entity->name = (char *) calloc(length_name + 1, sizeof(char));

  /* VALIDAR la reserva de memoria antes de copiar */
  if (entity->name == NULL) return ERROR;

  /* Copiamos (strcpy copia los caracteres y el \0 automáticamente) */
  strcpy(entity->name, name);

  return OK;
}
char*  entity_get_name(Entity *entity){
  if(!entity || !entity->name) return NULL;
  return  strdup(entity->name);
}


Bool entity_has_name(Entity *entity, char *name){
    char *entity_name = NULL;
    Bool result = FALSE;
    if(!entity|| !name) return FALSE;
    entity_name = entity_get_name(entity);
    if(!entity_name) return FALSE;
    result = (strcmp(entity_name, name) == 0) ? TRUE : FALSE;
    free(entity_name);
    return result;
}
/* gdesc */
Status  entity_set_gdesc(Entity *entity, char*  desc){
  int   length_desc;
  if(!entity || !desc) return  ERROR;


  /* Calculamos el tamaño del desc sin el \0  */
  length_desc = strlen(desc);

  /*  Si existe gdesc, liberalo.  Limpiamos nuestro anterior array*/
  if(entity->gdesc){
    free  (entity->gdesc);
    entity->gdesc = NULL;
  }

  /* Reservamos memoria (4 + 1 = 5 bytes para "Hola\0") */
  entity->gdesc = (char *) calloc(length_desc + 1, sizeof(char));

  /* VALIDAR la reserva de memoria antes de copiar */
  if (entity->gdesc == NULL) return ERROR; 

  /* Copiamos (strcpy copia los caracteres y el \0 automáticamente) */
  strcpy(entity->gdesc, desc);

  return OK;
}
char*  entity_get_gdesc(Entity *entity){
  if(!entity || !entity->gdesc){
    return NULL;
  }

  return  strdup(entity->gdesc);
}


/* message */
Status  entity_set_message(Entity *entity, char*  message){
  int   length_message;

  if(!entity || !message){
    return  ERROR;
  }

  /* Calculamos el tamaño del message sin el \0  */
  length_message = strlen(message);

  /*  Si existe message, liberalo*/
  if(entity->message){
    free  (entity->message);
    entity->message = NULL;
  }

  /* Reservamos memoria (4 + 1 = 5 bytes para "Hola\0") */
  entity->message = (char *) calloc(length_message + 1, sizeof(char));

  /* VALIDAR la reserva de memoria antes de copiar */
  if (entity->message == NULL) {
    return ERROR;
  }

  /* Copiamos (strcpy copia los caracteres y el \0 automáticamente) */
  strcpy(entity->message, message);

  return OK;
}
char*  entity_get_message(Entity *entity){
  if(!entity || !entity->message){
    return NULL;
  }

  return  strdup(entity->message);
}


/*=======Stats ========*/
/*healt*/
Status  entity_set_health(Entity *entity, int health){
  if(!entity) return ERROR;
  entity->stats.health = (health < MIN_LIFE) ? MIN_LIFE : health;
  return OK;
}
int  entity_get_health(Entity *entity){
  if(!entity) return ERROR_LIFE;
  return entity->stats.health;
}

/*speed*/
Status  entity_set_speed(Entity *entity, int speed){
  if(!entity) return ERROR;
  entity->stats.speed = speed;
  return OK;
}
int  entity_get_speed(Entity *entity){
  if(!entity) return 0;
  return entity->stats.speed;
}

/*energy*/
Status  entity_set_energy(Entity *entity, int energy){
  if(!entity) return ERROR;
  entity->stats.energy = (energy < MIN_ENGY)   ? MIN_ENGY : energy;
  return OK;
}
int  entity_get_energy(Entity *entity){
  if(!entity) return ERROR_ENGY;
  return entity->stats.energy;
}

/*attack*/
Status  entity_set_attack(Entity *entity, int attack){
  if(!entity) return ERROR;
  entity->stats.energy = (attack < MIN_ATTACK) ? MIN_ATTACK : attack;
  return OK;
}
int  entity_get_attack(Entity *entity){
  if(!entity) return ERROR_ATTACK;
  return entity->stats.attack;
}

/*Stats_general*/
Status  entity_set_stats(Entity *entity, int energy, int health, int speed, int attack){
  if(!entity) return ERROR;
  entity->stats.energy = (energy < MIN_ENGY)   ? MIN_ENGY : energy;
  entity->stats.health = (health < MIN_LIFE)   ? MIN_LIFE : health;
  entity->stats.attack = (attack < MIN_ATTACK) ? MIN_ATTACK : attack;
  entity->stats.speed = speed;
  return OK;
}

/*==== Position ===*/
/*pos_x*/
Status  entity_set_(Entity *entity, int x, int y){
  if(!entity) return ERROR;
  entity->position.pos_x = x;
  entity->position.pos_y = y;
  return OK;
}
int  entity_get_energy(Entity *entity){
  if(!entity) return ERROR_ENGY;
  return entity->stats.energy;
}


/*pos*/
Status  entity_set_Position(Entity *entity, int x, int y){
  if(!entity) return ERROR;
  entity->position.pos_x = x;
  entity->position.pos_y = y;
  return OK;

 
/* ========================================================================= */
/*                      SAVE: save                                           */
/* ========================================================================= */
static void game_actions_save(Game *game)
{
  if(!game)
  {
    game_set_last_cmd_status(game, ERROR_save);
    return;
  }

  if(game_save_file(game)==OK)
  game_set_last_cmd_status(game, OK);
  else{
    game_set_last_cmd_status(game, ERROR_save);
  }
  return;
}


/* ========================================================================= */
/*                      HELPER: PARSE DIRECTION                              */
/* ========================================================================= */

static Direction ge_parse_direction(const char *str)
{
  if (!str)
    return U;

  if (strcasecmp(str, "north") == 0 || strcasecmp(str, "n") == 0)
    return N;
  if (strcasecmp(str, "south") == 0 || strcasecmp(str, "s") == 0)
    return S;
  if (strcasecmp(str, "east") == 0 || strcasecmp(str, "e") == 0)
    return E;
  if (strcasecmp(str, "west") == 0 || strcasecmp(str, "w") == 0)
    return W;

  return U;
}