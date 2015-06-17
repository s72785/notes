import java.applet.*;
import java.awt.*;

/* wichtig! class muss public deklariert sein! */
public class HexDumpApplet extends Applet
{

	public void init(){
		setLayout(new BorderLayout());
		try{
			add(new HexDumpPanel());
		} catch(Exception e) {
			System.err.println("externe Klasse konnte nicht geladen werden: "+e);
		}
	}

}
