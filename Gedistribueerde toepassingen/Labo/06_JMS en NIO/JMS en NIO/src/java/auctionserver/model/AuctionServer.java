package auctionserver.model;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


/**
 *
 * @author counterpoint
 */
public class AuctionServer {

    public static void main(String[] args){
        
        ExecutorService executor = Executors.newCachedThreadPool();
        AuctionManager manager = new AuctionManager();
        
        
        executor.execute(new ClientServer(manager));
        executor.execute(manager);
    }
    

    
}
