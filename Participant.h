#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/** @brief
* Deals with user profile assignment as well as reading and updating the user data/user profiles file.
*/
class Participant{

    public:
        /** 
        * @brief
        * An inner class of Participant. Includes functions pertaining to participant profile name and adding to the user data file.
        */
        class ParticipantProfile;

        /** 
        * @brief
        * An inner class of Participant. Includes functions pertaining to user stats and updating the user data file.
        */
        class Account;

        /** 
        * @brief
        * Participant default constructor
        */
        Participant();

        /** 
        * @brief
        *   Create user data text file if it doesn't exist; is not located in the current folder.
        */
        void createDataFile();

        /**
        * @brief 
        * Displays all the names in the user data text file. Mainly used in menus relating to choosing a profile.
        */
        void displayAllNames();

        /**
        * @brief
        * Sets the player profile information with an existing profile. Prompts user for existing profile name. Used in choosePlayerProfileMenu().
        * @param participant Corresponding Participant object
        * @param pProfile Reference to a ParticipantProfile object. Holds name related functions.
        * @param pAccount Reference to an Account object. 
        */
        void chooseProfile( Participant& participant, Participant::ParticipantProfile& pName, Participant::Account& pAccount);

        /**
        * @brief 
        * Creates a new player profile and uses it. Prompts user for new profile name. Used in choosePlayerProfileMenu().
        * @param participant Corresponding Participant object
        * @param pProfile Reference to a ParticipantProfile object. Holds name related functions.
        * @param pAccount Reference to an Account object. 
        */
        void createNewProfile( Participant& participant, Participant::ParticipantProfile& pName, Participant::Account& pAccount);


        /**
        * @brief 
        * Menu for having the player(s) choose a guest profile, another existing profile, or a new profile to store their win data. 
        * @param playerNum Indicates which player is choosing an account
        * @param p Reference to a corresponding Participant object for a player
        * @param pProfile Reference to a ParticipantProfile object. Holds name related functions.
        * @param pAccount Reference to an Account object. 
        */
        void  choosePlayerProfileMenu( int playerNum, Participant& p, Participant::ParticipantProfile& pName, Participant::Account& pAccount);

        /**
        * @brief 
        * Menu for viewing any player stats. 
        * @param participant Corresponding Participant object
        * @param pProfile Reference to a ParticipantProfile object. Holds name related functions.
        * @param pAccount Reference to an Account object. 
        */
        void viewProfileStatsMenu( Participant& participant, Participant::ParticipantProfile& pName, Participant::Account& pAccount);

};

class Participant::ParticipantProfile{
    private:
        string name;
        int nameAtLine;

    public:
        /**
        * @brief 
        * ParticipantProfile default constructor
        */
        ParticipantProfile();


        /**
        * @brief 
        * Sets ParticipantProfile name (its name member function) that will be used by Player.
        * @param pName the name to set to the profile; "name" private member.
        */
        void setName(const string& pName);

        /**
        * @brief
        * Getter for the name private member in ParticipantProfile.
        * @return name The name associated with a profile in use.
        */
        string getName();

        /**
        * @brief 
        * Traverses the user data text file; searches for user profile in the user data text file. Mainly for verifying if a specific name is already in use.
        * @param pName String, name to search for in the user data text file.
        * @return nameFound boolean value, true if the name and user profile is found. False otherwise.
        */
        bool verifyName(const string& pName); 

        /**
        * @brief 
        * Finds the line in the user data text file with a specific player name. Also sets the nameAtLine private member in ParticipantProfile.
        * @param pName the user profile name to find in the data text file.
        * @return foundLine - the line in the data text file that has a player's name. If not found, returns -1.
        */
        int findNameAtLine(const string& pName); 

        /**
        * @brief 
        * Sets the nameAtLine private member. Receives the result from the findNameAtLine function.
        */
        void setNameAtLine();

        /**
        * @brief 
        * Getter for the nameAtLine private member in ParticipantProfile.
        * @return nameAtLine the line in the user data text file where the name is found
        */
        int getNameAtLine();

        /**
        * @brief 
        * Appends the user data text file with a new profile/account.
        * @param pName the name of the profile to be added to the user data text file.
        */
        void addNewProfileToFile(const string& pName);

};

class Participant::Account{
    private:
        int dataLine; 
        int gamesPlayed;
        int gamesWon;
        int winVsPlayer;
        int winVsCPU;
    
    public:
        /**
        * @brief 
        * Account default constructor
        */
        Account();

        /**
        * @brief 
        * Sets the line at which the participant profile's name is found.Meant to interact with findNameLine function and/or the nameAtLine getter in ParticipantProfile class.
        @param foundAtLine - Line in the text file where the user's name is found. 
        */
        void setDataLine(int foundAtLine);

        /**
        * @brief 
        * Set participant profile data from the user data text file. Uses dataLine private member to locate the data.
        */
        void fetchAccountDataFile();

        /** 
        * @brief 
        * Add one point to gamesPlayed member variable
        */
        void addGamesPlayed();

        /** 
        * @brief 
        * Add one point to winVsPlayer member variable. Also adds to the gamesWon member variable
        */
        void addWinVsPlayer();

        /** 
        * @brief 
        * Add one point to winVsCPU member variable. Also adds to the gamesWon member variable
        */
        void addWinVsCPU();

        /**
        * @brief 
        * Change participant profile data in the user data text file.
        * Uses dataLine private member to locate the data.
        */
        void updateAccount( Participant::ParticipantProfile& pName );

        /**
        * @brief 
        * Shows and calculates the stats for an account within the User Data text file given the line where a name is found.Used in viewProfileStatsMenu() in the Participant class
        @param nameLine - Line in the text file where the specific account data will be found. 
        */
        void showAnyStat(const int& nameLine);

};

#endif 