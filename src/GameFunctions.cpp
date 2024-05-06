/**
 * @file GameFunctions.cpp
 * @author Milan Fusco
 * @brief Source file for the GameFunctions module.
 * @details Contains functions for managing the gameplay of Blackjack.
 *         Includes functions for initializing the game, dealing cards, checking for Blackjack, 
 *         prompting the player to hit or stand, determining the winner, and collecting cards.
 * @note Uses the Shoe, Hand, and GameStats structs to manage the game state and statistics.
 */
#include <chrono>
#include <thread>
#include <iostream>
#include <limits>
#include "GameFunctions.h"
#include "constants.h"


//* ======== HELPER FUNCTIONS======== *//
/**
 * @brief Checks if the hand is a bust
 * @details Determines if the score of the hand exceeds 21, indicating a bust.
 * @param hand is the hand to be evaluated.
 * @return true if the hand is a bust
 * @return false if the hand is not a bust
 */
bool isBusted(const Hand &hand) {
    return hand.evaluateHandScore() > BLACKJACK;
}

/**
 * @brief Checks if the hand is a Blackjack
 * @details Determines if the hand has exactly two cards and a score of 21, indicating a Blackjack.
 * @param hand is the hand to be evaluated.
 * @return true if the hand is a Blackjack
 * @return false if the hand is not a Blackjack
 */
bool isBlackjack(const Hand &hand) {
    return hand.numCards == 2 && hand.evaluateHandScore() == BLACKJACK;
}

/**
 * @brief Compares the hands of a player and a dealer and updates the game statistics accordingly.
 * @details Determines the winner of the round based on the scores of the player and dealer hands.
 * @param playerHand The hand of the player.
 * @param dealerHand The hand of the dealer.
 * @param stats The game statistics to be updated.
 * @param playerIndex The index of the player in the game.
 */
void compareHands(const Hand &playerHand, const Hand &dealerHand, GameStats &stats, int playerIndex) {
    int playerScore = playerHand.evaluateHandScore();  ///> evaluate the score of the player hand and store it in a variable

    int dealerScore = dealerHand.evaluateHandScore();                           ///> evaluate the score of the dealer hand and store it in a variable
    if (isBusted(playerHand)) {                                                 ///> If the player busts, the dealer wins
        stats.playerLosses[playerIndex]++;                                      ///> 	Increment the player's loss count
        std::cout << playerHand.owner << " busted!" << std::endl;                    ///> 	Print a message indicating the player busted
    } else if (isBlackjack(playerHand) && !isBlackjack(dealerHand)) {           /// If the player has a Blackjack and the dealer does not, the player wins
        stats.playerWins[playerIndex]++;                                        ///> 	Increment the player's win count
        stats.playerBlackjacks[playerIndex]++;                                  ///> 	Increment the player's Blackjack count
        std::cout << playerHand.owner << " wins with a Blackjack!" << std::endl;     ///> 	Print a message indicating the player won with a Blackjack
    } else if (dealerScore > playerScore && !isBusted(dealerHand)) {            /// If the dealer wins, the player loses
        stats.playerLosses[playerIndex]++;                                      ///> 	Increment the player's loss count
        stats.dealerWins++;                                                     ///> 	Increment the dealer's win count
        std::cout << playerHand.owner << " loses against the dealer." << std::endl;  ///> 	Print a message indicating the player lost
    } else if (playerScore > dealerScore) {                                     /// If the player wins, the dealer loses
        stats.playerWins[playerIndex]++;                                        ///> 	Increment the player's win count
        std::cout << playerHand.owner << " wins against the dealer!" << std::endl;   ///> 	Print a message indicating the player won
    } else if (playerScore == dealerScore) {                                    /// If the player ties with the dealer, the round is a push
        stats.playerTies[playerIndex]++;                                        ///> 	Increment the player's tie count
        std::cout << playerHand.owner << " ties with the dealer." << std::endl;      ///> 	Print a message indicating the player tied
    }
}

/**
 * @brief Checks for Blackjack (score of 21) for each player and the dealer.
 * @details Evaluates each hand at the start of the round for a Blackjack.
 * @param stats Reference to the GameStats object for updating statistics.
 * @return True if any Blackjack is found; False otherwise.
 */
bool shouldEndRoundEarly(const GameStats &stats) {
    if (stats.dealerBlackjack) {                                 // Check if the dealer has Blackjack
        for (bool playerHasBlackjack : stats.playerBlackjack) {  // Check if any player also has Blackjack
            if (playerHasBlackjack) {                            // If any player has Blackjack, don't end the round early
                return false;
            }
        }
        return true;  // If the dealer has Blackjack and no player does, end the round early
    }
    return false;  // If the dealer doesn't have Blackjack, don't end the round early
}

//* ======== GAME FUNCTIONS======= *//

/**
 * @brief Get the Player Count object (1-3)
 * @details Prompts the user to enter the number of players in the game.
 * @return int
 */
int getPlayerCount() {
    int numPlayers;
    while (true) {
        std::cout << "Welcome to Blackjack! How many players are there? (1-" << MAX_PLAYER_COUNT << "): ";
        if (!(std::cin >> numPlayers) || numPlayers < 1 || numPlayers > MAX_PLAYER_COUNT) {                   ///> Get the number of players from the user
            std::cin.clear();                                                                                 ///> Clear the input stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                               ///> Ignore the rest of the input
            std::cout << "Invalid input. Please enter a number between 1 and " << MAX_PLAYER_COUNT << ".\n";  ///> Print an error message
        } else {                                                                                              ///> If the input is valid,
            return numPlayers;                                                                                ///> Return the number of players
        }
    }
}

/**
 * @brief Adds a card from the shoe to a given hand.
 *
 * Draws a card from the top of the shoe and adds it to the hand.
 * Used during the dealing phase and when a player hits.
 */
Hand drawFromShoe(Hand &hand, Shoe &deck) {
    Card drawnCard = deck.drawCardFromShoe();            ///> Draw a card from the deck
    if (drawnCard.rank != "" && drawnCard.suit != "") {  ///> If the card is not empty
        hand.addCardToHand(drawnCard);                   ///> Add the card to the hand
    } else {                                             ///> If there are no cards left to draw, print an error message
        std::cout << "ERROR: No more cards to deal." << std::endl;
    }
    return hand;
}

/**
 * @brief Initializes hands for each player and the dealer.
 *
 * Creates a separate hand for each player and the dealer, setting up for the game start.
 */
std::vector<Hand> initializeGameHands(int numPlayers) {
   std::vector<Hand> hands;                                       ///> Vector to store hands for all players and the dealer
    for (int i = 0; i < numPlayers; i++) {                    ///> Create hands for all players
        hands.push_back(Hand("Player " + std::to_string(i + 1)));  ///> Add a hand for each player
    }
    hands.push_back(Hand("Dealer"));  ///> Create a hand for the dealer

    return hands;
}

/**
 * @brief Deals cards to players and the dealer at the round start.
 *
 * Distributes two cards to each hand, ensuring a fair start for the round.
 */
void dealCards(std::vector<Hand> &hands, Shoe &deck) {
    for (int round = 0; round < STARTING_CARDS; round++) {                      ///>Deal one card at a time to each hand
        for (Hand &hand : hands) {                                              ///> Loop through each hand
            drawFromShoe(hand, deck);                                           ///> Deal one card to each hand
            std::cout << hand.owner << " was dealt a card."                     ///> Print a message indicating a card was dealt
                      << "(Cards in hand: " << (hand.numCards) << ")" << std::endl;  ///> Print the number of cards in the hand
            std::this_thread::sleep_for(std::chrono::milliseconds(500));        ///> 500 ms pause
        }
    }
    std::cout << "Initial deal completed." << std::endl;  ///> Announce that the initial deal is complete, without revealing hands
}

/**
 * @brief Displays all hands, with an option to reveal the dealer's hole card.
 *
 * Shows each player's and the dealer's hand, aiding in tracking game progress.
 */
void printHands(const std::vector<Hand> &hands, bool revealDealerHoleCard) {
    std::cout << "\n**** HAND REVEAL ****" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));  ///> Add a 2-second suspense pause before revealing hands
    for (const auto &hand : hands) {                       ///> Print each player's and the dealer's hand
        if (hand.owner == "Dealer") {                      ///> If the hand belongs to the dealer
            if (revealDealerHoleCard) {                    ///> Check if the flag to reveal the dealer's hole card is set
                hand.printHand();                          ///> Print the dealer's hand with all cards
            } else {                                       ///> Otherwise, only show the dealer's up card
                std::cout << "Dealer's hand: ?? " << hand.card[1].rank + hand.card[1].suit;
                std::cout << " (Score: XX)\n";
            }
        } else {
            hand.printHand();  ///> Print the player's hand
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  ///> 1000 ms pause between hands
    }
}

/**
 * @brief Checks for Blackjack in all hands at the round's start.
 *
 * Identifies Blackjacks and updates stats, potentially ending the round early.
 */
void checkBlackjack(const std::vector<Hand> &hands, GameStats &stats, int numPlayers) {
    stats.dealerBlackjack = isBlackjack(hands.back());                 ///> Check the dealer's hand for Blackjack
    if (stats.dealerBlackjack) {                                       ///> If the dealer has Blackjack
        bool anyPlayerHasBlackjack = false;                            ///> Flag to track if any player has Blackjack
        for (size_t i = 0; i < hands.size() - 1; ++i) {                ///> Check each player's hand for Blackjack
            if ((stats.playerBlackjack[i] = isBlackjack(hands[i]))) {  ///> If the player has Blackjack
                anyPlayerHasBlackjack = true;                          ///> Set the flag to true
                stats.playerTies[i]++;                                 ///> If both dealer and player have Blackjack, it's a tie
            } else {                                                   ///> If only the dealer has Blackjack, players lose
                stats.playerLosses[i]++;
            }
        }
        if (!anyPlayerHasBlackjack) {
            stats.dealerWins++;  ///> If only dealer has Blackjack, it's a win for the dealer
        }
    } else {
        for (size_t i = 0; i < hands.size() - 1; ++i) {        ///> Check each player's hand for Blackjack
            stats.playerBlackjack[i] = isBlackjack(hands[i]);  ///> If the player has Blackjack, set the flag to true
        }
    }
}

std::string getUserDecision(const Hand &playerHand) {
    std::string decision;  ///> string to store the player's decision
    while (true) {    ///> Loop until the player enters a valid decision
        std::cout << playerHand.owner << ": Would you like to hit or stand? ";
        std::cin >> decision;
        for (size_t i = 0; i < decision.size(); ++i) {
            decision[i] = std::tolower(decision[i]);
        }
        if (decision == "hit" || decision == "stand") {
            break;
        } else {
            std::cout << "Invalid input. Please enter 'hit' or 'stand'.\n";
            std::cin.clear();                                                    // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard the input
        }
    }
    return decision;
}

/**
 * @brief Allows a player to hit (draw a card) or stand (end turn).
 *
 * Interactively manages player decisions, updating hands as required.
 */
bool hitOrStand(Hand &playerHand, const Hand &dealerHand, Shoe &deck) {
    while (true) {
        playerHand.printHand();                                                                               ///> Print the player's hand to the console
        std::cout << "Dealer's up card: " << dealerHand.card[1].rank + dealerHand.card[1].suit << std::endl;  ///> Print the dealer's up card
        std::string decision = getUserDecision(playerHand);                                                        ///> Get the player's decision from the getUserDecision function
        if (decision == "hit") {                                                                              ///> If the player chooses to hit,
            playerHand.addCardToHand(deck.drawCardFromShoe());                                                ///> Draw a card from the deck and add it to the player's hand
            if (playerHand.evaluateHandScore() > BLACKJACK) {                                                 ///> If the player busts,
                playerHand.printHand();                                                                       ///> Print the player's hand
                std::cout << "You busted! Better luck next time!" << std::endl;                                    ///> Print a message indicating the player busted
                return false;                                                                                 ///> Return false to end the player's turn
            }
        } else if (decision == "stand") {  ///> If the player chooses to stand,
            return false;                  ///> Return false to end the player's turn
        } else {                           ///> If the player enters an invalid decision, print an error message
            std::cout << "Invalid input. Please enter 'hit' or 'stand'." << std::endl;
        }
    }
}

//* =========== GAME LOGIC ===========*//

/**
 * @brief Determines the winner of the round.
 *
 * Compares hand scores and updates stats, concluding the round.
 */
int determineWinner(std::vector<Hand> &hands, GameStats &stats, int numPlayers) {
    auto &dealerHand = hands.back();                             ///> Reference to the dealer's hand
    bool dealerBusted = isBusted(dealerHand);                    ///> Flag to track if the dealer busted
    if (isBlackjack(dealerHand)) {                               ///> Check for Blackjacks and update stats
        stats.dealerBlackjacks++;                                ///> Increment the dealer's Blackjack count
        bool allPlayersNoBlackjack = true;                       ///> Check if all players have no Blackjack
        for (bool playerHasBlackjack : stats.playerBlackjack) {  ///> Check if any player has Blackjack
            if (playerHasBlackjack) {                            ///> If any player has Blackjack,
                allPlayersNoBlackjack = false;                   ///> 	Set the flag to false
                break;                                           ///> 	Break out of the loop
            }
        }
        if (allPlayersNoBlackjack && !dealerBusted) {  ///> If the dealer has Blackjack and no player has Blackjack, the dealer wins
            stats.dealerWins++;                        ///> Increment the dealer's win count
        }
    }

    for (size_t i = 0; i < hands.size() - 1; ++i) {  ///> Check each player's hand for the outcome
        if (stats.playerBlackjack[i]) {              ///> If the player has Blackjack
            if (!isBlackjack(dealerHand)) {          ///> 	If the dealer does not have Blackjack, the player wins
                stats.playerWins[i]++;               ///> 		Increment the player's win count
                stats.playerBlackjacks[i]++;         ///> 		Increment the player's Blackjack count
            } else {                                 ///> If the dealer also has Blackjack,
                stats.playerTies[i]++;               ///> 	it's a tie
            }
        } else {  ///> If the player does not have Blackjack, compare the hands
            compareHands(hands[i], dealerHand, stats, i);
        }
    }

    if (dealerBusted) {                                              ///> If the dealer busted, all non-busted players win
        stats.dealerWins++;                                          ///>  Increment the dealer's win count
        for (size_t i = 0; i < hands.size() - 1; ++i) {              ///> Check each player's hand for the outcome
            if (!isBusted(hands[i]) && !stats.playerBlackjack[i]) {  ///> If the player did not bust, they win
                stats.playerWins[i]++;                               ///> 	Increment the player's win count
            }
        }
    }
    stats.totalRounds++;                 ///> Increment the total number of rounds played
    std::cout << "\nRound complete.\n";  ///> Print the round statistics
    stats.printStats(numPlayers);        ///> Print the game statistics
    return 0;                            ///> Return 0 to signal normal function completion
}

/**
 * @brief Prepares for the next round by collecting and shuffling cards.
 *
 * Resets hands and shuffles the deck, ensuring readiness for a new round.
 */
void collectCards(std::vector<Hand> &hands, Shoe &deck) {
    std::cout << "\nCollecting cards back to the shoe..." << std::endl;
    for (Hand &hand : hands) {  ///> reset the number of cards in the hand
        hand.numCards = 0;
    }
    deck.currentCard = 0;  ///> reset the current card index
    deck.shuffleDecks();   ///> shuffle the deck for the next round
}

/**
 * @brief Manages the flow of a single Blackjack round.
 *
 * Coordinates the dealing, player decisions, and outcome determination of a round.
 */
void playRound(Shoe &deck, int numPlayers, GameStats &stats) {
    std::vector<Hand> hands = initializeGameHands(numPlayers);  ///> Initialize hands for all players and the dealer
    dealCards(hands, deck);                                ///> Deal cards to all players and the dealer
    checkBlackjack(hands, stats, numPlayers);              ///> Check for Blackjack at the start of the round
    bool endRoundEarly = shouldEndRoundEarly(stats);       ///> Flag to end the round early

    ///> If the round should not end early, allow players to take their turns
    if (!endRoundEarly) {                                        ///> Players take their turns (range-based for loop for readability and simplicity)
        for (auto &hand : hands) {                               ///> Skip the turns for players with Blackjack or if it's the dealer's turn
            if (hand.owner != "Dealer" && !isBlackjack(hand)) {  ///> If the player has not busted, allow them to hit or stand
                while (hitOrStand(hand, hands.back(), deck))
                    ;
            }
        }
        ///> Dealer takes their turn
        auto &dealerHand = hands.back();
        while (dealerHand.evaluateHandScore() < DEALER_STAND) {
            dealerHand.addCardToHand(deck.drawCardFromShoe());
        }
    }
    printHands(hands, true);                    ///> Final reveal of all hands
    determineWinner(hands, stats, numPlayers);  ///> Determine the winner of the round and print the stats
    collectCards(hands, deck);                  ///> Collect all cards back to the shoe for the next round
}