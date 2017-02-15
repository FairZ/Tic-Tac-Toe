#ifndef _BINARYTREETEMPLATE_H_
#define _BINARYTREETEMPLATE_H_

#include<vector>
#include<iostream>

//template class for bi-directional binary tree
template <class T> class BinarySearchTree
{
	private:
		int m_level;
		T m_data;
		BinarySearchTree<T>* m_leftPointer;
		BinarySearchTree<T>* m_rightPointer;
		BinarySearchTree<T>* m_parentPointer;
	public:
		BinarySearchTree(T _data);
		BinarySearchTree(T _data, BinarySearchTree<T>* _parent);
		BinarySearchTree(T _rootData, std::vector<T> _dataList);
		~BinarySearchTree();
		void ChangeData(T _data);
		void AddChild(T _data);
		void CreateSubTree(std::vector<T> _dataList);
		void PrintTree();
};

template <class T> BinarySearchTree<T>::BinarySearchTree(T _data)
{
	//basic setup of a node given a piece of data
	m_level = 0;
	m_data = _data;
	m_rightPointer = nullptr;
	m_leftPointer = nullptr;
	m_parentPointer = nullptr;
}

template <class T> BinarySearchTree<T>::BinarySearchTree(T _data, BinarySearchTree<T>* _parent)
{
	//constructor used when adding new nodes to the tree at a given position
	m_level = _parent->m_level+1;
	m_data = _data;
	m_rightPointer = nullptr;
	m_leftPointer = nullptr;
	m_parentPointer = _parent;
}

template <class T> BinarySearchTree<T>::BinarySearchTree(T _rootData, std::vector<T> _dataList)
{
	//given a piece of root data (best if near the median value) and a vector of pieces of data
	//this constructor is used to generate an ordered binary tree
	m_level = 0;
	m_data = _rootData;
	m_rightPointer = nullptr;
	m_leftPointer = nullptr;
	m_parentPointer = nullptr;

	for(int i = 1; i < _dataList.size(); i++)
	{
		AddChild(_dataList[i]);
	}

}

template <class T> BinarySearchTree<T>::~BinarySearchTree()
{
	//cleans entire tree
	delete m_rightPointer;
	delete m_leftPointer;
}

template <class T> void BinarySearchTree<T>::ChangeData(T _data)
{
	//change data for a node
	m_data = _data;
}

template <class T> void BinarySearchTree<T>::AddChild(T _data)
{
	//adds new children to correct position in the tree when passed into the root node
	if (_data > m_data)
	{
		//if the data to be added is greater than the current data move it down the tree to the right
		//until it a space is available
		if (m_rightPointer != nullptr)
		{
			m_rightPointer->AddChild(_data);
		}
		else
		{
			m_rightPointer = new BinarySearchTree<T>(_data, this);
		}
	}
	else
	{
		//same as above but with lower numbers moving to the left
		if (m_leftPointer != nullptr)
		{
			m_leftPointer->AddChild(_data);
		}
		else
		{
			m_leftPointer = new BinarySearchTree<T>(_data, this);
		}
	}
}

template <class T> void BinarySearchTree<T>::CreateSubTree(std::vector<T> _dataList)
{
	//given a root node create a tree from it using given data
	for(int i = 0; i < _dataList.size(); i++)
	{
		AddChild(_dataList[i]);
	}
}

template <class T> void BinarySearchTree<T>::PrintTree()
{
	//print the tree in order from below the node that called the function
	if (m_leftPointer != nullptr)
	{
		m_leftPointer->PrintTree();
	}

	std::cout << m_data << std::endl;

	if (m_rightPointer != nullptr)
	{
		m_rightPointer->PrintTree();
	}
}

#endif