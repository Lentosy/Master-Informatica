/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package knockknockserver;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vongenae
 */
public class KnockKnockServer {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            // create socket
            int port = 4444;
            ServerSocket serverSocket = new ServerSocket(port);
            System.err.println("Started server on port " + port);

            // repeatedly wait for connections, and process
            while (true) {
                try ( // a "blocking" call which waits until a connection is requested
                        Socket clientSocket = serverSocket.accept()) {
                    System.err.println("Accepted connection from client");

                    try ( // open up IO streams
                            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                            BufferedReader in = new BufferedReader(
                                    new InputStreamReader(clientSocket.getInputStream()))) {
                        
                        String inputLine, outputLine;
                        // Initiate conversation with client
                        KnockKnockProtocol kkp = new KnockKnockProtocol();
                        outputLine = kkp.processInput(null);
                        out.println(outputLine);

                        while ((inputLine = in.readLine()) != null) {
                            outputLine = kkp.processInput(inputLine);
                            out.println(outputLine);
                            if (outputLine.equals("Bye.")) {
                                break;
                            }
                        }
                        System.err.println("Closing connection with client");
                    }
                } catch (IOException ex) {
                    Logger.getLogger(KnockKnockServer.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(KnockKnockServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
