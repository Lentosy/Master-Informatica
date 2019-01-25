package guiapplicatie;


import be.tiwi.woordenboek.gui.WoordenboekFrame;
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
public class GUIApplicatie {
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        WoordenboekFrame frame = new WoordenboekFrame();
        frame.setVisible(true);
      
    }
    
}
