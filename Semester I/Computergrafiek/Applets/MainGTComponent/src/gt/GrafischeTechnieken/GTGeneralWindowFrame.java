package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;


public class GTGeneralWindowFrame extends JInternalFrame implements ComponentListener {

    GTGeneralWindowPane mPane;
    JPanel cPane;
    int prefW = 480;
    int prefH = 480;

    static Color beige = new Color(228,228,219);

    public GTGeneralWindowFrame(int prefW, int prefH) {
	super();

	this.prefW = prefW;
	this.prefH = prefH;

	cPane = new JPanel(new BorderLayout());

	this.setClosable(false);
	this.setMaximizable(true);
	this.setIconifiable(true);
	this.setResizable(true);

	this.getContentPane().setLayout(new BorderLayout());
    }

    public void addWest(JComponent c) {
	this.getContentPane().add(c, BorderLayout.WEST);
    }

    public void addSouth(JComponent c) {
	this.getContentPane().add(c, BorderLayout.SOUTH);
    }

    public void setStretchablePane(JComponent p) {

	if(mPane!=null && cPane !=null)
	    cPane.remove(mPane);

	mPane = new GTGeneralWindowPane(prefW, prefH,
					34, 12, 
					13, 13, 1, 1, p);

	cPane.add(mPane, BorderLayout.CENTER);
	cPane.setBorder(new MatteBorder(new Insets(10,10,10,10),GTGeneralWindowFrame.beige));

	this.getContentPane().add(cPane);
    }


    public void setBigTitle(String bTitle) {
	mPane.setBigTitle(bTitle);
    }

    public void setSubTitle(String sTitle, int sWidth) {
	mPane.setSubTitle(sTitle, sWidth);
    }

    public void componentHidden(ComponentEvent e) {

    }

    public void componentMoved(ComponentEvent e) {

    }

    public void componentShown(ComponentEvent e) {
	if(mPane!=null)
	    mPane.componentResized(e);
    }

    public void componentResized(ComponentEvent e) {
	if(mPane!=null)
	    mPane.componentResized(e);
    }
    /*
    public static void main(String [] args) {
	GTToolPane gttp = new GTToolPane();
	GTDrawingCanvas gtdc = new GTDrawingCanvas(gttp);
	GTGeneralWindowPane gtp = new GTGeneralWindowPane(480, 480,
							  34, 12, 
							  13, 13, 1, 1, gtdc);
	GTGeneralWindowFrame gtf = new GTGeneralWindowFrame();

	JPanel cPane = new JPanel(new BorderLayout());
	cPane.add(gtp, BorderLayout.CENTER);
	cPane.add(gttp, BorderLayout.WEST);
	cPane.setBorder(new MatteBorder(new Insets(10,10,10,10),beige));

	gtf.getContentPane().add(cPane);
	gtf.setSize(800,640);

	gtf.pack();
	gtf.show();
	}*/
}
