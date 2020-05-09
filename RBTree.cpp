#include "RBTree.h"

RBTree::RBTree()
{
	_head = nullptr;

}

void RBTree::AddPair(KeyType key, ValueType value, Node* node) // now its for bst will be fixed soon
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

}


RBTree::Node::Node(const ValueType& value, const KeyType& key, bool dir, Node* node)
{
	this->value = value;
	this->key = key;
	if (dir == 0)
	{
		this->left = node;
		this->right = nullptr;
	}
	if (dir == 1)
	{
		this->left = nullptr;
		this->right = node;
	}
}
