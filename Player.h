#ifndef PLAYER_H
#define PLAYER_H

#include "Participant.h"
class NimGame;
//class Participant;


/**
* @brief
* Runs moves for players, removes marbles from nimgame 
*/
class Player {
    private:

        int removing;
        
    public:

        /**
        * @brief 
        * Let's the player make a move, returns new marble amount
        * 
        * @param game needs game to access getMarbles()
        * @param p1Account user data will be updated for Player1 if Player1 wins
        * @param p2Account user data will be updated for Player2 if Player2 wins
        * 
        * @return remaining number of marbles
        */
        int makeMove(NimGame &game, Participant::Account &p1Account, Participant::Account &p2Account);

        /**
        * @brief 
        * A getter for Removing, used by playbyplay to tell amount removed 
        * 
        * @return amount the player removed
        */
        int getRemoving();

};

#endif