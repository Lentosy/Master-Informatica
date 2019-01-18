package GrafischeTechnieken;


import java.util.*;

public class NevilleTree extends Tree {

    double X;
    double Y;

    int [] index;
    int p;
    int y;
    DataPunt [] points;
    GTPolynomial poly;

    // depth of this node
    int depth;

    // a flag for dynamic programming
    boolean flag;
    boolean dFlag;

    boolean diff;

    NevilleTree lChild;
    NevilleTree rChild;
    NevilleTree lParent;
    NevilleTree rParent;
    NevilleTree dParent;

    public NevilleTree() {
	super();
    }

    public NevilleTree(int [] index, int p, int y, DataPunt [] points, int parentParity, NevilleTree parent) {
	this.flag = false;
	this.diff = false;
	this.index = index;
	this.p = p;
	this.y = y;
	this.points = points;
	this.poly = new GTPolynomial();

	if(parent!=null)
	    if(parentParity == 0)
		this.lParent = parent;
	    else
		this.rParent = parent;

	// check for dynamic relations
	if(lParent !=null && lParent.lChild != null && lParent.lChild.rChild != null) {
	    this.lChild = lParent.lChild.rChild;
	}
	if(rParent !=null && rParent.rChild != null && rParent.rChild.lChild != null) {
	    this.rChild = rParent.rChild.lChild;
	}

	// special case for differential points
	if(index[y] == index[p]) {
	    if((y-p) == 2) {
		this.lChild = new NevilleTree(index, p, points[index[p]].getDiff2());
		this.lChild.rParent = this;
		this.lChild.diff = true;

		if(lParent!=null &&  lParent.lChild != null && lParent.lChild.rChild!=null) {
		    this.rChild = lParent.lChild.rChild;
		    this.rChild.dParent = this;
		}
		else { 
		    if(points[index[p]].getDiff1() != null) {
			this.rChild = new NevilleTree(index, p+1, y, points, 0, null);
		    }
		    else {
			this.rChild = new NevilleTree(index, p+2, y, points, 0, this);
		    }
		}
		this.rChild.dParent = this;
	    }
	    else if((y-p) == 1) {
		this.lChild = new NevilleTree(index, p, points[index[p]].getDiff1());
		this.lChild.rParent = this;
		this.lChild.diff = true;

		if(lParent!=null &&  lParent.lChild != null && lParent.lChild.rChild!=null) {
		    this.rChild = lParent.lChild.rChild;
		    this.rChild.dParent = this;
		}
		else { 
		    this.rChild = new NevilleTree(index, p+1, y, points, 0, null);
		    this.rChild.dParent = this;
		}
	    }
	    if ((y-p) == 0) {
		this.flag = true;
		this.X = points[index[p]].getX();
		this.Y = points[index[p]].getY();
	    }
	}
	else {
	    if(lChild == null)
		this.lChild = new NevilleTree(index, p, y-1, points, 1, this);

	    this.lChild.rParent = this;

	    if(rChild == null)
		this.rChild = new NevilleTree(index, p+1, y, points, 0, this);

	    this.rChild.lParent = this;
	}
    }

    public NevilleTree(int [] index, int y, Punt p) {
	this.X = p.getX();
	this.Y = p.getY();

	this.y = this.p = y;
	this.index = index;

	this.poly = new GTPolynomial();
	this.flag = true;
    }

    /**
     * Init flags for dynamic programming
     */
    public void initFlags(boolean flag) {
	this.flag = false;
	this.dFlag = false;

	if(lChild!=null)
	    lChild.initFlags(flag);
	if(rChild!=null)
	    rChild.initFlags(flag);

	if(y==p) {
	    this.flag = flag;
	    this.dFlag = false;
	}
    }

    public GTPolynomial getPolynomial() {
	return poly;
    }

    public void setPolynomial(GTPolynomial poly) {
	this.poly = poly;
	this.flag = true;
    }

    public void getLeafs(LinkedList l) {
	if(lChild!=null)
		lChild.getLeafs(l);
	else if (!l.contains(this)) {
	    l.add(this);
	}

	if(rChild!=null) {
	    if(rChild.dParent==this || rChild.dParent==null)
		rChild.getLeafs(l);
	}
	else if (!l.contains(this)) {
	    l.add(this);
	}
    }

    public GTPolynomial calcPolynomial(double [] knots) {
	if(lParent == null && rParent == null)
	    return poly;
	if(dFlag)
	    return poly;

	//	System.out.println("::: "+index[p]+","+index[y]+"|  ");

	GTPolynomial lPoly = new GTPolynomial();
	GTPolynomial rPoly = new GTPolynomial();

	double lty;
	double ltp;
	if(lParent!=null) {
	    lty = knots[index[lParent.y]];
	    ltp = knots[index[lParent.p]];
	} else { lty = 0; ltp = 1; }

	double rty;
	double rtp;
	if(rParent!=null) {
	    rty = knots[index[rParent.y]];
	    rtp = knots[index[rParent.p]];
	} else { rty = 0; rtp = 1; }

	lPoly.add(-ltp/(lty-ltp));
	lPoly.add(1/(lty-ltp));

	if(diff) {
	    // first degree
	    if((rParent.y - rParent.p) == 1) {
		rPoly.add(-rty);
		rPoly.add(1.0);
	    }
	    // second degree
	    else if((rParent.y - rParent.p) == 2) {
		rPoly.add(rty*rty/2.0);
		rPoly.add(-rty);
		rPoly.add(0.5);
	    }
	}
	else {
	    rPoly.add(rty/(rty-rtp));
	    rPoly.add(-1/(rty-rtp));
	}

	if(lParent!=null)
	    lPoly = lParent.calcPolynomial(knots).multiply(lPoly);
	else
	    lPoly = new GTPolynomial(0);
	
	if(rParent!=null)
	    rPoly = rParent.calcPolynomial(knots).multiply(rPoly);
	else
	    rPoly = new GTPolynomial(0);

	// System.out.print(":: "+index[p]+","+index[y]+"|  ");lPoly.sum(rPoly).print();

	if(dParent!=null)
	    lPoly = lPoly.sum(dParent.calcPolynomial(knots));

	this.poly = lPoly.sum(rPoly);
	dFlag = true;

	return poly;
    }

    public double[] calc(double u, double [] knots) {

	// dynamic programming
	if(flag) {
	    double [] pair = new double[2];
	    pair[0]= this.X; pair[1] = this.Y;
	    return pair;
	}


	double [] lP;
	double [] rP;

	String indexString = "";

	for(int i=p;i<=y;i++)
	    indexString = indexString + index[i];
 
	lP = lChild.calc(u, knots);
	rP = rChild.calc(u, knots);

	double [] pair = new double[2];

	double ty = knots[index[y]];
	double tp = knots[index[p]];

	if(index[y]!=index[p]) {
	    for(int i=0;i<2;i++)
		pair[i] = lP[i]*(ty-u)/(ty-tp) + rP[i]*(u-tp)/(ty-tp);
	}
	else {
	    for(int i=0;i<2;i++)
		pair[i] = rP[i] + Math.pow(points.length, y-p)*lP[i]*Math.pow((u-tp),(double) (y-p))/(double)(y-p);
	}

	this.X = pair[0];
	this.Y = pair[1];

	//	System.out.println(u +": " + indexString + " | "+this.X);
	flag = true;

	return pair;
    }
}

