/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package knockknockpool;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vongenae
 */
public class KnockKnockPool {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int portNumber = 9999;
        boolean listening = true;

        try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
            ExecutorService execServ = Executors.newFixedThreadPool(10);

            while (listening) {
                try {
                    Socket clientSocket = serverSocket.accept();
                    execServ.submit(new KnockKnockRunnable(clientSocket));
                } catch (IOException ex) {
                    Logger.getLogger(KnockKnockPool.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        } catch (IOException e) {
            Logger.getLogger(KnockKnockPool.class.getName()).log(Level.SEVERE, null, e);
            System.err.println("Could not listen on port " + portNumber);
            throw new RuntimeException(e);
        }
    }
    
}
