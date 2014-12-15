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
//	int i=0;
	int z,a;

	if( stellen <= 0 ) {
		return -1;//error code: ungueltiges Argument
	}

	z=1928;
	a=z;

	srand((unsigned) time(&t));

	while( z==a ) {
		z = (int)rand() % (int)pow( 10, stellen );
//		i++; // number ob rounds needed
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
*/
int
char2int(char c){
	if( isnumchar(c) ){
		return (int)(c-48);
	} else {
		return -1;
	}
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

#endif // _MYSTDLIB_H
