#include "card.h"
#include "obstacle.h"
#include "chance.h"
#include "challenge.h"
#include <iostream>
#include <random>
using namespace std;

// Constructor for Card class
Card::Card() : spaces(0), description("") {}

Card::~Card() {
	spaces = 0;
	description = "";	
}

// Getter for spaces
int Card::getSpaces() const {
    return spaces;
}

// Setter for spaces
void Card::setSpaces(int s) {
    spaces = s;
}

// Setter for description
void Card::setDescription(const string& desc) {
    description = desc;
}

// Display function for Card class
void Card::display() const {
    cout << description << endl;
}

// Overloaded << operator
ostream& operator<<(ostream& os, const Card& card) {
    os << card.description;
    return os;
}

// Overloaded = operator
Card& Card::operator=(const Card& rhs) {
    if (this != &rhs) {
        spaces = rhs.spaces;
        description = rhs.description;
    }
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

Obstacle::Obstacle() : skipTurn(0) {
	setDescription("Obstacle");
}

// Obstacle card class implementation
Obstacle::Obstacle(bool skip) : skipTurn(skip) {
	setDescription("Obstacle: You will either lose your turn or move 3 spaces backwards.");
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
		cout << description << endl;
}

bool Obstacle::getSkipTurn() {
	return skipTurn;
}

// Challenge card class constructor
Challenge::Challenge() {
    setDescription("Challenge: You will be solving a math problem. Answering correctly will result in moving forward 3 spaces. Answering incorrectly will move backwards 1 space.");
		
		for (int i = 0; i < 100; i++) {
			numbers[i] = rand() % 100 + 1;
		}
		int index1 = rand() % 100;
  	int index2 = rand() % 100;
  	num1 = numbers[index1];
  	num2 = numbers[index2];    
}

Challenge::~Challenge() {
	num1 = 0;
	num2 = 0;
	for (int i : numbers)
		numbers[i] = 0;	
}


// Challenge card class implementation
void Challenge::display() const {
	cout << description << endl;
}

int Challenge::getNum1() {
	return num1;
}

int Challenge::getNum2() {
	return num2;
}

Chance::Chance() : sides(0), forward(false) {}

Chance::~Chance() {
	sides = 0;
	forward = false;
}

// Chance card class constructor
Chance::Chance(int sides) : sides(sides) {
		setDescription("Chance: Rolling a dice and flipping a coin. The dice decides the number of spaces to move and the coin decides whether to go forwards or backwards.");
    forward = flipCoin();
    rolledSpaces = rollDice(sides);
		
	
		if (forward == false) {
			setSpaces(-rolledSpaces);
		}

		else {
			setSpaces(rolledSpaces);
		}
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
		cout << description << endl;

		if (forward == false) {
			cout << endl << "You got tails. Moving backwards " << rolledSpaces << " spaces." <<  endl; 
		}

		else {
			cout << endl << "You got heads! Moving forwards " << rolledSpaces << " spaces." << endl; 
		}
}




