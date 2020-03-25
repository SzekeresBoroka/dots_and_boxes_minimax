#pragma once
class Game
{
private:
	int rows, cols;
	int** board;
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

