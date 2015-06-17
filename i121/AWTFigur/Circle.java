import java.awt.*;
import java.lang.Math;

class Circle extends Figur {
	double radius=1;
	
	Circle( double r ) {
		this.radius=r;
	}
/* get/set für Attribute */
	double getRadius(){
		return this.radius;
	}
/* Methoden */
	double getCircumference() {
		return 2*Math.PI*this.getRadius();
	}
	double getArea() {
		double r=getRadius();
		return r*r*Math.PI;
	}
	double getDiameter() {
		return 2*this.getRadius();
	}
	int getWidth() {
		return (int)Math.round(this.getDiameter());
	}
	int getHeight() {
		return (int)Math.round(this.getDiameter());
	}
	public void paint( Graphics g ) {
		//g.drawArc( x, y, w, h, a, b );
		g.drawArc( 1, 1, this.getWidth(), this.getHeight(), 0, 360 );

	}
	
}
