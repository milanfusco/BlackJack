/**
 * @file constants.h
 * @author Milan Fusco
 * @brief Header file for the constants used in the Blackjack game.
 * @details This file defines various constants that are used throughout the Blackjack game.
 *          These constants include the maximum player count, maximum hand size, suit count, rank count,
 *          deck size, number of decks, starting cards, reshuffle threshold, blackjack value, face card value,
 *          ace high value, ace low value, and dealer stand value.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int MAX_PLAYER_COUNT = 3;
constexpr int MAX_HAND_SIZE = 12;
constexpr int SUIT_COUNT = 4;
constexpr int RANK_COUNT = 13;
constexpr int DECK_SIZE = 52;
constexpr int NUMBER_OF_DECKS = 6;
constexpr int STARTING_CARDS = 2;
constexpr int RESHUFFLE_THRESHOLD = 75;
constexpr int BLACKJACK = 21;
constexpr int FACE_CARD_VALUE = 10;
constexpr int ACE_HIGH = 11;
constexpr int ACE_LOW = 1;
constexpr int DEALER_STAND = 17;

#endif  // CONSTANTS_H