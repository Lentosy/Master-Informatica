package producer;

import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.JMSContext;
import javax.jms.JMSRuntimeException;
import javax.jms.Topic;
import javax.jms.Destination;
import javax.jms.Queue;

/**
 *
 * @author vongenae
 */
public class Producer {

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
        final int NUM_MSGS;

        if ((args.length < 1) || (args.length > 2)) {
            System.err.println(
                    "Program takes one or two arguments: "
                    + "<dest_type> [<number-of-messages>]");
            System.exit(1);
        }

        String destType = args[0];
        System.out.println("Destination type is " + destType);

        if (!(destType.equals("queue") || destType.equals("topic"))) {
            System.err.println("Argument must be \"queue\" or " + "\"topic\"");
            System.exit(1);
        }

        if (args.length == 2) {
            NUM_MSGS = (new Integer(args[1]));
        } else {
            NUM_MSGS = 1;
        }

        Destination dest;

        try {
            if (destType.equals("queue")) {
                dest = queue;
            } else {
                dest = topic;
            }

            /*
             * Within a try-with-resources block, create context.
             * Create producer and message.
             * Send messages, varying text slightly.
             * Send end-of-messages message.
             */
            try (JMSContext context = connectionFactory.createContext();) {
                int count = 0;

                for (int i = 0; i < NUM_MSGS; i++) {
                    String message = "This is message " + (i + 1)
                            + " from producer";
                    // Comment out the following line to send many messages
                    System.out.println("Sending message: " + message);
                    context.createProducer().send(dest, message);
                    count += 1;
                }
                System.out.println("Text messages sent: " + count);

                /*
                 * Send a non-text control message indicating end of
                 * messages.
                 */
                context.createProducer().send(dest, context.createMessage());
                // Uncomment the following line if you are sending many messages
                // to two synchronous consumers
                //context.createProducer().send(dest, context.createMessage());
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
