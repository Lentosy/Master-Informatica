package be.tiwi.woordenboek.impl;

import be.tiwi.woordenboek.data.ArrayOfDictionaryWord;;
import be.tiwi.woordenboek.data.DictService;
import be.tiwi.woordenboek.data.DictServiceSoap;
import be.tiwi.woordenboek.data.Woordenboek;
import be.tiwi.woordenboek.data.WoordenboekDAO;
import be.tiwi.woordenboek.data.WordDefinition;
import java.util.ArrayList;
import java.util.List;

public class WoordenBoekDAOImpl implements WoordenboekDAO {
        
    DictServiceSoap service;
    
    public WoordenBoekDAOImpl(){
        service = new DictService().getDictServiceSoap();
    }
    
    @Override
    public List<Woordenboek> getWoordenboeken() {
        List<Woordenboek> woordenboeken = new ArrayList<>();
        service.dictionaryList().getDictionary().forEach((d) -> {
            woordenboeken.add(new Woordenboek(d.getId(), d.getName()));
        });
        return woordenboeken;
    }

    @Override
    public List<String> zoekWoorden(String prefix, String woordenboekId) {
        List<String> woorden = new ArrayList<>();
        ArrayOfDictionaryWord a = service.matchInDict(woordenboekId, prefix, "prefix");
        a.getDictionaryWord().forEach((w) -> {
          woorden.add(w.getWord());  
        });
        return woorden;
    }

    @Override
    public List<String> getDefinities(String woord, String woordenboekId) {
       List<String> definities = new ArrayList<>();
       WordDefinition wd = service.defineInDict(woordenboekId, woord);  
       wd.getDefinitions().getDefinition().forEach((d) -> {
           definities.add(d.getWordDefinition());
        });
       return definities;
    }

}
