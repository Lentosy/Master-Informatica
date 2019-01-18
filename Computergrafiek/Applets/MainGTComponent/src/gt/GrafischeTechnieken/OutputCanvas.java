package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.geom.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class OutputCanvas extends Canvas implements ComponentListener, AssenStelselListener {

    Kromme itsKromme;
    Kromme [] itsSplines;

    boolean isSplines;
    GebruikersInterface itsGebruikersInterface;
    AssenStelsel itsAssenStelsel;

    BufferedImage curveBuffer;
    static Stroke dotDash;

    Rectangle2D assenStelselMark;

    public OutputCanvas(GebruikersInterface GUI) {
	super(true);

	itsAssenStelsel = new AssenStelsel();

	float [] dash2f = {1.0f,3.0f};
	dotDash = new BasicStroke(1.0f, 0,
				  2,
				  1.0f,
				  dash2f,
				  1.0f);

	ZoomBoxHandler zbl = new ZoomBoxHandler(this, itsAssenStelsel);

	this.addMouseMotionListener(zbl);
	this.addMouseListener(zbl);

	this.itsGebruikersInterface = GUI;

	this.setBorder(new EtchedBorder());
 
	this.addComponentListener(this);
    }

    public void paintComponent(Graphics G) {

	G.drawImage(curveBuffer, 0, 0, this);

	Graphics2D g2 = (Graphics2D) G;
	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);

	if(assenStelselMark!=null) {
	    g2.setColor(new Color(180,180,180,180));
	    g2.fill(assenStelselMark);
	    g2.setColor(new Color(255,255,255));
	    Point m = assenStelselMark.getBounds().getLocation();
	    m.translate((int) assenStelselMark.getWidth()/2,
			(int) assenStelselMark.getHeight()/2);

	    g2.setStroke(dotDash);
	    g2.drawLine((int) assenStelselMark.getX(), (int) m.getY(), 
			(int) (assenStelselMark.getX()+assenStelselMark.getWidth()), (int) m.getY());
	    g2.drawLine((int) m.getX(), (int) assenStelselMark.getY(), 
			    (int) m.getX(), (int) (assenStelselMark.getY()+assenStelselMark.getHeight()));

		g2.setStroke(new BasicStroke());
		g2.fillOval((int) m.getX() - 3, (int) m.getY() - 3, 7, 7);
		g2.setColor(new Color(128,128,128,200));
		g2.drawOval((int) m.getX() - 3, (int) m.getY() - 3, 7, 7);

		g2.setColor(Color.darkGray);
		g2.draw(assenStelselMark);
	}
    }

    public void paintKromme(Graphics2D G) {

	G.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER));
	G.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);

	G.setColor(new Color(230,230,230));
	G.fillRect(0,0,getWidth(), getHeight());

	if(itsKromme == null)
	    return;

	double [] xItsKromme = itsKromme.getXCurve();
	double [] yItsKromme = itsKromme.getYCurve();
	int [] sItsKrommeX = new int[xItsKromme.length];
	int [] sItsKrommeY = new int[yItsKromme.length];

	Rectangle rect = G.getClipBounds();
	int bufW = getWidth();
	int bufH = getHeight();


	for(int i=0;i<xItsKromme.length;i++) {
	    Point2D.Double sP = itsAssenStelsel.cartToScreen(xItsKromme[i],
						    yItsKromme[i],
						    (double) bufW,
						    (double) bufH);
	    sItsKrommeX[i] = (int) sP.getX();

	    sItsKrommeY[i] = (int) sP.getY();
	}

	G.setColor(new Color(80,50,80));
	G.setStroke(new BasicStroke(2.0f,0,BasicStroke.JOIN_ROUND));
	G.drawPolyline(sItsKrommeX, sItsKrommeY, xItsKromme.length);
    }

    public void paintSplines(Graphics2D G) {
	G.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER));
	G.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);

	G.setColor(new Color(230,230,230));
	G.fillRect(0,0,getWidth(), getHeight());

	if(itsSplines == null)
	    return;

	for(int nSeg=0; nSeg<itsSplines.length; nSeg++) {
	    double [] xItsKromme = itsSplines[nSeg].getXCurve();
	    double [] yItsKromme = itsSplines[nSeg].getYCurve();
	    int [] sItsKrommeX = new int[xItsKromme.length];
	    int [] sItsKrommeY = new int[yItsKromme.length];

	    Rectangle rect = G.getClipBounds();
	    int bufW = getWidth();
	    int bufH = getHeight();


	    for(int i=0;i<xItsKromme.length;i++) {
		Point2D.Double sP = itsAssenStelsel.cartToScreen(xItsKromme[i],
								 yItsKromme[i],
								 (double) bufW,
								 (double) bufH);
		sItsKrommeX[i] = (int) sP.getX();

		sItsKrommeY[i] = (int) sP.getY();
	    }

	    G.setColor(new Color(80,50,80));
	    G.setStroke(new BasicStroke(2.0f,0,BasicStroke.JOIN_ROUND));
	    G.drawPolyline(sItsKrommeX, sItsKrommeY, xItsKromme.length);
	}
    }

    public void setItsKromme(Kromme p_Kromme) {
	this.itsKromme = p_Kromme;
	isSplines = false;
	if(curveBuffer!=null && getWidth()>0 && getHeight()>0) {
	    paintKromme(curveBuffer.createGraphics());
	    repaint();
	}
    }
  
    public void setItsSplines(Kromme [] segments) {
	this.itsSplines = segments;
	isSplines = true;
	if(curveBuffer!=null && getWidth()>0 && getHeight()>0) {
	    paintSplines(curveBuffer.createGraphics());
	    repaint();
	}
    }

    public Image getCurveBuffer() {
	return curveBuffer;
    }

    public void componentHidden(ComponentEvent e) {

    }

    public void componentMoved(ComponentEvent e) {

    }

    public void componentResized(ComponentEvent e) {
	curveBuffer = new BufferedImage(getWidth(),getHeight(),BufferedImage.TYPE_INT_RGB);

	if(!isSplines)
	    paintKromme(curveBuffer.createGraphics());
	if(isSplines)
	    paintSplines(curveBuffer.createGraphics());
    }

    public void componentShown(ComponentEvent e) {

    }

    public void assenStelselChanged(double xMin, double yMin, double xMax, double yMax) {
	itsAssenStelsel.setBounds(xMin, yMin, xMax, yMax);
	this.assenStelselMark = null;
	if(itsKromme!=null && !isSplines)
	    paintKromme(curveBuffer.createGraphics());
	else if(isSplines && itsSplines!=null)
	    paintSplines(curveBuffer.createGraphics());
	repaint();
    }

    public void setAssenStelselMark(Rectangle2D r) {
	this.assenStelselMark = r;
	repaint();
    }

    public double getWidthOnScreen() {
	return getWidth();
    }

    public double getHeightOnScreen() {
	return getHeight();
    }

    public JComponent getAsComponent() {
	return this;
    }

    public void defaultView() {
	assenStelselChanged(-100.0, -100.0, 100.0, 100.0);
    }

    public void recenter(double x, double y) {
	assenStelselChanged(x+itsAssenStelsel.getXMin(), y+itsAssenStelsel.getYMin(), x+itsAssenStelsel.getXMax(), y+itsAssenStelsel.getYMax());
    }

    public void fitToScreen() {
	if(!isSplines)
	    fitKrommeToScreen();
	else
	    fitSplinesToScreen();
    }

    public void fitKrommeToScreen() {
	if(itsKromme!=null) {
	    double [] xCurve = itsKromme.getXCurve();
	    double [] yCurve = itsKromme.getYCurve();

	    double xMin = -100, yMin = -100, yMax = 100, xMax = 100;

	    xMin = xMax = xCurve[0];
	    yMin = yMax = yCurve[0];

	    for(int i=0;i<xCurve.length;i++) {
		if(xCurve[i] < xMin)
		    xMin = xCurve[i];
		if(xCurve[i] > xMax)
		    xMax = xCurve[i];

		if(yCurve[i] < yMin)
		    yMin = yCurve[i];
		if(yCurve[i] > yMax)
		    yMax = yCurve[i];
	    }
	    if(xMin!=xMax && yMax!=yMin)
		assenStelselChanged(xMin*1.1, yMin*1.1, xMax*1.1, yMax*1.1);
	}
    }

    private void fitSplinesToScreen() {
	double xMin = -100, yMin = -100, yMax = 100, xMax = 100;

	if(itsSplines==null)
	    return;

	xMin = xMax = itsSplines[0].getXCurve()[0];
	yMin = yMax = itsSplines[0].getYCurve()[0];

	for(int nSegment=0;nSegment<itsSplines.length;nSegment++) {
		double [] xCurve = itsSplines[nSegment].getXCurve();
		double [] yCurve = itsSplines[nSegment].getYCurve();

		for(int i=0;i<xCurve.length;i++) {
		    if(xCurve[i] < xMin)
			xMin = xCurve[i];
		    if(xCurve[i] > xMax)
			xMax = xCurve[i];

		    if(yCurve[i] < yMin)
			yMin = yCurve[i];
		    if(yCurve[i] > yMax)
			yMax = yCurve[i];
		}

		if(xMin!=xMax && yMax!=yMin)
		    assenStelselChanged(xMin*1.1, yMin*1.1, xMax*1.1, yMax*1.1);
	}
    }
}
