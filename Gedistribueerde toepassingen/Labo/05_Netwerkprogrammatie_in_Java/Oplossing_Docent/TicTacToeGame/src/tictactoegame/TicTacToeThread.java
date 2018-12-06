package tictactoegame;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Starts two threads. One that listens for client connections and one that 
 * starts a game when there are two players.
 * 
 * @author vongenae
 */
public class TicTacToeThread extends Thread {

    private final BlockingQueue<Player> players;
    PlayerListener gamesThread;
    Listener listener;

    public TicTacToeThread() {
        players = new LinkedBlockingQueue<>();
        gamesThread = new PlayerListener(players);
        listener = new Listener(players);
    }

    @Override
    public void run() {
        new Thread(gamesThread).start();
        new Thread(listener).start();
    }
    
}
