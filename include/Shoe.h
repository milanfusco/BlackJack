/**
 * @file Shoe.h
 * @author Milan Fusco
 * @brief Header file for the Shoe struct.
 * @details Manages multiple decks of playing cards.
 *          Responsible for initializing, shuffling, and providing cards for gameplay.
 *          Represents the combined set of decks used in the game. (A standard casino shoe has 6 decks of cards - 312 cards)
 *          Contains methods for shuffling decks and drawing cards, ensuring randomness and fair play.
 * @note Uses a fixed-size array to store multiple decks of cards, allowing for efficient card drawing and shuffling.
 */
#ifndef SHOE_H
#define SHOE_H

#include <array> // for std::array
#include "Card.h" // for Card struct
#include "constants.h"  // Include the global constants

/**
 * @struct Shoe
 * @brief Manages multiple decks of playing cards.
 * @details Responsible for initializing, shuffling, and providing cards for gameplay.
 *          Represents the combined set of decks used in the game. (A standard casino shoe has 6 decks of cards - 312 cards)
 *          Contains methods for shuffling decks and drawing cards, ensuring randomness and fair play.
 * @note Uses a fixed-size array to store multiple decks of cards, allowing for efficient card drawing and shuffling.
 */
struct Shoe {
    Card cards[DECK_SIZE * NUMBER_OF_DECKS];  ///> Define the array for 6 standard decks of 52 cards (312 cards - standard casino shoe)
    int currentCard;                          ///> index of the current card being drawn
    Shoe();                                   ///> Constructor to initialize the shoe with 6 standard decks of 52 cards (312 cards)
    void initializeDecks();                   ///> Initialize the 6 decks of cards in the shoe
    void shuffleDecks();                      ///> Shuffle the  6 decks to randomize the card order
    Card drawCardFromShoe();                  ///> Draw the top card from the deck housed in the shoe
    void printShoe() const;                   ///> Print the deck of cards in the shoe
    static Card convertCardToSymbol(Card c);  ///> Convert suit characters to their corresponding symbols
};

#endif  // SHOE_H