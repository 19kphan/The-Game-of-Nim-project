#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

#include "Participant.h"

/* Participant functions */

Participant::Participant(){

}

void Participant::createDataFile(){
    fstream statsFile;
    statsFile.open("UserData.txt");

    if(!(statsFile.is_open())){
        cout << "User data file not found. Creating file. . .\n";

        statsFile.open("UserData.txt" ,  fstream::in | fstream::out | fstream::trunc);
        statsFile << "Guest1\t0\t0\t0\t0\n";
        statsFile << "Guest2\t0\t0\t0\t0";

        statsFile.close();

        cout << "File created!\n";
    }
}

void Participant::displayAllNames(){
    ifstream statsFile;
    statsFile.open("UserData.txt");

    string line;
    const int maxNamesInLine = 8;
    const int numSpaces = 4;
    int coutNewLineBuffer = 0;

    string dName;
    string dPlayed, dWon, dVsP, dVsC;

    while(statsFile >> dName >> dPlayed >> dWon >> dVsP >> dVsC){
        cout << left << "\t" << "[" << setw(numSpaces) << dName
        << setw(numSpaces) << "]";
        coutNewLineBuffer += 1;
        if(coutNewLineBuffer == maxNamesInLine){
            cout << "\n";
            coutNewLineBuffer = 0;
        }
    }

    cout << "\n";

    statsFile.close();
}

void Participant::chooseProfile( Participant& participant, Participant::ParticipantProfile& pName, Participant::Account& pAccount){
    string chooseName;
    cout << "*CHOOSE PROFILE*\n";
    participant.displayAllNames();
    cout << "Choose an existing profile name without spaces. Press 'Enter' to confirm: ";
    cin >> chooseName;

    if( pName.verifyName(chooseName) == false ){
        while( pName.verifyName(chooseName) == false ){
            cout << "Profile name not found.\n Please Type an existing name. Press 'Enter' to confirm: ";
            cin >> chooseName;
        }
    }

    // Valid existing profile name entered.
    pName.setName(chooseName);
    pName.setNameAtLine();
    pAccount.setDataLine(pName.getNameAtLine());
    pAccount.fetchAccountDataFile();

}

void Participant::createNewProfile( Participant& participant, Participant::ParticipantProfile& pName, Participant::Account& pAccount){
    cout << "*NEW PROFILE*\n";
    string choiceName;
    participant.displayAllNames();

    cout << "Enter profile name without spaces. Press 'Enter' to confirm: ";
    cin >> choiceName;

    if( (pName.verifyName(choiceName)) ){
        while( (pName.verifyName(choiceName)) ){
            cout << "Profile with this name already exists.\nPlease enter a different name. Press 'Enter' to confirm: ";
            cin >> choiceName;
        }
    }

    // Valid new profile name entered
    pName.addNewProfileToFile(choiceName);
    pName.setName(choiceName);
    pName.setNameAtLine();
    pAccount.setDataLine(pName.getNameAtLine());
}

void Participant::choosePlayerProfileMenu( int playerNum, Participant& p, Participant::ParticipantProfile& pName, Participant::Account& pAccount){
    char choice;
    bool runMenu = true;

    cout << "[ PLAYER " << playerNum << "]\n 0: Play as Guest\n 1: Choose profile\n 2: Make and use new profile\n";

    while(runMenu){
        cin >> choice;
        if( choice == '0' || choice == '1' || choice == '2' ){
            runMenu = false;
        }else{
            cout << "Invalid input.\n0: Play as Guest\n 1: Choose profile\n 2: Make and use new profile\n";
        }
    }

    if(choice == '0'){
        cout << "*PLAY AS GUEST*\n";

        if(playerNum == 1){
            // Player 1 choosing Guest profile
            pName.setName("Guest1");
        }else{
            // Player 2 choosing Guest profile
            pName.setName("Guest2");
        }
        pName.setNameAtLine();
        pAccount.setDataLine( pName.getNameAtLine() );
        pAccount.fetchAccountDataFile();

        cout << "[ PLAYER " << playerNum << "] is " << pName.getName() << "\n";
        return;
    }
    if(choice == '1'){
        // Player is choosing an existing profile
        p.chooseProfile(p, pName, pAccount);
        cout << "[ PLAYER " << playerNum << "] is " << pName.getName() << "\n";
        return;
    }
    if(choice == '2'){
        // Player is creating a new profile and using it
        p.createNewProfile(p, pName, pAccount);
        cout << "[ PLAYER " << playerNum << "] is " << pName.getName() << "\n";
        return;
    }
}

void Participant::viewProfileStatsMenu( Participant& participant, Participant::ParticipantProfile& pName, Participant::Account& pAccount){
    string choiceName;

    cout << "--PROFILES AND STATS--\n";
    participant.displayAllNames();

    cout << "Choose a profile to view it's stats. Press 'Enter' to confirm: ";
    cin >> choiceName;

    if(pName.verifyName(choiceName) == 0){
        while(pName.verifyName(choiceName) == 0){
            cout << "Profile name not found.\n Please Type an existing name. Press 'Enter' to confirm: ";
            cin >> choiceName;
        }
    }

    pAccount.showAnyStat( pName.findNameAtLine(choiceName));
}


/* ParticipantProfile functions */

Participant::ParticipantProfile::ParticipantProfile(){
    name = "";
    nameAtLine = -1;
}

void Participant::ParticipantProfile::setName(const string& pName){
    this->name = pName;
}

string Participant::ParticipantProfile::getName(){
    return this->name;
}

bool Participant::ParticipantProfile::verifyName(const string& pName){
    ifstream statsFile;
    statsFile.open("UserData.txt");
    
    string line;
    bool nameFound = false;

    while(getline(statsFile, line) && nameFound == false){
        // name found
        if(line.find(pName) != -1){
            return nameFound = true;
        }
    }
    statsFile.close();
    return nameFound = false;
}

int Participant::ParticipantProfile::findNameAtLine(const string& pName){
    ifstream statsFile;
    statsFile.open("UserData.txt");
    
    string line;
    bool nameFound = false;

    int foundLine = 0;

    while(getline(statsFile, line) && nameFound == false){
        if(line.find(pName) != -1){
            return foundLine;
        }
        foundLine += 1;
    }

    statsFile.close();
    return foundLine = -1;
}

void Participant::ParticipantProfile::setNameAtLine(){
    this->nameAtLine = findNameAtLine(this->name);
}

int Participant::ParticipantProfile::getNameAtLine(){
    return nameAtLine;
}

void Participant::ParticipantProfile::addNewProfileToFile(const string& pName){
    ofstream statsFile;
    statsFile.open("UserData.txt", std::ios_base::app);

    if(!(statsFile.is_open())){
        cout << "Cannot find user data. Missing UserData.txt.";
        return;
    }else{

        statsFile << "\n" << pName; 
        statsFile << "\t0\t0\t0\t0";
        cout << "Profile added!\n";
    }

    statsFile.close();
}


/* Account functions */
Participant::Account::Account(){
    dataLine = -1;
    gamesPlayed = 0;
    gamesWon = 0;
    winVsPlayer = 0;
    winVsCPU = 0;    
}


void Participant::Account::setDataLine(int foundAtLine){
    dataLine = foundAtLine;
}


void Participant::Account::fetchAccountDataFile(){
    ifstream statsFile;
    statsFile.open("UserData.txt");

    string dummyName;
    string gPlayed, gWon, wVsP, wVsC;

    if(this->dataLine > -1){
        int lineMarker = this->dataLine;
        string line;
        for(int i = 0; i <= lineMarker; i++){
            statsFile >> dummyName >> gPlayed >> gWon >> wVsP >> wVsC;
        }

        this->gamesPlayed = stoi(gPlayed);
        this->gamesWon = stoi(gWon);
        this->winVsPlayer = stoi(wVsP);
        this->winVsCPU = stoi(wVsC);

    }else{
        cout << "Could not fetch data for this user. Name not found.";
    }

    statsFile.close();
}

void Participant::Account::addGamesPlayed(){
    gamesPlayed += 1;
}

void Participant::Account::addWinVsPlayer(){
    gamesWon += 1;
    winVsPlayer += 1;
}

void Participant::Account::addWinVsCPU(){
    gamesWon += 1;
    winVsCPU += 1;
}

void Participant::Account::updateAccount( Participant::ParticipantProfile& pName ){
    ifstream statsFile;
    statsFile.open("UserData.txt");

    if( !(statsFile.is_open()) ){
        cout << "Error processing UserData.txt.\n";
        cout << "Cannot find user data. Missing UserData.txt or file is empty.\n";
        return;
    }else{
        // Copying contents of UserData.txt
        vector<string> fileLines;
        string line;
        string updated;
        updated = pName.getName() + "\t" + to_string(this->gamesPlayed) + "\t" + to_string(this->gamesWon)
            + "\t" + to_string(this->winVsPlayer) + "\t" + to_string(this->winVsCPU);

        while(getline(statsFile, line)){
            fileLines.push_back(line);
        }
        statsFile.close();

        // Updating; rewriting UserData.txt
        ofstream writeStats;
        writeStats.open("UserData.txt");

        if( !(writeStats.is_open()) ){
            cout << "Error writing to UserData.txt\n";
            cout << "Cannot find user data. Missing UserData.txt or file is empty.\n";
            return;
        }else{
            fileLines[this->dataLine] = updated;
            for(int i = 0; i < fileLines.size(); i++){
                writeStats << fileLines[i] << "\n";
            }
            statsFile.close();
        }
    }
}


void Participant::Account::showAnyStat(const int& nameLine){

    ifstream statsFile;
    statsFile.open("UserData.txt");
    
    double pctWon, pctWvP, pctWvC;
    string dName, dPlayed, dWon, dWvP, dWvC;

    const int spaces1 = 4;

    for(int i = 0; i <= nameLine; i++){
        statsFile >> dName >> dPlayed >> dWon >> dWvP >> dWvC;
    }

    statsFile.close();

    // Calculation relies on games played and games won
    if( stoi(dPlayed) == 0 || stoi(dWon) == 0 ){
        // if games played = 0 and games won = 0, display 0 for all stats
        if( (stoi(dPlayed) == 0 && stoi(dWon) == 0) || stoi(dPlayed) == 0 ){
            cout << left << "Name: " << dName << "\n";
            cout << left << "Games Played:" << "\t" << setw(spaces1) << "0" << "\n";
            cout << left << "Games Won:" << "\t" << setw(spaces1) << "0" << setw(spaces1) 
                << "--" << setw(spaces1) << "0" << "%\n";
            cout << left << "Vs. Player:" << "\t" << setw(spaces1) << "0" << setw(spaces1) 
                << "--" << setw(spaces1) << "0" << "%\n";
            cout << left << "Vs. CPU:" << "\t" << setw(spaces1) << "0" << setw(spaces1) 
                << "--" << setw(spaces1) << "0" << "%\n";
        }
        else if( stoi(dWon) == 0 ){
            // if games won = 0, display 0 for all stats except games played
            cout << left << "Name: " << dName << "\n";
            cout << left << "Games Played:" << "\t" << setw(spaces1) << dPlayed << "\n";
            cout << left << "Games Won:" << "\t" << setw(spaces1) << "0" << setw(spaces1) 
                << "--" << setw(spaces1) << "0" << "%\n";
            cout << left << "Vs. Player:" << "\t" << setw(spaces1) << "0" << setw(spaces1) 
                << "--" << setw(spaces1) << "0" << "%\n";
            cout << left << "Vs. CPU:" << "\t" << setw(spaces1) << "0" << setw(spaces1) 
                << "--" << setw(spaces1) << "0" << "%\n";
        }
    }else{
        // otherwise, games won and games played have values
        pctWon = ( stod(dWon) / stod(dPlayed) ) * 100.0;
        pctWvP = ( stod(dWvP) / stod(dWon) ) * 100.0;
        pctWvC = ( stod(dWvC) / stod(dWon) ) * 100.0;

        cout << left << "Name: " << dName << "\n";
        cout << left << "Games Played:" << "\t" << setw(spaces1) << dPlayed << "\n";
        cout << left << "Games Won:" << "\t" << setw(spaces1) << dWon << setw(spaces1) 
            << "--" << setw(spaces1) << pctWon << "%\n";
        cout << left << "Vs. Player:" << "\t" << setw(spaces1) << dWvP << setw(spaces1) 
            << "--" << setw(spaces1) << pctWvP << "%\n";
        cout << left << "Vs. CPU:" << "\t" << setw(spaces1) << dWvC << setw(spaces1) 
            << "--" << setw(spaces1) << pctWvC << "%\n";
    }

}