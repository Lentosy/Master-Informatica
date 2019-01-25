package pd;

import PrisonerDilemma.PDComputerGame;
import PrisonerDilemma.Player;
import PrisonerDilemma.ResultRound;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

/**
 *
 * @author khaluf
 */
public class GameAgainstComputer extends PlayGame {

    public static void main(String[] args) throws IOException {
        System.out.println("Do you want to start a new game of Prisoner dilemma? yes|no");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String answer = br.readLine();
        if (answer.equals("yes")) {
            PDComputerGame pdGame = new PDComputerGame("your name");
            System.out.println("Your opponent has been selected");
            System.out.println("How many rounds?");
            int numOfRounds = Integer.parseInt(br.readLine());
            for (int i = 0; i < numOfRounds; i++) {
                System.out.println("Please enter your choice for the round number " + (i + 1)
                        + " (confess = 0, be silent = 1)");
                int choice = Integer.parseInt(br.readLine());
                ResultRound[] round = pdGame.playRound(choice);
                System.out.println(round[0].getMessage());
            }

            printPlayer(pdGame.getPlayer1());     
            printPlayer(pdGame.getPlayer2());

        } else {
            System.out.println("bye bye");
        }
    }

}
