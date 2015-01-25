#ifndef _LIST_CLASS_H
#define _LIST_CLASS_H

#include <stdio.h>

//typedef struct _elm {	/*  */
//} elem ;	/* no dada type listnelm */

typedef struct _lst {
	struct _lst *next;
	void *data;
} list;

list
*list_erstellen( void ) {
	list *ptrtmp = NULL;				/* decl. new list, init. with ptr on 0x0 for comparison */
	ptrtmp = malloc( sizeof(list) );	/* reserve memory on heap */
	if( ptrtmp != NULL ) {				/* malloc succeeded if ptr is not NULL */
		ptrtmp->next = NULL;			/* point value on 0x0 initially */
		ptrtmp->data = NULL;			/* no data yet, ptr on 0x0 for now */
	}
	return ptrtmp;						/* return list */
}

/* NULL in case of empty list */
void
*list_element( list *this ){
	return this->data;
}

/* NULL in case of empty list */
void
*list_findeelement( list *this, void *elm ){
	list *tmp = NULL;
	tmp = this;
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

/* 0:false,1:true */
int
list_anfuegeelement( list *this, void *elm ) {	/* add elm at end of list */
	list *lst = NULL;
	lst = malloc( sizeof(list) );

	if( lst != NULL ) {
		lst->next = NULL;
		lst->data = elm;
		while( this==NULL || this->next!=NULL )
			if(this == NULL) {
				this=lst;
			} else {
				if ( this->next==NULL ) {
					this->next=lst;
				} else {
					this = this->next;
				}
			}
	}
	if ( elm != NULL && (this == NULL || this->data == NULL ) ) {
		return 0;
	} else {
		return 1;
	}
}

int
list_isempty( list *this ) {
	return ( this == NULL );
}

/* 0:false,1:true */
void
list_loescheelement( list *this, void *elm ) {
	list *ptrtmp = this;
	void *tmp = NULL;
	tmp = malloc( sizeof(elm) );

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
