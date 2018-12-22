/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20;

import javax.websocket.Session;

/**
 *
 * @author thomas
 */
public class PDPlayerWrapper  {
    private String UUID;
    private int Decision = -1;
    private Session session;
    private String namePlayer;

    public PDPlayerWrapper(Session session, String namePlayer) {
        this.session = session;
        UUID = session.getId();
        this.namePlayer = namePlayer;
    }

    public void setDecision(int Decision) {
        this.Decision = Decision;
    }
    
    public int getAndClearDecision() throws Exception{
        if(!hasDecision()){
            throw new Exception("Could not retrieve players decision since no decision was made");
        }
        int tmp = Decision;
        clearDecision();
        return tmp;
        
    }
    
    public Boolean hasDecision(){
        return (Decision != -1);
    }
    
    private void clearDecision(){
         this.Decision = -1;
    }
    
    public String getUUID(){
        return session.getId();
    }

    public Session getSession() {
        return session;
    }

    public String getNamePlayer() {
        return namePlayer;
    }

    public int getDecision() {
        return Decision;
    }
    
    
    
    
}
