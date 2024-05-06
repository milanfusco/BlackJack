/**
 * @file GameStats.h
 * @author Milan Fusco
 * @brief Header file for the GameStats struct.
 * @details Manages and displays game-related statistics.
 *          Tracks and presents wins, losses, ties, and other relevant statistics for each player and the dealer.
 *          Useful for showing ongoing game progress and outcomes.
 * @note Each player's stats are stored in parallel vectors, allowing easy tracking and updating as the game progresses.
 */

#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <vector> // for std::vector

/**
 * @struct GameStats
 * @brief Manages and displays game-related statistics.
 * @details Tracks and presents wins, losses, ties, and other relevant statistics for each player and the dealer.
 *          Useful for showing ongoing game progress and outcomes.
 * @note Each player's stats are stored in parallel vectors, allowing easy tracking and updating as the game progresses.
 */
struct GameStats {
    std::vector<int> playerWins, playerLosses, playerTies, playerBlackjacks;   ///> Track wins, losses, ties, and Blackjacks for each player
    std::vector<bool> playerBlackjack;                                         ///> Track if player has Blackjack
    bool dealerBlackjack = false;                                              ///> Track if dealer has Blackjack
    int dealerWins = 0;                                                        ///> number of wins for the dealer
    int dealerBlackjacks = 0;                                                  ///> number of Blackjacks for the dealer
    int totalRounds = 0;                                                       ///> total number of rounds played (initialized to 1)
    explicit GameStats(int numPlayers);                                        ///> Constructor to initialize the game statistics
    void printStats(int numPlayers) const;                                     ///> Displays current game statistics
};

#endif // GAMESTATS_H