import java.awt.*;
import java.awt.event.*;
//~ import java.lang.double.*;
//~ import java.lang.Integer.*;

/* adding swing component for aligment option */
/* prof sais: thou shall not mix swing and awt */
//~ import javax.swing.JTextField;

class CalcPanel extends Panel {
	
	boolean	clearFlag = true,
			dotFlag = false,
			calcFlag = false;
	/* no swing, no right align in textfield */
	TextField tf; 
	//~ JTextField tf;
	
	double mem = 0.0;
	double op1 = 0.0;
	double op2 = 0.0;
	int tastenJeZeile = 5;
	String opt = "";

	ActionListener optL = new ActionListener(){
		public void actionPerformed( ActionEvent e ){
			if( e.getActionCommand().equals("CE") ) {
				reset();
				return;
			}
			//wenn operator nicht gesetzt, setze 1.
			if( !calcFlag ) {
				//speichere operand 1
				op1 = Double.valueOf( tf.getText() ).doubleValue();
				//speichere operator
				opt = e.getActionCommand();
				calcFlag = true;
				//demnächst Feld neu eingebe lassen, nächster wert
				clearFlag = true;
			}
			//wenn operator gesetzt, setze 2. 
			else {
				op2 = Double.valueOf( tf.getText() ).doubleValue();
				//berechne op1 neu
				switch( opt ) {
					case "/":
						op1 = op1 / op2 ;
					break;
					case "*":
						op1 = op1 * op2 ;
					break;
					case "+":
						op1 = op1 + op2 ;
					break;
					case "-":
						op1 = op1 - op2 ;
					break;
				}
				//neuen operant speichern
				opt = e.getActionCommand();
				//ausgabe
				if( new Double(new Double(op1).doubleValue() - new Double(op1).intValue()).equals(0.0) ) {
					tf.setText(( new Double(op1).intValue() ) + "" );
				} else {
					tf.setText( op1 + "" );
				}
				if( opt.equals("=") ) {
					clearFlag = true;
					calcFlag = false;
				}
			}
			
		};
	};
	
	ActionListener memL = new ActionListener(){
		public void actionPerformed( ActionEvent e ){
			double ax = Double.valueOf( tf.getText() ).doubleValue();
			switch( e.getActionCommand() ) {
				case "M+": mem += ax;
				break;
				case "M-": mem -= ax;
				break;
				case "MR": tf.setText( mem + "" );
				break;
			}
		};
	};
	
	ActionListener numL = new ActionListener(){
		public void actionPerformed( ActionEvent e ){
			String c = e.getActionCommand();
			if( clearFlag ) {
				tf.setText( "" );
				clearFlag = false;
			}
			if( c.equals(".") ) {
				if( dotFlag ) {
					c = "";
				} else {
					dotFlag = true;
				}
			}
			tf.setText( tf.getText() + c );
		};
	};
	
	String Tasten[] = { //.length
		"M+", "7", "8", "9", "/",
		"M-", "4", "5", "6", "*",
		"MR", "1", "2", "3", "-",
		"CE", "0", ".", "=", "+"
		//~ ,"^x", "sin", "cos", "1/x", "tau"
		//~ ,"\u221a", "tan", "exp", "log", "e"
	};
	
	ActionListener Aktionen[] = {
		memL, numL, numL, numL, optL, 
		memL, numL, numL, numL, optL, 
		memL, numL, numL, numL, optL, 
		optL, numL, numL, optL, optL
	};
	
	private void reset() {
		tf.setText("0");
		clearFlag = true;
		dotFlag = false;
		mem = 0.0;
		op1 = 0.0;
		op2 = 0.0;
		opt = "";
	}
	
	public CalcPanel() {
		this.setLayout( new BorderLayout() );

		/* no swing, no right align for textfield */
		tf = new TextField();
		//~ tf = new JTextField();
		//~ tf.setHorizontalAlignment( JTextField.RIGHT );

		
		this.add( tf, BorderLayout.NORTH );
		Panel cf = new Panel( new GridLayout( this.Tasten.length / tastenJeZeile, tastenJeZeile ) );
		this.add( cf, BorderLayout.CENTER );
		Button Btn;
		for( int i=0; i < this.Tasten.length; i++ ) {
			cf.add( Btn = new Button( this.Tasten[i] ) );
			Btn.addActionListener( Aktionen[i] );
		}
			
		//~ ok.addActionListener( new ActionListener() {
			//~ public void actionPerformed( ActionEvent e ) {
				//~ System.exit( 1 );
			//~ };
		//~ } );
		reset();
	}
	
	//~ @Override
	//~ public Dimension getPreferredSize() {
		//~ return new Dimension( 250, 200 );
	//~ }
	
	public static void main( String args[] ) {
		Frame F=new Frame();
		F.addWindowListener( new WindowAdapter() {
			public void windowClosing( WindowEvent e ) {
				System.exit( 1 );
			}
		} );
		CalcPanel P=new CalcPanel();
		F.add(P);
		F.pack();
		F.setVisible(true);
	}
}
