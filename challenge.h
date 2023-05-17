// Ronak Guliani
// CS302
// The purpose of the challenge class is to represent a challenge card in the game, as a card plus more. It provides a derived card class for methods for displaying an challenge card and applying card effects.

#ifndef CHALLENGE_H
#define CHALLENGE_H

#include "card.h"
#include <array>
using namespace std;

class Challenge : public Card {
public:
    Challenge();
		Challenge(char * description, int spaces, char * hint);
		~Challenge();
		Challenge(const Challenge& src);
		Challenge& operator=(const Challenge& other);
    void display() const override;
		bool performAction(Player&, const Position&) override;
		void setHint(char * newHint);
		void displayHint() const;

private:
    array<int, 100> numbers;
		int num1;
		int num2;
		char * hint;
};

#endif // CHALLENGE_H

