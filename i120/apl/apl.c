/* This APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014-2015  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// external libs
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// definitions for preprocessor
#define PWD 987
#define KTO_LAENGE 10    //10-stellige Kontonummern für 2. Teil der APL
#define BS_GROESSE 10   //10^2 f. 4-stellige Kontonummern im 1. Teil -> 4-stellig Hashes im 2. Teil
#define PIN_LAENGE 4     //#define PIN_LAENGE_BIT 13
//#define PIN_VERSUCHE 3
#define DEBUG_PRINT 1    // debug-output 1=enabled, 0=disabled
#define WE "XBT"         // defining currency as the exercise did not mention any
#define BETRAG_DELIMETER ','
#define STELLEN_VKOMMA 8
#define STELLEN_NKOMMA 8
#define GUTHABEN_MIN 0.0 // min. 1 we Guthaben
#define GUTHABEN_MAX 21000000.0	// max. Guthaben d. we
#define KUNDENKONTO_PRIM 10000000000ULL // 10.000.000.000 // erstes Kundenkonto
#define BARGELDKONTO 1000000000ULL // Konto für Bargeld der Bank

// header files for even more structure
#include "list.class.h"	// general functions
#include "mystdlib.h"	// general functions
#include "konto.class.h"// class konto (account)
#include "bank.class.h"	// class bank
#include "bankmenue.h"	// menue functions

// main function - no asertions as this shall not crash
int
main( void ) {
	bank *schalterbank = NULL;
	bank_init( schalterbank, 50000.0 );

//~ bank_findekonto( bank *this, unsigned long long kontonummer )
	list *ptrlst = NULL;
	konto *ptrkto = NULL;
	
	bank *this = schalterbank;
	int hash = kontohash( BARGELDKONTO );
	ptrlst = this->konten[ hash ];
	//~ ptrlst = bank_kontoliste( &schalterbank, BARGELDKONTO );

//~ printf("%d \n", ptrlst == NULL );
	
	while( ptrlst != NULL ) {

		printf("lst %d \n", ptrlst != NULL );
		if(ptrlst != NULL){
			printf("lnx %d \n", ptrlst->next != NULL );
			printf("ldt %d \n", ptrlst->data != NULL );
			printf("kto %d \n", ptrkto != NULL );
			
			ptrkto = ptrlst->data;
			if(ptrkto != NULL){
				printf("knr %d \n", ptrkto->ktonr != 0 );
				printf("kgh %d \n", ptrkto->guthaben != 0.0 );
				printf("kpn %d \n", ptrkto->pin != 0 );
			}
		}
		//~ if( ptrkto->ktonr == BARGELDKONTO ) {
			//~ printf("%d\n", ptrkto != NULL );
		//~ }else{
			//~ printf("X");
		//~ }
		ptrlst = ptrlst->next;
	}

exit(0);
	
	//signal( SIGINT, menue_programmbeenden() );
	while( menue_hauptmenue( schalterbank ) );	//infty-loop, its a "Bank-OS" after all
	//signal( SIGINT, SIG_DFL );
	return 0;
}
