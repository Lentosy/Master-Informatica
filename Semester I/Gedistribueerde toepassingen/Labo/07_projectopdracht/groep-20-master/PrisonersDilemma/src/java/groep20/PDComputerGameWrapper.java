/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20;

import PrisonerDilemma.PDComputerGame;
import PrisonerDilemma.ResultRound;
import com.google.gson.Gson;
import java.math.BigDecimal;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.json.Json;
import javax.websocket.Session;

/**
 *
 * @author thomas
 *
 */
public class PDComputerGameWrapper extends PDGameWrapper {

    private final PDComputerGame pdgame;

    public PDComputerGameWrapper(Session sessionA, String namePlayer) {
        super(sessionA, namePlayer);
        this.pdgame = new PDComputerGame(namePlayer);
    }

    /**
     *
     * @param UUID
     * @param decision
     * @throws Exception
     */
    @Override
    protected void addDecision(String UUID, int decision) throws Exception {
        playerA.setDecision(decision);
        Logger.getLogger(PDGameSessionHandler.class.getName()).log(Level.INFO, "added decision, calling handleWinner()");
        handleWinner();

    }

    @Override
    protected void handleWinner() {
        try {
        Logger.getLogger(PDGameSessionHandler.class.getName()).log(Level.INFO, "handleWinner()");
       
            ResultRound[] result = pdgame.
                    playRound(playerA.getAndClearDecision());

            String responseContent = Json.createObjectBuilder()
                    .add(ROUND_RESULT_KEY, result[0].getMessage().replace("\n", " "))
                    .add(ROUND_KEY, this.round)
                    .build()
                    .toString();

            playerA.getSession().getBasicRemote().sendText(responseContent);
            System.out.print("Result for name1: ");
            System.out.println(responseContent);
            if (round == MAX_ROUNDS) {
                Gson gson = new Gson();
                responseContent = Json.createObjectBuilder().add(END_GAME_KEY, gson.toJson(pdgame)).build().toString();
                playerA.getSession().getBasicRemote().sendText(responseContent);
                db.saveGame(pdgame);
            } else {
                this.round++;
            }

        } catch (Exception ex) {
            Logger.getLogger(PDGameWrapper.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
