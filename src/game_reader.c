/**
 * @brief It reads information from files to create the game
 *
 * @file game_reader.c
 * @author Violeta y Rafael
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  F_PLAY "#p:"
#define  F_SPAC "#s:"
#define  F_OBJE "#o:"
#define  F_CHAR "#c:"


/* ========== Private: Load spaces from file ========== */
/* Format: #s:id|name|gdesc0|gdesc1|gdesc2|gdesc3|gdesc4| */

/*A quien le toque, pero hay que quitar los vecinos de space, los spaces no conocen sus vecinos*/
Status game_load_spaces(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  Status status = OK;
  int tam_format;
  int i;

  if (!game || !filename) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  tam_format = strlen(F_SPAC);
  while (fgets(line, WORD_SIZE, file)){
    if (strncmp(F_SPAC, line, tam_format) == 0){
      toks = strtok(line + tam_format, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      
#ifdef DEBUG
      printf("Leido space: s:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif

      space = space_create();
      if (space != NULL){
        space_set_id(space, id);
        space_set_name(space, name);

        /* Try to read gdesc lines (optional, may not be present) */
        for (i = 0; i < MAX_LINE; i++){
          toks = strtok(NULL, "|");
          if (toks && toks[0] != '\n' && toks[0] != '\0'){
            space_set_gdesc_line(space, i, toks);
          }
        }

        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* ========== Private: Load objects from file ========== */
/* Format: #o:id|name|space_id */
Status game_load_objects(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, space_id = NO_ID;
  Object *obj = NULL;
  Space *space = NULL;
  Status status = OK;
  int     tam_format;

  if (!game || !filename) return ERROR;

  tam_format = strlen(F_OBJE);
  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)){
    if (strncmp(F_OBJE, line, tam_format) == 0){
      toks = strtok(line + tam_format, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|\n");
      space_id = atol(toks);

#ifdef DEBUG
      printf("Leido object: o:%ld|%s|%ld\n", id, name, space_id);
#endif

      obj = obj_create();
      if (obj != NULL){
        obj_set_id(obj, id);
        obj_set_name(obj, name);
        game_add_object(game, obj);

        /* Place object in its space */
        space = game_get_space(game, space_id);
        if (space) space_set_object(space, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* ========== Private: Load characters from file ========== */
/* Format: #c:id|name|gdesc|health|friendly(0/1)|message|space_id */
Status game_load_characters(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] =    "";
  char name[WORD_SIZE] =    "";
  char gdesc[WORD_SIZE] =   "";
  char message[WORD_SIZE] = "";
  char *toks =              NULL;
  Character *ch =           NULL;
  Space *space =            NULL;
  Id id = NO_ID, space_id = NO_ID;
  int health = 0, friendly = 1;
  Status status =           OK;
  int     tam_format;

  if (!game || !filename) return ERROR;

  tam_format = strlen(F_CHAR);
  file = fopen(filename, "r");
  if (file == NULL || tam_format > WORD_SIZE) return ERROR;

  while (fgets(line, WORD_SIZE, file)){
    if (strncmp(F_CHAR, line, tam_format) == 0){
      toks = strtok(line + tam_format, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);
      toks = strtok(NULL, "|\n");
      space_id = atol(toks);

#ifdef DEBUG
      printf("Leido character: c:%ld|%s|%s|%d|%d|%s|%ld\n", id, name, gdesc, health, friendly, message, space_id);
#endif

      ch = character_create();
      if (ch != NULL){
        character_set_id(ch, id);
        character_set_name(ch, name);
        character_set_gdesc(ch, gdesc);
        character_set_health(ch, health);
        character_set_friendly(ch, friendly ? TRUE : FALSE);
        character_set_message(ch, message);
        game_add_character(game, ch);

        /* Place character in its space */
        space = game_get_space(game, space_id);
        if (space) space_set_character(space, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* ========== Private: Load player ========== */
/*Format: #p: id|name|gdesc|location_id|healt|tam_bag    */
Status game_load_player(Game *game, char *filename){
  Player **player =           NULL;
  FILE    *file =             NULL;
  char    line[WORD_SIZE] =   "";
  char    *toks =             NULL;
  int     tam_format =        0;

  /*Atributos de player en lectura*/
  char    *player_name        = NULL;
  Id       player_id          = NO_ID;
  Id       player_location    = NO_ID;
  char    *player_gdesc       = NULL;
  int      player_health      = 0;
  int      player_tam_bag     = 0;


  if (!game || !filename || game_get_n_players(game) > MAX_PLAYERS) return ERROR;

  tam_format = strlen(F_PLAY);
  file = fopen(filename,"r");
  if(!file || tam_format > WORD_SIZE) return ERROR;

  while(fgets(line, WORD_SIZE, file)){
    if(strncmp(F_PLAY, line, tam_format) == 0){
      toks = strtok(line + tam_format, "|");
      if(!toks) continue;
      player_id = atol(toks);
      toks = strtok(NULL, "|");
      if(!toks) continue;

      if(player_name) {free(player_name); player_name = NULL;}
      player_name = strdup(toks);

      toks = strtok(NULL, "|");
      if(!toks) continue;
      if(player_gdesc){ free(player_gdesc); player_gdesc = NULL;}
      player_gdesc = strdup(toks); 
      toks = strtok(NULL, "|");
      if(!toks) continue;
      player_location = atol(toks);
      toks = strtok(NULL, "|");
      if(!toks) continue;
      player_health = atoi(toks);
      toks = strtok(NULL, "|");
      if(!toks) continue;
      player_tam_bag = atoi(toks);

      /*====  Configuracion de los players =====*/
      //CREACION PLAYER 0 , player 1, player 2,  player..., player n.
      //Rellenado de info a los players...

    }
    
  }









  player = game_get_players(game);
  if (!player) return ERROR;

  player_set_id(player, 1);
  player_set_name(player, "Player");
  player_set_health(player, 5);
  player_set_gdesc(player, ">8D");

  /* Start at first space */
  return player_set_location(player, game_get_space_id_at(game, 0));
}

/* ========== Public: Create game from file ========== */
Status game_create_from_file(Game **game, char *filename){
  if (!game || !filename) return ERROR;

  *game = game_create();
  if (*game == NULL) return ERROR;

  if (game_load_spaces(*game, filename) == ERROR){
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  if (game_load_objects(*game, filename) == ERROR){
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  if (game_load_characters(*game, filename) == ERROR){
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  if (game_load_player(*game, filename) == ERROR){
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  return OK;
}
