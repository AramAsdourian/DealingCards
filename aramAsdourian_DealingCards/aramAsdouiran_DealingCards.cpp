//-----------------------------------------------------------------------------
// Aram Asdourian   CMPSC330   3/26/2025
//
// lets the player choose an amount of players to randomly deal cards to
// the program displays a graphic for the deck of cards and for each players hand
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
using namespace std;

//got help with maps from here: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
//i used a map so i could contain the entire deck in a single data structure
//there are 4 keys for each of the suits (Clubs, Diamonds, Spades, Hearts)
//the values for each key is a vector of the cards (Ace, 1, 2, ... King), the extra spaces are so they line up when displayed
const map<string, vector<string>> deck = 
	{ 
	{"Clubs   ", {"  Ace", "    2", "    3", "    4", "    5", "    6", "    7", "    8", "    9", "   10", " Jack", "Queen", " King"}},
	{"Diamonds", {"  Ace", "    2", "    3", "    4", "    5", "    6", "    7", "    8", "    9", "   10", " Jack", "Queen", " King"}},
	{"Spades  ", {"  Ace", "    2", "    3", "    4", "    5", "    6", "    7", "    8", "    9", "   10", " Jack", "Queen", " King"}},
	{"Hearts  ", {"  Ace", "    2", "    3", "    4", "    5", "    6", "    7", "    8", "    9", "   10", " Jack", "Queen", " King"}},
	};

// constant vector of all the suits
const vector<string> suits = { "Clubs   ", "Diamonds", "Spades  ", "Hearts  " };

//vector that counts which cards are in play
vector<int> inPlay = {};


//got help with random number generators from here: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
//sets up the random number generator, 1-52 for each card.
random_device rd;
mt19937 card(rd());
uniform_int_distribution<> dealer(1, 52);

//-----------------------------------------------------------------------------
// Function name: cardNameFromNumber
// 
// created by: Aram Asdourian 3/26/2025
// 
// Description:
// takes a card number from 1-52 and gives the name of the card (ex: Ace of Spades)
// 
// it does this by subtracting 13 from the card number until it is less than 12
// the number of times it subtracted 13 is which suit it is (clubs if 0 times, hearts if 3 times)
// the remaining number is the card number (1 = ace, 13 = king, etc)
//-----------------------------------------------------------------------------
string cardNameFromNumber(int cardNumber)
{
	//initializes the suit number
	int suit = 0;
	//subtracts 1 from the card number because c++ starts counting from 0 not 1
	cardNumber -= 1;

	//if the card number is greater than 12 it subtracts 13 unil it cant anymore
	while (cardNumber  > 12)
	{
		cardNumber -= 13;
		//counts up the suits each time it subtracts
		suit +=1;
	}
	//returns the full name of the card
	//gets the number from the deck map and the suit name from the suits vector
	return( deck.at(suits[suit])[cardNumber] + " of " + suits[suit]);
}

//-----------------------------------------------------------------------------
// Function name: viewDeck
// 
// created by: Aram Asdourian 3/26/2025
// 
// Description:
// displays a chart showing which cards are in the deck
// 
// it checks the inPlay vector to see which cards are currently in someones hand
// if so it leaves the space for that card blank
// if the card is still in the deck it displays an X
//-----------------------------------------------------------------------------
void viewDeck()
{
	//the header for the card numbers and clubs suit
	printf("        | Ace |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  |Jack |Queen|King |\n");
	printf("--------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printf("   Clubs|");
	//iterates 52 times for each card
	for (int card = 1; card <= 52; card++)
	{
		//if the card is in play it leaves the spot blank
		if (count(inPlay.begin(), inPlay.end(), card))
		{
			printf("     |");
		}
		//if the card isnt in play it shows an X
		else
		{
			printf("  X  |");
		}

		//creates a new line and displays the header for the correct suit each time the card count is divisible by 13
		if (card % 13 == 0 and card != 52)
		{
			printf("\n--------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n");
			if(card / 13 == 1)
			{
				printf("Diamonds|");
			}
			if (card / 13 == 2)
			{
				printf("  Spades|");
			}
			if (card / 13 == 3)
			{
				printf("  Hearts|");
			}

		}

	}
}

int main()
{


	printf("\nWelcome to the casino, Here is the deck we will be playing with.\n");
	viewDeck();

	//initializes the playerCount and playerNames variables
	int playerCount = 0;
	vector<string> playerNames = {};

	//asks for the number of players until a valid number is given
	cout << "\n\nHow many people are playing? (Enter a number between 1-5): "; cin >> playerCount;
	while (playerCount < 1 or playerCount > 5)
	{
		//found out how to use cin.ignore with UINT_MAX from here: https://stackoverflow.com/questions/63953373/how-to-ignore-the-rest-of-the-line/63955209#63955209
		//UINT_MAX prevents the error message from appearing multiple times when a string is entered
		cin.clear(); cin.ignore(UINT_MAX, '\n');
		cout << "Invalid input, enter a number between 1-5: "; cin >> playerCount;
	}

	//asks the user to name each player (a maximum of 10 characters is specified so the chart displaying each player can be kept neat)
	int playerIteration = 1;
	while (playerNames.size() < playerCount)
	{
		//initializes the playername variable and asks for the name
		string playerName = "";
		cout << "What is the name of player " + to_string(playerIteration) + "? (at most 10 characters): "; cin >> playerName;
		//checks if the name is greater than 10 characters
		while (playerName.length() > 10)
		{
			cout << "More than 10 characters entered, enter the name of player " + to_string(playerIteration) + " with at most 10 characters: "; cin >> playerName;
		}

		//adds spaces to the name until it is exactly 10 characters, this is to keep everything in line when displayed
		while (playerName.length() != 10)
		{
			playerName.append(" ");
		}
		playerNames.push_back(playerName);
		playerIteration += 1;
	}

	//sets up the header for the player hands
	printf("\nThe players are dealt their cards.\n");
	printf("\n|Player Name|      Card 1      |      Card 2      |      Card 3      |      Card 4      |      Card 5      |\n");
	printf("|-----------|------------------|------------------|------------------|------------------|------------------|\n");
	//first iterates over however many players there are
	for (int playersDealt = 0; playersDealt <= (playerCount - 1); playersDealt++)
	{
		//displays the player name
		printf("| %s|", playerNames[playersDealt].c_str());
		//iterates 5 times to deal them their cards
		for (int cardsDealt = 0; cardsDealt < 5; cardsDealt++)
		{
			//picks a random number and checks if its already inplay or not
			int cardDealt = dealer(card);

			while (count(inPlay.begin(), inPlay.end(), cardDealt))
			{
				cardDealt = dealer(card);
			}
			
			//once a card that isnt in play is dealt it adds that card to the inplay vector
			inPlay.push_back(cardDealt);

			//displays the card
			printf(" %s|", cardNameFromNumber(cardDealt).c_str());

		}
		printf("\n|-----------|------------------|------------------|------------------|------------------|------------------|\n");
	}

	//finally displays the deck again
	printf("\n\nHere is what remains of the deck.\n");
	viewDeck();
	printf("\n");
}


