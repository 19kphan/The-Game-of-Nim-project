#include "Nimgame.h"

#include <iostream>
#include <fstream>
#include <string>
#include "Computer.h"
#include "Player.h"
#include "Participant.h"

using namespace std;

/* Nimgame functions */

void NimGame::initializeGame(Computer &computer, Computer::Mode &mode, NimGame::PlayByPlay &playbyplay,
            Participant &p1, Participant::ParticipantProfile &p1Name, Participant::Account &p1Account,
            Participant &p2, Participant::ParticipantProfile &p2Name, Participant::Account &p2Account){

    playAgainstPlayer2 = 0;

    cout << "*STARTING GAME*\nWould you like to play against a computer or player2?\n";
    while(true){
        cout << "Input '0' to play against Computer or '1' to play against Player2: ";
            cin >> choice;
        if(choice == 0){
            // Picking profile for Player1 to use.
            p1.choosePlayerProfileMenu(1, p1, p1Name, p1Account);

            cout << "Input '0' to play in Normal mode and '1' to play in Advanced mode: ";
            cin >> choice;
            mode.setDifficulty(choice);
            int difficulty = mode.getDifficulty();
            if(difficulty == 0){
                cout << "\nThe game will be played in Normal Mode\n";
                break;
            }
            else{
                cout << "\nThe game will be played in Advanced Mode\n";
                break;
            }
        }
        else if(choice == 1){
            // Picking profiles for both Player1 and Player2
            p1.choosePlayerProfileMenu(1, p1, p1Name, p1Account);
            p2.choosePlayerProfileMenu(2, p2, p2Name, p2Account);

            playAgainstPlayer2 = 1;
            break;
        }
        else{
            cout << "Invalid Choice. Please try again." << endl;
        }
    }
    playbyplay.setNewGame();

}

void NimGame::initializeMarbles(){
    //Max pile size is actually 1000, but 0 is accounted for as well.
    int maxSize = 1001;    
    //Rand will generate an int 10-1000
    srand(time(NULL));
    marbles = (rand()%maxSize); 
    cout << "The starting pile is: "<< marbles << endl;
    
}
void NimGame::setMarbles(int amount){
    marbles = amount;
}

void NimGame::turnOrder(){
    // If turnOrder is 0, computer will go first. If 1, human will go first.
    int rng = 2;
    srand(time(NULL));
    currentTurn = rand()%rng;
    if(currentTurn == 0 && playAgainstPlayer2 == 1){
        cout << "Player2 will go out first.\n";
    }
    else if(currentTurn == 0){
        cout << "The computer will go out first.\n";
    }
    else{
        cout << "Player1 will go out first.\n";
    }  
}

int NimGame::getMarbles(){
    return marbles;
}

void NimGame::runGame(Player &player, NimGame &game, Computer::Mode &mode, Computer &computer, PlayByPlay &playbyplay, 
                Participant &p1, Participant::ParticipantProfile &p1Name, Participant::Account &p1Account,
                Participant &p2, Participant::ParticipantProfile &p2Name, Participant::Account &p2Account){
            
    playbyplay.writeToFile(game, player, computer);
    if(playAgainstPlayer2 == 1){
        p1Account.addGamesPlayed();
        p2Account.addGamesPlayed();

        while(marbles > 0){
            if(currentTurn == 1){
                // Player 2 turn
                marbles = player.makeMove(game, p1Account, p2Account);
                playbyplay.writeToFile(game, player, computer);
                currentTurn = 2;
            }
            else{
                // Player 1 turn
                marbles = player.makeMove(game, p1Account, p2Account);
                playbyplay.writeToFile(game, player, computer);
                currentTurn = 1;
            }
        }

        p1Account.updateAccount( p1Name );
        p2Account.updateAccount( p2Name );
    }

    //Normal Mode
    else if(mode.getDifficulty() == 0){
        p1Account.addGamesPlayed();

        while(marbles > 0){
            if(currentTurn != 0){
                marbles = player.makeMove(game, p1Account, p2Account);
                playbyplay.writeToFile(game, player, computer);
                marbles = computer.computerNormal(game, p1Account);
                playbyplay.writeToFile(game, player, computer);
            }
            else{
                marbles = computer.computerNormal(game, p1Account);
                playbyplay.writeToFile(game, player, computer);
                marbles = player.makeMove(game, p1Account, p2Account);
                playbyplay.writeToFile(game, player, computer);
            }
        }

        p1Account.updateAccount( p1Name );
    }
    //Advanced Mode
    else{
        p1Account.addGamesPlayed();

        while(marbles > 0){
            if(currentTurn != 0){
                marbles = player.makeMove(game, p1Account, p2Account);
                playbyplay.writeToFile(game, player, computer);
                marbles = computer.computerAdvanced(game, p1Account);
                playbyplay.writeToFile(game, player, computer);
            }
            else{
                marbles = computer.computerAdvanced(game, p1Account);
                playbyplay.writeToFile(game, player, computer);
                marbles = player.makeMove(game, p1Account, p2Account);
                playbyplay.writeToFile(game, player, computer);
            }            
        }

        p1Account.updateAccount( p1Name );
    }
}

int NimGame::getCurrentTurn(){
    return currentTurn;
}

int NimGame::getIfPlayer2(){
    return playAgainstPlayer2;
}

void NimGame::PlayByPlay::writeToFile(NimGame &game, Player &player, Computer &computer){
    ofstream file;
    file.open("PlayByPlay.txt", ios::app);

    if(newGame){
        file << "------------------------------------------------------------------------------------------" << endl;
        file << "The Starting Pile is: " << game.getMarbles() << endl;
        newGame = 0;
        flip = 0;
        lock = 1;
    }
    else if (game.getIfPlayer2() == 1){
        if(game.getMarbles() > 0){
            file << "Player " << game.getCurrentTurn() << " removed " << player.getRemoving() << " marbles." << endl;
            file << "Pile is now: " << game.getMarbles() << endl;
        }
        else{
            if(game.currentTurn == 1){
                file << "Player 1 has removed the last marble. Remaining Marbles: 0" << endl;
                file << "Player 2 Wins!!!" << endl;
            }
            else{
                file << "Player 2 has removed the last marble. Remaining Marbles: 0" << endl;
                file << "Player 1 Wins!!!" << endl;

            }
        }
    }
    else{
        if(game.getMarbles() > 0){
            if(game.getCurrentTurn() != 0){
                if(flip == 0){
                    file << "Player 1 removed " << player.getRemoving() << " marbles." << endl;
                    file << "Pile is now: " << game.getMarbles() << endl;
                    flip = 1;
                }
                else if(flip == 1){
                    file << "Computer removed "<< computer.getRemoving() << " marbles." << endl;
                    file << "Pile is now: " << game.getMarbles() << endl;
                    flip = 0;
                }
            }
            else{
                if(flip == 1){
                    file << "Player 1 removed " << player.getRemoving() << " marbles." << endl;
                    file << "Pile is now: " << game.getMarbles() << endl;
                    flip = 0;
                }
                else if(flip == 0){
                    file << "Computer removed "<< computer.getRemoving() << " marbles." << endl;
                    file << "Pile is now: " << game.getMarbles() << endl;
                    flip = 1;
                }
            }
        }
        else{
            if(game.getCurrentTurn() != 0){
                if((flip == 0)){
                    if(lock){
                        file << "Player 1 removed the last marble." << endl;
                        file << "The Computer Wins!!!"<< endl;
                        flip = 1;
                        lock = 0;
                    }
                }
                else if((flip == 1)){
                    if(lock){
                        file << "Computer removed the last marble." << endl;
                        file << "Player 1 Wins!!!" << endl;
                        flip = 0;
                        lock = 0;
                    }
                }
            }
            else{
                if((flip == 1)){
                    if(lock){
                        file << "Player 1 removed the last marble." << endl;
                        file << "The Computer Wins!!!"<< endl;
                        flip = 0;
                        lock = 0;
                    }
                }
                else if((flip == 0)){
                    if(lock){
                        file << "Computer removed the last marble." << endl;
                        file << "Player 1 Wins!!!" << endl;
                        flip = 1;
                        lock = 0;
                    }
                }
            }
        }
    }
    file.close();
}

void NimGame::PlayByPlay::setNewGame(){
    newGame = 1;
}


