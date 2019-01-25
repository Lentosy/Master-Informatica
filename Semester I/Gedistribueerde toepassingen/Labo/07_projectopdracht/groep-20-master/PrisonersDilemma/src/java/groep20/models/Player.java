/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package groep20.models;

import java.util.ArrayList;

/**
 *
 * @author counterpoint
 */
public class Player {
    private String name;
    private ArrayList<Integer> choices;
    private ArrayList<Integer> convictions;
    public Player(){
        choices = new ArrayList<>();
        convictions = new ArrayList<>();
    }
    public Player(String name, ArrayList<Integer> choices, ArrayList<Integer> convictions) {
        this.name = name;
        this.choices = choices;
        this.convictions = convictions;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append(name).append("\n\tchoices [");
        choices.forEach(i -> builder.append(i).append(" "));
        builder.append("]\n");
        builder.append("\n\tconvict [");
        convictions.forEach(i -> builder.append(i).append(" "));
        builder.append("]\n");
        return builder.toString();
    }
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<Integer> getChoices() {
        return choices;
    }

    public void setChoices(ArrayList<Integer> choices) {
        this.choices = choices;
    }

    public ArrayList<Integer> getConvictions() {
        return convictions;
    }

    public void setConvictions(ArrayList<Integer> convictions) {
        this.convictions = convictions;
    }
    
    
    
    
}
