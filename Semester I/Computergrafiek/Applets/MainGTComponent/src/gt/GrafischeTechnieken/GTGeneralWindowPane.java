package GrafischeTechnieken;


import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.imageio.*;
import java.io.*;


public class GTGeneralWindowPane extends JPanel implements ComponentListener {

    JFrame parentFrame;

    int mWIDTH = 513;
    int mHEIGHT = 519;

    double hFactor;
    double vFactor;

    int th, bh;
    int lw, rw;

    BufferedImage gtw_tl;
    BufferedImage gtw_tt;
    BufferedImage gtw_tstretch;
    BufferedImage gtw_tspace;
    BufferedImage gtw_tr;
    BufferedImage gtw_lstretch;
    BufferedImage gtw_cbg;
    BufferedImage gtw_rstretch;
    BufferedImage gtw_bl;
    BufferedImage gtw_bstretch;
    BufferedImage gtw_br;

    HorStretchPane tPanel;
    VertStretchPane lPanel;
    JPanel centerPanel;
    HorStretchPane bPanel;
    VertStretchPane rPanel;

    BufferedImage bg_buffer;
    Graphics2D bg_graphics;

    public GTGeneralWindowPane(int dWidth, int dHeight, int tHeight, int bHeight, int lWidth, int rWidth, double hFactor, double vFactor, JComponent cPane) {
	super(new BorderLayout());
	collectImages();
	mWIDTH = dWidth;
	mHEIGHT = dHeight;

	this.th = tHeight;
	this.bh = bHeight;

	this.lw = lWidth;
	this.rw = rWidth;

	this.hFactor = hFactor;
	this.vFactor = vFactor;

	tPanel = new HorStretchPane(gtw_tl, 13, gtw_tt, 128, gtw_tstretch, 
				    gtw_tspace, 78, gtw_tr, 13, mWIDTH, tHeight);

	bPanel = new HorStretchPane(gtw_bl, 13, gtw_tt, 0, gtw_bstretch, 
				    gtw_tspace, 0, gtw_br, 13, mWIDTH, bHeight);

	lPanel = new VertStretchPane(gtw_lstretch, lWidth, 473);
	rPanel = new VertStretchPane(gtw_rstretch, rWidth, 473);

	this.add(cPane);
	this.add(tPanel, BorderLayout.NORTH);
	this.add(bPanel, BorderLayout.SOUTH);
	this.add(lPanel, BorderLayout.WEST);
	this.add(rPanel, BorderLayout.EAST);

	this.addComponentListener(this);
    }

    public void setStretchablePane(JPanel p) {
	this.centerPanel = p;
    }

    public void collectImages() {
	try {

	    gtw_tl = ImageIO.read(new File("images/GTW_top_left.png"));
	    gtw_tt = ImageIO.read(new File("images/GTW_generic_title.png"));
	    gtw_tstretch = ImageIO.read(new File("images/GTW_top_stretch.png"));
	    gtw_tspace = ImageIO.read(new File("images/GTW_top_space.png"));
	    gtw_tr = ImageIO.read(new File("images/GTW_top_right.png"));
	    gtw_lstretch = ImageIO.read(new File("images/GTW_left_stretch.png"));
	    gtw_cbg = ImageIO.read(new File("images/GTW_center_bg.png"));
	    gtw_rstretch = ImageIO.read(new File("images/GTW_right_stretch.png"));
	    gtw_bl =  ImageIO.read(new File("images/GTW_bottom_left.png"));
	    gtw_bstretch =  ImageIO.read(new File("images/GTW_bottom_stretch.png"));
	    gtw_br =  ImageIO.read(new File("images/GTW_bottom_right.png"));

	} catch (IOException e) { 
	    System.out.println("problem reading image files. check your paths.");
	    System.exit(0);
	}
    }

    public Dimension getPreferredSize() {
	return new Dimension(mWIDTH, mHEIGHT);
    }

    public void setSize(int width, int height) {
	this.mWIDTH = width;
	this.mHEIGHT = height;

	tPanel.setNewWidth(width);
	bPanel.setNewWidth(width);
	lPanel.setNewHeight(height);
	rPanel.setNewHeight(height);
    }

    public void setBigTitle(String bTitle) {
	tPanel.setBigTitle(bTitle);
    }

    public void setSubTitle(String sTitle, int sWidth) {
	tPanel.setSubTitle(sTitle, sWidth);
    }

    private class VertStretchPane extends JPanel {
	int vWidth, vHeight;

	BufferedImage stretch;

	public VertStretchPane(BufferedImage stretch, int vWidth, int vHeight) {
	    this.stretch = stretch;

	    this.vWidth = vWidth;
	    this.vHeight = vHeight;
	}

	public void paintComponent(Graphics g) {
	    g.drawImage(stretch, 0, 0, vWidth, vHeight, this);
	}

	public Dimension getPreferredSize() {
	    return new Dimension(vWidth, vHeight);
	}

	public void setNewHeight(int height) {
	    this.vHeight = height;
	}

    }

    private class HorStretchPane extends JPanel {

	int hWidth, hHeight, lw, tw, spw, rw, stretchWidth;

	BufferedImage left, title, stretch, space, right;
	Font titleFont = new Font("Dialog",Font.BOLD,14);
	Font subTitleFont = new Font("Dialog", Font.BOLD, 11);
	String bTitle, sTitle;
	int subTitleWidth;

	public HorStretchPane(BufferedImage left, int lw, BufferedImage title,
			      int tw, BufferedImage stretch, BufferedImage space, int spw,
			      BufferedImage right, int rw, int defaultWidth, int height) {
	    super(null);

	    this.left = left;
	    this.right = right;
	    this.title = title;
	    this.stretch = stretch;
	    this.space = space;
	    
	    this.lw = lw;
	    this.rw = rw;
	    this.spw = spw;
	    this.tw = tw;
	    this.hWidth = defaultWidth;
	    this.hHeight = height;

	    bTitle = sTitle = "";

	    this.subTitleWidth = 0;
	    this.stretchWidth = defaultWidth - lw - rw - spw - tw;
	}

	public void paintComponent(Graphics g) {
	    int curwidth = 0;

	    g.drawImage(left, 0, 0, this);
	    curwidth+=lw;

	    if(tw!=0)
		g.drawImage(title, curwidth, 0, this);
	    
	    curwidth +=tw;

	    if(stretchWidth>0)
		g.drawImage(stretch, curwidth, 0, stretchWidth, hHeight, this);

	    curwidth += stretchWidth;
	    if(spw!=0)
		g.drawImage(space, curwidth, 0, this);

	    curwidth += spw;

	    if(rw!=0)
		g.drawImage(right, curwidth, 0, this);

	    if(tw!=0) {
		g.setColor(Color.darkGray);
		g.setFont(titleFont);
		g.drawString(bTitle,lw+20,22);
		g.setFont(subTitleFont);
		g.drawString(sTitle,lw+hWidth-subTitleWidth,22);
	    }

	    curwidth += rw;
	}

	public void setBigTitle(String bTitle) {
	    this.bTitle = bTitle;
	    repaint();
	}

	public void setSubTitle(String sTitle, int subTitleWidth) {
	    this.sTitle = sTitle;
	    this.subTitleWidth = subTitleWidth;
	    repaint();
	}

	public Dimension getPreferredSize() {
	    return new Dimension(hWidth, hHeight);
	}

	public void setNewWidth(int width) {
	    this.hWidth = width;
	    this.stretchWidth = hWidth - lw - rw - spw - tw;
	    repaint();
	}
    }

    public void componentHidden(ComponentEvent e) {

    }

    public void componentMoved(ComponentEvent e) {

    }

    public void componentResized(ComponentEvent e) {
	Dimension d = e.getComponent().getSize();
	int nWidth = (int) (d.getWidth()*hFactor);
	int nHeight = (int) (d.getHeight()*vFactor);

	this.setSize(nWidth, nHeight);

	tPanel.repaint();
	rPanel.repaint();
	tPanel.repaint();
	bPanel.repaint();
    }

    public void componentShown(ComponentEvent e) {

    }


}

