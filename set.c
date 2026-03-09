#include "stdio.h"
#include "stdlib.h"
#include "set.h"

struct _Set{
    Id*  ids;
    int  n_ids;
};


Set*    set_creat(){
    Set*    newset = NULL;
    int i;

    

    if((newset= (Set*)malloc(sizeof(Set))) == NULL){
        return  NULL;
    }
    newset->n_ids = 0;
    
    if((newset->ids = (Id*)malloc(sizeof(Id))) == NULL){
        return  NULL;
    }

    newset->ids[0] = NO_ID;
    

    return newset;
}

Status  set_destroy(Set *pset){

    int i;

    if(!pset ){
        return ERROR;
    }

    if((pset)->ids){
        for ( i = 0; i < (pset)->n_ids; i++){
           (pset)->ids[i] = NO_ID;
        }
        free((pset)->ids);
        (pset)->ids = NULL;
    }

    (pset)->n_ids = 0;

    free((pset));

    return OK;
}

Bool	set_is_empty(Set *pset){

    int i;

	if(pset == NULL){
		return	FALSE;
	}

	if(pset->n_ids <= 0){
		return TRUE;
	}

	return FALSE;
}


Status	set_add(Set* pset, Id	 new_id){

	/* If pset or new_id don't exist  */
	if(pset == NULL || new_id == NO_ID){
		return	ERROR;
	}

	//agregamos un espacio en el conjutno de objetos
	Id* pset_temp = (Id*)realloc((void *)pset->ids, (sizeof(Id) * (pset->n_ids + 1)) );
	
	if(pset_temp == NULL){
		return ERROR;
	}
	pset_temp[pset->n_ids] = new_id;
	pset->n_ids++; 

	pset->ids = pset_temp;

	return	OK;
}

Id	set_pop(Set* pset){

	Id id_pop;

	if(!pset){
		return NO_ID;
	}
	if(set_is_empty(pset) == TRUE){
		return	NO_ID;
	}
	
	
	id_pop = pset->ids[pset->n_ids - 1 ];
	pset->ids[pset->n_ids - 1 ] = NO_ID;

	Id* pset_temp = (Id*)realloc((void *)pset->ids, (sizeof(Id) * (--pset->n_ids)));



	return ();

	



}