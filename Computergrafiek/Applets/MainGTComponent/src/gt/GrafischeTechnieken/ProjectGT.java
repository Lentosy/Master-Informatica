/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: ProjectGT
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\ProjectGT.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.imageio.*;
import java.io.*;
import java.awt.image.*;
import java.awt.geom.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\ProjectGT.java                                                                  
//----------------------------------------------------------------------------

//## class ProjectGT 
public class ProjectGT {

    private static final String bgImagePath = "images/woodsbig.jpg";
  
    protected GebruikersInterface itsGebruikersInterface;
    protected GrafischeEngine itsGrafischeEngine;
    protected OutputVenster itsOutputVenster;

    protected JWindow desktopWindow;

    // Constructors
    
    public ProjectGT() {
        initRelations();
	createDesktopPane();
    }
    
    private void createDesktopPane() {
	desktopWindow = new JWindow();

	Toolkit tk = desktopWindow.getToolkit();


	JLayeredPane lPane = new JLayeredPane();
	lPane.setDoubleBuffered(true);

	lPane.add(createBGPane(), Integer.MIN_VALUE);

	lPane.add(itsGebruikersInterface.getItsMenuVenster(), new Integer(1));
	lPane.add(itsGebruikersInterface.getItsOutputVenster(), new Integer(2));
	lPane.add(itsGebruikersInterface.getItsOutputVenster().getItsBasisMatrixVenster(), new Integer(2));
	lPane.add(itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster(), new Integer(2));
	lPane.add(itsGebruikersInterface.getItsMenuVenster().getItsGraadManipulatieVenster(), new Integer(2));
	lPane.add(itsGebruikersInterface.getItsMenuVenster().getItsHelpVenster(), new Integer(3));

	Color bgColor = new Color(0,0,0);
	// desktopPane.setBackground(bgColor);

	Font smallFont = new Font("SansSerif",Font.BOLD,11);

	desktopWindow.setLayeredPane(lPane);

	desktopWindow.setSize(tk.getScreenSize());
	desktopWindow.show();

	try {
	    itsGebruikersInterface.getItsMenuVenster().setSelected(true);
	    itsGebruikersInterface.getItsMenuVenster().show();

	    itsGebruikersInterface.getItsOutputVenster().setIcon(true);
	    itsGebruikersInterface.getItsOutputVenster().show();

	    itsGebruikersInterface.getItsOutputVenster().getItsBasisMatrixVenster().setIcon(true);
	    itsGebruikersInterface.getItsOutputVenster().getItsBasisMatrixVenster().show();

	    itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().setIcon(true);
	    itsGebruikersInterface.getItsOutputVenster().getItsGrafiekVenster().show();

	    itsGebruikersInterface.getItsMenuVenster().getItsHelpVenster().setIcon(true);
	    itsGebruikersInterface.getItsMenuVenster().getItsHelpVenster().show();

	} catch(java.beans.PropertyVetoException e) {e.printStackTrace();}
    }

    public JPanel createBGPane() {

	Toolkit tk = Toolkit.getDefaultToolkit();
	Dimension d = tk.getScreenSize();

	BufferedImage bgImg = new BufferedImage((int) d.getWidth(),(int) d.getHeight(),BufferedImage.TYPE_INT_RGB);
	Graphics2D bgGraph = bgImg.createGraphics();

	try {
	bgGraph.drawImage(ImageIO.read(new File(bgImagePath)), 0, 0, (int) d.getWidth(), (int) d.getHeight(), desktopWindow);
	} catch(IOException e) {}

	JLabel bgLabel = new JLabel(new ImageIcon(bgImg));
	bgLabel.setForeground(Color.black);
	bgLabel.setOpaque(true);

	JPanel testPane = new JPanel(new BorderLayout());
	testPane.add(bgLabel);
	testPane.setSize(tk.getScreenSize());
	testPane.setOpaque(false);

	return testPane;
    }

    public GebruikersInterface getItsGebruikersInterface() {
        return itsGebruikersInterface;
    }
    
    public GebruikersInterface newItsGebruikersInterface() {
        itsGebruikersInterface = new GebruikersInterface();
        return itsGebruikersInterface;
    }
    
    public void deleteItsGebruikersInterface() {
        itsGebruikersInterface=null;
    }
    
    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    
    public void deleteItsGrafischeEngine() {
        itsGrafischeEngine=null;
    }
    
    public OutputVenster getItsOutputVenster() {
        return itsOutputVenster;
    }
    
    public OutputVenster newItsOutputVenster() {
        itsOutputVenster = new OutputVenster();
        return itsOutputVenster;
    }
    
    public void deleteItsOutputVenster() {
        itsOutputVenster=null;
    }
    
    protected void initRelations() {
        itsGebruikersInterface = newItsGebruikersInterface();
        itsOutputVenster = newItsOutputVenster();
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\ProjectGT.java
*********************************************************************/

