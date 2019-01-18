/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: Knoop
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Knoop.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\Knoop.java                                                                  
//----------------------------------------------------------------------------

//## class Knoop 
public class Knoop {
    
    protected GrafischeEngine itsGrafischeEngine;
    protected KnopenManipulatieVenster itsKnopenManipulatieVenster;

    double value;

    // Constructors
    
    public Knoop() {
	this(0);
    }

    public Knoop(double value) {
	this.value = value;
    }

    public double getValue() {
	return value;
    }

    public void setValue(double value) {
	this.value = value;
    }
    
    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    
    public void __setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        itsGrafischeEngine = p_GrafischeEngine;
    }
    
    public void _setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(itsGrafischeEngine != null)
            itsGrafischeEngine._removeItsKnoop(this);
        __setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(p_GrafischeEngine != null)
            p_GrafischeEngine._addItsKnoop(this);
        _setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void _clearItsGrafischeEngine() {
        itsGrafischeEngine = null;
    }
    
    public KnopenManipulatieVenster getItsKnopenManipulatieVenster() {
        return itsKnopenManipulatieVenster;
    }
    
    public void __setItsKnopenManipulatieVenster(KnopenManipulatieVenster p_KnopenManipulatieVenster) {
        itsKnopenManipulatieVenster = p_KnopenManipulatieVenster;
    }
    
    public void _setItsKnopenManipulatieVenster(KnopenManipulatieVenster p_KnopenManipulatieVenster) {
        if(itsKnopenManipulatieVenster != null)
            itsKnopenManipulatieVenster._removeItsKnoop(this);
        __setItsKnopenManipulatieVenster(p_KnopenManipulatieVenster);
    }
    
    public void setItsKnopenManipulatieVenster(KnopenManipulatieVenster p_KnopenManipulatieVenster) {
        if(p_KnopenManipulatieVenster != null)
            p_KnopenManipulatieVenster._addItsKnoop(this);
        _setItsKnopenManipulatieVenster(p_KnopenManipulatieVenster);
    }
    
    public void _clearItsKnopenManipulatieVenster() {
        itsKnopenManipulatieVenster = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Knoop.java
*********************************************************************/

