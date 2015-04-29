import java.lang.*;
import java.io.*;

public class HexDump {
	byte data[];
	static final int BUF_SIZE=1024;

	HexDump(String s) {
		 data=s.getBytes();
	}

	HexDump(InputStream fis) {
		try {
			ByteArrayOutputStream bos = new ByteArrayOutputStream(this.BUF_SIZE);
			byte buf[] = new byte[this.BUF_SIZE];
			int lenr;

			while( ( lenr = fis.read(buf) ) > -1 ) {
				bos.write(buf,0,lenr);
			}

			data=bos.toByteArray();
		} catch(Exception e) {
			System.out.println(e);
		}
	}

	/* produces a char Array of length len displaying
		 the hexadecimal Value of the value z */
	private char[] getHexByte( int z, int len ) {
		char[] x=new char[len];
		int i,hx;
		for( i = len-1; i >= 0; i-- ) {
			 hx=z;
			 z>>>=4;
			 hx&=0xf;
			 x[i]=(char)(hx<=9?hx+'0':hx+'A'-10);
		}
		return x;
	}

	/* produces a String in the Form of a hexdump
		 of an array of bytes */
	public String getHexString() {

		String outStr = "";
		char addrArr[] = new char[4];
		char hexArr[] = new char[2];
		String hexStr = "";
		String clearStr = "";
		char dataByte = 0;
		int maxIndex = data.length;
		maxIndex = maxIndex / 16 * 16 + ( maxIndex % 16 + ( 16 - ( maxIndex % 16 ) ) );
		boolean	emptyFlag=true;

		for( int i=0; i < maxIndex; i++ ) {

			if( i < data.length ) {
				dataByte = (char)data[i];
				emptyFlag = true;
			} else {
				emptyFlag = false;
			}
			
			hexArr = getHexByte( dataByte, 2 );
			hexStr += ( !emptyFlag ) ? "   " : hexArr[0] + "" + hexArr[1] + " ";
			clearStr += ( !emptyFlag ) ? " ":( dataByte < 32 || dataByte > 126 ) ? "." : (char)dataByte ;

			if( (i+1)==maxIndex || ((i+1) % 16) == 0 ) {
				addrArr = getHexByte( ( i - ( ( i + 1 ) == data.length ? 0 : 15 ) ), 4 );
				outStr += "\n" + addrArr[0] + addrArr[1] + addrArr[2] + addrArr[3] + ": " + hexStr + "  "  + clearStr;
				hexStr = "";
				clearStr = "";
			} else if( ((i+1) % 4) == 0 ) {
				hexStr += "| ";
			}

		}
		return outStr;
	}

	public static void main(String args[]) {
		try {
			System.out.println( new HexDump( new FileInputStream( args[0] ) ).getHexString() );
		} catch( Exception e ) {
			System.out.println( e );
			System.out.println( "\nOutput for your Argument:" );
			System.out.println( new HexDump( args[0] ).getHexString() );
		}
	}

}
