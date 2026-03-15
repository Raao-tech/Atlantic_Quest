/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "character.h"

#define MAX_SPACES      100
#define MAX_OBJECTS     100
#define MAX_CHARACTERS  100

typedef struct _Game Game;


/* ========== Create / Destroy ========== */

/**
 * @brief It creates a new game, allocating memory and initializing it
 * @author Profesores PPROG
 *
 * @return pointer to new game, or NULL if memory fails
 */
Game *game_create();

/**
 * @brief It destroys a game, freeing all allocated memory
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_destroy(Game *game);


/* ========== Access: Enfoque B (expose pointers) ========== */

/**
 * @brief It gets the player pointer
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return pointer to the player, or NULL if game is NULL
 */
Player *game_get_player(Game *game);

/**
 * @brief It gets a space by its id
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param id the id of the space to find
 * @return pointer to the space, or NULL if not found
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets the last command
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return pointer to the last command, or NULL if game is NULL
 */
Command *game_get_last_command(Game *game);


/* ========== Add elements (used by game_reader) ========== */

/**
 * @brief It adds a space to the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param space a pointer to the space to add
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It adds an object to the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param obj a pointer to the object to add
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_add_object(Game *game, Object *obj);

/**
 * @brief It adds a character to the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param character a pointer to the character to add
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_add_character(Game *game, Character *character);


/* ========== Search: Objects ========== */

/**
 * @brief It finds an object by its id
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param id the id of the object to find
 * @return pointer to the object, or NULL if not found
 */
Object *game_get_object_by_id(Game *game, Id id);

/**
 * @brief It finds an object by its name
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param name the name of the object to find
 * @return pointer to the object, or NULL if not found
 */
Object *game_get_object_by_name(Game *game, char *name);

/**
 * @brief It finds in which space an object is located
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param obj_id the id of the object to locate
 * @return the id of the space containing the object, or NO_ID if not found (may be in player inventory)
 */
Id game_get_object_location(Game *game, Id obj_id);


/* ========== Search: Characters ========== */

/**
 * @brief It finds a character by its id
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param id the id of the character to find
 * @return pointer to the character, or NULL if not found
 */
Character *game_get_character_by_id(Game *game, Id id);

/**
 * @brief It finds a character by its name
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param name the name of the character to find
 * @return pointer to the character, or NULL if not found
 */
Character *game_get_character_by_name(Game *game, char *name);

/**
 * @brief It finds in which space a character is located
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param char_id the id of the character to locate
 * @return the id of the space containing the character, or NO_ID if not found
 */
Id game_get_character_location(Game *game, Id char_id);


/* ========== Access by index (for iteration) ========== */

/**
 * @brief It gets an object by its position in the array
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param position the index in the objects array
 * @return pointer to the object, or NULL if out of range
 */
Object *game_get_object_at(Game *game, int position);

/**
 * @brief It gets a character by its position in the array
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param position the index in the characters array
 * @return pointer to the character, or NULL if out of range
 */
Character *game_get_character_at(Game *game, int position);

/**
 * @brief It gets the id of a space by its position in the array
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param position the index in the spaces array
 * @return the id of the space, or NO_ID if out of range
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It returns the number of spaces in the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return number of spaces, or -1 if game is NULL
 */
int game_get_n_spaces(Game *game);

/**
 * @brief It returns the number of objects in the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return number of objects, or -1 if game is NULL
 */
int game_get_n_objects(Game *game);

/**
 * @brief It returns the number of characters in the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return number of characters, or -1 if game is NULL
 */
int game_get_n_characters(Game *game);


/* ========== Game state ========== */

/**
 * @brief It sets the game as finished or not
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param finished TRUE to mark as finished, FALSE otherwise
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief It checks if the game has finished
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return TRUE if finished, FALSE otherwise (defaults to TRUE if game is NULL)
 */
Bool game_get_finished(Game *game);

/**
 * @brief It sets the last command of the game
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param command a pointer to the command
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It sets the status result of the last command executed
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @param status OK or ERROR
 * @return OK, if everything goes well, or ERROR if game is NULL
 */
Status game_set_last_cmd_status(Game *game, Status status);

/**
 * @brief It gets the status result of the last command executed
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 * @return OK or ERROR (defaults to ERROR if game is NULL)
 */
Status game_get_last_cmd_status(Game *game);


/* ========== Print (debugging) ========== */

/**
 * @brief It prints the full game state for debugging
 * @author Violeta y Rafa
 *
 * @param game a pointer to the game
 */
void game_print(Game *game);

#endif