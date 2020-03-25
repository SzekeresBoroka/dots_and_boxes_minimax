#include "HumanPlayer.h"
#include <iostream>

using namespace std;

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::move()
{
	int startX, startY, destX, destY;
	bool good_coordinates = false;

	while (!good_coordinates) {
		good_coordinates = true;
		cout << "From: x_coordinate: ";
		cin >> startX;
		cout << "      y_coordinate: ";
		cin >> startY;
		cout << "To: x_coordinate: ";
		cin >> destX;
		cout << "    y_coordinate: ";
		cin >> destY;
		cout << endl;

		startX = 2 * startX;
		startY = 2 * startY;
		destX = 2 * destX;
		destY = 2 * destY;

		if (!this->game->validCoordinates(startX, startY))
			good_coordinates = false;

		if (!this->game->validCoordinates(destX, destY))
			good_coordinates = false;

		if (startX != destX && startY != destY)
			good_coordinates = false;

		if (startX == destX && abs(startY - destY) != 2)
			good_coordinates = false;

		if (startY == destY && abs(startX - destX) != 2)
			good_coordinates = false;

		if(good_coordinates && !this->game->lineIsFree(startX, startY, destX, destY))
			good_coordinates = false;

		if (!good_coordinates)
			cout << "invalid move, try again" << endl << endl;
	}

	//ha nyero pozicio

	this->game->addLine(startX, startY, destX, destY, ID);
	
}
