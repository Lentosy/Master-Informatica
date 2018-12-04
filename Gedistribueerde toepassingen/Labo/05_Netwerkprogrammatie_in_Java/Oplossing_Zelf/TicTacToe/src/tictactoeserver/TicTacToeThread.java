package tictactoeserver;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 *
 * @author counterpoint
 */
public class TicTacToeThread extends Thread {

    private BlockingQueue<Player> players;
    private PlayerListener playerListener; // listen to client ocnnections
    private Listener listener; // start game when two clients connected

    public TicTacToeThread() {
        players = new LinkedBlockingQueue<>();
        playerListener = new PlayerListener(players);
        listener = new Listener(players);
    }

    @Override
    public void run() {
        new Thread(playerListener).start();
        new Thread(listener).start();

    }

}
