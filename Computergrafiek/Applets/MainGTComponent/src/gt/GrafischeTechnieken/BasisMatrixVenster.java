package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.imageio.*;
import java.io.*;

public class BasisMatrixVenster extends Window {

    protected BasisMatrix [] matrices;
    protected BasisMatrix matrix;

    protected JPanel contentPane;
    boolean multipleMatrices;

    public BasisMatrixVenster() {
	super(250,200);

	this.setTitle("BasisMatrix");

	contentPane = new JPanel();
	contentPane.setBackground(new Color(200,200,200));

	this.setStretchablePane(contentPane);

	this.pack();
    }

    public void setMatrix(BasisMatrix matrix) {
	multipleMatrices = false;
	this.matrix = matrix;
	renewContent();
    }

    public void setMatrices(BasisMatrix [] matrices) {
	multipleMatrices = true;
	this.matrices = matrices;
	renewContent();
    }

    public void renewContent() {
	contentPane.removeAll();

	if((!multipleMatrices && matrix == null) || (multipleMatrices && matrices == null))
	    return;

	if(multipleMatrices) {

	    JTabbedPane tabPane = new JTabbedPane(JTabbedPane.RIGHT);

	    int nMatrix = 0;
	    for(nMatrix=0;nMatrix<matrices.length;nMatrix++) {
		JPanel matrixPane = new JPanel(new GridLayout(matrices[nMatrix].getSize(),matrices[nMatrix].getSize(), 5, 5));

		for(int i=0;i<matrices[nMatrix].getSize();i++)
		    for(int j=0;j<matrices[nMatrix].getSize();j++) {
			JLabel valLabel = new JLabel(matrices[nMatrix].getElementAt(j,i)+"", SwingConstants.CENTER);
			valLabel.setBackground(new Color(240,250,250));
			valLabel.setBorder(new EtchedBorder());

			matrixPane.add(valLabel);
		    }
		tabPane.add(nMatrix+"",matrixPane);
		contentPane.setLayout(new BorderLayout());
		contentPane.add(tabPane);
	    }
	    if(nMatrix==1)
		this.setBigTitle("B-Matrix");
	    else
		this.setBigTitle("B-Matrices ("+nMatrix+")");

	    // if(matrices[0]!=null)
	    // this.setSize(new Dimension(220 + (matrices[0].getSize())*30,220 + (matrices[0].getSize())*30));
	    if(!this.isIcon())
		this.pack();
	}
	else {
	    contentPane.setLayout(new GridLayout(matrix.getSize(),matrix.getSize(), 5, 5));

	    for(int i=0;i<matrix.getSize();i++)
		for(int j=0;j<matrix.getSize();j++) {
		    JLabel valLabel = new JLabel(matrix.getElementAt(j,i)+"", SwingConstants.CENTER);
		    valLabel.setBackground(new Color(240,250,250));
		    valLabel.setBorder(new EtchedBorder());

		    contentPane.add(valLabel);
		}

	    this.setBigTitle("LagrangeMatrix");

	    // this.setSize(new Dimension(220 + (matrix.getSize())*30,220 + (matrix.getSize())*30));
	    if(!this.isIcon())
		this.pack();
	}
    }
}
