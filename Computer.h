#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>
#include <string>
#include "Participant.h"
class NimGame;
//class Participant;


/**
* @brief
* Essentially another player, just automatic, removes marbles from nimgame 
*/
class Computer{

    private:
        int Removing;
    public:
        class Mode{
            
            private:
                int difficulty;
            public:

                /**
                * @brief 
                * A getter for difficulty
                * 
                * @return difficulty
                */
                int getDifficulty();

                /**
                * @brief 
                *  A setter for difficulty
                */
                void setDifficulty(int set);
        };

        /**
        * @brief 
        * Normal mode for the computer, grabs random amount
        * 
        * @param game needs game to access getMarbles() 
        * @param p1Account total wins and wins against CPU will be appended if Player1 wins
        * 
        * @return remaining number of marbles
        */
        int computerNormal(NimGame &game, Participant::Account &p1Account);

        /**
        * @brief 
        * Advanced mode for computer, grabs marbles to make it 2^n -1 
        * 
        * @param game needs game to access getMarbles()
        * @param p1Account total wins and wins against CPU will be appended if Player1 wins
        * 
        * @return remaining number of marbles
        */
        int computerAdvanced(NimGame &game, Participant::Account &p1Account);

        /**
        * @brief 
        * A getter for Removing, used for playbyplay to tell amount removed 
        * 
        * @return amount the computer removed
        */
        int getRemoving();
};


#endif