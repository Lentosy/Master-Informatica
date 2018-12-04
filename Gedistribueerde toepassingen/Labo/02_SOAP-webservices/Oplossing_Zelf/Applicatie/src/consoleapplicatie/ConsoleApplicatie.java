package consoleapplicatie;


import com.aonaware.services.webservices.DictService;
import com.aonaware.services.webservices.DictionaryWord;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

/**
 *
 * @author counterpoint
 */
public class ConsoleApplicatie {
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        DictService service = new DictService();
        
        
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Enter text:");
            String line = reader.readLine();
           
            for(String woord : line.split(" ")){
                List<DictionaryWord> DictionaryWords = service.getDictServiceSoap().match(woord, "lev").getDictionaryWord();
                System.out.print(woord + "\n -> ");
                for(DictionaryWord word : DictionaryWords){
                    System.out.print(word.getWord() + " ");
                }
                System.out.println("\n");
                
            }
        } catch(IOException ioe){
            System.err.println(ioe.getMessage());
        }
      
    }
    
}
