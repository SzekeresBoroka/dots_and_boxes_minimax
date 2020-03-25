#include "Game.h"

#define ID 1

class HumanPlayer
{
private:
	int score;
	Game* game;
public:
	HumanPlayer(Game* game) {
		score = 0;
		this->game = game;
	}
	~HumanPlayer();
	int getScore() {
		return score;
	}
	void incrementScore(int points) {
		score += points;
	}
	void move();
};

