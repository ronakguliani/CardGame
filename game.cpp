// Ronak Guliani

#include "game.h"
#include <iostream>
#include <random>
#include "position.h"

Position::Position() : index(0), skipTurn(false) {}

Position::Position(int index, bool skipTurn) : index(index), skipTurn(skipTurn) {}

Position::~Position() {
	index = 0;
	skipTurn = false;
}

void Position::setIndex(int newIndex) {
	index = newIndex;
}

bool Position::isSkipped() const {
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

// Game constructor
Game::Game(int pathSize, int stackSize)
    : pathSize(pathSize), stackSize(stackSize) {
    initGameBoard();
    initCardStack();
}

// Destructor
Game::~Game() {
	players.clear();
	pathSize = 0;
	stackSize = 0;
}

// Initialize the game board (DLL)
void Game::initGameBoard() {
		for (int i = 1; i <= pathSize; ++i) {
			int random_number = rand() % 3 + 1;
			bool skipTurn = false;
			if (random_number == 1) {
				skipTurn = true;	
			}	

			Position pos(i, skipTurn);
			gameBoard.insert(pos);
		}
}

// Initialize the card stack (LLL)
void Game::initCardStack() {
    for (int i = 1; i <= stackSize; ++i) {
				int cardType = rand() % 3 + 1;
				bool isSkip = rand() % 4 == 0;
        
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
		cout << "Display stack and board: " << endl;
		cout << "Card stack: " << endl;
		cardStack.display();
		cout << endl << "Game board: " << endl;
		gameBoard.display();
		cout << endl << endl;

		int numPlayers;
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
       	cout << "Enter the name of player " << i + 1 << ": ";
        cin >> playerName;
        players.push_back(Player(playerName));
    }

    bool gameFinished = false;
    while (!gameFinished) {
        for (auto& player : players) {
            cout << endl << "It's " << player.getName() << "'s turn." << endl;

            cout << "Enter 'r' to roll the dice or 'q' to quit the game: ";
            char roll;
            cin >> roll;
						if (roll == 'q') {
							gameFinished = true;
							break;	

						} else if (roll == 'r') {
								cout << "Rolling dice... ";	
								int side = rand() % 6 + 1;
								cout << " You rolled a " << side << "!" << endl;
								player.move(side);
								if (player.move(0) >= pathSize) {
									cout << "We found a winner!" << endl;
									gameFinished = true;
									break;	
								}
						}

            cout << player.getName() << " is now at position " << player.move(0) << "." << endl;
						cout << endl << "You are at a new position on the board! You will now be either drawing a card or skipping your turn..." << endl; 

						Position currentPosition;
						try {
            	currentPosition = gameBoard.retrieveByIndex(player.move(0));

						} catch (const out_of_range& e) {
								cerr << "Error: " << e.what() << endl;	
						}            

            if (currentPosition.isSkipped()) {
                cout << "Oh no! You have to skip this turn. Moving to next player's turn." << endl;

            } else {
                cout << "Enter 'd' to draw a card or 'q' to quit the game: ";
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
    									cerr << endl << "Error: No card was drawn" << endl;
										}

										drawnCard->performAction(player, currentPosition);

                    cout << player.getName() << " is now at position " << player.move(0) << "." << endl;
                    if (player.move(0) >= pathSize) {
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
    for (auto& player : players) {
        if (player.move(0) > maxPosition) {
            maxPosition = player.move(0);
            winners.clear();
            winners.push_back(player.getName());
        } else if (player.move(0) == maxPosition) {
            winners.push_back(player.getName());
        }
    }

    // Display the winner(s)
    if (winners.size() == 1) {
        cout << endl << "The winner is " << winners[0] << ", with " << maxPosition << " points!" << endl;
    } else {
        cout << "It's a tie between: ";
        for (const auto& winner : winners) {
            cout << winner << " ";
        }
       	cout << endl;
    	}
}


