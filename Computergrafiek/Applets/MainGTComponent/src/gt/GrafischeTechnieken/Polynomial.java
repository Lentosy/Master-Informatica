package GrafischeTechnieken;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.text.*;

public class Polynomial extends Vector {

    public Polynomial() {
	super();
    }

    public Polynomial(double val) {
	super();
	this.setElementAt(new Double(val),0);
    }

    public Polynomial(Polynomial p) {
	super();
	for(int i=0;i<p.size();i++)
	    this.setElementAt(p.elementAt(i),i);
    }

    public void multiply(Polynomial p2) {
	for(int i=0;i<p2.size();i++) {
	    Polynomial auxP = new Polynomial(this);
	    auxP.scalar((Double) p2.elementAt(i));
	    auxP.shiftLeft(i);
	    sum(auxP);
	}
    }

    public void scalar(Double f) {
	for(int i=0;i<size();i++)
	    this.setElementAt(new Double(f.doubleValue()*((Double) elementAt(i)).doubleValue()),i);
    }

    public void shiftLeft(int s) {
	for(int i=size()-1;i>s;i--)
	    this.setElementAt(elementAt(i),i+s);
	for(int i=0;i<s;i++)
	    this.setElementAt(new Double(0),i);
    }

    public void add(double d) {
	setElementAt(new Double(d),size());
    }

    public void sum(Polynomial p2) {
	for(int i=0;i<p2.size();i++) {
	    if(elementAt(i) == null)
		setElementAt(p2.elementAt(i), i);
	    else
		setElementAt(new Double(((Double) p2.elementAt(i)).doubleValue() +
					((Double) elementAt(i)).doubleValue()), i);
	}
    }

    public double eval(double t) {
	double result = 0;
	for(int i=0;i<size();i++)
	    result+=((Double) elementAt(i)).doubleValue() * Math.pow(t,i);

	return result;
    }

    public static void main(String [] args) {
	Polynomial p = new Polynomial();
	Polynomial p2 = new Polynomial();

	p.add(5.0);
	p.add(2.0);
	p.add(3.0);

	p2.add(1.0);
	p2.add(8.0);

	p.multiply(p2);
	p.eval(1.0);
    }
}
