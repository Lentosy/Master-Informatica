/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: Bezier
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Bezier.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\Bezier.java                                                                  
//----------------------------------------------------------------------------

//## class Bezier 
public class Bezier extends BSpline {
    
    
    // Constructors
    
    public  Bezier(GebruikersInterface gui) {
	super(gui);
    }

    public void berekenCurve() {
	itsGraad.setValue(itsControlePunt.size()-1);
	isOpen = true;
	if(itsControlePunt.size()>2)
	    super.berekenCurve();
    }

    public void outputToTekenVenster() {
	super.outputToTekenVenster();
	itsGebruikersInterface.getItsMenuVenster().setBigTitle("Bezier  (k="+(itsGraad.getValue()+1)+")");
    }


    public void flushInputs() {

	super.flushInputs();
	itsGebruikersInterface.getItsMenuVenster().setBigTitle("Bezier");
	itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().setBigTitle("Bernstein");
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Bezier.java
*********************************************************************/

