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
public class Punt {
    
    protected GrafischeEngine itsGrafischeEngine;
    protected TekenVenster itsTekenVenster;

    double x, y;
    // Constructors

    public Punt() {
	this.x = 0; this.y = 0;
    }
    
    public Punt(double x, double y) {
	this.x = x;
	this.y = y;
    }

    public Punt(Point2D.Double p) {
	this.x = p.getX();
	this.y = p.getY();
    }

    public double getX() {
	return x;
    }

    public double getY() {
	return y;
    }

    public void setX(double x) {
	this.x = x;
    }

    public void setY(double y) {
	this.y = y;
    }

    public Punt scalar(double s) {
	double x2 = x*s;
	double y2 = y*s;

	return new Punt(x2, y2);
    }

}
