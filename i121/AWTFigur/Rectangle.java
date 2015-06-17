import java.awt.*;

class Rectangle extends Figur {
	double edgeA=0;
	double edgeB=0;
	
	Rectangle( double a, double b ) {
		this.edgeA=a;
		this.edgeB=b;
	}
	
	double getCircumference() {
		return 2 * ( this.getEdgeA() + this.getEdgeB() );
	}
	double getArea() {
		return this.getEdgeA() * this.getEdgeB();
	}
	int getHeight() {
		return this.getEdgeB();
	}
	int getWidth() {
		return this.getEdgeA();
	}
	
	int getEdgeA() {
		return (int)Math.round(this.edgeA);
	}
	int getEdgeB() {
		return (int)Math.round(this.edgeB);
	}
	
	public void paint( Graphics g ) {
		g.drawRect( 1, 1, this.getWidth(), this.getHeight() );
	}
	
}
