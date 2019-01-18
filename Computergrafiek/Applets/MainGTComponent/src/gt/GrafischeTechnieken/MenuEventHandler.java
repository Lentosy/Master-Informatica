/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: MenuEventHandler
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MenuEventHandler.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.util.*;


//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\MenuEventHandler.java                                                                  
//----------------------------------------------------------------------------

//## class MenuEventHandler 
public class MenuEventHandler implements ActionListener {
    
    protected MenuVenster itsMenuVenster;
    
    // Constructors
    
    public  MenuEventHandler() {
    }

    public void actionPerformed(ActionEvent e) {
	String str = e.getActionCommand();

	if(str.equals("Quit")) {
	    System.exit(1);
	}
	if(str.equals("Toon console...")) {
	    itsMenuVenster.getItsConsoleVenster().show();
	    itsMenuVenster.getItsConsoleVenster().setExtendedState(Frame.NORMAL);

	}
	if(str.equals("Graad...")) {
	    itsMenuVenster.getItsGraadManipulatieVenster().show();
	}
	if(str.equals("Lagrange")) {
	    itsMenuVenster.getCurveSelectPane().veranderType(0);
	}
	if(str.equals("B-Splines")) {
	    itsMenuVenster.getCurveSelectPane().veranderType(1);
	}
	if(str.equals("Bézier")) {
	    itsMenuVenster.getCurveSelectPane().veranderType(2);
	}
	if(str.equals("Verwijder curve")) {
	    itsMenuVenster.getItsConsoleVenster().verwijderCurve();
	    itsMenuVenster.getItsGrafischeEngine().berekenCurve();
	}
	if(str.equals("Maak uniform")) {
	    itsMenuVenster.getItsGrafischeEngine().maakUniform();
	    itsMenuVenster.getItsGrafischeEngine().berekenCurve();
	}
	if(str.equals("Maak open-uniform")) {
	    itsMenuVenster.getItsGrafischeEngine().maakOpenUniform();
	    itsMenuVenster.getItsGrafischeEngine().berekenCurve();
	}
	if(str.equals("Reset View")) {
	    itsMenuVenster.getItsTekenVenster().defaultView();
	}
	if(str.equals("Fit curve to View")) {
	    itsMenuVenster.getItsTekenVenster().fitToScreen();
	}
	if(str.equals("Save...")) {
	    String filename = "";
	    JFileChooser chooser = new JFileChooser("curvefiles");
	    int returnVal = chooser.showSaveDialog(itsMenuVenster.getItsConsoleVenster());
	    if(returnVal == JFileChooser.APPROVE_OPTION) {
		filename = chooser.getSelectedFile().getName();
		itsMenuVenster.getItsConsoleVenster().save("curvefiles/"+filename);
	    }
	}
	if(str.equals("Documentation")) {
	    try {
		itsMenuVenster.getItsHelpVenster().setIcon(false);
		itsMenuVenster.getItsHelpVenster().setSelected(true);
		itsMenuVenster.getItsHelpVenster().show();
	    } catch (java.beans.PropertyVetoException pve) {System.out.println("oops");}
	}
	if(str.equals("Load...")) {
	    String filename = "";
	    JFileChooser chooser = new JFileChooser("curvefiles");
	    int returnVal = chooser.showOpenDialog(itsMenuVenster.getItsConsoleVenster());
	    if(returnVal == JFileChooser.APPROVE_OPTION) {
		filename = chooser.getSelectedFile().getName();
		itsMenuVenster.getItsConsoleVenster().load("curvefiles/"+filename);
		itsMenuVenster.getItsGrafischeEngine().berekenCurve();
	    }
	}
	if(str.equals("Save output to image...")) {
	    String filename = "";
	    JFileChooser chooser = new JFileChooser("pngfiles");
	    int returnVal = chooser.showSaveDialog(itsMenuVenster.getItsConsoleVenster());
	    if(returnVal == JFileChooser.APPROVE_OPTION) {
		filename = chooser.getSelectedFile().getName();
		itsMenuVenster.getItsConsoleVenster().save2png("pngfiles/"+filename);
	    }
	}
	if(str.equals("Clear console")) {
	    itsMenuVenster.getItsConsoleVenster().getItsTextArea().setText("");
	}
    }

    public MenuVenster getItsMenuVenster() {
        return itsMenuVenster;
    }
    
    public void __setItsMenuVenster(MenuVenster p_MenuVenster) {
        itsMenuVenster = p_MenuVenster;
    }
    
    public void _setItsMenuVenster(MenuVenster p_MenuVenster) {
        if(itsMenuVenster != null)
            itsMenuVenster.__setItsMenuEventHandler(null);
        __setItsMenuVenster(p_MenuVenster);
    }
    
    public void setItsMenuVenster(MenuVenster p_MenuVenster) {
        if(p_MenuVenster != null)
            p_MenuVenster._setItsMenuEventHandler(this);
        _setItsMenuVenster(p_MenuVenster);
    }
    
    public void _clearItsMenuVenster() {
        itsMenuVenster = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MenuEventHandler.java
*********************************************************************/

