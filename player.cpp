#include "player.h"
#include <iostream>
using namespace std;

// Player constructor with name parameter
Player::Player(const string &name) : name(name), position(0) {}

// Setter for player name
void Player::setName(const std::string &newName) {
    name = newName;
}

// Getter for player name
std::string Player::getName() const {
    return name;
}

// Setter for player position
void Player::setPosition(int newPosition) {
    position = newPosition;
}

// Move function to move player forwards or backwards
int Player::move(int spaces) {
    position += spaces;
		if (position < 0) {
			cout << "Resetting position back to space 0." << endl;	
			setPosition(0);
		}
		return position;
}

