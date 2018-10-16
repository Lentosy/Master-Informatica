package be.tiwi.planten.service;

import be.tiwi.planten.Plant;
import be.tiwi.planten.PlantBeheer;
import java.util.List;
import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;


@WebService(serviceName = "Planten")
public class PlantService {  
    
    PlantBeheer pb = PlantBeheerInstance.GetInstance();
    
    @WebMethod(operationName = "geefPlanten")
    public List<Plant> geefPlanten(@WebParam(name= "kleur") String kleur){
        return pb.geefPlanten(kleur);
    }

    @WebMethod(operationName = "voegPlantToe")
    public String voegPlantToe(@WebParam(name = "kleur") String kleur,
                               @WebParam(name = "naam")  String naam ,
                               @WebParam(name = "prijs") double prijs) {
        Plant p = new Plant();
        p.setKleur(kleur);
        p.setNaam(naam);
        p.setPrijs(prijs);
        p = pb.voegPlantToe(p);
        if(p == null){
            return "mislukt";
        }
        return "gelukt";
    }
}

