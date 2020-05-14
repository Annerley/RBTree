#pragma once
#include<iostream>

//using ValueType = double;
//using KeyType = std::string;
using namespace std;

enum class Color
{
	Red,
	Black
};
template <typename KeyType, typename ValueType>
class RBTree
{

public:
	
	struct Node 
	{	
		
		Node(const ValueType& value, const KeyType& key,, Node* node);
	//	~Node();

		ValueType value;
		KeyType key;
		Node* left;
		Node* right;
		Color color; // 0 - red, 1 - black; 
	};



	RBTree();
	RBTree(ValueType value, KeyType key);
	
	/*RBTree(const RBTree& copyTree);
	RBTree& operator=(const RBTree& copyTree);

	RBTree(RBTree&& moveTree) noexcept;
	RBTree& operator=(RBTree&& moveTree) noexcept;
	
	~RBTree();
	*/
	void AddPair(KeyType key, ValueType value, Node* node);
	void Add(ValueType value, KeyType key);
	/*
	void DeleteFirstKey(KeyType key);
	void DeleteKey(KeyType Key);

	size_t Find(KeyType Key);

	Node* FindNodeMax(KeyType Key);
	Node* FindNodeMin(KeyType Key);
	*/
	void TestPrint();

	size_t size()
	{
		return _size;
	}
	
	//bool IsEmpty();
private:

	Node* _head;
	size_t _size;
};


template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree()
{
	_head = nullptr;
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree(ValueType value, KeyType key)
{
	_head = new Node(value, key, 0, _head);
}



template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::AddPair(KeyType key, ValueType value, Node* node)
{
	if (node->key >= key)
	{
		if (node->left == nullptr)
		{
			node->left = new Node(value, key, 0, node->left);
		}
		else
		{
			AddPair(key, value, node->left);
		}
	}
	else
	{
		if (node->right == nullptr)
		{
			node->right = new Node(value, key, 1, node->right);
		}
		else
		{
			AddPair(key, value, node->right);
		}
	}
	//rebalance
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Add(ValueType value, KeyType key)
{
	if (_head == nullptr)
	{
		Node* newest = new Node(value, this->next);
		this->next = newest;
	}
	
	else
	{
		AddPair(value, key, _head);
	}

	_size++;

}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::TestPrint()
{
	
	cout << _head->left->value << " " << _head->left->key;
	cout << _head->right->value << " " << _head->right->key;
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::Node::Node(const ValueType& value, const KeyType& key, , Node* node)
{
	this->value = value;
	this->key = key;
	this->RB = Color::Red;
	if (dir == 0)
	{
		this->left = next;
		this->right = nullptr;
	}
	if (dir == 1)
	{
		this->left = nullptr;
		this->right = next;
	}

}
