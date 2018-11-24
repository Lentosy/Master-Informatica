package auctionserver.model;

import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Map;
import java.util.TimerTask;

/**
 *
 * @author counterpoint
 */
public class AuctionManager extends TimerTask {
    private Map<Client, SocketChannel> clients;
    private Selector selector;

    public AuctionManager(){
        clients = new HashMap<>();
    }
    
    public void addClient(Client client, SocketChannel socketChannel){
        clients.put(client, socketChannel);
    }
    @Override
    public void run() {
        
    }
    
}
