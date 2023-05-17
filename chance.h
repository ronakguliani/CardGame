// Ronak Guliani
// CS302
// The purpose of the chance class is to represent a chance card in the game, as a card plus more. It provides a derived card class for methods for displaying an chance card and applying card effects.

#ifndef CHANCE_H
#define CHANCE_H

#include "card.h"
#include "player.h"
#include "position.h"

class Chance : public Card {
public:
		Chance();
    Chance(int sides);
		~Chance();
    void display() const override;
		bool performAction(Player&, const Position&) override;
    int rollDice(int);
    bool flipCoin();

private:
    int sides;
		bool forward;
		int rolledSpaces;
};

#endif // CHANCE_H

