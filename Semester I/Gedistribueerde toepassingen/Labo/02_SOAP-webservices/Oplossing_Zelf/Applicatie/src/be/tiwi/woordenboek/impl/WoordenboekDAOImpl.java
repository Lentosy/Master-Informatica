package be.tiwi.woordenboek.impl;

import be.tiwi.woordenboek.data.Woordenboek;
import be.tiwi.woordenboek.data.WoordenboekDAO;
import com.aonaware.services.webservices.Definition;
import com.aonaware.services.webservices.DictService;
import com.aonaware.services.webservices.DictServiceSoap;
import com.aonaware.services.webservices.Dictionary;
import com.aonaware.services.webservices.DictionaryWord;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author counterpoint
 */
public class WoordenboekDAOImpl implements WoordenboekDAO {

    private DictServiceSoap dictServiceSoap;
    public WoordenboekDAOImpl(DictService dictService) {
        this.dictServiceSoap = dictService.getDictServiceSoap();
    }
    
    

    @Override
    public List<Woordenboek> getWoordenboeken() {
        List<Woordenboek> woordenboeken = new ArrayList<>();
        for(Dictionary d : dictServiceSoap.dictionaryList().getDictionary()){
            woordenboeken.add(new Woordenboek(d.getId(), d.getName()));
        }
        return woordenboeken; 
    }

    @Override
    public List<String> zoekWoorden(String prefix, String woordenboekId) {
        List<String> woorden = new ArrayList<>();
        for(DictionaryWord w : dictServiceSoap.matchInDict(woordenboekId, prefix, "prefix").getDictionaryWord()){
            woorden.add(w.getWord());
        }
        return woorden;
    }

    @Override
    public List<String> getDefinities(String woord, String woordenboekId) {
        List<String> definities = new ArrayList<>();
        for(Definition d : dictServiceSoap.defineInDict(woordenboekId, woord).getDefinitions().getDefinition()){
            definities.add(d.getWordDefinition());
        }
        return definities;
    }
    
}
