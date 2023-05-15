#ifndef CHANCE_H
#define CHANCE_H

#include "card.h"

class Chance : public Card {
public:
		Chance();
    Chance(int sides);
		~Chance();
    void display() const override;
    int rollDice(int);
    bool flipCoin();

private:
    int sides;
		bool forward;
		int rolledSpaces;
};

#endif // CHANCE_H

