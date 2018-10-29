package tictactoeserver;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;
import tictactoeserver.TicTacToeProtocol.TicTacToeProtocolMessage;

public class Player extends Thread {

    private final Socket socket;
    private final Symbol symbol;
    private Game game;
    private Player opponent;
    private PrintWriter out;
    private BufferedReader in;
    private TicTacToeProtocol protocol;

    public Player(Socket socket, Game game, Symbol symbol) {
        super("TicTacToeThread");
        this.socket = socket;
        this.symbol = symbol;
        this.game = game;
        protocol = new TicTacToeProtocol();
        try {
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            send(TicTacToeProtocol.SYMBOL, symbol.toString());
            send(TicTacToeProtocol.WAITING, String.format("Welcome Player %c. We are currently waiting to match you with another opponent", symbol));
        } catch (IOException ex) {
            Logger.getLogger(Player.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void run() {
        send(TicTacToeProtocol.MESSAGE, "All players are connected");
        if (symbol == Symbol.X) {
            send(TicTacToeProtocol.MESSAGE, "Player X, it is your turn");
        }

    }

    public Player getOpponent() {
        return opponent;
    }

    public void setOpponent(Player opponent) {
        this.opponent = opponent;
    }

    public void otherPlayerMoved(int location) {

    }

    private void send(String command, String message) {
        TicTacToeProtocolMessage protocolMessage = protocol.build(command, message);
        out.println(protocolMessage.toString());
    }

}
