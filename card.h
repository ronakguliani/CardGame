// Ronak Guliani
// CS302
// The purpose of the Card class is to represent a single card in the game, with different types of cards such as Obstacle, Challenge, and Chance. It provides a base class for these specialized cards and contains methods for displaying card information and applying card effects on the players.

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include "player.h"
#include "position.h"
using namespace std;

class Card {
public:
    Card();
		virtual ~Card();
    void setDescription(const string& description);
    string getDescription() const;

    void setSpaces(int spaces);
		int getSpaces() const;

		virtual void performAction(Player& player, const Position& currentPosition); 

    virtual void display() const;

    friend ostream& operator<<(ostream& os, const Card& card);

    Card& operator=(const Card& other);
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;

protected:
    int spaces;
    string description;
};

#endif // CARD_H

