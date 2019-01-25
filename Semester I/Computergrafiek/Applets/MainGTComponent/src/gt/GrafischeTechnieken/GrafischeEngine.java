/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: GrafischeEngine
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GrafischeEngine.java
*********************************************************************/

package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\GrafischeEngine.java                                                                  
//----------------------------------------------------------------------------

//## class GrafischeEngine 
public class GrafischeEngine {
    
    protected BasisMatrix itsBasisMatrix;
    protected LinkedList itsControlePunt;
    protected LinkedList itsDataPunt;
    protected GebruikersInterface itsGebruikersInterface;
    protected Graad itsGraad;
    protected LinkedList itsKnoop;
    protected LinkedList itsTree;

    boolean isOpen;
    // Constructors
    
    public  GrafischeEngine(GebruikersInterface itsGebruikersInterface) {
        {
            itsControlePunt=new LinkedList();
        }
        {
            itsDataPunt=new LinkedList();
        }
        {
            this.itsGebruikersInterface=itsGebruikersInterface;
        }
        {
            itsKnoop=new LinkedList();
        }
        {
            itsTree=new LinkedList();
        }
    }

    public void renderBuffers() {

    }

    public void renderToTekenVenster(Graphics2D g2) {
	
    }

    public void renderToOutputVenster(Graphics2D g2) {

    }

    //## operation berekenCurve() 
    public void berekenCurve() {
        //#[ operation berekenCurve() 
        //#]
    }
    
    //## operation configureerEngine() 
    public void configureerEngine() {
        //#[ operation configureerEngine() 
        //#]
    }
    
    //## operation gebruikGraad() 
    public void gebruikGraad() {
        //#[ operation gebruikGraad() 
        //#]
    }
    
    //## operation maakLeeg() 
    public void maakLeeg() {
        //#[ operation maakLeeg() 
        //#]
    }
    
    //## operation veranderAfgeleide(DataPunt) 
    public void veranderAfgeleide(DataPunt p) {
        //#[ operation veranderAfgeleide(DataPunt) 
        //#]
    }
    
    //## operation verplaatsControlePunt() 
    public void verplaatsControlePunt(int index, ControlePunt cp) {
        //#[ operation verplaatsControlePunt() 
	if(index>=0 && index<itsControlePunt.size())
	    itsControlePunt.set(index, cp);
        //#]
    }
    
    //## operation verplaatsDataPunt() 
    public void verplaatsDataPunt(int index, DataPunt dp) {
        //#[ operation verplaatsDataPunt() 
	if(index>=0 && index<itsDataPunt.size()) {
	    itsDataPunt.set(index, dp);
	}
        //#]
    }
    
    //## operation verplaatsPunt() 
    public void verplaatsPunt(Punt p, double newX, double newY) {
        //#[ operation verplaatsDataPunt() 
	p.setX(newX);
	p.setY(newY);
        //#]
    }

    //## operation verplaatsKnoop() 
    public void verplaatsKnoop() {
        //#[ operation verplaatsKnoop() 
        //#]
    }

    // wordt overridden door de verschillende implementaties (neville/bspline/..)
    public void voegtoeKnoop(double knoop_value) {

    }
    
    //## operation verwijderAfgeleide(DataPunt) 
    public void verwijderAfgeleide(DataPunt p) {
        //#[ operation verwijderAfgeleide(DataPunt) 
	p.setDiff1(null);
        //#]
    }

    public void verwijderAfgeleide(int index) {
	if(index>=0 && index < itsDataPunt.size())
	    ((DataPunt) itsDataPunt.get(index)).setDiff1(null);
    }

    public void verwijderTweedeAfgeleide(int index) {
	if(index>=0 && index < itsDataPunt.size())
	    ((DataPunt) itsDataPunt.get(index)).setDiff2(null);
    }

    public void verwijderTweedeAfgeleide(DataPunt p) {
	p.setDiff2(null);
    }

    
    public void verplaatsAfgeleide(int index, Punt nieuwe_afgeleide) {
        //#[ operation veranderAfgeleide(DataPunt) 
	if(index>=0 && index<itsDataPunt.size())
	    ((DataPunt) itsDataPunt.get(index)).setDiff1(nieuwe_afgeleide);
        //#]
    }
    
    public void verplaatsTweedeAfgeleide(int index, Punt nieuwe_afgeleide) {
        //#[ operation veranderAfgeleide(DataPunt) 
	if(index>=0 && index<itsDataPunt.size())
	    ((DataPunt) itsDataPunt.get(index)).setDiff2(nieuwe_afgeleide);
        //#]
    }

    //## operation verwijderControlePunt() 
    public void verwijderControlePunt(int index) {
        //#[ operation verwijderControlePunt() 
	if(index>=0 && index < itsControlePunt.size())
	    itsControlePunt.remove(index);
    }

    //## operation verwijderDataPunt() 
    public void verwijderDataPunt(int index) {
        //#[ operation verwijderControlePunt() 
	if(index>=0 && index < itsDataPunt.size())
	    itsDataPunt.remove(index);
    }

    //## operation verwijderDataPunt() 
    public void verwijderControlePunt(Punt p) {
        //#[ operation verwijderDataPunt()
	itsControlePunt.remove(p);
	maakUniform();
        //#]
    }

    //## operation verwijderDataPunt() 
    public void verwijderDataPunt(Punt p) {
        //#[ operation verwijderDataPunt()
	itsDataPunt.remove(p);
	maakUniform();
        //#]
    }
    
    //## operation voegtoeAfgeleide(DataPunt) 
    public void voegtoeAfgeleide(DataPunt p, Punt afgeleide) {
        //#[ operation voegtoeAfgeleide(DataPunt) 
	p.setDiff1(afgeleide);
        //#]
    }
    
    //## operation voegtoeControlePunt() 
    public void voegtoeControlePunt(ControlePunt cp) {
        //#[ operation voegtoeControlePunt() 
	addItsControlePunt(cp);
        //#]
    }
    
    //## operation voegtoeDataPunt() 
    public void voegtoeDataPunt(DataPunt dp) {
	addItsDataPunt(dp);
        //#]
    }
    
    public void voegtoeKnoopWaarde(double knoopVal) {
        //#[ operation voegtoeKnoop() 
	Knoop k;

	itsKnoop.add(k = new Knoop(knoopVal));
    }

    public void maakUniform() {
	int n = itsDataPunt.size() + itsControlePunt.size();

	itsKnoop.clear();

	for(int i=0;i<n;i++) {
	    voegtoeKnoopWaarde((double) i);
	}

	itsGebruikersInterface.getItsMenuVenster().getItsKnopenManipulatieVenster().repaint();

	isOpen = false;
    }

    public void maakOpenUniform() {
	maakUniform();

	isOpen = true;
    }

    public void wijzigGraad(int graad) {
	if(itsGraad!=null && graad>0)
	    itsGraad.setValue(graad);
    }

    public void verwijderCurve() {
	itsControlePunt.clear();
	itsDataPunt.clear();
	itsKnoop.clear();
	itsBasisMatrix= null;
    }

    // adjust all inputs to this grafische engine
    public void flushInputs() {
	
    }    

    public void saveToFile(RandomAccessFile out) 
    throws IOException {
	ListIterator iterD = itsDataPunt.listIterator(0);
	ListIterator iterC = itsControlePunt.listIterator(0);
	ListIterator iterK = itsKnoop.listIterator(0);

	out.writeInt(itsDataPunt.size());
	while(iterD.hasNext()) {
	    DataPunt dp = (DataPunt) iterD.next();
	    if(dp.getDiff2()!=null)
		out.writeInt(2);
	    else if(dp.getDiff1()!=null)
		out.writeInt(1);
	    else
		out.writeInt(0);

	    out.writeDouble(dp.getX());
	    out.writeDouble(dp.getY());

	    if(dp.getDiff1()!=null) {
		out.writeDouble(dp.getDiff1().getX());
		out.writeDouble(dp.getDiff1().getY());
	    }
	    if(dp.getDiff2()!=null) {
		out.writeDouble(dp.getDiff2().getX());
		out.writeDouble(dp.getDiff2().getY());
	    }
	}

	out.writeInt(itsControlePunt.size());
	while(iterC.hasNext()) {
	    ControlePunt cp = (ControlePunt) iterC.next();
	    out.writeDouble(cp.getX());
	    out.writeDouble(cp.getY());
	}

	out.writeInt(itsKnoop.size());
	while(iterK.hasNext()) {
	    Knoop kn = (Knoop) iterK.next();
	    out.writeDouble(kn.getValue());
	}
	out.writeLong(0xdeadbeef);
    }
    

    public void loadFromFile(RandomAccessFile in) 
    throws IOException {
	int dataPuntSize = in.readInt();

	for(int i=0;i<dataPuntSize;i++) {
	    int nDiffs = in.readInt();
	    double x = in.readDouble();
	    double y = in.readDouble();
	    DataPunt dp = new DataPunt(x, y);

	    if(nDiffs > 0) {
		x = in.readDouble();
		y = in.readDouble();
		dp.setDiff1(new Punt(x, y));
	    }
	    if(nDiffs > 1) {
		x = in.readDouble();
		y = in.readDouble();
		dp.setDiff2(new Punt(x, y));
	    }
	    itsDataPunt.add(dp);
	}

	int controlePuntSize = in.readInt();

	for(int i=0;i<controlePuntSize;i++) {
	    double x = in.readDouble();
	    double y = in.readDouble();
	    ControlePunt cp = new ControlePunt(x, y);

	    itsControlePunt.add(cp);
	}

	int knoopSize = in.readInt();

	for(int i=0;i<knoopSize;i++) {
	    double knoopVal = in.readDouble();

	    itsKnoop.add(new Knoop(knoopVal));
	}

	flushInputs();
    }

    public void outputBasisMatrix() {
	if(itsBasisMatrix!=null)
	    itsGebruikersInterface.getItsOutputVenster().getItsBasisMatrixVenster().setMatrix(itsBasisMatrix);
    }

    public BasisMatrix getItsBasisMatrix() {
        return itsBasisMatrix;
    }
    
    public void __setItsBasisMatrix(BasisMatrix p_BasisMatrix) {
        itsBasisMatrix = p_BasisMatrix;
    }
    
    public void _setItsBasisMatrix(BasisMatrix p_BasisMatrix) {
        if(itsBasisMatrix != null)
            itsBasisMatrix.__setItsGrafischeEngine(null);
        __setItsBasisMatrix(p_BasisMatrix);
    }
    
    public void setItsBasisMatrix(BasisMatrix p_BasisMatrix) {
        if(p_BasisMatrix != null)
            p_BasisMatrix._setItsGrafischeEngine(this);
        _setItsBasisMatrix(p_BasisMatrix);
    }
    
    public void _clearItsBasisMatrix() {
        itsBasisMatrix = null;
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
            p_ControlePunt._setItsGrafischeEngine(this);
        _addItsControlePunt(p_ControlePunt);
    }
    
    public void _removeItsControlePunt(ControlePunt p_ControlePunt) {
        itsControlePunt.remove(p_ControlePunt);
    }
    
    public void removeItsControlePunt(ControlePunt p_ControlePunt) {
        if(p_ControlePunt != null)
            p_ControlePunt.__setItsGrafischeEngine(null);
        _removeItsControlePunt(p_ControlePunt);
    }
    
    public void _clearItsControlePunt() {
        itsControlePunt.clear();
    }
    
    public void clearItsControlePunt() {
        ListIterator iter=itsControlePunt.listIterator(0);
        while (iter.hasNext()){
            ((ControlePunt)(iter.next()))._clearItsGrafischeEngine();
            
        }
        _clearItsControlePunt();
    }
    
    public ListIterator getItsDataPunt() {
        ListIterator iter=itsDataPunt.listIterator(0);
        return iter;
    }
    
    public void _addItsDataPunt(DataPunt p_DataPunt) {
        itsDataPunt.add(p_DataPunt);
    }
    
    public void addItsDataPunt(DataPunt p_DataPunt) {
        if(p_DataPunt != null)
            p_DataPunt._setItsGrafischeEngine(this);
        _addItsDataPunt(p_DataPunt);
    }
    
    public void _removeItsDataPunt(DataPunt p_DataPunt) {
        itsDataPunt.remove(p_DataPunt);
    }
    
    public void removeItsDataPunt(DataPunt p_DataPunt) {
        if(p_DataPunt != null)
            p_DataPunt.__setItsGrafischeEngine(null);
        _removeItsDataPunt(p_DataPunt);
    }
    
    public void _clearItsDataPunt() {
        itsDataPunt.clear();
    }
    
    public void clearItsDataPunt() {
        ListIterator iter=itsDataPunt.listIterator(0);
        while (iter.hasNext()){
            ((DataPunt)(iter.next()))._clearItsGrafischeEngine();
            
        }
        _clearItsDataPunt();
    }
    
    public GebruikersInterface getItsGebruikersInterface() {
        return itsGebruikersInterface;
    }

    public void setItsGebruikersInterface(GebruikersInterface itsGebruikersInterface) {
	this.itsGebruikersInterface = itsGebruikersInterface;
    }    

    public Graad getItsGraad() {
        return itsGraad;
    }
    
    public void __setItsGraad(Graad p_Graad) {
        itsGraad = p_Graad;
    }
    
    public void _setItsGraad(Graad p_Graad) {
        if(itsGraad != null)
            itsGraad.__setItsGrafischeEngine(null);
        __setItsGraad(p_Graad);
    }
    
    public void setItsGraad(Graad p_Graad) {
        if(p_Graad != null)
            p_Graad._setItsGrafischeEngine(this);
        _setItsGraad(p_Graad);
    }
    
    public void _clearItsGraad() {
        itsGraad = null;
    }
    
    public ListIterator getItsKnoop() {
        ListIterator iter=itsKnoop.listIterator(0);
        return iter;
    }

    public void setItsKnoop(LinkedList itsKnoop) {
	this.itsKnoop = itsKnoop;
    }
    
    public void _addItsKnoop(Knoop p_Knoop) {
        itsKnoop.add(p_Knoop);
    }
    
    public void addItsKnoop(Knoop p_Knoop) {
        if(p_Knoop != null)
            p_Knoop._setItsGrafischeEngine(this);
        _addItsKnoop(p_Knoop);
    }
    
    public void _removeItsKnoop(Knoop p_Knoop) {
        itsKnoop.remove(p_Knoop);
    }
    
    public void removeItsKnoop(Knoop p_Knoop) {
        if(p_Knoop != null)
            p_Knoop.__setItsGrafischeEngine(null);
        _removeItsKnoop(p_Knoop);
    }
    
    public void _clearItsKnoop() {
        itsKnoop.clear();
    }
    
    public void clearItsKnoop() {
        ListIterator iter=itsKnoop.listIterator(0);
        while (iter.hasNext()){
            ((Knoop)(iter.next()))._clearItsGrafischeEngine();
            
        }
        _clearItsKnoop();
    }
    
    public ListIterator getItsTree() {
        ListIterator iter=itsTree.listIterator(0);
        return iter;
    }
    
    public void _addItsTree(Tree p_Tree) {
        itsTree.add(p_Tree);
    }
    
    public void addItsTree(Tree p_Tree) {
        if(p_Tree != null)
            p_Tree._setItsGrafischeEngine(this);
        _addItsTree(p_Tree);
    }
    
    public void _removeItsTree(Tree p_Tree) {
        itsTree.remove(p_Tree);
    }
    
    public void removeItsTree(Tree p_Tree) {
        if(p_Tree != null)
            p_Tree.__setItsGrafischeEngine(null);
        _removeItsTree(p_Tree);
    }
    
    public void _clearItsTree() {
        itsTree.clear();
    }
    
    public void clearItsTree() {
        ListIterator iter=itsTree.listIterator(0);
        while (iter.hasNext()){
            ((Tree)(iter.next()))._clearItsGrafischeEngine();
            
        }
        _clearItsTree();
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GrafischeEngine.java
*********************************************************************/

