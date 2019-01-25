/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: GrafiekVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GrafiekVenster.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import javax.swing.*;
import java.awt.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\GrafiekVenster.java                                                                  
//----------------------------------------------------------------------------

//## class GrafiekVenster 
public class GrafiekVenster extends Window {
    
    protected OutputVenster itsOutputVenster;
    protected GrafiekCanvas grafiekCanvas;

    protected JPanel contentPane;

    // Constructors
    
    public  GrafiekVenster() {
	super(300,300);

	contentPane = new JPanel(new BorderLayout());

	this.setStretchablePane(contentPane);

	this.setTitle("GrafiekVenster");
	this.pack();
    }
    
    public void setInputData(BasisMatrix matrix, double [] knots) {
	contentPane.removeAll();

	GrafiekCanvas grafiekCanvas = new GrafiekCanvas();
	grafiekCanvas.setInputData(matrix, knots);

	grafiekCanvas.setSize(contentPane.getSize());
	contentPane.add(grafiekCanvas);

	if(!this.isIcon())
	    this.pack();
    }

    public void setInputData(BasisMatrix [] matrices, double [] knots, int k) {
	contentPane.removeAll();

	JTabbedPane tabPane = new JTabbedPane(JTabbedPane.RIGHT);

	for(int i=0;i<matrices.length;i++) {
	    GrafiekCanvas grafiekCanvas = new GrafiekCanvas();
	    grafiekCanvas.setInputData(matrices[i], knots, k, i+1);

	    tabPane.add(i+"", grafiekCanvas);
	}

	contentPane.add(tabPane);

	if(!this.isIcon())
	    this.pack();
    }

    public OutputVenster getItsOutputVenster() {
        return itsOutputVenster;
    }
    
    public void __setItsOutputVenster(OutputVenster p_OutputVenster) {
        itsOutputVenster = p_OutputVenster;
    }
    
    public void _setItsOutputVenster(OutputVenster p_OutputVenster) {
        if(itsOutputVenster != null)
            itsOutputVenster.__setItsGrafiekVenster(null);
        __setItsOutputVenster(p_OutputVenster);
    }
    
    public void setItsOutputVenster(OutputVenster p_OutputVenster) {
        if(p_OutputVenster != null)
            p_OutputVenster._setItsGrafiekVenster(this);
        _setItsOutputVenster(p_OutputVenster);
    }
    
    public void _clearItsOutputVenster() {
        itsOutputVenster = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GrafiekVenster.java
*********************************************************************/

