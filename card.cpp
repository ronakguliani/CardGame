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
	setDescription("Obstacle");
	if (skipTurn)
		setSpaces(1);
	else
		setSpaces(-3);
}

Obstacle::~Obstacle() {
	skipTurn = false;	
}


void Obstacle::display() const {
    Card::display();
    cout << "Obstacle: ";
    if (skipTurn) {
        cout << "Skip your turn." << endl;
    } else {
        cout << "Move 3 spaces backward." << endl;
    }
}

bool Obstacle::getSkipTurn() {
	return skipTurn;
}

// Challenge card class constructor
Challenge::Challenge() {
    setDescription("Challenge");
    setSpaces(0);
		
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
    Card::display();
    cout << "Challenge: Calculate the sum of " << num1 << " + " << num2 << endl;
}

int Challenge::getNum1() {
	return num1;
}

int Challenge::getNum2() {
	return num2;
}

Chance::Chance() : sides(0), forward(false) {

}

Chance::~Chance() {
	sides = 0;
	forward = false;
}

// Chance card class constructor
Chance::Chance(int sides) : sides(sides) {
    setDescription("Chance");
    forward = flipCoin();
    int rolledSpaces = rollDice(sides);
		if (forward == false)
			setSpaces(-rolledSpaces);
		else
			setSpaces(rolledSpaces);
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
    Card::display();
		if (forward)
    	cout << "Chance: " << "Move forward " << spaces << " spaces." << endl;
		else
    	cout << "Chance: " << "Move backward " << spaces << " spaces." << endl;
}




