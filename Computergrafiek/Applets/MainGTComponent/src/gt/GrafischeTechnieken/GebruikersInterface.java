/*********************************************************************
	Rhapsody	: 4.0
	Login		: Administrator
	Component	: GTComponent
	Configuration 	: GTConfig
	Model Element	: GebruikersInterface
//!	Generated Date	: Tue, 9, Mar 1999 
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GebruikersInterface.java
*********************************************************************/

package GrafischeTechnieken;


import java.util.*;

//## package GrafischeTechnieken 

//----------------------------------------------------------------------------
// GrafischeTechnieken\GebruikersInterface.java                                                                  
//----------------------------------------------------------------------------

//## class GebruikersInterface 
public class GebruikersInterface {
    
    protected ConsoleVenster itsConsoleVenster;
    protected ArrayList itsGrafischeEngineList;
    protected GrafischeEngine itsGrafischeEngine;
    protected OutputVenster itsOutputVenster;
    protected MenuVenster itsMenuVenster;

    // tool to switch between different engines
    protected CurveSelectPane itsCurveSelectPane;

    protected LinkedList itsVensterEventHandler;
    
    // Constructors
    
    public  GebruikersInterface() {
        {
            itsVensterEventHandler=new LinkedList();
        }
        initRelations();

	itsGrafischeEngineList = new ArrayList();

	for(int i=0; i<itsCurveSelectPane.getMaxNumberOfCurves(); i++) {
	    if(i/4==0 || i/4==3)
		itsGrafischeEngineList.add(new Neville(this));
	    if(i/4==1)
		itsGrafischeEngineList.add(new BSpline(this));
	    if(i/4==2)
		itsGrafischeEngineList.add(new Bezier(this));

	}

	setActiveGrafischeEngine(0);
	flushGrafischeEngineInputs();
    }
    
    public ConsoleVenster getItsConsoleVenster() {
        return itsConsoleVenster;
    }
    
    public ConsoleVenster newItsConsoleVenster() {
        itsConsoleVenster = new ConsoleVenster();
        return itsConsoleVenster;
    }
    
    public void deleteItsConsoleVenster() {
        itsConsoleVenster=null;
    }
    
    public GrafischeEngine getItsGrafischeEngine() {
        return itsGrafischeEngine;
    }
    

    public void __setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        itsGrafischeEngine = p_GrafischeEngine;
	itsMenuVenster.setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void _setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(itsGrafischeEngine != null)
            itsGrafischeEngine.setItsGebruikersInterface(null);
        __setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine) {
        if(p_GrafischeEngine != null)
            p_GrafischeEngine.setItsGebruikersInterface(this);
        _setItsGrafischeEngine(p_GrafischeEngine);
    }
    
    public void setItsGrafischeEngine(GrafischeEngine p_GrafischeEngine, int id) {
	if(p_GrafischeEngine != null)
            p_GrafischeEngine.setItsGebruikersInterface(this);
	itsGrafischeEngineList.set(id, p_GrafischeEngine);
    }

    public void setActiveGrafischeEngine(int id) {
	if(itsGrafischeEngineList!=null && itsGrafischeEngineList.get(id) != null)
	    __setItsGrafischeEngine((GrafischeEngine)itsGrafischeEngineList.get(id)); 
    }

    // adjust all inputs to the current grafische engine
    public void flushGrafischeEngineInputs() {
	if(itsGrafischeEngine!=null)
	    itsGrafischeEngine.flushInputs();
    }

    public void _clearItsGrafischeEngine() {
        itsGrafischeEngine = null;
    }
    
    public OutputVenster getItsOutputVenster() {
        return itsOutputVenster;
    }
    
    public void __setItsOutputVenster(OutputVenster p_OutputVenster) {
        itsOutputVenster = p_OutputVenster;
    }
    
    public void _setItsOutputVenster(OutputVenster p_OutputVenster) {
        if(itsOutputVenster != null)
            itsOutputVenster.__setItsGebruikersInterface(null);
        __setItsOutputVenster(p_OutputVenster);
    }
    
    public OutputVenster newItsOutputVenster() {
        itsOutputVenster = new OutputVenster();
        itsOutputVenster._setItsGebruikersInterface(this);
        return itsOutputVenster;
    }
    
    public void deleteItsOutputVenster() {
        itsOutputVenster.__setItsGebruikersInterface(null);
        itsOutputVenster=null;
    }
    
    public MenuVenster getItsMenuVenster() {
        return itsMenuVenster;
    }
    
    public MenuVenster newItsMenuVenster() {
        itsMenuVenster = new MenuVenster();
        return itsMenuVenster;
    }
    
    public void deleteItsMenuVenster() {
        itsMenuVenster=null;
    }
    
    public ListIterator getItsVensterEventHandler() {
        ListIterator iter=itsVensterEventHandler.listIterator(0);
        return iter;
    }
    
    public ListIterator getItsVensterEventHandlerEnd() {
        return itsVensterEventHandler.listIterator(itsVensterEventHandler.lastIndexOf(itsVensterEventHandler.getLast()));
    }
    
    public void _addItsVensterEventHandler(VensterEventHandler p_VensterEventHandler) {
        itsVensterEventHandler.add(p_VensterEventHandler);
    }
    
    public VensterEventHandler newItsVensterEventHandler() {
        VensterEventHandler newVensterEventHandler = new VensterEventHandler();
        newVensterEventHandler._setItsGebruikersInterface(this);
        itsVensterEventHandler.add(newVensterEventHandler);
        return newVensterEventHandler;
    }
    
    public void _removeItsVensterEventHandler(VensterEventHandler p_VensterEventHandler) {
        itsVensterEventHandler.remove(p_VensterEventHandler);
    }
    
    public void deleteItsVensterEventHandler(VensterEventHandler p_VensterEventHandler) {
        p_VensterEventHandler._setItsGebruikersInterface(null);
        itsVensterEventHandler.remove(p_VensterEventHandler);
        p_VensterEventHandler=null;
    }

    protected void initRelations() {
        itsConsoleVenster = newItsConsoleVenster();
        itsOutputVenster = newItsOutputVenster();
        itsMenuVenster = newItsMenuVenster();
	itsCurveSelectPane = new CurveSelectPane(this);
	itsMenuVenster.setCurveSelectPane(itsCurveSelectPane);

        itsConsoleVenster._setItsMenuVenster(itsMenuVenster);
    }
    
}
/*********************************************************************
	File Path	: GTComponent\GTConfig\GrafischeTechnieken\GebruikersInterface.java
*********************************************************************/

