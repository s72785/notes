#ifndef _BANKMENUE_H
# define _BANKMENUE_H

#ifndef _STDIO_H
# include <stdio.h>
#endif
#ifndef	_MYIO_H
# include "myio.h"
#endif
#ifndef _KONTO_CLASS_H
# include "konto.class.h"
#endif

void
menue_cls() {
	int i;
	for( i=0; i<80; i++ ) {
		printf("\n");
	}
}

void
menue_bankstatus( bank *this ) {
	printf("Bar-Guthaben: %17.8f\n",this->konten[BARGELDKONTO].guthaben);
	printf("Konten:          %04d\n",this->kontenzahl);
	printf("Neuester Kunde:  %d\n\n\n",this->neuesterkunde);
}

void
menue_kontostatus( konto *this ) {
	printf("Konto:        %04d\n", this->ktonr);
	printf("Status:       %d\n", this->sperrung);
	printf("Guthaben: %17.8f\n", this->guthaben);
	printf("PIN:          %04d\n\n\n", this->pin);
}

int
menue_bestaetigen(){
	char a = '9';

	printf("(1) Ja\n(0) Nein\n\nEntscheidung: ");

	while(!( isboolint( char2int( a ) ) )) {
		a = waitnumkbhit();
	}
	if(DEBUG_PRINT)printf( "\n# Antwort: %d %x \t", a, a );
	printf("%c\n", a);

	return char2int( a );
}

int
menue_programmbeenden() {
	int pass;

	menue_cls();
	printf("\n\n\n\nSie sind im Begriff das Programm zu beenden!");
	printf("\nDie Kundendaten werden hierbei gelöscht.");
	printf("\n\nPasswort: ");

	pass = myinputint( 4, (int)'*' );

	if( pass != PWD ) {
		return 1;
	}
	return !(menue_bestaetigen());
}
/**/

void
menue_pineditieren( konto *this ) {
	int pin0=0;	//for not leaking which entry was wrong, the user has to enter all three every time again
	int pin1=0;
	int pin2=0;
	int loop=1;

	while( loop ) {
		pin1 = 0;
		pin2 = 0;
		menue_cls();
		printf("\nAlte PIN\n");
		pin0 = menue_eingabepin( PIN_LAENGE );
		printf("\nNeue PIN\n");
		pin1 = menue_eingabepin( PIN_LAENGE );
		printf("Bitte Wiederholen\n");
		pin2 = menue_eingabepin( PIN_LAENGE );
		if(
			this->pin != pin0
			|| pin0 == pin1
			|| pin1 != pin2
			|| konto_checkpin(pin1)!=1
		) {
			printf("Ungueltige Eingabe oder Neue PIN zu einfach!!\n");
			mypause("\n\nWeiter ...\n");
		} else {
			this->pin = pin2;
			printf("\nPIN neu festgelegt!\n");
			loop = 0;
		}
	}
}

void
menue_zeigekontodaten( konto *this ) {
	menue_cls();
	//todo: put number of positions from pp macro in format-string
	printf("\n");
	printf("Konto-/Kunden-Nummer: ");
	//lessons learned: k leadin zeros in decimal with %0kd
	printf("%04d\n", this->ktonr);
	printf("Ihre PIN:             %04d\n", this->pin);
	printf("Ihr Kontostand:       %13.8lf %s\n", this->guthaben, WE);
}

/* ask for account number, do not accept anything but numbers and just KTO_LAENGE of them */
int
menue_eingabekontonummer( int laenge ) {
	printf("Kundennummer (####): ");
		
	return myinputint( laenge, 1 );
}

/* ask for PIN, same as for account number */
int
menue_eingabepin( int laenge ) {
	printf("PIN (####):          ");

	return myinputint( laenge, (int)'*' );
}

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
		while (
			c != '\n'
			&& loop
		){
			c=waitfloatkbhit( kpos, BETRAG_DELIMETER );
			if( c == BETRAG_DELIMETER ) {
				kpos=i;
			}
			if( c == '\n' ) {
				loop = 0;
				break;
			}
			if( kpos==0 && (i >= STELLEN_VKOMMA) ){
				loop = 0;
			}
			if( kpos!=0 && ((i - kpos) >= STELLEN_NKOMMA) ){
				loop = 0;
			}
			if( kpos == 0 ){
				betrag = 10.0*betrag + (double)char2int(c);
			} else if( isnumchar(c) ) {
				betrag = betrag + pow( 10, kpos - i ) * (double)char2int(c);
			}
			//BETRAG_NKOMMA
			//pin += char2int(c) * (int)pow( 10, laenge-i-1 );
			if(DEBUG_PRINT)printf("\n# %02d %02d %02d %02d %17.8f \t", c, c, i, kpos, betrag);
			printf("%c", c);
			i++;
		}
		printf("\n");
		if( loop==0 ) {
			if(DEBUG_PRINT)printf("# Betragseingabe beendet\n");
		}
	}
	
	return betrag;
}

/*
int strtoint(char *s, l) {
	int i;
	for(i=l; i>0; i--) {
	}
}*/

void
menue_einzahlen( konto *this ) {
	int antwort=0;
	double betrag=0.0;
	
	printf( "Einzahlen auf das Konto %04d\n\n", this->ktonr );
	printf( "Geben Sie den Einzahlungsbetrag an!\n\n" );
	betrag = menue_eingabebetrag( this->guthaben );
	printf( "\nSoll die Transaktion ausgefuehrt werden?\n\n" );
	antwort=menue_bestaetigen();
	if(antwort == 1) {
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
	
	printf( "Auszahlen vom Konto %04d\n\n", this->ktonr );
	printf( "Geben Sie den Auszahlungsbetrag an!\n\n" );
	betrag = menue_eingabebetrag( this->guthaben );
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
menue_ueberweisen( bank *this, int akonto ) {
	int ekonto = 1000;
	int antwort=0;
	double betrag = 0.0;
	
	printf( "Ueberweisung vom Konto %04d\n\n", akonto );
	ekonto = menue_eingabekontonummer( KTO_LAENGE );
	betrag = menue_eingabebetrag( this->konten[akonto].guthaben );
	printf( "\nSoll die Transaktion ausgefuehrt werden?\n\n" );
	antwort=menue_bestaetigen();
	if(antwort == 1) {
		if(DEBUG_PRINT)printf("\n# %f %f\n", this->konten[akonto].guthaben, this->konten[ekonto]);
		switch( bank_ueberweisen( this, akonto, ekonto, betrag ) ){
			case 1:
				printf( "\nUeberweisung ausgefuehrt!\n" );
				if(DEBUG_PRINT)printf("\n# %f %f\n", this->konten[akonto].guthaben, this->konten[ekonto].guthaben );
				break;
			case 0:
				printf( "\nZu geringes Guthaben fuer diese Transaktion!\n" );
				break;
			case 2:
				printf( "\nDiese Transaktion konnte mit dem angegeben Konto nicht durchgefuehrt werden!\n" );
				break;
		}
	} else {
		printf( "\nUeberweisung nicht ausgefuehrt!\n" );
	}
}

void
menue_kundenkonto( bank *this, int k ) { //ToDo
	char antwort;
	int rc=1;

	while( rc ) {
		antwort = '\0';
		menue_cls();
		printf("\n\n\n\nKundenkonto %04d\n\n", k);
	
		printf("(1) Guthaben anzeigen\n");
		printf("(2) Einzahlung\n");
		printf("(3) Auszahlung\n");
		printf("(4) Ueberweisung (Bank-intern)\n");
		printf("(5) PIN aendern\n");
		printf("(6) PIN festlegen\n");
		printf("(0) Abmelden\n");
	
		printf("\n\nAuswahl: ");
		while (
			antwort != '1'
			&& antwort != '2'
			&& antwort != '3'
			&& antwort != '4'
			&& antwort != '5'
			&& antwort != '6'
			&& antwort != '0'
		) {
			antwort=waitkbhit();
		}
		printf("%c\n", antwort);
	
		menue_cls();
		switch ( antwort ) {
			case '1':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Guthaben anzeigen\n");
				printf("Guthaben auf dem Konto %04d\n\n\nGuthaben: %16.8f %s", this->konten[k].ktonr, this->konten[k].guthaben, WE);
				break;
			case '2':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Einzahlung\n");
				menue_einzahlen( &(this->konten[k]) );
				break;
			case '3':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Auszahlung\n");
				menue_auszahlen( &(this->konten[k]) );
				break;
			case '4':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Ueberweisung\n");
				menue_ueberweisen(  this, k );
				break;
			case '5':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: PIN aendern\n");
				konto_neuepin( &(this->konten[k]) ); //einfach aendern
				menue_zeigekontodaten( &(this->konten[k]) ); //und anzeigen
				break;
			case '6':
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: PIN festlegen\n");
				menue_pineditieren( &(this->konten[k]) ); //einfach aendern
				break;
			case '0':
				rc=0;
				if(DEBUG_PRINT == 2)printf("\n# Aufruf: Abmelden\n");
				break;
		}
		antwort='0';
		mypause("\n\nWeiter ...\n");
	}
}

int
menue_kundenlogin( bank *this ) { //ToDo
	int loop=1;	//true for continuing "bank os"
	int rc=1;
	int kontonr=0;
	int pin=0;
	int i;
	char c;
	char *s[4];

	while( loop ) {
		menue_cls();
		printf("\n\n\n\nKundenlogin\n\n");

	    kontonr = menue_eingabekontonummer( KTO_LAENGE );
		
		pin = menue_eingabepin( PIN_LAENGE );

		//mypause("\n\nWeiter ...\n");

		// unknown data, exit func
		// pin 0000 == 0 theoretically possible
		if( kontonr < KUNDENKONTO_PRIM || this->konten[kontonr].sperrung == gesperrt ) {
			printf("Ungueltige Kontodaten!\n\n");
			if(DEBUG_PRINT)printf("# KtoNr:    %d\n", this->konten[kontonr].ktonr);
			if(DEBUG_PRINT)printf("# Sperrung: %d\n", this->konten[kontonr].sperrung);
			if(DEBUG_PRINT)printf("# Guthaben: %d %s\n", this->konten[kontonr].guthaben, WE);
			if(DEBUG_PRINT)printf("# PIN:      %d\n", this->konten[kontonr].pin);
			mypause("\nWeiter ...\n");
			loop=0;
			break;
		}

		// test on account status
		if(this->konten[kontonr].sperrung == pin3) {
			if(DEBUG_PRINT)printf("# Dieses Konto ist gesperrt!\nBitte nehmen Sie Kontakt zum Service auf.\n\n");
			mypause("\n\nWeiter ...\n");
			loop=0;
			break;
		}

		//+ Prüfung PIN
		if(this->konten[kontonr].pin != pin) {
			menue_cls();
			if(DEBUG_PRINT)printf("# PIN!!! %d %d\n", this->konten[kontonr].pin, pin, pin==this->konten[kontonr].pin);
			switch(this->konten[kontonr].sperrung) {
				case eroeffnet:
					this->konten[kontonr].sperrung=pin1;
					printf("PIN-Fehlversuch 1/3!\n\n");
					break;
				case pin1:
					this->konten[kontonr].sperrung=pin2;
					printf("PIN-Fehlversuch 2/3!\n\n");
					break;
				case pin2:
					this->konten[kontonr].sperrung=pin3;
					printf("PIN-Fehlversuch 3/3!\n\n");
					break;
				case pin3:
					break;
			}
			mypause("\n\nWeiter ...\n");
			kontonr=0;
		}else{
			this->konten[kontonr].sperrung=eroeffnet;
			menue_kundenkonto(this, kontonr);
			loop=0;
		}


		//+ Prüfung counter<3
		//  - true:Kontoübersicht
		//  - false:counter erhöhen
	
		
	}

	return loop;
}

int
menue_hauptmenue( bank *this ) {
	int rc=1; // true for continuing "bank os"
	char antwort = '\0';
	int i;
	
	menue_cls();
	if(DEBUG_PRINT)printf("# DEBUG Modus ist aktiv!\n\n");
	printf("APL Programmierung 1, 1. Semester Wirtschaftsinformatik, WS/2014\n\tbei Prof. B. Hollas\t\tAutor: <s72785>\n\nEin interaktives Banksystem\n");
	if(DEBUG_PRINT)printf("\n\n# Konten der Bank: %d\n", this->kontenzahl);
	/* wondering: how to put together a format string? */
	if(DEBUG_PRINT) { 
		for(i=0 ; i < this->kontenzahl; i++) {
			printf("# Konto %04d hat %17.8lf %s Guthaben, PIN %04d \n",(KUNDENKONTO_PRIM+i), this->konten[KUNDENKONTO_PRIM+i].guthaben, WE, this->konten[KUNDENKONTO_PRIM+i].pin);
		}
	}
	printf("\n\n");
	printf("  (1) Bestandskunde anmelden\n");
	printf("  (2) Neukunde anlegen\n");
	if(DEBUG_PRINT)printf("# (3) Programm beenden\n");
	if(DEBUG_PRINT)printf("# (4) Bankstatus\n");

	printf("\n\nAuswahl: ");
	while (
		antwort != '1'
		&& antwort != '2'
		&& antwort != '3'
		&& (antwort != '4' )
	) {
		antwort=waitkbhit();
	}
	printf("%c\n", antwort);

	switch ( antwort ) {
		case '1':
			if(DEBUG_PRINT)printf("\n# Aufruf: Kundenlogin\n");
			menue_kundenlogin(this);
			break;
		case '2':
			if(DEBUG_PRINT)printf("\n# Aufruf: Neukunde\n");
			bank_kontoeroeffnen( this );
			menue_zeigekontodaten( &(this->konten[this->neuesterkunde]) );
			mypause("\n\nWeiter ...\n");
			break;
		case '3':
			if(DEBUG_PRINT)printf("\n# Aufruf: Programm beenden\n");
			rc = menue_programmbeenden();
			break;
		case '4':
			if ( DEBUG_PRINT >= 1 ) {
				menue_cls();
				printf("Bank Status\n\n", antwort);
				menue_bankstatus(this);
				mypause("\n\nWeiter ...\n");
			}
			break;
	}

	return rc;
}

#endif //_BANKMENUE_H
