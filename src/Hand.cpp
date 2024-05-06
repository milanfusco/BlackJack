/**
 * @file Hand.cpp
 * @author Milan Fusco
 * @brief source file for the Hand struct
 * @de
 * 
 */
#include <iostream> 
#include <map>
#include "Hand.h"
#include "Card.h"
#include "constants.h"

/**
 * @brief Construct a new Hand:: Hand object
 * @details default constructor for the 'Hand' object.
 * @return Hand::Hand object
 */
Hand::Hand() : owner("Unknown"), numCards(0) {}

/**
 * @brief Construct a new Hand:: Hand object with the specified owner.
 * @details Constructor for the 'Hand' object with the specified owner and number of cards.
 * @param ownerName Name of the owner of the hand.
 * @return Hand::Hand object
 */
Hand::Hand(const std::string &ownerName) : owner(ownerName), numCards(0){}

/**
 * @brief instance method to print the hand and score of the hand.
 * @details Prints the hand and score of the hand to the console.
 */
void Hand::printHand() const {
    std::cout << "\n"
              << owner << "'s hand:";                          ///> Print the owner's name and the cards in the hand
    for (int i = 0; i < numCards; ++i) {                       ///> Loop through each card in the hand
        std::cout << " " << card[i].rank << card[i].suit;      ///> print the card rank and suit
    }
    std::cout << " (Score: " << evaluateHandScore() << ")\n";  ///> Print the score of the hand
}

/**
 * @brief instance method to add a card to the hand.
 * @param c Card to be added to the hand.
 *  */
void Hand::addCardToHand(Card c) {
    ///> Don't attempt to add past element 11 (0-11 is 12 items) and ensure the card is not empty
    if (numCards < MAX_HAND_SIZE - 1        ///> adjust for 0-based index
        && c.rank != "" && c.suit != "") {  ///> Ensure the card is not empty
        card[numCards] = c;                 ///> Add the card to the hand
        numCards++;                         ///> Increment the number of cards in the hand
    }
}

/**
 * @brief Instance method to print a single card in the hand.
 * @param card is the card to be printed.
 * @return string of the card.
 */
std::string Hand::printCardInHand(const Card &card) const {
    return card.rank + card.suit;
}

/**
 * @brief Instance method to determine the score of the hand containing an ace.
 * @param score
 * @param aceCount
 * @return int
 */
int Hand::adjustScoreForAces(int score, int aceCount) const {
    while (score > BLACKJACK && aceCount > 0) {  ///> While the score is over 21 and there are still aces in the hand
        score -= ACE_HIGH - ACE_LOW;             ///> Convert an Ace from 11 to 1
        aceCount--;                              ///> Decrement the number of aces
    }
    return score;  ///> Return the adjusted score
}

/**
 * @brief Instance method to evaluate the score of the hand.
 * @details This function calculates the score of a hand by summing up the values of each card in the hand.
 * 	It takes into account the special value of an Ace card, which can be either 1 or 11 depending on the current score.
 * @param score is the score of the hand.
 * @param aceCount is the number of aces in the hand.
 * @return int is the score of the hand.
 */
int Hand::evaluateHandScore() const {
    int score = 0;                                             ///> Initialize the score to 0
    int aceCount = 0;                                          ///> Initialize the ace count to 0
    std::map<std::string, int> cardValues = {                  ///> Map to store the values of each card rank
                                             {"A", ACE_HIGH},  ///> Ace high by default, will be adjusted if needed
                                             {"K", FACE_CARD_VALUE},
                                             {"Q", FACE_CARD_VALUE},
                                             {"J", FACE_CARD_VALUE},
                                             {"T", 10},
                                             {"9", 9},
                                             {"8", 8},
                                             {"7", 7},
                                             {"6", 6},
                                             {"5", 5},
                                             {"4", 4},
                                             {"3", 3},
                                             {"2", 2}};

    for (const auto &singleCard : card) {      ///> reference the array of cards in the hand
        score += cardValues[singleCard.rank];  ///> Add the value of the card to the score
        if (singleCard.rank == "A") {          ///> If the card is an Ace,
            aceCount++;                        ///> increment the ace count
        }
    }

    return adjustScoreForAces(score, aceCount);
}
