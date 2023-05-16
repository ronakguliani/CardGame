// Ronak Guliani
// CS302
// The purpose of the Position class is to represent a single position on the game board, with properties such as position number and skip turn status. It provides methods for getting and setting these properties, allowing the game to determine the effects of each position on the players as they move through the game.

#ifndef POSITION_H
#define POSITION_H
#include <iostream>
using std::ostream;

class Position {
public:
		Position();
    Position(int index, bool skipTurn);
		~Position();

    void setIndex(int newIndex);

    bool isSkipped() const;
    void setSkipTurn(bool newSkipTurn);
    
		friend bool operator==(const Position& lhs, const Position& rhs);

    friend ostream& operator<<(ostream& os, const Position& pos);

private:
    int index;
    bool skipTurn;
};

#endif // POSITION_H

