long searchprime( int target ) {
	long p = 0;
	long l = 0;

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

int h( long long bigint ) {
	long prim = 13;
	return bigint % 13;
}
int main( void ) {
	long prime; // primzahl, die ich suchen muss
	int target = 10000000000 / 10000; // target: 10-stellig auf 4-stellig abbilden
	//wanna have still an array with size 10.000 "as I am used to that"
	prime = searchprim( target );
	printf("Gefundene Primzahl für Zielgroesse %d ist: %d", target, prime);

	return 0;
}
