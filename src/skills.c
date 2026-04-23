/**
 * @brief It implements the skills struct
 *
 * @file skills.c
 * @author Rafael
 * @version 0
 * @date 20-04-2026
 * @copyright GNU Public License
 */

#include "skills.h"

/*============== PUBLIC FUNCTION ======================*/
void skill_active(Numen * sender, Numen* receiver, Skills id_skill)
{
    if(!sender || !receiver || id_skill == NO_ID) return ERROR;

    switch (id_skill)
    {
    case TAKLE : skill_active_takle(sender, receiver, id_skill);
        /* code */
        break;
    
    default:
        break;
    }

}