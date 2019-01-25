/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20;

import groep20.persistence.DatabaseWrapper;
import javax.websocket.Session;

/**
 *
 * @author thomas
 */
public abstract class PDGameWrapper {
    protected final int MAX_ROUNDS = 30;
    
    protected final String ROUND_RESULT_KEY = "ROUND_RESULT";
    protected final String ROUND_KEY = "ROUND";
    protected final String END_GAME_KEY = "END_GAME";
    protected DatabaseWrapper db = new DatabaseWrapper();
    protected int round = 1;

    protected PDPlayerWrapper playerA;

    public PDGameWrapper(Session sessionA, String namePlayer) {
        this.playerA = new PDPlayerWrapper(sessionA, namePlayer);
    }

    public String getPlayerAUuid() {
        return playerA.getUUID();
    }

    protected abstract void addDecision(String UUID, int decision) throws Exception;

    protected abstract void handleWinner();

}
