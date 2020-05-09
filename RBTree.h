#pragma once
#include<iostream>

using ValueType = double;
using KeyType = std::string;

enum class Color
{
	Red,
	Black
};

class RBTree
{

public:
	struct Node 

	{

		Node(const ValueType& value, const KeyType& key, bool dir);
		~Node();



		ValueType value;
		KeyType key;
		Node* left;
		Node* right;
		Color RB; // 0 - red, 1 - black; 
	};



	RBTree();
	RBTree(const RBTree& copyTree);
	RBTree& operator=(const RBTree& copyTree);

	RBTree(RBTree&& moveTree) noexcept;
	RBTree& operator=(RBTree&& moveTree) noexcept;

	~RBTree();

	void AddPair(KeyType key, ValueType value, Node node);
	AddTo(Node node, ValueType value, KeyType key);

	void DeleteFirstKey(KeyType key);
	void DeleteKey(KeyType Key);

	size_t Find(KeyType Key);

	Node* FindNodeMax(KeyType Key);
	Node* FindNodeMin(KeyType Key);

	size_t size()
	{
		return _size;
	}

	bool IsEmpty();
private:

	Node* _head;
	size_t _size;
};

