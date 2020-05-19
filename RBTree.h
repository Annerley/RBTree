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
		~Node();

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
	void Delete(KeyType key)
	{
		DeleteKey(key, _head);
	}
	void DeleteKey(KeyType key, Node* node = _head);

	void DeleteNode(Node* node);
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

	void Print_Color(Node* cur);
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
	_head = new Node(value, key, nullptr, Color::Black);
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
				Buf->right= new Node(key, value, parent, Color::Red);
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
inline void RBTree<KeyType, ValueType>::DeleteKey(KeyType key, Node* node)
{
	
	if (node == nullptr) return;
	if (key > node->key)
	{
		DeleteKey(node->right->key, node->right);
	}
	if (key < node->key)
	{
		DeleteKey(node->left->key, node->left);
	}
	if (key == node->key)
	{
		DeleteNode(node);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::DeleteNode(Node* node)
{
	//если нет потомков
	if (node->left == nullptr && node->right == nullptr)
	{
		if (node->parent->left == node)
		{
			node->parent->left = nullptr;
		}
		else node->parent->right = nullptr;
		delete node;
		return;
	}

	//если 1 потомок
	if (node->left == nullptr)
	{
		Node* right = node->right;
		node->value = right->value;
		node->left = right->left;
		node->right = right->right;
		delete right;
		return;
	}
	else if(node->right == nullptr)
	{
		Node* left = node->left;
		node->value = left->value;//key
		node->left = left->left;
		node->right = left->right;
		delete left;
		return;
	}


	//если 2 потомка

	Node* n = node;
	if (n->right->left == nullptr)
	{
		n->value = n->right->value;//key??

		Node* buf = n->right->right;
		delete n->right;
		n->right = buf;
	}
	else
	{
		Node* l = n->right;
		while (l != nullptr)
		{
			l = l->left;
		}
		l = l->parent;
		n->value = l->value;  //key??
		DeleteNode(l);
	}

	
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::TestPrint()
{
	/*cout << _head->parent->value << " " << _head->parent->key << " ";
	Print_Color(_head->parent);
	cout << endl;

	cout << _head->parent->right->value << " " << _head->parent->right->key << " ";
	Print_Color(_head->parent->right);
	cout << endl;*/

	cout << _head->value << " " << _head->key << " ";
	Print_Color(_head);
	cout << endl;

	cout << _head->left->value << " " << _head->left->key << " ";
	Print_Color(_head->left);
	cout << endl;

	cout << _head->right->value << " " << _head->right->key << " ";
	Print_Color(_head->right);
	cout << endl;

	

	cout << _head->right->left->value << " " << _head->right->left->key << " ";
	Print_Color(_head->right->left);
	cout << endl;


	cout << _head->right->right->value << " " << _head->right->right->key << " ";
	Print_Color(_head->right->right);
	cout << endl;

	cout << _head->left->right->value << " " << _head->left->right->key << " ";
	Print_Color(_head->left->right);
	cout << endl;

	
	/*
	cout << _head->right->left->value << " " << _head->right->left->key << " ";
	Print_Color(_head->right->left);
	cout << endl;
	*/
	 
}




template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Rebalance(Node* cur)
{
	first_add_case(cur);
}

template<typename KeyType, typename ValueType>
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::uncle(Node* cur) const
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
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::grandpa(Node* cur) const
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
	if (cur->parent == nullptr)
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
		return;

	}
	else third_add_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::third_add_case(Node* cur)
{
	Node* u = uncle(cur);

		if ((u != nullptr) && (u->color == Color::Red))
		{
			cur->parent->color = Color::Black;
			u->color = Color::Black;
			Node* g = grandpa(cur);
			g->color = Color::Red;
			first_add_case(g);
		}
		else
		{
			fourth_add_case(cur);
		}

}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::fourth_add_case(Node* cur)
{	
		Node* g = grandpa(cur);		
		Node* p = cur->parent;

			if ((cur == cur->parent->right) && (cur->parent == g->left ))
			{
				left_rotate(cur->parent);
				cur = cur->left;
			}
			else if ((cur == cur->parent->left) && (cur->parent == g->right))
			{
				right_rotate(cur->parent);
				cur = cur->right;
			}
		fifth_add_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::fifth_add_case(Node* cur)
{
	Node* g = g = grandpa(cur);
	cur->parent->color = Color::Black;
	g->color = Color::Red;
	if ((cur == cur->parent->left) && (cur->parent == g->left))
	{
		right_rotate(g);
	}
	else if (cur == cur->parent->right && (cur->parent == g->right))
	{
		left_rotate(g);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::right_rotate(Node* cur)
{
	Node* buf = cur->left;
	if (cur->parent == nullptr)
	{
		_head = buf;
	}
	buf->parent = cur->parent;
	if (buf->parent == _head) _head = buf->parent;
	if (cur->parent != nullptr) {
		if (cur->parent->left == cur)
			cur->parent->left = buf;
		else
			cur->parent->right = buf;
	}

	cur->left = buf->right;
	if (buf->right != nullptr)
		buf->right->parent = cur;

	cur->parent = buf;
	buf->right = cur;
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::left_rotate(Node* cur)
{
	Node* buf = cur->right;
	if (cur->parent == nullptr)
	{
		_head = buf;
	}
	buf->parent = cur->parent; 

	if (cur->parent != nullptr) {
		if (cur->parent->left == cur)
			cur->parent->left = buf;
		else
			cur->parent->right = buf;
	}

	cur->right = buf->left;
	if (buf->left != nullptr)
		buf->left->parent = cur;

	cur->parent = buf;
	buf->left = cur;
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Print_Color(Node* cur)
{
	if (cur->color == Color::Red)
		std::cout << "Red";
	else if (cur->color == Color::Black)
		std::cout << "Black";
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

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация, надеюсь тут тоже ничего удалять не надо
}
