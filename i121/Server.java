import java.net.*;
import java.io.*;

public class Server implements Runnable {

    public int port = 0;
    public ServerSocket welcomeSocket;

    public void setPort(int port) {
        this.port = port;
    }

    public Server(int port) {
        setPort(port);
    }

    public void run() {

// Der SendeSocket
DatagramSocket ds;
// leeres Datagramm bereitstellen
DatagramPacket packr=new DatagramPacket(new byte[1024],1024);
        try {
//Socket initialisieren
ds = new DatagramSocket();
// Warten auf Empfang, Socket von voriger Folie weiter verwendet
ds.receive(packr);
// Paket auspacken
String messr=new String(packr.getData(),0,packr.getLength());
System.out.println(messr);
ds.close();


// Datagram Senden
//~ String myHost=“MeinHost.informatik,htw-dresden.de“
//~ String myHost=“localhost“
//~ byte[] mess=args[0].getBytes();
//~ // Liefert Internetadresse
//~ InetAddress addr=InetAddress.getByName(myHost);
//~ // Das Datenpaket
//~ DatagramPacket packs= new DatagramPacket
//~ (mess,mess.length, addr, myPort);
//~ // Der SendeSocket
//~ DatagramSocket ds = new DatagramSocket();
//~ // Paket absenden
//~ ds.send(packs);

            //~ try {
                //~ this.welcomeSocket = new ServerSocket(port);
            //~ } catch (IOException e) {
                //~ System.out.println("failed to bind socket on port " + port);
            //~ };

            //~ while (true) {
                //~ Socket connectionSocket = welcomeSocket.accept();
                //~ Thread c = new Thread(new TCP_Connection(connectionSocket));
                //~ c.start();
            //~ }

        } catch (Exception e) {
            Thread.currentThread().interrupt();
            System.out.println(e);
            //~ e.print
        }
    }

    public static void main(String args[])
        throws Exception {

        //~ Thread s = new Thread(new Server( Integer.parseInt(argv[0]) ));
        Thread s = new Thread(new Server(3333));
        s.start();

    }
}
