/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: BSpline
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\BSpline.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\BSpline.java                                                                  
//----------------------------------------------------------------------------

//## class BSpline 
public class BSpline extends GrafischeEngine {

    BasisMatrix [] itsBasisMatrices;
    BSplineTree itsRenderTree;
    LinkedList listOfTrees;
    Kromme [] segments;
    Kromme curve;

    // Constructors
    
    public  BSpline(GebruikersInterface gui) {
	super(gui);
	itsGraad = new Graad();
	isOpen = false;
    }
    

    public void berekenCurve() {
	int k = itsGraad.getValue()+1;

	// real knots + virtual knots
	double [] knots = new double[itsKnoop.size()+k];
	double density = 0;

	if(itsControlePunt.size()>=k-1) {

	    density = 50;
	    listOfTrees = new LinkedList();

	    int nSegments = itsControlePunt.size()-k+1;
	    knots = getKnotsAsDoubles();

	    Punt [] points = new Punt[itsControlePunt.size()];
	    Object [] pobj = itsControlePunt.toArray();

	    for(int i=0; i<pobj.length; i++) {
		points[i] = (Punt) pobj[i];
	    }

	    segments = new Kromme[nSegments];

	    BSplineTree.constructSegmentTrees(listOfTrees, nSegments, k, points);

	    calcCurveUp(density, knots);
	    //calcCurveDown(density, knots);
	    calcBasisMatrix(knots);
	}
	outputBasisMatrix();
	outputPolynomes(knots);
	outputToTekenVenster();
	outputCurve();
    }

    public void flushInputs() {
	itsGebruikersInterface.getItsOutputVenster().setItsKromme(curve);

	TekenVenster tekenVenster = itsGebruikersInterface.getItsMenuVenster().getItsTekenVenster();
	KnopenManipulatieVenster knopenVenster = itsGebruikersInterface.getItsMenuVenster().getItsKnopenManipulatieVenster();
	OutputVenster outputVenster = itsGebruikersInterface.getItsOutputVenster();
	GraadManipulatieVenster graadVenster = itsGebruikersInterface.getItsMenuVenster().getItsGraadManipulatieVenster();
	itsGebruikersInterface.getItsMenuVenster().setBigTitle("B-Spline  (k="+(itsGraad.getValue()+1)+")");

	tekenVenster.setItsDataPunt(itsDataPunt);
	tekenVenster.setItsControlePunt(itsControlePunt);
	tekenVenster.setItsSplines(segments);
	knopenVenster.setItsKnoop(this.itsKnoop);
	outputVenster.setItsSplines(segments);
	graadVenster.setItsGraad(this.itsGraad);
	itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().setBigTitle("B-spline");
    }

    public void outputBasisMatrix() {
	    itsGebruikersInterface.getItsOutputVenster().getItsBasisMatrixVenster().setMatrices(itsBasisMatrices);
    }

   private double [] getKnotsAsDoubles() {
       int k = itsGraad.getValue()+1;

       ListIterator knoopIter = itsKnoop.listIterator(0);

       double [] knots = new double[itsControlePunt.size()+k];

       for(int i=k-2;i<itsControlePunt.size()+k-2;i++) {
	   Knoop knoop = (Knoop) knoopIter.next();
	   knots[i] = knoop.getValue();
       }


	for(int i=0;i<=k-2;i++) {
	    if(isOpen)
		knots[i] = knots[k-1];
	    else
		knots[i] = (double) (i-k+2);
	}

	for(int i=knots.length-k+1;i<knots.length;i++) {
	    if(isOpen)
		knots[i] = knots[knots.length-k];
	    else
		knots[i] = knots[i-1]+1;
	}

	return knots;
    }

    public void calcCurveUp(double density, double [] knots) {
	
	ListIterator iterCurves = listOfTrees.listIterator(0);
	segments = new Kromme[listOfTrees.size()];
	int nSegment = 0;
	int k = itsGraad.getValue()+1;
	while(iterCurves.hasNext()) {

	    BSplineTree segmentRenderTree = (BSplineTree) iterCurves.next();

	    double [] xCurve;
	    double [] yCurve;

	    xCurve = new double[(int) density + 1];
	    yCurve = new double[(int) density + 1];

	    int len = knots.length;

	    int i = 0;

	    for(double id=knots[nSegment+k-1]; i <= (int) density; 
		id+=((knots[nSegment+k]-knots[nSegment+k-1])/density), 
		    i++) {

		segmentRenderTree.initFlags(true);
		double [] cPoint = segmentRenderTree.calc(id, knots);

		xCurve[i] = cPoint[0];
		yCurve[i] = cPoint[1];
	    }

	    segments[nSegment] = new Kromme(xCurve, yCurve);
	    nSegment++;
	}
    }

    public void calcBasisMatrix(double [] knots) {
	int k = itsGraad.getValue()+1;
	LinkedList leafList = new LinkedList();
	itsBasisMatrices = new BasisMatrix[listOfTrees.size()];

	ListIterator iterCurves = listOfTrees.listIterator(0);

	while(iterCurves.hasNext()) {
	    BSplineTree itsRenderTree = (BSplineTree) iterCurves.next();
	    //	    	itsRenderTree.setPolynomial(new GTPolynomial(1.0));
	    itsRenderTree.getLeafs(leafList);
	}

	for(int nSegment = 0; nSegment<listOfTrees.size(); nSegment++) {
	    itsBasisMatrices[nSegment] = new BasisMatrix();

	    // init root polynomials
	    iterCurves = listOfTrees.listIterator(0);
	    while(iterCurves.hasNext())
		((BSplineTree) iterCurves.next()).initFlags(true);

	    ((BSplineTree) listOfTrees.get(nSegment)).poly = new GTPolynomial(1.0);


	    for(int i=nSegment;i<nSegment+k;i++) {
		GTPolynomial poly = ((BSplineTree) leafList.get(i)).calcPolynomial(knots);
		itsBasisMatrices[nSegment].addCol(poly);
	    }
	}
    }

    public void verwijderCurve() {
	super.verwijderCurve();
	segments = null;
	itsBasisMatrices=null;

	flushInputs();
    }

    public void outputToTekenVenster() {
	itsGebruikersInterface.getItsMenuVenster().getItsTekenVenster().setItsSplines(segments);
	itsGebruikersInterface.getItsMenuVenster().setBigTitle("B-Spline  (k="+(itsGraad.getValue()+1)+")");
    }

    public void outputCurve() {
	itsGebruikersInterface.getItsOutputVenster().setItsSplines(segments);
    }

    public void outputPolynomes(double [] knots) {
	int k = itsGraad.getValue()+1;
	if(itsBasisMatrices!=null)
	    itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().setInputData(itsBasisMatrices,knots,k);
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\BSpline.java
*********************************************************************/

