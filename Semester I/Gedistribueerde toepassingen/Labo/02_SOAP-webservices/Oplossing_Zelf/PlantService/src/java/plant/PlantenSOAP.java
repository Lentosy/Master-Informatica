/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package plant;

import be.tiwi.planten.Plant;
import java.util.List;
import javax.jws.WebService;
import javax.jws.WebMethod;
import javax.jws.WebParam;

/**
 *
 * @author counterpoint
 */
@WebService(serviceName = "PlantenSOAP")
public class PlantenSOAP {
    
    
    @WebMethod(operationName = "getPlanten")
    public List<Plant> getPlanten(@WebParam(name = "kleur") String kleur){
        return PlantenDAO.getPlanten(kleur);
    }

    /**
     * This is a sample web service operation
     * @param plant
     * @return 
     */
    @WebMethod(operationName = "voegPlantToe")
    public String voegPlantToe(@WebParam(name = "plant") Plant plant) {
        return PlantenDAO.voegPlantToe(plant);
      
    }
}
