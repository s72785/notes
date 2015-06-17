import java.awt.*;

class Quadrat extends Figur {
	double edge=0;

	Quadrat( double a ) {
		this.edge=a;
	}

	double getCircumference() {
		return 4 * this.getEdge();
	}
	double getArea() {
		return this.getEdge() * this.getEdge();
	}
	int getHeight() {
		return this.getEdge();
	}
	int getWidth() {
		return this.getEdge();
	}
	
	private int getEdge() {
		return (int)Math.round(this.edge);
	}

	public void paint( Graphics g ) {
		//g.drawRect( x,y,w,h );
		g.drawRect( 1, 1, this.getWidth(), this.getHeight() );
	}

}
