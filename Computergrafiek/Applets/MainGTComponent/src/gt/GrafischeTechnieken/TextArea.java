/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: TextArea
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\TextArea.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.text.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\TextArea.java                                                                  
//----------------------------------------------------------------------------

//## class TextArea 
public class TextArea extends JTextPane {
    
    protected ConsoleVenster itsConsoleVenster;

    protected TextAutoCompletionEngine autoCompletionEngine;

    protected String commandString;
    protected String paramString;

    protected JLabel commandInfoLabel;

    // Constructors
    
    public  TextArea(JLabel commandInfoLabel) {
	super();

	this.commandInfoLabel = commandInfoLabel;
	this.setEnabled(true);
	this.setEditable(true);
	autoCompletionEngine = new TextAutoCompletionEngine(this);
	this.addKeyListener(autoCompletionEngine);

	this.setDoubleBuffered(true);

    }
    
    public ConsoleVenster getItsConsoleVenster() {
        return itsConsoleVenster;
    }
    
    public JLabel getCommandInfoLabel() {
	return commandInfoLabel;
    }

    public void setWrongCommand(String bufferString) {
	commandInfoLabel.setText("<html><font color=#995555 size=+1>ERR:</font>&nbsp;&nbsp;no command starts with : '<I><font color=#555599>"+
	bufferString+"</FONT></I>'</HTML>");
    }

    public void setParamString(String paramString) {
	this.paramString = paramString;
    }

    public void setCommandString(String commandString) {
	this.commandString = commandString;
	StyledDocument content = this.getStyledDocument();

	commandInfoLabel.setText("<html><B>"+commandString+
				 "</B>&nbsp;&nbsp;<font color=#555555 size=2>(press <B>[TAB]</B> to complete.)</font></html>" );
    }

    public String setCommandCompleted() {

	String [] commandParameters;

	if(!paramString.equals(""))
	    commandParameters = paramString.split(",");
	else {
	    commandParameters = new String[1];
	    commandParameters[0] = "void";
	}

	if(commandParameters.length > 0) {
	    String contentString = "<html><B>"+commandString+
		"(</B><font color=#555555 size=2>";
	    for(int i=0; i<commandParameters.length;i++) {
		contentString += commandParameters[i];
		if(i<commandParameters.length-1)
		    contentString+=", ";
	    }

	    commandInfoLabel.setText(contentString+"</font><B>)</b></html");
	    //	    try {
		//	    } catch(BadLocationException e) {}
	    replaceSelection(commandString+"(");
	    return commandString;
	}

	return null;
    }

    public void __setItsConsoleVenster(ConsoleVenster p_ConsoleVenster) {
        itsConsoleVenster = p_ConsoleVenster;
    }
    
    public void _setItsConsoleVenster(ConsoleVenster p_ConsoleVenster) {
        if(itsConsoleVenster != null)
            itsConsoleVenster.__setItsTextArea(null);
        __setItsConsoleVenster(p_ConsoleVenster);
    }
    
    public void setItsConsoleVenster(ConsoleVenster p_ConsoleVenster) {
        if(p_ConsoleVenster != null)
            p_ConsoleVenster._setItsTextArea(this);
        _setItsConsoleVenster(p_ConsoleVenster);
    }
    
    public void _clearItsConsoleVenster() {
        itsConsoleVenster = null;
    }

    public static void main(String [] args) {
	JFrame testFrame = new JFrame("test");
	JLabel outputLabel  = new JLabel("<html>test</html>");

	testFrame.getContentPane().add(new TextArea(outputLabel),BorderLayout.NORTH);
	testFrame.getContentPane().add(outputLabel);
	testFrame.setSize(new Dimension(300,300));
	testFrame.pack();
	testFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	testFrame.show();
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\TextArea.java
*********************************************************************/

