#include "player.h"
#include <iostream>

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

// Getter for player position
int Player::getPosition() const {
    return position;
}

// Move function to move player forwards or backwards
void Player::move(int spaces) {
    position += spaces;
}

