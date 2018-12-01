/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package processauction;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.Queue;

/**
 *
 * @author vongenae
 */
public class NotSoldConsumer {

    @Resource(lookup = "java:comp/DefaultJMSConnectionFactory")
    private static ConnectionFactory connectionFactory;
    @Resource(lookup = "jms/MyQueue")
    private static Queue queue;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try (JMSContext context = connectionFactory.createContext();) {
            JMSConsumer consumer = context.createConsumer(queue, "SOLD = false");
            Message m = consumer.receive(1000);
            while (m != null) {
                System.out.println("message received");
                try {
                    String message = m.getBody(String.class);
                    System.out.println(message);
                    if (message.startsWith("NOT SOLD")) {
                        int startId = 9;
                        int endId = message.indexOf(" LAST OFFER ");
                        int startPrice = endId + 12;
                        int endPrice = message.length();
                        String itemId = message.substring(startId, endId);
                        String price = message.substring(startPrice, endPrice);
                        System.out.println("Meld aan eigenaars van item " + itemId 
                                + " dat het item niet verkocht is. Hoogst geboden prijs was " + price);
                    } else {
                        Logger.getLogger(NotSoldConsumer.class.getName()).log(Level.WARNING, "Ongeldig bericht {0}", m);
                    }
                } catch (JMSException ex) {
                    Logger.getLogger(NotSoldConsumer.class.getName()).log(Level.SEVERE, null, ex);
                }
                m = consumer.receive(1000);
            }
        }
    }
}
