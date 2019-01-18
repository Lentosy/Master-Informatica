package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.image.*;
import java.awt.geom.*;
import javax.imageio.*;
import java.io.*;

public class GTToolPane extends JPanel {
    GTToolLabel [] labels;
    PuntenVenster parent;

    String [] toolDescr = {"add", "remove", "move", "zoom", "pan"};
    int nTools = 5;
    int activeID;

    public GTToolPane(PuntenVenster parent) {
	super();
	this.parent = parent;
	this.setBackground(GTGeneralWindowFrame.beige);

	JPanel cPane = new JPanel(new GridLayout(0,1));
	Font smallFont = new Font("SansSerif",Font.BOLD,11);

	this.setBorder(new MatteBorder(new Insets(13,10,10,10),
				       GTGeneralWindowFrame.beige));

	cPane.setBorder(new CompoundBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.gray,1)," Tools ",TitledBorder.CENTER,TitledBorder.TOP,smallFont,Color.black),new MatteBorder(new Insets(0,5,5,5),GTGeneralWindowFrame.beige)));
	//cPane.setBorder(new CompoundBorder(BorderFactory.createTitledBorder(new EtchedBorder()," Tools ",TitledBorder.CENTER,TitledBorder.TOP,smallFont,Color.black),new MatteBorder(new Insets(0,5,5,5),GTGeneralWindowFrame.beige)));

	cPane.setBackground(GTGeneralWindowFrame.beige);

	labels = new GTToolLabel[nTools];

	try {
	     for(int i=0;i<nTools;i++) {
		labels[i] = new GTToolLabel(toolDescr[i],
					    ImageIO.read(new File("images/tool_"+i+".png")),
					    this,
					    i);
		cPane.add(labels[i]);
	     }
	     

	     activeID = 0;
	     labels[activeID].setActive();
	     labels[activeID].repaintImg();
	     this.add(cPane);

	} catch (IOException e) {
	    System.out.println("problem reading image files. check your paths.");
	    System.exit(0);
	}
    }

    public void setActive(int id) {
	if(activeID!=id) {
	    labels[activeID].deActivate();
	    this.activeID = id;
	}
    }

    public int getMode() {
	return activeID;
    }


}
