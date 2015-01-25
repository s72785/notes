/* This APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014-2015  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _BANK_CLASS_H
#define _BANK_CLASS_H

#include <stdio.h>
#include "myio.h"
#include "konto.class.h"

/* Bank hat KTO_LAENGE-stellige Konten,
 * im 1. Teil waren's noch 10^KTO_LAENGE bei KTO_LAENGE=4
 * und damit BS_GROESSE-1 Konten wenn ohne 0
 * 
 * Konto 0-1000 ist die Bank selbst
 * Kundenkonten beginnen ab 1001, s. KUNDENKONTO_PRIM
 * */
// todo: redefine accounts as list
// bilanz
typedef struct bank_t {
	list *konten[BS_GROESSE]; // list*->data* = konto*
	unsigned long long neuesterkunde;
	unsigned long long kontenzahl;
} bank;

/*return*/
konto
*bank_kontoeroeffnen( bank *this ) {
	konto *kto = NULL;
	kto = malloc( sizeof(konto) );
	
	this->neuesterkunde++;
	this->kontenzahl++;

	kto->ktonr = this->neuesterkunde;
	kto->pin = 0;
	kto->guthaben = 0.0;
	kto->sperrung = eroeffnet;

	konto_neuepin( kto );
	return kto;
}

void
bank_init( bank *this, double kapital ) {
	konto *kto = NULL;
	int k = 0;
	
	if(DEBUG_PRINT)printf("%llu\n", (KUNDENKONTO_PRIM-1) );

	this->neuesterkunde = KUNDENKONTO_PRIM-1;
	this->kontenzahl = 0;
	
	for(k=0; k < (BS_GROESSE-1); k++) {
		this->konten[k] = list_erstellen();
	}
	
	kto = bank_kontoeroeffnen( this );
	kto->guthaben = kapital;
	kto->pin = 1928;
	
	list_anfuegeelement( this->konten[kontohash(BARGELDKONTO)], kto );
}

/* returns NULL if not found */
konto
*bank_findekonto( bank *this, unsigned long long kontonummer ) {
	list *ptrlst = NULL;
	konto *ptrkto = NULL;
	
	ptrlst = this->konten[kontohash( kontonummer )];
	
	while( ptrlst->next != NULL && ptrlst->next->data != NULL ) {
		ptrkto = ptrlst->data;
		if( ptrkto->ktonr == kontonummer ) {
			return ptrkto;
		}
	}
	
	return NULL;
}

int
bank_ueberweisen( bank *this, int auszahlungskonto, int einzahlungskonto, double summe ) { /* rc: 0 - Zu geringes Guthaben, 1 - alles ok, 2 - ein Konto ist gesperrt, 3 gleiches Konto */
	konto *ktoa, *ktoe;
	ktoa = bank_findekonto( this, auszahlungskonto );
	ktoe = bank_findekonto( this, einzahlungskonto );
	if( auszahlungskonto == einzahlungskonto ) {
		return 3;
	}
	if( ktoa->sperrung != eroeffnet || ktoe->sperrung != eroeffnet ) {
		return 2;
	}
	if ( konto_auszahlung( ktoa, summe ) && konto_einzahlung( ktoe, summe ) ){	
		return 1;
	} else {
		return 0;
	}
}

void
bank_kontoloeschen( bank *this, unsigned long long k ) {
	konto *kto = NULL;
	list *lst = NULL;
	
	lst = this->konten[kontohash( k )];
	kto = bank_findekonto( this, k );
	
	list_loescheelement( lst, kto );
}

#endif // _BANK_CLASS_H
