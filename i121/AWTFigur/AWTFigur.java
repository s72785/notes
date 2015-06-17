import java.awt.*;
import java.awt.event.*;

class AWTFigur extends Panel {
	
	Figur f;
	
	AWTFigur( Figur f ) {
		this.f=f;
	}
	
	public void paint( Graphics g ) {
		f.paint( g );
	}
	
	public Dimension getPreferredSize() {
		return new Dimension( f.getWidth()+2, f.getHeight()+2 );
	}
	
	public static void main( String args[] ) {
		Frame F=new Frame();
		F.setLayout( new FlowLayout() );
		F.addWindowListener( new WindowAdapter() {
			public void windowClosing( WindowEvent e ) {
				System.exit(0);
			}
		} );
		Figur F1;
		F1=new Dreieck(20, 20);
		AWTFigur P1=new AWTFigur( new Quadrat(30) );			F.add(P1);
		AWTFigur P2=new AWTFigur( new Circle(50) );			F.add(P2);
		AWTFigur P3=new AWTFigur( new Rectangle(5, 20) );			F.add(P3);
		AWTFigur P4=new AWTFigur( new Elipse(5, 40) );			F.add(P4);
		AWTFigur P5=new AWTFigur( F1 );			F.add(P5);
		F.pack();
		F.setVisible(true);
	}
}
