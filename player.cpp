// Ronak Guliani

#include "player.h"
#include <iostream>
using namespace std;

// Player constructor with name parameter
Player::Player(const string &name) : name(name), position(0) {}

// Setter for player name
void Player::setName(const string &newName) {
    name = newName;
}

// Get player name
string Player::getName() const {
    return name;
}

// Setter for player position
void Player::setPosition(int newPosition) {
    position = newPosition;
}

// Overloaded += operator
Player& Player::operator+=(int spaces) {
    int newPosition = position + spaces;
    if (newPosition < 0 || newPosition > maxPosition) {
        throw out_of_range("New position is out of the allowed range.");
    }
    move(spaces);
    return *this;
}

// Overloaded == operator
bool Player::operator==(const Player& other) const {
    return position == other.position;
}

// Overloaded != operator
bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}

// Overloaded < operator
bool Player::operator<(const Player& other) const {
    return position < other.position;
}

// Overloaded <= operator
bool Player::operator<=(const Player& other) const {
    return *this < other || *this == other;
}

// Overloaded > operator
bool Player::operator>(const Player& other) const {
    return !(*this <= other);
}

// Overloaded >= operator
bool Player::operator>=(const Player& other) const {
    return !(*this < other);
}

bool operator==(int pos, const Player& other) {
    return pos == other.position;
}

bool operator!=(int pos, const Player& other) {
    return pos != other.position;
}

bool operator<(int pos, const Player& other) {
    return pos < other.position;
}

bool operator<=(int pos, const Player& other) {
    return pos <= other.position;
}

bool operator>(int pos, const Player& other) {
    return pos > other.position;
}

bool operator>=(int pos, const Player& other) {
    return pos >= other.position;
}


// Overloaded << operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player: " << player.name << ", Position: " << player.position << endl;
    return os;
}

istream& operator>>(istream& is, Player& player) {
	cout << "Enter player name: ";
	is >> player.name;
	cout << "Enter player position: ";
	is >> player.position;
	return is;
}


// Move function to move player forwards or backwards
int Player::move(int spaces) {
		try {
    	position += spaces;
			if (position < 0) {
				cout << "Resetting position back to space 0." << endl;	
				setPosition(0);
			}
		}
		catch (const out_of_range& e) {
      cerr << "Error: " << e.what() << endl;
		}

		return position;
}
