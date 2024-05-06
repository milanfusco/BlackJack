/**
 * @file {main.cpp}
 *
 * @version 1.0
 * @brief Blackjack With Friends! (A Multiplayer Console Game) |  1-3 players
 * @mainpage Blackjack With Friends!
 * @author Milan Fusco
 * @date 7 April 2024
 * 
 * @dependencies: C++11 or later
 */

#include <iostream>

#include "GameFunctions.h"  // Include the game functions
#include "Shoe.h"
#include "GameStats.h"
using namespace std;


int main() {
    srand(time(0));                     ///> seed the random number generator, set the replay flag, and initialize the deck
    bool playAgain = true;              ///> Replay flag
    Shoe deck;                          ///> Fill the shoe with 6 decks of cards
    int numPlayers = getPlayerCount();  ///> Welcome message and prompt for number of players
    GameStats stats(numPlayers);        ///> Initialize game statistics

    ///> Main game loop
    while (playAgain) {
        playRound(deck, numPlayers, stats);                       ///> PlayRound handles the entire game flow for a single round
        std::cout << "Would you like to play again? (yes/no): ";  ///> Replay option after each round
        string answer;
        std::cin >> answer;
        playAgain = (answer == "yes" || answer == "y");
        if (playAgain) {
            std::cout << "\nStarting a new round...\n";
        }
    }
    std::cout << "Thanks for playing Blackjack! Goodbye!" << std::endl;  // Display farewell message when the game ends
    return 0;
}



