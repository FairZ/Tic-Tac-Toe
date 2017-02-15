#include "Tree.h"

//constructor which copies values from a given node
Node::Node(Node* _copy)
{
	for (int i=0; i<9;i++)
	{
		m_data[i] = _copy->m_data[i];
	}
	m_playerTurn = _copy->m_playerTurn;
	m_parent = _copy->m_parent;
	m_level = 0;
	m_score = 0;
	m_win = false;
	m_lose = false;
}

//constructor to create new node on tree and assign appropriate values
Node::Node(char _data[9], bool _playerTurn ,Node* _parent)
{
	for (int i=0; i<9;i++)
	{
		m_data[i] = _data[i];
	}
	m_playerTurn = _playerTurn;
	m_parent = _parent;
	m_level = m_parent->m_level + 1;
	m_win = false;
	m_lose = false;
	SetScore();
}

//default constructor for creating first node
Node::Node()
{
	for (int i=0; i<9;i++)
	{
		m_data[i] = 0;
	}
	m_playerTurn = true;
	m_parent = nullptr;
	m_level = 0;
	m_score = 0;
	m_win = false;
	m_lose = false;
}


Node::~Node()
{
	//cleanup tree
	while(m_branches.size() > 0)
	{
		delete m_branches.back();
		m_branches.pop_back();
	}
}


void Node::GenerateMoves()
{
	bool full = true;
	//if the current node is a win or lose condition do not create more nodes
	if (m_win||m_lose)
	{
		return;
	}
	//if it is cross's turn create as many possible cross moves as is legal
	if (m_playerTurn == true)
	{
		for (int i=0; i<9; i++)
		{
			if (m_data[i] == 0)
			{
				char tempData[9];
				for (int j=0; j<9;j++)
				{
					tempData[j] = m_data[j];
				}
				tempData[i] = 1;
				m_branches.push_back(new Node(tempData, !m_playerTurn, this));
				full = false;
			}
		}
	}
	//if it is naught's turn create as many possible naught moves as is legal
	else
	{
		for (int i=0; i<9; i++)
		{
			if (m_data[i] == 0)
			{
				char tempData[9];
				for (int j=0; j<9;j++)
				{
					tempData[j] = m_data[j];
				}
				tempData[i] = -1;
				m_branches.push_back(new Node(tempData, !m_playerTurn, this));
				full = false;
			}
		}
	}
	//if new moves were created and the depth limit has not been reached reccursively generate more moves
	if ((full != true) && (m_level < 4)) 
	{
		for (auto i : m_branches)
		{
			i->GenerateMoves();
		}
	}
	//otherwise unwind reccursion by 1
	else
	{
		return;
	}
}

void Node::SetScore()
{
	//if crosses have won set the score to +10 and set win state to true
	if (((m_data[0] == 1)&&(m_data[1] == 1)&&(m_data[2] == 1))||((m_data[3] == 1)&&(m_data[4] == 1)&&(m_data[5] == 1))
		||((m_data[6] == 1)&&(m_data[7] == 1)&&(m_data[8] == 1))||((m_data[0] == 1)&&(m_data[3] == 1)&&(m_data[6] == 1))
		||((m_data[1] == 1)&&(m_data[4] == 1)&&(m_data[7] == 1))||((m_data[2] == 1)&&(m_data[5] == 1)&&(m_data[8] == 1))
		||((m_data[0] == 1)&&(m_data[4] == 1)&&(m_data[8] == 1))||((m_data[6] == 1)&&(m_data[4] == 1)&&(m_data[2] == 1)))
	{
		m_score = 10;
		m_win = true;
	}
	//if naughts have won set the score to -10 and set the win state to false
	else if (((m_data[0] == -1)&&(m_data[1] == -1)&&(m_data[2] == -1))||((m_data[3] == -1)&&(m_data[4] == -1)&&(m_data[5] == -1))
		||((m_data[6] == -1)&&(m_data[7] == -1)&&(m_data[8] == -1))||((m_data[0] == -1)&&(m_data[3] == -1)&&(m_data[6] == -1))
		||((m_data[1] == -1)&&(m_data[4] == -1)&&(m_data[7] == -1))||((m_data[2] == -1)&&(m_data[5] == -1)&&(m_data[8] == -1))
		||((m_data[0] == -1)&&(m_data[4] == -1)&&(m_data[8] == -1))||((m_data[6] == -1)&&(m_data[4] == -1)&&(m_data[2] == -1)))
	{
		m_score = -10;
		m_lose = true;
	}
	//if neither has won on this node, set score to -1 in order to encourage the AI to win as quickly as possible
	else
	{
		m_score = -1;
	}
	//if there is a parent, add this nodes score to the parent's score
	if (m_parent != nullptr)
	{
		m_parent->m_score += m_score;
	}
}

Node* Node::FindBestOfChildren()
{
	//calculate best possible next move using minimax
	int maxScore = -1000;
	Node* bestOutcome;
	for (auto i : m_branches)
	{
		if (i->m_score > maxScore)
		{
			maxScore = i->m_score;
			bestOutcome = i;
		}
	}
	return bestOutcome;
}

bool Node::PlaceMark(int _pos, bool _player)
{
	//if the chosen position already has a mark in it, do not allow the nw one to be placed
	if (m_data[_pos-1] != 0)
	{
		return false;
	}
	//otherwise place the appropriate naught or cross
	else if (_player == 0)
	{
		m_data[_pos-1] = -1;
		m_playerTurn = 1;
	}
	else
	{
		m_data[_pos-1] = 1;
		m_playerTurn = 0;
	}
	//return true on successful placement
	return true;
}

bool Node::CheckFull()
{
	bool full = true;
	//check through the data to see if the board is full
	for(auto i : m_data)
	{
		if (i == 0)
		{
			full = false;
		}
	}
	//return true or false if the board is full or not respectively
	return full;
}