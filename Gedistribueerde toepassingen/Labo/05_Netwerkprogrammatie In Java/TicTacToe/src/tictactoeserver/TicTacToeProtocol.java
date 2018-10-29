package tictactoeserver;

public class TicTacToeProtocol {

    public static final String WAITING = "WAITING";
    public static final String MESSAGE = "MESSAGE";
    public static final String MOVE = "MOVE";
    public static final String SYMBOL = "SYMBOL";

    private final char delimiter = ';';

    // assume for now that every message will have a correct format
    public TicTacToeProtocolMessage read(String line) {
        System.err.println(line);
        String[] pieces = line.split(String.valueOf(delimiter));
        return new TicTacToeProtocolMessage(pieces[0], pieces[1]);
    }

    public TicTacToeProtocolMessage build(String command, String message) {
        return new TicTacToeProtocolMessage(command, message);
    }

    public class TicTacToeProtocolMessage {

        public String command;
        public String message;

        public TicTacToeProtocolMessage(String command, String message) {
            this.command = command;
            this.message = message;
        }

        @Override
        public String toString() {
            return String.format("%s%c%s\n", command, delimiter, message);
        }

    }

}
