// Ronak Guliani
// CS302
// The purpose of the obstacle class is to represent a obstacle card in the game, as a card plus more. It provides a derived card class for methods for displaying an obstacle card and applying card effects.

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

