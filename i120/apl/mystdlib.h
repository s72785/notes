#ifndef _MYSTDLIB_H
# define _MYSTDLIB_H

#ifndef _STDIO_H
# include <stdio.h>
#endif
#ifndef	_MATH_H
# include <math.h>
#endif
#ifndef	_TIME_H
# include <time.h>
#endif

/*
double betrag( double betrag );
int intZufallszahl ( int stellen );
int isnumchar ( char c );
int isboolint ( int i );
int char2int(char c);
*/

double
betrag( double betrag ) {
	if( betrag < 0 ) {
		return (double)( -betrag );
	} else {
		return (double)betrag;
	}
}

/* renerate random number, avoid double ones */
int
intZufallszahl ( int stellen ) {
	time_t t;
	int z,a;

	if( stellen <= 0 ) {
		return -1;//error code: ungueltiges Argument
	}

	z=0;

	srand( (unsigned)time(&t) );

	while( z == a || z == 0 || a == 0 ) {
		a=z;
		z = (int)rand() % (int)pow( 10, stellen );
	}

	return z;
}

/*
 * 1=true
 * 0=false
 * */
int
isnumchar ( char c ) {
	if( c >= '0' && c <= '9'){
		return 1;
	} else {
		return 0;
	}
}

/*
 * 1=true
 * 0=false
 * */
int
isboolint ( int i ) {
	if( i >= 0 && i <= 1){
		return 1;
	} else {
		return 0;
	}
}

/*
-1 = no number char as input
0-9 = int for char '0'-'9'
*/
int
char2int(char c){
	if( isnumchar(c) ){
		return (int)(c-48);
	} else {
		return -1;
	}
}

#endif // _MYSTDLIB_H
