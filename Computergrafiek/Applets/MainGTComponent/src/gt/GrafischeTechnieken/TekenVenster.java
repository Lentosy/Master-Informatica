/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: TekenVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\TekenVenster.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.*;
import java.io.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\TekenVenster.java                                                                  
//----------------------------------------------------------------------------

//## class TekenVenster 
public class TekenVenster extends Canvas implements ComponentListener, AssenStelselListener {
    
    protected AssenStelsel itsAssenStelsel;
    protected LinkedList itsControlePunt;
    protected LinkedList itsDataPunt;

    protected DataPunt activeDataPunt;

    protected Kromme itsKromme;
    protected Kromme [] itsSplines;

    protected PuntenVenster itsPuntenVenster;
    protected GrafischeEngine itsGrafischeEngine;

    public static NevilleMouseEventHandler nevilleMouseListener;
    public static BSplineMouseEventHandler bsplineMouseListener;
    public static BezierMouseEventHandler bezierMouseListener;
    
    public static BufferedImage dataPointImg;
    public static BufferedImage sDataPointImg;
    public static BufferedImage controlPointImg;
    public static BufferedImage sControlPointImg;

    Color fadeBlack = new Color(0,0,0,128);
    Color reddish = new Color(250,160,170,170);
    Color blueish = new Color(180,160,230,170);
    Color greenish = new Color(180,250,180,170);

    Rectangle2D assenStelselMark;

    int typeOfCurve;
    Color curveColor;

    static Stroke thinDash;
    static Stroke dotDash;

    private static final Font miniFont = new Font("Monospaced", Font.BOLD, 10);

    Punt selectedPoint;

    // for double-buffered rendering
    BufferedImage curveBuffer;

    boolean isSpline;
    // Constructors
    
    public  TekenVenster() {
	super(true);
	this.addComponentListener(this);

	try {
	dataPointImg = ImageIO.read(new File("images/point_0.png"));
	sDataPointImg = ImageIO.read(new File("images/point_1.png"));
	controlPointImg = ImageIO.read(new File("images/point_2.png"));
	sControlPointImg = ImageIO.read(new File("images/point_3.png"));
	} catch(IOException e) {}

	float[] dashf = {1.0f,3.0f};
	thinDash = new BasicStroke(1.0f, 0,
				   0,
				   1.0f,
				   dashf,
				   0.0f);
	float [] dash2f = {1.0f,3.0f,2.0f};
	dotDash = new BasicStroke(1.0f, 0,
			      2,
			      1.0f,
			      dash2f,
			      1.0f);
	curveColor = reddish;
        {
            itsControlePunt=new LinkedList();
        }
        {
            itsDataPunt=new LinkedList();
        }
        initRelations();
	selectedPoint = null;
    }
    

    public void drawGrid() {
	super.redrawGrid();
	Point2D.Double p = itsAssenStelsel.cartToScreen(0,0, 
							(double) getWidth(), (double) getHeight());

	int centerx = (int) p.getX();
	int centery = (int) p.getY();

	int step = itsAssenStelsel.getGridStep();

	gridBufG.setColor(fadeBlack);
	gridBufG.setStroke(new BasicStroke());
	gridBufG.drawLine(centerx,10,centerx,mHeight-10);
	gridBufG.drawLine(10,centery,mWidth-10,centery);

	gridBufG.setStroke(thinDash);

	int x = centerx;
	// draw vertical lines
	while(x+step<mWidth-5) {
	    x += step;
	    gridBufG.drawLine(x,0,x,mHeight);
	}
	x = centerx;
	while(x-step>5) {
	    x -= step;
	    gridBufG.drawLine(x,0,x,mHeight);
	}
	// draw horizontal lines
	int y = centery;
	while(y+step<mHeight-5) {
	    y += step;
	    gridBufG.drawLine(0,y,mWidth,y);
	}
	y = centery;
	while(y-step>5) {
	    y -= step;
	    gridBufG.drawLine(0,y,mWidth,y);
	}

	gridBufG.fillOval(centerx-3,centery-3,7,7);
    }

    public void paintComponent(Graphics G) {
	Graphics2D g2 = (Graphics2D) G;
	
	g2.drawImage(gridBuf, 0, 0, mWidth, mHeight, this);
	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);


	if(itsKromme!=null || itsSplines!=null)
	    G.drawImage(curveBuffer, 0, 0, this);
	paintInputs((Graphics2D) G);


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

    public void paintInputs(Graphics2D g2) {
	int id = 0;
	ListIterator iterD = getItsDataPunt();
	while(iterD.hasNext()) {
	    paintDataPunt((DataPunt) iterD.next(),id, g2);
	    id++;
	}
	iterD = getItsControlePunt();
	while(iterD.hasNext()) {
	    paintControlePunt((ControlePunt) iterD.next(),id, g2);
	    id++;
	}
    }

    public void paintDataPunt(DataPunt dp, int id, Graphics2D g2) {

	double x = dp.getX();
	double y = dp.getY();

	// calculate screen coords of point
	Point2D.Double sP = itsAssenStelsel.cartToScreen(x, y, 
							 (double) this.getWidth(),
							 (double) this.getHeight());
	int sx = (int) sP.getX();
	int sy = (int) sP.getY();

	// first order differential
	if(dp.getDiff1() != null) {
	    Point2D.Double diff1P = itsAssenStelsel.cartToScreen(dp.getDiff1().getX()+x, dp.getDiff1().getY()+y, 
								 (double) this.getWidth(),
								 (double) this.getHeight());
	    int diff1x = (int) diff1P.getX();
	    int diff1y = (int) diff1P.getY();

	    g2.setColor(new Color(255,255,255,128));
	    g2.setStroke(new BasicStroke(3.0f));
	    g2.drawLine(sx, sy, diff1x, diff1y);
	    g2.setColor(new Color(70,80,100));
	    g2.setStroke(new BasicStroke(1.5f));
	    g2.drawLine(sx, sy, diff1x, diff1y);
	    g2.setColor(new Color(255,255,255,128));
	    g2.fillOval(diff1x-4, diff1y-4,9,9);
	    g2.setColor(Color.black);
	    g2.fillOval(diff1x-3, diff1y-3,7,7);
	    g2.setColor(Color.white);
	    g2.fillOval(diff1x-1, diff1y-1,3,3);

	    if(dp.getDiff2() != null) {
		Point2D.Double diff2P = itsAssenStelsel.cartToScreen(dp.getDiff2().getX()+x, dp.getDiff2().getY()+y, 
								 (double) this.getWidth(),
								 (double) this.getHeight());
		int diff2x = (int) diff2P.getX();
		int diff2y = (int) diff2P.getY();

		g2.setColor(new Color(255,255,255,128));
		g2.setStroke(new BasicStroke(3.0f));
		g2.drawLine(sx, sy, diff2x, diff2y);
		g2.setColor(new Color(90,90,60));
		g2.setStroke(new BasicStroke());
		g2.drawLine(sx, sy, diff2x, diff2y);
		g2.setColor(new Color(255,255,255,128));
		g2.fillOval(diff2x-4, diff2y-4,9,9);
		g2.setColor(new Color(50,50,20));
		g2.fillOval(diff2x-3, diff2y-3,7,7);
	    }
	}

	g2.setFont(miniFont);
	g2.setColor(new Color(220,220,220,220));
	g2.setStroke(new BasicStroke(0.5f));

	if(id<10) {
	    g2.fillRoundRect(sx+3,sy+1,13,11,3,3);
	    g2.setColor(Color.white);
	    g2.drawRoundRect(sx+3,sy+1,13,11,3,3);
	}
	else {
    	    g2.fillRoundRect(sx+3,sy+1,20,11,3,3);
	    g2.setColor(Color.white);
	    g2.drawRoundRect(sx+3,sy+1,20,11,3,3);
	}

	g2.setColor(Color.black);
	g2.drawString(id+"",sx+6,sy+10);

	if(selectedPoint != (Punt) dp)
	    g2.drawImage(dataPointImg, null, sx-7, sy-7);
	else
	    g2.drawImage(sDataPointImg, null, sx-7, sy-7);
    }

    public void paintControlePunt(ControlePunt cp, int id, Graphics2D g2 ) {
	double x = cp.getX();
	double y = cp.getY();

	// calculate screen coords of point
	Point2D.Double sP = itsAssenStelsel.cartToScreen(x, y, 
							 (double) this.getWidth(),
							 (double) this.getHeight());
	int sx = (int) sP.getX();
	int sy = (int) sP.getY();

	g2.setFont(miniFont);
	g2.setColor(new Color(220,220,220,220));
	g2.setStroke(new BasicStroke(0.5f));

	if(id<10) {
	    g2.fillRoundRect(sx+3,sy+1,13,11,3,3);
	    g2.setColor(Color.white);
	    g2.drawRoundRect(sx+3,sy+1,13,11,3,3);
	}
	else {
    	    g2.fillRoundRect(sx+3,sy+1,20,11,3,3);
	    g2.setColor(Color.white);
	    g2.drawRoundRect(sx+3,sy+1,20,11,3,3);
	}

	g2.setColor(Color.black);
	g2.drawString(id+"",sx+6,sy+10);

	if(selectedPoint != (Punt) cp)
	    g2.drawImage(controlPointImg, null, sx-7, sy-7);
	else
	    g2.drawImage(sControlPointImg, null, sx-7, sy-7);
    }

    public void paintKromme(Graphics2D G) {

	G.setComposite(AlphaComposite.getInstance(AlphaComposite.CLEAR));
	G.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);

	G.setColor(new Color(0,0,0,0));
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

	G.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER));

	for(int i=0;i<xItsKromme.length;i++) {
	    Point2D.Double sP = itsAssenStelsel.cartToScreen(xItsKromme[i],
						    yItsKromme[i],
						    (double) bufW,
						    (double) bufH);
	    sItsKrommeX[i] = (int) sP.getX();

	    sItsKrommeY[i] = (int) sP.getY();
	}

	G.setColor(curveColor);
	G.setStroke(new BasicStroke(5.0f));
	G.drawPolyline(sItsKrommeX, sItsKrommeY, xItsKromme.length);

	G.setColor(new Color(80,50,80));
	G.setStroke(new BasicStroke(1.0f,0,BasicStroke.JOIN_ROUND));
	G.drawPolyline(sItsKrommeX, sItsKrommeY, xItsKromme.length);
    }

    public void paintSplines(Graphics2D G) {

	G.setComposite(AlphaComposite.getInstance(AlphaComposite.CLEAR));
	G.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			    RenderingHints.VALUE_ANTIALIAS_ON);

	G.setColor(new Color(0,0,0,0));
	G.fillRect(0,0,getWidth(), getHeight());

	if(itsSplines == null)
	    return;

	for(int nSegment=0;nSegment<itsSplines.length;nSegment++) {

	    double [] xItsKromme = itsSplines[nSegment].getXCurve();
	    double [] yItsKromme = itsSplines[nSegment].getYCurve();
	    int [] sItsKrommeX = new int[xItsKromme.length];
	    int [] sItsKrommeY = new int[yItsKromme.length];

	    Rectangle rect = G.getClipBounds();
	    int bufW = getWidth();
	    int bufH = getHeight();

	    G.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER));

	    for(int i=0;i<xItsKromme.length;i++) {
		Point2D.Double sP = itsAssenStelsel.cartToScreen(xItsKromme[i],
								 yItsKromme[i],
								 (double) bufW,
								 (double) bufH);
		sItsKrommeX[i] = (int) sP.getX();

		sItsKrommeY[i] = (int) sP.getY();
	    }

	    G.setColor(curveColor);
	    G.setStroke(new BasicStroke(5.0f));
	    G.drawPolyline(sItsKrommeX, sItsKrommeY, xItsKromme.length);

	    G.setColor(new Color(80,50,80));
	    G.setStroke(new BasicStroke(1.0f,0,BasicStroke.JOIN_ROUND));
	    G.drawPolyline(sItsKrommeX, sItsKrommeY, xItsKromme.length);

	    G.setColor(Color.black);
	    G.fillOval(sItsKrommeX[0]-4,sItsKrommeY[0]-4,9,9);
	    G.setColor(Color.white);
	    G.fillOval(sItsKrommeX[0]-1,sItsKrommeY[0]-1,3,3);

	    if(nSegment==itsSplines.length-1) {
		G.setColor(Color.black);
		G.fillOval(sItsKrommeX[sItsKrommeX.length-1]-4,sItsKrommeY[sItsKrommeY.length-1]-4,9,9);
		G.setColor(Color.white);
		G.fillOval(sItsKrommeX[sItsKrommeX.length-1]-1,sItsKrommeY[sItsKrommeY.length-1]-1,3,3);
	    }
	}
    }

    public void setSelectedPoint(Punt p) {
	this.selectedPoint = p;
	repaint();
    }

    public Punt getSelectedPoint() {
	return selectedPoint;
    }

    public void changePunt(Punt p, double newX, double newY) {
	itsGrafischeEngine.verplaatsPunt(p, newX, newY);
	itsGrafischeEngine.berekenCurve();
    }

    public void removeDataPunt(Punt p) {
	if(p!=null) {
	    itsDataPunt.remove(p);
	    itsGrafischeEngine.verwijderDataPunt(p);
	    itsGrafischeEngine.berekenCurve();
	}
    }

    public void removeControlePunt(Punt p) {
	if(p!=null) {
	    itsControlePunt.remove(p);
	    itsGrafischeEngine.verwijderControlePunt(p);
	    itsGrafischeEngine.berekenCurve();
	}
    }
    public void setItsKromme(Kromme p_Kromme) {
	this.itsKromme = p_Kromme;
      
	if(curveBuffer!=null && getWidth()>0 && getHeight()>0) {
	    paintKromme(curveBuffer.createGraphics());
	    repaint();
	}
    }

    public void setItsSplines(Kromme [] p_Kromme) {
	this.itsSplines = p_Kromme;
      
	if(curveBuffer!=null && getWidth()>0 && getHeight()>0) {
	    paintSplines(curveBuffer.createGraphics());
	    repaint();
	}
    }

    public void redrawDetails() {
	
    }

    public void setItsGrafischeEngine(GrafischeEngine ge) {
	this.itsGrafischeEngine = ge;
    }

    public AssenStelsel getItsAssenStelsel() {
        return itsAssenStelsel;
    }
    
    public void __setItsAssenStelsel(AssenStelsel p_AssenStelsel) {
        itsAssenStelsel = p_AssenStelsel;
    }
    
    public void _setItsAssenStelsel(AssenStelsel p_AssenStelsel) {
        if(itsAssenStelsel != null)
            itsAssenStelsel.__setItsTekenVenster(null);
        __setItsAssenStelsel(p_AssenStelsel);
    }
    
    public AssenStelsel newItsAssenStelsel() {
        itsAssenStelsel = new AssenStelsel();
        itsAssenStelsel._setItsTekenVenster(this);
        return itsAssenStelsel;
    }
    
    public void deleteItsAssenStelsel() {
        itsAssenStelsel.__setItsTekenVenster(null);
        itsAssenStelsel=null;
    }
    
    public ListIterator getItsControlePunt() {
        ListIterator iter=itsControlePunt.listIterator(0);
        return iter;
    }
    
    public void _addItsControlePunt(ControlePunt p_ControlePunt) {
        itsControlePunt.add(p_ControlePunt);
    }
    
    public void addItsControlePunt(ControlePunt p_ControlePunt) {
        if(p_ControlePunt != null)
            p_ControlePunt._setItsTekenVenster(this);
        _addItsControlePunt(p_ControlePunt);
    }
    
    public void _removeItsControlePunt(ControlePunt p_ControlePunt) {
        itsControlePunt.remove(p_ControlePunt);
    }
    
    public void removeItsControlePunt(ControlePunt p_ControlePunt) {
        if(p_ControlePunt != null)
            p_ControlePunt.__setItsTekenVenster(null);
        _removeItsControlePunt(p_ControlePunt);
    }
    
    public void _clearItsControlePunt() {
        itsControlePunt.clear();
    }
    
    public void clearItsControlePunt() {
        ListIterator iter=itsControlePunt.listIterator(0);
        while (iter.hasNext()){
            ((ControlePunt)(iter.next()))._clearItsTekenVenster();
            
        }
        _clearItsControlePunt();
    }
    
    public ListIterator getItsDataPunt() {
        ListIterator iter=itsDataPunt.listIterator(0);
        return iter;
    }
    
    public void setItsDataPunt(LinkedList itsDataPunt) {
	this.itsDataPunt = itsDataPunt;
    }

   public void setItsControlePunt(LinkedList itsControlePunt) {
	this.itsControlePunt = itsControlePunt;
    }

    // add a data point in screen coordinates
    public void addScreenDataPunt(Point p) {
	Point2D.Double cartP = itsAssenStelsel.screenToCart(p.getX(), p.getY(), mWidth, mHeight);

	activeDataPunt = new DataPunt(cartP);

	addDataPunt(activeDataPunt);

	repaint();
    }

    public void addScreenControlePunt(Point p) {
	Point2D.Double cartP = itsAssenStelsel.screenToCart(p.getX(), p.getY(), mWidth, mHeight);

	addItsControlePunt(new ControlePunt(cartP));
    }

    public void addDataPunt(DataPunt dp) {
	addItsDataPunt(dp);
    }

    public DataPunt getActiveDataPunt() {
	return activeDataPunt;
    }

    public void setScreenDiff1(Point p, DataPunt dp) {
	Point2D.Double cartP = itsAssenStelsel.screenToCart(p.getX(), p.getY(), mWidth, mHeight);
	Point2D.Double diffP = new Point2D.Double((cartP.getX() - dp.getX()), (cartP.getY() - dp.getY()));
	Punt diff = new Punt(diffP);

	dp.setDiff1(diff);
    }

    public void setScreenDiff1(Punt p, Point new_location) {
	DataPunt dp = (DataPunt) itsDataPunt.get(itsDataPunt.indexOf(p));
	if(dp!=null)
	    setScreenDiff1(new_location, dp);
    }

    public void setScreenDiff2(Point p, DataPunt dp) {
	Point2D.Double cartP = itsAssenStelsel.screenToCart(p.getX(), p.getY(), mWidth, mHeight);
	Point2D.Double diffP = new Point2D.Double((cartP.getX() - dp.getX()), (cartP.getY() - dp.getY()));
	Punt diff = new Punt(diffP);

	if(dp.getDiff1() != null)
	    dp.setDiff2(diff);
    }

    public void setScreenDiff2(Punt p, Point new_location) {
	DataPunt dp = (DataPunt) itsDataPunt.get(itsDataPunt.indexOf(p));
	if(dp!=null)
	    setScreenDiff2(new_location, dp);
    }

    public void _addItsDataPunt(DataPunt p_DataPunt) {
        itsDataPunt.add(p_DataPunt);
    }
    
    public void addItsDataPunt(DataPunt p_DataPunt) {
        if(p_DataPunt != null)
            p_DataPunt._setItsTekenVenster(this);
        _addItsDataPunt(p_DataPunt);
    }
    
    public void _removeItsDataPunt(DataPunt p_DataPunt) {
        itsDataPunt.remove(p_DataPunt);
    }
    
    public void removeItsDataPunt(DataPunt p_DataPunt) {
        if(p_DataPunt != null)
            p_DataPunt.__setItsTekenVenster(null);
        _removeItsDataPunt(p_DataPunt);
    }
    
    public void _clearItsDataPunt() {
        itsDataPunt.clear();
    }
    
    public void clearItsDataPunt() {
        ListIterator iter=itsDataPunt.listIterator(0);
        while (iter.hasNext()){
            ((DataPunt)(iter.next()))._clearItsTekenVenster();
            
        }
        _clearItsDataPunt();
    }
    
    public PuntenVenster getItsPuntenVenster() {
        return itsPuntenVenster;
    }
    
    public void __setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        itsPuntenVenster = p_PuntenVenster;

	nevilleMouseListener.setItsPuntenVenster(itsPuntenVenster);
	bsplineMouseListener.setItsPuntenVenster(itsPuntenVenster);
	bezierMouseListener.setItsPuntenVenster(itsPuntenVenster);
    }
    
    public void _setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        if(itsPuntenVenster != null)
            itsPuntenVenster.__setItsTekenVenster(null);
        __setItsPuntenVenster(p_PuntenVenster);
    }
    
    public void setItsPuntenVenster(PuntenVenster p_PuntenVenster) {
        if(p_PuntenVenster != null)
            p_PuntenVenster._setItsTekenVenster(this);
        _setItsPuntenVenster(p_PuntenVenster);

	drawGrid();
    }
    
    public void _clearItsPuntenVenster() {
        itsPuntenVenster = null;
    }
    
    protected void initRelations() {
        itsAssenStelsel = newItsAssenStelsel();

	nevilleMouseListener = new NevilleMouseEventHandler();
	bsplineMouseListener = new BSplineMouseEventHandler();
	bezierMouseListener = new BezierMouseEventHandler();
    }
    
    public void changeTypeOfCurve(int oldType, int newType) {
	switch(oldType) {
	case 0:
	    this.removeMouseListener(nevilleMouseListener);
	    this.removeMouseMotionListener(nevilleMouseListener);
	    break;
	case 1:
	    this.removeMouseListener(bsplineMouseListener);
	    this.removeMouseMotionListener(bsplineMouseListener);
	    break;
	case 2:
	    this.removeMouseListener(bezierMouseListener);
	    this.removeMouseMotionListener(bezierMouseListener);
	    break;
	}

	switch(newType) {
	case 0:
	    this.addMouseListener(nevilleMouseListener);
	    this.addMouseMotionListener(nevilleMouseListener);
	    isSpline = false;
	    curveColor = reddish;
	    break;
	case 1:
	    this.addMouseListener(bsplineMouseListener);
	    this.addMouseMotionListener(bsplineMouseListener);
	    isSpline = true;
	    curveColor = blueish;
	    break;
	case 2:
	    this.addMouseListener(bezierMouseListener);
	    this.addMouseMotionListener(bezierMouseListener);
	    isSpline = true;
	    curveColor = greenish;
	    break;
	}

	typeOfCurve = newType;
    }

    public int getType() {
	return typeOfCurve;
    }


    public void componentHidden(ComponentEvent e) {

    }

    public void componentMoved(ComponentEvent e) {

    }

    public void componentResized(ComponentEvent e) {
	mWidth = getWidth();
	mHeight = getHeight();
	drawGrid();
	curveBuffer = new BufferedImage(getWidth(),getHeight(),BufferedImage.TYPE_INT_ARGB);

	if(itsKromme!=null)
	    paintKromme(curveBuffer.createGraphics());
	if(itsSplines!=null)
	    paintSplines(curveBuffer.createGraphics());
    }

    public void componentShown(ComponentEvent e) {

    }

    public void assenStelselChanged(double xMin, double yMin, double xMax, double yMax) {
	if(xMin!=xMax && yMax!=yMin)
	    itsAssenStelsel.setBounds(xMin, yMin, xMax, yMax);
	this.assenStelselMark = null;
	if(itsKromme!=null)
	    paintKromme(curveBuffer.createGraphics());
	if(itsSplines!=null)
	    paintSplines(curveBuffer.createGraphics());

	drawGrid();
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
	this.assenStelselMark = null;
	repaint();
    }

    public void fitToScreen() {
	if(!isSpline)
	    fitKrommeToScreen();
	else
	    fitSplinesToScreen();
    }

    public void recenter(double x, double y) {
	assenStelselChanged(x+itsAssenStelsel.getXMin(), y+itsAssenStelsel.getYMin(), x+itsAssenStelsel.getXMax(), y+itsAssenStelsel.getYMax());
    }

    private void fitKrommeToScreen() {
	double xMin = -100, yMin = -100, yMax = 100, xMax = 100;

	if(itsKromme!=null) {
	    double [] xCurve = itsKromme.getXCurve();
	    double [] yCurve = itsKromme.getYCurve();

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
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\TekenVenster.java
*********************************************************************/

