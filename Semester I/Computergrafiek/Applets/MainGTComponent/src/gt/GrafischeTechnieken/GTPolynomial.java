package GrafischeTechnieken;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.text.*;

public class GTPolynomial extends Vector {

    public GTPolynomial() {
	super();
    }

    public GTPolynomial(double val) {
	super();
	add(val);
    }

    public GTPolynomial(GTPolynomial p) {
	super();
	setSize(p.size());
	for(int i=0;i<p.size();i++)
	    this.setElementAt(p.elementAt(i),i);
    }

    public GTPolynomial multiply(GTPolynomial p2) {
	GTPolynomial result = new GTPolynomial();

	for(int i=0;i<p2.size();i++) {
	    GTPolynomial auxP = new GTPolynomial(this);
	    auxP.scalar((Double) p2.elementAt(i));
	    auxP.shiftLeft(i);
	    result = result.sum(auxP);
	}

	return result;
    }

    public void scalar(Double f) {
	for(int i=0;i<size();i++)
	    this.setElementAt(new Double(f.doubleValue()*((Double) elementAt(i)).doubleValue()),i);
    }

    public void shiftLeft(int s) {
	if(s>0) {
	    setSize(size()+s);
	    for(int i=size()-1;i>=s;i--)
		this.setElementAt(elementAt(i-s),i);
	    for(int i=0;i<s;i++)
		this.setElementAt(new Double(0),i);
	}
    }

    public void add(double d) {
	setSize(size()+1);
	setElementAt(new Double(d),size()-1);
    }

    public GTPolynomial sum(GTPolynomial p2) {
	GTPolynomial p = new GTPolynomial(this);

	if(p2.size()>p.size())
	    p.setSize(p2.size());

	for(int i=0;i<p2.size();i++) {
	    if(p.elementAt(i) == null)
		p.setElementAt(p2.elementAt(i), i);
	    else
		p.setElementAt(new Double(((Double) p2.elementAt(i)).doubleValue() +
					  ((Double) p.elementAt(i)).doubleValue()), i);
	}

	return p;
    }

    public double eval(double t) {
	double result = 0;
	for(int i=0;i<size();i++)
	    result+=((Double) elementAt(i)).doubleValue() * Math.pow(t,i);

	return result;
    }

    public void print() {
	for(int i=0;i<size();i++)
	    System.out.print(elementAt(i).toString()+", ");

	    System.out.println();
    }

    public static void main(String [] args) {
	GTPolynomial p = new GTPolynomial();
	GTPolynomial p2 = new GTPolynomial();

	p.add(-1.0);
	p.add(2.0);
	p.add(-3.0);

	p2.add(4.0);
	p2.add(-5.0);
	p2.add(5.0);
	p2.add(10.0);

	p = p.multiply(p2);
	System.out.println(p.eval(2.0));
    }
}
