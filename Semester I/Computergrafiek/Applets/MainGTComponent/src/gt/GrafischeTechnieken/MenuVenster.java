/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: MenuVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MenuVenster.java
*********************************************************************/

package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\MenuVenster.java                                                                  
//----------------------------------------------------------------------------

//## class MenuVenster 
public class MenuVenster extends PuntenVenster {
    
    protected Menu itsMenu;
    protected MenuEventHandler itsMenuEventHandler;
    protected MouseEventHandler itsMenuMouseEventHandler;
    
    protected HelpVenster itsHelpVenster;
    // new
    protected ConsoleVenster itsConsoleVenster;

    // Constructors
    
    public  MenuVenster() {
	super();
        this.initMenuRelations();
	setJMenuBar(itsMenu);

	//this.setTitle("MenuVenster");

	// this window will close the app
	this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	this.pack();
    }
    
    public Menu getItsMenu() {
        return itsMenu;
    }
    
    public void __setItsMenu(Menu p_Menu) {
        itsMenu = p_Menu;
    }
    
    public void _setItsMenu(Menu p_Menu) {
        if(itsMenu != null)
            itsMenu.__setItsMenuVenster(null);
        __setItsMenu(p_Menu);
    }
    
    public Menu newItsMenu() {
        itsMenu = new Menu();
        itsMenu._setItsMenuVenster(this);
        return itsMenu;
    }
    
    public void deleteItsMenu() {
        itsMenu.__setItsMenuVenster(null);
        itsMenu=null;
    }
    
    public MenuEventHandler getItsMenuEventHandler() {
        return itsMenuEventHandler;
    }
    
    public void __setItsMenuEventHandler(MenuEventHandler p_MenuEventHandler) {
        itsMenuEventHandler = p_MenuEventHandler;
    }
    
    public void _setItsMenuEventHandler(MenuEventHandler p_MenuEventHandler) {
        if(itsMenuEventHandler != null)
            itsMenuEventHandler.__setItsMenuVenster(null);
        __setItsMenuEventHandler(p_MenuEventHandler);
    }
    
    public MenuEventHandler newItsMenuEventHandler() {
        itsMenuEventHandler = new MenuEventHandler();
        itsMenuEventHandler._setItsMenuVenster(this);
        return itsMenuEventHandler;
    }
    
    public void deleteItsMenuEventHandler() {
        itsMenuEventHandler.__setItsMenuVenster(null);
        itsMenuEventHandler=null;
    }
    
    public MouseEventHandler getItsMenuMouseEventHandler() {
        return itsMenuMouseEventHandler;
    }
    
    public MouseEventHandler newItsMenuMouseEventHandler() {
        // itsMenuMouseEventHandler = new MouseEventHandler();
        return itsMenuMouseEventHandler;
    }
    
    public void deleteItsMenuMouseEventHandler() {
        itsMenuMouseEventHandler=null;
    }
    
    public ConsoleVenster getItsConsoleVenster() {
	return itsConsoleVenster;
    }

    public void setItsConsoleVenster(ConsoleVenster p_ConsoleVenster) {
	itsConsoleVenster = p_ConsoleVenster;
    }

    public HelpVenster getItsHelpVenster() {
	return itsHelpVenster;
    }

    protected void initMenuRelations() {
        itsMenu = newItsMenu();
        itsMenuEventHandler = newItsMenuEventHandler();
        itsMenuMouseEventHandler = newItsMenuMouseEventHandler();
	itsMenu.addActionListener(itsMenuEventHandler);
	itsHelpVenster = new HelpVenster();
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MenVenster.java
*********************************************************************/

