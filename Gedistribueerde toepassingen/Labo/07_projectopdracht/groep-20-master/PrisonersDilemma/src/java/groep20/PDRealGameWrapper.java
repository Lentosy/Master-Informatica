/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20;

import PrisonerDilemma.PDComputerGame;
import PrisonerDilemma.PDRealGame;
import PrisonerDilemma.Player;
import PrisonerDilemma.ResultRound;
import com.google.gson.Gson;
import java.io.IOException;
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
public class PDRealGameWrapper extends PDGameWrapper {

    private PDRealGame pdgame;
    private PDPlayerWrapper playerB;

    public PDRealGameWrapper(Session sessionA, String namePlayer) {
        super(sessionA, namePlayer);
    }

    public void addSecondPlayer(Session sessionB, String namePlayer) {
        this.playerB = new PDPlayerWrapper(sessionB, namePlayer);
        this.pdgame = new PDRealGame(playerA.getNamePlayer(), playerB.getNamePlayer());
    }

  

    /**
     *
     * @param UUID
     * @param decision
     * @throws Exception
     */
    @Override
    protected void addDecision(String UUID, int decision) throws Exception {
        if (getPlayerAUuid() == UUID) {
            playerA.setDecision(decision);
        } else if (getPlayerBUuid() == UUID) {
            playerB.setDecision(decision);
        } else {
            throw new Exception("Player does not exist in this game");
        }

        if (AllPlayersHaveDecided()) {
            handleWinner();
        } else {
            System.out.printf("waiting for other player. Player a: %d and player B: %d\n", playerA.getDecision(), playerB.getDecision());
        }

    }

    public void broadCastMessage(String key, String message) {
        String gameEndingMessage = Json.createObjectBuilder()
                .add(key, message)
                .build()
                .toString();
        try {
            playerA.getSession().getBasicRemote().sendText(gameEndingMessage);
            playerB.getSession().getBasicRemote().sendText(gameEndingMessage);
        } catch (IOException ex) {
            Logger.getLogger(PDRealGameWrapper.class.getName()).log(Level.SEVERE, "could not send broadcast message");
        }

    }

    public String getPlayerBUuid() {
        return playerB.getUUID();
    }

    private Boolean AllPlayersHaveDecided() {
        return playerA.hasDecision() && playerB.hasDecision();
    }

    @Override
    protected void handleWinner() {
        try {
            ResultRound[] roundResult = pdgame.playRound(playerA.getAndClearDecision(), playerB.getAndClearDecision());

            String responseContentA = Json.createObjectBuilder()
                    .add(ROUND_RESULT_KEY, roundResult[0].getMessage().replace("\n", " "))
                    .add(ROUND_KEY, this.round)
                    .build()
                    .toString();

            String responseContentB = Json.createObjectBuilder()
                    .add(ROUND_RESULT_KEY, roundResult[1].getMessage().replace("\n", " "))
                    .add(ROUND_KEY, this.round)
                    .build()
                    .toString();

            playerA.getSession().getBasicRemote().sendText(responseContentA);
            playerB.getSession().getBasicRemote().sendText(responseContentB);

            System.out.println("Result for name1");
            System.out.println(responseContentA);
            System.out.println("Result for name2");
            System.out.println(responseContentB);
            if (round == MAX_ROUNDS) {
                Gson gson = new Gson();
                String responseContent = Json.createObjectBuilder().add(END_GAME_KEY, gson.toJson(pdgame)).build().toString();
                playerA.getSession().getBasicRemote().sendText(responseContent);
                playerB.getSession().getBasicRemote().sendText(responseContent);
                db.saveGame(pdgame);
            } else {
                this.round++;
            }

        } catch (Exception ex) {
            Logger.getLogger(PDGameWrapper.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
