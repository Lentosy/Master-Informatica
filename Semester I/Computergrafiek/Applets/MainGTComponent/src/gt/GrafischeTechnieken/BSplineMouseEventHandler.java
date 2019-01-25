/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: MouseEventHandler
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MouseEventHandler.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\MouseEventHandler.java                                                                  
//----------------------------------------------------------------------------

//## class MouseEventHandler 
public class BSplineMouseEventHandler extends MouseEventHandler implements ActionListener {

    // Constructors
    
    JPopupMenu addMenu;
    JPopupMenu moveMenu;
    JPopupMenu removeMenu;

    public BSplineMouseEventHandler() {
	super();
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mousePressed(MouseEvent e) {

	lastScreenPoint = e.getPoint();

	if(itsPuntenVenster != null) {
	    int cursorMode = itsPuntenVenster.getItsToolPane().getMode();
	    switch(cursorMode) {
	    case 0: // add
		itsPuntenVenster.getItsTekenVenster().addScreenControlePunt(e.getPoint());
		itsPuntenVenster.getItsKnopenManipulatieVenster().addKnoop();
		itsPuntenVenster.onConfiguratieChange();
		break;

	    case 1:
		itsPuntenVenster.getItsTekenVenster().removeControlePunt(itsPuntenVenster.getItsTekenVenster().getSelectedPoint());

		break;
	    }
	}
    }

    public void mouseEntered(MouseEvent e) {
	if(itsPuntenVenster != null) {
	    int cursorMode = itsPuntenVenster.getItsToolPane().getMode();
	    switch(cursorMode) {
	    case 0:
		itsPuntenVenster.getItsTekenVenster().setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
		break;
	    case 1:
		itsPuntenVenster.getItsTekenVenster().setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
		break;
	    case 2:
		itsPuntenVenster.getItsTekenVenster().setCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
		break;
	    case 3:
		itsPuntenVenster.getItsTekenVenster().setCursor(Cursor.getPredefinedCursor(Cursor.SE_RESIZE_CURSOR));
		break;
	    case 4:
		itsPuntenVenster.getItsTekenVenster().setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		break;
	    }
	}
    }

    public void mouseExited(MouseEvent e) {
	itsPuntenVenster.getItsTekenVenster().setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseMoved(MouseEvent e) {

	boolean closePoint = false;

	if(itsPuntenVenster!=null) {
	    Point2D.Double sp = itsPuntenVenster.getItsTekenVenster().getItsAssenStelsel().screenToCart(e.getX(), e.getY(), 
													itsPuntenVenster.getItsTekenVenster().getWidth(),
													itsPuntenVenster.getItsTekenVenster().getHeight());
	    String xString = "("+((int) (100*sp.getX()))/100.0;
	    String yString = ((int) (100*sp.getY()))/100.0+")";

	    itsPuntenVenster.setSubTitle(xString+","+yString,140);

	    ListIterator iterD = itsPuntenVenster.getItsTekenVenster().getItsControlePunt();
	    while(iterD.hasNext()) {
		Punt p = (Punt) iterD.next();
		sp = itsPuntenVenster.getItsTekenVenster().getItsAssenStelsel().cartToScreen(p.getX(), p.getY(), 
											     itsPuntenVenster.getItsTekenVenster().getWidth(),
											     itsPuntenVenster.getItsTekenVenster().getHeight());
		if(sp.distance(e.getPoint()) < 15) {
		    if(itsPuntenVenster.getItsTekenVenster().getSelectedPoint() != p)
			itsPuntenVenster.getItsTekenVenster().setSelectedPoint(p);

		    closePoint = true;
		}
	    }
	    if(!closePoint)
		itsPuntenVenster.getItsTekenVenster().setSelectedPoint(null);
	}
    }

    public void mouseDragged(MouseEvent e) {
	if(itsPuntenVenster != null) {

	    int cursorMode = itsPuntenVenster.getItsToolPane().getMode();
	    switch(cursorMode) {
	    case 0: // add
		break;

	    case 1: // remove

		break;

	    case 2: // move

		Punt p = itsPuntenVenster.getItsTekenVenster().getSelectedPoint();
		if(p!=null) {
		    Point2D.Double sp = itsPuntenVenster.getItsTekenVenster().getItsAssenStelsel().screenToCart(e.getX(), e.getY(), 
														itsPuntenVenster.getItsTekenVenster().getWidth(),
														itsPuntenVenster.getItsTekenVenster().getHeight());
		    itsPuntenVenster.getItsTekenVenster().changePunt(p, sp.getX(), sp.getY());
		}
	    }
	}
    }

    public void actionPerformed(ActionEvent e) {

    }

}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\MouseEventHandler.java
*********************************************************************/

