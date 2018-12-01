/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ws;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringReader;
import java.util.Collections;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.namespace.QName;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.soap.SOAPException;
import javax.xml.soap.SOAPMessage;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMResult;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;
import jdk.internal.org.xml.sax.InputSource;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

/**
 *
 * @author khaluf
 */
public class E2DMessageHandler implements SOAPHandler<SOAPMessageContext> {

    @Override
    public boolean handleMessage(SOAPMessageContext messageContext) {
        /*message direction, true for outbound messages, false for inbound*/
        Boolean outbound = (Boolean) messageContext.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
        if (!outbound) {
            SOAPMessage msg = messageContext.getMessage();
            try {
                Source src = msg.getSOAPPart().getContent();
                TransformerFactory factory = TransformerFactory.newInstance();
                Transformer tf = factory.newTransformer(new StreamSource(this.getClass().getClassLoader().getResourceAsStream("ws/colorTranslation.xsl")));
               // StreamResult result = new StreamResult(resultStream);
               // tf.transform(src, result);
               // String resultMessage = resultStream.toString();
                //Logger.getLogger(TelLogicalHandler.class.getName()).log(Level.INFO, "res " +  resultMessage);
                DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder builder = dFactory.newDocumentBuilder();
              //  InputStream stream = new ByteArrayInputStream(resultMessage.getBytes());
                Document resultDoc = builder.newDocument();//builder.parse(stream);
                //DOMSource DOMresultsDoc = new DOMSource(resultDoc);
                DOMResult DOMresultsDoc = new DOMResult(resultDoc);
                tf.transform(src, DOMresultsDoc);
                msg.getSOAPPart().setContent(new DOMSource(DOMresultsDoc.getNode()));
            } catch (TransformerConfigurationException ex) {
                Logger.getLogger(E2DMessageHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (TransformerException | SOAPException ex) {
                Logger.getLogger(E2DMessageHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (ParserConfigurationException ex) {
                Logger.getLogger(E2DMessageHandler.class.getName()).log(Level.SEVERE, null, ex);
            /*} catch (SAXException ex) {
                Logger.getLogger(E2DMessageHandler.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IOException ex) {
                Logger.getLogger(E2DMessageHandler.class.getName()).log(Level.SEVERE, null, ex);
            }*/
            }

        }
        return true;
    }

    @Override
    public Set<QName> getHeaders() {
        return Collections.EMPTY_SET;
    }

    @Override
    public boolean handleFault(SOAPMessageContext messageContext) {
        return true;
    }

    public void close(MessageContext context) {
    }

}
