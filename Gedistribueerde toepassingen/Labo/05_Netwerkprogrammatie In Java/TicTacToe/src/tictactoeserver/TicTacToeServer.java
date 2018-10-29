package tictactoeserver;

import java.io.IOException;
import java.net.ServerSocket;

public class TicTacToeServer {

    private static final int PORTNUMBER = 8901;
    private static final int MAXIMUM_CONNECTIONS = 10;

    /*De server kan de berichten van verschillende clients tegelijk afhandelen. 
    OXO is een spel met twee spelers. Alle logica van het spel wordt gerealiseerd door de server. 
    De taken van de server zijn dus (naast het beheren van de connecties):

    controleren of de zetten van de spelers correct zijn
    controleren of er een winnaar en een verliezer is
    de spelers informeren over de zetten van de tegenstander
     */
    public static void main(String args[]) throws IOException {
        int currentConnections = 0;
        boolean listening = true;
        try (ServerSocket serverSocket = new ServerSocket(PORTNUMBER)) {
            while (listening) {
                if (currentConnections < MAXIMUM_CONNECTIONS) {
                    Game game = new Game();
                    Player playerX = new Player(serverSocket.accept(), game, Symbol.X);
                    currentConnections++;
                    Player playerO = new Player(serverSocket.accept(), game, Symbol.O);
                    currentConnections++;
                    

                    game.currentPlayer = playerX;

                    playerX.setOpponent(playerO);
                    playerO.setOpponent(playerX);
                    playerX.start();
                    playerO.start();

                }
            }
        } catch (IOException ioe) {
            System.err.println(ioe.getMessage());
            System.exit(-1);
        }
    }
}
