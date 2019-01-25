/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: PuntenVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\PuntenVenster.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\PuntenVenster.java                                                                  
//----------------------------------------------------------------------------

//## class PuntenVenster 
public class PuntenVenster extends Window {
    
    protected GraadManipulatieVenster itsGraadManipulatieVenster;
    protected KnopenManipulatieVenster itsKnopenManipulatieVenster;
    protected TekenVenster itsTekenVenster;

    protected GTToolPane itsToolPane;
    protected CurveSelectPane itsCurveSelectPane;

    protected GrafischeEngine itsGrafischeEngine;

    // Constructors
    
    public  PuntenVenster() {
	super(480, 480);
        this.initRelations();
	this.setLocation(10,20);
	this.setStretchablePane(itsTekenVenster);
	this.setBigTitle("Lagrange");

	ZoomBoxHandler zbh = new ZoomBoxHandler(itsTekenVenster, itsTekenVenster.getItsAssenStelsel(), itsToolPane);
	itsTekenVenster.addMouseListener(zbh);
	itsTekenVenster.addMouseMotionListener(zbh);
	

	placeKnotEditor();
    }
    
    private void placeKnotEditor() {
	JPanel pane = new JPanel(new BorderLayout());	
	GTGeneralWindowPane gPane = new GTGeneralWindowPane(240,100,34,12,13,13,1,1,
					      itsKnopenManipulatieVenster);

	gPane.setBigTitle("KnopenVenster");
	pane.add(gPane);
	pane.setBorder(new MatteBorder(new Insets(10,10,10,10),GTGeneralWindowFrame.beige));

	this.addSouth(pane);
    }

    private void placeTools() {
	
	JPanel westPane = new JPanel();
	JPanel wsPane = new JPanel();

	westPane.setLayout(new BoxLayout(westPane, BoxLayout.Y_AXIS));
	westPane.add(itsToolPane);
	westPane.add(Box.createVerticalStrut(0));
	westPane.add(itsCurveSelectPane);
	westPane.add(Box.createVerticalGlue());

	westPane.setBackground(GTGeneralWindowFrame.beige);

	this.addWest(westPane);
	this.pack();
	//setSize(new Dimension(500,500));
    }

    public GrafischeEngine getItsGrafischeEngine() {
	return itsGrafischeEngine;
    }

    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
	this.itsGrafischeEngine = p_GrafischeEngine;
	itsTekenVenster.setItsGrafischeEngine(p_GrafischeEngine);
    }

    public GraadManipulatieVenster getItsGraadManipulatieVenster() {
        return itsGraadManipulatieVenster;
    }

    public void onConfiguratieChange() {
	itsGrafischeEngine.berekenCurve();
    }

    public void __setItsGraadManipulatieVenster(GraadManipulatieVenster p_GraadManipulatieVenster) {
        itsGraadManipulatieVenster = p_GraadManipulatieVenster;
    }
    
    public void _setItsGraadManipulatieVenster(GraadManipulatieVenster p_GraadManipulatieVenster) {
        if(itsGraadManipulatieVenster != null)
            itsGraadManipulatieVenster.__setItsPuntenVenster(null);
        __setItsGraadManipulatieVenster(p_GraadManipulatieVenster);
    }
    
    public GraadManipulatieVenster newItsGraadManipulatieVenster() {
        itsGraadManipulatieVenster = new GraadManipulatieVenster();
        itsGraadManipulatieVenster._setItsPuntenVenster(this);
        return itsGraadManipulatieVenster;
    }
    
    public void deleteItsGraadManipulatieVenster() {
        itsGraadManipulatieVenster.__setItsPuntenVenster(null);
        itsGraadManipulatieVenster=null;
    }
    
    public KnopenManipulatieVenster getItsKnopenManipulatieVenster() {
        return itsKnopenManipulatieVenster;
    }
    
    public void __setItsKnopenManipulatieVenster(KnopenManipulatieVenster p_KnopenManipulatieVenster) {
        itsKnopenManipulatieVenster = p_KnopenManipulatieVenster;
    }
    
    public void _setItsKnopenManipulatieVenster(KnopenManipulatieVenster p_KnopenManipulatieVenster) {
        if(itsKnopenManipulatieVenster != null)
            itsKnopenManipulatieVenster.__setItsPuntenVenster(null);
        __setItsKnopenManipulatieVenster(p_KnopenManipulatieVenster);
    }
    
    public KnopenManipulatieVenster newItsKnopenManipulatieVenster() {
        itsKnopenManipulatieVenster = new KnopenManipulatieVenster();
        itsKnopenManipulatieVenster._setItsPuntenVenster(this);
        return itsKnopenManipulatieVenster;
    }
    
    public void deleteItsKnopenManipulatieVenster() {
        itsKnopenManipulatieVenster.__setItsPuntenVenster(null);
        itsKnopenManipulatieVenster=null;
    }
    
    public TekenVenster getItsTekenVenster() {
        return itsTekenVenster;
    }
    
    public void __setItsTekenVenster(TekenVenster p_TekenVenster) {
        itsTekenVenster = p_TekenVenster;
    }
    
    public void _setItsTekenVenster(TekenVenster p_TekenVenster) {
        if(itsTekenVenster != null)
            itsTekenVenster.__setItsPuntenVenster(null);
        __setItsTekenVenster(p_TekenVenster);
    }
    
    public TekenVenster newItsTekenVenster() {
        itsTekenVenster = new TekenVenster();
        itsTekenVenster._setItsPuntenVenster(this);
        return itsTekenVenster;
    }
    
    public GTToolPane getItsToolPane() {
	return itsToolPane;
    }

    public GTToolPane newItsToolPane() {
	itsToolPane = new GTToolPane(this);
	return itsToolPane;
    }

    public void setCurveSelectPane(CurveSelectPane itsCurveSelectPane) {
	this.itsCurveSelectPane = itsCurveSelectPane;
	placeTools();
    }

    public CurveSelectPane getCurveSelectPane() {
	return itsCurveSelectPane;
    }

    public void deleteItsTekenVenster() {
        itsTekenVenster.__setItsPuntenVenster(null);
        itsTekenVenster=null;
    }
    
    protected void initRelations() {
        itsGraadManipulatieVenster = newItsGraadManipulatieVenster();
        itsKnopenManipulatieVenster = newItsKnopenManipulatieVenster();
        itsTekenVenster = newItsTekenVenster();
	itsToolPane = newItsToolPane();
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\PuntenVenster.java
*********************************************************************/

