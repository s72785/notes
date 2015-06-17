import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;
import java.security.*;

public class SimpleSecureServer
{
	public static void main(String argv[]) throws IOException
	{

		/* s.a. http://www.tutego.de/java/articles/SecurityManager.html */
		System.setSecurityManager( new SecurityManager(){

			@Override
			public void checkRead( String Filename ) {
				/* Bibliothek wird verhindert, muss deshalb behandelbar sein */
				Properties P=System.getProperties();
				final String LibPath=P.getProperty("sun.boot.library.path");
				
				// zuerst Zugriffe erlauben
				if (
					Filename.startsWith(LibPath) //Library nachladen erlauben
					|| Filename.endsWith("SimpleSecureServerConn.class") //eigene Verbindungs-Klasse erlauben
				) {
					return;
				}
				
				File FileHandle = new File(Filename);
				if(Filename.startsWith("/") | Filename.contains("..")) {
					throw new SecurityException("Kein Zugriff auf die Datei: " + Filename);
				}
			}
			@Override
			public void checkAccept (String host, int port)  {}
			@Override
			public void checkPermission 	(Permission p){} //neu!!
			//~ @Override
			//~ public void checkExit(int status) {
				//~ throw new SecurityException();
			//~ }
			//~ public void  checkPermission( java.security.Permission ){	}
			/* weitere Schnittstellen, die genutzt werden können */
			//~ public void checkAccess( Thread g ) {}
			//~ public void checkListen( int port ) {}
			//~ public void checkLink( String lib ) {}
			//~ public void checkPropertyAccess( String key ) {}
			//~ public void checkAccept( String host, int port ) {}
			//~ public void checkWrite( FileDescriptor fd ) {}
			//~ public void checkRead( FileDescriptor fd ) {}

		} );
		// aus Java6_Net.odp, hilft aber nicht
		ServerSocket SrvSocket = new ServerSocket( Integer.parseInt( argv[0] ) );
		while (true) {
			new SimpleSecureServerConn(SrvSocket.accept());
		}
	}	
}

class SimpleSecureServerConn extends Thread /* implements runable */ {
	Socket Sockt;
	SimpleSecureServerConn( Socket S ) {
		Sockt=S;
		//~ setPriority(NORM_PRIORITY -1);
		start(); 
	}

	public void run() {
		String Command=null;

		try {
			OutputStream out=Sockt.getOutputStream();
			String query=new BufferedReader(new InputStreamReader(Sockt.getInputStream())).readLine();
			System.out.println("Anfrage: "+query);

			StringTokenizer st=new StringTokenizer(query);
			if (
				(st.countTokens()>=2)
				&&  (Command=st.nextToken()).equals("GET")
			) {
				if( (query = st.nextToken()).startsWith("/") ) {
					query=query.substring(1);
				}
				try {
					System.out.println("Dateiname: "+query);
					
					SecurityManager security = System.getSecurityManager();
					if (security != null) {
						security.checkRead( query );
					} else {
						System.out.println( "Security haben wir (noch) nicht!" );
					}
					
					File FileHanlde=new File(query);
					FileInputStream fis=new FileInputStream(query);
					byte[] data=new byte[(int)FileHanlde.length()];
					System.out.println(fis.read(data)+" Zeichen");
					out.write(data);
				} catch (FileNotFoundException e) {
					System.out.println( "Datei nicht gefunden: "+ query);
					PrintStream ps = new PrintStream(out);
					char c=0;
					ps.print("HTTP/1.1 400 file not found or lack of privilege\r\n\r\n");
					ps.print("Nix da!\r\n");
				} catch (SecurityException e) {
					System.out.println("SecurityException");
				}
			} else {
				System.out.println("Fehler, aber hab' kein Bock auf Exception");
			}
			
			Sockt.close();
		} catch(IOException e) {
			System.out.println("I/O Error "+e);
		}
	}
}
