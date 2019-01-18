/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: KnopenManipulatieVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\KnopenManipulatieVenster.java
*********************************************************************/

package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.imageio.*;
import java.io.*;
import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\KnopenManipulatieVenster.java                                                                  
//----------------------------------------------------------------------------

//## class KnopenManipulatieVenster 
public class KnopenManipulatieVenster extends Canvas  
    implements ComponentListener, MouseMotionListener, MouseListener {
    
    protected LinkedList itsKnoop;
    protected PuntenVenster itsPuntenVenster;

    private static final Font miniFont = new Font("Monospaced", Font.PLAIN, 10);
    private static final Font fatFont = new Font("Monospaced", Font.PLAIN, 12);

    private static Stroke dashedLine;
    private static Stroke dottedLine;

    int knotDragged;

    // Constructors
    
    public  KnopenManipulatieVenster() {
	super(false);

	this.addComponentListener(this);
	this.addMouseListener(this);
	this.addMouseMotionListener(this);

	float[] dashf = {4.0f,2.0f};
	dashedLine = new BasicStroke(1.0f, 0,
				   0,
				   1.0f,
				   dashf,
				   0.0f);

	float[] dashf2 = {1.0f,2.0f};
	dottedLine = new BasicStroke(1.0f, 0,
				   0,
				   1.0f,
				   dashf2,
				   0.0f);

	knotDragged = -1;

        {
            itsKnoop=new LinkedList();
        }
    }
    
    public void drawGrid() {
	super.redrawGrid();

	gridBufG.setColor(Color.darkGray);
	gridBufG.setStroke(dottedLine);

	if(itsKnoop.size() > 0) {
	    double scale = (double) (mWidth-60) / (double) (itsKnoop.size()-1);
	    gridBufG.setColor(new Color(150,150,150));
	    for(double id=0; id*scale < mWidth-60; id+=0.25) {
		gridBufG.drawLine((int) (id*scale)+30, mHeight, (int) (id*scale)+30, 0);
	    }	
	    gridBufG.setColor(Color.darkGray);
	    for(int i=0; i<itsKnoop.size(); i++) {
		gridBufG.drawLine((int) (i*scale)+30, mHeight, (int) (i*scale)+30, 0);
	    }
	}
    }

    public void paintComponent(Graphics g) {
	Graphics2D g2 = (Graphics2D) g;
	
	g2.drawImage(gridBuf, 0, 0, mWidth, mHeight, this);
	//g2.setColor(new Color(200, 200, 200));
	//g2.fillRect(0, 0, mWidth, mHeight);

	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);

	if(itsKnoop.size()>0) {
	    g2.setColor(Color.darkGray);
	    g2.setStroke(dashedLine);
	    g2.drawLine(10,mHeight/2,mWidth-10,mHeight/2);

	    g2.setStroke(new BasicStroke());
	    drawKnots(g2);
	}

    }

    public void drawKnots(Graphics2D g) {
	ListIterator iter = getItsKnoop();

	int i = 0;

	double last = ((Knoop) itsKnoop.getLast()).getValue();
	double scale = (double) (mWidth-60)/last;

	String vector = "";

	while(iter.hasNext()) {
	    Knoop k = (Knoop) iter.next();

	    if(i != knotDragged) {
		g.setColor(new Color(220,220,230));
		g.fillOval((int) (k.getValue()*scale)+30-6, mHeight/2-6, 12, 12);

		g.setColor(Color.darkGray);
		g.drawOval((int) (k.getValue()*scale)+30-6, mHeight/2-6, 12, 12);
		g.fillOval((int) (k.getValue()*scale)+30 - 1, mHeight/2 - 1, 
			   3, 3);

		g.setColor(new Color(200,200,200));
		g.fillRect((int) (k.getValue()*scale)+30-8, mHeight-18, 15, 10);

		g.setColor(Color.darkGray);
		g.setFont(miniFont);
		g.drawString(i+"", (int) (k.getValue()*scale)+30-3, mHeight-10);
	    }
	    else {
		g.setColor(new Color(240,200,200,128));
		g.fillRect((int) (k.getValue()*scale)+30-6, mHeight/2-6, 12, 12);

		g.setColor(Color.black);
		g.drawRect((int) (k.getValue()*scale)+30-6, mHeight/2-6, 12, 12);

		g.setColor(new Color(200,200,200));
		g.fillRect((int) (k.getValue()*scale)+30-8, mHeight-18, 15, 10);

		g.setColor(Color.darkGray);
		g.setFont(miniFont);
		g.drawString(i+"", (int) (k.getValue()*scale)+30-3, mHeight-10);

		String valString = k.getValue()+"";
		g.setColor(new Color(200,240,200));
		g.fillRect( (int) (k.getValue()*scale)+30-20, mHeight-52, valString.length()*6+10, 15);
		g.setColor(Color.darkGray);
		g.drawRect( (int) (k.getValue()*scale)+30-20, mHeight-52, valString.length()*6+10, 15);
		g.drawString(valString, (int) (k.getValue()*scale)+30-15, mHeight-40);
	    }

	    i++;
	}
    }


    public void knotsChanged() {
	itsPuntenVenster.getItsGrafischeEngine().berekenCurve();
    }

    // adds a knot trying to be uniform 
    // with the already existing knots
    public void addKnoop() {
	int len = itsKnoop.size();
	_addItsKnoop(new Knoop((double) len));
    }

    public void clearItsKnoop() {
	itsKnoop = new LinkedList();
    }

    public ListIterator getItsKnoop() {
        ListIterator iter=itsKnoop.listIterator(0);
        return iter;
    }
    
    public ListIterator getItsKnoopEnd() {
        return itsKnoop.listIterator(itsKnoop.lastIndexOf(itsKnoop.getLast()));
    }
    
    public void _addItsKnoop(Knoop p_Knoop) {
        itsKnoop.add(p_Knoop);

	drawGrid();
	repaint();
    }
    
    public void setItsKnoop(LinkedList itsKnoop) {
	this.itsKnoop = itsKnoop;

	if(itsKnoop.size() > 0) {
	    drawGrid();
	}

	repaint();
    }

    public Knoop newItsKnoop() {
        Knoop newKnoop = new Knoop();
        newKnoop._setItsKnopenManipulatieVenster(this);
        itsKnoop.add(newKnoop);
        return newKnoop;
    }
    
    public void _removeItsKnoop(Knoop p_Knoop) {
        itsKnoop.remove(p_Knoop);
    }
    
    public void deleteItsKnoop(Knoop p_Knoop) {
        p_Knoop._setItsKnopenManipulatieVenster(null);
        itsKnoop.remove(p_Knoop);
        p_Knoop=null;
    }
    
    public PuntenVenster getItsPuntenVenster() {
        return itsPuntenVenster;
    }
    
    public void __setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        itsPuntenVenster = p_PuntenVenster;
    }
    
    public void _setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        if(itsPuntenVenster != null)
            itsPuntenVenster.__setItsKnopenManipulatieVenster(null);
        __setItsPuntenVenster(p_PuntenVenster);
    }
    
    public void setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        if(p_PuntenVenster != null)
            p_PuntenVenster._setItsKnopenManipulatieVenster(this);
        _setItsPuntenVenster(p_PuntenVenster);
    }
    
    public void _clearItsPuntenVenster() {
        itsPuntenVenster = null;
    }

    public void componentHidden(ComponentEvent e) {

    }

    public void componentMoved(ComponentEvent e) {

    }

    public void componentResized(ComponentEvent e) {
	mWidth = getWidth();
	mHeight = getHeight();

	redrawGrid();
	drawGrid();
	repaint();
    }

    public void componentShown(ComponentEvent e) {

    }
    
    public void mousePressed(MouseEvent e) {
	ListIterator iter = getItsKnoop();

	if(iter.hasNext())
	    iter.next();

	if(itsKnoop.size() > 0) {
	    double last = ((Knoop) itsKnoop.getLast()).getValue();
	    double scale = (double) (mWidth-60)/last;

	    for(int i=1; i<itsKnoop.size()-1; i++) {
		Knoop k = (Knoop) iter.next();

		Point kp = new Point((int) (k.getValue()*scale)+30, 
				     mHeight/2);
		Point p = e.getPoint();
		
		if(p.distance(kp) < 12) {
		    knotDragged = i;
		    repaint();
		    break;
		}
	    }
	}
    }

    public void mouseClicked(MouseEvent e) {

    }

    public void mouseEntered(MouseEvent e) {

    }

    public void mouseExited(MouseEvent e) {

    }

    public void mouseMoved(MouseEvent e) {

    }

    public void mouseDragged(MouseEvent e) {
	if(knotDragged > 0) {
	    double last = ((Knoop) itsKnoop.getLast()).getValue();
	    double scale = (double) (mWidth-60)/last;

	    Knoop k = (Knoop) itsKnoop.get(knotDragged);
	    Knoop nk = (Knoop) itsKnoop.get(knotDragged + 1);
	    Knoop pk = (Knoop) itsKnoop.get(knotDragged - 1);

	    if((e.getX()-30)/scale > pk.getValue() && 
	       (e.getX()-30)/scale < nk.getValue()) {		
		k.setValue((e.getX()-30)/scale);
		knotsChanged();
		itsPuntenVenster.getItsTekenVenster().repaint();
		repaint();		
	    }
	}
    }

    public void mouseReleased(MouseEvent e) {
	if(knotDragged > 0) {
	    knotDragged = -1;
	    repaint();
	}
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\KnopenManipulatieVenster.java
*********************************************************************/

