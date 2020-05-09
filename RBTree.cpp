#include "RBTree.h"

RBTree::RBTree()
{
	_head = nullptr;

}

void RBTree::AddPair(KeyType key, ValueType value, Node* node)
{
	
	if (node->key >= key)
	{
		if (node->left == 0)
		{
			node->left = new Node(value, key, 0);
		}
		else
		{
			AddPair();
		}
	}

}


RBTree::Node::Node(const ValueType& value, const KeyType& key, bool dir)
{
	this->value = value;
	this->key = key;
	if (dir == 0)
	{
		this->left = left;
		this->right = nullptr;
	}
	if (dir == 1)
	{
		this->left = nullptr;
		this->right = right;
	}
}
