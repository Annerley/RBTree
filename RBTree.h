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
	RBTree(KeyType key, ValueType value);
	
	/*RBTree(const RBTree& copyTree);
	RBTree& operator=(const RBTree& copyTree);

	RBTree(RBTree&& moveTree) noexcept;
	RBTree& operator=(RBTree&& moveTree) noexcept;
	
	~RBTree();
	*/
	
	void Add(const ValueType& value, const KeyType& key);
	void Delete(KeyType key)
	{
		while (BooleanFind(key, _head))
		{
			DeleteFirstKey(key, _head);
		}
	}

	void DeleteFirst(KeyType key)
	{
		DeleteFirstKey(key, _head);
	}

	void DeleteNode(Node* node);
	
	
	ValueType Find(const KeyType& Key);

	Node* FindNodeMax();
	Node* FindNodeMin();

	bool BooleanFind(const KeyType& Key, Node* cur);
	bool a(KeyType Key)
	{
		return BooleanFind(Key, _head);
	}
	
	void Print()
	{
		PrintTree(_head);
	}
	void PrintTree(Node* node);

	Node* uncle(Node* cur) const;
	Node* grandpa(Node* cur) const;
	Node* sibling(Node* cur) const;
	

	void first_add_case(Node* cur);
	void second_add_case(Node* cur);
	void third_add_case(Node* cur);
	void fourth_add_case(Node* cur);
	void fifth_add_case(Node* cur);

	void first_delete_case(Node* cur);
	void second_delete_case(Node* cur);
	void third_delete_case(Node* cur);
	void fourth_delete_case(Node* cur);
	void fifth_delete_case(Node* cur);
	void sixth_delete_case(Node* cur);

	
	void right_rotate(Node* cur);
	void left_rotate(Node* cur);


	size_t size()
	{
		return _size;
	}
	
	bool IsEmpty()
	{
		if (_head == nullptr) return true;
		return false;
	}
private:

	Node* _head;
	size_t _size;

	ValueType PrivateFind(const KeyType& Key, Node* cur);
	

	void DeleteAllKey(KeyType key);
	void DeleteFirstKey(KeyType key, Node* node = _head);
	void RebalanceDelete(Node* node);

	void Print_Color(Node* cur);

	void Rebalance(Node* cur);
};


template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree()
{
	_head = nullptr;
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree(KeyType key, ValueType value)
{
	_head = new Node(value, key, nullptr, Color::Black);
}



template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::Add(const ValueType& value, const KeyType& key)
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
inline void RBTree<KeyType, ValueType>::DeleteAllKey(KeyType key)
{
	while (BooleanFind(key))
	{

	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::DeleteFirstKey(KeyType key, Node* node)
{
	
	if (node == nullptr) return;
	if (key > node->key)
	{
		DeleteFirstKey(key, node->right);
	}
	if (key < node->key)
	{
		DeleteFirstKey(key, node->left);
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

		RebalanceDelete(node);
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
		node->key = right->key;
		node->left = right->left;
		node->right = right->right;
		RebalanceDelete(right);
		delete right;
		return;
	}
	else if(node->right == nullptr)
	{
		Node* left = node->left;
		node->value = left->value;
		node->key = left->key;
		node->left = left->left;
		node->right = left->right;
		RebalanceDelete(left);
		delete left;
		return;
	}


	//если 2 потомка

	Node* n = node;
	if (n->right->left == nullptr)
	{
		n->value = n->right->value;
		n->key = n->right->key;
		Node* buf = n->right->right;
		RebalanceDelete(n->right);
		delete n->right;
		n->right = buf;
		return;
	}
	else
	{
		Node* l = n->right;
		while (l->left != nullptr)
		{
			l = l->left;
		}
	
		n->value = l->value;
		n->key = l->key;
		
		DeleteNode(l);
	}

	
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::RebalanceDelete(Node* node)
{
	if (node->color == Color::Black && node->right == nullptr && node->left == nullptr)
	{
		first_delete_case(node);
		
	}

}

template<typename KeyType, typename ValueType>
inline ValueType RBTree<KeyType, ValueType>::PrivateFind(const KeyType& Key, Node* cur)
{
	if (_head != nullptr)
	{
		
		if (Key != cur->key)
		{
			if (cur->left != nullptr)
			{
				PrivateFind(Key, cur->left);
			}
			if (cur->right != nullptr)
			{
				PrivateFind(Key, cur->right);
			}
		}
		else if (Key == cur->key)
		{
			return cur->value;
		}
		
	}
}

template<typename KeyType, typename ValueType>
inline bool RBTree<KeyType, ValueType>::BooleanFind(const KeyType& Key, Node* cur)
{
	Node* buf = cur;
	if (_head != nullptr)
	{
		if (cur == nullptr) return false;
		else if (Key == cur->key)
			return true;
		else if (Key < cur->key)
			return BooleanFind(Key, cur->left);
		else if (Key >= cur->key)
			return BooleanFind(Key, cur->right);
		//return false;
		

	}
}

template<typename KeyType, typename ValueType>
inline ValueType RBTree<KeyType, ValueType>::Find(const KeyType& Key)
{
	return PrivateFind(Key, _head);
}

template<typename KeyType, typename ValueType>
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::FindNodeMax()
{
	Node* buf = _head;
	while (buf->right)
	{
		buf = buf->right;
	}
	cout << buf->value;
	return buf;
}

template<typename KeyType, typename ValueType>
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::FindNodeMin()
{
	Node* buf = _head;
	while (buf->left)
	{
		buf = buf->left;
	}
	cout << buf->value;
	return buf;
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::PrintTree(Node* node)
{
	if (_head != nullptr)
	{
		cout << node->value << " " << node->key;
		Print_Color(node);
		cout << endl;
		if (node->left != nullptr)
		{
			PrintTree(node->left);
		}
		if (node->right != nullptr)
		{
			PrintTree(node->right);
		}
	}

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
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::sibling(Node* cur) const
{
	Node* g = grandpa(cur);
	if (!cur || !cur->parent)
	{
		return nullptr;
	}
	if (cur->parent->right == cur)
	{
		return cur->parent->left;
	}
	else return cur->parent->right;
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
inline void RBTree<KeyType, ValueType>::first_delete_case(Node* cur)
{

	if (cur->parent != nullptr)
	{
		second_delete_case(cur);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::second_delete_case(Node* cur)
{
	Node* s = sibling(cur);
	Node* p = cur->parent;
	if (s->color == Color::Red)
	{
		p->color = Color::Red;
		s->color = Color::Black;
		if (p->left == cur)
		{
			left_rotate(cur->parent);
		}
		else right_rotate(cur->parent);
	}
	
	third_delete_case(cur);

}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::third_delete_case(Node* cur)
{
	Node* s = sibling(cur);
	
	if ((cur->parent->color == Color::Black) && (s->color == Color::Black) &&(!s->left || s->left->color==Color::Black) && (!s->right || s->right->color == Color::Black))
	{
		s->color = Color::Red;
		first_delete_case(cur->parent);
	}
	else fourth_delete_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::fourth_delete_case(Node* cur)
{
	Node* s = sibling(cur);
	if (cur->parent->color == Color::Red && s->color == Color::Black && (!s->left || s->left->color == Color::Black) && (!s->right || s->right->color == Color::Black))
	{
		s->color = Color::Red;
		cur->parent->color = Color::Black;
	}
	else fifth_delete_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::fifth_delete_case(Node* cur)
{
	Node* s = sibling(cur);
	if (s->color == Color::Black)
	{
		if (cur->parent->left == cur && (!s->left || s->left->color == Color::Red) && (!s->right || s->right->color == Color::Black))
		{
			s->color = Color::Red;
			s->left->color = Color::Black;
			right_rotate(s);
		}
		else if (cur->parent->right == cur && (!s->left || s->left->color == Color::Black) && (!s->right || s->right->color == Color::Red))
		{
			s->color = Color::Red;
			s->right->color = Color::Black;
			left_rotate(s);
		}
		
	}
	sixth_delete_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::sixth_delete_case(Node* cur)
{
	Node* s = sibling(cur);
	s->color = cur->parent->color;
	cur->parent->color = Color::Black;
	if (cur->parent->left == cur)
	{
		s->right->color = Color::Black;
		left_rotate(cur->parent);
	}
	else
	{
		s->left->color = Color::Black;
		right_rotate(cur->parent);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::right_rotate(Node* cur)
{
	Node* buf = cur->left;
	
	if (cur->parent == nullptr)
	{
		_head = buf;
		_head->left = buf->left;
		_head->right = buf->right;
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
		_head->left = buf->left;
		_head->right = buf->right;
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
