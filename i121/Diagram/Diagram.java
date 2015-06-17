import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/* Quellen:
 * 	http://wahlen.dresden.de/2015/OBW/index.html ,
 * 	http://www.google.de/imgres?imgurl=http%3A%2F%2Fwww.dresden-central.de%2Ffileadmin%2F_processed_%2Fcsm_dresden-central_impressionen-096_5db90a198d.jpg&imgrefurl=http%3A%2F%2Fwww.dresden-central.de%2Fde%2Fentdecken%2Fmuseum%2Fkunstgewerbe.html&h=800&w=1066&tbnid=45MRinGGwq5AMM%3A&zoom=1&docid=LBMGfT6grs-7AM&ei=8Ax-VfvmLc7e7Aapi4GgDA&tbm=isch&iact=rc&uact=3&dur=303&page=8&start=81&ndsp=12&ved=0CJcCEK0DMFFqFQoTCPue0oeqkMYCFU4v2wodqUUAxA
 * 1. Kreis
 * 2. Säulen
 * CLI-Parameter: Werte, Bild -> [<Text> <Zahl>, ...], <Bild>
 * Komstruktor: Image Bild, Array Werte
 * Daten: Ulbig 15.4 Vogel 4.8 Festerling 9.6 Stange 36.0 Stosch 2.5 Hilbert 31.7 
 * Daten: 15.4 4.8 9.6 36.0 2.5 31.7 truemmerfrau.jpg
 * */
public class Diagram extends Panel {

	public Diagram( Image Background, double[] values ) {
		
		Picture BGPic=new Picture( Background, values );
		
		setLayout( new BorderLayout() );
		add( BGPic, BorderLayout.CENTER );
	}
	
	public static void main( String args[] ) /*throws Exception*/ {
		double numbers[] = new double[10];
		//~ String values[] = new String[10]; 
		Image Pic;
		
		//~ System.out.print( (args.length-1)+" Werte: " );
		//~ for (int i=0; i<(args.length-1); i++)
			//~ System.out.print( args[i]+" " );
		//~ System.out.println();
		//~ System.out.println( "Bild: "+ args[args.length-1] );
		
		if (
			//~ args.length % 2 == 0 ||
			args.length < 3
		) {
			System.out.println("[[Bezeichner], [Zahl], ...], [Bild] ");
			System.exit(1);
		}
		
		for (int i = 0; i < (args.length-1); i++) {
			numbers[i] = Double.parseDouble( args[i] );
		}
		
		Frame DiagramFrame=new Frame("Diagramm Oberbürgermeister DRESDEN 2015, 1. Wahlgang 7.6.");
		DiagramFrame.setLayout(new BorderLayout());
		
		DiagramFrame.addWindowListener(
			new WindowAdapter() {
				public void windowClosing( WindowEvent E ) {
					System.exit(1);
				}
			}
		);
		
		Pic = Toolkit.getDefaultToolkit().getImage( args[args.length-1] );
		DiagramFrame.add( new Diagram( Pic, numbers ), BorderLayout.CENTER );
		DiagramFrame.setVisible(true);
		DiagramFrame.pack();
	
	}
}

class Picture extends Panel {
	Image Img;
	int dimension=350;
	double[] values;
	double sum=0;
	double max=0;
	
// * Daten: Ulbig 15.4 Vogel 4.8 Festerling 9.6 Stange 36.0 Stosch 2.5 Hilbert 31.7 
	Color Colors[]={
					Color.black
					, Color.blue
					, new Color( 0xA5, 0x2A, 0x2A )	//brown
					, Color.red
					, new Color( 0x7E, 0x42, 0x7E ) //violet
					, Color.orange
					, Color.white
					, Color.pink
					, Color.yellow
				};
	
	public Picture( Image Im, double[] values ) {
		this.Img=Im;
		this.values = values;
		
		for( int i=0; i<10; i++ ) {
			values[i]=Math.abs( values[i] );
			if( values[i] == 0 ) {
				break;
			}
			this.sum += values[i];
			if( values[i] > this.max ) this.max = values[i];
		}
		//~ System.out.println( "sum: "+sum );

		for( int i = 0; i < Colors.length; i++ ) {
			Colors[i] = getColorTransparent( Colors[i], 50 ); //Farbe, Transparenz-Prozent
		}
		
		MediaTracker Tracker = new MediaTracker( this );
		Tracker.addImage( this.Img, 0 );
		
		try {
			Tracker.waitForID(0);
		} catch( Exception e ) {
			System.out.println( e );
			e.printStackTrace();
		}
		
	}
	
	public Color getColorTransparent( Color C, int prozent ) {
		//~ System.out.println( C.getRed() + "r " + C.getGreen() + "g " + C.getBlue() + "b " + C.getAlpha() + "a -> " + (int)Math.round(255*prozent/100) + "a");
		// in verständlich
		//~ return new Color(
			//~ C.getRed(),
			//~ C.getGreen(),
			//~ C.getBlue(),
			//~ (int)Math.round(255*prozent/100)
		//~ );
		// in wahrscheiunlich schneller
		return new Color( (C.getRGB() & 0x00FFFFFF) | ((int)Math.round(255*prozent/100)<<24) , true );
	}
		
	@Override
	public void paint(Graphics Graphic) {
		int b = 30;
		int r = 2;
		int v0 = 0;
		int vn = 0;
		int vm = 0;
		int mx = (this.Img.getWidth(this)/5*(5-4)-this.dimension/2);
		int my = mx;
		int ex = this.Img.getWidth(this)/5*4-((b+r)*values.length)/4;
		int ey = my+b/2;
		
		Graphic.drawImage( this.Img, 0, 0, this );
		
		for( int i=0; i < (this.values.length-1); i++ ) {
			vn = (int)Math.round(values[i]/this.sum*360.0);
			vm = (int)Math.round(values[i]/this.max*this.dimension);
			Graphic.setColor( Colors[ (i % Colors.length) ] );
			Graphic.fillArc( mx, my, this.dimension, this.dimension, v0, vn );
			Graphic.fillRect( ex+i*(b+r), ey+this.dimension-vm, b, vm );
			v0 += vn;
		}
	
	}
	@Override
	public Dimension getPreferredSize()
	{
		return new Dimension( this.Img.getWidth(this), this.Img.getHeight(this) );
	}
}
