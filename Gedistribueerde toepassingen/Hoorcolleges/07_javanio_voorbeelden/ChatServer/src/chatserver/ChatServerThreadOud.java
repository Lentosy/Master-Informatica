/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chatserver;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.util.LinkedList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Gebaseerd op ChatterServer.java
 *
 * A basic example of a multi-user chat application using the JDK 1.4 NIO
 * libraries
 *
 * @author <a href="mailto:bret@hypefiend.com">bret barker</a>
 * @version 1.0
 *
 * @author vongenae
 */
public class ChatServerThreadOud extends Thread {

    private static final int BUFFER_SIZE = 255;
    private static final int PORT = 4444;

    private static final Logger log = Logger.getLogger(ChatServerThreadOud.class.getName());
    private ServerSocketChannel sSockChan;
    private Selector inputSelector;
    private boolean running;
    private final LinkedList<SocketChannel> clients;
    private final ByteBuffer readBuffer;
    private final ByteBuffer writeBuffer;
    private final CharsetDecoder asciiDecoder;

    public ChatServerThreadOud() {
        clients = new LinkedList<>();
        readBuffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
        writeBuffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
        asciiDecoder = Charset.forName("US-ASCII").newDecoder();
    }

    private void initServerSocket() {
        try {
            // open a non-blocking server socket channel
            sSockChan = ServerSocketChannel.open();
//            sSockChan.configureBlocking(false);

            // bind to localhost on designated port
            InetAddress addr = InetAddress.getLocalHost();
            sSockChan.socket().bind(new InetSocketAddress(addr, PORT));

            // get a selector for multiplexing the client channels
//            inputSelector = Selector.open();
//            sSockChan.register(inputSelector, SelectionKey.OP_ACCEPT);
        } catch (Exception e) {
            log.log(Level.SEVERE, "error initializing server", e);
        }
    }

    @Override
    public void run() {
        initServerSocket();

        log.info("ChatterServer running");
        running = true;

        // block while we wait for a client to connect
        while (running) {
            try {
                SocketChannel client = sSockChan.accept();
                prepWriteBuffer("hallo");
                channelWrite(client, writeBuffer);
                // check for new client an incoming messages connections
//            waitForInput();
            } catch (IOException ex) {
                Logger.getLogger(ChatServerThreadOud.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private void waitForInput() {
        try {
            int readyChannels = inputSelector.select();
            if (readyChannels != 0) {
                for (SelectionKey selectedKey : inputSelector.selectedKeys()) {
                    if (selectedKey.isAcceptable()) {
                        // a connection was accepted by a ServerSocketChannel.
                        addNewClient((SocketChannel) selectedKey.channel());
                    } else if (selectedKey.isReadable()) {
                        // a channel is ready for reading
                        readIncomingMessages(selectedKey);
                    }
                }
            }
        } catch (IOException ex) {
            log.log(Level.SEVERE, null, ex);
        }
    }

    private void readIncomingMessages(SelectionKey key) {
        try {
            SocketChannel channel = (SocketChannel) key.channel();
            readBuffer.clear();

            // read from the channel into our buffer
            long nbytes = channel.read(readBuffer);

            // check for end-of-stream
            if (nbytes == -1) {
                log.log(Level.INFO, "disconnect: {0}, end-of-stream", channel.socket().getInetAddress());
                channel.close();
                clients.remove(channel);
                sendBroadcastMessage("logout: " + channel.socket().getInetAddress(), channel);
            } else {
                // grab the StringBuffer we stored as the attachment
                StringBuffer sb = (StringBuffer) key.attachment();
                // use a CharsetDecoder to turn those bytes into a string
                // and append to our StringBuffer
                readBuffer.flip();
                String str = asciiDecoder.decode(readBuffer).toString();
                readBuffer.clear();
                sb.append(str);

                // check for a full line
                String line = sb.toString();
                if ((line.contains("\n")) || (line.contains("\r"))) {
                    line = line.trim();
                    if (line.startsWith("quit")) {
                        // client is quitting, close their channel, remove them from the list and notify all other clients
                        log.log(Level.INFO, "got quit msg, closing channel for : {0}", channel.socket().getInetAddress());
                        channel.close();
                        clients.remove(channel);
                        sendBroadcastMessage("logout: " + channel.socket().getInetAddress(), channel);
                    } else {
                        // got one, send it to all clients
                        log.log(Level.INFO, "broadcasting: {0}", line);
                        sendBroadcastMessage(channel.socket().getInetAddress() + ": " + line, channel);
                        sb.delete(0, sb.length());
                    }
                }
            }

        } catch (IOException ioe) {
            log.log(Level.WARNING, "error during select(): {0}", ioe.getMessage());
        } catch (Exception e) {
            log.log(Level.SEVERE, "exception in run(){0}", e.getMessage());
        }

    }

    private void addNewClient(SocketChannel chan) {
        try {
            log.log(Level.INFO, "got connection from: {0}", chan.socket().getInetAddress());
            sendBroadcastMessage("login from: " + chan.socket().getInetAddress(), chan);
            sendMessage(chan, "\n\nWelcome to ChatterBox, there are "
                    + clients.size() + " users online.\n");
            sendMessage(chan, "Type 'quit' to exit.\n");

            // add to our list
            clients.add(chan);

            // register the channel with the selector
            // store a new StringBuffer as the Key's attachment for holding partially read messages
            chan.configureBlocking(false);
            chan.register(inputSelector, SelectionKey.OP_READ, new StringBuffer());
        } catch (IOException ex) {
            Logger.getLogger(ChatServerThreadOud.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    private void sendMessage(SocketChannel channel, String mesg) {
        prepWriteBuffer(mesg);
        channelWrite(channel, writeBuffer);
    }

    private void sendBroadcastMessage(String mesg, SocketChannel from) {
        prepWriteBuffer(mesg);
        for (SocketChannel channel : clients) {
            if (channel != from) {
                channelWrite(channel, writeBuffer);
            }
        }
    }

    private void prepWriteBuffer(String mesg) {
        // fills the buffer from the given string
        // and prepares it for a channel write
        writeBuffer.clear();
        writeBuffer.put(mesg.getBytes());
        writeBuffer.putChar('\n');
        writeBuffer.flip();
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
            Logger.getLogger(ChatServerThreadOud.class.getName()).log(Level.SEVERE, null, ex);
        }

        // get ready for another write if needed
        writeBuffer.rewind();
    }

}
