#ifndef _MYSTDLIB_H
#define _MYSTDLIB_H

# include <math.h> //for rand() and pow()
# include <time.h> //for clock() or time()

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
nextlowerprime( unsigned long long x ) {
	unsigned long long i = 1;
	while( 1 ){
		if( ( x - 1 ) <= 2 ) {
			return 2;
		}
		if ( isprime( x - i ) == 1 && ( x - i ) > 1 ) {
			return ( x - i);
		}
		i++;
	}
	return -1;
}

int
hash( unsigned long long potentiellgrossezahl, unsigned long long oberegrenze ) {
	//switch(oberegrenze) //maybe decide for hash function on parameter basis later
	//mid number
	//checksum
	//crypto
	//primes:
	//~ printf("\n z:%llu o:%llu p:%d h:%llu \n", potentiellgrossezahl, oberegrenze, nextlowerprime( oberegrenze ), potentiellgrossezahl % nextlowerprime( oberegrenze ));
	return potentiellgrossezahl % nextlowerprime( oberegrenze ) ;
}

int /* rc: -1 = unknown argument, z = random number */
intZufallszahl ( int stellen ) { /* renerate random number, avoid double ones */
	int z=-1;
	int a=0;

	if( stellen > 0 ) {

		z=0;

		srand( (unsigned)clock() );

		while( z == a || z == 0 || a == 0 ) {
			a=z;
			z = (int)rand() % (int)pow( 10, stellen );
		}
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
