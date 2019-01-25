/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * Author:  bdsaffel
 * Created: Dec 10, 2018
 */

CREATE TABLE Game(
    ID INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY (START WITH 1, INCREMENT BY 1),
    NAME_PLAYER_ONE VARCHAR(30) NOT NULL,
    NAME_PLAYER_TWO VARCHAR(30) NOT NULL
);

CREATE TABLE Decision(      
    GAME_ID INT NOT NULL,
    ROUND INT NOT NULL,
    DECISION_PLAYER_ONE INT NOT NULL,
    DECISION_PLAYER_TWO INT NOT NULL,
    CONVICTION_PLAYER_ONE INT NOT NULL,
    CONVICTION_PLAYER_TWO INT NOT NULL,
    PRIMARY KEY (GAME_ID, ROUND),
    FOREIGN KEY (GAME_ID) REFERENCES Game(ID)
);


