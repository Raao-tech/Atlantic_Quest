/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

void game_actions_next(Game *game);

void game_actions_back(Game *game);

void game_actions_left(Game *game);

void game_actions_right(Game *game);

void game_actions_take(Game *game);

void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd)
  {

  case UNKNOWN:
    game_actions_unknown(game);
    break;

  case EXIT:
    game_actions_exit(game);
    break;

  case NEXT:
    game_actions_next(game);
    break;

  case LEFT:
    game_actions_left(game);
    break;
  case RIGHT:
    game_actions_right(game);
    break;

  case BACK:
    game_actions_back(game);
    break;

  case TAKE:
    game_actions_take(game);
    break;
  case DROP:
    game_actions_drop(game);
    break;

  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) { (void)game; }

void game_actions_exit(Game *game) { (void)game; }

void game_actions_next(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));

  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_left(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));

  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_right(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));

  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game)
{
  Id obj_id = NO_ID;
  Id space_id = NO_ID;
  char *obj_name = NULL;

  space_id = game_get_player_location(game);
  obj_name = command_get_obj(game_get_last_command(game));

  obj_id=game_get_obj_id_from_name(obj_name);

  if (NO_ID == space_id)
  {
    return;
  }

  if (game_is_obj_in_space(space_id, obj_id) == FALSE) return;
  
  if (game_set_player_object(game, obj_id) == ERROR) return;

  if (game_delete_space_object(space_id, obj_id) == ERROR) return;
  
  return;
}


void game_actions_drop(Game *game){
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) return;

  if (game_player_drop(game) == ERROR) return;
  
  return;
}
