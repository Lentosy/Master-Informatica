/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tictactoeserver;

import java.util.Scanner;

/**
 *
 * @author counterpoint
 */
public class TicTacToeServer {
    
    public static void main(String[] args){
        
        Thread tictactoeThread = new TicTacToeThread();
        tictactoeThread.start();
               
        
        
        Scanner sc = new Scanner(System.in);
        String input;
        do {
            input = sc.nextLine();
        } while (!input.equals("quit"));   
    }
}
