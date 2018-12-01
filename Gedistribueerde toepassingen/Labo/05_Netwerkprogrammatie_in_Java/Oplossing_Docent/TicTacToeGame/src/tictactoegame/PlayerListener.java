package tictactoegame;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Takes two players from the queue and starts a new game (thread).
 *
 * @author vongenae
 */
public class PlayerListener extends Thread {

    private final BlockingQueue<Player> players;
    ExecutorService execServ;

    PlayerListener(BlockingQueue<Player> list) {
        this.players = list;
    }

    @Override
    public void run() {
        execServ = Executors.newFixedThreadPool(10);
        boolean active = true;
        while (active) {
            try {
                Player player1 = players.take();
                Player player2 = players.take();
                Game game = new Game(players, player1, player2);
                execServ.submit(game);
            } catch (InterruptedException ex) {
                Logger.getLogger(PlayerListener.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        execServ.shutdown();
    }

}
