/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package be.tiwi.planten.service;

import java.util.HashMap;
import java.util.Map;
import javax.xml.ws.LogicalMessage;
import javax.xml.ws.handler.LogicalHandler;
import javax.xml.ws.handler.LogicalMessageContext;
import javax.xml.ws.handler.MessageContext;

/**
 *
 * @author Bert
 */
public class KleurLogicalHandler implements LogicalHandler<LogicalMessageContext> {

    private static Map<String, Integer> frequenties = new HashMap<>();

    @Override
    public boolean handleMessage(LogicalMessageContext messageContext) {

        // Map<String, List<String>> s = (Map<String, List<String>>) messageContext.get(MessageContext.HTTP_REQUEST_HEADERS);
        //  QName n = (QName) messageContext.get(MessageContext.WSDL_OPERATION);$
        String s = (String) messageContext.get(MessageContext.QUERY_STRING);
        String kleur = "";
        LogicalMessage message = messageContext.getMessage();
        boolean inbound = !(boolean) messageContext.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
        if (inbound) {
            if (frequenties.containsKey(kleur)) {
                frequenties.put(kleur, frequenties.get(kleur) + 1);
            } else {
                frequenties.put(kleur, 1);
            }

            System.out.println("Info:\t" + kleur + " is " + frequenties.get(kleur) + " keer opgevraagd.");
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
