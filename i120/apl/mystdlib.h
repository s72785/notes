#ifndef _MYSTDLIB_H
# define _MYSTDLIB_H

#ifndef	_MATH_H
# include <math.h> //for rand() and pow()
#endif
#ifndef	_TIME_H
# include <time.h> //for clock() or time()
#endif

int
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
isnumchar ( char c ) { /* 1=true, 0=false */
	if( c >= '0' && c <= '9'){
		return 1;
	} else {
		return 0;
	}
}

int
isboolint ( int i ) { /* 1=true, 0=false */
	if( i >= 0 && i <= 1){
		return 1;
	} else {
		return 0;
	}
}

int
char2int(char c){ /* -1 = no number char as input, 0-9 = int for char '0'-'9' */
	if( isnumchar(c) ){
		return (int)(c-48);
	} else {
		return -1;
	}
}

#endif // _MYSTDLIB_H
