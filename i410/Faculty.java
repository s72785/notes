import java.util.*;

class Faculty {
	private ArrayList<Integer> Fakulties=new ArrayList<Integer>();

	Faculty() {
		this.Fakulties.add(0, 1);
	}
	
	public int getMax() {
		return this.Fakulties.size();
	}

	public int Berechnen( int i ) {
		int n;
		if( i < this.getMax() ) {
			return ( this.Fakulties.get( i ) );
		} else if( i == this.getMax() ) {
			n = i * this.Berechnen( i - 1 );
			this.Fakulties.add( i, n );
			return n;
		} else {
			n = this.Berechnen( i - 1 );
			this.Fakulties.add( i, n );
			return n;
		}
	}

	public static void main(String args[]) {
//		Faculty x=new Faculty();
		ArrayList<Integer> Fakulties=new ArrayList<Integer>();
		int i = 0;
		int o = 0;

		Fakulties.add(0,1);
		int n;
		int m;
		for( String a : args ) {
			n = Integer.parseInt( a );
			m = Fakulties.size() - 1;

			if( n > 0 ) {
				if( n > m ) {
					for( i=m+1; i<=n; i++ ) {
						Fakulties.add( i, Fakulties.get(i-1) * i );
					}
				}
			}

		}

			for( int j=0; j<Fakulties.size(); j++ ) {//String a : Fakulties.toArray() ){
				i = Fakulties.get(j);
				System.out.println( j + ": " + i );
			}
	}

}

