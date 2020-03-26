#include <iostream>
#include <cstdio>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

int main() {
	cout << "Dots and Boxes - Minimax Algorithm" << endl << endl;
	int rows = 3, cols = 3, depth = 10, turnTime = 10000;
	Game *game = new Game(rows, cols);
	HumanPlayer *p1 = new HumanPlayer(game);
	ComputerPlayer *p2 = new ComputerPlayer(game, depth, turnTime);

	int players_turn = 1;
	int score1 = 0, score2 = 0;
	while (game->checkEndGame() == false) {
		game->printBoard();
		cout << "Player1 -  Player2" << endl;
		cout << "   " << p1->getScore() << "          " << p2->getScore() << endl << endl;
		if (players_turn == 1) {
			p1->move();
			players_turn = 2;
			if (score1 < p1->getScore()) {
				players_turn = 1;
				score1 = p1->getScore();
			}
		}
		else {
			p2->move();
			players_turn = 1;
			if (score2 < p2->getScore()) {
				players_turn = 2;
				score2 = p2->getScore();
			}
		}
	}

	game->printBoard();
	cout << "Player1 -  Player2" << endl;
	cout << "   " << p1->getScore() << "          " << p2->getScore() << endl << endl;

	if (score1 > score2) {
		cout << "Congratulations! You won!" << endl << endl;
	}
	else {
		if (score1 == score2) {
			cout << "No winner..." << endl << endl;
		}
		else {
			cout << "Player2 won." << endl << endl;
		}
	}
	

	cout << "Press Enter to exit.\n";
	char c;
	cin >> c;
	return 0;
}