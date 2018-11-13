package synchconsumer;

import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.JMSRuntimeException;
import javax.jms.Message;
import javax.jms.Queue;
import javax.jms.TextMessage;
import javax.jms.Topic;

/**
 *
 * @author vongenae
 */
public class SynchConsumer {

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
             * Receive all text messages from destination until
             * a non-text message is received indicating end of
             * message stream.
             */
            try (JMSContext context = connectionFactory.createContext();) {

                JMSConsumer consumer = context.createConsumer(dest);
                int count = 0;

                while (true) {
                    Message m = consumer.receive(1000);

                    if (m != null) {
                        if (m instanceof TextMessage) {
                            // Comment out the following two lines to receive
                            // a large volume of messages
                            System.out.println(
                                    "Reading message: " + m.getBody(String.class));
                            count += 1;
                        } else {
                            break;
                        }
                    }
                }
                System.out.println("Messages received: " + count);
            } catch (JMSException e) {
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
