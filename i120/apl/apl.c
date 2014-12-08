// external libs

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

// definitions for preprocessor

#define PWD "0987"
#define BS_GROESSE 10000//f. 4-stellige Kontonummern
#define PIN_LAENGE 4
#define PIN_LAENGE_BIT 13
#define KTO_LAENGE 4
#define KTO_LAENGE_BIT 13
#define TERM_STRING "-0-\0"
#define DEBUG_PRINT 1	//debug-ausgabe kann abgeschalten werden
#define KUNDENKONTO_PRIM 1000
#define BARGELDKONTO 1000
#define WE "XBT" //Haupt-Waehrungseinheit definiert
#define GUTHABEN_MAX 21000000.0	//max. Guthaben d. we
#define GUTHABEN_MIN 1.0	//min. 1 we Guthaben
#define ZEIT_MENUEVERLASSEN 30 //in Sekunden

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

//dont use typeof for sticking to iso/standard
//0 - no error
//1 - unwanted input
int chkZahl(char s[]){
	int i=0;//counter
	char c;
	while(!strcmp(s[i],'\0')){//todo: string durchlaufen um ungueltiges auszuschliessen
		c=(char)s[i];
		if(c < 48 || c > 57){
			return 1;
		}
	}
	return 0;
}

/**
void myfflush{
		char c;
		//windows-alternative
		//fflush(stdin)
		while(getchar()!='\n');
}
**/

//Eingabe will man so haben: http://www.undertec.de/blog/2009/05/kbhit-und-getch-fur-linux.html

// general functions

void cleartoendofline(void){
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

double betrag(double betrag){
	if(betrag < 0){
		return (double)(-betrag);
	}else{
		return (double)betrag;
	}
}

/* Zufallszahlen ohne fuehrende Nullen */
int intZufallszahl(int stellen){
	time_t t;
	srand((unsigned) time(&t));
	int z=1928;
	int i=0;
	while((pow(10,stellen-1)-z)>0){
		z = (int)rand() % (int)pow(10,stellen);
		i++;
	}
	if(DEBUG_PRINT)printf("Zufallszahl brauchte %d Durchlaeufe!\n",i);
	return z;
}

void mypause(char *s){
	char c;
	printf("%s", s);
	getchar();
	cleartoendofline();
}

// class konto (account)

typedef struct {
	int ktonr;//: KTO_LAENGE_BIT;	//n-stellig -> m bit
	int pin;//: PIN_LAENGE_BIT;
	double guthaben;
	enum sperrung_t { gesperrt, eroeffnet, pin1, pin2, pin3, geloescht, gekuendigt } sperrung;
//	time	letzterlogin;
//	person	kunde;
//	enum kontotyp_t {privatkonto, geschaeftskonto, firmenkonto} kontotyp;
//	int aktivetanliste;
//	services service;
//	enum waehrung_t { btc, eur, usd } waehrung;
} konto;

/**/
int konto_einzahlung(konto *this, double summe){
	//GUTHABEN_MAX
	this->guthaben += summe;
}

/* Fehler-Codes:
 * 0 - alles ok
 * */
int konto_auszahlung(konto *this, double summe){
	//GUTHABEN_MIN
	this->guthaben -= summe;
	return 0;
}

void konto_eroeffnen(konto *this, int nummer){
	//todo: Registrierungsdatum speichern
	this->ktonr = nummer;	//Kontonummer festlegen
	this->pin = intZufallszahl(PIN_LAENGE);	//Pin generieren
	this->sperrung = eroeffnet;
	this->guthaben = 0;
}

// bonus...
//0 - no error
//1 - unwanted input
int chkPIN(int z){
	/*
	if(chkZahl(s[])!=0){//Zahl?!
		return 1;
	}
	*/
	//todo: checke auf triviale pins (
	//alles zahlen?
	//1. jede Zahl nur einmal,
	//2. nicht 4 aufeinander folgende)
	return z;
}

/*
void konto_pinaendern(konto *this, int pin){

}
*/

// class bank

/* Bank hat BS_GROESSE-1 Konten
 * Konto 0-1000 ist die Bank selbst
 * Kundenkonten beginnen ab 1001, s. KUNDENKONTO_PRIM
 * */
typedef struct {
	int kontenzahl;//: KTO_LAENGE_BIT;
//	double kundenvermoegen;
	konto konten[BS_GROESSE];
	int neuesterkunde;
} bank;

void bank_init(bank *this, double kapital){
	this->kontenzahl=0;
	this->konten[BARGELDKONTO].guthaben=kapital;
	this->neuesterkunde=KUNDENKONTO_PRIM;
}

void bank_status(bank *this){
	printf("Guthaben:\t%f\n",this->konten[BARGELDKONTO].guthaben);
	printf("Konten:\t\t%d\n",this->kontenzahl);
	printf("Neuester Kunde:\t%d\n\n\n",this->neuesterkunde);
	mypause("\n\nWeiter ...\n");
}

/* Fehler-Codes:
 * 0 - alles ok
 * 1 - ein Konto ist gesperrt
 * 2 - Fehler bei Betrag
 * 3 - Konto nicht gedeckt
 * */
int bank_ueberweisen(bank *this, konto *auszahlungskonto, konto *einzahlungskonto, double summe){
	/*
	 * 1. Konto gesperrt?
	 * 2. Konto gesperrt?
	 * summe == betrag(summe) && summe > 0?
	 * 1. konto gedeckt?
	 * */
	konto_auszahlung(auszahlungskonto, summe);
	konto_einzahlung(einzahlungskonto, summe);
	return 0;
}

// menue functions

void menue_cls(){
	int i;
	for(i=0;i<80;i++){
		printf("\n");
	}
}

int menue_abfragen(char *antwort){//char *stringArrayFragen,char *charArrayAntworten){
//	int i;
//	int loop=1;
	scanf("%c", antwort);
	cleartoendofline();
//Idee:Eingabe innerhalb einer Zeitspanne, sonst Funktion verlassen und Terminal sperren
/*
	time_t now;
	time(&now);
*/

/*
	while(loop){
		for(i=0; i<256 ; i++){
			printf("%s\n", stringArrayFragen[i]);
			if(strcmp(stringArrayFragen[i], TERM_STRING)){
				break;
			}
		}
*/

/*
				loop=0U;
	}
*/
	return 0;
}

int menue_programmbeenden(){
	int antwort=1;
	char pass[4];

	menue_cls();
	printf("\n\n\n\nSie sind im Begriff das Programm zu beenden!");
	printf("\nDie Kundendaten werden hierbei gelöscht.");
	printf("\n\nPasswort: ");
	scanf("%4s", &pass);
	cleartoendofline();

	if(!strcmp(pass, PWD)){
		printf("\nProgramm wird beendet!\n");
		return 0;
	}else{
		printf("(1) Ja, Programm beenden und alle Kundenfaten verlieren");
		printf("(2) Nein, auf keinen Fall");
		switch (antwort){
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


void menue_neukunde(bank *this){ //ToDo
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
int strtoint(char *s, l){
	int i;
	for(i=l; i>0; i--){
	}
}*/

int menue_kundenlogin(bank *this){ //ToDo
	int loop=1;	//true for continuing "bank os"
	int rc=1;
	int kontonr=0;
	int pin=0;

	menue_cls();
	while(loop){
		printf("\n\n\n\nKundenlogin %d\n\n(0) Zurueck ...\n\n", kontonr);

	    //+ Abfrage Kundennummer
		printf("Kundennummer:\t");
		scanf("%4d", &kontonr);
		cleartoendofline();
		
		//teste KtoNr ist nichtnegative Zahl

		//+ Abfrage PIN
		printf("PIN:\t\t");
		scanf("%4d", &pin);
		cleartoendofline();

		//leere Eingabe zurueck zu Vormenue
		if(pin <= 0 || kontonr <= 0){
			printf("Ungueltige Kontodaten!\n\n");
			mypause("\n\nWeiter ...\n");
			loop=0;
		}
		//teste ob Kto ist eroeffnet
		if(this->konten[kontonr].sperrung == pin3){
			if(DEBUG_PRINT)printf("Dieses Konto ist wg. Falschanmeldung gesperrt!\nBitte nehmen Sie Kontakt zum Service auf.\n\n");
			mypause("\n\nWeiter ...\n");
			loop=0;
			break;
		}

		//+ Prüfung PIN
		if(this->konten[kontonr].pin != pin){
printf("PIN!!! %d\n", this->konten[kontonr].pin);
			switch(this->konten[kontonr].sperrung){
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
		}


		//+ Prüfung counter<3
		//  - true:Kontoübersicht
		//  - false:counter erhöhen
	
		
	}

	return loop;
}

/*
void menue_kundenkonto(bank *this){ //ToDo
	menue_cls();
}
*/

unsigned char menue_hauptmenue(bank *this){
	int rc=1;//true for continuing "bank os"
	char antwort;
	
	menue_cls();

	if(DEBUG_PRINT)printf("\n\n\n\n# Bank hat %d Kunden\n", this->kontenzahl);
	/* how to put together a format string? */
	if(DEBUG_PRINT)printf("Konto %d hat %16.8lf Guthaben \n",(KUNDENKONTO_PRIM+this->kontenzahl), this->konten[KUNDENKONTO_PRIM+this->kontenzahl].guthaben);

	printf("\n\n");
	printf("(1) Bestandskunde\n");
	printf("(2) Neukunde\n");
//		printf("(3) Programm b[e]enden\n");
//		printf("(4) Bank[s]tatus\n");

	printf("\n\nAuswahl: ");
	scanf("%1c", &antwort);
//	cleartoendofline();

	switch (antwort){
		case '1':
		case 'K':
		case 'k':
			if(DEBUG_PRINT)printf("\nAufruf: Kundenlogin\n");
			menue_kundenlogin(this);
			rc=1;
			break;
		case '2':
		case 'N':
		case 'n':
			if(DEBUG_PRINT)printf("\nAufruf: Neukunde\n");
			menue_neukunde(this);
			rc=1;
			break;
		case '3':
		case 'E':
		case 'e':
			if(DEBUG_PRINT)printf("\nAufruf: Programm beenden\n");
			rc = menue_programmbeenden();
			break;
		case '4':
		case 'S':
		case 's':
			bank_status(this);
			rc=1;
			break;
		//default://nuexx
	}

	return rc;
}

// main function

main(){
	bank schalterbank;
	bank_init(&schalterbank, 50000.0);
	/*
	printf("Konten:\t%d\n",(&schalterbank)->kontenzahl);
	neu = (&schalterbank)->konten[(&schalterbank)->kontenzahl + KUNDENKONTO_PRIM+1];
	printf("Guthaben:\t%d\n",(&neu)->guthaben);
	/**/
	while(menue_hauptmenue(&schalterbank)){
		//einfach Dauerschleife, ist halt ne Bank
	}
	/***/
}
