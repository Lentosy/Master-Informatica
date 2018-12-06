/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package auctionserver;

import java.nio.channels.Selector;
import java.util.TimerTask;

/**
 *
 * @author vongenae
 */
public class WaitForOffer extends TimerTask {
    Selector inputSelector;

    WaitForOffer(Selector inputSelector) {
        this.inputSelector = inputSelector;
    }

    @Override
    public void run() {
        inputSelector.wakeup();
    }
    
}
