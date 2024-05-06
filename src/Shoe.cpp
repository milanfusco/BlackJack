/**
 * @file Shoe.cpp
 * @author Milan Fusco
 * @brief Source file for the Shoe struct.
 * @details Manages multiple decks of playing cards.
 *         Responsible for initializing, shuffling, and providing cards for gameplay.
 *        Represents the combined set of decks used in the game. (A standard casino shoe has 6 decks of cards - 312 cards)
 *       Contains methods for shuffling decks and drawing cards, ensuring randomness and fair play.
 * @note Uses a fixed-size array to store multiple decks of cards, allowing for efficient card drawing and shuffling.
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <thread>
#include "Shoe.h"


/**
 * @brief Construct a new Shoe:: Shoe object
 * @details Constructor to initialize the shoe with 6 decks of cards and shuffles the deck.
 * @param None
 * @return Shoe::Shoe object
 */
Shoe::Shoe() {
    currentCard = 0;    ///> Initialize the current card index
    initializeDecks();  ///> Initialize the 6 decks of cards in the shoe
    shuffleDecks();     ///> Shuffle the 6 decks to randomize the card order
}

/**
 * @brief Initialize the 6 decks of cards in the shoe
 * @details This function initializes the 6 decks of cards in the shoe with 52 cards each.
 * 		The cards are organized in a 4-dimensional array, where each element represents a card in a specific deck.
 * 	 	The suits are represented by characters 'C', 'D', 'H', and 'S', and the ranks are represented by strings containing the card values
 * 		(e.g., "A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2").
 */
void Shoe::initializeDecks() {
    const char suits[] = {'C', 'D', 'H', 'S'};                                                     ///> Array of suits
    const std::string cardRanks[] = {"A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"};  ///> Array of card ranks

    ///> Initialize the 6 decks of cards in the shoe
    int count = 0;                                                         ///> Loop through each deck
    for (int deck = 0; deck < NUMBER_OF_DECKS; ++deck) {                   ///> Loop through each deck
        for (int suit = 0; suit < SUIT_COUNT; ++suit) {                    ///> Loop through each suit
            for (int rank = 0; rank < RANK_COUNT; ++rank) {                ///> loop through each rank
                Card current = {cardRanks[rank], std::string(1, suits[suit])};  ///> Create a new card and add it to the shoe
                cards[count++] = convertCardToSymbol(current);             ///>convert the suit characters to their corresponding symbols
            }
        }
    }
}

/**
 * @brief Instance method to shuffle the cards in the shoe.
 * @details This function shuffles the cards in the shoe by swapping each card with a random card in a different position in the shoe.
 * 	              A 2-second pause is also added to simulate a real-world shuffling process.
 */
void Shoe::shuffleDecks() {
    for (int i = 0; i < (DECK_SIZE * NUMBER_OF_DECKS); ++i) {      ///> loop through each card in the shoe
        int randomIndex = rand() % (DECK_SIZE * NUMBER_OF_DECKS);  ///> generate a random index to swap with
        std::swap(cards[i], cards[randomIndex]);                        ///> swap the current card with the random card
    }
    std::cout << "\nShuffling the deck...\n"
              << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  ///> 2-second pause
}



/**
 * @brief Instance method to draw a single card from the shoe and return it
 * @details If the current card index is greater than the reshuffle threshold, the deck is reshuffled.
 * The reshuffle threshold prevents players from card counting by removing 75 random cards from gameplay.
 * @param None
 * @return Card
 */
Card Shoe::drawCardFromShoe() {
    if (currentCard >= DECK_SIZE * NUMBER_OF_DECKS - RESHUFFLE_THRESHOLD) {  ///> If at or beyond the Reshuffle point
        shuffleDecks();                                                      ///> Shuffle the deck and reset the current card index
        currentCard = 0;                                                     ///> Reset the current card index
        return cards[currentCard++];                                         ///> Return the next card in the deck
    }

    if (currentCard < (DECK_SIZE * NUMBER_OF_DECKS)) {                      ///> If there are still cards left to draw
        return cards[currentCard++];                                        ///> return the next card in the deck
    } else {                                                                ///> If there are no cards left to draw
        std::cout << "ERROR: No more cards to deal, reshuffling." << std::endl;  ///> Print an error message
        shuffleDecks();                                                     ///> reshuffle the deck
        currentCard = 0;                                                    ///> Reset the current card index
        return cards[currentCard++];                                        ///> Return the next card in the deck
    }
}

/**
 * @brief Instance method to print the decks of cards in the shoe.
 * @details Displays the cards in the shoe separated by commas.
 * @param None
 */
void Shoe::printShoe() const {
    for (int i = 0; i < (DECK_SIZE * NUMBER_OF_DECKS); i++) {  //> Loop through the shoe of cards
        std::cout << cards[i].rank << cards[i].suit;           ///> Print the card
        if (i != (DECK_SIZE * NUMBER_OF_DECKS) - 1)            ///> If the card is not the last card in the shoe
            std::cout << ", ";                                 ///> Print a comma to separate the cards
    }
    std::cout << std::endl;
}

/**
 * @brief Static method to converts the suit characters to their corresponding symbols (for the shoe of cards)
 * @param c
 * @return Card
 */
Card Shoe::convertCardToSymbol(Card c) {  ///> Convert the suit characters to their corresponding symbols (for the shoe of cards)
    if (c.suit == "S")
        c.suit = "♠";
    else if (c.suit == "H")
        c.suit = "♥";
    else if (c.suit == "C")
        c.suit = "♣";
    else if (c.suit == "D")
        c.suit = "♦";
    return c;
}