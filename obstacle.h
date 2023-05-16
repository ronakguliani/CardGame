#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "card.h"

class Obstacle : public Card {
public:
		Obstacle();
    Obstacle(bool);
		~Obstacle();
    void display() const override;
		bool getSkipTurn();
		void performAction(Player& player, const Position& currentPosition) override;

private:
		bool skipTurn;
};

#endif // OBSTACLE_H

