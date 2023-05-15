#include "game.h"

// Main function
int main() {
		srand(time(NULL));
    Game game(20, 40);
    game.playGame();
    return 0;
}
