/**
 * @file GameStats.cpp
 * @brief Source file for the GameStats module.
 * @details Contains the implementation of the GameStats class, 
 *          which manages game statistics for Blackjack.
 * @note This file uses the GameStats struct to track player and dealer statistics.
 */

#include <iostream>
#include <iomanip>
#include "GameStats.h"

/**
 * @brief Construct a new Game Stats object
 * @details Constructor to initialize the game statistics with the number of players.
 * @param numPlayers The number of players in the game.
 */
GameStats::GameStats(int numPlayers) : playerWins(numPlayers), playerLosses(numPlayers), playerTies(numPlayers), playerBlackjacks(numPlayers), playerBlackjack(numPlayers) {}

/**
 * @brief Construct a new GameStats:: GameStats object
 * @details Constructor to initialize the GameStats object with the number of players.
 * @param numPlayers Number of players in the game.
 * @return GameStats::GameStats object
 */
void GameStats::printStats(int numPlayers) const {
    std::cout << std::fixed << std::setprecision(2);  ///> Set the precision for the output

    for (int i = 0; i < numPlayers; ++i) {
        ///> Calculate win, loss, and tie percentages using ternary operator to avoid division by zero (condition ? true : false)
        double winPercent = (totalRounds > 0) ? (static_cast<double>(playerWins[i]) / totalRounds) * 100 : 0;
        double lossPercent = (totalRounds > 0) ? (static_cast<double>(playerLosses[i]) / totalRounds) * 100 : 0;
        double tiePercent = (totalRounds > 0) ? (static_cast<double>(playerTies[i]) / totalRounds) * 100 : 0;
        ///> Print player statistics
        std::cout << "Player " << (i + 1) << " - Wins: " << playerWins[i] << " (" << winPercent << "%), "
                  << "Losses: " << playerLosses[i] << " (" << lossPercent << "%), "
                  << "Ties: " << playerTies[i] << " (" << tiePercent << "%), "
                  << "Blackjacks: " << playerBlackjacks[i] << std::endl;
    }
    ///> Calculate and print dealer statistics
    std::cout << "Dealer - Wins: " << dealerWins << " Blackjacks: " << dealerBlackjacks << std::endl;
}
