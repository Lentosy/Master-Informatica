package tictactoegame;

import java.util.Scanner;

/**
 * A server for a network multi-player tic tac toe game. Here are the strings
 * that are sent for communication in the Tic Tac Toe game:
 *
 * <blockquote>
 * Client -> Server 
 *      MOVE {n} (0 &lt;= n &lt;= 8)
 *      QUIT
 *      CONTINUE
 * Server -> Client 
 *      WELCOME {char} (char in {X, O}) 
 *      VALID_MOVE
 *      OTHER_PLAYER_MOVED {n} 
 *      VICTORY 
 *      DEFEAT 
 *      TIE 
 *      MESSAGE {text} 
 *      QUIT
 * </blockquote>
 *
 * This server allows an 10 pairs of players to play.
 */
public class TicTacToeServer {

    /**
     * Runs the application. Starts a thread for the server and listens to the
     * console.
     *
     * @param args
     */
    public static void main(String[] args) {
        // start thread: listen for players
        TicTacToeThread ticTacToe = new TicTacToeThread();
        Thread ticTacToeThread = new Thread(ticTacToe);
        ticTacToeThread.start();
        // wait for quit in the console
        Scanner sc = new Scanner(System.in);
        String input;
        do {
            input = sc.nextLine();
        } while (!input.equals("quit"));        
        System.exit(0);
    }
}
