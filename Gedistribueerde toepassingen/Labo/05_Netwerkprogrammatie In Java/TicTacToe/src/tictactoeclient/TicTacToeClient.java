package tictactoeclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import javax.swing.JFrame;
import tictactoeserver.TicTacToeProtocol;
import tictactoeserver.TicTacToeProtocol.TicTacToeProtocolMessage;

public class TicTacToeClient {

    private static final String HOSTNAME = "localhost";
    private static final int PORTNUMBER = 8901;
    private TicTacToeFrame frame;
    private TicTacToeProtocol protocol;
    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;

    /**
     * Runs the client as an application.
     *
     * @param args
     * @throws java.lang.Exception
     */
    public static void main(String[] args) throws Exception {

        TicTacToeClient client = new TicTacToeClient();
        client.initializeConnection();
        client.initializeGUI();
        client.play();
    }

    public void initializeConnection() throws IOException {

        socket = new Socket(HOSTNAME, PORTNUMBER);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);
        protocol = new TicTacToeProtocol();

    }

    public void initializeGUI() {

        frame = new TicTacToeFrame();
        new Thread(() -> {
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(500, 400);
            frame.setVisible(true);
            frame.setResizable(false);
        }).start();
    }

    public void play() throws Exception {
        try {
            while (true) {
                TicTacToeProtocolMessage response = protocol.read(in.readLine());
                switch (response.command) {
                    case TicTacToeProtocol.SYMBOL:
                        frame.setMark(response.message.charAt(0));
                        break;
                    case TicTacToeProtocol.MESSAGE:
                        frame.bericht(response.message);
                        break;
                    default:
                        break;
                }

            }
        } finally {
            socket.close();
        }

    }
}
