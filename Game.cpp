#include <iostream>
#include "Game.h"

using namespace std;

Game::Game(const int rows, const int cols)
{
	this->rows = 2 * rows - 1;
	this->cols = 2 * cols - 1;
	this->board = new int*[this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->board[i] = new int[this->cols];
		for (int j = 0; j < this->cols; j++) {
			this->board[i][j] = 0;
		}
	}
}


Game::~Game()
{
	for (int i = 0; i < this->rows; i++) {
		delete[] this->board[i];
	}
	delete[] this->board;
}

void Game::printBoard()
{
	//y coordinates
	cout << "    ";
	for (int j = 0; j < (this->cols + 1)/2; j++)
		cout << j << "   ";
	cout << endl << "    ";
	for (int j = 1; j < (this->cols + 1) / 2; j++)
		cout << "____";
	cout << "_" << endl;
	for (int i = 0; i < this->rows; i++) {
		//x coordinates
		if (i % 2 == 0)
			cout << " " << i / 2 << " |";
		else
			cout << "   |";
		for (int j = 0; j < this->cols; j++) {
			//dots
			if (i%2 == 0 && j%2 == 0) {
				cout << "*";
				continue;
			}
			//square
			if (i % 2 == 1 && j % 2 == 1) {
				if (this->board[i][j] == 0)
					cout << "   ";
				else
					cout << " " << this->board[i][j] << " ";
				continue;
			}
			//horizontal lines
			if (i % 2 == 0 && j % 2 == 1) {
				if (this->board[i][j] == 0)
					cout << "   ";
				else
					cout << "---";
				continue;
			}
			//vertical lines
			if (this->board[i][j] == 0)
				cout << " ";
			else
				cout << "|";
		}
		cout << endl;
	}
	cout << endl;

}

bool Game::validCoordinates(int x, int y)
{
	if (x < 0 || x >= this->rows || y < 0 || y >= this->cols) {
		return false;
	}
	return true;
}

bool Game::lineIsFree(int startX, int startY, int destX, int destY)
{
	int x, y;
	this->convertLineCoordinates(startX, startY, destX, destY, &x, &y);
	
	if (this->board[x][y] == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Game::addLine(int startX, int startY, int destX, int destY)
{
	int x, y;
	this->convertLineCoordinates(startX, startY, destX, destY, &x, &y);

	this->board[x][y] = 1;
}

void Game::convertLineCoordinates(int startX, int startY, int destX, int destY, int * x, int * y)
{
	if (startX == destX) {
		*x = startX;
		if (startY < destY)
			*y = startY + 1;
		else
			*y = destY + 1;
	}
	else {
		*y = startY;
		if (startX < destX)
			*x = startX + 1;
		else
			*x = destX + 1;
	}
}

bool Game::checkEndGame()
{
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			if (i % 2 == 0 && j % 2 == 1 && this->board[i][j] == 0)
				return false;
			if (i % 2 == 1 && j % 2 == 0 && this->board[i][j] == 0)
				return false;
		}
	}
	return true;
}

int Game::completedBoxesWithMove(int startX, int startY, int destX, int destY, int player_id)
{
	int x, y;
	this->convertLineCoordinates(startX, startY, destX, destY, &x, &y);

	//horizontal line
	if (x % 2 == 0 && y % 2 == 1) {

		//top line - max 1 box
		if (x == 0) {
			if (this->board[x + 1][y - 1] == 1 && this->board[x + 1][y + 1] == 1 && this->board[x + 2][y] == 1 && this->board[x + 1][y] == 0) {
				this->board[x + 1][y] = player_id;
				return 1;
			}
			return 0;
		}

		//bottom line - max 1 box
		if (x == this->rows - 1) {
			if (this->board[x - 1][y - 1] == 1 && this->board[x - 1][y + 1] == 1 && this->board[x - 2][y] == 1 && this->board[x - 1][y] == 0) {
				this->board[x - 1][y] = player_id;
				return 1;
			}
			return 0;
		}

		//center line - max 2 boxes
		int nr = 0;
		if (this->board[x + 1][y - 1] == 1 && this->board[x + 1][y + 1] == 1 && this->board[x + 2][y] == 1 && this->board[x + 1][y] == 0) {
			this->board[x + 1][y] = player_id;
			nr++;
		}
		if (this->board[x - 1][y - 1] == 1 && this->board[x - 1][y + 1] == 1 && this->board[x - 2][y] == 1 && this->board[x - 1][y] == 0) {
			this->board[x - 1][y] = player_id;
			nr++;
		}
		return nr;
	 }

	//vertical line
	if (x % 2 == 1 && y % 2 == 0) {

		//left edge line - max 1 box
		if (x == 0) {
			if (this->board[x - 1][y + 1] == 1 && this->board[x + 1][y + 1] == 1 && this->board[x][y + 2] == 1 && this->board[x][y + 1] == 0) {
				this->board[x][y + 1] = player_id;
				return 1;
			}
			return 0;
		}

		//rigth edge line - max 1 box
		if (x == this->cols - 1) {
			if (this->board[x - 1][y - 1] == 1 && this->board[x + 1][y - 1] == 1 && this->board[x][y - 2] == 1 && this->board[x][y - 1] == 0) {
				this->board[x][y - 1] = player_id;
				return 1;
			}
			return 0;
		}

		//center line - max 2 boxes
		int nr = 0;
		if (this->board[x - 1][y + 1] == 1 && this->board[x + 1][y + 1] == 1 && this->board[x][y + 2] == 1 && this->board[x][y + 1] == 0) {
			this->board[x][y + 1] = player_id;
			nr++;
		}
		if (this->board[x - 1][y - 1] == 1 && this->board[x + 1][y - 1] == 1 && this->board[x][y - 2] == 1 && this->board[x][y - 1] == 0) {
			this->board[x][y - 1] = player_id;
			nr++;
		}
		return nr;
	}

	return 0;
}

int ** Game::getState()
{
	int** state = new int*[this->rows];
	for (int i = 0; i < this->rows; i++) {
		state[i] = new int[this->cols];
		for (int j = 0; j < this->cols; j++) {
			state[i][j] = this->board[i][j];
		}
	}
	return state;
}
