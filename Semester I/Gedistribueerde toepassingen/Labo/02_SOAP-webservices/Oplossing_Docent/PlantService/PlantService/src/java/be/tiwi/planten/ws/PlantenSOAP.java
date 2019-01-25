/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package be.tiwi.planten.ws;

import be.tiwi.planten.Plant;
import java.util.List;
import javax.jws.HandlerChain;
import javax.jws.WebService;
import javax.jws.WebMethod;
import javax.jws.WebParam;

/**
 *
 * @author vongenae
 */
@WebService(serviceName = "PlantenSOAP")
public class PlantenSOAP {
    
    /**
     * Web service getPlanten
     * @param kleur
     * @return 
     */
    @WebMethod(operationName = "getPlanten")
    public List<Plant> getPlanten(@WebParam(name = "kleur") String kleur) {
        return PlantHouder.getPlanten().geefPlanten(kleur);
    }

    /**
     * Web service getPlanten
     * @param plant
     * @return 
     */
    @WebMethod(operationName = "voegPlantToe")
    public String voegPlantToe(@WebParam(name = "plant") Plant plant) {
        String resultaat = "mislukt";
        if (PlantHouder.getPlanten().voegPlantToe(plant) != null) {
            resultaat = "gelukt";
        }
        return resultaat;
    }
    
    
    
    
}
