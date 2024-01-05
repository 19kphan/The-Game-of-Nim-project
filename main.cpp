#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>

#include "Participant.h"
#include "Computer.h"
#include "Nimgame.h"
#include "Player.h"

using namespace std;

void startingPrompt();
int displayMenu(int &userInput);
void exit();

int main(){
    srand(time(NULL));
    startingPrompt();

    int userInput;

    while(true){
        Participant P1;
        Participant::ParticipantProfile P1Name;
        Participant::Account P1Account;

        // Generate UserData.txt if it is not found in the game's file.
        P1.createDataFile();

        displayMenu(userInput);
        if(userInput == 1){
            // Run NimGame
            Computer computer;
            Computer::Mode mode;
            NimGame nimgame;
            NimGame::PlayByPlay playbyplay;
            Player player;
            Participant P2;
            Participant::ParticipantProfile P2Name;
            Participant::Account P2Account;

            nimgame.initializeGame(computer, mode, playbyplay,
                P1, P1Name, P1Account, P2, P2Name, P2Account);
            nimgame.initializeMarbles();
            nimgame.turnOrder();
            nimgame.runGame(player, nimgame, mode, computer, playbyplay,
                P1, P1Name, P1Account, P2, P2Name, P2Account);
            
        }
        else if(userInput == 2){
            // View any profile stats with percentages calculated
            P1.viewProfileStatsMenu(P1, P1Name, P1Account);
        }
        else if(userInput == 3){   
            // Exit game
            exit();         
        }
        else{
            cout << "Invalid input." << endl;
        }
    }

}

void startingPrompt(){
    cout << "Welcome to Game of Nim!\n";
    cout << "The rules are simple. The starting pile will range from 10-1000.\n";
    cout << "A random integer will be generated to determine who goes first. If 1 is rolled, player1 will go first.";
    cout << " Otherwise, the opponent will go first.\n";
    cout << "Throughout each turn, each player must declare a size between 1 and half the current size of the pile.\n";
    cout << "The player to remove the last marble loses.\n";
    cout << "Good luck and have fun!" << endl;
}

int displayMenu(int &userInput){
    cout << "\n1) Enter '1' to start the game.\n";
    cout << "2) Enter '2' to see player stats.\n";
    cout << "3) Enter '3' to quit the game.\n Input: ";
    cin >> userInput;
    return userInput;
}

void exit(){
    int choice;
    cout << "Would you like to exit the game? Enter '1' for yes or '0' for no" << endl;
    cin >> choice;
    if(choice == 1){
        exit(0);
    }
    else{
        return;    
    }
}