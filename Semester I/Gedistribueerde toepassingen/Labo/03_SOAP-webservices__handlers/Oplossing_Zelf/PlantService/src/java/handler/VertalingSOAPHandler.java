/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package handler;

import java.util.Collections;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.namespace.QName;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.soap.SOAPException;
import javax.xml.soap.SOAPMessage;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMResult;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamSource;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;
import org.w3c.dom.Document;

/**
 *
 * @author counterpoint
 */
public class VertalingSOAPHandler implements SOAPHandler<SOAPMessageContext> {
    
    @Override
    public boolean handleMessage(SOAPMessageContext messageContext) {
        Boolean outboundProperty = (Boolean) messageContext.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
        if(!outboundProperty){
            SOAPMessage msg = messageContext.getMessage();
            try {
                
                Source source = msg.getSOAPPart().getContent();
                TransformerFactory factory =  TransformerFactory.newInstance();
                Transformer transformer = factory.newTransformer(new StreamSource(this.getClass().getClassLoader().getResourceAsStream("handler/vertalingen.xsl")));
                
                DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder builder = dFactory.newDocumentBuilder();
                
                Document resultDoc = builder.newDocument();
                
                
                DOMResult DOMresultsDoc = new DOMResult(resultDoc);
                transformer.transform(source, DOMresultsDoc);
                msg.getSOAPPart().setContent(new DOMSource(DOMresultsDoc.getNode()));
                
            } catch (SOAPException ex) {
                Logger.getLogger(VertalingSOAPHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (TransformerConfigurationException ex) {
                Logger.getLogger(VertalingSOAPHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (TransformerException ex) {
                Logger.getLogger(VertalingSOAPHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (ParserConfigurationException ex) {
                Logger.getLogger(VertalingSOAPHandler.class.getName()).log(Level.SEVERE, null, ex);
            } 
             
        }
        
        
        
        return true;
    }
    
    public Set<QName> getHeaders() {
        return Collections.EMPTY_SET;
    }
    
    public boolean handleFault(SOAPMessageContext messageContext) {
        return true;
    }
    
    public void close(MessageContext context) {
    }
    
}
