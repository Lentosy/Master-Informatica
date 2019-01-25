/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20;

import PrisonerDilemma.Player;
import java.io.StringReader;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.enterprise.context.ApplicationScoped;
import javax.inject.Inject;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;
import javax.websocket.OnClose;
import javax.websocket.OnError;
import javax.websocket.OnMessage;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;

/**
 *
 * @author bdsaffel
 */
//TODO: implementatie websockets
@ApplicationScoped
@ServerEndpoint("/game")
public class PrisonersDilemmaSocketServer {

    private static final String GAME_MODE = "GAMEMODE";
    private static final String PLAYER_DECISION = "PLAYER_DECISION";
    private static final String PLAYER_NAME = "PLAYERNAME";

    @Inject
    private PDGameSessionHandler sessionHandler;

    @OnOpen
    public void open(Session session) {
        // no extra code needed.
        // session will first be handled when a user makes a player mode decision
        Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.INFO, "User Connected with session: " + session.toString());
  
        Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.INFO, "User Connected with id: " + session.getId());
  
    }

    @OnClose
    public void OnCclose(Session session) {
        sessionHandler.removeSession(session.getId());
    }

    @OnError
    public void onError(Throwable error) {
        
         Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "Error in onerror()");
       
        Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, error.getMessage());
        // Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, null, error);
    }

    @OnMessage
    public void handleMessage(String message, Session session) {

        //imrovement: use encoders and decoders.
        JsonReader reader = Json.createReader(new StringReader(message));
        JsonObject jsonMessage = reader.readObject();

        System.out.print("received message");
        Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, jsonMessage.toString());
        Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, session.toString());

        try {
            if (jsonMessage.containsKey(GAME_MODE)) {
                if ("player".equals(jsonMessage.getString(GAME_MODE))) {
 Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "spelerspel with id"+ session.getId());
                    sessionHandler.addSession(session, Boolean.TRUE, jsonMessage.getString(PLAYER_NAME));
                }
                if ("computer".equals(jsonMessage.getString(GAME_MODE))) {
                    
                     Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "computerspel");
                    sessionHandler.addSession(session, Boolean.FALSE, jsonMessage.getString(PLAYER_NAME));
                }
            }

            if (jsonMessage.containsKey(PLAYER_DECISION)) {
                     Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, "keuze gemaakt door speler");
                sessionHandler.addDecision(session.getId(), jsonMessage.getInt(PLAYER_DECISION));
            }
        } catch (Exception e) {
            Logger.getLogger(PrisonersDilemmaSocketServer.class.getName()).log(Level.SEVERE, e.getMessage());

        }
    }

}
