package pd;

import PrisonerDilemma.PDRealGame;
import PrisonerDilemma.ResultRound;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import static pd.PlayGame.printPlayer;

/**
 *
 * @author vongenae
 */
public class GameBetweenPlayers extends PlayGame{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        
        System.out.println("Do you want to start a new game of Prisoner dilemma? yes|no");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String answer = br.readLine();
        if (answer.equals("yes")) {
            PDRealGame pdGame = new PDRealGame("name1", "name2");
            System.out.println("How many rounds?");
            int numOfRounds = Integer.parseInt(br.readLine());
            for (int i = 0; i < numOfRounds; i++) {
                System.out.println("Please enter the choice for the round number " + (i + 1)
                        + " (confess = 0, be silent = 1) for player name1");
                int choice1 = Integer.parseInt(br.readLine());
                System.out.println("Please enter the choice for the round number " + (i + 1)
                        + " (confess = 0, be silent = 1) for player name2");
                int choice2 = Integer.parseInt(br.readLine());
                ResultRound[] round = pdGame.playRound(choice1, choice2);
                System.out.println("Result for name1");
                System.out.println(round[0].getMessage());
                System.out.println("Result for name2");
                System.out.println(round[1].getMessage());
            }

            printPlayer(pdGame.getPlayer1());     
            printPlayer(pdGame.getPlayer2());

        } else {
            System.out.println("bye bye");
        }
    }
    
}
