package tictactoeclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JFrame;



/**
 * 
 * 
 * Client -> Server         Server -> Client
 * ----------------         ----------------
 * MOVE <n> (0 <= n <= 8)   WELCOME <char> (char in {X, O})
 * 
 * 
 * 
 * 
 * @author counterpoint
 */
public class TicTacToeClient implements AutoCloseable, Observer {
    
    private final int PORT = 8901;
    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;
    private TicTacToeFrame frame;
    
    public TicTacToeClient(String address, TicTacToeFrame frame) throws IOException {
        socket = new Socket(address, PORT);
        
        out = new PrintWriter(socket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        
        this.frame = frame;
        
    }
    
    public void play() throws IOException{
        boolean quit = false;
        do{
            String input = in.readLine();
            frame.bericht(input);
        } while(!quit);
    }
    
    public static void main(String[] args) throws Exception {
        TicTacToeFrame frame = new TicTacToeFrame();
        new Thread(() -> {
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(400, 300);
            frame.setVisible(true);
            frame.setResizable(false);
        }).start();
        
        TicTacToeClient client = new TicTacToeClient("localhost", frame);
        frame.addListener(client);
        client.play();
    }

    @Override
    public void update(Observable o, Object arg) {
        out.println("MOVE " + frame.getPosition());      
    }

    @Override
    public void close() throws Exception {
        socket.close();
    }
}
