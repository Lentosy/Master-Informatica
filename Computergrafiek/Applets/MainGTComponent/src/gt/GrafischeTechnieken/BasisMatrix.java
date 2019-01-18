/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: BasisMatrix
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\BasisMatrix.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\BasisMatrix.java                                                                  
//----------------------------------------------------------------------------

//## class BasisMatrix 
public class BasisMatrix {
    
    protected GrafischeEngine itsGrafischeEngine;

    // the polynomes that fit in the columns
    protected Vector cols;
    
    // Constructors
    
    public BasisMatrix() {
	cols = new Vector();
    }
    
    public void init() {
	cols = new Vector();
    }

    public int getSize() {
	return cols.size();
    }

    public double eval(int i, double t) {
	return ((GTPolynomial) cols.elementAt(i)).eval(t);
    }

    public void addCol(GTPolynomial v) {
	cols.setSize(cols.size()+1);
	cols.setElementAt(v, cols.size() - 1);
    }

    public double getElementAt(int i, int j) {
	long val = Math.round(1000.0 * ((Double) ((GTPolynomial) cols.elementAt(i)).elementAt(cols.size()-j-1)).doubleValue());
	return val/1000.0;
    }

    public String printHTML() {
	String HTML = "<html><table>";

	for(int i=0; i< cols.size(); i++) {
	    GTPolynomial poly = (GTPolynomial) cols.elementAt(i);
	    HTML += "<TR>";
	    for(int j=0; j < poly.size(); j++) {
		HTML += "<TD";
		double val_ij = ((Double) poly.elementAt(j)).doubleValue();
		HTML += val_ij;
		HTML += "</TD>";
	    }
	    HTML += "</TR>";
	}
	HTML+="</table></html>";

	return HTML;
    }

    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    
    public void __setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        itsGrafischeEngine = p_GrafischeEngine;
    }
    
    public void _setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(itsGrafischeEngine != null)
            itsGrafischeEngine.__setItsBasisMatrix(null);
        __setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(p_GrafischeEngine != null)
            p_GrafischeEngine._setItsBasisMatrix(this);
        _setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void _clearItsGrafischeEngine() {
        itsGrafischeEngine = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\BasisMatrix.java
*********************************************************************/

