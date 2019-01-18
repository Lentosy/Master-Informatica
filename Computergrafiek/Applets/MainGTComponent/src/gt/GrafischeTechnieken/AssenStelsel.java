/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: AssenStelsel
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\AssenStelsel.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.geom.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\AssenStelsel.java                                                                  
//----------------------------------------------------------------------------

//## class AssenStelsel 
public class AssenStelsel {
    
    protected TekenVenster itsTekenVenster;
    
    // Constructors
    double xMin;
    double xMax;
    double yMin;
    double yMax;

    public  AssenStelsel() {
	xMin = -100.0;
	xMax = 100.0;
	yMin = -100.0;
	yMax = 100.0;
    }
    

    public Point2D.Double cartToScreen(double x, double y, double sW, double sH) {
	return new Point2D.Double(((x-xMin)*(sW/(xMax-xMin))),
				  ((-y+yMax)*(sH/(yMax-yMin))));
    }

    public Point2D.Double screenToCart(double x, double y, double sW, double sH) {
	return new Point2D.Double((x*((xMax-xMin)/sW)+xMin),
				  -(y*((yMax-yMin)/sH)-yMax));

    }

    public void setBounds(double xMin, double yMin, double xMax, double yMax) {
	this.xMin = xMin;
	this.xMax = xMax;
	this.yMin = yMin;
	this.yMax = yMax;
    }

    public double getXMax() {
	return xMax;
    }

    public double getXMin() {
	return xMin;
    }

    public double getYMax() {
	return yMax;
    }

    public double getYMin() {
	return yMin;
    }

    public int getGridStep() {
	return 25;
    }

    public TekenVenster getItsTekenVenster() {
        return itsTekenVenster;
    }
    
    public void __setItsTekenVenster(TekenVenster p_TekenVenster) {
        itsTekenVenster = p_TekenVenster;
    }
    
    public void _setItsTekenVenster(TekenVenster p_TekenVenster) {
        if(itsTekenVenster != null)
            itsTekenVenster.__setItsAssenStelsel(null);
        __setItsTekenVenster(p_TekenVenster);
    }
    
    public void setItsTekenVenster(TekenVenster p_TekenVenster) {
        if(p_TekenVenster != null)
            p_TekenVenster._setItsAssenStelsel(this);
        _setItsTekenVenster(p_TekenVenster);
    }
    
    public void _clearItsTekenVenster() {
        itsTekenVenster = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\AssenStelsel.java
*********************************************************************/

