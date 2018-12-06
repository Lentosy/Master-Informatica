package auctionserver;

import auctionserver.model.Auction;
import auctionserver.model.Offer;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.ConnectionFactory;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.Queue;

/**
 *
 * @author counterpoint
 */
public class AuctionManager implements Runnable {
    
    private static final int BUFFER_SIZE = 255;
    private static final int MESSAGE_SIZE = 500;

    private boolean running;
    private List<SocketChannel> clients;
    private Selector inputSelector;
    private final ServerSocketChannel serverSocketChannel;
    private final Queue queue;
    private final JMSContext context;
    private final Auction auction;
    private Offer offer;

    AuctionManager(ConnectionFactory connectionFactory, Queue queue, ServerSocketChannel serverSocketChannel) {
        context = connectionFactory.createContext();
        this.queue = queue;
        this.serverSocketChannel = serverSocketChannel;

        running = true;

        auction = new Auction();
        clients = new ArrayList<SocketChannel>();

    }

    @Override
    public void run() {
        try {
            inputSelector = Selector.open(); // Selector aanmaken
            serverSocketChannel.configureBlocking(false); // Het Channel object MOET in non-blocking mode staan om met een selector te kunnen werken
            serverSocketChannel.register(inputSelector, SelectionKey.OP_ACCEPT); // de SelectionKey.OP_ACCEPT zegt dat we enkel geïnteresseerd zijn in nieuwe connecties voor dit kanaal

            while (running) {
                waitForInput();
            }

        } catch (IOException ex) {
            Logger.getLogger(AuctionManager.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                context.close();
                serverSocketChannel.close();
            } catch (IOException ex) {
                Logger.getLogger(AuctionManager.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private void waitForInput() {
        try {
            int readyChannels = inputSelector.select();
            if (readyChannels != 0) {
                inputSelector.selectedKeys().forEach((key) -> {
                    if (key.isAcceptable()) {
                        addNewClient(key);
                    } else if (key.isReadable()) {
                        readIncomingMessages(key);
                    }
                });
                inputSelector.selectedKeys().clear();
            }
        } catch (IOException ex) {
            Logger.getLogger(AuctionManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void readIncomingMessages(SelectionKey key) {
        
        ServerSocketChannel channel = (ServerSocketChannel) key.channel();
        StringBuffer name = (StringBuffer) key.attachment();
        
        ByteBuffer readBuffer = ByteBuffer.allocate(BUFFER_SIZE);
        readBuffer.clear();
    }

    private void addNewClient(SelectionKey key) {
        try {
            ServerSocketChannel channel = (ServerSocketChannel) key.channel();
            SocketChannel clientChannel = channel.accept();

            Logger.getLogger(AuctionManager.class.getName()).log(Level.INFO, "got connection from: {0}", clientChannel.socket().getInetAddress());

            clients.add(clientChannel);
            clientChannel.configureBlocking(false);
            clientChannel.register(inputSelector, SelectionKey.OP_READ, new StringBuffer());
            

        } catch (IOException ex) {
            Logger.getLogger(AuctionManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private void sendMessage(String data, SocketChannel clientChannel) throws IOException {
        ByteBuffer buf = ByteBuffer.allocate(BUFFER_SIZE);
        buf.clear();
        buf.put(data.getBytes());
        buf.flip();
       
        while(buf.hasRemaining()){
            clientChannel.write(buf);
        }
    }

    public void stop() {

    }

    private void newOffer() {

    }

    /**
     * Send a message to the Queue that an item is sold
     *
     * @param offer
     */
    private void registerItemSold(Offer offer) {
        try {
            Message message = context.createTextMessage("ITEM " + offer.getItem().getId() + " SOLD BY " + offer.getClient() + " FOR " + offer.getCurrentOffer());
            message.setBooleanProperty("SOLD", true);
            context.createProducer().send(queue, message);
        } catch (JMSException ex) {
            Logger.getLogger(AuctionManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
