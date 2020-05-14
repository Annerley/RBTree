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
		
		Node(const ValueType& value, const KeyType& key, Node* parent, Color color = Color::Red);
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
	Node* FindNodeMin(KeyType Key);*/
	
	void TestPrint();
	void Rebalance(Node* cur);

	Node* uncle(Node* cur) const;
	Node* grandpa(Node* cur) const;
	

	void first_add_case(Node* cur);
	void second_add_case(Node* cur);
	void third_add_case(Node* cur);
	void fourth_add_case(Node* cur);
	void fifth_add_case(Node* cur);
	
	void right_rotate(Node* cur);
	void left_rotate(Node* cur);

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



template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Add(ValueType value, KeyType key)
{
	if (_head == nullptr)
	{
		_head = new Node(value, key, nullptr, Color::Black);
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
				_size++;
				Rebalance(Buf);
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
				_size++;
				Rebalance(Buf);
				return;
			}
			else 
				Buf = Buf->right;

		}
	
	}

}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::TestPrint()
{
	cout << _head->value << " " << _head->key << " "<<_head->color << endl;
	cout << _head->left->value << " " << _head->left->key << " " << _head->left->color << endl;
	cout << _head->right->value << " " << _head->right->key << " " << _head->right->color << endl;
	cout << _head->right->right->value << " " << _head->right->right->key << " " << _head->right->right->color << endl;
}




template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Rebalance(Node* cur)
{
	first_add_case(cur);
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::uncle(Node* cur) const
{
	Node* g = grandpa(cur);
	if(!g)
	{
		return nullptr;
	}
	if (cur->parent == g->right)
	{
		return g->left;
	}
	else return g->right;
}

template<typename KeyType, typename ValueType>
inline Node* RBTree<KeyType, ValueType>::grandpa(Node* cur) const
{
	if (!cur || !cur->parent)
	{
		return nullptr;
	}
	return cur->parent->parent;
}



template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::first_add_case(Node* cur)
{
	if (cur == _head)
	{
		cur->color = Color::Black;
	}
	else second_add_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::second_add_case(Node* cur)
{
	if (cur->parent->color == Color::Black)
	{
		third_add_case(cur);

	}
	else return;
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::third_add_case(Node* cur)
{
	Node* u = new Node;
	u = uncle(cur);
	if (u && cur->parent->color == Color::Red)
	{
		if (u != nullptr && u->color == Color::Red)
		{
			cur->parent->color = Color::Black;
			u->color = Color::Black;
			Node* g = new Node;
			g = grandpa(cur);
			g->color = Color::Red;
			first_add_case(g);
		}
		else
		{
			fourth_add_case(cur);
		}
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::fourth_add_case(Node* cur)
{
	Node* u = new Node;
	u = uncle(cur);
	if (u == Color::Black && cur->parent == Color::Red)
	{
		Node* g = new Node;
		g = grandpa(cur);
		Node* p = new Node;
		p = cur->parent;
		if (cur == p->right && p == g->left)
		{
			left_rotate(p);
			cur = cur->left;
		}
		else if (cur == p->left && p == g->right)
		{
			right_rotate(p);
			cur = cur->right;
		}
		fifth_add_case(cur);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::fifth_add_case(Node* cur)
{
	Node* g = new Node;
	g = grandpa(cur);
	cur->parent->color = Color::Black;
	g->color = Color::Red;
	if (cur == cur->parent->left && node->parent == g->left)
	{
		right_rotate(g);
	}
	else
	{
		left_rotate(g);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::right_rotate(Node* cur)
{
	Node buf = cur->left;
	cur->left = buf->right;
	buf->right = cur;
	return buf;
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::left_rotate(Node* cur)
{
	Node buf = cur->right;
	cur->right = buf->left;
	buf->left = cur;
	return buf;
}





template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::Node::Node(const ValueType& value, const KeyType& key, Node* parent, Color color)
{
	this->value = value;
	this->key = key;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = parent;

}
