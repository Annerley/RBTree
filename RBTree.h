#pragma once
#include<iostream>

using ValueType = double;
using KeyType = std::string;
class RBTree
{

public:
	struct Node 

	{
		ValueType value;
		KeyType key;
		Node* left;
		Node* right;
		bool Color; // 0 - red, 1 - black;
	};

	RBTree();
	RBTree(const RBTree& copyTree);
	RBTree& operator=(const RBTree& copyTree);

	RBTree(RBTree&& moveTree) noexcept;
	RBTree& operator=(RBTree&& moveTree) noexcept;

	~RBTree();

	void AddLeaf(KeyType key, ValueType value);

	void DeleteFirstKey(KeyType key);
	void DeleteKey(KeyType Key);

	ValueType Find(KeyType Key);

	Node* FindNodeMax(KeyType Key);
	Node* FindNodeMin(KeyType Key);

	size_t size()
	{
		return _size;
	}

	bool IsEmpty();
private:

	Node _head;
	size_t _size;
};

