/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package echoclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vongenae
 */
public class EchoClient {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String hostName = "localhost"; // 127.0.0.1 of ::1
        int portNumber = 4444;

        try (Socket echoSocket = new Socket(hostName, portNumber); 
                PrintWriter out = new PrintWriter(echoSocket.getOutputStream(), true); 
                BufferedReader in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream())); 
                BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))) {
            String userInput = leesTekst(stdIn);
            while (!userInput.equals("exit")) {
                out.println(userInput); // naar server
                System.out.println("echo: " + in.readLine()); // van server
                userInput = leesTekst(stdIn);
            }
        } catch (IOException ex) {
            Logger.getLogger(EchoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private static String leesTekst(final BufferedReader stdIn) throws IOException {
        System.out.print("Geef invoer: ");
        String userInput = stdIn.readLine();
        return userInput;
    }
}
