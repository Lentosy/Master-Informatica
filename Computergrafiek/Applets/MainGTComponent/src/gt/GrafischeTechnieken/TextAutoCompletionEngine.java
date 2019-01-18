package GrafischeTechnieken;

import java.util.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class TextAutoCompletionEngine implements KeyListener {

    TextArea target;

    String [] completionStrings = {"voegToePunt",
				   "verwijderPunt",
				   "verplaatsPunt", "voegToeAfgeleide", "verwijderAfgeleide",
				   "voegToeTweedeAfgeleide", "verwijderTweedeAfgeleide",
				   "voegToeKnoop", "maakUniform", "maakOpenUniform", "wijzigGraad",
				   "berekenCurve", "verwijderCurve", "veranderCurve", "veranderType", "save", "load",
				   "save2png"};

    String [] paramStrings = {"double x,double y",
			      "int index",
			      "int index, double x, double y", "int index, double x, double y",
			      "int index", "int index, double x, double y", "int index",
			      "double t", "", "",
			      "int nieuwe_graad", "", "", "int nieuwe_index", "int nieuw_type", "string filename",
			      "string filename", "string filename"};

    String stringBuffer;

    public TextAutoCompletionEngine(TextArea target) {
	this.target = target;

	initStrings();
	stringBuffer = "";
    }

    public void initStrings() {
    }

    private void completeCommand(int id, KeyEvent e) {
	target.replaceSelection(completionStrings[id]+"(");
	target.getCommandInfoLabel().setText("<html><B>"+completionStrings[id]+
					     "</B><font color=#555555 size=2>&nbsp("+
					     paramStrings[id]+")");
	e.consume();
    }

    public void tryToExecute() {
	String lastLine = target.getText();
	lastLine = lastLine.substring(lastLine.lastIndexOf('\n')+1,lastLine.length());
	String commandPart = (lastLine.split("\\(")[0]).toLowerCase();

	int id = 0;
	for(id=0;id<completionStrings.length;id++)
	    if(completionStrings[id].toLowerCase().equals(commandPart))
		break;

	if(id < completionStrings.length) {
	    // valid command
	    int paramLength;
	    if(paramStrings[id].length() == 0)
		paramLength = 0;
	    else
		paramLength = paramStrings[id].split(",").length;

	    String paramPart;
	    if(lastLine.endsWith("("))
		paramPart = "";
	    else
		paramPart = (lastLine.split("\\(")[1]).toLowerCase().split("\\)")[0];

	    if((paramLength!=0 && paramPart.split(",").length != paramLength) ||
	       (paramLength==0 && paramPart.split(",")[0].length()!=0) ) {
		target.getCommandInfoLabel().setText("<html><font color=#995555 size=+1>ERR:</font>&nbsp;&nbsp;wrong parameters</FONT><font color=#555555 size=2>&nbsp&nbsp("+paramStrings[id]+")</HTML>");
		return;
	    }
	    
	    target.getItsConsoleVenster().executeCommand(id, paramPart.split(","));
	}
	else {
	    target.getCommandInfoLabel().setText("<html><font color=#995555 size=+1>ERR:</font>&nbsp;&nbsp;no such command : '<I><font color=#555599>"+commandPart+"</FONT></I>'</HTML>");
	    return;
	}
    }

    public void keyPressed(KeyEvent e) {
	if(e.getKeyChar() == '\n') {
	    tryToExecute();
	}

	if(!e.isShiftDown()) {
	    if(e.getKeyCode() == 112) //voegtoepunt
		completeCommand(0, e);
	    if(e.getKeyCode() == 113) //verplaatspunt
		completeCommand(2, e);
	    if(e.getKeyCode() == 114) //voegtoeafgeleide
		completeCommand(3, e);
	    if(e.getKeyCode() == 115) //voegtoetweedeafgeleide
		completeCommand(5, e);
	    if(e.getKeyCode() == 116) //voegtoeknoop
		completeCommand(7, e);
	    if(e.getKeyCode() == 117) //maakUniform
		completeCommand(8, e);
	    if(e.getKeyCode() == 118) //wijzigGraad
		completeCommand(10, e);
	    if(e.getKeyCode() == 119) //berekenCurve
		completeCommand(11, e);
	    if(e.getKeyCode() == 120) //veranderCurve
		completeCommand(13, e);
	    if(e.getKeyCode() == 122) //save
		completeCommand(15, e);
	    if(e.getKeyCode() == 123) //save
		completeCommand(17, e);

	}
	else {
	    if(e.getKeyCode() == 112) //verwijderpunt
		completeCommand(1, e);
	    if(e.getKeyCode() == 114) //verwijderafgeleide
		completeCommand(4, e);
	    if(e.getKeyCode() == 115) //verwijdertweedeafgeleide
		completeCommand(6, e);
	    if(e.getKeyCode() == 117) //maakOpenUniform
		completeCommand(9, e);
	    if(e.getKeyCode() == 119) //verwijderCurve
		completeCommand(12, e);
	    if(e.getKeyCode() == 120) //veranderType
		completeCommand(14, e);
	    if(e.getKeyCode() == 122) //load
		completeCommand(16, e);
	}
	if(e.isShiftDown() && !e.isControlDown()) {
	}
	if(e.isControlDown() && !e.isShiftDown()) {
	    if(e.getKeyCode() == 78)
		completeCommand(0, e);

	}
	if(e.isControlDown() && e.isShiftDown()) {
	    if(e.getKeyCode() == 78)
		completeCommand(1, e);
	}
	if(!e.isControlDown() && !e.isShiftDown()) {
	}
    }

    public void keyReleased(KeyEvent e) {

    }

    public void keyTyped(KeyEvent e) {
    }
}






