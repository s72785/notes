import java.net.*;
import java.io.*;

public class TCP_Connection implements Runnable {
    public Socket connection;

    public TCP_Connection(Socket connectionSocket) {
        connection = connectionSocket;
    }

    public void run() {
        try {
            // Application
            while (true) {
                echo();
            }
        } catch (Exception e) {
            Thread.currentThread().interrupt();
        }
    }

// Application
    public String clientSentence;
    public String capitalizedSentence;

    public void echo() throws IOException {
        BufferedReader inFromClient =
            new BufferedReader(new InputStreamReader(this.connection.getInputStream()));

        DataOutputStream outToClient =
            new DataOutputStream ( this.connection.getOutputStream());

        clientSentence = inFromClient.readLine();
        capitalizedSentence = clientSentence.toUpperCase() + '\n';

        outToClient.writeBytes( capitalizedSentence );
    }
// --
}
