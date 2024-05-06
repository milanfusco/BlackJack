/**
 * @file Hand.h
 * @author Milan Fusco
 * @brief Header file for the Hand struct.
 * @details Represents a hand of cards for a player or the dealer in Blackjack.
 *          The Hand struct manages a collection of 'Card' objects to represent a hand.
 *          Provides functionality for adding cards, calculating the score, and displaying the hand.
 *          Essential for implementing game rules like hitting, standing, and scoring.
 * @note The maximum number of cards in a hand is defined by MAX_HAND_SIZE.
 * 
 */
#ifndef HAND_H
#define HAND_H

#include "Card.h" // for Card struct
#include "Shoe.h" // for Shoe struct
#include <string> // for std::string
#include <array> // for std::array

/**
 * @struct Hand
 * @brief Represents a hand of cards for a player or the dealer in Blackjack.
 * @details Manages a collection of 'Card' objects to represent a hand. Provides functionality for adding cards, calculating the score, and displaying the hand.
 *          Essential for implementing game rules like hitting, standing, and scoring.
 * @note The maximum number of cards in a hand is defined by MAX_HAND_SIZE.
 */
struct Hand {
    static const int MAX_HAND_SIZE = 11;                     ///> Maximum number of cards in a hand (A,A,A,A,2,2,2,2,3,3,3)
    std::string owner;                                       ///> name of the hand's owner (e.g., player name or "Dealer")
    int numCards = 0;                                        ///> Initalize number of cards in the hand
    Card card[MAX_HAND_SIZE];                                ///> max possible hand is A,A,A,A,2,2,2,2,3,3,3
    
    Hand();                                                  ///> Default constructor for an empty hand
    Hand(const std::string &ownerName);                      ///> Constructor to initialize a hand with a specified owner (parameters: ownerName)
    void printHand() const;                                  ///> Print the cards in the hand
    void addCardToHand(Card c);                              ///> Add a card to the hand (Parameters: card)
    std::string printCardInHand(const Card &card) const;     ///> Print a single card (Parameters: card reference);
    int adjustScoreForAces(int score, int aceCount) const;   ///> Adjust the score for Aces (Parameters: score, aceCount)
    int evaluateHandScore() const;                           ///> Calculate the score of the hand
};

#endif // HAND_H