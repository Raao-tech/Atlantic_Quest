/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG, Violeta, Rafael, Salvador and Javier
 * @version 5
 * @date 23-04-2026
 * @copyright GNU Public License
 */
#include "game_actions.h"
#include "game_management.h"
#include "game_rules.h"
#include "raylib.h" /*esto es una prueba*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/**
 * Private function prototypes.
 * Each handles one command type and sets the last_cmd_status in game.
 */
static void game_actions_unknown (Game* game);
static void game_actions_exit (Game* game);
static void game_actions_move (Game* game);
static void game_actions_walk (Game* game);
static void game_actions_take (Game* game);
static void game_actions_drop (Game* game);
static void game_actions_attack (Game* game);
static void game_actions_chat (Game* game);
static void game_actions_inspect (Game* game);
static void game_actions_use (Game* game);
static void game_actions_save (Game* game);
static void game_actions_load (Game* game);
static void game_actions_recruit (Game* game);
static void game_actions_kick (Game* game);


/* ======================================================
*				PRIVATE FUNCIONS TO EFFECTS				
=========================================================
*/

/**
 * @brief Esta función sirve como selccionador entre todas los posibles efectos
 * 
 *  @note	esta comprueba si el objeto es consumible o no al finalizar su función, por lo que 
 * 		asigna a NO_ID el objeto que es consumible y fue usado
 * 		
 * Por otro lado, no esoty seguro en sid ebería de ser Públia o no, 
 * Porque podríamos usar dichos efectos en otras cosas como por ejemplo en skill, aunque también 
 * pienso que si hay algún efecto, eso es problema de las acciones de player
 * 
 * 
 * 
 * 
 * 
*/
Status	game_actions_apply_effect (Game *game, Object *obj, Effect obj_effect); /*Todavía no estoy seguro de si hacerla publica o no*/

Status	_game_actions_apply_health_plus (Game* game, Object* obj);
Status	_game_actions_apply_health_less (Game* game, Object* obj);
Status	_game_actions_apply_open_door 	(Game* game, Object* obj);
Status	_game_actions_apply_speed_plus  (Game* game, Object* obj); 	/*Falta implementar*/
Status	_game_actions_apply_speed_less  (Game* game, Object* obj);	/*Falta implementar*/

/**
 * @brief Converts a direction string to a Direction enum value
 *
 * Accepts "north"/"n", "south"/"s", "east"/"e", "west"/"w"
 * (case-insensitive).  Returns U if unrecognized.
 */
Direction ge_parse_direction (const char* str);

/* ========================================================================= */
/*                          PUBLIC: DISPATCHER                               */
/* ========================================================================= */

/*
 * La idea seria que ahora no solo seactivaran las caciones ,por medio del
 * teclado. esto se mantendrá, pero el comando central tiene que ser el input
 * del usario por medio del teclado,  player 1 y 2 pueden mverse gracias a
 * "wasd" o a las flechas "Up, Down, Right, Left" y tendrànm posibildiad de
 * hacer otras cosas con otras "KEYs" del teclado. Tal vez lo del Keyboards no
 * es el tipo de dato, eso se pued equitar, era para no olvidar que ese cambio
 * se tienme que hacer Pero ta,mbien hay que mantender ewl command porque las
 * pruebas automatixadas se hacen atraves de texto, asi que eso se debe de jdjar
 * para los logs, luego veré como hago coo
 *
 *   Punto importante:                         Modo de Juego (SourceInput)
 *       Modo Test                                     Modo Juego
 *  (Textual, no visual)                         (keys de Keyboard, Visual)
 *  (comandos por player, No en paralelo)        (comandos dependientes de
 * "wasd" o flechas, en paralelo)
 *
 *  Una posible propuesta de adaptación es la siguiente:
 *      la estrctura de command tendrá : {}
 *
 *
 *
 */
Status
game_actions_update (Game* game, Command* command)
{
	CommandCode cmd;

	if (!game || !command) return ERROR;
	if (game_set_last_command (game, command) == ERROR) return ERROR;

	cmd = command_get_code (command);

	switch (cmd)
		{
			case UNKNOWN: game_actions_unknown (game); break;
			case EXIT: game_actions_exit (game); break;
			case MOVE: game_actions_move (game); break;
			case WALK: game_actions_walk (game); break;
			case TAKE: game_actions_take (game); break;
			case DROP: game_actions_drop (game); break;
			case ATTACK: game_actions_attack (game); break;
			case CHAT: game_actions_chat (game); break;
			case INSPECT: game_actions_inspect (game); break;
			case USE: game_actions_use (game); break;
			case SAVE: game_actions_save (game); break;
			case LOAD: game_actions_load (game); break;
			case RECRUIT: game_actions_recruit (game); break;
			case KICK: game_actions_kick (game); break;
			default: break;
		}
	return OK;
}

/* ========================================================================= */
/*                       PRIVATE: ACTION HANDLERS                            */
/* ========================================================================= */

/* ---- UNKNOWN ---- */
static void
game_actions_unknown (Game* game)
{
	if (!game) return;
	game_set_last_cmd_status (game, ERROR);
}

/* ---- EXIT ---- */
static void
game_actions_exit (Game* game)
{
	if (!game) return;
	game_set_last_cmd_status (game, OK);
}

/* ========================================================================= */
/*                    MOVE (F8): move <direction>                             */
/* ========================================================================= */

static void
game_actions_move (Game* game)
{
	if (!game || game_rule_move (game) == ERROR)
		{
			game_set_last_cmd_status (game, ERROR);
			return;
		}
	game_set_last_cmd_status (game, OK);
	return;
}

/* ========================================================================= */
/*                    TAKE (F10): take <object_name>                          */
/* ========================================================================= */
static void
game_actions_take (Game* game)
{
	Player* player = NULL;
	Space* space   = NULL;
	Object* obj    = NULL;
/* 	char* obj_name = NULL; */
	Position obj_pos;
	Position ply_vision;
	Id space_id, obj_id, dependency_id;
	Bool movable;

	if (!game) return;

	ply_vision.pos_x = NO_POS;
	ply_vision.pos_y = NO_POS;
	obj_pos.pos_x    = NO_POS;
	obj_pos.pos_y    = NO_POS;


	/*Se obtiene el player*/
	player = game_get_player_by_turn (game);
	if (!player){game_set_last_cmd_status (game, ERROR_take);return;}

	/*Se  Obtiene el campo de visión o acción del player*/
	ply_vision = player_get_vision (player);

	/*Se  Obtiene el Space donde esta el player*/
	space_id   = player_get_zone (player);
	if (space_id == NO_ID)	{game_set_last_cmd_status (game, ERROR_take);	return;}
	space         = game_get_space (game, space_id);
	if (!space) {game_set_last_cmd_status (game, ERROR_take);	return;}


	/*Se obtinee el objeto del objet que coincide con la cision del player*/
	obj  	= game_get_object_by_vision (game, ply_vision);
	if(!obj) {game_set_last_cmd_status (game, ERROR_take);	return;}
	obj_id = obj_get_id (obj);
	if (obj_id == NO_ID) {game_set_last_cmd_status (game, ERROR_take);	return;}


	/*Si el obejto no está contenido en el space, error*/
	if (space_contains_object (space, obj_id) == FALSE)
		{game_set_last_cmd_status (game, ERROR_take);	return;}

	/*Preguntamos si es un obejto movible*/
	movable = obj_get_movable (obj);
	if (movable == FALSE)
		{
			/*Si no es movible se pregunta  por lo que necesita player para mover dicho objeto*/
			dependency_id = obj_get_dependency (obj);
			if (dependency_id == NO_ID || player_contains_object (player, dependency_id) == FALSE)
				{game_set_last_cmd_status (game, ERROR_take);	return;}
		}
	
	space_remove_object (space, obj_id, obj_pos);
	if (player_add_object (player, obj_id) != OK)
		{
			/* Inventory full — put the object back */
			space_set_object (space, obj_id, obj_pos);
			game_set_last_cmd_status (game, ERROR_take);
			return;
		}

	game_set_last_cmd_status (game, OK);
	return;
}

/* ========================================================================= */
/*                    DROP: drop <object_name>                          */
/* ========================================================================= */
static void
game_actions_drop (Game* game)
{
	Player* player 			= NULL;
	Space* space   			= NULL;
	Object* obj    			= NULL;
	Command* last_command	= NULL; 
	char*obj_char			= NULL;
	Id space_id, obj_id;
	Position ply_vision;

	/*Inicializamos la vision*/
	ply_vision.pos_x = NO_POS;
	ply_vision.pos_y = NO_POS;

	if (!game) return;


	/*Obtenemos el puntero a player*/
	player = game_get_player_by_turn (game);
	if (!player)	{ game_set_last_cmd_status (game, ERROR_drop);	return;}

	/*Obtenemos el valor de la posicion a la que esta viendo el player*/
	ply_vision = player_get_vision (player);
	if (ply_vision.pos_x == NO_POS || ply_vision.pos_y == NO_POS)
		{game_set_last_cmd_status (game, ERROR_drop);	return;}

	/*Obtenemos el utlimo comando del jgador*/
	last_command = game_get_last_command (game);
	if (!last_command)	{game_set_last_cmd_status (game, ERROR_drop);	return;}

	/*Obtenemos el Objeto que tiene activo el jugador*/
	obj_char = command_get_target(last_command);
	if (obj_char)
	{
		obj = game_get_object_by_name (game, obj_char);
		if (!obj)	{game_set_last_cmd_status (game, ERROR_drop);	return;}
		obj_id = obj_get_id (obj);
	}
	else
	{
		obj_id = player_get_active_object(player);
		obj = game_get_object_by_id (game, obj_id);
		if (!obj)	{game_set_last_cmd_status (game, ERROR_drop);	return;}
	}


	

	/*Obtenemos space en el que esta el jugador*/
	space_id = player_get_zone (player);
	if (space_id == NO_ID)	{game_set_last_cmd_status (game, ERROR_drop);	return;}

	/*Volvemos a comprobar que el jugador tenga el objeto en su invetario*/
	if (player_contains_object (player, obj_id) == FALSE)
		{game_set_last_cmd_status (game, ERROR_drop);return;}

	
   /* Mecánica del drop */
    player_delete_object (player, obj_id);
    space_set_object (space, obj_id, ply_vision);   /* o la posición que toque */
    obj_set_position (obj, ply_vision.pos_x, ply_vision.pos_y);

    /* Si era el active_object, lo limpiamos: ya no lo porta */
    if (player_get_active_object (player) == obj_id)
        player_set_active_object (player, NO_ID);
	
	game_set_last_cmd_status (game, OK);
}

/* ========================================================================= */
/*            WALK: walk (w) <direction>                    */
/* ========================================================================= */
static void
game_actions_walk (Game* game)
{
    Command*  lst_cmd;
    Player*   player;
    char*     dir_str;
    Space*    space;
    int*      grid_line;
    Direction direction;
    Position  pos_current;
    int       cell_x, cell_y, pos_update;

    if (!game)                            { game_set_last_cmd_status (game, ERROR_walk); return; }
    lst_cmd = game_get_last_command (game);
    if (!lst_cmd)                         { game_set_last_cmd_status (game, ERROR_walk); return; }
    dir_str = command_get_target (lst_cmd);
    if (!dir_str)                         { game_set_last_cmd_status (game, ERROR_walk); return; }
    direction = ge_parse_direction (dir_str);
    if (direction == U)                   { game_set_last_cmd_status (game, ERROR_walk); return; }

    player = game_get_player_at (game, PLAYER);
    if (!player)                          { game_set_last_cmd_status (game, ERROR_walk); return; }

    pos_current = player_get_position (player);

    /* Calculamos la posicion destino EN PIXELES */
    switch (direction)
    {
        case N: pos_current.pos_y -= SCALE; break;
        case S: pos_current.pos_y += SCALE; break;
        case W: pos_current.pos_x -= SCALE; break;
        case E: pos_current.pos_x += SCALE; break;
        default: game_set_last_cmd_status (game, ERROR_walk); return;
    }

    /* Convertimos a CELDAS y validamos rango */
    cell_x = pos_current.pos_x / SCALE;
    cell_y = pos_current.pos_y / SCALE;
    if (cell_x < 0 || cell_x >= WIDHT ||
        cell_y < 0 || cell_y >= HIGHT)
    {
        /* Salirte del mapa por el borde es un walk fallido (de momento).
         * esto sera el detector para cambiar de space. */
        game_set_last_cmd_status (game, ERROR_walk);
        return;
    }

    /* Pedimos solo la fila que necesitamos, no el grid entero */
    space = game_get_space (game, player_get_zone (player));
    if (!space)                           { game_set_last_cmd_status (game, ERROR_walk); return; }

    grid_line = space_get_grid_by_line (space, cell_y);
    if (!grid_line)                       { game_set_last_cmd_status (game, ERROR_walk); return; }

    pos_update = grid_line[cell_x];

    /* Celda no transitable: 0 (pared) o un id de objeto bloqueante.
     * Por ahora simplemente pedimos transitable=1. */
    if (pos_update == 0)	{game_set_last_cmd_status (game, ERROR_walk);	return;}

    if (player_set_position (player, pos_current.pos_x, pos_current.pos_y) == ERROR)
    	{game_set_last_cmd_status (game, ERROR_walk);	return;}

    game_set_last_cmd_status (game, OK);
}
/* ========================================================================= */
/*            ATTACK: attack <name>  (NPC or PvP)                            */
/* ========================================================================= */
/*
 * The attack command now supports TWO modes:
 *
 *  1. NPC combat (original):
 *     "attack Skeleton" → find Character by name → must be in
 *     same spacee, hostile, alive → random roll.
 *
 *  2. PvP combat (NEW):
 *     "attack witch" -> if no Character found with that name,
 *     search for a Player with that name → must be in same space,
 *     cannot be yourself -> random roll anddd game_turn_update can whit all
 *     trust sjsj
 */
static void
game_actions_attack (Game* game)
{
	Player* player = NULL;
	Space* space   = NULL;
	Numen *num = NULL, *enemy_num = NULL;
	char* skill_indx_ch = NULL;
	Skills_id skill     = TAKLE;
	Id space_id, num_id;
	Set* space_numens = NULL;
	int roll, distance, skill_indx, radio, active_pos_x, active_pos_y, enemy_pos_x, enemy_pos_y, num_enemies, i;

	if (!game) return;

	player = game_get_player_at (game, PLAYER);
	if (!player)			{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	num_id = player_get_active_numen (player);
	if (num_id == NO_ID)	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	space_id = player_get_zone (player);
	if (space_id == NO_ID)	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	skill_indx_ch = command_get_target (game_get_last_command (game));
	if (!skill_indx_ch)	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	skill_indx = atoi (skill_indx_ch);
	if (skill_indx < 0 || skill_indx >= NUM_SKILLS) 	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	space = game_get_space (game, space_id);
	num   = game_get_numen_by_id (game, num_id);
	if (!space || !num)		{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	active_pos_x = numen_get_pos_x (num);
	active_pos_y = numen_get_pos_y (num);

	if (numen_get_health (num) <= 0)	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	skill = numen_get_skill_by_index (num, skill_indx);
	if (skill == NO_SKILL)	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	radio        = skill_get_radio (skill); /*por implementar*/

	space_numens = space_get_numens (space);
	if (!space_numens)	{game_set_last_cmd_status (game, ERROR_Attack);	return;}

	num_enemies = space_get_n_numens (space);

	/* For simplicity, we apply the skill effect to all valid targets in range. */
	for (i = 0; i < num_enemies; i++)
		{
			enemy_num = game_get_numen_by_id (game, set_get_id_at (space_numens, i));
			if (enemy_num && enemy_num && numen_get_id (enemy_num) != num_id && numen_get_corrupt (enemy_num) == FALSE)
				{
					if (numen_get_health (enemy_num) <= 0) { continue; /* Skip dead enemies */ }
					enemy_pos_x = numen_get_pos_x (enemy_num);
					enemy_pos_y = numen_get_pos_y (enemy_num);
					distance    = sqrt (pow (active_pos_x - enemy_pos_x, 2) + pow (active_pos_y - enemy_pos_y, 2));
					if (distance <= radio)
						{
							if (skill_active (num, enemy_num, skill, distance) == ERROR) /*por implementar status skill_apply_effect*/
								{game_set_last_cmd_status (game, ERROR_Attack);	return;}

							/*====== Efectos Secudarios ============*/
							/**
							 *  Propagacion de Fire Ball: tras golpear al primer enemigo,
						 	 * lanzamos una FIRE_BALL_A desde su posicion a todos sus vecinos.	
							 * 	
							 * 
							 * Estos efectos secudnarios puede que sea mejor implemantar un switch
							 * y hacerlos funciones privadas de game_actions attack, más que nada porque }
							 * generan muhco ruido en el código, el cual debería de ser lo más simple y legible
							 * que se pueda.  Pero por cuestiones de tiempo lo tendremos así
							 * 
							 * Por favor, alguien que recuerde que esto lo tenemos que cambiar o mjeorar, pero 
							 * lo primero es que funcione.
							 * 
							 * 
							 * 
							*/
							if (skill == FIRE_BALL)
							{
							    int radio_a = skill_get_radio (FIRE_BALL_A);
							    int j;
							    for (j = 0; j < num_enemies; j++)
							    {
							        Numen* secondary = game_get_numen_by_id (game, set_get_id_at (space_numens, j));
							        if (!secondary || secondary == enemy_num) continue;
							        if (numen_get_id (secondary) == num_id) continue;
							        if (numen_get_corrupt (secondary) == FALSE) continue;
							        if (numen_get_health (secondary) <= 0) continue;
								
							        int dx = numen_get_pos_x (secondary) - numen_get_pos_x (enemy_num);
							        int dy = numen_get_pos_y (secondary) - numen_get_pos_y (enemy_num);
							        int sec_distance = (int)sqrt (pow (dx, 2) + pow (dy, 2));
								
							        if (sec_distance <= radio_a)
							            skill_active (enemy_num, secondary, FIRE_BALL_A, sec_distance);
							    }
							}
						}
				}
		}
	game_set_last_cmd_status (game, OK);
	return;
}

/* ========================================================================= */
/*                    CHAT: chat <character_name>                             */
/* ========================================================================= */
static void
game_actions_chat (Game* game)
{
	Player* player  = NULL;
	Space* space    = NULL;
	Numen* ch       = NULL;
	char* char_name = NULL;
	Id char_id, space_id;

	if (!game) return;

	player = game_get_player_by_turn (game);
	if (!player)
		{
			game_set_last_cmd_status (game, ERROR_Chat);
			return;
		}

	space_id = player_get_zone (player);
	if (space_id == NO_ID)
		{
			game_set_last_cmd_status (game, ERROR_Chat);
			return;
		}

	char_name = command_get_target (game_get_last_command (game));
	if (!char_name)
		{
			game_set_last_cmd_status (game, ERROR_Chat);
			return;
		}

	ch = game_get_numen_by_name (game, char_name);
	if (!ch)
		{
			game_set_last_cmd_status (game, ERROR_Chat);
			return;
		}

	char_id = numen_get_id (ch);
	space   = game_get_space (game, space_id);

	if (space_contains_character (space, char_id) == FALSE)
		{
			game_set_last_cmd_status (game, ERROR_Chat);
			return;
		}

	if (numen_get_following (ch) == NO_ID)
		{
			game_set_last_cmd_status (game, ERROR_Chat);
			return;
		}

	game_set_last_cmd_status (game, OK);
}

/* ========================================================================= */
/*           INSPECT (F9): inspect <object_name>                             */
/* ========================================================================= */
/*
 */
static void
game_actions_inspect (Game* game)
{
	Player* player = NULL;
	Space* space   = NULL;
	Object* obj    = NULL;
	char* obj_name = NULL;
	Id obj_id, space_id;
	Bool in_space, in_inventory;

	if (!game) return;

	player = game_get_player_by_turn (game);
	if (!player)	{game_set_last_cmd_status (game, ERROR_inspect);	return;}

	obj_name = command_get_target (game_get_last_command (game));
	if (!obj_name)	{game_set_last_cmd_status (game, ERROR_inspect);	return;}

	obj = game_get_object_by_name (game, obj_name);
	if (!obj)	{game_set_last_cmd_status (game, ERROR_inspect);		return;}

	obj_id   = obj_get_id (obj);
	space_id = player_get_zone (player);
	space    = game_get_space (game, space_id);

	/* Object must be accessible: in current space OR in inventory */
	in_space     = (space && space_contains_object (space, obj_id));
	in_inventory = player_contains_object (player, obj_id);

	if (in_space == FALSE && in_inventory == FALSE)	{game_set_last_cmd_status (game, ERROR_inspect);	 return;}

	/* Object must have a description */
	if (obj_get_description (obj) == NULL || obj_get_description (obj)[0] == '\0')
		{game_set_last_cmd_status (game, ERROR_inspect);	 return;}

	game_set_last_cmd_status (game, OK);
}

/* ========================================================================= */
/*           USE: use <object_name>                                          */
/* ========================================================================= */
static void
game_actions_use (Game* game)
{
	Player* player = NULL;
	Numen* num     = NULL;
	Object* obj    = NULL;
	char* obj_name = NULL;
	Id obj_id;
	Bool in_inventory = FALSE;
	Effect obj_effect = NO_EFECT;
	Status	result_effect = ERROR_use;

	if (!game) return;

	/*Obtenemos jugador*/
	player = game_get_player_by_turn (game);
	if (!player)	{game_set_last_cmd_status (game, ERROR_use);    return;}
	/*obtenemos objeto el nombre del objeto*/
	obj_name = command_get_target (game_get_last_command (game));
	if (!obj_name)	{game_set_last_cmd_status (game, ERROR_use);    return;}
	/*Obtenemos el objeto según el nombre anteriormente guardado*/
	obj = game_get_object_by_name (game, obj_name);
	if (!obj)   {game_set_last_cmd_status (game, ERROR_use);    return;}

	/*Obtenemos el id del objeto*/
	obj_id = obj_get_id (obj);
	/* Verficamos que el objeto esté en el inventory según su Id */
	in_inventory = player_contains_object (player, obj_id);
	if (in_inventory == FALSE)  {game_set_last_cmd_status (game, ERROR_use); return;}

	
	/*Preguntamos si el objeto tiene algún efecto*/
	obj_effect = obj_get_effect (obj);

	/*Aplicamos el efecto y guardamos su resultado*/
	result_effect = game_actions_apply_effect (game, obj, obj_effect);

	
	/*****************************/

	game_set_last_cmd_status (game, result_effect);
	return;
}


/* ========================================================================= */
/*                      SAVE: save                                           */
/* ========================================================================= */
static void
game_actions_save (Game* game)
{
	if (!game)	{game_set_last_cmd_status (game, ERROR_save);		return;}

	if (game_management_save_file (&game) == OK) game_set_last_cmd_status (game, OK);
	else	{game_set_last_cmd_status (game, ERROR_save);}

	return;
}

void game_actions_load (Game* game)
{
	if(!game) return;
	return;
}

void game_actions_recruit (Game* game)
{
	if(!game) return;
	return;
}
void game_actions_kick (Game* game)
{
	if(!game) return;
	return;
}




/* ========================================================================= */
/*                      HELPER: PARSE DIRECTION                              */
/* ========================================================================= */

Direction
ge_parse_direction (const char* str)
{
	if (!str) return U;

	if (strcasecmp (str, "north") == 0 || strcasecmp (str, "n") == 0 || strcasecmp (str, "N") == 0) return N;
	if (strcasecmp (str, "south") == 0 || strcasecmp (str, "s") == 0 || strcasecmp (str, "S") == 0) return S;
	if (strcasecmp (str, "east") == 0 || strcasecmp (str, "e") == 0  || strcasecmp (str, "E") == 0) return E;
	if (strcasecmp (str, "west") == 0 || strcasecmp (str, "w") == 0  || strcasecmp (str, "W") == 0) return W;

	return U;
}

/* ========================================================================= */
/*                         EFFECT (Objects)                                	 */
/* ========================================================================= */

Status	
game_actions_apply_effect (Game *game, Object *obj, Effect obj_effect)
{
	Status result = OK;
	if(!game || !obj ) 			return ERROR;
	if(obj_effect == NO_EFECT)	return OK; /*En principio un objeto que no tiene efecto no debería de generar un error de uso, porque no tiene ni siquera un uso*/

	/*    NO_EFECT,
    HEALTH_PLUS,
    SPEED_PLUS,
    SPEED_LES,
    OPEN*/
	switch (obj_effect)
	{
		case HEALTH_PLUS:	result = _game_actions_apply_health_plus (game, obj);	break;
		case HEALTH_LESS:	result = _game_actions_apply_health_less (game, obj);	break;
		case SPEED_PLUS:	result = _game_actions_apply_speed_plus  (game, obj);	break; /*Falta implementar apply_speed*/
		case SPEED_LESS:	result = _game_actions_apply_speed_less  (game, obj);	break; /*Falta implementar apply_speed*/
		case OPEN:			result = _game_actions_apply_open_door	 (game, obj);	break; 
	
		default: result = ERROR_use;														break;
	}


	if(obj_get_consumable (obj) == TRUE ) obj_set_id (obj, NO_ID);  /*"Quitamos" a obj del juego*/

	return result;
}


/* ========================== FALTA IMPLEMENTAR ============================*/
Status _game_actions_apply_speed_plus  (Game* game, Object* obj)
{
	if(!game || !obj) return ERROR_use;
	return OK;
}
Status _game_actions_apply_speed_less  (Game* game, Object* obj)
{
	if(!game || !obj) return ERROR_use;
	return OK;
}
/* ========================== ======================== ============================*/


Status
_game_actions_apply_health_plus (Game* game, Object* obj)
{
	Numen   *numen_active = NULL;
	Player  *player       = NULL;
	Id		 active_id	  = NO_ID;
	int      life_update  = 0;
	if(!game || !obj) return  ERROR_use;

	player = game_get_player (game);
	if (!player) return ERROR_use;
	active_id = player_get_active_numen (player);
	if (active_id == NO_ID) return ERROR_use;
	numen_active = game_get_numen_by_id (game, active_id);
	if (!numen_active) return ERROR_use;

	life_update = numen_get_health (numen_active) + obj_get_health (obj);

	if (numen_set_health (numen_active, life_update) == ERROR) return ERROR_use;

	return OK;
}
Status
_game_actions_apply_health_less (Game* game, Object* obj)
{
	Numen   *numen_active = NULL;
	Player  *player       = NULL;
	Id		active_id	  = NO_ID;
	int      life_update  = 0;
	if(!game || !obj) return  ERROR_use;

	player = game_get_player (game);
	if (!player) return ERROR_use;
	active_id = player_get_active_numen (player);
	if (numen_active == NO_ID) return ERROR_use;
	numen_active = game_get_numen_by_id (game, active_id);
	if (!numen_active) return ERROR_use;

	life_update = numen_get_health (numen_active) - obj_get_health (obj);

	if (numen_set_health (numen_active, life_update) == ERROR) return ERROR_use;

	return OK;
}

Status
_game_actions_apply_open_door (Game* game, Object* obj)
{
	Player  *player       = NULL;
	Space	*space		  = NULL;
	Links	*link		  = NULL;
	Id		 space_id 	  = NO_ID;
	Id		 link_id 	  = NO_ID;
	int      life_update  = 0;
	if(!game || !obj) return  ERROR_use;

	/*Obtenemos player*/
	player = game_get_player (game);
	if (!player) return ERROR_use;

	/*Obtenemos space en el que está el player*/
	space_id = player_get_zone (player);
	space	 = game_get_space(game, space_id);
	if (!space) return ERROR_use;
	
	/*Obtenemos el link que abre el objeto*/
	link_id = obj_get_open (obj);
	link = 	  game_get_link_by_id (game, link_id);
	if(!link) return ERROR_open; /*Error especial del use*/


	/*Preguntamos si ya está abierto el link que se iba  a abrir, para no hacerlo dos veces (origen <-> destino)*/
	if (game_connection_is_open (game, space_id, link_get_direction (link)) == TRUE)
		{return ERROR_open;}

	/*Preguntamos los ids de los spaces coentacods por link*/
	if (link_get_origin_id (link) != space_id && link_get_destination_id (link) != space_id)
		{return ERROR_open;}

	/*Si el jugador está en el destino, la llave abre el origen*/
	if (link_get_destination_id (link) == space_id  && link_set_open_dest_to_origin (link, TRUE) == ERROR) 
		{return ERROR_open;}
	/*Si el jugador está en el origen, la llave abre el destino*/
	else if (link_get_origin_id (link) == space_id  && link_set_open_origin_to_dest (link, TRUE) == ERROR)
		{return ERROR_open;}

	return OK;
}