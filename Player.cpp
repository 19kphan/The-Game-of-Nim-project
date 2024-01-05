#include "Player.h"

#include <iostream>
#include <string>
#include "Nimgame.h"
#include "Participant.h"

using namespace std;

/* Player functions*/

int Player::makeMove(NimGame &game, Participant::Account &p1Account, Participant::Account &p2Account){
    int marble = game.getMarbles();
    if(marble == 1){
        marble -= 1;
        // If game ends on currentTurn = 1, Player2 wins. If currentTurn = 2, Player1 wins.
        cout << "Player " << game.getCurrentTurn() << " removed the last marble. Remaining marbles: " << marble << endl;
        cout << "The opponent wins!!!" << endl;

        if( game.getIfPlayer2() == 1){
            if(game.getCurrentTurn() == 1){
                p2Account.addWinVsPlayer();
            }else{
                p1Account.addWinVsPlayer();
            }
        }

        return marble;
    }
    else if(marble == 0){
        return marble;
    }
    else{      
        int tempSize;
        int half = 2;
        int amount2;
        tempSize = marble/half;
        cout << "Please input an amount between 1 and half of the current pile size: ";
        cin >> amount2; 
        while(amount2 > tempSize || amount2 < 0){
            cout << "Invalid input. Please try again: ";
            cin >> amount2;        
        }
        removing = amount2;
        marble = marble - amount2;
        cout << "The pile is now: " << marble << endl;
        return marble;
    }
}

int Player::getRemoving(){
    return removing;
}