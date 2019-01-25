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
public class NevilleMouseEventHandler extends MouseEventHandler implements ActionListener {

    // Constructors
    
    JPopupMenu addMenu;
    JPopupMenu moveMenu;
    JPopupMenu removeMenu;
    JRadioButtonMenuItem movePoint;
    JRadioButtonMenuItem moveDiff;
    JRadioButtonMenuItem moveDiff2;

    public NevilleMouseEventHandler() {
	super();

	moveMenu = new JPopupMenu();
	movePoint = new JRadioButtonMenuItem("verplaats punt");
	moveDiff = new JRadioButtonMenuItem("verplaats afgeleide");
	moveDiff2 = new JRadioButtonMenuItem("verplaats tweede afgeleide");

	moveMenu.add(movePoint);
	moveMenu.add(moveDiff);
	moveMenu.add(moveDiff2);

	ButtonGroup bGroup = new ButtonGroup();
	bGroup.add(movePoint);
	bGroup.add(moveDiff);
	bGroup.add(moveDiff2);

	movePoint.setSelected(true);

	movePoint.addActionListener(this);
	moveDiff.addActionListener(this);
	moveDiff2.addActionListener(this);
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mousePressed(MouseEvent e) {
	lastScreenPoint = e.getPoint();

	if(itsPuntenVenster != null) {
	    int cursorMode = itsPuntenVenster.getItsToolPane().getMode();
	    switch(cursorMode) {
	    case 0: // add
		itsPuntenVenster.getItsTekenVenster().addScreenDataPunt(e.getPoint());
		itsPuntenVenster.getItsKnopenManipulatieVenster().addKnoop();
		itsPuntenVenster.onConfiguratieChange();
		break;

	    case 1:
		itsPuntenVenster.getItsTekenVenster().removeDataPunt(itsPuntenVenster.getItsTekenVenster().getSelectedPoint());

		break;
	    case 2:
		Punt p = itsPuntenVenster.getItsTekenVenster().getSelectedPoint();
		if(p != null) {
		    moveMenu.show(itsPuntenVenster, e.getX(), e.getY());
		}
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

	    ListIterator iterD = itsPuntenVenster.getItsTekenVenster().getItsDataPunt();
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
		if(lastScreenPoint != null)
		    if(e.getPoint().distance(lastScreenPoint) < 15)
			return;
		DataPunt dp = itsPuntenVenster.getItsTekenVenster().getActiveDataPunt();
		if(dp != null) { // has a currently selected DataPoint
		    itsPuntenVenster.getItsTekenVenster().setScreenDiff1(e.getPoint(), dp);
		    itsPuntenVenster.onConfiguratieChange();
		    itsPuntenVenster.getItsTekenVenster().repaint();
		}
		break;

	    case 1: // remove

		break;

	    case 2: // move

		Punt p = itsPuntenVenster.getItsTekenVenster().getSelectedPoint();
		if(p!=null) {
		    Point2D.Double sp = itsPuntenVenster.getItsTekenVenster().getItsAssenStelsel().screenToCart(e.getX(), e.getY(), 
														itsPuntenVenster.getItsTekenVenster().getWidth(),
														itsPuntenVenster.getItsTekenVenster().getHeight());
		    if(movePoint.isSelected())
			itsPuntenVenster.getItsTekenVenster().changePunt(p, sp.getX(), sp.getY());
		    else if(moveDiff.isSelected()) {
			itsPuntenVenster.getItsTekenVenster().setScreenDiff1(p, e.getPoint());
			itsPuntenVenster.onConfiguratieChange();
		    }
		    else if(moveDiff2.isSelected()) {
			itsPuntenVenster.getItsTekenVenster().setScreenDiff2(p, e.getPoint());
			itsPuntenVenster.onConfiguratieChange();
		    }
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

