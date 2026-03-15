/**
 * @brief It declares the tests for the game module
 *
 * @file game_test.h
 * @author Rafael y Violeta
 * @version 2
 * @date 28-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_TEST_H
#define GAME_TEST_H

/* game_create / destroy */
void test1_game_create();
void test2_game_create();
void test1_game_destroy();
void test2_game_destroy();

/* game_get_player */
void test1_game_get_player();
void test2_game_get_player();

/* game_add_space / get_space */
void test1_game_add_space();
void test2_game_add_space();
void test1_game_get_space();
void test2_game_get_space();
void test3_game_get_space();

/* game_add_object / get_object_by_id / get_object_by_name */
void test1_game_add_object();
void test2_game_add_object();
void test1_game_get_object_by_id();
void test2_game_get_object_by_id();
void test1_game_get_object_by_name();
void test2_game_get_object_by_name();

/* game_get_object_location */
void test1_game_get_object_location();
void test2_game_get_object_location();
void test3_game_get_object_location();

/* game_add_character / get_character_by_id / get_character_by_name */
void test1_game_add_character();
void test2_game_add_character();
void test1_game_get_character_by_id();
void test2_game_get_character_by_id();
void test1_game_get_character_by_name();
void test2_game_get_character_by_name();

/* game_get_character_location */
void test1_game_get_character_location();
void test2_game_get_character_location();

/* game_get_object_at / character_at / space_id_at */
void test1_game_get_object_at();
void test2_game_get_object_at();
void test1_game_get_character_at();
void test2_game_get_character_at();
void test1_game_get_space_id_at();
void test2_game_get_space_id_at();

/* game_get_n_spaces / n_objects / n_characters */
void test1_game_get_n_spaces();
void test2_game_get_n_spaces();
void test1_game_get_n_objects();
void test1_game_get_n_characters();

/* game state: finished, last_command, last_cmd_status */
void test1_game_set_finished();
void test2_game_get_finished();
void test1_game_set_last_command();
void test1_game_set_last_cmd_status();
void test2_game_get_last_cmd_status();

#endif
