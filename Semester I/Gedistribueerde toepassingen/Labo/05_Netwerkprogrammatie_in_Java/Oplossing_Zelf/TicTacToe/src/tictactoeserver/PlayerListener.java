package tictactoeserver;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author counterpoint
 */
public  class PlayerListener implements Runnable {

    private final int MAX_PLAYERS = 10;

    private BlockingQueue<Player> players;
    private ExecutorService executorService;

    PlayerListener(BlockingQueue<Player> players) {
        this.players = players;
    }

 
    @Override
    public void run() {
        executorService = Executors.newFixedThreadPool(MAX_PLAYERS);
        while (true) {
            try {
                Player player1 = players.take();
                Player player2 = players.take();
                Game game = new Game(player1, player2);
                executorService.execute(game);
            } catch (InterruptedException ex) {
                Logger.getLogger(PlayerListener.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
     //   executorService.shutdown();
    }

}
