/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20.models;

/**
 *
 * @author counterpoint
 */
public class Game {
    private long id;
    private Player player1;
    private Player player2;

    public Game(long id, Player player1, Player player2) {
        this.id = id;
        this.player1 = player1;
        this.player2 = player2;
    }
    
    
    // debugging
    @Override
    public String toString(){
        StringBuilder builder = new StringBuilder();
        builder.append("Game ").append(id).append(" : ").append(player1.getName()).append(" vs ").append(player2.getName()).append("\n");
        builder.append(player1.toString());
        builder.append(player2.toString());
        
        return builder.toString();
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Player getPlayer1() {
        return player1;
    }

    public void setPlayer1(Player player1) {
        this.player1 = player1;
    }

    public Player getPlayer2() {
        return player2;
    }

    public void setPlayer2(Player player2) {
        this.player2 = player2;
    }
    
    
    
    
    
}
