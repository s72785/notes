import java.applet.*;
import java.awt.*;

/* wichtig! class muss public deklariert sein! */
public class CalcApplet extends Applet {
	public void init(){
		setLayout(new BorderLayout());
		add(new CalcPanel(), BorderLayout.CENTER);
	}
}
