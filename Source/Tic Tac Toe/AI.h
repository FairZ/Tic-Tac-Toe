#ifndef _AI_H_
#define _AI_H_

#include "Tree.h"

//AI class contains reference to a tree structure of moves, which is regenerated each round,
//and the ability to find the best possible move
class AI
{
private:
	Node* m_root;
public:
	AI();
	~AI();
	void NewRound(Node* _currentState);
	Node* BestMove();
};

#endif