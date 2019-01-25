package GrafischeTechnieken;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.image.*;
import java.awt.geom.*;

public class GTToolLabel extends JLabel implements MouseListener {

    String description;
    BufferedImage toolImg;

    BufferedImage buf;
    Graphics2D bufG;

    GTToolPane parent;

    static Color beige = new Color(228,228,219);
    static Color neutral = new Color(240,240,240);
    static Color active = new Color(250,210,210);
    static Color mouseover = new Color(210,250,210);

    int id;

    static int imgW = 30;
    static int imgH = 30;

    int state;

    public GTToolLabel(String description, BufferedImage toolImg, 
		       GTToolPane parent, int id) {
	this.description = description;
	this.toolImg = toolImg;
	this.parent = parent;
	this.id = id;

	buf = new BufferedImage(imgW,imgH,BufferedImage.TYPE_INT_ARGB_PRE);
	bufG = buf.createGraphics();
	bufG.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			      RenderingHints.VALUE_ANTIALIAS_ON);

	repaintImg();

	this.setText(description);
	this.setBackground(beige);

	state = 0;

	this.addMouseListener(this);

	id ++;
    }

    public void setActive() {
	state = 1;
	parent.setActive(id);
	repaintImg();
    }

    public void setMouseOver() {
	state = 2;
	repaintImg();

    }

    public void deActivate() {
	state = 0;
	repaintImg();
    }

    public void repaintImg() {
	bufG.setColor(beige);
	bufG.fillRect(0,0,imgW, imgH);

	switch (state) {
	case 0:
	    bufG.setColor(neutral);
	    bufG.fillOval(2,2,imgW-4,imgH-4);
	    bufG.setColor(Color.black);
	    bufG.drawOval(2,2,imgW-4,imgH-4);
	    this.setForeground(Color.gray);
	    break;
	case 1:
	    bufG.setColor(active);
	    bufG.fillRect(2,2,imgW-4,imgH-4);
	    bufG.setColor(Color.black);
	    bufG.drawRect(2,2,imgW-4,imgH-4);
	    this.setForeground(Color.black);
	    break;
	case 2:
	    bufG.setColor(mouseover);
	    bufG.fillOval(2,2,imgW-4,imgH-4);
	    bufG.setColor(Color.black);
	    bufG.drawOval(2,2,imgW-4,imgH-4);
	    this.setForeground(Color.white);
	    break;
	}

	bufG.drawImage(toolImg,7,7,this);

	this.setIcon(new ImageIcon(buf));

    }

    public void mouseClicked(MouseEvent e) {

    }

    public void mousePressed(MouseEvent e) {
	if(state!=1) {
	    setActive();
	}
    }

    public void mouseEntered(MouseEvent e) {
	if(state!=1 && state!= 2) {
	    setMouseOver();
	}
    }

    public void mouseExited(MouseEvent e) {
	if(state!=1 && state!= 0) {
	    deActivate();
	}
    }

    public void mouseReleased(MouseEvent e) {

    }
}
