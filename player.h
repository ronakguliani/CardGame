// Ronak Guliani
// CS302
// This class defines a player. A player's primary purpose is to be able to constantly move forward or backwards in the board. The operator overloading allows for this. 

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using std::string;
using std::ostream;
using std::istream;


class Player {
public:
    Player(const string& name);

    string getName() const;
    void setName(const string& name);

    void setPosition(int position);

    int move(int steps);

		Player& operator+=(int);
		bool operator==(const Player& other) const;
		bool operator!=(const Player& other) const;
		bool operator<(const Player& other) const;
		bool operator<=(const Player& other) const;
    bool operator>(const Player& other) const;
    bool operator>=(const Player& other) const;
		friend bool operator==(int, const Player& other);
		friend bool operator!=(int, const Player& other);
		friend bool operator<(int, const Player& other);
		friend bool operator<=(int, const Player& other);
    friend bool operator>(int, const Player& other);
    friend bool operator>=(int, const Player& other);
    friend ostream& operator<<(ostream& os, const Player& player);
		friend istream& operator>>(istream& is, Player& player);

private:
    string name;
    int position;
		int maxPosition;
};

#endif // PLAYER_H

