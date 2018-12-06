package tictactoeserver;

import java.io.IOException;
import java.net.ServerSocket;
import java.util.concurrent.BlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author counterpoint
 */
public class Listener implements Runnable {

    private final int PORT = 8901;

    private BlockingQueue<Player> players;
    private ServerSocket listener;

    Listener(BlockingQueue<Player> players) {
        this.players = players;
        try {
            listener = new ServerSocket(PORT);
            System.out.println("Tic Tac Toe Server is up ...");
        } catch (IOException ex) {
            Logger.getLogger(Listener.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void run() {
        while (true) {
            try {
                players.add(new Player(listener.accept()));
                System.out.println("Accepting player...");
            } catch (IOException ex) {
                Logger.getLogger(Listener.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
