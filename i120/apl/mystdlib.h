
#ifndef	_MYSTDLIB_H
# define	_MYSTDLIB_H	1
#endif

#ifndef _STDIO_H
# include <stdio.h>
#endif
#ifndef	_MATH_H
# include <math.h>
#endif
#ifndef	_TIME_H
# include <time.h>
#endif

double
betrag( double betrag ) {
	if( betrag < 0 ) {
		return (double)( -betrag );
	} else {
		return (double)betrag;
	}
}

/* Zufallszahlen für Stellenzahl > 0 */
int
intZufallszahl ( int stellen ) {
	time_t t;
	if( stellen <= 0 ) {
		return -1;//error code: ungueltiges Argument
	}
	srand((unsigned) time(&t));
	int z=1928;
	int a=z;
	int i=0;
	while( z==a ) {
		a=z;
		z = (int)rand() % (int)pow( 10, stellen );
		i++;
	}
	return z;
}

int
isnumchar ( char c ) {
	if( c >= '0' && c <= '9'){
		return 0;
	}
	return 1;
}

//dont use typeof for sticking to iso/standard
//0 - no error
//1 - unwanted input
/*
int chkZahl ( char *s ) {
	int i = 0;//counter
	char c;
	while( !strcmp(s[i],'\0') ) {//todo: string durchlaufen um ungueltiges auszuschliessen
		c = (char)s[i];
		if( c < 48 || c > 57 ) {
			return 1;
		}
	}
	return 0;
}
*/

/*
//already built in
int
strlen ( char *str ) {
	int i = 0 ;

	while ( *str++ ) {
		i++;
	}

	return i;
}
/**/
