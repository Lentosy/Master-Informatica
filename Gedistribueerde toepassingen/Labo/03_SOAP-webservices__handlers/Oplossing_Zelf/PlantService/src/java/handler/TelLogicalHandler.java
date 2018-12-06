/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package handler;

import com.sun.media.jfxmedia.logging.Logger;
import java.io.ByteArrayOutputStream;
import java.util.HashMap;
import java.util.Map;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.ws.LogicalMessage;
import javax.xml.ws.handler.LogicalHandler;
import javax.xml.ws.handler.LogicalMessageContext;
import javax.xml.ws.handler.MessageContext;

/**
 *
 * @author counterpoint
 */
public class TelLogicalHandler implements LogicalHandler<LogicalMessageContext> {
    
    Map<String, Integer> kleuren = new HashMap<>();
    
    public boolean handleMessage(LogicalMessageContext messageContext) {
                Boolean outboundProperty = (Boolean) messageContext.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
        
        if(!outboundProperty){ // enkel bij een inkomende call loggen, vermijden dat er dus tweemaal gelogt zal worden
            try {
                LogicalMessage message = messageContext.getMessage();
                Source payload = message.getPayload();
            
                TransformerFactory factory = TransformerFactory.newInstance();
                Transformer transformer = factory.newTransformer();
                ByteArrayOutputStream uit = new ByteArrayOutputStream();
                StreamResult result = new StreamResult(uit);
                transformer.transform(payload, result);
                String bericht = uit.toString();
                int startIndex = bericht.indexOf("<kleur>");
                int eindIndex = bericht.indexOf("</kleur>");
                
                if(startIndex > -1 && eindIndex > -1){
                    String kleur = bericht.substring(startIndex + 7, eindIndex);
                    if(kleuren.containsKey(kleur)){
                        kleuren.put(kleur, kleuren.get(kleur) + 1);
                    } else {
                        kleuren.put(kleur, 1);
                    }
                   
                    System.out.println(kleur + " is " + kleuren.get(kleur) + " maal opgevraagd");
                }
                
                
            } catch(TransformerException te){
                System.err.println(te.getMessage());
            }
        }    

        
        return true;
    }
    
    public boolean handleFault(LogicalMessageContext messageContext) {
        return true;
    }
    
    public void close(MessageContext context) {
    }
    
}
