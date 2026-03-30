/**
 * @brief It implements the links struct
 *
 * @file link.c
 * @author Violeta
 * @version 0
 * @date 04-02-2025
 * @copyright GNU Public License
 */

 #include "links.h"

 struct _Links{
    Direction   direction; 
    Id          id; 
    Id          origin; 
    Id          destiny; 
    char*       name; 
    Status      status_orig;
    Status      status_dest;
};


Links*       link_create()
{   
    Links*  newlink = (Links *)malloc(sizeof(Links));
    if(!newlink) return NULL;

    newlink->name        = NULL;
    newlink->destiny     = NO_ID;
    newlink->origin      = NO_ID;
    newlink->id          = NO_ID;
    newlink->status_dest = TRUE;
    newlink->status_orig = TRUE;

    return newlink;
}

Status       link_destroy(Links *link)
{
    if(!link) return ERROR;

    if(link->name)
    {
        free(link->name);
        link->name = NULL;
    }
    free(link);
    return OK;
}

/* ============== (set/get)  ====================== */

Status       link_set_id(Links *link, Id id_new)
{
    if(!link || id_new == NO_ID) return ERROR;

    link->id = id_new;
    return  OK;
}
Id           link_get_id(Links *link)
{
    if(!link) return NO_ID;

    return link->id;  
}


/* ============== (set/get)  ====================== */

Status       link_set_name(Links *link, char *name)
{

    if(!link || !name) return ERROR;

    /* Si existe name, borra */
    if(link->name)
    {
        free(link->name);
        link->name = NULL;
    }

    /*Reservamos espacio para el nuevo name */
    int str_len = strlen(name);
    link->name = (char *)calloc(str_len + 1, sizeof(char));
    if (!link->name) return ERROR;

    /* Copiamos name en link.name, el espacio sobrante será rellenado por '\0' */
    strncpy(link->name, name, str_len);

    return  OK;
}
char*        link_get_name(Links *link)
{
    if(!link || !link->name) return NULL;

    return strdup(link->name);
}


/* ============== (set/get) status (dest_to_origin/ origin_to_dest) ====================== */

Status       link_set_open_dest_to_origin(Links *link, Bool status)
{
    if(!link) return ERROR;
    link->status_orig = status;
    return OK;
}
Bool         link_get_open_dest_to_origin(Links *link)
{
     if(!link) return FALSE;
    return link->status_orig;   
}

Status       link_set_open_origin_to_dest(Links *link, Bool status)
{
    if(!link) return ERROR;
    link->status_dest = status;
    return OK;
}
Bool         link_get_open_origin_to_dest(Links *link)
{
    if(!link) return FALSE;
    return link->status_dest; 
}

/* ============== (set/get) direction ====================== */

Status       link_set_direction(Links *link, Direction dir)
{
    if(!link || dir== U) return ERROR;
    link->direction = dir;
    return OK;
}
Direction    link_get_direction(Links *link)
{
    if(!link) return FALSE;
    return link->direction;
}

/* oppsited direction */
Direction    link_get_oppsite_direction(Links *link)
{
    if(!link) return U;
    //esto se puede optimizar tla vez usando congruencias, pero  a falta de una idea funcional lo dejare asi
    if(link->direction == N) return S;
    if(link->direction == S) return N;
    if(link->direction == E) return W;
    if(link->direction == W) return E;
    
    return U;
}

/* ============== (set/get) origin/destination ====================== */

Status       link_set_origin_id(Links *link, Id id_orig)
{
    if(!link || id_orig == U) return ERROR;
    
   link->origin = id_orig;
}
Id           link_get_origin_id(Links *link);

Status       link_set_destination_id(Links *link, Id id_dest);
Id           link_get_destination_id(Links *link);



/* ============== PRINT ====================== */

Status       link_print(Links *link);

 