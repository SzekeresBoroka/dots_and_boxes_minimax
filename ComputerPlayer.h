#pragma once
class ComputerPlayer
{
private:
	int score;
public:
	ComputerPlayer() {
		score = 0;
	}
	~ComputerPlayer();
	int getScore() {
		return score;
	}
	void incrementScore() {
		score++;
	}
};

