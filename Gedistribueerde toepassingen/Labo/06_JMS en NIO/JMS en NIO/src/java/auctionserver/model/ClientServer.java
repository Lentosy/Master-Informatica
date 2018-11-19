/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package auctionserver.model;

/**
 *
 * @author counterpoint
 */
public class ClientServer implements Runnable{

    private AuctionManager auctionManager;
    
    public ClientServer(AuctionManager auctionManager){
        this.auctionManager = auctionManager;
    }
    @Override
    public void run() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
