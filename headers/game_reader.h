/**
 * @brief It reads information from files to define the game
 *
 * @file game_reader.h
 * @author Profesores PPROG
 * @version 2
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief It creates a game and loads all data from a file
 * @author Violeta y Rafa
 *
 * @param game pointer to pointer to the game (will be allocated)
 * @param filename string with the name of the data file
 * @return OK, if everything goes well, or ERROR if there was some mistake
 */
Status game_create_from_file(Game **game, char *filename);

#endif
