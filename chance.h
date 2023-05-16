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
		void performAction(Player&, const Position&) override;
    int rollDice(int);
    bool flipCoin();

private:
    int sides;
		bool forward;
		int rolledSpaces;
};

#endif // CHANCE_H

