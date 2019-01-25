/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: DataPunt
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\DataPunt.java
*********************************************************************/

package GrafischeTechnieken;

import java.awt.*;
import java.util.*;
import java.awt.image.*;
import java.awt.geom.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\DataPunt.java                                                                  
//----------------------------------------------------------------------------

//## class DataPunt 
public class DataPunt extends Punt {

    Punt diff1;
    Punt diff2;

    public  DataPunt() {
	super();
    }
    
    public DataPunt(Point2D.Double p) {
	super(p);
    }

    public DataPunt(double x, double y) {
	super(x, y);
    }

    public Punt getDiff1() {
	return diff1;
    }

    public Punt getDiff2() {
	return diff2;
    }

    public void setDiff1(Punt p) {
	this.diff1 = p;
    }

    public void setDiff2(Punt p) {
	if(diff1!=null)
	    this.diff2 = p;
    }

    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    
    public void __setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        itsGrafischeEngine = p_GrafischeEngine;
    }
    
    public void _setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(itsGrafischeEngine != null)
            itsGrafischeEngine._removeItsDataPunt(this);
        __setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(p_GrafischeEngine != null)
            p_GrafischeEngine._addItsDataPunt(this);
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
            itsTekenVenster._removeItsDataPunt(this);
        __setItsTekenVenster(p_TekenVenster);
    }
    
    public void setItsTekenVenster(TekenVenster p_TekenVenster) {
        if(p_TekenVenster != null)
            p_TekenVenster._addItsDataPunt(this);
        _setItsTekenVenster(p_TekenVenster);
    }
    
    public void _clearItsTekenVenster() {
        itsTekenVenster = null;
    }

}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\DataPunt.java
*********************************************************************/

