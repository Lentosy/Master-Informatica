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
import java.io.*;
import java.net.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\GraadManipulatieVenster.java                                                                  
//----------------------------------------------------------------------------

//## class GraadManipulatieVenster 
public class HelpVenster extends Window {

    JEditorPane contentPane;

    public HelpVenster() {
	super(400,400);

	try {
	    String path = "/help/help.html"; 
	    URL url = getClass().getResource(path); 

	    contentPane = new JEditorPane(url);

	    JScrollPane scrollPane = new JScrollPane(contentPane);

	    this.setStretchablePane(scrollPane);
	    this.setBigTitle("Documentatie");
	    this.setTitle("HelpVenster");
	    this.pack();
	} catch (IOException e) {
	    System.out.println("help file could not be found. quitting.");
	    System.exit(1);
	}
    }
}
