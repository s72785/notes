#include <stdio.h>

long searchprime( unsigned long long target ) {
	unsigned long long p = 0UL;
	unsigned long long l = 0UL;
	unsigned long long i;

	p = 2;
	while( p <= target ) {
		for( i = 1; i < p / 2; i++ ) {
			//pruefe auf prim
			l=p; // letzte primzahl beiseite legen
		}
		p++; // f. abbrichbedingung ikcrementieren
	}

	return l;
}

int h( unsigned long long bigint ) {
	unsigned long long prim = 13UL;

	return bigint % (unsigned long long)prim;
}
int main( void ) {
	unsigned long long target = 10000000000 / 10000; // target: 10-stellig auf 4-stellig abbilden
	unsigned long long prime; // primzahl, die ich suchen muss
	//wanna have still an array with size 10.000 "as I am used to that"
	prime = 13ULL;//searchprime( target );
	printf("Gefundene Primzahl für Zielgroesse %llu ist: %llu\n", target, prime);

	return 0;
}
