#include <iostream>
#include <cstdio>
#include "Game.h"
#include "HumanPlayer.h"

using namespace std;

int main() {
	cout << "Dots and Boxes - Minimax Algorithm" << endl << endl;
	int rows = 4, cols = 4;
	Game *game = new Game(rows, cols);
	HumanPlayer *p1 = new HumanPlayer(game);

	while (game->checkEndGame() == false) {
		game->printBoard();
		p1->move();
	}
	

	cout << "Press Enter to exit.\n";
	int c = getchar();
	return 0;
}