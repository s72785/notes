public class Materialartikel
{
  private String artikelname;
  private String artikelnummer;
  private String mengeneinheit;
  private int packungsgroesse;
  private int nachbestellung;
  private int bestellmenge;
  private int bestand;


  //Konstruktor
    public Materialartikel(String artikelname, String artikelnummer, String mengeneinheit)
    {
      this.artikelname 	= artikelname;
      this.artikelnummer 	= artikelnummer;
      this.mengeneinheit 	= mengeneinheit;
    }
    //"Standardkonstruktor"
    public Materialartikel()
    {
      this.artikelname 	= "";
      this.artikelnummer = "-1";
    }

  //set'er und get'er
    void setArtikelname(String artikelname){
      this.artikelname = artikelname;
    }
    String getartikelname(){
      return artikelname;
    }

    void setArtikelnummer(String a){
      this.artikelnummer = a;
    }
    String getartikelnummer(){
      return this.artikelnummer;
    }

    void setmengeneinheit(int mengeneinheint){
      this.mengeneinheit=mengeneinheit;
    }
    String getmengeneinheit(){
      return mengeneinheit;
    }

    void setpackungsgoesse(int packungsgroesse){
      this.packungsgroesse=packungsgroesse;
    }
    int getpackungsgroesse(){
      return packungsgroesse;
    }

    void setnachbestellung(int nachbestellung){
      this.nachbestellung=nachbestellung;
    }
    int getnachbestellung(){
      return nachbestellung;
    }

    void setbestellmenge(int bestellmenge){
      this.bestellmenge=bestellmenge;
    }
    int getbestellmenge(){
      return bestellmenge;
    }

    void setBestand(int bestand){
      this.bestand=bestand;
    }
    int getbestand(){
      return bestand;
    }


    //so ungefähr eine Standartausgabe
    public String toString()
    {
      return "Artikelname: "+artikelname+", Artikelnummer: "+artikelnummer+", Bestand: "+bestand;
    }
    //**********************************


  public static void main(String args[])
  {
    Materialartikel artikel;	//Referenzvbariable

	if(args.length < 3){
           System.out.println("Zu wenig Argumente angegeben!");
    }else{

      artikel=new Materialartikel();
      artikel.setArtikelname(args[0]);
      artikel.setArtikelnummer(args[1] );
      artikel.setBestand(Integer.parseInt(args[2]) );


		System.out.println(artikel);
   }


   /* System.out.println("Artikelname: "+auto.getartikelname()+",
Artikelnummer: "+auto.getartikelnummer()+
      ", Mengeneinheit: "+auto.getmengeneinheit());

    auto.setArtikelname("Osterei");
        System.out.println("Artikelname: "+auto.getartikelname()+",
Artikelnummer: "+auto.getartikelnummer()+
      ", Mengeneinheit: "+auto.getmengeneinheit());

   Materialartikel m=new Materialartikel();
    System.out.println(m);//hier spricht er automatisch die toString
funktion an
  }*/
  }
}
