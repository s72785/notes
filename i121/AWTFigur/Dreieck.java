import java.awt.*;
import java.lang.Math;

class Dreieck extends Figur {
	double edgeA=1;
	double height=1;
	
	Dreieck( double r1, double r2 ) {
		this.edgeA=r1;
		this.height=r2;
	}
/* get/set für Attribute */
	double getedgeA(){
		return this.edgeA;
	}
/* Methoden */
	double getCircumference() {
		return getWidth()+getHeight()+Math.sqrt((Math.pow(getWidth(), 2) + Math.pow(getHeight(), 2)));
	}
	double getArea() {
		return (getWidth()*getHeight())/2;
	}
	int getWidth() {
		return (int)Math.round(this.getedgeA());
	}
	int getHeight() {
		return (int)Math.round(this.height);
	}
	public void paint( Graphics g ) {
		//g.drawArc( x, y, w, h, a, b );
		
		//g.drawLine( 1, 1, this.getWidth(), this.getHeight() );
		g.drawLine( 1, 1, this.getWidth(), 1 );
		g.drawLine( 1, 1, 1, this.getHeight() );
		g.drawLine( this.getWidth(), 1 , 1, this.getHeight() );

	}
	
}
