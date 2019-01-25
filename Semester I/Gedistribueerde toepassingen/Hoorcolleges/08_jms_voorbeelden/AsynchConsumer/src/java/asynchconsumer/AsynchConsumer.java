package asynchconsumer;

import java.io.IOException;
import java.io.InputStreamReader;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSRuntimeException;
import javax.jms.Queue;
import javax.jms.Topic;

/**
 *
 * @author vongenae
 */
public class AsynchConsumer {

    @Resource(lookup = "jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;
    @Resource(lookup = "jms/MyQueue")
    private static Queue queue;
    @Resource(lookup = "jms/MyTopic")
    private static Topic topic;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        if (args.length != 1) {
            System.err.println("Program takes one argument: <dest_type>");
            System.exit(1);
        }

        String destType = args[0];
        System.out.println("Destination type is " + destType);

        if (!(destType.equals("queue") || destType.equals("topic"))) {
            System.err.println("Argument must be \"queue\" or \"topic\"");
            System.exit(1);
        }

        Destination dest;
        try {
            if (destType.equals("queue")) {
                dest = queue;
            } else {
                dest = topic;
            }
            
            /*
             * In a try-with-resources block, create context.
             * Create consumer.
             * Register message listener (TextListener).
             * Receive text messages from destination.
             * When all messages have been received, enter Q to quit.
             */
            try (JMSContext context = connectionFactory.createContext();) {
                JMSConsumer consumer = context.createConsumer(dest);
                TextListener listener = new TextListener();
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
            } catch (JMSRuntimeException e) {
                System.err.println("Exception occurred: " + e.toString());
                System.exit(1);
            }
        } catch (JMSRuntimeException e) {
            System.err.println("Error setting destination: " + e.toString());
            System.exit(1);
        }

        System.exit(0);
    }

}
