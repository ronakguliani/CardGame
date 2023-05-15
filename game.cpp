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
		for (int i = 1; i <= pathSize; ++i) {
			int random_number = rand() % 4 + 1;
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
		cout << "Card stack: " << endl;
		cardStack.display();
		cout << endl << "Game board: " << endl;
		gameBoard.display();
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
						Position currentPosition;
						try {
            	currentPosition = gameBoard.retrieveByIndex(player.getPosition());

						} catch (const out_of_range& e) {
							cerr << "Error: " << e.what() << endl;	
						}            
            if (currentPosition.getSkipTurn()) {
                cout << "Oh no! You have to skip this turn. Automatically moving forward 1 position." << endl;
                cout << player.getName() << " is now at position " << player.getPosition() << "." << endl;
                player.move(1);
                if (player.getPosition() >= pathSize) {
                	gameFinished = true;
                  break;
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

                    if (Obstacle* obstacleCard = dynamic_cast<Obstacle*>(drawnCard)) {
                        if (obstacleCard->getSkipTurn()) {
                            cout << endl << "Your turn is skipped. Resting at current position." << endl;
                        } else if (player.getPosition() - 3 < 0) {
															cout << "Resetting position to 1 to avoid going negative." << endl;
															player.setPosition(1);	
												} else {
                    				player.move(3);
													}
                    } else if (Challenge* challengeCard = dynamic_cast<Challenge*>(drawnCard)) {
                        int userAnswer;
                        cout << "Enter the sum of " << challengeCard->getNum1() << " and " << challengeCard->getNum2() << ": ";
                        cin >> userAnswer;
                        if (userAnswer == challengeCard->getNum1() + challengeCard->getNum2()) {
														cout << "Correct! Moving forward 3 spaces. " << endl;
                            player.move(3);
                        } else {
														if (player.getPosition() == 0 || player.getPosition() == 1)
														{
															cout << "Incorrect. Staying at " << player.getPosition() << " position. " << endl;
															player.move(0);	
														}
														else {
															cout << "Incorrect. Moving 1 space back." << endl;
                            	player.move(-1);
														}
                        }
                    } else if (Chance* chanceCard = dynamic_cast<Chance*>(drawnCard)) {
                       		player.move(drawnCard->getSpaces());
													if (player.getPosition() < 0) {
														cout << "Position reset to 1 to avoid going negative." << endl;
														player.setPosition(1);
													}
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
        cout << endl << "The winner is: " << winners[0] << endl;
    } else {
        cout << "It's a tie between: ";
        for (const auto& winner : winners) {
            cout << winner << " ";
        }
        cout << endl;
    }
}


