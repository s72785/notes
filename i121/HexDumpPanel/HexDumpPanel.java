/*
 * done: HexDumpApplet extends Applet, oads HexDumpPanel in BorderLayout
 * HexDumpPanel extends Panel
 * 	HexDumpPanel() - add dropbox, textfiel, HexDumpArea aka TextArea
 * HexDumpArea extends TextArea
 * 	HexDumpArea(URL)
 * 	HexDumpArea(URLConnection)
 * 	HexDumpArea(Socket)
 * use HexDump
 * Actionliener zu TextField
 * */

import java.awt.*;
import java.awt.font.*;
import java.awt.event.*;
import java.lang.*;
import java.io.*;
import java.net.*;
//~ import java.lang.double.*;
//~ import java.lang.Integer.*;

/* adding swing component for aligment option */
/* prof sais: thou shall not mix swing and awt */
//~ import javax.swing.JTextField;

public class HexDumpPanel extends Panel {
	
	//~ HexDumpArea tf; 
	Choice lst;
	TextField tf;
	TextArea ha;
	InputStream is;
	URL url;
	URLConnection urlc;
	Socket sckt;

	ActionListener ctrl = new ActionListener(){
		public void actionPerformed( ActionEvent e ){
			
			// ToDo: reload ha
			
			//~ e.getActionCommand()
			//~ ha.setText( lst.getItem( lst.getSelectedIndex() ) );
			String Link = tf.getText();
			int index=lst.getSelectedIndex();
			try{
			switch( lst.getItem( index ) ) {
				case "URL":
					url = new URL( Link );
					is = url.openStream();
					break;
				case "URL-Connection":
					url = new URL( Link );
					is = url.openConnection().getInputStream();
					break;
				case "Socket":
					BufferedWriter out = null;
					sckt = new Socket( new URL(Link).getHost(), 80 );
					out = new BufferedWriter( new OutputStreamWriter( sckt.getOutputStream() ) );
					out.write( "GET " + Link + " HTTP/1.1\r\n\r\n" );
					out.flush();
					is = sckt.getInputStream();
					break;
				default:
					ha.setText( lst.getItem( index ) );
			}
			}catch( Exception exception ){
				
			}
			ha.setText( "" );
			ha.append( new HexDump( is ).getHexString() );
		};
	};
	
	public HexDumpPanel() {
		setFont( new Font( "System", Font.PLAIN, 24 ) );
		setLayout( new BorderLayout() );
		//~ add( new Label( "Enter File: " ) );

		//~ List lst = new List( 1, false );
		//~ lst.add( "URL" );
		//~ lst.add( "URL-Connection" );
		//~ lst.add( "Socket" );
		//~ add( lst, BorderLayout.WEST );

		lst = new Choice();
		lst.add( "URL" );
		lst.add( "URL-Connection" );
		lst.add( "Socket" );
		add( lst, BorderLayout.WEST );
		//~ lst.addActionListener( ctrl );

		tf = new TextField( "http://www2.htw-dresden.de/~beck/PSPII_WI/praktika/HEX/java06.html" );
		this.add( tf, BorderLayout.EAST );
		tf.addActionListener( ctrl );

		ha = new TextArea( 20, 80 );//HexDumpArea
		ha.setFont( new Font( "Courier", 0, 12 ) );
		ha.setEditable( false );
		//~ ( "http://www2.htw-dresden.de/~beck/PSPII_WI/praktika/HEX/java06.html" );
		add( ha, BorderLayout.SOUTH );

		//~ Panel cf = new Panel( new GridLayout( this.Tasten.length / tastenJeZeile, tastenJeZeile ) );
		//~ this.add( cf, BorderLayout.CENTER );
		//~ Button Btn;
		//~ for( int i=0; i < this.Tasten.length; i++ ) {
			//~ cf.add( Btn = new Button( this.Tasten[i] ) );
			//~ Btn.addActionListener( Aktionen[i] );
		//~ }
			
		//~ reset();
	}

	public static void main( String args[] ) {
		Frame F=new Frame();
		F.addWindowListener( new WindowAdapter() {
			public void windowClosing( WindowEvent e ) {
				System.exit( 1 );
			}
		} );
		HexDumpPanel P=new HexDumpPanel();
		F.add(P);
		F.pack();
		F.setVisible(true);
	}
}
