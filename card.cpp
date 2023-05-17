// Ronak Guliani

#include "card.h"
#include "obstacle.h"
#include "chance.h"
#include "challenge.h"
#include "cstring"
#include <iostream>
#include <random>
using namespace std;

// Constructor for Card class
Card::Card() : spaces(0), description(nullptr) {}

Card::Card(int spaces, char * description) {
	this->spaces = spaces;
	setDescription(description);
}

Card::Card(const Card& src) : spaces(src.spaces), description(nullptr) {
	if (src.description != nullptr) {
		this->description = new char[strlen(src.description) + 1];
		strcpy(this->description, src.description);	
	}	

	else
		this->description = nullptr;
}

Card::~Card() {
	spaces = 0;
	if (description != nullptr)
		delete [] description;
}

// Setter for spaces
void Card::setSpaces(int s) {
    spaces = s;
}

// Setter for description
void Card::setDescription(char * desc) {
	if (description)
		delete [] description;

	this->description = new char[strlen(desc) + 1];
	strcpy(this->description, desc);
}

// Display function for Card class
void Card::display() const {
    cout << description << endl;
}

bool Card::performAction(Player& player, const Position& currentPosition) {
	return true;
} 

// Overloaded << operator
ostream& operator<<(ostream& os, const Card& card) {
    os << "Description: " << card.description;
    return os;
}

// Overloaded = operator
Card& Card::operator=(const Card& src) {
		if (this == &src)
			return *this;

		if (description)
			delete [] description;

		description = new char[strlen(src.description) + 1];
		strcpy(description, src.description);

		spaces = src.spaces;
    return *this;
}

// Overloaded == operator
bool Card::operator==(const Card& rhs) const {
    return description == rhs.description;
}

// Overloaded != operator
bool Card::operator!=(const Card& rhs) const {
    return !(*this == rhs);
}

Obstacle::Obstacle() : skipTurn(0) {}

// Obstacle card class implementation
Obstacle::Obstacle(bool skip) : skipTurn(skip) {
	char newObstacle[] = "Obstacle: You will either lose your turn or move 3 spaces backwards.";
	setDescription(newObstacle);
	if (skipTurn) {
		return;
	}

	else {
		setSpaces(-3);
	}
}

Obstacle::~Obstacle() {
	skipTurn = false;	
}


void Obstacle::display() const {
		cout << description << endl << endl;
}

void Obstacle::setSkipTurn(bool skip) {
	skipTurn = skip;
} 

bool Obstacle::performAction(Player& player, const Position &currentPosition) {
	if (currentPosition.isSkipped()) {
		cout << "You ran into an obstacle! Your turn is skipped. Resting at current position." << endl;	
	}
	else {
		cout << endl << "You ran into an obstacle! Moving backwards 3 spaces." << endl;
		player.move(-3);	
	}

	return true;
}



// Challenge card class constructor
Challenge::Challenge() {
		char newChallenge[] = "Challenge: You will be solving a math problem. Answering correctly will result in moving forward 3 spaces. Answering incorrectly will move backwards 1 space.";
    setDescription(newChallenge);
		char hint[] = "Hint: When adding two numbers, start from the rightmost digit and carry over if needed.";
		setHint(hint);
		
		for (int i = 0; i < 100; i++) {
			numbers[i] = rand() % 100 + 1;
		}
		int index1 = rand() % 100;
  	int index2 = rand() % 100;
  	num1 = numbers[index1];
  	num2 = numbers[index2];    
}


Challenge::Challenge(char * description, int spaces, char * hint) : Card(spaces, description) {
	this->hint = new char[strlen(hint) + 1];
	strcpy(this->hint, hint);

}

Challenge::Challenge(const Challenge& src) : Card(src), numbers(src.numbers), num1(src.num1), num2(src.num2), hint(nullptr) {
	hint = new char[strlen(src.hint) + 1];
  strcpy(hint, src.hint);	
}

Challenge::~Challenge() {
	delete [] hint;
	num1 = 0;
	num2 = 0;
	for (int i : numbers)
		numbers[i] = 0;	
}


void Challenge::setHint(char * newHint) {
	if (hint)
		delete [] hint;

	this->hint = new char[strlen(newHint) + 1];
	strcpy(this->hint, newHint);
}

void Challenge::displayHint() const {
	cout << "Hint: " << hint << endl;
}


// Challenge card class implementation
void Challenge::display() const {
	cout << description << endl << endl;
}



bool Challenge::performAction(Player& player, const Position& currentPosition) {
    if (currentPosition.isSkipped()) {
        cout << "Oh no! You have to skip this turn due to the position. Moving to next player's turn." << endl;
				return true;
    }

   	cout << "Enter the sum of " << num1 << " and " << num2 << ". ";
		char userChoice;
    cout << endl << "Would you like a hint? Enter 'Y' for yes or 'N' for no: ";
    cin >> userChoice;

    if (toupper(userChoice) == 'Y') {
        displayHint();
    }

    int userAnswer;
		cout << "Enter sum: "; 
    cin >> userAnswer;
    if (userAnswer == num1 + num2) {
        cout << "Correct! Moving forward 3 spaces. " << endl;
        player.move(3);
				return true;
    } else {
        cout << "Incorrect. Moving 1 space back." << endl;
        player.move(-1);
				return true;
    }
}


Chance::Chance() : sides(0), forward(false), rolledSpaces(0) {}

Chance::~Chance() {
	sides = 0;
	forward = false;
}

// Chance card class constructor
Chance::Chance(int sides) : sides(sides) {
		char newChance[] = "Chance: Rolling a dice and flipping a coin. The dice decides the number of spaces to move and the coin decides whether to go forwards or backwards.";
		setDescription(newChance);
    forward = flipCoin();
    rolledSpaces = rollDice(sides);
		
	
		if (forward == false) {
			setSpaces(-rolledSpaces);
		}

		else {
			setSpaces(rolledSpaces);
		}
}


bool Chance::performAction(Player& player, const Position& currentPosition) {
	player.move(spaces);
	return true;
}


int Chance::rollDice(int sides) {
	return rand() % sides + 1;
}

bool Chance::flipCoin() {
	int result = rand() % 2 + 1;
	if (result == 1)
		return false;
	else
		return true;
}


// Chance card class implementation
void Chance::display() const {
		cout << description << endl << endl;

		if (forward == false) {
			cout << endl << "You got tails. Moving backwards " << rolledSpaces << " spaces." <<  endl; 
		}

		else {
			cout << endl << "You got heads! Moving forwards " << rolledSpaces << " spaces." << endl; 
		}
}




