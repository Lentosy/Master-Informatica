package tictactoegame;

import java.io.IOException;
import java.net.ServerSocket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vongenae
 */
public class Listener extends Thread {

    // Server is listening at port '8901'
    private static final int POORT = 8901;
    private ServerSocket listener;
    BlockingQueue<Player> players;

    Listener(BlockingQueue<Player> players) {
        this.players = players;
        try {
            listener = new ServerSocket(POORT);
            System.out.println("Tic Tac Toe Server is up  ...");
        } catch (IOException ex) {
            Logger.getLogger(Listener.class.getName()).log(Level.SEVERE, null, ex);
            throw new RuntimeException(ex);
        }
    }

    @Override
    public void run() {

        while (true) {
            try {
                Player player = new Player(listener.accept());
                players.add(player);
            } catch (IOException ex) {
                Logger.getLogger(TicTacToeThread.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
