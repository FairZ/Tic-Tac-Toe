#ifndef _TREE_H_
#define _TREE_H_

#include<vector>
#include <iostream>

//Node class containing references to parent of node and it's children
//has a number of functions for accessing and editing node data outside of the node class
class Node
{
private:
	char m_data[9];
	bool m_playerTurn;
	std::vector<Node*> m_branches;
	Node* m_parent;
	int m_level;
	int m_score;
	bool m_win;
	bool m_lose;
public:
	Node(Node* _copy);
	Node(char _data[9], bool _playerTurn ,Node* _parent);
	Node();
	~Node();
	char* GetData(){return m_data;}
	int GetLevel(){return m_level;}
	Node* GetParent(){return m_parent;}
	int GetScore(){return m_score;}
	void GenerateMoves();
	bool CheckFull();
	bool PlaceMark(int _pos, bool _player);
	void SetScore();
	Node* FindBestOfChildren();
};

#endif