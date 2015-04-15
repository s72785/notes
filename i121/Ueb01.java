class Ueb01 {

	private int wochentag(int y, int m, int d){
		int mt[]={31,28,31,30,31,30,31,31,30,31,30,31};
		int md = 0;
		int wd=0;

		for(int i=1; i<m; i++){
			md += mt[i];
		}
		return ((y-1900)*365 + (y-1900)/4 + md + d)%7;
	}

	public static void main(String argv[]){
		int y, m, d;
		y = m = d = 0;
		String dn="";
		String wt[]={ "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa" };

		/* 1.1.1900 */
		if( argv[0].indexOf(".") > -1 ) {
			String[] s = argv[0].split("\\.");
			d = Integer.parseInt(s[0]);
			m = Integer.parseInt(s[1]);
			y = Integer.parseInt(s[2]);
		} else { /* 1900 1 1 */
			y = Integer.parseInt(argv[0]);
			m = Integer.parseInt(argv[1]);
			d = Integer.parseInt(argv[2]);
		}

		System.out.printf("%d. Wochentag", wd );
		System.out.printf(" ist %s\n", wt[wd] );
	}
	
}
