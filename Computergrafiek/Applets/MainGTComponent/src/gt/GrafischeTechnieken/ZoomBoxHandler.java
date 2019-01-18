package GrafischeTechnieken;

import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;

public class ZoomBoxHandler implements MouseListener, MouseMotionListener, ActionListener {

    boolean needsToolPane;

    GTToolPane toolPane;
    AssenStelselListener target;
    AssenStelsel assenStelsel;

    // store the last selected screenpoint
    Point lastScreenPoint;
    Point nPoint;

    boolean draggingBox;

    JPopupMenu zoomMenu;
    JMenuItem boxZoom;

    public ZoomBoxHandler(AssenStelselListener target, AssenStelsel assenStelsel, GTToolPane toolPane) {
	this.target = target;
	this.assenStelsel = assenStelsel;
	this.toolPane = toolPane;

	needsToolPane = true;

	makeZoomMenu();
    }

    public ZoomBoxHandler(AssenStelselListener target, AssenStelsel assenStelsel) {
	this.target = target;
	this.assenStelsel = assenStelsel;

	needsToolPane = false;

	makeZoomMenu();
    }

    public void makeZoomMenu() {
	zoomMenu = new JPopupMenu();
	zoomMenu.add(boxZoom = new JMenuItem("Use dragged box"));
	JMenuItem fitToScreen, defaultView;

	zoomMenu.add(fitToScreen = new JMenuItem("Fit to screen"));
	zoomMenu.add(defaultView = new JMenuItem("Default view"));

	target.getAsComponent().add(zoomMenu);

	boxZoom.setEnabled(false);

	boxZoom.addActionListener(this);
	fitToScreen.addActionListener(this);
	defaultView.addActionListener(this);
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mousePressed(MouseEvent e) {
	if((needsToolPane&&toolPane.getMode()==3) || !needsToolPane)
	    lastScreenPoint = e.getPoint();
	if(needsToolPane&&toolPane.getMode()==4) {
	    Point2D.Double centerP = assenStelsel.screenToCart(e.getX(), e.getY(), 
							       target.getWidthOnScreen(), target.getHeightOnScreen());
	    target.recenter(centerP.getX(), centerP.getY());
	}
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
	if((needsToolPane&&toolPane.getMode()==3) || !needsToolPane) {
	    nPoint = e.getPoint();

	    if(lastScreenPoint!=null)
		zoomMenu.show(e.getComponent(), e.getX(), e.getY());
	}
    }

    public void mouseMoved(MouseEvent e) {
    }

    public void mouseDragged(MouseEvent e) {
	if((needsToolPane&&toolPane.getMode()==3) || !needsToolPane) {
	    if(lastScreenPoint!=null) {
		draggingBox = true;
		boxZoom.setEnabled(true);
		Rectangle r = new Rectangle();
		r.setRect(lastScreenPoint.getX(), lastScreenPoint.getY(), 
			  e.getPoint().getX() - lastScreenPoint.getX(),
			  e.getPoint().getY() - lastScreenPoint.getY());
		target.setAssenStelselMark(r);
	    }
	}
    }

    public void actionPerformed(ActionEvent e) {
	String str = e.getActionCommand();
	if(str.equals("Use dragged box"))
	    zoomWithBox();
	if(str.equals("Fit to screen"))
	    target.fitToScreen();
	if(str.equals("Default view"))
	    target.defaultView();

	    boxZoom.setEnabled(false);
	    draggingBox = false;
	    lastScreenPoint = null;
    }

    public void zoomWithBox() {
	if(draggingBox) {
	    double xMin;
	    double yMin;
	    double xMax;
	    double yMax;

	    Point2D.Double firstP = assenStelsel.screenToCart(lastScreenPoint.getX(), lastScreenPoint.getY(), 
						 target.getWidthOnScreen(), target.getHeightOnScreen());

	    Point2D.Double lastP = assenStelsel.screenToCart(nPoint.getX(), nPoint.getY(), 
							     target.getWidthOnScreen(), target.getHeightOnScreen());
	    xMin = Math.min(firstP.getX(), lastP.getX());
	    xMax = Math.max(firstP.getX(), lastP.getX());
	    yMin = Math.min(firstP.getY(), lastP.getY());
	    yMax = Math.max(firstP.getY(), lastP.getY());


	    target.assenStelselChanged(xMin, yMin, xMax, yMax);
	}
    }
}




