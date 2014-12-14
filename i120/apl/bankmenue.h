#ifndef _STDIO_H
# include <stdio.h>
#endif
#ifndef	_MYIO_H
# include "myio.h"
#endif

void menue_cls() {
	int i;
	for( i=0; i<80; i++ ) {
		printf("\n");
	}
}

int menue_programmbeenden() {
	int antwort=1;
	char pass[4];

	menue_cls();
	printf("\n\n\n\nSie sind im Begriff das Programm zu beenden!");
	printf("\nDie Kundendaten werden hierbei gelöscht.");
	printf("\n\nPasswort: ");
	scanf("%4s", &pass);
	cleartoendofline();

	if(!strcmp(pass, PWD)) {
		printf("\nProgramm wird beendet!\n");
		return 0;
	}else{
		printf("(1) Ja, Programm beenden und alle Kundenfaten verlieren");
		printf("(2) Nein, auf keinen Fall");
		switch (antwort) {
			case '1':
			case 'J':
			case 'j': antwort=1;
			break;
			case '2':
			case 'N':
			case 'n': antwort=0;
			break;
		}
	}
	return antwort;
}
/**/


void menue_neukunde(bank *this) { //ToDo
	int n;
	n=this->kontenzahl+KUNDENKONTO_PRIM+1;
	konto_eroeffnen(&(this->konten[n]), n);

	menue_cls();
	printf("\nKonto-/Kunden-Nummer:\t%7d\n", this->konten[n].ktonr);
	printf("Ihre PIN:\t\t%7d\n", this->konten[n].pin);
	printf("Ihr Kontostand:\t\t%16.8lf\n   ", this->konten[n].guthaben);
	this->kontenzahl++;
	mypause("\n\nWeiter ...\n");
}

/*
int strtoint(char *s, l) {
	int i;
	for(i=l; i>0; i--) {
	}
}*/

void menue_kundenkonto(bank *this, int k) { //ToDo
	char antwort;
	int rc=1, laenge;
	konto kto=this->konten[k];

	while(rc) {
		menue_cls();
	
		printf("\n\n");
		printf("(1) Guthaben anzeigen\n");
		printf("(2) Einzahlung\n");
		printf("(3) Auszahlung\n");
		printf("(4) Ueberweisung (Bank-intern)\n");
		printf("(5) PIN aendern\n");
		printf("(6) Abmelden\n");
	
		printf("\n\nAuswahl: ");
		laenge=scanf("%1c", &antwort);
	//	cleartoendofline();
	
		if(laenge!=1) {
			printf("Bitte beachten Sie die gueltigen Eingabeoptionen!\n");
		}
		else{
	
			switch (antwort) {
				case '1':
					if(DEBUG_PRINT)printf("\nAufruf: Guthaben anzeigen\n");
					printf("Guthaben: %f", kto.guthaben);
					rc=1;
					break;
				case '2':
					if(DEBUG_PRINT)printf("\nAufruf: Einzahlung\n");
					rc=1;
					break;
				case '3':
					if(DEBUG_PRINT)printf("\nAufruf: Auszahlung\n");
					break;
				case '4':
					if(DEBUG_PRINT)printf("\nAufruf: Ueberweisung\n");
					break;
				case '5':
					if(DEBUG_PRINT)printf("\nAufruf: PIN aendern\n");
					break;
				case '6':
					rc=0;
					if(DEBUG_PRINT)printf("\nAufruf: Abmelden\n");
					break;
				//default://nuexx
			}
			mypause("\n\nWeiter ...\n");
		}
	}
	//return rc;
}

int menue_kundenlogin(bank *this) { //ToDo
	int loop=1;	//true for continuing "bank os"
	int rc=1;
	int kontonr=0;
	int pin=0, laenge;
	int *c[4];

	menue_cls();
	while( loop ) {
		printf("\n\n\n\nKundenlogin");
		if(DEBUG_PRINT)printf("% d", kontonr);
		printf("\n\n(0) Zurueck ...\n\n");

	    //+ Abfrage Kundennummer
		printf("Kundennummer:\t");
		laenge=scanf("%c%c%c%c", c[0], c[1], c[2], c[3]);
		cleartoendofline();
		//convert string to int
		//kontonr=sscanf(c, "%s", &c);
		printf("%d %d",laenge,kontonr);
		if(laenge != KTO_LAENGE )continue;
		
		//teste KtoNr ist nichtnegative Zahl

		//+ Abfrage PIN
		printf("PIN:\t\t");
		laenge=scanf("%4d", &pin);
		cleartoendofline();
		if(laenge != PIN_LAENGE )continue;

		//leere Eingabe zurueck zu Vormenue
		if( pin <= 0 || kontonr <= 0) {
			printf("Ungueltige Kontodaten!\n\n");
			mypause("\n\nWeiter ...\n");
			loop=0;
		}
		//teste ob Kto ist eroeffnet
		if(this->konten[kontonr].sperrung == pin3) {
			if(DEBUG_PRINT)printf("Dieses Konto ist wg. Falschanmeldung gesperrt!\nBitte nehmen Sie Kontakt zum Service auf.\n\n");
			mypause("\n\nWeiter ...\n");
			loop=0;
			break;
		}

		//+ Prüfung PIN
		if(this->konten[kontonr].pin != pin) {
printf("PIN!!! %d\n", this->konten[kontonr].pin);
			switch(this->konten[kontonr].sperrung) {
				case eroeffnet:
					this->konten[kontonr].sperrung=pin1;
					break;
				case pin1:
					this->konten[kontonr].sperrung=pin2;
					break;
				case pin2:
					this->konten[kontonr].sperrung=pin3;
					break;
				case pin3:
					break;
			}
			kontonr=0;
		}else{
			this->konten[kontonr].sperrung=eroeffnet;
			menue_kundenkonto(this, kontonr);
		}


		//+ Prüfung counter<3
		//  - true:Kontoübersicht
		//  - false:counter erhöhen
	
		
	}

	return loop;
}

unsigned char menue_hauptmenue(bank *this) {
	int rc=1;//true for continuing "bank os"
	char antwort;
	
	menue_cls();

	if(DEBUG_PRINT)printf("\n\n\n\n# Bank hat %d Kunden\n", this->kontenzahl);
	/* how to put together a format string? */
	if(DEBUG_PRINT)printf("Konto %d hat %16.8lf Guthaben \n",(KUNDENKONTO_PRIM+this->kontenzahl), this->konten[KUNDENKONTO_PRIM+this->kontenzahl].guthaben);

	printf("\n\n");
	printf("(1) Bestandskunde\n");
	printf("(2) Neukunde\n");
	printf("(3) Programm beenden\n");
//	printf("(4) Bankstatus\n");

	printf("\n\nAuswahl: ");
	scanf("%1c", &antwort);
//	cleartoendofline();

	switch ( antwort ) {
		case '1':
			if(DEBUG_PRINT)printf("\nAufruf: Kundenlogin\n");
			menue_kundenlogin(this);
			rc=1;
			break;
		case '2':
			if(DEBUG_PRINT)printf("\nAufruf: Neukunde\n");
			menue_neukunde(this);
			rc=1;
			break;
		case '3':
			if(DEBUG_PRINT)printf("\nAufruf: Programm beenden\n");
			rc = menue_programmbeenden();
			break;
//		case '4':
//			bank_status(this);
//			break;
		//default://nuexx
	}

	return rc;
}
