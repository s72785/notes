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
int konto_einzahlung( konto *this, double summe ) {
	//GUTHABEN_MAX
	this->guthaben += summe;
}

/* Fehler-Codes:
 * 0 - alles ok
 * */
int konto_auszahlung( konto *this, double summe ) {
	//GUTHABEN_MIN
	this->guthaben -= summe;
	return 0;
}

void konto_eroeffnen( konto *this, int nummer ) {
	//todo: Registrierungsdatum speichern
	this->ktonr = nummer;	//Kontonummer festlegen
	this->pin = intZufallszahl(PIN_LAENGE);	//Pin generieren
	this->sperrung = eroeffnet;
	this->guthaben = 0;
}

// bonus function, not necessary for the enlisted tasks...
//0 - no error
//1 - unwanted input
int konto_checkpin( konto *this, int z ) {
	/*
	if(chkZahl(s[])!=0) {//Zahl?!
		return 1;
	}
	*/
	//todo: checke auf triviale pins (
	//alles zahlen?
	//1. jede Zahl nur einmal,
	//2. nicht 4 aufeinander folgende)
	return 0;
}

/*
void konto_pinaendern(konto *this, int pin) {

}
*/
