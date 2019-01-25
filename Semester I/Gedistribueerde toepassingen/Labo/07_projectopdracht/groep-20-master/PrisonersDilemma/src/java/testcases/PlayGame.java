/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pd;

import PrisonerDilemma.Player;
import java.util.ArrayList;

/**
 *
 * @author vongenae
 */
public class PlayGame {
    
    protected static void printPlayer(Player player) {
        System.out.println("Name player " + player.getName());
        System.out.println("The history of choices ");
        printList(player.getChoiceHistory());
        System.out.println("Years in prison ");
        printList(player.getScoreHistory());
    }

    protected static void printList(ArrayList listToPrint) {
        listToPrint.stream().forEach((Object listToPrint1) -> {
            System.out.println(listToPrint1);
        });
    }
    
}
