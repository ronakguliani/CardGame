// Ronak Guliani
// CS302
// The purpose of the Game class is to manage the overall game logic, player interactions, and game state. It initializes the game board, card stack, and player instances, and provides methods for playing the game, including drawing cards and moving players on the game board.

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

