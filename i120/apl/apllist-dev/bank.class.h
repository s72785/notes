/* This APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014-2015  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _BANK_CLASS_H
# define _BANK_CLASS_H

#ifndef _STDIO_H
# include <stdio.h>
#endif
#ifndef	_MYIO_H
# include "myio.h"
#endif
#ifndef _KONTO_CLASS_H
# include "konto.class.h"
#endif

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
	long long kontenzahl;//: KTO_LAENGE_BIT;
//	double kundenvermoegen;
	konto konten[BS_GROESSE];
	unsigned long long neuesterkunde;
} bank;

void
bank_kontoeroeffnen( bank *this ){
	unsigned long long nr = KUNDENKONTO_PRIM + this->kontenzahl++;
	/* todo: neu adressieren */
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
	/* todo: neu adressieren */
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
