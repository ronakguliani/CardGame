#ifndef GAME_H
#define GAME_H

#include <list>
#include "list.h"
#include "card.h"
#include "obstacle.h"
#include "challenge.h"
#include "chance.h"
#include "player.h"
#include "position.h"
using namespace std;

class Game {
public:
    Game();
		Game(int, int);
    ~Game();

    void playGame();

private:
    void initGameBoard();
    void initCardStack();

    LLL<Card*> cardStack;
    DLL<Position> gameBoard;
    list<Player> players;
    int pathSize;
    int stackSize;
};

#endif // GAME_H

