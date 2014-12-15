#ifndef _KONTO_CLASS_H
# define _KONTO_CLASS_H

//todo: redo as list
// deleting accounts
typedef struct {
	int ktonr;//: KTO_LAENGE_BIT;	//n-stellig -> m bit
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
} konto;

/* Fehler-Codes:
 * 1 - alles ok
 * 0 - Grenze ueberschritten
 * */
int
konto_einzahlung( konto *this, double summe ) {
	if( (this->guthaben + summe) <= GUTHABEN_MAX ) {
		this->guthaben += summe;
		return 1;
	}
	return 0;
}

/* Fehler-Codes:
 * 1 - alles ok
 * 0 - Grenze unterschritten
 * */
int
konto_auszahlung( konto *this, double summe ) {
	if(DEBUG_PRINT == 2)printf("\n# this %d\n",this);
	if( (this->guthaben - summe) >= GUTHABEN_MIN ) {
		this->guthaben -= summe;
		return 1;
	}
	return 0;
}

void
konto_neuepin( konto *this ) {
	if(DEBUG_PRINT == 2)printf("\n# this %d\n",this);
	this->pin=0;
	while( !(konto_checkpin(this->pin)) ) {
		this->pin = intZufallszahl(PIN_LAENGE); // generate new(!) PIN 
	}
}

void
konto_eroeffnen( konto *this, int nummer ) {
	if(DEBUG_PRINT == 2)printf("\n# this %d\n",this);
	//todo: save date of registration
	this->ktonr = nummer;	// determine account number
	this->sperrung = eroeffnet;
	this->guthaben = 0.0;
	konto_neuepin( this );
}

// bonus function, not necessary for the enlisted tasks...
//1 - no error
//0 - unwanted input
int
konto_checkpin( int z ) {
	if( z == 0) return 0;
	if( z == 1234) return 0;
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
	return 1;
	/*
	if(chkZahl(s[])!=0) {//Zahl?!
		return 1;
	}
	*/
	//todo: checke auf triviale pins (
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

void konto_pinaendern(konto *this, int npin) {
	this->pin = npin;
}

#endif // _KONTO_CLASS_H
