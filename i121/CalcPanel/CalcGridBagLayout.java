import java.awt.*;
import java.awt.event.*;

/* adding swing component for aligment option */
/* prof sais: thou shall not mix swing and awt */
//~ import javax.swing.JTextField;

class CalcGridBagLayout extends Panel {
	
	GridBagConstraints C=new  GridBagConstraints();
	boolean	clearFlag = true,
			dotFlag = false,
			calcFlag = false;
	/* no swing, no right align in textfield */
	TextField tf; 
	//~ JTextField tf;
	
	Double mem = 0.0;
	Double op1 = 0.0;
	Double op2 = 0.0;
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
				//~ tf.setText(( new Double(new Double(op1).doubleValue() - new Double(op1).intValue()).equals(0.0) ? new Double(op1).intValue() : tf.setText( op1 + "" ) ) + "" );
				if( opt.equals("=") ) {
					clearFlag = true;
					calcFlag = false;
				}
			}
			
		};
	};
	
	ActionListener memL = new ActionListener(){
		public void actionPerformed( ActionEvent e ){
			Double ax = Double.valueOf( tf.getText() ).doubleValue();
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
		//~ "-/+", "sin", "cos", "1/x", "e",
		//~ "\u221a", "tan", "exp", "log", "^x",
		"M+", "7", "8", "9", "/",
		"M-", "4", "5", "6", "*",
		"MR", "1", "2", "3", "-",
		"CE", "0", ".", "=", "+"
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
	
	public CalcGridBagLayout() {
		this.setLayout( new GridBagLayout() );
		
		C.weightx = 1.0;
		C.weighty = 1.0;
		C.fill = GridBagConstraints.BOTH;
		C.anchor = GridBagConstraints.WEST;
		C.gridx = 0;
		C.gridy = 0;
    
		/* no swing, no right align for textfield */
		tf = new TextField();
		//~ tf = new JTextField();
		//~ tf.setHorizontalAlignment( JTextField.RIGHT );
		
		C.gridwidth = GridBagConstraints.REMAINDER;
		this.add( tf, C );
		Button Btn;
		C.gridwidth=1;
		//C.gridx GridBagConstraints.RELATIVE;
		for( int i=0; i < this.Tasten.length; i++ ) {
			C.gridx = (i % tastenJeZeile == 0)? 1 : GridBagConstraints.RELATIVE ;
			C.gridy = (i + tastenJeZeile) / tastenJeZeile;
			this.add( Btn = new Button( this.Tasten[i] ), C );
			Btn.addActionListener( Aktionen[i] );
		}
		//TR initialisieren
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
		CalcGridBagLayout P=new CalcGridBagLayout();
		F.add(P);
		F.pack();
		F.setVisible(true);
	}
}
