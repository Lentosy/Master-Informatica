/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ws;

import be.tiwi.planten.PlantBeheer;
import be.tiwi.planten.PlantBeheer;
import be.tiwi.planten.impl.PlantenGeheugenDB;

/**
 *
 * @author vongenae
 */
public class PlantHouder {
    private final PlantenGeheugenDB planten;
    private static PlantHouder houder;

    private PlantHouder() {
        planten = new PlantenGeheugenDB();
        planten.setPlanten("planten.txt");
    }
    
    public static synchronized PlantBeheer getPlanten() {
        if (houder == null) {
            houder = new PlantHouder();
        }
        return houder.planten;
    }
    
    
    
}
