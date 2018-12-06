/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package processauction;

import java.io.IOException;
import java.io.InputStreamReader;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.Queue;

/**
 *
 * @author vongenae
 */
public class SoldConsumer {

    @Resource(lookup = "java:comp/DefaultJMSConnectionFactory")
    private static ConnectionFactory connectionFactory;
    @Resource(lookup = "jms/AuctionQueue")
    private static Queue queue;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try (JMSContext context = connectionFactory.createContext();) {
            JMSConsumer consumer = context.createConsumer(queue, "SOLD = true");

            AuctionListener listener = new AuctionListener();
            consumer.setMessageListener(listener);

            System.out.println("To end program, enter Q or q, then <return>");
            InputStreamReader inputStreamReader = new InputStreamReader(System.in);

            char answer = '\0';

            while (!((answer == 'q') || (answer == 'Q'))) {
                try {
                    answer = (char) inputStreamReader.read();
                } catch (IOException e) {
                    System.err.println("I/O exception: " + e.toString());
                }
            }
        }
    }

}
