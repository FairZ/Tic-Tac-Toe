#include "AI.h"

AI::AI()
{
	m_root = nullptr;
}

AI::~AI()
{
	delete m_root;
}

void AI::NewRound(Node* _currentState)
{
	//each new round the old tree is deleted
	delete m_root;
	//a new one is created from the current game board state
	m_root = new Node(_currentState);
	m_root->GenerateMoves();
}


Node* AI::BestMove()
{
	//calls the find brest of children function in the current tree
	return m_root->FindBestOfChildren();
}