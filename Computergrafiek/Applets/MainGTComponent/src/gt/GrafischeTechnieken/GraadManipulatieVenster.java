/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: GraadManipulatieVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GraadManipulatieVenster.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\GraadManipulatieVenster.java                                                                  
//----------------------------------------------------------------------------

//## class GraadManipulatieVenster 
public class GraadManipulatieVenster extends Window implements ChangeListener {
    
    protected PuntenVenster itsPuntenVenster;
    protected Graad itsGraad;
    protected JSpinner spinner;

    // Constructors
    
    public  GraadManipulatieVenster() {
	super(150,80);

	spinner = new JSpinner();
	SpinnerNumberModel spinnerModel = new SpinnerNumberModel(3, 1, 99, 1);
	spinner.setModel(spinnerModel);
	spinner.addChangeListener(this);

	JPanel contentPane = new JPanel(new BorderLayout());
	JPanel spinnerPane = new JPanel();
	spinnerPane.add(spinner);
	contentPane.add(spinnerPane);
	this.setStretchablePane(contentPane);
	this.setBigTitle("Graad");
	this.setTitle("GraadManipulatie");
	this.setClosable(true);
	this.pack();
    }

    public void setItsGraad(Graad p_Graad) {
	this.itsGraad = p_Graad;
	spinner.setValue(new Integer(p_Graad.getValue()));
    }
    
    public Graad getItsGraad() {
	return new Graad(((Integer) spinner.getValue()).intValue());
    }

    public PuntenVenster getItsPuntenVenster() {
        return itsPuntenVenster;
    }
    
    public void __setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        itsPuntenVenster = p_PuntenVenster;
    }
    
    public void _setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        if(itsPuntenVenster != null)
            itsPuntenVenster.__setItsGraadManipulatieVenster(null);
        __setItsPuntenVenster(p_PuntenVenster);
    }
    
    public void setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        if(p_PuntenVenster != null)
            p_PuntenVenster._setItsGraadManipulatieVenster(this);
        _setItsPuntenVenster(p_PuntenVenster);
    }
    
    public void _clearItsPuntenVenster() {
        itsPuntenVenster = null;
    }
    
    public void stateChanged(ChangeEvent e) {
	if(e.getSource().equals(spinner)) {
	    itsGraad.setValue(((Integer) spinner.getValue()).intValue());
	    itsPuntenVenster.onConfiguratieChange();
	}
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GraadManipulatieVenster.java
*********************************************************************/

