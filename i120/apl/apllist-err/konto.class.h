/* This APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014-2015  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _KONTO_CLASS_H
#define _KONTO_CLASS_H

#include "mystdlib.h"

typedef struct _konto {
	unsigned long long ktonr;//: KTO_LAENGE_BIT;	//n-stellig -> m bit
	int pin;//: PIN_LAENGE_BIT;
	double guthaben;
	enum sperrung_t { gesperrt, eroeffnet, pin1, pin2, pin3, geloescht, gekuendigt } sperrung;
//	double ueberziehungskredit;
//	time	letzterlogin;
//	person	kunde;
//	enum kontotyp_t {privatkonto, geschaeftskonto, firmenkonto} kontotyp;
//	int aktivetanliste;
//	services service;
//	enum waehrung_t { btc, eur, usd } waehrung;
	//struct _konto *naechster;	//pointer on next user in same slot (of the hashtable)
} konto;

int
kontohash( unsigned long long kontonummer ) {
	return hash( kontonummer, BS_GROESSE );
}

int
konto_einzahlung( konto *this, double summe ) { /* rc: 1 - alles ok, 0 - Grenze ueberschritten */
	if( (this->guthaben + summe) <= GUTHABEN_MAX ) {
		this->guthaben += summe;
		return 1;
	}
	return 0;
}

int
konto_auszahlung( konto *this, double summe ) { /* rc: 1 - alles ok, 0 - Grenze unterschritten */
	if( (this->guthaben - summe) >= GUTHABEN_MIN ) {
		this->guthaben -= summe;
		return 1;
	}
	return 0;
}

/* bonus function, not necessary for the enlisted tasks... */
int 
konto_checkpin( int z ) { /* 1 - no error, 0 - unwanted input */
	if( z == 0) return 0;
	if( z == 123) return 0;
	if( z == 1234) return 0;
	if( z == 2345) return 0;
	if( z == 3456) return 0;
	if( z == 4567) return 0;
	if( z == 5678) return 0;
	if( z == 6789) return 0;
	if( z == 7890) return 0;
	if( z == 8901) return 0;
	if( z == 9012) return 0;
	if( z == 1111) return 0;
	if( z == 2222) return 0;
	if( z == 3333) return 0;
	if( z == 4444) return 0;
	if( z == 5555) return 0;
	if( z == 6666) return 0;
	if( z == 7777) return 0;
	if( z == 8888) return 0;
	if( z == 9999) return 0;
	if( z == 4321) return 0;
	if( z == 3210) return 0;
	if( z == 2109) return 0;
	if( z == 1098) return 0;
	if( z == 987) return 0;
	if( z == 9876) return 0;
	if( z == 8765) return 0;
	if( z == 7654) return 0;
	if( z == 6543) return 0;
	if( z == 5432) return 0;
	return 1;
	/*
	if(chkZahl(s[])!=0) {//Zahl?!
		return 1;
	}
	*/
	//todo: checke algorithmisch auf triviale pins (
	//alles zahlen? -> enforced with input implementation
	// ciphers max two times
	int n[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	int i,p;
	for( i=0; i < 4; i++ ) {
		p=0; //todo: number in postion i
		if (n[p] == 0) {
			return 0;
		} else {
			n[p]--;
		}
	}
	//todo: nicht 3 aufeinander folgende)
	return 1;
}

void
konto_neuepin( konto *this ) {
	this->pin=0;
	while( !(konto_checkpin(this->pin)) ) {
		this->pin = intZufallszahl(PIN_LAENGE); // generate new(!) PIN 
	}
}

/* returns NULL on fail or an account on success */
konto
*konto_eroeffnen( int nummer ) {
	konto *this = NULL;
	this = (konto*)malloc( sizeof(konto) );
	if( this != NULL ) {
		this->ktonr = nummer;	// determine account number
		this->sperrung = eroeffnet;
		this->guthaben = 0.0;
		konto_neuepin( this );
	}
	return this;
}

void
konto_pinaendern( konto *this, int npin ) {
	this->pin = npin;
}

#endif // _KONTO_CLASS_H
