#ifndef POSITION_H
#define POSITION_H
#include <iostream>
using std::ostream;

class Position {
public:
		Position() : index(0), skipTurn(false) {}
    Position(int index, bool skipTurn) : index(index), skipTurn(skipTurn) {}

    int getIndex() const { return index; }
    void setIndex(int newIndex) { index = newIndex; }

    bool getSkipTurn() const { return skipTurn; }
    void setSkipTurn(bool newSkipTurn) { skipTurn = newSkipTurn; }
    
		friend bool operator==(const Position& lhs, const Position& rhs) { return lhs.index == rhs.index && lhs.skipTurn == rhs.skipTurn; }

    friend ostream& operator<<(ostream& os, const Position& pos) {
	os << "(" << pos.index << ", " << (pos.skipTurn ? "skip" : "play") << ")";
    return os;	
		}


private:
    int index;
    bool skipTurn;
};

#endif // POSITION_H

