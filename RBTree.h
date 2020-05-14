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
		
		Node(const ValueType& value, const KeyType& key, Node* parent);
	//	~Node();

		ValueType value;
		KeyType key;
		Node* parent;
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
	//void AddPair(KeyType key, ValueType value, Node* node); // now probably useless
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
	_head = new Node(value, key, nullptr);
}



/*template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::AddPair(KeyType key, ValueType value, Node* node)
{
	if (node->key >= key)
	{
		if (node->left == nullptr)
		{
			node->left = new Node(value, key, node);
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
			node->right = new Node(value, key, node);
		}
		else
		{
			AddPair(key, value, node->right);
		}
	}
	//rebalance
}*/

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Add(ValueType value, KeyType key)
{
	if (_head == nullptr)
	{
		_head = new Node(value, key, nullptr);
		return;
	}
	Node* Buf = _head;
	Node* parent = nullptr;
	//cout << Buf->value << " " << _head->value;

	while (true)
	{
		if (key < Buf->key)
		{
			parent = Buf;
			
			if (Buf->left == nullptr)
			{
				Buf->left = new Node(key, value, parent);
				Buf = Buf->left;
				return;
			}
			else
				Buf = Buf->left;
		}
		


		else if (key >= Buf->key)
		{
			parent = Buf;
			
			if (Buf->right == nullptr)
			{
				Buf->right= new Node(key, value, parent);
				Buf = Buf->right;
				return;
			}
			else 
				Buf = Buf->right;

		}
	
	}
/*
	Buf->value = value;
	Buf->key = key;
	Buf->parent = parent;
	Buf->right = nullptr;
	Buf->left = nullptr;*/
	_size++;
	//rebalance
	

	

}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::TestPrint()
{
	cout << _head->value << " " << _head->key << endl;
	cout << _head->left->value << " " << _head->left->key << endl;
	cout << _head->right->value << " " << _head->right->key << endl;
	cout << _head->right->right->value << " " << _head->right->right->key << endl;
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::Node::Node(const ValueType& value, const KeyType& key, Node* parent)
{
	this->value = value;
	this->key = key;
	this->color = Color::Red;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = parent;

}
