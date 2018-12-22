/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20;

import static com.sun.xml.ws.spi.db.BindingContextFactory.LOGGER;
import javax.enterprise.context.ApplicationScoped;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.websocket.Session;

/**
 *
 * @author thomas
 */
@ApplicationScoped
public class PDGameSessionHandler {

    //private TwoKeyHash<String, PDRealGame> UIDToGame = new TwoKeyHash<>();
    private LinkedList<PDGameWrapper> games = new LinkedList<>();

    //private HashMap<String, Integer> UIDToDecision = new HashMap<>();
    // all games with only one player, waiting for a second one
    // normally only one player should be in this queue.
    private Queue<PDRealGameWrapper> waitingGames = new LinkedBlockingQueue<>();

    public void removeSession(String userID) {
        PDGameWrapper current = findGameByUUID(userID);
           if(current != null){
               if(current instanceof PDRealGameWrapper){
                ((PDRealGameWrapper) current).broadCastMessage("GAMESTATUS","your opponent disconnected");
                 }
               games.remove(current);
        } else {
            Logger.getLogger(PDGameSessionHandler.class.getName()).log(Level.SEVERE, "Trying to remove session but it was not found, nothing to do ");
        }
    }

    void addDecision(String UUID, int decision) {

        try {
            PDGameWrapper current = findGameByUUID(UUID);
            if(current == null){
                 throw new Exception("Could not find Game by it's UUID");
            }
            current.addDecision(UUID, decision);
        } catch (Exception ex) {
            Logger.getLogger(PDGameSessionHandler.class.getName()).log(Level.SEVERE, "error in addDecision (custom)", ex);
            Logger.getLogger(PDGameSessionHandler.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private PDGameWrapper findGameByUUID(String UUID) {
        int num = 0;
        while (games.size() > num) {
            if (UUID == games.get(num).getPlayerAUuid()) {
                return games.get(num);
            }
            if (games.get(num) instanceof PDRealGameWrapper && UUID == ((PDRealGameWrapper) games.get(num)).getPlayerBUuid()) {
                return games.get(num);

            }
            num++;

        }
        return null;

    }

    // add a PDRealGame or PDComputerGame based on users choice
    public void addSession(Session session, Boolean isRealGame, String namePlayer) {
        LOGGER.log(Level.INFO, session.getId());
        LOGGER.log(Level.INFO, "isrealgame: "+ isRealGame);
        LOGGER.log(Level.INFO, "name player:"+ namePlayer);
        if (findGameByUUID(session.getId()) != null) {
            LOGGER.log(Level.WARNING, "Player already connected, nothing to do");
            return;
        }
       
        if (!isRealGame) {
            LOGGER.log(Level.INFO, "Single player {0}", session.getId());
            Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "Single player");

            games.push(new PDComputerGameWrapper(session,namePlayer));
        } else if (waitingGames.isEmpty()) {
            // no waiting games, so this new game will be waiting
            waitingGames.add(new PDRealGameWrapper(session,namePlayer));
            Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "player in waiting state");
            LOGGER.log(Level.INFO, "{0} is in waiting state", session.getId());

        } else {
            // a game with a player is already waiting. This game has just received his second player.
            PDRealGameWrapper currentGame = waitingGames.remove();
            currentGame.addSecondPlayer(session,namePlayer);
            currentGame.broadCastMessage("GAMESTATUS", "You have been connected with annother player");
            games.push(currentGame);
            
            Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "player connected to annother player");
            LOGGER.log(Level.INFO, "{0} connected to {1}", new Object[]{currentGame.getPlayerAUuid(), currentGame.getPlayerBUuid()});
        }
    }
}
