import java.awt.*;
import java.awt.event.*;

class Muster extends Panel {
	
	Button ok;
	TextArea ta;
	
	public Muster() {
		setLayout( new BorderLayout() );
	
		//Komponenten erzeugen und Oberfläche zusammenbauen
		//Listener verbinden
		ta=new TextArea();
		this.add( ta, BorderLayout.CENTER );
		ok=new Button( "OK" );
		this.add( ok, BorderLayout.SOUTH );
		ok.addActionListener( new ActionListener() {
			public void actionPerformed( ActionEvent e ) {
				System.exit( 1 );
			};
		} );
	}
	
	@Override
	public Dimension getPreferredSize() {
		return new Dimension( 200, 150 );
	}
	
	public static void main( String args[] ) {
		Frame F=new Frame();
		F.addWindowListener( new WindowAdapter() {
			public void windowClosing( WindowEvent e ) {
				System.exit( 1 );
			}
		} );
		Muster P=new Muster();
		F.add(P);
		F.pack();
		F.setVisible(true);
	}
}
