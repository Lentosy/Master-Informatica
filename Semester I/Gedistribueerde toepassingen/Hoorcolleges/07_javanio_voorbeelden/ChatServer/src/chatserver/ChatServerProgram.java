/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chatserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.ServerSocketChannel;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vongenae
 */
public class ChatServerProgram {

    private static final int PORT = 4444;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
            serverSocketChannel.socket().bind(new InetSocketAddress(PORT));
            ChatServer cs = new ChatServer(serverSocketChannel);
            Thread csThread = new Thread(cs);
            csThread.start();
            Scanner sc = new Scanner(System.in);
            if (sc.nextLine().equals("quit")) {
                cs.stop();
            }
        } catch (IOException ex) {
            Logger.getLogger(ChatServerProgram.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
