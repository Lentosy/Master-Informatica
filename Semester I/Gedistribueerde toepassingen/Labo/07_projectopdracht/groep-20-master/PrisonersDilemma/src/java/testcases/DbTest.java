/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testcases;

import PrisonerDilemma.PDGame;
import PrisonerDilemma.PDRealGame;
import groep20.models.Game;
import groep20.persistence.DatabaseWrapper;
import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author counterpoint
 */
public class DbTest {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {

            DatabaseWrapper db = new DatabaseWrapper();

            PDGame game = new PDRealGame("bert", "thomas");
            for (int i = 0; i < 30; i++) {
                int x = 1, y = 1;
                if (Math.random() < 0.5) {
                    x = 0;
                }
                if (Math.random() < 0.5) {
                    y = 0;
                }
                game.playRound(x, y);
            }
              db.saveGame(game);   
            game = new PDRealGame("veerle", "thomas");
            for (int i = 0; i < 30; i++) {
                int x = 1, y = 1;
                if (Math.random() < 0.5) {
                    x = 0;
                }
                if (Math.random() < 0.5) {
                    y = 0;
                }
                game.playRound(x, y);
            }
              db.saveGame(game);   
            List<Game> games = db.getAllGames();
            for (int i = 0; i < games.size(); i++) {
                Game getGame = games.get(i);

                System.out.println(getGame.toString());
            }
        } catch (SQLException ex) {
            Logger.getLogger(DbTest.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
