#ifndef _STDIO_H
# include <stdio.h>
#endif
#ifndef	_MYIO_H
# include "myio.h"
#endif

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

void bank_init( bank *this, double kapital ) {
	this->kontenzahl=0;
	this->konten[BARGELDKONTO].guthaben=kapital;
	this->neuesterkunde=KUNDENKONTO_PRIM;
}

void bank_status( bank *this ) {
	printf("Guthaben:       %f\n",this->konten[BARGELDKONTO].guthaben);
	printf("Konten:         %d\n",this->kontenzahl);
	printf("Neuester Kunde: %d\n\n\n",this->neuesterkunde);
	mypause("\n\nWeiter ...\n");
}

/* Fehler-Codes:
 * 0 - alles ok
 * 1 - ein Konto ist gesperrt
 * 2 - Fehler bei Betrag
 * 3 - Konto nicht gedeckt
 * */
int bank_ueberweisen( bank *this, konto *auszahlungskonto, konto *einzahlungskonto, double summe ) {
	int rc=0;
	/*
	 * 1. Konto existent?
	 * 1. Konto gesperrt?
	 * 2. Konto existent?
	 * 2. Konto gesperrt?
	 * summe == betrag(summe) && summe > 0?
	 * 1. konto gedeckt?
	 * */
	rc = konto_auszahlung( auszahlungskonto, summe );
	rc = konto_einzahlung( einzahlungskonto, summe );
	return 0;
}
