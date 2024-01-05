#include "Computer.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <string>
#include "Nimgame.h"
#include "Participant.h"

using namespace std;

/* Computer functions */

int Computer::Mode::getDifficulty(){
    return difficulty;
}

void Computer::Mode::setDifficulty(int set){
    difficulty = set;
}

int Computer::computerNormal(NimGame &game, Participant::Account &p1Account){
    int marble = game.getMarbles();
    if(marble == 1){
        marble -= 1;
        Removing = 1;
        cout << "The computer removed the last marble. Remaining marbles: " << marble << endl;
        cout << "Player1 wins!!!" << endl;
        p1Account.addWinVsCPU();
        return marble;
    }
    else if(marble == 0){
        return marble;
    }  
    else{            
        srand(time(NULL));
        int amount1;
        amount1 = (rand() % (marble/2) + 1);
        marble = marble - amount1;
        Removing = amount1;
        cout << "The computer removed " << amount1 << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;
        return marble;
    } 
}

int Computer::computerAdvanced(NimGame &game, Participant::Account &p1Account){
    int marble = game.getMarbles();
    if(marble == 3 || marble == 7 || marble == 15 || marble == 31 || marble == 63 || marble == 127 || marble == 255 || marble == 511){
        int n;
        srand(time(NULL));
        n = (rand()% marble/2 +1);
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;  
    }
    else if(marble == 1){
        marble -= 1;
        Removing = 1;
        cout << "The computer removed the last marble. Remaining marbles: " << marble << endl;
        cout << "Player1 wins!!!" << endl;
        p1Account.addWinVsCPU();
        return marble;
    }
    else if(marble == 0){
        return marble;
    }
    else if(marble > 511){
        int n = marble - 511;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 255) & (marble < 511)){
        int n = marble - 255;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 125) & (marble < 255)){
        int n = marble - 125;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 63) & (marble < 125)){
        int n = marble - 63;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 31) & (marble < 63)){
        int n = marble - 31;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 15) & (marble < 31)){
        int n = marble - 15;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 7) & (marble < 15)){
        int n = marble - 7;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if((marble > 3) & (marble < 7)){
        int n = marble - 3;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
    else if(marble == 2){
        int n = 1;
        marble = marble - n;
        Removing = n;
        cout << "The computer removed " << n << " from the pile!" << endl;
        cout << "The pile is now: " << marble << endl;   
        return marble;
    }
}

int Computer::getRemoving(){
    return Removing;
}
