/**
 * @file Card.h
 * @author Milan Fusco
 * @brief Header file for the Card struct.
 * @details Encapsulates a card's suit and rank.
 *          Used throughout the Blackjack game to represent individual cards in hands and decks.
 *          The Card hold the rank (number or face) and suit (club, diamond, heart, spade) of a playing card.
 *          The Card struct is used in the Shoe struct to represent individual cards in the deck.
 */
#ifndef CARD_H // include guard to prevent multiple inclusions of the header
#define CARD_H

#include <string> // for std::string

/**
 * @struct Card
 * @brief Represents a single playing card.
 *
 * @details Encapsulates a card's suit and rank, which are key elements in card games.
 *          Used throughout the Blackjack game to represent individual cards in hands and decks.
 */
struct Card {
    std::string rank;  ///> rank of the card (A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2)
    std::string suit;  ///> suit of the card (C, D, H, S)
};

#endif // CARD_H