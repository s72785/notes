/* APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// external libs
#include <stdio.h>
#include <stdlib.h>

// definitions for preprocessor
#define PWD 987
#define BS_GROESSE 10000 //f. 4-stellige Kontonummern
#define PIN_LAENGE 4	//#define PIN_LAENGE_BIT 13
//#define PIN_VERSUCHE 3
#define KTO_LAENGE 4	//#define KTO_LAENGE_BIT 13
#define DEBUG_PRINT 0	// debug-output 1=enabled, 0=disabled
#define WE "XBT" // defining currency as the exercise did not mention any
#define BETRAG_DELIMETER ','
#define STELLEN_VKOMMA 8
#define STELLEN_NKOMMA 8
#define GUTHABEN_MIN 0.0	// min. 1 we Guthaben
#define GUTHABEN_MAX 21000000.0	// max. Guthaben d. we
#define KUNDENKONTO_PRIM 1000
#define BARGELDKONTO 1000

// header files for even more structure
#include "mystdlib.h"	// general functions
#include "konto.class.h"// class konto (account)
#include "bank.class.h"	// class bank
#include "bankmenue.h"	// menue functions

// main function - no asertions as this shall not crash
int
main( void ) {
	bank schalterbank;
	bank_init( &schalterbank, 50000.0 );
	
	while( menue_hauptmenue( &schalterbank ) );	//infty-loop, its a "Bank-OS" after all

	return 0;
}
