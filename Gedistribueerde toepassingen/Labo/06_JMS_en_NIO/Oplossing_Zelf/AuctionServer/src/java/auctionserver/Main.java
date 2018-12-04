package auctionserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.ServerSocketChannel;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.Queue;


/**
 *
 * @author counterpoint
 */
public class Main  {

    private static final int PORT = 7777;

    @Resource(lookup = "java:comp/DefaultJMSConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup = "jms/AuctionQueue")
    private static Queue queue;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        try {
            ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
            serverSocketChannel.socket().bind(new InetSocketAddress(PORT));
            AuctionManager auctionManager = new AuctionManager(connectionFactory, queue, serverSocketChannel);
            Thread thread = new Thread(auctionManager);
            thread.start();

            Scanner sc = new Scanner(System.in);
            if (sc.nextLine().equals("quit")) {
                auctionManager.stop();
            }
        } catch (IOException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

}
