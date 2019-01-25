package GrafischeTechnieken;


import java.util.*;

public class BSplineTree extends Tree {

    double X;
    double Y;

    int p;
    int y;

    Punt [] points;
    GTPolynomial poly;

    // a flag for dynamic programming
    boolean flag;
    boolean dFlag;

    // pointers for going up - and down the tree
    BSplineTree lChild, rChild, rParent, lParent;

    // create an empty tree (useful for manually naming child pointers - dynamic programming)
    public BSplineTree() {
	super();

	this.flag = false;
	this.dFlag = false;
	this.poly = new GTPolynomial();
    }

    // make a full new tree (this is only done once, for the first segment, the others
    // 'inherit' branches from this tree)
    public BSplineTree(int rangeStart, Punt [] points, int k) {
	this();

	this.p = this.y = rangeStart;
	this.poly = new GTPolynomial(1.0);

	this.lChild = new BSplineTree(rangeStart, rangeStart, points, k, 1, this);

	this.rChild = new BSplineTree(rangeStart+1, rangeStart+1, points, k, 0, this);
    }

    public BSplineTree(int p, int y, Punt [] points, int k, int parentParity, BSplineTree parent) {
	this();

	this.p = p;
	this.y = y;

	if(parent!=null)
	    if(parentParity == 0)
		this.lParent = parent;
	    else
		this.rParent = parent;

	if((y-p) == (k-2)) {
	    this.X = points[p-1].getX();
	    this.Y = points[p-1].getY();
	    this.flag = true;
	}
	else {
	    // important step for dynamic programming!!
	    if(lParent!=null && lParent.lChild!=null && lParent.lChild.rChild!=null)
		this.lChild = lParent.lChild.rChild;
	    else
		this.lChild = new BSplineTree(p-1, y, points, k, 1, this);
	    this.lChild.rParent = this;

	    if(rParent!=null && rParent.rChild!=null && rParent.rChild.lChild!=null)
		this.rChild = rParent.rChild.lChild;
	    else
		this.rChild = new BSplineTree(p, y+1, points, k, 0, this);
	    this.rChild.lParent = this;
	}
    }

    public static void constructSegmentTrees(LinkedList ll, int nSegments, int k, Punt [] points) {
	while(ll.size() < nSegments) {
	    if(ll.size() == 0)
		ll.add(new BSplineTree(ll.size()+k-1, points, k));
	    else {
		BSplineTree nextSegmentTree = new BSplineTree();
		nextSegmentTree.p = nextSegmentTree.y = ll.size()+k-1;
		nextSegmentTree.poly = new GTPolynomial(1.0);

		nextSegmentTree.lChild = ((BSplineTree) ll.getLast()).rChild;

		((BSplineTree) ll.getLast()).rChild.rParent = nextSegmentTree;
		// nextSegmentTree.lChild.lParent = ((BSplineTree) ll.getLast()).rChild;
		nextSegmentTree.lChild.rParent = nextSegmentTree;

		nextSegmentTree.rChild = new BSplineTree(ll.size()+k, ll.size()+k, points, k, 0, nextSegmentTree);


		ll.add(nextSegmentTree);
	    }
	}
    }

    public void getLeafs(LinkedList l) {
	if(lChild!=null)
		lChild.getLeafs(l);
	else if (!l.contains(this))
	    l.add(this);

	if(rChild!=null)
	    rChild.getLeafs(l);
	else if (!l.contains(this))
	    l.add(this);
    }

    public void initFlags(boolean flag) {
	this.flag = false;
	this.dFlag = false;
	this.poly = new GTPolynomial();

	if(lChild!=null)
	    lChild.initFlags(flag);
	else {
	    this.flag = flag;
	    this.dFlag = false;
	}
	if(rChild!=null)
	    rChild.initFlags(flag);
	else {
	    this.flag = flag;
	    this.dFlag = false;
	}
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
 
	lP = lChild.calc(u, knots);
	rP = rChild.calc(u, knots);

	double [] pair = new double[2];

	double ty; 
	// exception for top of the tree
	ty = knots[y+1];
	double tp; 
	if(lParent==null && rParent==null)
	    tp = knots[p];
	else
	    tp = knots[p-1];

	// System.out.println(":"+p+", "+y+" = "+ty+","+tp);

	for(int i=0;i<2;i++)
	    pair[i] = lP[i]*(ty-u)/(ty-tp) + rP[i]*(u-tp)/(ty-tp);


	this.X = pair[0];
	this.Y = pair[1];

	// System.out.println(X+","+Y);

	this.flag = true;

	return pair;
    }

    public GTPolynomial calcPolynomial(double [] knots) {
	if(lParent == null && rParent == null)
	    return poly;
	if(dFlag)
	    return poly;

	//	System.out.println("::: "+index[p]+","+index[y]+"|  ");
	// System.out.print(":: "+p+","+y+"|  ");

	GTPolynomial lPoly = new GTPolynomial();
	GTPolynomial rPoly = new GTPolynomial();

	double lty;
	double ltp;
	if(lParent!=null) {
	    lty = knots[y];
	    ltp = knots[p-1];
	} else { lty = 0; ltp = 1; }

	double rty;
	double rtp;
	if(rParent!=null) {
	    rty = knots[y+1];
	    rtp = knots[p];
	} else { rty = 0; rtp = 1; }

	lPoly.add(-ltp/(lty-ltp));
	lPoly.add(1/(lty-ltp));

	rPoly.add(rty/(rty-rtp));
	rPoly.add(-1/(rty-rtp));

	if(lParent!=null)
	    lPoly = lParent.calcPolynomial(knots).multiply(lPoly);
	else
	    lPoly = new GTPolynomial(0);
	
	if(rParent!=null)
	    rPoly = rParent.calcPolynomial(knots).multiply(rPoly);
	else
	    rPoly = new GTPolynomial(0);

	this.poly = lPoly.sum(rPoly);

	// poly.print();

	dFlag = true;

	return poly;
    }

}

