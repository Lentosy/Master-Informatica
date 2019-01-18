package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.imageio.*;
import java.io.*;

public class GrafiekCanvas extends Canvas implements ComponentListener, AssenStelselListener {

    double [][] xPoints;
    double [][] yPoints;

    double knotStart;
    double knotEnd;
    double yMax;
    double yMin;
    double [] knots;
    BasicStroke dotDash;

    Rectangle2D assenStelselMark;

    protected AssenStelsel assenStelsel;
    protected BasisMatrix matrix;

    int k;

    public GrafiekCanvas() {
	super(false);
	assenStelsel = new AssenStelsel();
	this.addComponentListener(this);

	ZoomBoxHandler zbl = new ZoomBoxHandler(this, assenStelsel);

	this.addMouseMotionListener(zbl);
	this.addMouseListener(zbl);

	float [] dash2f = {1.0f,2.0f};
	dotDash = new BasicStroke(1.0f, 0,
			      0,
			      1.0f,
			      dash2f,
			      1.0f);
    }

    public void paintComponent(Graphics g) {

	Graphics2D g2 = (Graphics2D) g;
	

	g2.setColor(new Color(200,200,200));
	g2.fillRect(0,0,mWidth, mHeight);
	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);


	if(matrix!=null) {

	    BasicStroke thickStroke = new BasicStroke(5.0f);
	    Point2D.Double p1, p2;

	    for(int i=0; i<knots.length; i++) {
		p1 = assenStelsel.cartToScreen(knots[i], yMin, getWidth(), getHeight());
		p2 = assenStelsel.cartToScreen(knots[i], yMax, getWidth(), getHeight());
		g2.setColor(new Color(150,150,150,70));
		g2.setStroke(thickStroke);
		g2.drawLine((int) p1.getX(), (int) p1.getY(), (int) p2.getX(), (int) p2.getY());
		g2.setColor(new Color(250,250,250));
		g2.setStroke(dotDash);
		g2.drawLine((int) p1.getX(), (int) p1.getY(), (int) p2.getX(), (int) p2.getY());
	    }
	    int [][] xCurve = new int [matrix.getSize()][xPoints[0].length];
	    int [][] yCurve = new int [matrix.getSize()][yPoints[0].length];

	    for(int pi=0;pi<matrix.getSize();pi++) {
		for(int i=0; i<xPoints[0].length;i++) {
		    Point2D.Double sP = assenStelsel.cartToScreen(xPoints[pi][i], yPoints[pi][i], getWidth(), getHeight());
		    xCurve[pi][i] = (int) sP.getX();
		    yCurve[pi][i] = (int) sP.getY();
		}
	    }

	    g2.setColor(Color.black);
	    for(int pi=0;pi<matrix.getSize();pi++) {
		g2.setColor(new Color(255,255,255,120));
		g2.setStroke(new BasicStroke(5.0f));
		g2.drawPolyline(xCurve[pi], yCurve[pi], xCurve[0].length);
		g2.setStroke(new BasicStroke(1.0f));
		g2.setColor(Color.getHSBColor((float) ((float) pi/(float) matrix.getSize()),0.9f,0.4f));
		g2.drawPolyline(xCurve[pi], yCurve[pi], xCurve[0].length);
	    }

	    g2.setStroke(new BasicStroke(2.0f));
	    g2.setColor(Color.black);
	    p1 = assenStelsel.cartToScreen(knots[0], yMin, getWidth(), getHeight());
	    p2 = assenStelsel.cartToScreen(knots[0], yMax, getWidth(), getHeight());
	    g2.drawLine((int) p1.getX(), (int) p1.getY(), (int) p2.getX(), (int) p2.getY());
	    p1 = assenStelsel.cartToScreen(knotEnd, yMin, getWidth(), getHeight());
	    p2 = assenStelsel.cartToScreen(knotEnd, yMax, getWidth(), getHeight());
	    g2.drawLine((int) p1.getX(), (int) p1.getY(), (int) p2.getX(), (int) p2.getY());
	    g2.setStroke(new BasicStroke());
	    p1 = assenStelsel.cartToScreen(knotStart, 0, getWidth(), getHeight());
	    p2 = assenStelsel.cartToScreen(knotEnd, 0, getWidth(), getHeight());
	    g2.drawLine((int) p1.getX(), (int) p1.getY(), (int) p2.getX(), (int) p2.getY());

	    g2.setStroke(new BasicStroke());
	    for(int i=0; i<knots.length; i++) {
		Point2D.Double pKnot =  assenStelsel.cartToScreen(knots[i], 0, 
							 getWidth(), getHeight());
		g2.setColor(Color.white);
		g2.fillOval((int)pKnot.getX()-5, (int) pKnot.getY()-5, 10, 10);
		g2.setColor(Color.black);
		g2.drawOval((int)pKnot.getX()-5, (int) pKnot.getY()-5, 10, 10);
		g2.drawLine((int)pKnot.getX(), (int) pKnot.getY(), (int)pKnot.getX(), (int) pKnot.getY());
	    }
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
    }

    public void recalcCurves() {
	boolean minmax = false;
	yMax = 0;
	yMin = 0;

	double density = 100.0;

	if(matrix!=null && knots!=null) {
	    xPoints = new double [matrix.getSize()][(int) density+1];
	    yPoints = new double [matrix.getSize()][(int) density+1];

	    for(int pi=0;pi<matrix.getSize();pi++) {
		int i=0;
		for(double xf=knotStart;i<(int) density;
		    xf+=(knotEnd - knotStart)/density, i++) {
		    double yf = matrix.eval(pi,xf);
		    xPoints[pi][i] = xf;
		    yPoints[pi][i] = yf;
		    if(!minmax) {
			yMin = yMax = yf;
			minmax = true;
		    }
		    else {
			if(yf<yMin)
			    yMin = yf;
			if(yf>yMax)
			    yMax = yf;
		    }
		}
		double xf = knotEnd;
		double yf = matrix.eval(pi,xf);
		xPoints[pi][i] = xf;
		yPoints[pi][i] = yf;
	    }
	    // 	    System.out.println(yMin+","+yMax+","+density);
	    assenStelsel.setBounds(knotStart-0.1, 11.0*yMin/10.0, knotEnd+0.1, 11.0*yMax/10.0);
	}
    }

    public void setInputData(BasisMatrix matrix, double [] knots) {
	this.matrix = matrix;

	if(knots.length>0) {
	this.knotStart = knots[0];
	this.knotEnd = knots[knots.length-1];
	this.knots = knots;
	} else this.knots = null;

	recalcCurves();

	repaint();
    }    

    public void setInputData(BasisMatrix matrix, double [] knots, int k, int firstKnotIndex) {
	this.matrix = matrix;

	this.knotStart = knots[firstKnotIndex];
	this.knotEnd = knots[firstKnotIndex + 2*k - 3];
	this.knots = knots;
	this.k = k;

	recalcCurves();

	repaint();
    }    

    public void componentHidden(ComponentEvent e) {

    }

    public void componentMoved(ComponentEvent e) {

    }

    public void componentResized(ComponentEvent e) {
	mWidth = getWidth();
	mHeight = getHeight();

	//if(mWidth > 0 && mHeight > 0)
	    // drawGrid();

	repaint();
    }

    public void componentShown(ComponentEvent e) {
    }

    public void assenStelselChanged(double xMin, double yMin, double xMax, double yMax) {
	if(xMin!=xMax && yMax!=yMin)
	    assenStelsel.setBounds(xMin, yMin, xMax, yMax);
	this.assenStelselMark = null;
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
	assenStelsel.setBounds(knotStart-0.1, 11.0*yMin/10.0, knotEnd+0.1, 11.0*yMax/10.0);
	this.assenStelselMark = null;
	repaint();
    }

    public void fitToScreen() {
	assenStelsel.setBounds(knotStart-0.1, 11.0*yMin/10.0, knotEnd+0.1, 11.0*yMax/10.0);
	this.assenStelselMark = null;
	repaint();
    }

    public void recenter(double x, double y) {
	assenStelselChanged(x+assenStelsel.getXMin(), y+assenStelsel.getYMin(), x+assenStelsel.getXMax(), y+assenStelsel.getYMax());
    }

}
