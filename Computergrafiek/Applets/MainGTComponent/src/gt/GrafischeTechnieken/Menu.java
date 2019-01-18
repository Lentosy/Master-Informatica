/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: Menu
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Menu.java
*********************************************************************/

package GrafischeTechnieken;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\Menu.java                                                                  
//----------------------------------------------------------------------------

//## class Menu 
public class Menu extends JMenuBar {
    
    protected MenuVenster itsMenuVenster;

    JMenu fileMenu;
    JMenuItem saveItem;
    JMenuItem loadItem;
    JMenuItem save2png;

    JMenuItem quitItem;

    JMenu viewMenu;
    JMenuItem defaultView;
    JMenuItem fitToScreen;

    JMenu knopenMenu;
    JMenu curveMenu;
    JMenu windowsMenu;
    JMenu helpMenu;
    JMenuItem documentation;

    JMenuItem uniform;
    JMenuItem openUniform;
    JMenuItem toonConsole;
    JMenuItem clearConsole;
    JMenuItem graad;
    JRadioButtonMenuItem lagrange;
    JRadioButtonMenuItem bspline;
    JRadioButtonMenuItem bezier;
    JMenuItem verwijder;
    // Constructors

    public  Menu() {
	super();
	this.setLayout(new BoxLayout(this, BoxLayout.X_AXIS));

	graad = new JMenuItem("Graad...");

	fileMenu = new JMenu("File");
	fileMenu.add(saveItem = new JMenuItem("Save..."));
	fileMenu.add(loadItem = new JMenuItem("Load..."));
	fileMenu.add(save2png = new JMenuItem("Save output to image..."));
	fileMenu.addSeparator();
	fileMenu.add(quitItem = new JMenuItem("Quit"));

	viewMenu = new JMenu("View");
	viewMenu.add(defaultView = new JMenuItem("Reset View"));
	viewMenu.addSeparator();
	viewMenu.add(fitToScreen = new JMenuItem("Fit curve to View"));

	knopenMenu = new JMenu("Knopen");
	knopenMenu.add(uniform = new JMenuItem("Maak uniform"));
	knopenMenu.add(openUniform = new JMenuItem("Maak open-uniform"));

	curveMenu = new JMenu("Curve");
	JMenu typeMenu = new JMenu("Type");
	typeMenu.add(lagrange = new JRadioButtonMenuItem("Lagrange"));
	typeMenu.add(bspline = new JRadioButtonMenuItem("B-Splines"));
	typeMenu.add(bezier = new JRadioButtonMenuItem("Bézier"));
	ButtonGroup bGroup = new ButtonGroup();
	bGroup.add(lagrange); bGroup.add(bspline); bGroup.add(bezier);
	curveMenu.add(typeMenu);
	curveMenu.addSeparator();
	curveMenu.add(graad);
	curveMenu.addSeparator();
	curveMenu.add(verwijder = new JMenuItem("Verwijder curve"));

	windowsMenu = new JMenu("Console");
	windowsMenu.add(toonConsole = new JMenuItem("Toon console..."));
	windowsMenu.add(clearConsole = new JMenuItem("Clear console"));

	helpMenu = new JMenu("Help");
	helpMenu.add(documentation = new JMenuItem("Documentation"));

	// make it pwetty!!
	Color menuColor = new Color(220,220,225);
	fileMenu.setBorder(new CompoundBorder(new MatteBorder(new Insets(5,5,3,0),new Color(200,200,200)),
					      new EtchedBorder()));
	viewMenu.setBorder(new CompoundBorder(new MatteBorder(new Insets(5,0,3,0),new Color(200,200,200)),
					      new EtchedBorder()));
	knopenMenu.setBorder(new CompoundBorder(new MatteBorder(new Insets(5,0,3,0),new Color(200,200,200)),
					      new EtchedBorder()));
	curveMenu.setBorder(new CompoundBorder(new MatteBorder(new Insets(5,0,3,0),new Color(200,200,200)),
					      new EtchedBorder()));
	windowsMenu.setBorder(new CompoundBorder(new MatteBorder(new Insets(5,0,3,0),new Color(200,200,200)),
					      new EtchedBorder()));
	helpMenu.setBorder(new CompoundBorder(new MatteBorder(new Insets(5,0,3,5),new Color(200,200,200)),
					      new EtchedBorder()));
	knopenMenu.setBackground(menuColor);
	fileMenu.setBackground(menuColor);
	viewMenu.setBackground(menuColor);
	curveMenu.setBackground(menuColor);
	windowsMenu.setBackground(menuColor);
	helpMenu.setBackground(menuColor);

	menuColor = new Color(200,200,200);

	this.add(fileMenu);
	this.add(viewMenu);
	this.add(knopenMenu);
	this.add(curveMenu);
	this.add(windowsMenu);
	this.add(Box.createHorizontalGlue());
	this.add(helpMenu);

	this.setBackground(menuColor);

    }
    
    public void setTypeSelected(int newType) {
	switch(newType) {
	case 0:
	    lagrange.setSelected(true);
	    graad.setEnabled(false);
	    break;
	case 1:
	    bspline.setSelected(true);
	    graad.setEnabled(true);
	    break;
	case 2:
	    bezier.setSelected(true);
	    graad.setEnabled(false);
	    break;
	}
    }

    public void addActionListener(ActionListener menuListener) {
	saveItem.addActionListener(menuListener);
	loadItem.addActionListener(menuListener);
	save2png.addActionListener(menuListener);
	toonConsole.addActionListener(menuListener);
	clearConsole.addActionListener(menuListener);
	uniform.addActionListener(menuListener);
	openUniform.addActionListener(menuListener);
	quitItem.addActionListener(menuListener);
	lagrange.addActionListener(menuListener);
	bspline.addActionListener(menuListener);
	bezier.addActionListener(menuListener);
	graad.addActionListener(menuListener);
	verwijder.addActionListener(menuListener);
	fitToScreen.addActionListener(menuListener);
	defaultView.addActionListener(menuListener);
	documentation.addActionListener(menuListener);
    }

    public MenuVenster getItsMenuVenster() {
        return itsMenuVenster;
    }
    
    public void __setItsMenuVenster(MenuVenster p_MenuVenster) {
        itsMenuVenster = p_MenuVenster;
    }
    
    public void _setItsMenuVenster(MenuVenster p_MenuVenster) {
        if(itsMenuVenster != null)
            itsMenuVenster.__setItsMenu(null);
        __setItsMenuVenster(p_MenuVenster);
    }
    
    public void setItsMenuVenster(MenuVenster p_MenuVenster) {
        if(p_MenuVenster != null)
            p_MenuVenster._setItsMenu(this);
        _setItsMenuVenster(p_MenuVenster);
    }
    
    public void _clearItsMenuVenster() {
        itsMenuVenster = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Menu.java
*********************************************************************/

