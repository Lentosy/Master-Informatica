package tictactoeserver;

public class Game {

    private Player board[];

    public Player currentPlayer;

    public Game() {
        board = new Player[9];
    }

    /*
    -------------
    | 0 | 1 | 2 |
    -------------
    | 3 | 4 | 5 |
    -------------
    | 6 | 7 | 8 |
    
     */
    public boolean IsWinConditionAchieved() {
        int[][] winConditions = { // the indices of the board that has to be equal to consider a win
            {0, 1, 2},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {3, 4, 5},
            {6, 7, 8},
            {0, 4, 8},
            {6, 4, 2}
        };
        for (int[] wincondition : winConditions) {
            if (wincondition[0] == wincondition[1] && wincondition[0] == wincondition[2]) {
                return true;
            }
        }
        return false;
    }

    public synchronized boolean move(int location, Player player) {
        if (player == currentPlayer && board[location] == null) { // move is OK when the location is empty
            board[location] = currentPlayer;
            currentPlayer = currentPlayer.getOpponent();
            currentPlayer.otherPlayerMoved(location);
            return true;
        }
        // else the move is NOT OK
        return false;
    }

    public boolean isBoardFull() {
        for (Player p : board) {
            if (p == null) {
                return false;
            }
        }
        return true;
    }

}
