#pragma once
class Game
{
private:
	int rows, cols;
	int** board;
	/*
	BOARD 3x3 (5x5 actually) -> 2*rows - 1, 2*cols - 1

				   0 1 2 3 4	-> actual coordinates
				   0   1   2	-> coordinates for player
				  ___________
			0  0 | *   *   *
			1    |
			2  1 | *   *   *
			3    |
			4  2 | *   *   *


			DOTS: -> i and j are even numbers

			LINES: -> i is odd, j is even 
					  or i is even, j is odd

			SQUARES: -> i and j are odd numbers
	*/
public:
	Game(const int rows, const int cols);
	~Game();
	void printBoard();
	bool validCoordinates(int x, int y);
	bool lineIsFree(int startX, int startY, int destX, int destY);
	void addLine(int startX, int startY, int destX, int destY, int player_id);
	void convertLineCoordinates(int startX, int startY, int destX, int destY, int *x, int *y);
	bool checkEndGame();
};

