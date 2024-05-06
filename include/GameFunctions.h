/**
 * @file GameFunctions.h
 * @author Milan Fusco
 * @brief Header file for the GameFunctions module.
 * @details Contains functions for managing the gameplay of Blackjack.
 *          Includes functions for initializing the game, dealing cards, checking for Blackjack, prompting the player to hit or stand, determining the winner, and collecting cards.
 */

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <vector>  // for std::vector

#include "GameStats.h"  // for GameStats struct
#include "Hand.h"       // for Hand struct
#include "Shoe.h"       // for Shoe struct

/**
 * @brief Get the player count.
 * @return The number of players in the game.
 */
int getPlayerCount();

/**
 * @brief Draw a card from the top of the deck and add it to the hand.
 * @param hand The hand to draw the card into.
 * @param deck The deck of cards to draw from.
 * @return The updated hand after drawing the card.
 */
Hand drawFromShoe(Hand &hand, Shoe &deck);

/**
 * @brief Create a vector of hands for the dealer and players.
 * @param numPlayers The number of players in the game.
 * @return A vector of hands, including the dealer's hand and the players' hands.
 */
std::vector<Hand> initializeGameHands(int numPlayers);

/**
 * @brief Deal two cards to each player and the dealer.
 * @param hands The vector of hands to deal cards to.
 * @param deck The deck of cards to deal from.
 */
void dealCards(std::vector<Hand> &hands, Shoe &deck);

/**
 * @brief Print the hands of the dealer and players.
 * @param hands The vector of hands to print.
 * @param revealDealerHoleCard Whether to reveal the dealer's hole card or not.
 */
void printHands(const std::vector<Hand> &hands, bool revealDealerHoleCard);

/**
 * @brief Check for Blackjack in the hands.
 * @param hands The vector of hands to check.
 * @param stats The game statistics to update.
 * @param numPlayers The number of players in the game.
 */
void checkBlackjack(const std::vector<Hand> &hands, GameStats &stats, int numPlayers);

/**
 * @brief Prompt the player to hit or stand.
 * @param playerHand The player's hand.
 * @param dealerHand The dealer's hand.
 * @param deck The deck of cards.
 * @return True if the player chooses to hit, false if the player chooses to stand.
 */
bool hitOrStand(Hand &playerHand, const Hand &dealerHand, Shoe &deck);

/**
 * @brief Determine the winner of the round.
 * @param hands The vector of hands.
 * @param stats The game statistics to update.
 * @param numPlayers The number of players in the game.
 * @return The index of the winning hand in the vector of hands.
 */
int determineWinner(std::vector<Hand> &hands, GameStats &stats, int numPlayers);

/**
 * @brief Collect the cards from the hands and return them to the deck.
 * @param hands The vector of hands.
 * @param deck The deck of cards.
 */
void collectCards(std::vector<Hand> &hands, Shoe &deck);

/**
 * @brief Play a round of Blackjack.
 * @param deck The deck of cards.
 * @param numPlayers The number of players in the game.
 * @param stats The game statistics to update.
 */
void playRound(Shoe &deck, int numPlayers, GameStats &stats);

#endif // GAMEFUNCTIONS_H