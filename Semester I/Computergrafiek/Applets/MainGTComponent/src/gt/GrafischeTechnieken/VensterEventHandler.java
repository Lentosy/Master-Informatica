/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: VensterEventHandler
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\VensterEventHandler.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\VensterEventHandler.java                                                                  
//----------------------------------------------------------------------------

//## class VensterEventHandler 
public class VensterEventHandler {
    
    protected GebruikersInterface itsGebruikersInterface;
    
    // Constructors
    
    public  VensterEventHandler() {
    }
    
    public GebruikersInterface getItsGebruikersInterface() {
        return itsGebruikersInterface;
    }
    
    public void __setItsGebruikersInterface(GebruikersInterface p_GebruikersInterface) {
        itsGebruikersInterface = p_GebruikersInterface;
    }
    
    public void _setItsGebruikersInterface(GebruikersInterface p_GebruikersInterface) {
        if(itsGebruikersInterface != null)
            itsGebruikersInterface._removeItsVensterEventHandler(this);
        __setItsGebruikersInterface(p_GebruikersInterface);
    }
    
    public void setItsGebruikersInterface(GebruikersInterface p_GebruikersInterface) {
        if(p_GebruikersInterface != null)
            p_GebruikersInterface._addItsVensterEventHandler(this);
        _setItsGebruikersInterface(p_GebruikersInterface);
    }
    
    public void _clearItsGebruikersInterface() {
        itsGebruikersInterface = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\VensterEventHandler.java
*********************************************************************/

