#include "game.h"
using namespace std;

// Main function
int main() {
		srand(time(NULL));
    Game game(20, 40);
    bool play = game.playGame();
		if (play == false) {
			cout << "Cannot play game!" << endl;	
		}
    return 0;
}
