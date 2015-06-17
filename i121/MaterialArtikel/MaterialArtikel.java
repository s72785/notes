import java.io.*;

class MaterialArtikel {
	private String Artikelname="Linux";
	private int Lagerbestand=20;
	private int Mindeststueckzahl=10;
	private int Bestellmenge=50;
//bisher unbenutzt:
	private int Packungsgroesse=1;
	private String Artikelnummer="a100";
	private String Hersteller="Gruen";
	private String Haendler="Blau";
	private String Mengeneinheit="Stck";

	/* Konstruktoren */

	public MaterialArtikel(){	}
	public MaterialArtikel(String Artikelname) { this.Artikelname = Artikelname; }

	/*  [gs]etter  */

	//Artikelname
	public String getArtikelname() { return this.Artikelname; }
	public void setArtikelname(String Artikelname) { this.Artikelname = Artikelname; }
	//Lagerbestand
	public int getLagerbestand() { return this.Lagerbestand; }
	public void setLagerbestand(int Anzahl) { this.Lagerbestand = Anzahl; }
	//Hersteller
	public String getHersteller() { return this.Hersteller; }
	public void setHersteller(String Hersteller) { this.Hersteller = Hersteller; }
	//Haendler
	public String getHaendler() { return this.Haendler; }
	public void setHaendler(String Haendler) { this.Haendler = Haendler; }
	//Mengeneinheit
	public String getMengeneinheit() { return this.Mengeneinheit; }
	public void setMengeneinheit(String Einheit) { this.Mengeneinheit = Einheit; }
	//Artikelnummer
	public String getArtikelnummer() { return this.Artikelnummer; }
	public void setArtikelnummer(String Artikelnummer) { this.Artikelnummer = Artikelnummer; }
	//Packungsgroesse
	public int getPackungsgroesse() { return this.Packungsgroesse; }
	public void setPackungsgroesse(int Anzahl) { this.Packungsgroesse = Anzahl; }
	//Mindeststueckzahl
	public int getMindeststueckzahl() { return this.Mindeststueckzahl; }
	public void setMindeststueckzahl(int Anzahl) { this.Mindeststueckzahl = Anzahl; }
	//Bestellmenge
	public int getBestellmenge() { return this.Bestellmenge; }
	public void setBestellmenge(int Anzahl) { this.Bestellmenge = Anzahl; }

	/*  ...  */

	public String toString() { return "Artikel: "+getArtikelname()+", Bestand: "+getLagerbestand()+", Hersteller: "+getHersteller()+", Händler: "+getHaendler()+", Mengeneinheit: "+getMengeneinheit()+", Artikelnummer: "+getArtikelnummer()+", Packungsgröße: "+getPackungsgroesse()+", Mindeststückzahl: "+getMindeststueckzahl()+", Bestellmenge: "+getBestellmenge(); }

	public boolean Entnahme(int Anzahl) /* throws Exception */ {
		if( getLagerbestand() >= Anzahl ) {
			this.Lagerbestand -= Anzahl;
			return true;
		} else {
			// throw new LagerLeerException("Lager leer");
			return false;
		}
	}
	
	public boolean ausreichendBestand() {
		return (this.getLagerbestand() >= this.getMindeststueckzahl());
	}

	public void Bestellen() {
		this.setLagerbestand(this.getLagerbestand() + this.getBestellmenge() );
	}
	/*  ...  */

	public static void main(String args[]) throws Exception {
		//falls man mal was nur so zum Testen ausgeben mag
		boolean debug=false;
		
		MaterialArtikel x =  new MaterialArtikel();
		
		if(args.length > 0){
			//umständliche Schleife weil ggf. mehr Eigenschaften hinzu kommen und so die Verzweigung über die Anzahl erledigt ist
			for(int i=0; i<args.length; i++) {

				switch(i) {
					case 0:
						x.setArtikelname(args[i]);
						break;
					case 1:
						x.setLagerbestand(Integer.parseInt(args[i]));
						break;
					case 2:
						x.setMindeststueckzahl(Integer.parseInt(args[i]));
						break;
					case 3:
						x.setMindeststueckzahl(Integer.parseInt(args[i]));
						break;
					case 4:
						x.setBestellmenge(Integer.parseInt(args[i]));
						break;
					case 5:
						break;
					default:
				}

			}

		} else {

			System.out.println("Sie haben keine Argumente übergeben!\nBitte übergeben Sie als nulltes den Artikelnamen und als erstes die Anzahl.");

		}

		System.out.println("\n\n== Bestand == \n\n" + x/*.toString()*/);

		//hält die Eingabeschleife am Leben
		boolean run = true;

		while(run){

			if(!x.ausreichendBestand()) {
				/*while(delta <= 0) {
					System.out.print("Wieviel? Anzahl in Ziffern: ");
					try {
						delta = Integer.parseInt(br.readLine());
					} catch(NumberFormatException nfe) {
						System.out.println("Das war jetzt nicht nett, benimm dich!");
					}
				}*/
				x.Bestellen();
				System.out.println("\nNachbestellung von " + x.getBestellmenge() + " ausgelöst!\n");
				System.out.println("\n== Bestand == \n\n" + x/*.toString()*/);
//			} else {
//				System.out.println("Keine Nachbestellung notwendig!");
			}

			System.out.print("\n== Funktionen ==\n\n1 - Materialentnahme\n" + /* "2 - Nachbestellung\n" + */ "9 - Beenden\n\n");
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

			int auswahl=0;
			while(auswahl==0) {
				try {
					System.out.println("Eingabe: ");
					auswahl = Integer.parseInt(br.readLine());
				} catch(NumberFormatException nfe) {
					System.out.println("Ne, das will keiner wissen!");
				}
			}
			int delta=0;
			boolean success=false;

			switch(auswahl){
				case 1:
					while(delta <= 0) {
						System.out.print("Wieviel? Anzahl in Ziffern: ");
						try {
							delta = Integer.parseInt(br.readLine());
						} catch(NumberFormatException nfe){
							System.out.println("Das war jetzt nicht nett, benimm dich!");
						}
					}
					success = x.Entnahme(delta);
					if( !success ) {
						System.out.println("Das Lager hat nicht genug Artikel für ihren Auftrag!");
					}
					break;
				case 9:
					run = false;
					break;
				default:
					System.out.println("Unerwartete Eingabe!");
			}

			System.out.println("\n"+x/*.toString()*/);
		}

	}

}
