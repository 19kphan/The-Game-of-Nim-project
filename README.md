# The-Game-of-Nim-project
Designing a C++ program that will implement a version of the classic Nim game, where two players take turns removing a number of marbles from a pile, and the player who takes the last marble loses.

This program encompasses various classes designed to manage game logic, player interactions, profile handling, and statistical tracking. The architecture is structured to provide a user-friendly interface, enabling players to engage in the game against either a computer or another player. This report delves into the intricacies of each class, their functionalities, and their interrelationships within the program.

# Class Descriptions and Relationships:

#### NimGame Class

Responsibility: Manages the game setup, turn order, and execution.

Relationships: Interacts with Participant and Computer classes to initialize games and determine game modes.

#### Participant Class

Responsibility: Handles player accounts, profiles, and data management.

Relationships: Utilizes Account and ParticipantProfile classes to handle profile selection, creation, and statistical updates.

#### ParticipantProfile Class

Responsibility: Manages individual player profiles and their locations within the data file.

Relationships: Nested within Participant, interacts with Account to set and retrieve profile data from the "UserData.txt" file.

#### Account Class

Responsibility: Tracks and updates player statistics such as games played, games won, and win percentages.

Relationships: Nested within Participant, fetches and updates profile statistics in the "UserData.txt" file.

#### Computer Class

Responsibility: Represents the computer player with defined difficulty levels.

Relationships: Utilizes Mode to determine difficulty level and defines move strategies based on the selected level.

#### Mode Class

Responsibility: Determines and sets the difficulty level for the computer player.

Relationships: Nested within Computer, facilitates the decision-making process for the computer's moves.

#### Player Class

Responsibility: Represents a human player and handles their move selections.

Relationships: Interacts with the game (NimGame) to input and execute human player moves.

PlayByPlay Class
Responsibility: Records and manages the play-by-play details of each game.
Relationships: Nested within NimGame, captures and logs game progress and outcomes.
