package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;
import java.io.*;


public class CurveSelectPane extends JPanel implements ActionListener {

    int aantal;

    int WIDTH = 80;
    int HEIGHT = 120;
    CurveSelectLabel activeLabel;

    CurveSelectLabel [] labels;
    GebruikersInterface GUI;

    JMenuItem lagrange, bspline, bezier, graad;

    public CurveSelectPane(GebruikersInterface GUI) {
	super();

	this.GUI = GUI;

	this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

	JPanel cPane = new JPanel(new GridLayout(4,4,4,4));
	Font smallFont = new Font("SansSerif",Font.BOLD,11);

	this.setBackground(GTGeneralWindowFrame.beige);
	cPane.setBackground(GTGeneralWindowFrame.beige);

	aantal = 16;
	labels = new CurveSelectLabel [aantal];
	for(int i=0; i<aantal; i++) {
	    labels[i] = new CurveSelectLabel(i+1, this, (i/4)%3);
	    cPane.add(labels[i]);
	}

	graad = new JMenuItem("Graad...");

	cPane.setBorder(new MatteBorder(new Insets(5,4,2,4),GTGeneralWindowFrame.beige));

	this.setBorder(new CompoundBorder(new MatteBorder(new Insets(0,18,10,13),GTGeneralWindowFrame.beige), BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.gray,1)," Curve # ",TitledBorder.CENTER,TitledBorder.TOP,smallFont,Color.black)));

	this.add(cPane);

	JPanel menuPane = new JPanel();
	JMenuBar menuBar1 = new JMenuBar();
	JMenuItem snijpunten;

	JMenu menu1 = new JMenu("    Opties    ");
	JMenu menu2 = new JMenu("Type");

	menu2.add(lagrange = new JRadioButtonMenuItem("Lagrange"));
	menu2.add(bspline = new JRadioButtonMenuItem("B-Spline"));
	menu2.add(bezier = new JRadioButtonMenuItem("Bézier"));

	ButtonGroup group = new ButtonGroup();
	group.add(lagrange);
	group.add(bspline);
	group.add(bezier);
	lagrange.addActionListener(this);
	bspline.addActionListener(this);
	bezier.addActionListener(this);

	menu2.add(new JSeparator());

	menu2.add(graad);

	graad.addActionListener(this);

	menu1.add(menu2);
	menu1.add(new JSeparator());

	menu1.setBorder(new EtchedBorder());
	// menu2.setBorder(new EtchedBorder());

	menuBar1.add(menu1);

	menuPane.add(menuBar1);
	// menuPane.add(menuBar2);

	menuBar1.setBackground(GTGeneralWindowFrame.beige);
	menuBar1.setBorder(new EmptyBorder(new Insets(0,0,-1,0)));

	menuPane.setBackground(GTGeneralWindowFrame.beige);

	menu1.setBackground(new Color(216,238,235));
	menu2.setBackground(new Color(250,216,215));

	setActive(labels[0]);

	this.add(menuPane);

	JPanel iconPane = new JPanel(new GridLayout(3,0));
	JLabel iconLabel;
	Font miniFont = new Font("Dialog", Font.BOLD, 10);
	iconLabel = new JLabel("= lagrange",new ImageIcon("images/lagrange_icon.png"),SwingConstants.LEFT);
	iconLabel.setFont(miniFont);
	iconLabel.setOpaque(false);
	iconPane.add(iconLabel);

	iconLabel = new JLabel("= b-spline",new ImageIcon("images/bspline_icon.png"),SwingConstants.LEFT);
	iconLabel.setFont(miniFont);
	iconLabel.setOpaque(false);
	iconPane.add(iconLabel);

	iconLabel = new JLabel("= bézier",new ImageIcon("images/bezier_icon.png"),SwingConstants.LEFT);
	iconLabel.setFont(miniFont);
	iconLabel.setOpaque(false);
	iconPane.add(iconLabel);
	iconPane.setBorder(new EmptyBorder(new Insets(0,5,0,5)));
	iconPane.setOpaque(false);
	this.add(iconPane);
    }

    public void setActive(CurveSelectLabel activeLabel) {
	int oldType;

	if(this.activeLabel==null)
	    oldType = 0;
	else
	    oldType = this.activeLabel.getType();

	if(this.activeLabel!=null)
	    this.activeLabel.setUnactive();

	this.activeLabel = activeLabel;
	activeLabel.setActive();
	int newType = activeLabel.getType();

	switch(newType) {
	case 0:
	    lagrange.setSelected(true);
	    graad.setEnabled(false);
	    break;
	case 1:
	    bspline.setSelected(true);
	    graad.setEnabled(true);
	    break;
	case 2:
	    bezier.setSelected(true);
	    graad.setEnabled(false);
	    break;
	}
	GUI.getItsMenuVenster().getItsMenu().setTypeSelected(newType);

	GUI.setActiveGrafischeEngine(activeLabel.getId()-1);
	GUI.getItsMenuVenster().getItsTekenVenster().changeTypeOfCurve(oldType, activeLabel.getType());
	GUI.flushGrafischeEngineInputs();
    }

    public void setActiveLabel(int nIndex) {
	if(nIndex>=0 && nIndex<aantal)
	    setActive(labels[nIndex]);
    }

    public Dimension getPreferredSize() {
	return new Dimension(WIDTH, HEIGHT);
    }

    public int getMaxNumberOfCurves() {
	return aantal;
    }

    public int getType() {
	if(activeLabel!=null)
	    return activeLabel.getType();
	else
	    return 0;
    }

    public void veranderType(int nieuw_type) {
	switch(nieuw_type) {
	case 0:
	    if(activeLabel.getType() != 0) {
		int oldType = activeLabel.getType();
		activeLabel.setType(0);
		GUI.setItsGrafischeEngine(new Neville(GUI), activeLabel.getId()-1);
		graad.setEnabled(false);
		GUI.getItsMenuVenster().getItsMenu().setTypeSelected(0);
		GUI.setActiveGrafischeEngine(activeLabel.getId()-1);
		GUI.getItsMenuVenster().getItsTekenVenster().changeTypeOfCurve(oldType, activeLabel.getType());
		GUI.flushGrafischeEngineInputs();
	    }
	    break;
	case 1:
	    if(activeLabel.getType() != 1) {
		int oldType = activeLabel.getType();
		activeLabel.setType(1);
		GUI.setItsGrafischeEngine(new BSpline(GUI), activeLabel.getId()-1);
		graad.setEnabled(true);
		GUI.getItsMenuVenster().getItsMenu().setTypeSelected(1);
		GUI.setActiveGrafischeEngine(activeLabel.getId()-1);
		GUI.getItsMenuVenster().getItsTekenVenster().changeTypeOfCurve(oldType, activeLabel.getType());
		GUI.flushGrafischeEngineInputs();
	    }
	    break;
	case 2:
	    if(activeLabel.getType() != 2) {
		int oldType = activeLabel.getType();
		activeLabel.setType(2);
		GUI.setItsGrafischeEngine(new Bezier(GUI), activeLabel.getId()-1);
		graad.setEnabled(false);
		GUI.getItsMenuVenster().getItsMenu().setTypeSelected(2);
		GUI.setActiveGrafischeEngine(activeLabel.getId()-1);
		GUI.getItsMenuVenster().getItsTekenVenster().changeTypeOfCurve(oldType, activeLabel.getType());
		GUI.flushGrafischeEngineInputs();
	    }
	    break;
	}
    }

    public void actionPerformed(ActionEvent e) {
	String str = e.getActionCommand();
	if(str.equals("Graad..."))
	    GUI.getItsMenuVenster().getItsGraadManipulatieVenster().show();
	if(str.equals("Lagrange"))
	    veranderType(0);
	if(str.equals("B-Spline"))
	    veranderType(1);
	if(str.equals("Bézier"))
	    veranderType(2);
    }
}
