/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chatserver;

import java.io.IOException;
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
 *
 * @author vongenae
 */
public class ChatServer implements Runnable {

    private static final int BUFFER_SIZE = 255;
    private final ServerSocketChannel serverSocketChannel;
    private Selector inputSelector;
    private boolean running;
    private final LinkedList<SocketChannel> clients;
    private final ByteBuffer writeBuffer;
    private final ByteBuffer readBuffer;
    private final CharsetDecoder asciiDecoder;

    public ChatServer(ServerSocketChannel serverSocketChannel) {
        this.serverSocketChannel = serverSocketChannel;
        running = true;
        clients = new LinkedList<>();
        writeBuffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
        readBuffer = ByteBuffer.allocateDirect(BUFFER_SIZE);
        asciiDecoder = Charset.forName("US-ASCII").newDecoder();
    }

    @Override
    public void run() {
        try {
            // get a selector for multiplexing the client channels
            inputSelector = Selector.open();
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.register(inputSelector, SelectionKey.OP_ACCEPT);
            while (running) {
                waitForInput();
            }
        } catch (IOException ex) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    protected void stop() {
        running = false;
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
            }
        } catch (IOException ex) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void addNewClient(SelectionKey key) {
        try {
            ServerSocketChannel channel = (ServerSocketChannel) key.channel();
            SocketChannel clientChannel = channel.accept();
            String newData = "welkom";
            ByteBuffer buf = ByteBuffer.allocate(48);
            buf.clear();
            buf.put(newData.getBytes());
            // data schrijven
            buf.flip();
            while (buf.hasRemaining()) {
                clientChannel.write(buf);
            }

            Logger.getLogger(ChatServer.class.getName()).log(Level.INFO, "got connection from: {0}", clientChannel.socket().getInetAddress());
            sendBroadcastMessage("login from: " + clientChannel.socket().getInetAddress(), clientChannel);
            sendMessage(clientChannel, "\n\nWelcome to ChatterBox, there are "
                    + clients.size() + " users online.\n");
            sendMessage(clientChannel, "Type 'quit' to exit.\n");

            // add to our list
            clients.add(clientChannel);

            // register the channel with the selector
            // store a new StringBuffer as the Key's attachment for holding partially read messages
            clientChannel.configureBlocking(false);
            clientChannel.register(inputSelector, SelectionKey.OP_READ, new StringBuffer());
        } catch (IOException ex) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, "problemen bij afhandelen client", ex);
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
                Logger.getLogger(ChatServer.class.getName()).log(Level.INFO, "disconnect: {0}, end-of-stream", channel.socket().getInetAddress());
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
                        Logger.getLogger(ChatServer.class.getName()).log(Level.INFO, "got quit msg, closing channel for : {0}", channel.socket().getInetAddress());
                        channel.close();
                        clients.remove(channel);
                        sendBroadcastMessage("logout: " + channel.socket().getInetAddress(), channel);
                    } else {
                        // got one, send it to all clients
                        Logger.getLogger(ChatServer.class.getName()).log(Level.INFO, "broadcasting: {0}", line);
                        sendBroadcastMessage(channel.socket().getInetAddress() + ": " + line, channel);
                        sb.delete(0, sb.length());
                    }
                }
            }

        } catch (IOException ioe) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.WARNING, "error during select(): {0}", ioe.getMessage());
        } catch (Exception e) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, "exception in run(){0}", e.getMessage());
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
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, null, ex);
        }

        // get ready for another write if needed
        writeBuffer.rewind();
    }

}
