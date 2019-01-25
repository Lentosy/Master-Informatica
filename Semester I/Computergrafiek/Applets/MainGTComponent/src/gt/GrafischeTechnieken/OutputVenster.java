/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: OutputVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\OutputVenster.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.*;
import java.io.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\OutputVenster.java                                                                  
//----------------------------------------------------------------------------

//## class OutputVenster 
public class OutputVenster extends Window {
    
    protected GebruikersInterface itsGebruikersInterface;
    protected GrafiekVenster itsGrafiekVenster;
    protected BasisMatrixVenster itsBasisMatrixVenster;

    protected OutputCanvas itsOutputCanvas;
    // Constructors
    
    public  OutputVenster() {
	super(480, 480);

        initRelations();

	this.setTitle("OutputVenster");

	this.setStretchablePane(itsOutputCanvas);
	this.setBigTitle("Output");

	this.pack();
    }
    
    public GebruikersInterface getItsGebruikersInterface() {
        return itsGebruikersInterface;
    }

    public JComponent getItsOutputCanvas() {
	return itsOutputCanvas;
    }

    public void saveOutputToPng(String filename) 
    throws IOException {
	Image curveBuffer = itsOutputCanvas.getCurveBuffer();

	if(curveBuffer != null)
	    ImageIO.write((RenderedImage)curveBuffer, "png", new File(filename));
    }

    public void __setItsGebruikersInterface(GebruikersInterface p_GebruikersInterface) {
        itsGebruikersInterface = p_GebruikersInterface;
    }
    
    public void _setItsGebruikersInterface(GebruikersInterface p_GebruikersInterface) {
        if(itsGebruikersInterface != null)
            itsGebruikersInterface.__setItsOutputVenster(null);
        __setItsGebruikersInterface(p_GebruikersInterface);
    }
    
    public void setItsGebruikersInterface(GebruikersInterface p_GebruikersInterface) {
        if(p_GebruikersInterface != null)
            p_GebruikersInterface._setItsOutputVenster(this);
        _setItsGebruikersInterface(p_GebruikersInterface);
    }
    
    public void _clearItsGebruikersInterface() {
        itsGebruikersInterface = null;
    }
        
    public BasisMatrixVenster getItsBasisMatrixVenster() {
	return itsBasisMatrixVenster;
    }
    
    public GrafiekVenster getItsGrafiekVenster() {
        return itsGrafiekVenster;
    }
    
    public void __setItsGrafiekVenster(GrafiekVenster p_GrafiekVenster) {
        itsGrafiekVenster = p_GrafiekVenster;
    }
    
    public void _setItsGrafiekVenster(GrafiekVenster p_GrafiekVenster) {
        if(itsGrafiekVenster != null)
            itsGrafiekVenster.__setItsOutputVenster(null);
        __setItsGrafiekVenster(p_GrafiekVenster);
    }
    
    public GrafiekVenster newItsGrafiekVenster() {
        itsGrafiekVenster = new GrafiekVenster();
        itsGrafiekVenster._setItsOutputVenster(this);
        return itsGrafiekVenster;
    }
    
    public void deleteItsGrafiekVenster() {
        itsGrafiekVenster.__setItsOutputVenster(null);
        itsGrafiekVenster=null;
    }
    
    protected void initRelations() {
        itsGrafiekVenster = newItsGrafiekVenster();
	// only output : no double relation necessary
	itsBasisMatrixVenster = new BasisMatrixVenster();
	itsOutputCanvas = new OutputCanvas(itsGebruikersInterface);
    }

    public void setItsKromme(Kromme p_Kromme) {
	itsOutputCanvas.setItsKromme(p_Kromme);
    }
    
    public void setItsSplines(Kromme [] segments) {
	itsOutputCanvas.setItsSplines(segments);
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\OutputVenster.java
*********************************************************************/

