/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: MouseEventHandler
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MouseEventHandler.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\MouseEventHandler.java                                                                  
//----------------------------------------------------------------------------

//## class MouseEventHandler 
abstract class MouseEventHandler implements MouseListener, MouseMotionListener {
    
    protected PuntenVenster itsPuntenVenster;

    // useful for drag operations : store the last selected screenpoint
    Point lastScreenPoint;

    // Constructors
    
    public  MouseEventHandler() {
    }

    public PuntenVenster getItsPuntenVenster() {
        return itsPuntenVenster;
    }
    
    public void setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        itsPuntenVenster = p_PuntenVenster;
    }
    
    public void _clearItsPuntenVenster() {
        itsPuntenVenster = null;
    }

}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MouseEventHandler.java
*********************************************************************/

