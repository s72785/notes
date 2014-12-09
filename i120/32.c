#include <stdlib.h>
#include <stdio.h>

struct _list {
	int item;
	struct _list *next;
};
typedef struct _list list;

void push(list **l, int i){
	// neues Elm deklarieren
	list *neu = (list*) malloc(sizeof(list));
	// neues Elm initialisieren
	neu->item = i;
	//neu-next = NULL;
	// l als Nachfolger fuer neues Elm 
	neu->next = *l;
	// l auf neues Elm setzen
	*l=neu;
	// neues Elm loeschen
	//free(neu);
	//return 0;
}

int pop(list **l){
	int e;
	// handle Elm fuer erstes Elm von l
	list *el ;//= (list*) malloc(sizeof(list));
	el = *l;
	//new_el->next=NULL
	// i aus l auslesen
	e = el->item;
	// l auf nachfolger setzen -> 1. Elm ist geloescht
	*l = *l->next;
	//el->next=NULL;
	// Speicher befreien -> handle Elm loeschen
	//free(el);
	// i zurueckgeben
	return e;
}

int main() {
	// Zeiger auf den Anfang der Liste (initial leer)
	list *l;// = (list*) malloc(sizeof(list));
	l=NULL;
//	l->next = NULL;
	int i, e;
//i=1;
	for(i=1; i<=10; i++){
		e=i;
		push(&l, e);
		// l besteht jetzt aus einem Element, in dem 1 gespeichert ist
		printf("%d. Elm hinzugefuegt %d\n", i, l->item);
		// Element mit dem Wert 1 loeschen
		e=pop(&l);
		printf("%d. Elm entfernt\n", i, e);
	}
	// Liste wieder freigeben
	//free(l);
	return 0;
}
