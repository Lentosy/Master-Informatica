/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package auctionserver;

import auctionserver.model.Auction;
import auctionserver.model.Item;
import auctionserver.model.Offer;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.util.LinkedList;
import java.util.Timer;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.ConnectionFactory;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.Queue;

/**
 *
 * @author vongenae
 */
public class AuctionThread implements Runnable {

    private static final int BUFFER_SIZE = 255;
    private static final int MESSAGE_SIZE = 500;
    private static final int INTERVAL = 60 * 1000;
    private final ServerSocketChannel serverSocketChannel;
    private Selector inputSelector;
    private boolean running;
    private final LinkedList<SocketChannel> clients;
    private final CharsetDecoder asciiDecoder;
    private final Queue queue;
    private final Timer timer;
    private final JMSContext context;
    private final Auction auction;
    private Offer offer;
    private WaitForOffer waitForOffer;

    public AuctionThread(ConnectionFactory connectionFactory, Queue queue, ServerSocketChannel serverSocketChannel) {
        context = connectionFactory.createContext();
        auction = new Auction();
        this.queue = queue;
        this.serverSocketChannel = serverSocketChannel;
        running = true;
        clients = new LinkedList<>();
        asciiDecoder = Charset.forName("US-ASCII").newDecoder();
        timer = new Timer();
    }

    @Override
    public void run() {
        try {
            // get a selector for multiplexing the client channels
            inputSelector = Selector.open();
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.register(inputSelector, SelectionKey.OP_ACCEPT);
            newOffer();
            while (running) {
                waitForInput();
            }
        } catch (IOException ex) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            context.close();
            try {
                serverSocketChannel.close();
            } catch (IOException ex) {
                Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public void stop() {
        running = false;
        waitForOffer.cancel();
        timer.purge();
        inputSelector.wakeup();
    }

    private void waitForInput() {
        try {
            int readyChannels = inputSelector.select();
            if (readyChannels != 0) {
                for (SelectionKey selectedKey : inputSelector.selectedKeys()) {
                    if (selectedKey.isAcceptable()) {
                        addNewClient(selectedKey);
                    } else if (selectedKey.isReadable()) {
                        // a channel is ready for reading
                        readIncomingMessages(selectedKey);
                    }
                }
                inputSelector.selectedKeys().clear();
            } else { // timer finished
                finishOffer();
                newOffer();
            }
        } catch (IOException ex) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void addNewClient(SelectionKey key) {
        try {
            ServerSocketChannel channel = (ServerSocketChannel) key.channel();
            SocketChannel clientChannel = channel.accept();
            sendMessage("Welkom ", clientChannel);

            Logger.getLogger(AuctionThread.class.getName()).log(Level.INFO, "got connection from: {0}", clientChannel.socket().getInetAddress());

            // add to our list
            clients.add(clientChannel);

            // register the channel with the selector
            // store a new StringBuffer as the Key's attachment for holding partially read messages
            clientChannel.configureBlocking(false);
            clientChannel.register(inputSelector, SelectionKey.OP_READ, new StringBuffer());
            
        } catch (IOException ex) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, "new client problems ", ex);
        }
    }

    private void sendMessage(String newData, SocketChannel clientChannel) throws IOException {
        ByteBuffer buf = ByteBuffer.allocate(MESSAGE_SIZE);
        buf.clear();
        buf.put(newData.getBytes());
        // send welcome
        buf.flip();
        while (buf.hasRemaining()) {
            clientChannel.write(buf);
        }
    }

    private void readIncomingMessages(SelectionKey key) {

        try {
            SocketChannel channel = (SocketChannel) key.channel();

            // grab the StringBuffer we stored as the attachment
            StringBuffer name = (StringBuffer) key.attachment();

            ByteBuffer readBuffer = ByteBuffer.allocate(BUFFER_SIZE);
            readBuffer.clear();

            // read from the channel into our buffer
            long nbytes = channel.read(readBuffer);

            // check for end-of-stream
            if (nbytes == -1) {
                Logger.getLogger(AuctionThread.class.getName())
                        .log(Level.INFO, "disconnect: {0} from {1}, end-of-stream",
                                new Object[]{name, channel.socket().getInetAddress()});
                channel.close();
                clients.remove(channel);
            } else {
                // use a CharsetDecoder to turn those bytes into a string
                // and append to our StringBuffer
                readBuffer.flip();
                String line = asciiDecoder.decode(readBuffer).toString();
                readBuffer.clear();

                if (line.startsWith("QUIT")) {
                    // client is quitting, close their channel, remove them from the list and notify all other clients
                    Logger.getLogger(AuctionThread.class.getName())
                            .log(Level.INFO, "got quit msg, closing channel for : {0} from {1}",
                                    new Object[]{name, channel.socket().getInetAddress()});
                    channel.close();
                    clients.remove(channel);
                } else if (name.length() == 0) { // not registered
                    if (line.startsWith("REGISTER")) {
                        String[] tokens = line.split(" ");
                        name.append(tokens[1].trim());
                        sendMessage(messageOffer(offer.getItem()).toString(), channel);
                        sendMessage("CURRENT OFFER " + offer.getCurrentOffer(), channel);
                    } else {
                        sendMessage("REGISTER FIRST ", channel);
                    }
                } else if (line.startsWith("OFFER")) { // registered
                    int spatie = line.indexOf(' '); // first space
                    line = line.substring(spatie + 1); // OFFER removed
                    String amountString = line.trim();
                    try {
                        double amount = Double.parseDouble(amountString);
                        if (offer.offerAccepted(name.toString(), amount)) {
                            sendBroadcastMessage("OFFER FROM " + name + ": " + amount);
                            waitForOffer.cancel();
                            //timer.cancel();
                            waitForOffer = new WaitForOffer(inputSelector);
                            timer.schedule(waitForOffer, INTERVAL);
                        } else {
                            sendMessage("OFFER DENIED", channel);
                        }
                        Logger.getLogger(AuctionThread.class.getName())
                                .log(Level.INFO, "got offer msg for offer {0} from {1}: {2} ",
                                        new Object[]{offer.getItem(), name, amount});
                    } catch (NumberFormatException nfex) {
                        sendMessage("OFFER NOT VALID", channel);
                    }
                } else {
                    Logger.getLogger(AuctionThread.class.getName())
                            .log(Level.INFO, "wrong command: {0} from {1} ",
                                    new Object[]{name, channel.socket().getInetAddress()});
                    sendMessage("WRONG COMMAND", channel);
                }
            }
        } catch (IOException ioe) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.WARNING, "error during select(): {0}", ioe.getMessage());
        } catch (Exception e) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, "exception in run(){0}", e.getMessage());
        }

    }

    private void sendBroadcastMessage(String mesg) {

        ByteBuffer writeBuffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
        // fills the buffer from the given string
        // and prepares it for a channel write
        writeBuffer.clear();
        writeBuffer.put(mesg.getBytes());
        writeBuffer.putChar('\n');
        writeBuffer.flip();
        for (SocketChannel channel : clients) {
            channelWrite(channel, writeBuffer);
        }
    }

    private void channelWrite(SocketChannel channel, ByteBuffer writeBuffer) {
        long nbytes = 0;
        long toWrite = writeBuffer.remaining();

        // loop on the channel.write() call since it will not necessarily
        // write all bytes in one shot
        try {
            while (nbytes != toWrite) {
                nbytes += channel.write(writeBuffer);

            }
        } catch (IOException ex) {
            Logger.getLogger(AuctionThread.class
                    .getName()).log(Level.SEVERE, null, ex);
        }

        // get ready for another write if needed
        writeBuffer.rewind();
    }

    private void finishOffer() {
        StringBuilder message = new StringBuilder();
        message.append("ITEM");
        message.append(offer.getItem().getDescription());
        if (offer.getClient() != null) {
            message.append(" SOLD TO ");
            message.append(offer.getClient());
            message.append(" FOR ");
            message.append(offer.getCurrentOffer());
            registerItemSold(offer);
        } else {
            message.append(" NOT SOLD");
            registerItemNotSold(offer);
        }
        sendBroadcastMessage(message.toString());
    }

    private void newOffer() {
        Item item = auction.getItem();
        if (item != null) {
            broadcastOffer(item);
            offer = new Offer(item);
            waitForOffer = new WaitForOffer(inputSelector);
            timer.schedule(waitForOffer, INTERVAL);
        } else {
            stop();
        }
    }

    private void broadcastOffer(Item item) {
        StringBuilder message = messageOffer(item);
        sendBroadcastMessage(message.toString());
    }

    private StringBuilder messageOffer(Item item) {
        StringBuilder message = new StringBuilder();
        message.append("ITEM ");
        int id = item.getId();
        message.append(id);
        message.append(" ");
        message.append(item.getDescription());
        message.append(" MINIMUM PRICE");
        message.append(item.getMinPrice());
        return message;
    }

    private void registerItemNotSold(Offer offer) {
        try {
            Message message = context.createTextMessage("NOT SOLD " + offer.getItem().getId()
                    + " LAST OFFER " + offer.getCurrentOffer());
            message.setBooleanProperty("SOLD", false);
            context.createProducer().send(queue, message);
        } catch (JMSException ex) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void registerItemSold(Offer offer) {
        try {
            Message message = context.createTextMessage("ITEM " + offer.getItem().getId()
                    + " SOLD BY " + offer.getClient() + " FOR " + offer.getCurrentOffer());
            message.setBooleanProperty("SOLD", true);
            context.createProducer().send(queue, message);
        } catch (JMSException ex) {
            Logger.getLogger(AuctionThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
