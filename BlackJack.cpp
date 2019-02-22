/*
Program name	: BlackJack.cpp
Author			: Wm. Rabe
Date created	: 12.1.2018
Original author	: Suzy Oliver (don't change this)
Description		: This program simulates one hand of a simplified version of BlackJack (or 21).
					It has 2 players: a user and the dealer/computer. It allows a user to say whether to
					Hit or Stay. The computer then tries to beat the user. The code for the user's part
					has been removed for the students to code themselves.
					This contains 3 classes: Card, Player, and Game.
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <array>
#include <ctype.h>

using namespace std;

// ENUMERATIONS
enum Rank { Ace, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
enum Suit { Clubs, Diamonds, Hearts, Spades };

// CARD CLASS

class Card
{

public:
	// CARD CONSTANTS AND STATICS
	const static int NUMBER_SUITS = 4;
	const static int NUMBER_RANKS = 13;
	const static int NUMBER_CARDS = NUMBER_SUITS * NUMBER_RANKS;

private:
	Rank rank; // of the type enum Rank
	Suit suit; // of the type enum Suit

	// prototypes
public:
	Card(Rank initRank, Suit initSuit);
	void setSuit(Suit initSuit);
	void setRank(Rank initRank);
	const Suit getSuit(void);
	const Rank getRank(void);
	const char rankChar(void);
	const char suitChar(void);
	string to_string(void);
	int rankValue(void);
	bool isAce(void);
};

// STATICS AND CONSTANTS OUTSIDE THE CLASS
// values is the point values for each of the ranks (except that Ace can be 1 or 11).
const static int values[Card::NUMBER_RANKS] = { 11 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 10, 10, 10 };
const static char ranks[Card::NUMBER_RANKS] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
const static char suits[Card::NUMBER_SUITS] = { 'C','D','H','S' };

// CARD CONSTRUCTOR
Card::Card(Rank initRank, Suit initSuit)
{
	rank = initRank;
	suit = initSuit;
}

// CARD SETTERS
void Card::setRank(Rank initRank)
{
	rank = initRank;
}

void Card::setSuit(Suit initSuit)
{
	suit = initSuit;
}

// CARD GETTERS
const Rank Card::getRank(void)
{
	return rank;
}

const Suit Card::getSuit(void)
{
	return suit;
}

const char Card::rankChar(void)
{
	// use the array called ranks with the letter of the card ranks
	return ranks[(int)rank];
}

const char Card::suitChar(void)
{
	// use the array called suits with the letter of the card suits
	return suits[(int)suit];
}

int Card::rankValue(void)
{
	return values[(int)rank];
}

bool Card::isAce(void)
{
	return rank == Ace ? true : false;
}

string Card::to_string(void)
{
	string returnString = "";
	returnString += rankChar();
	returnString += suitChar();
	return returnString;
}

class Player
{
	// CLASS ATTRIBUTES
private:
	int				playerNumber;
	vector<Card>	hand;

public:
	Player(int initPlayerNumber);
	void setPlayerNumber(int initPlayerNumber);
	int  getPlayerNumber();
	vector<Card> getHand(void);
	void addCardToHand(Card card);
	int numAcesInHand(void);
	int handValue(void);
	bool isSoftHand(void);
	void clearhand(void);
};

// PLAYER SETTERS
void Player::setPlayerNumber(int initPlayerNumber)
{
	playerNumber = initPlayerNumber;
}

// PLAYER GETTERS
int Player::getPlayerNumber(void)
{
	return playerNumber;
}

vector<Card> Player::getHand(void)
{
	return hand;
}

// PLAYER METHODS

void Player::addCardToHand(Card card)
{
	hand.push_back(card);
}

int Player::handValue(void)
{
	int returnValue = 0;
	int numAcesUnused = 0;
	for (int cardIndex = 0; cardIndex < hand.size(); cardIndex++)
	{
		returnValue += hand[cardIndex].rankValue();
		if (hand[cardIndex].isAce())
			numAcesUnused++;
	}

	// if this is over 21, adjust the value for aces in the hand
	for ( /* start numAcesUnused where it is */; numAcesUnused > 0 && returnValue > 21; numAcesUnused--)
	{
		returnValue -= 10; // use one of the aces to be 1 instead of 11, so subtract the difference which is 10.
	}

	return returnValue;
}

int Player::numAcesInHand(void)
{
	int returnValue = 0;
	for (int cardIndex = 0; cardIndex < hand.size(); cardIndex++)
	{
		if (hand[cardIndex].isAce())
			returnValue++;
	}
	return returnValue;
}

bool Player::isSoftHand(void)
{
	if (numAcesInHand() > 0)
		return true;
	return false;
}
void Player::clearhand(void){
	hand.clear();
}
// PLAYER CONSTRUCTOR
Player::Player(int initPlayerNumber)
{
	playerNumber = initPlayerNumber;
}

// REGULAR PROTOTYPES
int main(void);
ostream & operator<<(ostream &os, const Card &);
ostream & operator<<(ostream &os, vector<Card> & cards);
ostream & operator<<(ostream &os, Player & player);

// OPERATOR OVERLOADS

// << overload for Card
ostream & operator<<(ostream &os, Card & card)
{
	return cout << card.rankChar() << card.suitChar();
}

// << overload for vector<Card>
ostream & operator<<(ostream &os, vector<Card> & cards)
{
	string cardsString = "";
	for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++)
	{
		if (cardIndex > 0)
			cardsString += " ";
		cardsString += cards[cardIndex].to_string();
	}
	return cout << cardsString;
}

// << overload for Player
ostream & operator<<(ostream &os, Player & player)
{
	vector<Card> hand = player.getHand();
	string handString = "";
	for (int cardIndex = 0; cardIndex < hand.size(); cardIndex++)
	{
		if (cardIndex > 0)
			handString += " ";
		handString += hand[cardIndex].to_string();
	}
	return cout << player.getPlayerNumber() << ": " << handString << " Value: " <<
		player.handValue() << " Number aces: " << player.numAcesInHand() << endl;
}

class Game
{
	// CONSTANTS AND STATICS
public:
	const static int  NUMBER_PLAYERS = 2;

	// ATTRIBUTES
private:
	vector<Player> players;
	vector<Card> deck;

	// METHOD PROTOTYPES
public:
	Game(void);
	void generateDeck(void);
	void shuffleDeckUpToNTimes(int n);
	void shuffleDeck(void);
	void dealCard(int playerNumber);
	void printCards(vector<Card>cards, bool hideDealerHoleCard);
	void printPlayers(bool hideDealerHoleCard);
	void dealRound(void);
	void printInstructions(void);
	void handleUsersPlay(void);
	void handleDealersPlay(void);
	int  dealUserCardAndProcess(void);
	int  dealDealerCardAndProcess(void);
	void play(void);
	int countCards(void);
};

int Game::countCards(void){
	return deck.size();
}

// GAME CONSTRUCTOR
Game::Game(void)
{
	string answer;
	cout << endl << "This simulates one hand of a simple game of BlackJack with 2 players: you and the computer." << endl;
	cout << "You are player #0, and the computer is player #1." << endl;
	cout << "This program does NOT handle any kind of insurance, splitting, or doubling down." << endl;
	cout << "There is no betting or chips of any kind." << endl << endl;
	cout << "Do you want to see the rules? (y or n): ";
	cin >> answer;
	cout << endl;
	if (tolower(answer[0]) == 'y')
		printInstructions();

	generateDeck(); // loads 3 decks into the shuffle
	generateDeck();
	generateDeck();
	cout << "Three decks, " << countCards()<< " cards." << endl;
	shuffleDeckUpToNTimes(5); // shuffle 2-5 times
	//printCards(deck);

	// create the players
	for (int playerIndex = 0; playerIndex < Game::NUMBER_PLAYERS; playerIndex++)
	{
		Player player = Player(playerIndex);
		players.push_back(player);
	}
}

void Game::play(void)
{
	char answer = 'y';
	while(tolower(answer) == 'y'){ // extra credit to allow user to play more than one hand
		players[0].clearhand();
		players[1].clearhand();

		// Deal 2 cards to each player
		for (int cardNum = 0; cardNum < 2; cardNum++)
		{
			dealRound();
		}

		// show the hands as they are now
		printPlayers(true); // true means that the hole card will be hidden from the user

		// handle the users play
		handleUsersPlay();

		// handle the dealer's play
		handleDealersPlay();

		cout << "Play another hand? (y/n): ";
		cin >> answer;
		cout << endl;
	}

}	//	end play method

void Game::handleUsersPlay(void){
	char answer;
	int userHandValue = players[0].handValue();
	int dealerHandValue = players[1].handValue();
	if (userHandValue == 21 && players[0].getHand().size() == 2)
	{
		// user already won with a BlackJack
			cout << "BlackJack!! Winner winner chicken dinner!" << endl;
	} else {
		while(userHandValue < 21){
			cout << "Hit or stand? (h/s): " << endl;
			cin >> answer;
			if ((answer == 'H') || (answer == 'h')){
				userHandValue = dealUserCardAndProcess();
			} else {
				break;
			}

		}

	}
}

void Game::handleDealersPlay(void){
	char answer;

	int userHandValue = players[0].handValue();
	int dealerHandValue = players[1].handValue();

	if (userHandValue == 21 && players[0].getHand().size() == 2){
	  // user has black jack
	}	else if (userHandValue <= 21){
		printPlayers(false); // show the hole card
		if (dealerHandValue > userHandValue)
		{
			cout << "Sorry, the dealer already has more points. You lose. Better luck next time." << endl;
		}
		else if (dealerHandValue == userHandValue)
		{
			cout << "It's a Push (tie)." << endl;
		}
		else
		{
			cout << endl << "Now that it is the dealer's turn,  you can see the dealer's hole card. Enter c to continue: ";
			cin >> answer;
			cout << endl;

			// see if dealer is required to Hit
			if (dealerHandValue <= 16 || (dealerHandValue == 17 && players[1].isSoftHand()))
			{
				dealerHandValue = dealDealerCardAndProcess();
			}

			// dealer keeps drawing until he wins or goes bust or ties
			while (dealerHandValue < userHandValue)
			{
				dealerHandValue = dealDealerCardAndProcess();
			}

			if (dealerHandValue == userHandValue && dealerHandValue < 17)
			{
				// draw one more time
				dealerHandValue = dealDealerCardAndProcess();
			}

		}	// end else dealerHandValue
	}	//	end if userHandValue <= 21

}

int Game::dealDealerCardAndProcess(void){
	string answer;
	dealCard(1);
	printPlayers(false);
	cout << endl << "The dealer drew a " << players[1].getHand().back() << "." << endl;

	int userHandValue = players[0].handValue();
	int dealerHandValue = players[1].handValue();

  if (dealerHandValue > 21)
	{
		cout << "The dealer went Bust. You win! Congratulations!" << endl;
	}
	else if (dealerHandValue > userHandValue)
	{
		cout << "Sorry, the dealer has more points than you. You lose. Better luck next time." << endl;
	}
	else
	{
		cout << endl << "Enter c to continue: ";
		cin >> answer;
		cout << endl;
	}
	return dealerHandValue;
}

int Game::dealUserCardAndProcess(void){
	dealCard(0);
	printPlayers(true);
	cout << endl << "You were dealt a " << players[0].getHand().back() << "." << endl;

	int userHandValue = players[0].handValue();
	int dealerHandValue = players[1].handValue();
	if(userHandValue == 21){
	  cout << "You now have 21 points! Now it's the Dealer's turn!" << endl;
	}

	else if (userHandValue > 21)
	{
		cout << "You went Bust! Better luck next time." << endl;
	}

	return userHandValue;

}

void Game::generateDeck(void){
	int cardCount = 0;

	for (int suitIndex = 0; suitIndex < Card::NUMBER_SUITS; suitIndex++)
	{
		for (int rankIndex = 0; rankIndex < Card::NUMBER_RANKS; rankIndex++, cardCount++)
		{
			Card card = Card((Rank)rankIndex, (Suit)suitIndex);
			deck.push_back(card);
		}
	}
}

void Game::shuffleDeck(void){
	int randomNumber = -1;
	vector<Card> newCards;

	/* initialize random seed: */
	srand(time(NULL));

	for (int deckCount = deck.size() - 1; deckCount >= 0; deckCount--)
	{
		// generate random between 0 and #cards-1
		if (deckCount == 0)
			randomNumber = 0;
		else
			randomNumber = rand() % deckCount;
		//cout << "In shuffleCards, randomNumber = " << randomNumber << ", cardsCount = " << cardsCount << ", cardsCount-randomNumber = " << cardsCount-randomNumber  << ", card = " << cards[cardsCount - randomNumber] << endl;
		newCards.push_back(deck[deckCount - randomNumber]);
		deck.erase(deck.begin()+deckCount - randomNumber);
	}
	deck = newCards;
}

// this shuffles the cards between 2 and N times
void Game::shuffleDeckUpToNTimes(int n)
{
	/* initialize random seed: */
	srand(time(NULL));

	// generate a random number between 2 and N, inclusive
	int numberShuffles = rand() % (n-1) + 2;
	for (int i = 0; i < numberShuffles; i++)
	{
		shuffleDeck();
	}
}

void Game::dealCard(int playerNumber)
{
	// we are going to treat the end of the vector as the top of the deck since there
	// are methods that get and delete the last card.
	int cardsCount = deck.size();
	if (cardsCount > 0 && players[playerNumber].handValue() < 21)
	{
		Card card = deck.back();
		// delete the card from the vector
		deck.pop_back();
		players[playerNumber].addCardToHand(card);
	}
}

void Game::dealRound(void)
{
	for (int playerIndex = 0; playerIndex < Game::NUMBER_PLAYERS; playerIndex++)
	{
		dealCard(playerIndex);
	}
}

void Game::printCards(vector<Card>cards, bool hideHoleCard)
{
	for (int cardsIndex = 0; cardsIndex < cards.size(); cardsIndex++)
	{
		if (hideHoleCard && cardsIndex == 1)
			cout << "** ";
		else
			// the following works only because we overloaded << with the Card type
			cout << cards[cardsIndex] << " ";
	}
	cout << endl;
}

void Game::printPlayers(bool hideDealerHoleCard)
{
	cout << "Players: \n";
	for (int playerIndex = 0; playerIndex < Game::NUMBER_PLAYERS; playerIndex++)
	{
		// we can print the whole hand if the parameter is false or if it's not the dealer or if the dealer has more than 2 cards
		if (! hideDealerHoleCard || playerIndex < Game::NUMBER_PLAYERS-1 || players[playerIndex].getHand().size() > 2)
			cout << players[playerIndex];
		else
		{
			// we have to hide the dealer's hole card
			cout << playerIndex << ": ";
			printCards(players[playerIndex].getHand(), hideDealerHoleCard);
		}
	}
}

void Game::printInstructions(void)
{
	cout << endl;
	cout << "The idea is to get a higher number of points than the dealer without going over 21." << endl;
	cout << "Numbered cards are worth their number value, the Ace is worth 1 or 11, and other face cards" << endl;
	cout << "are worth 10. The dealer deals a card to you and a card to himself face up. Then one to you" << endl;
	cout << "face up and one to himself face down. You decide if you want another card (hit) or not (stand)."<< endl;
	cout << "If you choose to Hit, you may continue choosing to Hit until you decide to Stand or until you" << endl;
	cout << "go Bust (over 21). If you get a BlackJack (an Ace and any card worth 10 on your first two" << endl;
	cout << "cards), you automatically win. If you stand, the dealer turns over his hidden card, and keeps" << endl;
	cout << "Hitting until he beats you or until he goes Bust. Note that if the Dealer starts with 16 or" << endl;
	cout << "less or has a soft 17 (soft means he has an Ace), he is required to Hit at least once." << endl;
	cout << "The cards are shown with rank first (A=Ace, K=King, Q=Queen, J=Jack, T=10, and the number cards)." << endl;
	cout << "Then the suit follows (S=Spades, H=Hearts, D=Diamonds, C=Clubs). So TS means 10 of Spades." << endl << endl;
}

int main(void)
{
	Game game = Game();
	game.play();

	getchar();
	getchar();
	return 0;
} // end main
