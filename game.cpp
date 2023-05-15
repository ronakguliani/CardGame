#include "game.h"
#include <iostream>
#include <random>

// Game constructor
Game::Game(int pathSize, int stackSize)
    : pathSize(pathSize), stackSize(stackSize) {
    initGameBoard();
    initCardStack();
}

// Destructor
Game::~Game() {}

// Initialize the game board (DLL)
void Game::initGameBoard() {
		int random_number = rand() % 3 + 1;

    for (int i = 1; i <= pathSize; ++i) {
        bool skipTurn = random_number % 3 == 0;
        Position pos(i, skipTurn);
        gameBoard.insert(pos);
    }
}

// Initialize the card stack (LLL)
void Game::initCardStack() {
		int skipped = rand() % 2 + 1;
		bool isSkip;
	 	if (skipped == 1)
			isSkip = true;	
		else
			isSkip = false;
    for (int i = 1; i <= stackSize; ++i) {
				int cardType = rand() % 3 + 1;
        Card* card;
        switch (cardType) {
        case 1:
            card = new Obstacle(isSkip);
            break;
        case 2:
            card = new Challenge();
            break;
        case 3:
            card = new Chance(6);
            break;
        default:
            card = nullptr;
            break;
        }
        if (card) {
            cardStack.insert(card);
        }
    }
}

// Play the game
void Game::playGame() {
    int numPlayers;
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> playerName;
        players.push_back(Player(playerName));
    }

    bool gameFinished = false;
    while (!gameFinished) {
        for (auto& player : players) {
            cout << "It's " << player.getName() << "'s turn." << endl;
						Position currentPosition;
						try {
            	currentPosition = gameBoard.retrieveByIndex(player.getPosition());

						} catch (const out_of_range& e) {
							cerr << "Error: " << e.what() << endl;	
						}            
            if (currentPosition.getSkipTurn()) {
                cout << "Oh no! You have to skip this turn." << endl;
                player.move(1);
            } else {
                std::cout << "Enter 'd' to draw a card or 'q' to quit the game: ";
                char choice;
                cin >> choice;

                if (choice == 'q') {
                    gameFinished = true;
                    break;
                } else if (choice == 'd') {
                    Card * drawnCard = cardStack.getRandomCard();
										if (drawnCard) {
    									drawnCard->display();
										} else {
    									cerr << "Error: No card was drawn" << endl;
										}

                    if (Obstacle* obsCard = dynamic_cast<Obstacle*>(drawnCard)) {
                        if (obsCard->getSkipTurn()) {
                            cout << "Your turn is skipped." << endl;
                            player.move(1);
                        } else {
                            player.move(drawnCard->getSpaces());
                        }
                    } else if (Challenge* chCard = dynamic_cast<Challenge*>(drawnCard)) {
                        int userAnswer;
                        cout << "Enter the sum of " << chCard->getNum1() << " and " << chCard->getNum2() << ": ";
                        cin >> userAnswer;
                        if (userAnswer == chCard->getNum1() + chCard->getNum2()) {
                            player.move(3);
                        } else {
                            player.move(-1);
                        }
                    } else if (Chance* chCard = dynamic_cast<Chance*>(drawnCard)) {
                        player.move(drawnCard->getSpaces());
                    }

                    cout << player.getName() << " is now at position " << player.getPosition() << "." << endl;
                    if (player.getPosition() >= pathSize) {
                        gameFinished = true;
                        break;
                    }
                }
            }
        }
    }

		// Declare winner
    int maxPosition = 0;
    vector<string> winners;
    for (const auto& player : players) {
        if (player.getPosition() > maxPosition) {
            maxPosition = player.getPosition();
            winners.clear();
            winners.push_back(player.getName());
        } else if (player.getPosition() == maxPosition) {
            winners.push_back(player.getName());
        }
    }

    // Display the winner(s)
    if (winners.size() == 1) {
        std::cout << "The winner is: " << winners[0] << std::endl;
    } else {
        cout << "It's a tie between: ";
        for (const auto& winner : winners) {
            cout << winner << " ";
        }
        cout << endl;
    }
}


