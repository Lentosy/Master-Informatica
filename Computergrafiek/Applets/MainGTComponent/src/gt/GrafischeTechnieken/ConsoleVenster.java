/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: ConsoleVenster
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\ConsoleVenster.java
*********************************************************************/

package GrafischeTechnieken;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.io.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\ConsoleVenster.java                                                                  
//----------------------------------------------------------------------------

//## class ConsoleVenster 
public class ConsoleVenster extends JFrame {
    
    public static final Color neutralGray = new Color(200,200,200);

    protected MenuVenster itsMenuVenster;
    protected TextArea itsTextArea;
    protected JLabel outputLabel;

    // Constructors
    
    public  ConsoleVenster() {
	super();//300, 250);
        initRelations();

	placeOutputPane();
	placeTextPane(400, 200);

	this.setTitle("Console");
	this.pack();
    }
    
    private void placeTextPane(int prefW, int prefH) {
	JScrollPane scrollPane = new JScrollPane(itsTextArea);

	scrollPane.setBorder(new CompoundBorder(new MatteBorder(new Insets(10,10,10,10), ConsoleVenster.neutralGray),
					  new EtchedBorder()));

	JPanel cPane = new JPanel(new BorderLayout());

	GTGeneralWindowPane mPane = new GTGeneralWindowPane(prefW, prefH,
					34, 12, 
					13, 13, 1, 1, scrollPane);

	cPane.add(mPane, BorderLayout.CENTER);
	cPane.setBorder(new MatteBorder(new Insets(10,10,10,10),GTGeneralWindowFrame.beige));
	mPane.setBigTitle("Input");
	this.getContentPane().add(cPane);
    }

    private void placeOutputPane() {

	JPanel pane = new JPanel(new BorderLayout());
	GTGeneralWindowPane gPane = new GTGeneralWindowPane(240,80,34,12,13,13,1,1,
							    outputLabel);
	pane.add(gPane);
	pane.setBorder(new MatteBorder(new Insets(10,10,10,10),GTGeneralWindowFrame.beige));

	gPane.setBigTitle("Output");

	this.getContentPane().add(pane, BorderLayout.SOUTH);

    }

    public void executeCommand(int id, String [] params) {
	switch(id) {
	case 0: // voegtoepunt
	    if(itsMenuVenster.getItsTekenVenster().getType() == 0)
		voegtoeDataPunt(params[0], params[1]);
	    else 
		voegtoeControlePunt(params[0], params[1]);

	    itsMenuVenster.getItsKnopenManipulatieVenster().addKnoop();
	    berekenCurve();
	    break;
	case 1: // verwijderpunt
	    if(itsMenuVenster.getItsTekenVenster().getType() == 0)
		verwijderDataPunt(params[0]);
	    else 
		verwijderControlePunt(params[0]);
	     
	    maakUniform();
	    berekenCurve();
	    break;
	case 2: // verplaatsPunt
	    if(itsMenuVenster.getItsTekenVenster().getType() == 0)
		verplaatsDataPunt(params[0], params[1], params[2]);
	    else 
		verplaatsControlePunt(params[0], params[1], params[2]);
    
	    berekenCurve();
	    break;
	case 3: //verander afgeleide
	    verplaatsAfgeleide(params[0], params[1], params[2]);
	    berekenCurve();
	    break;
	case 4: //verwijder afgeleide
	    verwijderAfgeleide(params[0]);
	    verwijderTweedeAfgeleide(params[0]);
	    berekenCurve();
	    break;
	case 5: //verander 2de afgeleide
	    verplaatsTweedeAfgeleide(params[0], params[1], params[2]);
	    berekenCurve();
	    break;
	case 6: //verander 2de afgeleide
	    verwijderTweedeAfgeleide(params[0]);
	    berekenCurve();
	    break;
	case 7: //voegtoeknoop
	    voegtoeKnoop(params[0]);
	    berekenCurve();
	    break;
	case 8: //maakUniform
	    maakUniform();
	    berekenCurve();
	    break;
	case 9: //maakOpenUniform
	    maakOpenUniform();
	    berekenCurve();
	    break;
	case 10: //wijzigGraad
	    wijzigGraad(params[0]);
	    berekenCurve();
	    break;
	case 11: //berekenCurve
	    berekenCurve();
	    break;
	case 12: //verwijderCurve
	    verwijderCurve();
	    break;
	case 13: //veranderCurve
	    veranderCurve(params[0]);
	    break;
	case 14: //veranderCurve
	    veranderType(params[0]);
	    break;
	case 15: //save
	    save(params[0]);
	    break;
	case 16: //load
	    load(params[0]);
	    berekenCurve();
	    break;
	case 17:
	    save2png(params[0]);
	    break;
	}
    }

    //## operation berekenCurve() 
    public void berekenCurve() {
        //#[ operation berekenCurve() 
	itsMenuVenster.getItsGrafischeEngine().berekenCurve();
        //#]
    }
    
    //## operation bewaarPuntSequentie() 
    public void bewaarPuntSequentie() {
        //#[ operation bewaarPuntSequentie() 
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
    
    //## operation herschaalAssen() 
    public void herschaalAssen() {
        //#[ operation herschaalAssen() 
        //#]
    }
    
    //## operation laadGTScript() 
    public void laadGTScript() {
        //#[ operation laadGTScript() 
        //#]
    }
    
    //## operation laadPuntSequentie() 
    public void laadPuntSequentie() {
        //#[ operation laadPuntSequentie() 
        //#]
    }
    
    //## operation maakLeeg() 
    public void maakLeeg() {
        //#[ operation maakLeeg() 
        //#]
    }
    
    //## operation verplaatsControlePunt() 
    public void verplaatsControlePunt(String index, String x, String y) {
        //#[ operation verplaatsControlePunt() 
	int indexInt = Integer.parseInt(index);
	double dx = Double.parseDouble(x);
	double dy = Double.parseDouble(y);

	itsMenuVenster.getItsGrafischeEngine().verplaatsControlePunt(indexInt, new ControlePunt(dx, dy));
        //#]
    }
    
    //## operation verplaatsDataPunt() 
    public void verplaatsDataPunt(String index, String x, String y) {
        //#[ operation verplaatsDataPunt() 
	int indexInt = Integer.parseInt(index);
	double dx = Double.parseDouble(x);
	double dy = Double.parseDouble(y);

	itsMenuVenster.getItsGrafischeEngine().verplaatsDataPunt(indexInt, new DataPunt(dx, dy));
        //#]
    }
    
    //## operation verplaatsKnoop() 
    public void verplaatsKnoop() {
        //#[ operation verplaatsKnoop() 
        //#]
    }
    
    public void verplaatsAfgeleide(String index, String x, String y) {
	int indexInt = Integer.parseInt(index);
	double dx = Double.parseDouble(x);
	double dy = Double.parseDouble(y);

	itsMenuVenster.getItsGrafischeEngine().verplaatsAfgeleide(indexInt, new DataPunt(dx, dy));
    }
    
    public void verwijderAfgeleide(String index) {
	int indexInt = Integer.parseInt(index);

	itsMenuVenster.getItsGrafischeEngine().verwijderAfgeleide(indexInt);
    }

    public void verplaatsTweedeAfgeleide(String index, String x, String y) {
	int indexInt = Integer.parseInt(index);
	double dx = Double.parseDouble(x);
	double dy = Double.parseDouble(y);

	itsMenuVenster.getItsGrafischeEngine().verplaatsTweedeAfgeleide(indexInt, new DataPunt(dx, dy));
    }
    
    public void verwijderTweedeAfgeleide(String index) {
	int indexInt = Integer.parseInt(index);

	itsMenuVenster.getItsGrafischeEngine().verwijderTweedeAfgeleide(indexInt);
    }

    //## operation verwijderControlePunt() 
    public void verwijderControlePunt(String index) {
        //#[ operation verwijderControlePunt()
	int indexInt = Integer.parseInt(index);

	itsMenuVenster.getItsGrafischeEngine().verwijderControlePunt(indexInt);
    }
    
    //## operation verwijderDataPunt() 
    public void verwijderDataPunt(String index) {
        //#[ operation verwijderDataPunt() 
	int indexInt = Integer.parseInt(index);

	itsMenuVenster.getItsGrafischeEngine().verwijderDataPunt(indexInt);
    }
    
    //## operation verzetOorsprong() 
    public void verzetOorsprong() {
        //#[ operation verzetOorsprong() 
        //#]
    }
    
    
    //## operation voegtoeControlePunt() 
    public void voegtoeControlePunt(String x, String y) {
	//#[ operation voegtoeDataPunt() 
	double xd = Double.parseDouble(x);
	double yd = Double.parseDouble(y);

	itsMenuVenster.getItsGrafischeEngine().voegtoeControlePunt(new ControlePunt(xd, yd));
        //#]
    }
    
    //## operation voegtoeDataPunt() 
    public void voegtoeDataPunt(String x, String y) {
        //#[ operation voegtoeDataPunt() 
	double xd = Double.parseDouble(x);
	double yd = Double.parseDouble(y);

	itsMenuVenster.getItsGrafischeEngine().voegtoeDataPunt(new DataPunt(xd, yd));
        //#]
    }
    
    public void save(String filename) {
	try {
	    RandomAccessFile out = new RandomAccessFile(filename, "rw");
	    out.writeLong(0xdeadbeef);
	    out.writeInt(itsMenuVenster.getCurveSelectPane().getType());
	    itsMenuVenster.getItsGrafischeEngine().saveToFile(out);
	} catch(IOException e) {
	    System.out.println("problem writing output file!");
	}
    }

    public void load(String filename) {
	try {

	    RandomAccessFile in = new RandomAccessFile(filename, "r");
	    long first = in.readLong();
	    if(first!=0xdeadbeef) {
		System.out.println("invalid curve file");
		return;
	    }
	    verwijderCurve();
	    int type = in.readInt();
	    veranderType(type+"");
	    itsMenuVenster.getItsGrafischeEngine().loadFromFile(in);

	} catch(IOException e) {
	    System.out.println("problem reading input file!");
	}
    }

    public void save2png(String filename) {
	try {
	itsMenuVenster.getItsGrafischeEngine().getItsGebruikersInterface().getItsOutputVenster().saveOutputToPng(filename);
	} catch(IOException e) {
	    System.out.println("problem writing image file");
	}
    }

    //## operation voegtoeKnoop() 
    public void voegtoeKnoop(String knoop_val) {
        //#[ operation voegtoeKnoop() 
	double dval = Double.parseDouble(knoop_val);
	itsMenuVenster.getItsGrafischeEngine().voegtoeKnoop(dval);
        //#]
    }
    
    public void verwijderCurve() {
	itsMenuVenster.getItsGrafischeEngine().verwijderCurve();
    }

    public void veranderCurve(String index) {
	int indexInt = Integer.parseInt(index);

	itsMenuVenster.getCurveSelectPane().setActiveLabel(indexInt-1);
    }

    public void veranderType(String type) {
	int nieuwType = Integer.parseInt(type);
	itsMenuVenster.getCurveSelectPane().veranderType(nieuwType);
    }

    public void wijzigGraad(String graad) {
	int graadInt = Integer.parseInt(graad);
	itsMenuVenster.getItsGrafischeEngine().wijzigGraad(graadInt);
    }

    public void maakUniform() {
	itsMenuVenster.getItsGrafischeEngine().maakUniform();
    }

    public void maakOpenUniform() {
	itsMenuVenster.getItsGrafischeEngine().maakOpenUniform();
    }

    public PuntenVenster getItsMenuVenster() {
        return itsMenuVenster;
    }
    
    public void _setItsMenuVenster(MenuVenster p_MenuVenster) {
        itsMenuVenster = p_MenuVenster;
	itsMenuVenster.setItsConsoleVenster(this);
    }

    public TextArea getItsTextArea() {
        return itsTextArea;
    }
    
    public void __setItsTextArea(TextArea p_TextArea) {
        itsTextArea = p_TextArea;
    }
    
    public void _setItsTextArea(TextArea p_TextArea) {
        if(itsTextArea != null)
            itsTextArea.__setItsConsoleVenster(null);
        __setItsTextArea(p_TextArea);
    }
    
    public TextArea newItsTextArea(JLabel outputLabel) {
        itsTextArea = new TextArea(outputLabel);
        itsTextArea._setItsConsoleVenster(this);
        return itsTextArea;
    }
    
    public void deleteItsTextArea() {
        itsTextArea.__setItsConsoleVenster(null);
        itsTextArea=null;
    }
    
    protected void initRelations() {
	outputLabel = new JLabel("<html><P align=center><font size=2>[this window will display command info]</html>");
	outputLabel.setBorder(new EmptyBorder(new Insets(0,20,0,20)));

        itsTextArea = newItsTextArea(outputLabel);
    }
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\ConsoleVenster.java
*********************************************************************/

