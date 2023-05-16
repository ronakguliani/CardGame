// Ronak Guliani
#include "position.h"

Position::Position() : index(0), skipTurn(false) {}

Position::Position(int index, bool skipTurn) : index(index), skipTurn(skipTurn) {}

void Position::setIndex(int newIndex) {
	index = newIndex;
}

bool Position::getSkipTurn() const {
	return skipTurn;
}

void Position::setSkipTurn(bool newSkipTurn) {
	skipTurn = newSkipTurn;
}

bool operator== (const Position& lhs, const Position& rhs) {
	return lhs.index == rhs.index && lhs.skipTurn == rhs.skipTurn;
}

ostream& operator<< (ostream& os, const Position& pos) {
	os << "(" << pos.index << ", " << (pos.skipTurn ? "skip" : "play") << ")";
	return os;
}

