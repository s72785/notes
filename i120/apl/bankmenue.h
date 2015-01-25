/* This APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014-2015  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _BANKMENUE_H
#define _BANKMENUE_H

#include <stdio.h>
#include <math.h>
#include "myio.h"
#include "konto.class.h"

void
menue_cls() {
	int i;
	for( i = 0; i < 80; i++ ) {
		printf("\f");
	}
}

void
menue_bankstatus( bank *this ) {
	konto *kto = NULL;
	kto = bank_findekonto( this, BARGELDKONTO );
	if( kto != NULL ) {
		printf("Bar-Guthaben: %17.8f %s\n", kto->guthaben, WE);
		printf("Konten:          %010llu\n", this->kontenzahl);
		printf("Neuester Kunde:  %010llu\n\n\n", this->neuesterkunde);
	} else {
		printf("Kein Konto:      %010llu\n\n\n", (unsigned long long)BARGELDKONTO);
	}
}

void
menue_kontostatus( konto *this ) {
	printf("\nKonto:        %010llu", this->ktonr);
	printf("\nStatus:       %d", this->sperrung);
	//~ switch(){
	//~ }
	printf("\nGuthaben: %17.8f %s", this->guthaben, WE);
	printf("\nPIN:          %04d\n\n\n", this->pin);
}

int
menue_eingabepin( int laenge ) {
	if(DEBUG_PRINT)printf("Laenge der Eingabe %d\n", laenge);
	return myeingabeganzzahl( laenge, (int)'*', 0, 1, "PIN (4 Stellen):           " ); /* ask for PIN, same as for account number */
}

unsigned long long
menue_eingabekontonummer( int laenge ) { /* ask for account number, do not accept anything but numbers and just KTO_LAENGE of them */
	if(DEBUG_PRINT)printf("Laenge der Eingabe %d\n", laenge);
	return myeingabeganzzahl( laenge, 1, 0, 1, "Kundennummer (10 Stellen): " );
}

int
menue_bestaetigen(){
	return askyesno("(1) Ja\n(0) Nein\n\nEntscheidung: ");
}

int
menue_programmbeenden() {
	int pass;

	menue_cls();
	printf("\n\n\n\nSie sind im Begriff das Programm zu beenden!");
	printf("\nDie Kundendaten werden hierbei geloescht.");
	printf("\n\nPasswort: ");

	pass = myinputint( 4, (int)'*', 0, 1 );

	if( pass == PWD && menue_bestaetigen() ) {
		return 0;
	}
	return 1;
}

void
menue_pineditieren( konto *this ) { //for not leaking which entry was wrong, the user has to enter all three every time again
	int pin0, pin1, pin2;

		menue_cls();
		pin1 = 0;
		pin2 = 0;
		printf("\nAlte PIN\n");
		pin0 = menue_eingabepin( PIN_LAENGE );
		printf("\nNeue PIN\n");
		pin1 = menue_eingabepin( PIN_LAENGE );
		printf("Bitte Wiederholen\n");
		pin2 = menue_eingabepin( PIN_LAENGE );
		if( this->pin != pin0 || pin0 == pin1 || pin1 != pin2 || konto_checkpin(pin1)!=1 ) {
			printf("Ungueltige Eingabe oder Neue PIN zu einfach!!\n");
		} else {
			this->pin = pin2;
			printf("\nPIN neu festgelegt!\n");
		}
}

void
menue_zeigekontodaten( konto *this ) {
	menue_cls();
	if( this != NULL ) {
		printf("\nKonto-/Kunden-Nummer: %010llu\n", this->ktonr); //lessons learned: k leadin zeros in decimal with %0kd
		printf("Ihre PIN:             %04d\n", this->pin);
		printf("Ihr Kontostand:       %17.8f %s\n", this->guthaben, WE);
	} else {
		printf("Das Konto kann nicht angezeigt werden oder existiert nicht. ");
	}
	
}

//todo: input for float, general implementation
/*double myfloatinput(char delim, char* ignore) {
	double float = 0.0;


	return f;
}*/

double
menue_eingabebetrag( double maximalbetrag ) {
	int loop = 1;
	int i;
	char c='\0';
	int kpos = 0;
	double betrag=0.0;

	while( loop && ( betrag <= 0.0 || betrag > maximalbetrag ) ){
		printf("Betrag (0%c00): ", BETRAG_DELIMETER);

		i = 0;
		while ( c != '\n' && loop ){
			c=waitfloatkbhit( kpos, BETRAG_DELIMETER, 1, 0 );
			if( c == BETRAG_DELIMETER ) { kpos = i; }
			if( c == '\n' || ( kpos == 0 && (i >= ( STELLEN_VKOMMA - 1 )) ) || ( kpos!=0 && ((i - kpos) >= STELLEN_NKOMMA) )) { loop = 0; }
			betrag = ( (kpos == 0 && isnumchar(c) )? 10.0*betrag + (double)char2int(c) : (( isnumchar(c) )? betrag + pow( 10, kpos - i ) * (double)char2int(c) : betrag ) );
			if(DEBUG_PRINT)printf("\n# %02d %02d %02d %02d %17.8f \t", c, c, i, kpos, betrag);
			if( c != '\n' ) { printf("%c", c); }
			i++;
		}
		printf("\n");

		if( loop==0 ) {
			if(DEBUG_PRINT)printf("# Betragseingabe beendet %17.8f\n", betrag);
		}
	}
	
	return betrag;
}

void
menue_einzahlen( konto *this ) {
	int antwort=0;
	double betrag=0.0;
	
	printf( "Einzahlen auf das Konto %010llu\n\n", this->ktonr );
	printf( "Geben Sie den Einzahlungsbetrag an!\n\n" );
	betrag = menue_eingabebetrag( this->guthaben );
	/* prüfung kann vernachlässig werden, weil eingabe das bereits erledigt */
	printf( "\nSoll die Transaktion ausgefuehrt werden?\n\n" );
	antwort = menue_bestaetigen();
	if(DEBUG_PRINT)printf( "\n# Konto %010llu Betrag %17.8f Rueckgabe %i\n\n", this->ktonr, betrag, antwort );
	if(antwort != 0) {
		if ( konto_einzahlung( this, betrag ) ) {
			printf( "\nEinzahlung ausgefuehrt\n" );
		} else {
			printf( "\nDiese Transaktion konnte mit den angegeben Konto nicht durchgefuehrt werden!\n" );
		}
	} else {
		printf( "\nEinzahlung nicht ausgefuehrt\n" );
	}
}

void
menue_auszahlen( konto *this ) {
	int antwort=0;
	double betrag=0.0;
	
	printf( "Auszahlen vom Konto %010llu\n\n", this->ktonr );
	printf( "Geben Sie den Auszahlungsbetrag an!\n\n" );
	betrag = menue_eingabebetrag( this->guthaben );
	/* prüfung kann vernachlässig werden, weil eingabe das bereits erledigt */
	printf( "\nSoll die Transaktion ausgefuehrt werden?\n\n" );
	antwort=menue_bestaetigen();
	if(antwort == 1) {
		if( konto_auszahlung( this, betrag ) ) {
			printf( "\nAuszahlung ausgefuehrt!\n" );
		} else {
			printf( "\nZu geringes Guthaben fuer diese Transaktion!\n" );
		}
	} else {
		printf( "\nAuszahlung nicht ausgefuehrt!\n" );
	}
}

void
menue_ueberweisen( bank *this, unsigned long long akonto ) {
	unsigned long long ekonto = 1000;
	int antwort = 0;
	double betrag = 0.0;
	konto *ptrktoa, *ptrktoe;
	
	printf( "Ueberweisung von Kontonummer %010llu\n\n", akonto );
	ekonto = menue_eingabekontonummer( KTO_LAENGE );
	ptrktoa = bank_findekonto( this, akonto );
	ptrktoe = bank_findekonto( this, ekonto );
	betrag = menue_eingabebetrag( ptrktoa->guthaben );
	printf( "\nSoll die Transaktion ausgefuehrt werden?\n\n" );
	antwort = menue_bestaetigen();
	if(antwort == 1) {
		if(DEBUG_PRINT)printf("\n# %17.8f %s %17.8f %s\n", ptrktoa->guthaben, WE, ptrktoe->guthaben, WE );
		switch( bank_ueberweisen( this, akonto, ekonto, betrag ) ){
			case 1:
				printf( "\nUeberweisung ausgefuehrt!\n" );
				if(DEBUG_PRINT)printf("\n# von %010llu an %010llu\n# von %17.8f %s an %17.8f %s\n", akonto, ekonto, ptrktoa->guthaben, WE, ptrktoe->guthaben, WE );
				break;
			case 0:
				printf( "\nZu geringes Guthaben fuer diese Transaktion!\n" );
				break;
			default:
				printf( "\nDiese Transaktion konnte mit dem angegeben Konto nicht durchgefuehrt werden!\n" );
				break;
		}
	} else {
		printf( "\nUeberweisung nicht ausgefuehrt!\n" );
	}
}

void
menue_kontoloeschen( bank *this, unsigned long long k) {
	konto *kto = NULL;
	kto = bank_findekonto( this, k );
	int pin = 0;

	menue_cls();
	printf("\n\n\n\nSie sind im Begriff das Konto %010llu zu loeschen!", kto->ktonr );
	printf("\nDas Guthaben von %17.8f geht dabei verloren!", kto->guthaben );
	printf("\n\nPasswort: ");

	pin = menue_eingabepin( PIN_LAENGE );

	if( pin == kto->pin && menue_bestaetigen() ) {
		bank_kontoloeschen( this, k );
		printf("\n\nDas Konto wurde erfolgreich geloescht!");
	} else {
		printf("\n\nDas Konto wurde nicht geloescht!");
	}
}

/* bank, kontonummer */
void
menue_kundenkonto( bank *this, unsigned long long k ) {
	char antwort;
	int rc = 1;
	konto *kto = NULL;
	
	kto = bank_findekonto( this, k );

	while( rc ) {
		antwort = '\0';
		menue_cls();
		printf("\n\n\n\nKundenkonto %010llu\n\n", k);
	
		printf("(1) Guthaben anzeigen\n");
		printf("(2) Einzahlung\n");
		printf("(3) Auszahlung\n");
		printf("(4) Ueberweisung (Bank-intern)\n");
		printf("(5) PIN aendern\n");
		printf("(6) PIN festlegen\n");
		printf("(7) Konto stilllegen\n");
		printf("(0) Abmelden\n");
	
		printf("\n\nAuswahl: ");
		while ( !( char2int(antwort) >= 0 && char2int(antwort) <= 6) ) {
			antwort=waitkbhit();
		}
		printf("%c\n", antwort);
	
		menue_cls();
		switch ( antwort ) {
			case '1':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Guthaben anzeigen\n");
				printf("Guthaben auf dem Konto %010llu\n\n\n", kto->ktonr);
				printf("Guthaben: %16.8f %s", kto->guthaben, WE);
				break;
			case '2':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Einzahlung\n");
				menue_einzahlen( kto );
				break;
			case '3':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Auszahlung\n");
				menue_auszahlen( kto );
				break;
			case '4':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Ueberweisung\n");
				menue_ueberweisen(  this, k );
				break;
			case '5':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: PIN aendern\n");
				konto_neuepin( kto ); //einfach aendern
				menue_zeigekontodaten( kto ); //und anzeigen
				break;
			case '6':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: PIN festlegen\n");
				menue_pineditieren( kto ); //einfach aendern
				break;
			case '7':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Konto stilllegen\n");
				menue_kontoloeschen( this, k );
				break;
			case '0':
				rc=0;
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Abmelden\n");
				break;
		}
		antwort='0';
		mypause("\n\nWeiter mit Enter ...\n");
	}
}

int
menue_kundenlogin( bank *this ) {
	int loop = 1;	//true for continuing "bank os"
	unsigned long long kontonr = 0;
	konto *k = NULL;
	int pin = 0;

	while( loop ) {
		menue_cls();
		printf("\n\n\n\nKundenlogin\n\n");

	    kontonr = menue_eingabekontonummer( KTO_LAENGE );		
		pin = menue_eingabepin( PIN_LAENGE );
		k = bank_findekonto( this, kontonr );

		if( kontonr < KUNDENKONTO_PRIM
			|| k->sperrung == gesperrt
		) { // unknown data, exit func
			printf("Ungueltige Kontodaten!\n\n");

			if(DEBUG_PRINT)printf("# KtoNr:    %010llu\n", k->ktonr);
			if(DEBUG_PRINT)printf("# Sperrung: %d\n", k->sperrung);
			if(DEBUG_PRINT)printf("# Guthaben: %17.8f %s\n", k->guthaben, WE);
			if(DEBUG_PRINT)printf("# PIN:      %d\n", k->pin);
			mypause("\nWeiter mit Enter ...\n");
			loop=0;
			break;
		}

		if( k->sperrung == pin3 ) { // test on account status
			if(DEBUG_PRINT)printf("# Dieses Konto ist gesperrt!\nBitte nehmen Sie Kontakt zum Service auf.\n\n");
			mypause("\n\nWeiter mit Enter ...\n");
			loop=0;
			break;
		}

		if( k->pin != pin ) { //+ Pruefung PIN
			menue_cls();
			if(DEBUG_PRINT)printf("# PIN!!! %04d %04d %04d\n", k->pin, pin, pin==k->pin);
			switch( k->sperrung ) {
				case eroeffnet:
					k->sperrung=pin1;
					printf("PIN-Fehlversuch 1/3!\n\n");
					break;
				case pin1:
					k->sperrung=pin2;
					printf("PIN-Fehlversuch 2/3!\n\n");
					break;
				case pin2:
					k->sperrung=pin3;
					printf("PIN-Fehlversuch 3/3!\n\n");
					break;
				default:
					break;
			}
			mypause("\n\nWeiter mit Enter ...\n");
			kontonr = 0;
		}else{
			k->sperrung=eroeffnet;
			menue_kundenkonto( this, kontonr );
			loop = 0;
		}
	}

	return loop;
}

int
menue_hauptmenue( bank *this ) {
	int rc=1; // true for continuing "bank os"
	char antwort = '\0';
	konto *kto = NULL;

	menue_cls();
	if(DEBUG_PRINT)printf("# DEBUG Modus ist aktiv!\n\n");

	printf("1. Semester Wirtschaftsinformatik, WS 2014/2015\n\tbei Prof. B. Hollas\n\tan der HTW Dresden\nProgrammierung 1, APL\n\tTeil 1 bis 16.12.2014\n\tTeil 2 bis 26.01.2015\nAutor:\t<s72785>\n\tunter General Public License Version 3\n\nThema: Ein interaktives Banksystem\n");
//~ 
//~ exit(0);
//~ 
	unsigned long long i;
	if(DEBUG_PRINT) { 
		printf("\n\n# Konten der Bank: %llu\n", this->kontenzahl);
		for(i=0 ; i < this->kontenzahl; i++) {
			kto = bank_findekonto( this, (KUNDENKONTO_PRIM+i) );
			
			if ( kto != NULL ) {
				printf("# Konto %llu", (kto->ktonr) );
				printf("# Konto %010llu", kto->ktonr );
				printf("hat %17.8f ", kto->guthaben );
				printf("%s Guthaben", WE );
				printf(", PIN %04d \n", kto->pin );
			}
		}
	}

	printf("\n\n");
	printf("  (1) Bestandskunde anmelden\n");
	printf("  (2) Neukunde anlegen\n");
	if(DEBUG_PRINT)printf("# (3) Programm beenden\n");
	if(DEBUG_PRINT)printf("# (4) Bankstatus\n");
	printf("\n\nAuswahl: ");

	while ( !( char2int(antwort)>=1 && char2int(antwort)<=4 ) ) {
		antwort=waitkbhit();
	}
	printf("%c\n", antwort);

	switch ( antwort ) {
		case '1':
			if(DEBUG_PRINT)printf("\n# Aufruf: Kundenlogin\n");
			menue_kundenlogin( this );
			break;
		case '2':
			if(DEBUG_PRINT)printf("\n# Aufruf: Neukunde\n");
			bank_kontoeroeffnen( this );
			kto = bank_findekonto( this, (this->neuesterkunde) );
			menue_zeigekontodaten( kto );
			mypause("\n\nWeiter mit Enter ...\n");
			break;
		case '3':
			if(DEBUG_PRINT)printf("\n# Aufruf: Programm beenden\n");
			rc = menue_programmbeenden();
			break;
		case '4':
			if ( DEBUG_PRINT >= 1 ) {
				menue_cls();
				printf("Bank Status\n\n");
				menue_bankstatus( this );
				mypause("\n\nWeiter mit Enter ...\n");
			}
			break;
	}

	return rc;
}


#endif //_BANKMENUE_H
