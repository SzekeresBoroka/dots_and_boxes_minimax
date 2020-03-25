#include <iostream>
#include <cstdio>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

int main() {
	cout << "Dots and Boxes - Minimax Algorithm" << endl << endl;
	int rows = 4, cols = 4;
	Game *game = new Game(rows, cols);
	HumanPlayer *p1 = new HumanPlayer(game);
	ComputerPlayer *p2 = new ComputerPlayer(game);

	while (game->checkEndGame() == false) {
		game->printBoard();
		cout << "Player1 -  Player2" << endl;
		cout << "   " << p1->getScore() << "          " << p2->getScore() << endl << endl;
		p1->move();
	}
	

	cout << "Press Enter to exit.\n";
	int c = getchar();
	return 0;
}