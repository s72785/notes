// external libs

#include <stdio.h>
#include <stdlib.h>

// definitions for preprocessor

#define PWD "0987"
#define BS_GROESSE 10000 //f. 4-stellige Kontonummern
#define PIN_LAENGE 4
//#define PIN_VERSUCHE 3
#define PIN_LAENGE_BIT 13
#define KTO_LAENGE 4
#define KTO_LAENGE_BIT 13
#define TERM_STRING "-0-\0"
#define DEBUG_PRINT 1	// debug-ausgabe kann abgeschalten werden
#define KUNDENKONTO_PRIM 1000
#define BARGELDKONTO 1000
#define WE "XBT" // Haupt-Waehrungseinheit definiert
#define GUTHABEN_MAX 21000000.0	// max. Guthaben d. we
#define GUTHABEN_MIN 1.0	// min. 1 we Guthaben
#define ZEIT_MENUEVERLASSEN 30 // in Sekunden

// experimental

/* //idee fflush als makro nachzubilden
#define Fflush(int_keyboard_buffer)\
	while(( (int_keyboard_buffer)=getchar() ) != '\n')
*/
//#define NACHKOMMA_MAX 8U //es gibt nur 8 Nachkomma-Stellen
/* //Uberweisungsgebuehren
#define UEBGEB_MINABS 0.1	//min x we
#define UEBGEB_MINREL 0.01	//min x/100 we
*/

/*
typedef struct {
	enum fehler_t {betrag, guthaben, gesperrt} nummer;
	char beschreibung[30];
} konto_fehler;

typedef struct {
	enum geschlecht_r {mann, frau, zwitter, geschlechtslos, unbekannt} geschlecht;
	char vorname[99];
	char nachname[99];
//	time geburtsdatum;
	char adresse[99];
	char stadt[50];
	char zip[10];
	char land[50];
} person;
*/

// general functions

#include "mystdlib.h"

// class konto (account)

#include "konto.class.h"

// class bank

#include "bank.class.h"

// menue functions

#include "bankmenue.h"

// main function

int main( void ) {
	bank schalterbank;
	bank_init( &schalterbank, 50000.0 );
	while( menue_hauptmenue( &schalterbank ) );	//infty-loop, its a "Bank-OS" after all
	return 0;
}
