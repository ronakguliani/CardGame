#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using std::string;


class Player {
public:
    Player(const string& name);

    string getName() const;
    void setName(const string& name);

    void setPosition(int position);

    int move(int steps);

private:
    string name;
    int position;
};

#endif // PLAYER_H

