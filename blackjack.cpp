/*
import random, sys




def main():

    money = 5000
    while True:  # Main game loop.
        # Check if the player has run out of money:
        if money <= 0:
            print("You're broke!")
            print("Good thing you weren't playing with real money.")
            print('Thanks for playing!')
            sys.exit()

        # Let the player enter their bet for this round:
        print('Money:', money)
        bet = getBet(money)

        # Give the dealer and player two cards from the deck each:
        deck = getDeck()
        dealerHand = [deck.pop(), deck.pop()]
        playerHand = [deck.pop(), deck.pop()]

        # Handle player actions:
        print('Bet:', bet)
        while True:  # Keep looping until player stands or busts.
            displayHands(playerHand, dealerHand, False)
            print()

            # Check if the player has bust:
            if getHandValue(playerHand) > 21:
                break

            # Get the player's move, either H, S, or D:
            move = getMove(playerHand, money - bet)

            # Handle the player actions:
            if move == 'D':
                # Player is doubling down, they can increase their bet:
                additionalBet = getBet(min(bet, (money - bet)))
                bet += additionalBet
                print('Bet increased to {}.'.format(bet))
                print('Bet:', bet)

            if move in ('H', 'D'):
                # Hit/doubling down takes another card.
                newCard = deck.pop()
                rank, suit = newCard
                print('You drew a {} of {}.'.format(rank, suit))
                playerHand.append(newCard)

                if getHandValue(playerHand) > 21:
                    # The player has busted:
                    continue

            if move in ('S', 'D'):
                # Stand/doubling down stops the player's turn.
                break

        # Handle the dealer's actions:
        if getHandValue(playerHand) <= 21:
            while getHandValue(dealerHand) < 17:
                # The dealer hits:
                print('Dealer hits...')
                dealerHand.append(deck.pop())
                displayHands(playerHand, dealerHand, False)

                if getHandValue(dealerHand) > 21:
                    break  # The dealer has busted.
                input('Press Enter to continue...')
                print('\n\n')

        # Show the final hands:
        displayHands(playerHand, dealerHand, True)

        playerValue = getHandValue(playerHand)
        dealerValue = getHandValue(dealerHand)
        # Handle whether the player won, lost, or tied:
        if dealerValue > 21:
            print('Dealer busts! You win ${}!'.format(bet))
            money += bet
        elif (playerValue > 21) or (playerValue < dealerValue):
            print('You lost!')
            money -= bet
        elif playerValue > dealerValue:
            print('You won ${}!'.format(bet))
            money += bet
        elif playerValue == dealerValue:
            print('It\'s a tie, the bet is returned to you.')

        input('Press Enter to continue...')
        print('\n\n')



*/

// Blackjack, by Al Sweigart al@inventwithpython.com
// The classic card game also known as 21. (This version doesn't have
//     splitting or insurance.)
//     More info at : https://en.wikipedia.org/wiki/Blackjack
// This code is available at https ://nostarch.com/big-book-small-python-programming

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

// Set up the constants :
char HEARTS = 3; // Character 9829 is '♥'.
char DIAMONDS = 4; // Character 9830 is '♦'.
char CLUBS = 5; // Character 9824 is '♠'.
char SPADES = 6; // Character 9827 is '♣'.
string BACKSIDE = "backside";
// (A list of chr codes is at https://inventwithpython.com/charactermap)

int getBet(int maxBet);
vector <string> getDeck();
int getHandValue(vector <string> cards);
void displayCards(vector <string> cards);
void displayHands(vector <string> playerHand, vector <string> dealerHand, bool showDealerHand);
string getMove(vector <string> playerHand, int money) {

int main() {
    cout << "Blackjack, by Al Sweigart al@inventwithpython.com\n";
    cout << "Rules :\n";
    cout << "\tTry to get as close to 21 without going over.\n";
    cout << "\tKings, Queens, and Jacks are worth 10 points.\n";
    cout << "\tAces are worth 1 or 11 points.\n";
    cout << "\tCards 2 through 10 are worth their face value.\n";
    cout << "\t(H)it to take another card.\n";
    cout << "\t(S)tand to stop taking cards.\n";
    cout << "\tOn your first play, you can(D)ouble down to increase your bet\n";
    cout << "\tbut must hit exactly one more time before standing.\n";
    cout << "\tIn case of a tie, the bet is returned to the player.\n";
    cout << "\tThe dealer stops hitting at 17.\n";
    cout << "\t\n";
    cout << "\t\n";
        

        
    
        
        
        
        
        
        
        
   
        

    return 0;
}

int getHandValue(vector <string> cards) {
    // Returns the value of the cards. Face cards are worth 10, aces are
    // worth 11 or 1 (this function picks the most suitable ace value).
    int value = 0;
    int numberOfAces = 0;
    // Add the value for the non-ace cards:
    for (string card : cards) {
        char rank = card[0]; // card is a tuple like(rank, suit)
        if (rank == 'A') {
            numberOfAces += 1;
        } else if (rank == 'K' || rank == 'Q' || rank == 'J') { // Face cards are worth 10 points.
            value += 10;
        } else {
            value += int(rank - '0'); // Numbered cards are worth their number.
        }
    }

    // Add the value for the aces:
    value += numberOfAces; // Add 1 per ace.
    for (int i = 0; i < numberOfAces; ++i) { 
        // If another 10 can be added without busting, do so:
        if (value + 10 <= 21) {
            value += 10;
        }
    }

    return value;
}

void displayCards(vector <string> cards) {
    // Display all the cards in the cards list.
    vector<string> rows = { "", "", "", "", "" }; // The text to display on each row.
    for (string card : cards) {
        rows[0] += "  ___  "; // Print the top line of the card.
        if (card == BACKSIDE) {
            // Print a card's back:
            rows[1] += " |## | ";
            rows[2] += " |###| ";
            rows[3] += " |_##| ";
        } else {
            // Print the card's front:
            char rank = card[0], suit = card[1]; // The card is a tuple data structure.
            rows[1] = rows[1] + " |" + rank + "  | ";
            rows[2] = rows[2] + " | " + suit + " | ";
            rows[3] = rows[3] + " |__" + rank + "| ";
        }
    }

    // Print each row on the screen:
    for (auto row : rows) {
        cout << row << '\n';
    }
    cout << '\n';
}

int getBet(int maxBet) {
    // Ask the player how much they want to bet for this round.
    while (1) { // Keep asking until they enter a valid amount.
        cout << "How much do you bet? (1-" << maxBet << ", or QUIT)";
        cout << "> ";
        string bet = "";
        getline(cin, bet);
        transform(bet.begin(), bet.end(), bet.begin(), ::toupper);
        if (bet == "QUIT") {
            cout << "Thanks for playing!\n";
            exit(0);
        }
        bool flagSkip = false;
        for (char c : bet) {
            if (c < '0' || c > '9') {
                flagSkip = true;
                break;
            }
        }

        if (flagSkip) {
            continue; // If the player didn't enter a number, ask again.
        }

        int intBet = stoi(bet);
        if (1 <= intBet && intBet <= maxBet) {
            return intBet; // Player entered a valid bet.
        }
    }
}

vector <string> getDeck() {
    // Return a list of (rank, suit) tuples for all 52 cards.
    vector <string> deck(52);
    int index = 0;

    for (int i = 2; i < 11; ++i) {
        // Add the numbered cards.
        string tmpHEARTS = to_string(i) + HEARTS;
        string tmpDIAMONDS = to_string(i) + DIAMONDS;
        string tmpCLUBS = to_string(i) + CLUBS;
        string tmpSPADES = to_string(i) + SPADES;
        deck[index++] = tmpHEARTS;
        deck[index++] = tmpDIAMONDS;
        deck[index++] = tmpCLUBS;
        deck[index++] = tmpSPADES;
    }

    string rank = "J";
    for (size_t i = 0; i < 4; ++i) {
        // Add the face and ace cards.
        string tmpHEARTS = rank + HEARTS;
        string tmpDIAMONDS = rank + DIAMONDS;
        string tmpCLUBS = rank + CLUBS;
        string tmpSPADES = rank + SPADES;
        deck[index++] = tmpHEARTS;
        deck[index++] = tmpDIAMONDS;
        deck[index++] = tmpCLUBS;
        deck[index++] = tmpSPADES;
        if (i == 0) {
            rank = "Q";
        } else if (i == 1) {
            rank = "K";
        } else if (i == 2) {
            rank = "A";
        }
    }

    // Create a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister PRNG engine
    std::uniform_int_distribution<int> distribution(1, 100); // Define the range
    // Generate a random number
    int random_number = distribution(gen);
    for (int i = 0; i < random_number; ++i) {
        random_shuffle(deck.begin(), deck.end());
    }

    return deck;
}

void displayHands(vector <string> playerHand, vector <string> dealerHand, bool showDealerHand) {
    // Show the player's and dealer's cards. Hide the dealer's first
    // card if showDealerHand is False.
    cout << '\n';
    if (showDealerHand) {
        cout << "DEALER:\n";
        cout << getHandValue(dealerHand) << "\n";
        displayCards(dealerHand);
    } else {
        cout << "DEALER: ???\n";
        // Hide the dealer's first card:
        // displayCards([BACKSIDE] + dealerHand[1:]) 
    }

    // Show the player's cards:
    cout << "PLAYER:\n";
    cout << getHandValue(playerHand) << "\n";
    displayCards(playerHand);
}

string getMove(vector <string> playerHand, int money) {
    // Asks the player for their move, and returns 'H' for hit, 'S' for
    // stand, and 'D' for double down.
    while (1) { // Keep looping until the player enters a correct move.
        // Determine what moves the player can make:
        vector <string> moves = { "(H)it", "(S)tand" };
        // The player can double down on their first move, which we can
        // tell because they'll have exactly two cards:
        bool Doubledown = false;
        if (playerHand.size() == 2 && money > 0) {
            moves.push_back("(D)ouble down");
            Doubledown = true;
        }

        // Get the player's move:
        cout << "(H)it, (S)tand";
        if (Doubledown) {
            cout << ", (D)ouble down";
        }
        cout << " > ";
        string move = "";
        getline(cin, move);
        transform(move.begin(), move.end(), move.begin(), ::toupper);
        if (move == "H" || move == "S") {
            return move; // Player has entered a valid move.
        }
        if (move == "D" && Doubledown) {
            return move; // Player has entered a valid move.
        }
    }
}