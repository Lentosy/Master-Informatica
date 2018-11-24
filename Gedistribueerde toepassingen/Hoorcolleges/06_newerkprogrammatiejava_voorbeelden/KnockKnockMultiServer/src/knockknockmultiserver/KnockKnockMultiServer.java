/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package knockknockmultiserver;

import java.io.IOException;
import java.net.ServerSocket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vongenae
 */
public class KnockKnockMultiServer {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int portNumber = 9999;
        boolean listening = true;

        try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
            while (listening) {
                try {
                    new KnockKnockThread(serverSocket.accept()).start();
                } catch (IOException ex) {
                    Logger.getLogger(KnockKnockMultiServer.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        } catch (IOException e) {
            Logger.getLogger(KnockKnockMultiServer.class.getName()).log(Level.SEVERE, null, e);
            System.err.println("Could not listen on port " + portNumber);
            throw new RuntimeException(e);
        }
    }

}
