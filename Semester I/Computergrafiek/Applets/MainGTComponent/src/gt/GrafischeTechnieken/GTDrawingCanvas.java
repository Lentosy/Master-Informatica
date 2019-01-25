package GrafischeTechnieken;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.image.*;
import java.awt.geom.*;
import javax.imageio.*;
import java.io.*;

public class GTDrawingCanvas extends JPanel {
    
    BufferedImage bgBuf;
    BufferedImage gridBuf;

    Graphics2D gridBufG;

    int mWidth, mHeight;
    boolean withBG;

    GTToolPane tools;

    public GTDrawingCanvas(boolean withBG) {
	super();
	this.tools = null;
	this.withBG = withBG;

	try {
	    if(withBG)
		bgBuf = ImageIO.read(new File("images/GTW_center_bg.jpg"));
	} catch (IOException e) {
	    System.out.println("problem reading image files. check your paths.");
	    System.exit(0);
	}

    }


    public GTDrawingCanvas(GTToolPane tools) {
	super();
	this.tools = tools;

	try {
	    bgBuf = ImageIO.read(new File("images/GTW_center_bg.png"));
	} catch (IOException e) {
	    System.out.println("problem reading image files. check your paths.");
	    System.exit(0);
	}

    }

    public void redrawGrid() {
	mWidth = getWidth();
	mHeight = getHeight();

	gridBuf = new BufferedImage(mWidth,mHeight,BufferedImage.TYPE_INT_RGB);

	gridBufG = gridBuf.createGraphics();
	gridBufG.setColor(new Color(200,200,200));

	if(withBG)
	    gridBufG.drawImage(bgBuf, 0, 0, getWidth(), getHeight(), this);
	else
	    gridBufG.fillRect(0, 0, getWidth(), getHeight());
    }

    public Dimension getPreferredWidth() {
	    return new Dimension(mWidth, mHeight);
    }
}
