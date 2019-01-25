/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package processauction;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;

/**
 *
 * @author vongenae
 */
public class AuctionListener implements MessageListener {

    @Override
    public void onMessage(Message m) {
        try {
            System.out.println("message received");
            String message = m.getBody(String.class);
            System.out.println(message);
            if (message.contains("SOLD BY")) {
                int startId = 5;
                int endId = message.indexOf(" SOLD BY ");
                int startClient = endId + 9;
                int endClient = message.indexOf(" FOR ");
                int startPrice = endClient + 5;
                int endPrice = message.length();
                String itemId = message.substring(startId, endId);
                String client = message.substring(startClient, endClient);
                String price = message.substring(startPrice, endPrice);
                System.out.println("Stuur factuur voor " + price + " naar " + client);
                System.out.println("Verstuur item " + itemId + " naar " + client);
                System.out.println("Meld verkoop aan eigenaars van item " + itemId);
            } else {
                Logger.getLogger(AuctionListener.class.getName()).log(Level.WARNING, "Ongeldig bericht {0}", m);
            }
        } catch (JMSException ex) {
            Logger.getLogger(AuctionListener.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
