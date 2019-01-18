/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: ControlePunt
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\ControlePunt.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.geom.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\ControlePunt.java                                                                  
//----------------------------------------------------------------------------

//## class ControlePunt 
public class ControlePunt extends Punt {
    
    protected GrafischeEngine itsGrafischeEngine;
    protected TekenVenster itsTekenVenster;
    
    // Constructors
    
    public  ControlePunt() {
	super();
    }
    
    public ControlePunt(Point2D.Double p) {
	super(p);
    }

    public ControlePunt(double x, double y) {
	super(x, y);
    }

    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    
    public void __setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        itsGrafischeEngine = p_GrafischeEngine;
    }
    
    public void _setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(itsGrafischeEngine != null)
            itsGrafischeEngine._removeItsControlePunt(this);
        __setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(p_GrafischeEngine != null)
            p_GrafischeEngine._addItsControlePunt(this);
        _setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void _clearItsGrafischeEngine() {
        itsGrafischeEngine = null;
    }
    
    public TekenVenster getItsTekenVenster() {
        return itsTekenVenster;
    }
    
    public void __setItsTekenVenster(TekenVenster p_TekenVenster) {
        itsTekenVenster = p_TekenVenster;
    }
    
    public void _setItsTekenVenster(TekenVenster p_TekenVenster) {
        if(itsTekenVenster != null)
            itsTekenVenster._removeItsControlePunt(this);
        __setItsTekenVenster(p_TekenVenster);
    }
    
    public void setItsTekenVenster(TekenVenster p_TekenVenster) {
        if(p_TekenVenster != null)
            p_TekenVenster._addItsControlePunt(this);
        _setItsTekenVenster(p_TekenVenster);
    }
    
    public void _clearItsTekenVenster() {
        itsTekenVenster = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\ControlePunt.java
*********************************************************************/

