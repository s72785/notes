import java.awt.*;
import java.lang.Math;

class Elipse extends Figur {
	double radiusA=1;
	double radiusB=1;
	
	Elipse( double r1, double r2 ) {
		this.radiusA=r1;
		this.radiusB=r2;
	}
/* get/set für Attribute */
	double getRadiusA(){
		return this.radiusA;
	}
	double getRadiusB(){
		return this.radiusB;
	}
/* Methoden */
	double getCircumference() {
		double r1=getRadiusA();
		double r2=getRadiusB();
		return Math.PI*Math.sqrt( 2*( this.getRadiusA()*this.getRadiusA() + this.getRadiusB()*this.getRadiusB() ));
	}
	double getArea() {
		double r1=getRadiusA();
		double r2=getRadiusB();
		return Math.PI*(r1+r2)/2*(r1+r2)/2;
	}
	int getWidth() {
		return (int)Math.round(2*this.getRadiusA());
	}
	int getHeight() {
		return (int)Math.round(2*this.getRadiusB());
	}
	public void paint( Graphics g ) {
		//g.drawArc( x, y, w, h, a, b );
		g.drawOval( 1, 1, this.getWidth(), this.getHeight() );

	}
	
}
