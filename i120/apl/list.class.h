#ifndef _LIST_CLASS_H
#define _LIST_CLASS_H

#include <stdio.h>
#include "konto.class.h"

typedef struct _lst {
	struct _lst *next;
	konto *data;
} list;

list
*list_erstellen( void ) {
	list *ptrtmp = NULL;				/* decl. new list, init. with ptr on 0x0 for comparison */
	ptrtmp = (list*)malloc( sizeof(list) );	/* reserve memory on heap */
	if( ptrtmp != NULL ) {				/* malloc succeeded if ptr is not NULL */
		ptrtmp->next = NULL;			/* point value on 0x0 initially */
		ptrtmp->data = NULL;			/* no data yet, ptr on 0x0 for now */
	}
	return ptrtmp;						/* return list */
}

/* 0:false,1:true */
int
list_anfuegeelement( list *this, konto *elm ) {	/* add elm at end of list */
	list *lst = NULL;
	lst = (list*)malloc( sizeof(list) );

	if( lst != NULL ) {
		lst->next = NULL;
		lst->data = elm;
		while( this==NULL || this->next!=NULL )
			if( this == NULL ) {
				this = lst;
			} else {
				if ( this->next==NULL ) {
					this->next=lst;
				} else {
					this = this->next;
				}
			}
	}
	if ( elm != NULL && ( this == NULL || this->data == NULL ) ) {
		return 0;
	} else {
		return 1;
	}
}

/* 0:false,1:true */
int
list_anfuegen( list *this, list *elm ) {	/* add elm at end of list */
	while( this->next != NULL ){
		this = this->next;
	}
	this->next = elm;
	return 1;
}

/* NULL in case of empty list */
void
*list_element( list *this ){
	return this->data;
}

/* NULL in case of empty list */
void
*list_findeelement( list *this, konto *elm ){
	list *tmp = NULL;
	tmp = this;
	if(DEBUG_PRINT)printf("tmp:      %d\n", tmp != NULL);
	if(tmp != NULL){
		if(DEBUG_PRINT)printf("tmp-next: %d\n", tmp->next != NULL);
		if(DEBUG_PRINT)printf("tmp-data: %d\n", tmp->data != NULL);
	}
	while( tmp->next != NULL && tmp->data != elm ) {
		tmp = tmp->next;
	}
	return tmp->data;
}

/* NULL in case if empty list */
void
*list_naechsteselement( list *this ) {
	return this->next;
}

int
list_isempty( list *this ) {
	return ( this == NULL );
}

/* 0:false,1:true */
void
list_loescheelement( list *this, konto *elm ) {
	list *ptrtmp = this;
	void *tmp = NULL;
	tmp = (list*)malloc( sizeof(elm) );

	if( !list_isempty(ptrtmp) ) {

		while( ptrtmp->next != NULL && ptrtmp->next->data != elm ){
			ptrtmp = ptrtmp->next;
		}
		
		tmp = this->next->data;
		this->next->data = NULL;
		free(tmp);
	
	}
}

#endif // _LIST_CLASS_H
