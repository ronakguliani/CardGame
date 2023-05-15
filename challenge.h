#ifndef CHALLENGE_H
#define CHALLENGE_H

#include "card.h"
#include <array>
using namespace std;

class Challenge : public Card {
public:
    Challenge();
		~Challenge();
    void display() const override;
		int getNum1();
		int getNum2();

private:
    array<int, 100> numbers;
		int num1;
		int num2;
};

#endif // CHALLENGE_H

