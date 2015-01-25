#ifndef _BANK_CLASS_H
#define _BANK_CLASS_H

#include <stdio.h>
#include "myio.h"
#include "konto.class.h"

/* Bank hat BS_GROESSE-1 Konten
 * Konto 0-1000 ist die Bank selbst
 * Kundenkonten beginnen ab 1001, s. KUNDENKONTO_PRIM
 * */
// todo: redefine accounts as list
// bilanz
typedef struct bank_t {
	unsigned long long kontenzahl;//: KTO_LAENGE_BIT;
//	double kundenvermoegen;
	konto konten[BS_GROESSE];
	unsigned long long neuesterkunde;
} bank;

void
bank_kontoeroeffnen( bank *this ){
	unsigned long long nr = KUNDENKONTO_PRIM + this->kontenzahl++;
	this->konten[nr].ktonr = nr;	// determine account number
	this->konten[nr].sperrung = eroeffnet;
	this->konten[nr].guthaben = 0.0;
	this->konten[nr].pin=0;
	this->neuesterkunde = nr;
	konto_neuepin( &(this->konten[nr]) );
}

void
bank_init( bank *this, double kapital ) {
	this->kontenzahl = 0;
	this->neuesterkunde = KUNDENKONTO_PRIM-1;
	bank_kontoeroeffnen( this );
	this->konten[BARGELDKONTO].guthaben = kapital;
	this->konten[BARGELDKONTO].pin = 1928;
}

int
bank_ueberweisen( bank *this, int auszahlungskonto, int einzahlungskonto, double summe ) { /* rc: 0 - Zu geringes Guthaben, 1 - alles ok, 2 - ein Konto ist gesperrt, 3 gleiches Konto */
	if( auszahlungskonto == einzahlungskonto ) {
		return 3;
	}
	if( this->konten[auszahlungskonto].sperrung != eroeffnet || this->konten[einzahlungskonto].sperrung != eroeffnet ) {
		return 2;
	}
	if ( konto_auszahlung( &(this->konten[auszahlungskonto]), summe ) && konto_einzahlung( &(this->konten[einzahlungskonto]), summe ) ){	
		return 1;
	} else {
		return 0;
	}
}

#endif // _BANK_CLASS_H
