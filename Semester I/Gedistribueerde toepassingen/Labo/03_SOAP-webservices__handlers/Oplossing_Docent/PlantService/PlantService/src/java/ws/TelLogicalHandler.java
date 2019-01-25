/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ws;

import java.io.ByteArrayOutputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.ws.LogicalMessage;
import javax.xml.ws.handler.LogicalHandler;
import javax.xml.ws.handler.LogicalMessageContext;
import javax.xml.ws.handler.MessageContext;

/**
 *
 * @author vongenae
 */
public class TelLogicalHandler implements LogicalHandler<LogicalMessageContext> {

    Map<String, Integer> telKleuren = new HashMap<>();

    @Override
    public boolean handleMessage(LogicalMessageContext messageContext) {

        Boolean outboundProperty = (Boolean) messageContext.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);

        if (!outboundProperty) {
            try {
                LogicalMessage lm = messageContext.getMessage();
                Source payload = lm.getPayload();
                TransformerFactory tFact = TransformerFactory.newInstance();
                Transformer tf = tFact.newTransformer();
                ByteArrayOutputStream uit = new ByteArrayOutputStream();
                StreamResult result = new StreamResult(uit);
                tf.transform(payload, result);
                String bericht = uit.toString();
                int startKleur = bericht.indexOf("<kleur>");
                int stopKleur = bericht.indexOf("</kleur>");
                if (startKleur > -1 && stopKleur > -1) {
                    String kleur = bericht.substring(startKleur+7, stopKleur);
                    if (telKleuren.containsKey(kleur)) {
                        telKleuren.put(kleur, telKleuren.get(kleur)+1);
                    } else {
                        telKleuren.put(kleur, 1);
                    }
                    Logger.getLogger(TelLogicalHandler.class.getName()).log(Level.INFO, kleur 
                            + "  is " + telKleuren.get(kleur) + " keer opgevraagd.");
                }
                
            } catch (TransformerConfigurationException ex) {
                Logger.getLogger(TelLogicalHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (TransformerException ex) {
                Logger.getLogger(TelLogicalHandler.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        return true;
    }

    @Override
    public boolean handleFault(LogicalMessageContext messageContext) {
        return true;
    }

    @Override
    public void close(MessageContext context) {
    }

}
