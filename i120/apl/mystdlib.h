/* This APL is a demo for an interactive bank system and dedicated to first steps in learning C programming language,  Copyright (C) 2014-2015  s72785
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _MYSTDLIB_H
#define _MYSTDLIB_H

#include <math.h> //for rand() and pow()
#include <time.h> //for clock() or time()

/* 1=true, -1=false */
int
isprime( unsigned long long candidate ) {
	unsigned long long i;

	for( i = 2 ; i <= candidate - 1 ; i++ ) {
		if ( candidate % i == 0 ) { 
			return -1;
			break;
		}
	}
	if( i == candidate ) {
		return 1;
	}
	return -1;//suppressing compiler warning
}

int
nextprime( unsigned long long x ) {
	unsigned long long i = 1;

	while( 1 ){
		if( isprime( x + i ) == 1 ) {
			return ( x + i);
		} else if ( isprime( x - i ) == 1 && ( x - i ) > 1 ) {
			return ( x - i);
		}
		i++;
	}
}

int
hash( unsigned long long potentiellgrossezahl, unsigned long long oberegrenze ) {
	return potentiellgrossezahl % nextprime( oberegrenze ) ;
}

//~ int
//~ kontohash( unsigned long long kontonummer ) {
	//~ return hash( kontonummer, BS_GROESSE );
//~ }
//~ 
int /* rc: -1 = unknown argument, z = random number */
intZufallszahl ( int stellen ) { /* renerate random number, avoid double ones */
	int z;
	int a;

	if( stellen <= 0 ) {
		return -1;//error code: ungueltiges Argument
	}

	z=0;

	srand( (unsigned)clock() );

	while( z == a || z == 0 || a == 0 ) {
		a=z;
		z = (int)rand() % (int)pow( 10, stellen );
	}

	return z;
}

int
isnumchar ( char c ) { /* rc: 1=true, 0=false */
	if( c >= '0' && c <= '9'){
		return 1;
	} else {
		return 0;
	}
}

int
isboolint ( int i ) { /* rc: 1=true, 0=false */
	if( i >= 0 && i <= 1){
		return 1;
	} else {
		return 0;
	}
}

int
char2int(char c){ /* rc: -1 = no number char as input, 0-9 = int for char '0'-'9' */
	if( isnumchar(c) ){
		return (int)(c-48);
	} else {
		return -1;
	}
}

#endif // _MYSTDLIB_H
