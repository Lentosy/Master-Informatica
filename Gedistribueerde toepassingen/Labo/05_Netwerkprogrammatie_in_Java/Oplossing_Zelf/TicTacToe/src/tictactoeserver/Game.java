package tictactoeserver;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author counterpoint
 */
public class Game implements Runnable {
    
    private final Character O = 'O';
    private final Character X = 'X';
    Map<Character, Player> players; // zoda we easy access kunnen doen, bv geef mij speler met 'X' symbool
    
    private Player currentPlayer;
    
    private final Player[] board = {
        null, null, null,
        null, null, null,
        null, null, null
    };
    
    public Game(Player player1, Player player2) {
        player1.mark = 'X';
        player2.mark = 'O';
        
        players = new HashMap<Character, Player>();
        
        players.put('X', player1);
        players.put('O', player2);
    }
    
    public boolean hasWinner(){
        int winconditions[][] = {
            // horizontal
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},           
            // vertical
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},       
            //diagonal
            {0, 4, 8},
            {6, 4, 2}
        };
        for (int[] wincondition : winconditions) {
            return wincondition[0] == wincondition[1] && wincondition[0] == wincondition[2];
        }
        return false;
    }

    @Override
    public void run() {
        currentPlayer = players.get('X');
        currentPlayer.send("its your turn BITCH");
    }
    
}
