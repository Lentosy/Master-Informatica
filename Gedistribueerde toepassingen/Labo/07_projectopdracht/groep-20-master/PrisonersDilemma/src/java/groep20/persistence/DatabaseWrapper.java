package groep20.persistence;

import PrisonerDilemma.PDGame;
import PrisonerDilemma.Player;
import groep20.models.Game;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author counterpoint
 */
public class DatabaseWrapper {

    private static String url = "jdbc:mariadb://group20-DB:3306/PrisonersDilemma";
    private Connection connection;
    private static String uName = "groep20";
    private static String uPass= " test";

    public DatabaseWrapper() {
        try {
            Class.forName("org.mariadb.jdbc.Driver").newInstance();
             Logger.getLogger(DatabaseWrapper.class.getName()).log(Level.SEVERE, "CONNECTING TO DB!!!!!!!!!!!!!!");
    
            connection = DriverManager.getConnection(url,uName, null);
            Logger.getLogger(DatabaseWrapper.class.getName()).log(Level.SEVERE, "v2.1 - Trying to connect " + url);
        } catch (ClassNotFoundException | SQLException | InstantiationException | IllegalAccessException ex) {
       
            Logger.getLogger(DatabaseWrapper.class.getName()).log(Level.SEVERE, null, ex);
        }
    }


    public void saveGame(PDGame game) throws SQLException {
        try (Statement statement = connection.createStatement()) {
            String gameInsert = "INSERT INTO GAME (NAME_PLAYER_ONE, NAME_PLAYER_TWO) VALUES ('"
                    + game.getPlayer1().getName() + "','" + game.getPlayer2().getName()
                    + "')";
            statement.execute(gameInsert, Statement.RETURN_GENERATED_KEYS);
            ResultSet keys = statement.getGeneratedKeys();
            // zal maar 1 sleutel bevatten, die dat gegenereerd werd voor het spel
            keys.next();
            int key = keys.getInt(1);
            StringBuilder decisionInsert = new StringBuilder("INSERT INTO DECISION VALUES\n");
            Player player1 = game.getPlayer1();
            Player player2 = game.getPlayer2();
            for (int i = 0; i < 29; i++) {
                decisionInsert.append(
                        String.format("(%d, %d, %d, %d, %d, %d),\n",
                                key, i + 1, (player1.getChoiceHistory()).get(i), (player2.getChoiceHistory()).get(i), (player1.getScoreHistory()).get(i), (player2.getScoreHistory()).get(i))
                );
            }

            // laatste regel mag geen komma hebben bij de VALUES clausule
            int i = 29;
            decisionInsert.append(
                    String.format("(%d, %d, %d, %d, %d, %d)",
                            key, i + 1, (player1.getChoiceHistory()).get(i), (player2.getChoiceHistory()).get(i), (player1.getScoreHistory()).get(i), (player2.getScoreHistory()).get(i))
            );
            statement.execute(decisionInsert.toString());
        }
    }

    public List<Game> getAllGames() throws SQLException {
        List<Game> result = new ArrayList<>();
        try (Statement statement = connection.createStatement()) {

            ResultSet gameSet = statement.executeQuery("SELECT * FROM GAME JOIN DECISION ON ID = GAME_ID");
            iterateResultSet(gameSet, result);
        }
        return result;
    }

    public List<Game> getGamesForPlayer(String playerName) throws SQLException {
        List<Game> result = new ArrayList<>();
        try (Statement statement = connection.createStatement()) {

            ResultSet gameSet = statement.executeQuery("SELECT * FROM GAME JOIN DECISION ON ID = GAME_ID WHERE NAME_PLAYER_ONE = '" + playerName + "' OR NAME_PLAYER_TWO = '" + playerName + "'");
            iterateResultSet(gameSet, result);
        }
        return result;
    }

    /**
     * *
     * Iterates the resultset and filles the list of games
     *
     * @param gameSet
     * @param games List<Game> object that will be filled
     * @throws SQLException
     */
    private void iterateResultSet(ResultSet gameSet, List<Game> games) throws SQLException {

        while (gameSet.next()) {
            groep20.models.Player player1 = new groep20.models.Player();
            player1.setName(gameSet.getString("NAME_PLAYER_ONE"));
            groep20.models.Player player2 = new groep20.models.Player();
            player2.setName(gameSet.getString("NAME_PLAYER_TWO"));
            Game game = new Game(gameSet.getLong("ID"), player1, player2);
            for (int i = 0; i < 29; i++) {
                game.getPlayer1().getConvictions().add(gameSet.getInt("CONVICTION_PLAYER_ONE"));
                game.getPlayer1().getChoices().add(gameSet.getInt("DECISION_PLAYER_ONE"));
                game.getPlayer2().getConvictions().add(gameSet.getInt("CONVICTION_PLAYER_TWO"));
                game.getPlayer2().getChoices().add(gameSet.getInt("DECISION_PLAYER_TWO"));
                gameSet.next();
            }
            // LAATSTE KEER MAR GEEN GAMESET.NEXT() UITGEVOERD WORDEN, anders slagen we ronde 1 over van volgende game
            System.out.println("Adding round " + gameSet.getInt("ROUND") + " to game " + game.getId());
            game.getPlayer1().getConvictions().add(gameSet.getInt("CONVICTION_PLAYER_ONE"));
            game.getPlayer1().getChoices().add(gameSet.getInt("DECISION_PLAYER_ONE"));
            game.getPlayer2().getConvictions().add(gameSet.getInt("CONVICTION_PLAYER_TWO"));
            game.getPlayer2().getChoices().add(gameSet.getInt("DECISION_PLAYER_TWO"));

            games.add(game);
        }
    }
}
