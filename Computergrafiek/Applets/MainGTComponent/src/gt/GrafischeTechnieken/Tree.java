/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: Tree
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Tree.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\Tree.java                                                                  
//----------------------------------------------------------------------------

//## class Tree 
public class Tree {
    
    protected GrafischeEngine itsGrafischeEngine;
    
    // Constructors
    
    public  Tree() {
    }
    
    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    
    public void __setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        itsGrafischeEngine = p_GrafischeEngine;
    }
    
    public void _setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(itsGrafischeEngine != null)
            itsGrafischeEngine._removeItsTree(this);
        __setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(p_GrafischeEngine != null)
            p_GrafischeEngine._addItsTree(this);
        _setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void _clearItsGrafischeEngine() {
        itsGrafischeEngine = null;
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\Tree.java
*********************************************************************/

