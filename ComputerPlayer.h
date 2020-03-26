#include "Game.h"

#define ID 2
#define ALPHA_MIN INT_MIN
#define BETA_MAX INT_MAX

typedef struct ABNode {
	int alpha, beta;
	int moveX, moveY;
	int numBoxesTakenByMove;
	int value;
	int** state;
	bool isMax;
	int numChildren;
	ABNode *parent, *child, *sibling;
} ABNode;

class ComputerPlayer
{
private:
	int score, depth, turnTime;
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

private:
	ABNode* newABRootNode(int** state);
	ABNode* newABNode(ABNode * parent, int moveX, int moveY, int** preMoveState);
	int minimaxAplhaBetaPruning(ABNode * node, int** state, int depth, int * nodesVisitedCount, int * branchesPrunedCount, bool isRoot);
	int howManyBoxesDoesMoveComplete(int** state, int moveX, int moveY);
	int howManyBoxesDoesMoveGiveAway(int** state, int moveX, int moveY);
	int getNumFreeLines(int** state);
	void getPotentialMoves(int** state, int** potentialMoves);
};

