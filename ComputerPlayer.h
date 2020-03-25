#include "Game.h"

class ComputerPlayer
{
private:
	int score;
	Game* game;

public:
	ComputerPlayer(Game* game) {
		this->score = 0;
		this->game = game;
	}
	~ComputerPlayer();
	int getScore() {
		return score;
	}
	void incrementScore(int points) {
		score += points;
	}
};

