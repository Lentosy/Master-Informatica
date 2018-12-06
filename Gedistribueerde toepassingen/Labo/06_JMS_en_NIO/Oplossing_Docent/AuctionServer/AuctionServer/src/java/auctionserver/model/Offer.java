/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package auctionserver.model;

/**
 *
 * @author vongenae
 */
public class Offer {
    private Item item;
    private String client;
    private double currentOffer;
    
    public Offer(Item item) {
        this.item = item;
    }

    public Item getItem() {
        return item;
    }

    public String getClient() {
        return client;
    }

    public double getCurrentOffer() {
        return currentOffer;
    }
    
    public boolean offerAccepted(String client, double offer) {
        boolean accepted = false;
        if (sufficient(offer) && offer > currentOffer) {
            this.client = client;
            this.currentOffer = offer;
            accepted = true;
        }
        return accepted;
    }
     
    public boolean sufficient(double offer) {
        return item.getMinPrice() <= offer;
    }
}
