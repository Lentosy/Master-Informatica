/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package plant;

import be.tiwi.planten.Plant;
import be.tiwi.planten.impl.PlantenGeheugenDB;
import java.util.List;

/**
 *
 * @author counterpoint
 */
public class PlantenDAO {
    
    private static PlantenGeheugenDB db; 
    private static PlantenDAO instance;
    
    public static PlantenDAO getInstance(){
        if(instance == null){
            db = new PlantenGeheugenDB();
            db.setPlanten("planten.txt");
        }   
        return instance;
    }
    
    public static List<Plant> getPlanten(String kleur){
        return getInstance().db.geefPlanten(kleur);
    }
    
    public static synchronized String voegPlantToe(Plant plant){
        return getInstance().voegPlantToe(plant) != null ? "gelukt" : "mislukt";
    }
    
    
}
