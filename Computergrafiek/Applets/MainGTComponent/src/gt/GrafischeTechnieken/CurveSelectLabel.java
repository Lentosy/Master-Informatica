package GrafischeTechnieken;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;
import java.io.*;


public class CurveSelectLabel extends JLabel implements MouseListener{
    Color mouseOver = new Color(250,250,200);
    Color [] activeColor = new Color[3];

    boolean isActive;
    int number;
    int WIDTH = 15;
    int HEIGHT = 15;
    int type; // 0: neville; 1: b-spline; 2: bezier

    Color bgColor;
    CurveSelectPane parent;

    public CurveSelectLabel(int number, CurveSelectPane parent, int type){
	this.setBackground(GTGeneralWindowFrame.beige);

	this.number = number;
	this.parent = parent;
	this.addMouseListener(this);
	this.setFont(new Font("Monospaced",Font.BOLD,9));
	this.type = type;

	this.isActive = false;

	activeColor[0] = new Color(250,200,200);
	activeColor[1] = new Color(210,220,250);
	activeColor[2] = new Color(200,240,210);
	bgColor = activeColor[type];
    }

    public void paintComponent(Graphics g) {
	((Graphics2D) g).setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			   RenderingHints.VALUE_ANTIALIAS_ON);
	if(isActive) {
	    g.setColor(bgColor);
	    g.fillRect(0,0,WIDTH, HEIGHT);
	    ((Graphics2D) g).setStroke(new BasicStroke(2.0f));
	    g.setColor(Color.white);
	    g.drawRect(0,0,WIDTH, HEIGHT);
	    ((Graphics2D) g).setStroke(new BasicStroke(1.0f));
	    g.setColor(Color.black);
	    g.drawRect(0,0,WIDTH, HEIGHT);
	}
	else {
	    g.setColor(new Color(Math.min(255,bgColor.getRed()+20), 
				 Math.min(255,bgColor.getGreen()+20), 
				 Math.min(255,bgColor.getBlue()+20), 120));
	    g.fillRoundRect(0,0,WIDTH, HEIGHT,5,5);
	    g.setColor(new Color(120,120,120));
	    g.drawRoundRect(0,0,WIDTH, HEIGHT,5,5);
	}

	if(isActive)
	    g.setColor(Color.black);
	else
	    g.setColor(Color.darkGray);

	((Graphics2D) g).setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
			   RenderingHints.VALUE_ANTIALIAS_OFF);
	if(number < 10)
	    g.drawString(""+number,6,11);
	else
	    g.drawString(""+number,3,11);
    }

    public Dimension getPreferredSize() {
	return new Dimension(WIDTH+1, HEIGHT+1);
    }

    public void setUnactive() {
	this.isActive = false;
	repaint();
    }

    public void setType(int type) {
	this.type = type;
	bgColor = activeColor[type];
	repaint();
    }

    public int getType() {
	return type;
    }

    public void setActive() {
	this.isActive = true;
	this.bgColor = activeColor[type];
	repaint();
    }

    public int getId() {
	return number;
    }

    public void mousePressed(MouseEvent e) {
	this.bgColor = activeColor[type];
	parent.setActive(this);
	repaint();
    }
    
    public void mouseClicked(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
	if(!isActive) {
	    bgColor = mouseOver;
	    repaint();
	}
    }

    public void mouseExited(MouseEvent e) {
	if(bgColor==mouseOver) {
	    bgColor = activeColor[type];
	    repaint();
	}
    }
}
