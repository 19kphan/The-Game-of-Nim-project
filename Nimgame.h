#ifndef NIMGAME_H
#define NIMGAME_H

#include "Player.h"
#include "Computer.h"
#include "Participant.h"


/**
* @brief
* Runs the whole game, connecting all the classes together to act as an engine
*/
class NimGame{
    private:
        int marbles;
        int choice;
        int currentTurn;
        int playAgainstPlayer2;


    public:
        class PlayByPlay{
                private:
                    int newGame;
                    int flip;
                    int lock;
                public:

                    /**
                    * @brief 
                    * Writes turns made to a txt file
                    * 
                    * @param game for access to marbles and currentTurn
                    * @param player to find out how many marbles were removed
                    * @param computer to find out how many marbles were removed
                    */
                    void writeToFile(NimGame &game, Player &player, Computer &computer);

                    /**
                    * @brief 
                    * Sets newGame to 1 
                    */
                    void setNewGame();
            };

        /**
        * @brief 
        * Initializes game for player vs computer/player and difficulty of computer
        *
        * @param computer 
        * @param mode set difficulty for computer
        * @param playbyplay to reset newGame for when it writes to txt file
        * @param p1 corresponding Participant object for Player 1
        * @param p1Name corresponding ParticipantProfile object for Player 1, holds name
        * @param p1Account corresponding Account object for Player 1, holds stats for profile chosen
        * @param p2 corresponding Participant object for Player 1
        * @param p2Name corresponding ParticipantProfile object for Player 1, holds name
        * @param p2Account corresponding Account object for Player 1, holds stats for profile chosen
        *
        */
        void initializeGame(Computer &computer, Computer::Mode &mode, NimGame::PlayByPlay &playbyplay, 
            Participant &p1, Participant::ParticipantProfile &p1Name, Participant::Account &p1Account,
            Participant &p2, Participant::ParticipantProfile &p2Name, Participant::Account &p2Account );

        /**
        * @brief 
        * Randomly sets turn order to which player will go first, changes currentTurn
        */
        void turnOrder();

        /**
        * @brief 
        * Sets marbles to a random value between 10 and 1000
        */
        void initializeMarbles();

        /**
        * @brief 
        * A setter for marbles
        * 
        * @param amount sets marbles to amount 
        */
        void setMarbles(int amount);

        /**
        * @brief 
        * Main code for running Nimgame, connects all files together to make the game function
        * 
        * @param player takes player so it can use the makeMove function
        * @param game uses itself so other classes running functions in nimgame may use nimgame as a parameter
        * @param mode used to check difficulty for computer
        * @param computer  a computer to play against
        * @param playbyplay used to write actions made on turns into a txt file
        * @param p1 corresponding Participant object for Player 1
        * @param p1Name corresponding ParticipantProfile object for Player 1, holds name
        * @param p1Account corresponding Account object for Player 1, holds stats for profile chosen
        * @param p2 corresponding Participant object for Player 1
        * @param p2Name corresponding ParticipantProfile object for Player 1, holds name
        * @param p2Account corresponding Account object for Player 1, holds stats for profile chosen
        */
        void runGame(Player &player, NimGame &game, Computer::Mode &mode, Computer &computer, PlayByPlay &playbyplay, 
            Participant &p1, Participant::ParticipantProfile &p1Name, Participant::Account &p1Account,
            Participant &p2, Participant::ParticipantProfile &p2Name, Participant::Account &p2Account);

        /**
        * @brief 
        * A getter for marbles
        * 
        * @return amount of marbles
        */
        int getMarbles();

        /**
        * @brief 
        * A getter for currentTurn
        * 
        * @return currentTurn
        */
        int getCurrentTurn();

        /**
        * @brief 
        * A getter for playAgainstPlayer2, returns playAgainstPlayer2
        * 
        * @return playAgainstPlayer2
        */
        int getIfPlayer2();


};


#endif 