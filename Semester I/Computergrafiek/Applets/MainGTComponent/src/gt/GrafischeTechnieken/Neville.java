/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: Neville
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Neville.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.image.*;
import java.awt.geom.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\Neville.java                                                                  
//----------------------------------------------------------------------------

//## class Neville 
public class Neville extends GrafischeEngine {
    
    NevilleTree itsRenderTree;
    private Kromme curve;


    // Constructors
    
    public  Neville(GebruikersInterface gui) {
	super(gui);
    }

    public void berekenCurve() {

	// real knots + virtual knots
	double [] knots = new double[itsKnoop.size()];
	double density = 0;

	if(itsDataPunt.size()>=2) {

	    knots = getKnotsAsDoubles();
	    int [] index = getRootLabel();

	    DataPunt [] points = new DataPunt[itsDataPunt.size()];
	    Object [] pobj = itsDataPunt.toArray();

	    for(int i=0; i<pobj.length; i++) {
		points[i] = (DataPunt) pobj[i];
	    }

	    itsRenderTree = new NevilleTree(index, 0, index.length - 1, points, 0, null);

	    density = (double) index.length*25.0;
	    itsRenderTree.initFlags(true);
	    calcBasisMatrix(knots);
	    // calcCurveUp(density, knots);
	    calcCurveDown(density, knots);
	}
	    outputBasisMatrix();
	    outputPolynomes(knots);

	    outputToTekenVenster();
	    outputCurve();
    }

    private double [] getKnotsAsDoubles() {
	
	ListIterator knoopIter = itsKnoop.listIterator(0);

	double [] knots = new double[itsKnoop.size()];

	for(int i=0;i<knots.length;i++) {
	    Knoop knoop = (Knoop) knoopIter.next();
	    knots[i] = knoop.getValue()/((double) knots.length-1);
	}

	return knots;
    }

    private int [] getRootLabel() {
	
	ListIterator iterD = getItsDataPunt();
	int indexlength = 0;

	while(iterD.hasNext()) {
	    DataPunt dp = (DataPunt) iterD.next();
	    if(dp.getDiff2() != null)
		indexlength += 2;
	    else if(dp.getDiff1() != null)
		indexlength ++;
	    indexlength ++;
	}

	int [] index = new int[indexlength];

	iterD = getItsDataPunt();

	int i=0, j=0;

	while(iterD.hasNext()) {
	    DataPunt dp = (DataPunt) iterD.next();
	    
	    if(dp.getDiff2() != null) {
		index[i++] = j;
		index[i++] = j;
	    }
	    else if(dp.getDiff1() != null)
		index[i++] = j;

	    index[i++] = j;

	    j++;
	}
	return index;
    }

    public void calcBasisMatrix(double [] knots) {
	itsRenderTree.setPolynomial(new GTPolynomial(1.0));
	LinkedList leafList = new LinkedList();
	itsBasisMatrix = new BasisMatrix();

	itsRenderTree.getLeafs(leafList);

	for(int i=0;i<leafList.size();i++) {
	    NevilleTree nTree = (NevilleTree) leafList.get(i);
	    itsBasisMatrix.addCol(((NevilleTree) leafList.get(i)).calcPolynomial(knots));
	}
    }

    // use upwards recursion to calc the curve
    public void calcCurveUp(double density, double [] knots) {
	
	double [] xCurve;
	double [] yCurve;

	xCurve = new double[(int) density + 1];
	yCurve = new double[(int) density + 1];

	int len = knots.length;

	int i = 0;
	for(double id=0; i < (int) density; id+=(knots[len-1]/density), i++) {
	    itsRenderTree.initFlags(true);
	    double [] cPoint = itsRenderTree.calc(id, knots);

	    xCurve[i] = cPoint[0];
	    yCurve[i] = cPoint[1];
	}

	DataPunt lP = (DataPunt) itsDataPunt.getLast();
	xCurve[i] = lP.getX();
	yCurve[i] = lP.getY();

	curve = new Kromme(xCurve, yCurve);
    }

    public void calcCurveDown(double density, double [] knots) {
	int i = 0, curPoint = 0;

	double [] xCurve;
	double [] yCurve;

	xCurve = new double[(int) density + 1];
	yCurve = new double[(int) density + 1];

	LinkedList allPoints = new LinkedList();

	ListIterator iterD = getItsDataPunt();
	int graad = itsDataPunt.size();
	// #!! zie verslag : opmerking extra scalair bij afgeleides !!
	while(iterD.hasNext()) {
	    DataPunt dp = (DataPunt) iterD.next();
	    if(dp.getDiff2() != null)
		allPoints.add(dp.getDiff2().scalar((double) graad*graad));
	    if(dp.getDiff1() != null)
		allPoints.add(dp.getDiff1().scalar((double) graad));
	    allPoints.add(dp);
	}

	for(double id=0; i < (int) density; id+=(knots[knots.length-1]/density), i++) {
	    curPoint = 0;
	    iterD = allPoints.listIterator(0);
	    xCurve[i] = 0;
	    yCurve[i] = 0;

	    while(iterD.hasNext()) {
		double factor = itsBasisMatrix.eval(curPoint, id);
		Punt dp = (Punt) iterD.next();
		xCurve[i] += factor*dp.getX();
		yCurve[i] += factor*dp.getY();
		curPoint++;
	    }
	}

	Punt lP = (Punt) itsDataPunt.getLast();
	xCurve[i] = lP.getX();
	yCurve[i] = lP.getY();

	curve = new Kromme(xCurve, yCurve);
    }

    public void outputPolynomes(double [] knots) {
	if(itsBasisMatrix!=null)
	    itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().setInputData(itsBasisMatrix,knots);
    }

    public void outputToTekenVenster() {
	itsGebruikersInterface.getItsMenuVenster().getItsTekenVenster().setItsKromme(curve);
    }

    public void outputCurve() {
	itsGebruikersInterface.getItsOutputVenster().setItsKromme(curve);
    }

    public void configureerEngine() {
	
    }

    public void flushInputs() {
	itsGebruikersInterface.getItsOutputVenster().setItsKromme(curve);

	TekenVenster tekenVenster = itsGebruikersInterface.getItsMenuVenster().getItsTekenVenster();
	KnopenManipulatieVenster knopenVenster = itsGebruikersInterface.getItsMenuVenster().getItsKnopenManipulatieVenster();
	OutputVenster outputVenster = itsGebruikersInterface.getItsOutputVenster();
	GraadManipulatieVenster graadVenster = itsGebruikersInterface.getItsMenuVenster().getItsGraadManipulatieVenster();

	itsGebruikersInterface.getItsMenuVenster().setBigTitle("Lagrange");

	tekenVenster.setItsDataPunt(itsDataPunt);
	tekenVenster.setItsControlePunt(itsControlePunt);
	tekenVenster.setItsKromme(curve);
	knopenVenster.setItsKnoop(this.itsKnoop);
	outputVenster.setItsKromme(curve);
	graadVenster.setItsGraad(new Graad());
	itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().setBigTitle("Lagrange");
    }


    //## operation verwijderDataPunt() 
    public void verwijderDataPunt(Punt p) {
        //#[ operation verwijderDataPunt()
	itsDataPunt.remove(p);
	maakUniform();
        //#]
    }

    public void verwijderCurve() {
	super.verwijderCurve();
	curve = null;

	flushInputs();
    }

    // wordt overridden door de verschillende implementaties (neville/bspline/..)
    public void voegtoeKnoop(double knoop_value) {
	berekenCurve();
	double [] knots = getKnotsAsDoubles();

	for(int l=0;l<itsKnoop.size();l++)
	    if(((Knoop) itsKnoop.get(l)).getValue() == knoop_value)
		return;

	int i=0;
	for(i=0;i<itsKnoop.size()-1;i++) {
	    Knoop thisK = (Knoop) itsKnoop.get(i);
	    Knoop nextK = (Knoop) itsKnoop.get(i+1);

	    if(thisK.getValue()<knoop_value && knoop_value<nextK.getValue())
		break;
	}
	if(knoop_value < ((Knoop) itsKnoop.getFirst()).getValue())
	    i = -1;

	itsKnoop.add(i+1, new Knoop(knoop_value));

	itsRenderTree.initFlags(true);
	double [] cPoint = itsRenderTree.calc(knoop_value/(double) itsKnoop.size(), knots);
	itsDataPunt.add(i+1, new DataPunt(cPoint[0], cPoint[1])); 

	itsGebruikersInterface.getItsMenuVenster().getItsKnopenManipulatieVenster().repaint();
   }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Neville.java
*********************************************************************/

