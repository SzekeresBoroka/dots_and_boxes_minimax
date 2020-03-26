#include "ComputerPlayer.h"
#include <iostream>
#include <time.h>  
#include <algorithm>  

using namespace std;


ComputerPlayer::~ComputerPlayer()
{
}


void ComputerPlayer::move()
{
	cout << "Player2's turn!\n";
	int x, y, nodesVisited, branchesPruned;
	ABNode* root = newABRootNode(this->game->getState());
	minimaxAplhaBetaPruning(root, this->game->getState(), this->depth, &nodesVisited, &branchesPruned, true);
	ABNode * child = root->child;
	// go to the end of the linked list
	int m = -1;
	while (child->sibling != NULL) {
		if (m < child->value) {
			m = child->value;
			x = child->moveX;
			y = child->moveY;
		}
		//cout << child->value << " ";
		child = child->sibling;
		
	}
	//cout << endl;

	//cout << x << " " << y << endl;
	//cout << "nodes visited: " << nodesVisited << "\nbranches pruned: " << branchesPruned << endl;

	int startX, startY, destX, destY;
	//horizontal line
	if (x % 2 == 0 && y % 2 == 1) {
		startX = x;
		startY = y - 1;
		destX = x;
		destY = y + 1;
	}
	//vertical line
	if (x % 2 == 1 && y % 2 == 0) {
		startX = x - 1;
		startY = y;
		destX = x + 1;
		destY = y;
	}

	this->game->addLine(startX, startY, destX, destY);

	int points = this->game->completedBoxesWithMove(startX, startY, destX, destY, ID);
	this->incrementScore(points);

	if (x % 2 == 0 && y % 2 == 1) {
		startX = x / 2;
		startY = y / 2;
		destX = x / 2;
		destY = y / 2 + 1;
	}
	//vertical line
	if (x % 2 == 1 && y % 2 == 0) {
		startX = x / 2;
		startY = y / 2;
		destX = x / 2 + 1;
		destY = y / 2;
	}

	cout << "Moves: " << startX << "," << startY << " - " << destX << "," << destY << endl << endl;
}

ABNode * ComputerPlayer::newABRootNode(int** state)
{
	ABNode * node = (ABNode *)malloc(sizeof(ABNode));

	node->alpha = ALPHA_MIN;
	node->beta = BETA_MAX;
	node->moveX = -1;
	node->moveY = -1;
	node->numBoxesTakenByMove = 0;
	node->parent = NULL;
	node->child = NULL;
	node->sibling = NULL;
	node->numChildren = 0;
	node->isMax = true;
	node->value = ALPHA_MIN;

	return node;
}

ABNode * ComputerPlayer::newABNode(ABNode * parent, int moveX, int moveY, int ** preMoveState)
{
	ABNode * node = (ABNode *)malloc(sizeof(ABNode));

	node->alpha = parent->alpha;
	node->beta = parent->beta;
	node->moveX = moveX;
	node->moveY = moveY;
	node->numBoxesTakenByMove = howManyBoxesDoesMoveComplete(preMoveState, moveX, moveY);

	node->parent = parent;
	node->child = NULL;
	node->sibling = NULL;
	node->numChildren = 0;

	if (node->numBoxesTakenByMove == 0)
		node->isMax = !(parent->isMax);
	else
		node->isMax = parent->isMax;

	if (node->isMax)
		node->value = ALPHA_MIN;
	else
		node->value = BETA_MAX;

	//add child to parent
	if (parent->child == NULL)
		parent->child = node;
	else {
		ABNode * otherChild = parent->child;
		// go to the end of the linked list
		while (otherChild->sibling != NULL)
			otherChild = otherChild->sibling;

		otherChild->sibling = node;
	}

	parent->numChildren += 1;

	return node;
}

int ComputerPlayer::minimaxAplhaBetaPruning(ABNode * node, int ** state, int depth, int * nodesVisitedCount, int * branchesPrunedCount, bool isRoot)
{
	*nodesVisitedCount += 1;

	const int numFreeLines = getNumFreeLines(state);
	// Node is terminal
	if (depth == 0 || numFreeLines == 0) {
		int score = 0;

		if (depth == 0 && numFreeLines > 0) {
			// heuristic value for the node
			// assume we get half of what's left
			score += numFreeLines / 2;
		}

		// number of boxes that have been taken.
		do {
			if (node->isMax)
				score += node->numBoxesTakenByMove;
			node = node->parent;
		} while (node != NULL);

		return score;
	}

	// else enumerate the possible moves and try them.
	int** potentialMoves = new int*[numFreeLines];
	for (int i = 0; i < numFreeLines; i++) {
		potentialMoves[i] = new int[2];
	}
	getPotentialMoves(state, potentialMoves);


	unsigned long long endTime;
	if (isRoot) // Limit the maximum turn time
		endTime = time(NULL) + turnTime;

	for (int i = 0; i < numFreeLines; i++) {
		int moveX = potentialMoves[i][0];
		int moveY = potentialMoves[i][1];

		ABNode * child = newABNode(node, moveX, moveY, state);
		//try move
		state[moveX][moveY] = 1;

		int newDepth = numFreeLines == 1 ? depth : depth - 1;

		int v = minimaxAplhaBetaPruning(child, state, newDepth, nodesVisitedCount, branchesPrunedCount, false);

		// reset the state
		state[moveX][moveY] = 0;

		/*if (isRoot)
			printf("Checked move %d,%d. Score is: %d\n", moveX, moveY, v);*/

		if (node->isMax) {
				if (v > node->value) {
					node->value = v;
				}
				node->alpha = max(node->alpha, v);
				if (node->beta <= node->alpha) {
					*branchesPrunedCount += 1;
					// beta cutoff
					return node->alpha;
				}
		}
		else {
				if (v < node->value) {
					node->value = v;
				}
				node->beta = min(node->beta, v);

				if (node->beta <= node->alpha) {
					*branchesPrunedCount += 1;
					// alpha cutoff
					return node->beta;
				}
		}

		if (isRoot && time(NULL) > endTime) {
			printf("Search has taken too much time. Returning best move found so far.\n");
			break;
		}
	}
	return node->value;
}

int ComputerPlayer::howManyBoxesDoesMoveComplete(int ** state, int x, int y)
{
	//horizontal line
	if (x % 2 == 0 && y % 2 == 1) {

		//top line - max 1 box
		if (x == 0) {
			if (state[x + 1][y - 1] == 1 && state[x + 1][y + 1] == 1 && state[x + 2][y] == 1) {
				return 1;
			}
			return 0;
		}

		//bottom line - max 1 box
		if (x == this->game->getNumRows() - 1) {
			if (state[x - 1][y - 1] == 1 && state[x - 1][y + 1] == 1 && state[x - 2][y] == 1) {
				return 1;
			}
			return 0;
		}

		//center line - max 2 boxes
		int nr = 0;
		if (state[x + 1][y - 1] == 1 && state[x + 1][y + 1] == 1 && state[x + 2][y] == 1) {
			nr++;
		}
		if (state[x - 1][y - 1] == 1 && state[x - 1][y + 1] == 1 && state[x - 2][y] == 1) {
			nr++;
		}
		return nr;
	}

	//vertical line
	if (x % 2 == 1 && y % 2 == 0) {

		//left edge line - max 1 box
		if (x == 0) {
			if (state[x - 1][y + 1] == 1 && state[x + 1][y + 1] == 1 && state[x][y + 2] == 1 && state[x][y + 1] == 0) {
				state[x][y + 1] = ID;
				return 1;
			}
			return 0;
		}

		//rigth edge line - max 1 box
		if (x == this->game->getNumCols() - 1) {
			if (state[x - 1][y - 1] == 1 && state[x + 1][y - 1] == 1 && state[x][y - 2] == 1 && state[x][y - 1] == 0) {
				state[x][y - 1] = ID;
				return 1;
			}
			return 0;
		}

		//center line - max 2 boxes
		int nr = 0;
		if (state[x - 1][y + 1] == 1 && state[x + 1][y + 1] == 1 && state[x][y + 2] == 1 && state[x][y + 1] == 0) {
			state[x][y + 1] = ID;
			nr++;
		}
		if (state[x - 1][y - 1] == 1 && state[x + 1][y - 1] == 1 && state[x][y - 2] == 1 && state[x][y - 1] == 0) {
			state[x][y - 1] = ID;
			nr++;
		}
		return nr;
	}
	return 0;
}

int ComputerPlayer::howManyBoxesDoesMoveGiveAway(int ** state, int x, int y)
{
	//horizontal line
	if (x % 2 == 0 && y % 2 == 1) {

		//top line - max 1 box
		if (x == 0) {
			if (state[x + 1][y - 1] + state[x + 1][y + 1] + state[x + 2][y] == 2 ) {
				return 1;
			}
			return 0;
		}

		//bottom line - max 1 box
		if (x == this->game->getNumRows() - 1) {
			if (state[x - 1][y - 1] + state[x - 1][y + 1] + state[x - 2][y]  == 2) {
				return 1;
			}
			return 0;
		}

		//center line - max 2 boxes
		int nr = 0;
		if (state[x + 1][y - 1] + state[x + 1][y + 1] + state[x + 2][y] == 2) {
			nr++;
		}
		if (state[x - 1][y - 1] + state[x - 1][y + 1] + state[x - 2][y] == 2) {
			nr++;
		}
		return nr;
	}

	//vertical line
	if (x % 2 == 1 && y % 2 == 0) {

		//left edge line - max 1 box
		if (x == 0) {
			if (state[x - 1][y + 1] + state[x + 1][y + 1] + state[x][y + 2] == 2) {
				return 1;
			}
			return 0;
		}

		//rigth edge line - max 1 box
		if (x == this->game->getNumCols() - 1) {
			if (state[x - 1][y - 1] + state[x + 1][y - 1] + state[x][y - 2] == 2 ) {
				return 1;
			}
			return 0;
		}

		//center line - max 2 boxes
		int nr = 0;
		if (state[x - 1][y + 1] + state[x + 1][y + 1] + state[x][y + 2] == 2) {
			nr++;
		}
		if (state[x - 1][y - 1] + state[x + 1][y - 1] + state[x][y - 2] == 2) {
			nr++;
		}
		return nr;
	}
	return 0;
}

int ComputerPlayer::getNumFreeLines(int ** state)
{
	int count = 0;
	for (int i = 0; i < this->game->getNumRows(); i++) {
		for (int j = 0; j < this->game->getNumCols(); j++) {
			//horizontal lines
			if (i % 2 == 0 && j % 2 == 1) {
				if (state[i][j] == 0)
					count++;
			}
			//vertical lines
			if (i % 2 == 1 && j % 2 == 0) {
				if (state[i][j] == 0)
					count++;
			}
		}
	}
	return count;
}

void ComputerPlayer::getPotentialMoves(int ** state, int ** potentialMoves)
{
	int count = 0;
	for (int i = 0; i < this->game->getNumRows(); i++) {
		for (int j = 0; j < this->game->getNumCols(); j++) {
			//horizontal lines
			if (i % 2 == 0 && j % 2 == 1) {
				if (state[i][j] == 0) {
					potentialMoves[count][0] = i;
					potentialMoves[count][1] = j;
					count++;
				}
			}
			//vertical lines
			if (i % 2 == 1 && j % 2 == 0) {
				if (state[i][j] == 0) {
					potentialMoves[count][0] = i;
					potentialMoves[count][1] = j;
					count++;
				}
			}
		}
	}
}
