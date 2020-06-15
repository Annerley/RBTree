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

		//родственники
		Node* uncle(Node* cur) const;
		Node* grandpa(Node* cur) const;
		Node* sibling(Node* cur) const;
	};


	//тройка конструкторов
	RBTree();
	RBTree(const KeyType& key, const ValueType& value);
	
	RBTree(const RBTree& copyTree);
	
	~RBTree();
	
	//повороты от текущего узлы
	void right_rotate(Node* cur);
	void left_rotate(Node* cur);

	
	
	void add(const KeyType& key, const ValueType& value);

	//удал€ет все узлы с опр key
	void _delete(const KeyType& key)
	{
		while (boolean_find(key, _head))
		{
			delete_first_key(key, _head);
			_size--;
		}
	}

	//удал€ет первый узел с опр key
	void delete_first(const KeyType& key)
	{
		delete_first_key(key, _head);
		_size--;
	}

	//удал€ет узел
	void delete_node(Node* node);
	
	//поиск по ключу
	ValueType find(const KeyType& Key);

	//поиск максимальной и минимальной ноды по ключу
	Node* find_node_max();
	Node* find_node_min();

	//есть ли элемент с таким key
	bool boolean_find(const KeyType& Key, Node* cur);
	
	//вывод дерева
	void print()
	{
		print_tree(_head);
	}
	void print_tree(Node* node);


	size_t size() const
	{
		return _size;
	}
	
	bool IsEmpty() const
	{
		if (_head == nullptr) return true;
		return false;
	}
private:

	Node* _head;
	size_t _size;

	ValueType private_find(const KeyType& Key, Node* cur);
	

	void delete_first_key(KeyType key, Node* node);
	void rebalance_delete(Node* node);

	void print_color(Node* cur);

	void rebalance(Node* cur);

	void copy_construct(Node* cur, Node* copy);
	void destruct(Node* cur);

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
};


template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree()
{
	_head = nullptr;
	_size = 0;
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree(const KeyType& key, const ValueType& value)
{
	_head = new Node(value, key, nullptr, Color::Black);
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::RBTree(const RBTree& copyTree)
{
	this->_size = copyTree._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyTree._head->value, copyTree._head->key, nullptr, copyTree._head->color);
	
	copy_construct(_head, copyTree._head);
	
}

template<typename KeyType, typename ValueType>
inline RBTree<KeyType, ValueType>::~RBTree()
{
	destruct(_head);
}



template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::add(const KeyType& key, const ValueType& value)
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
				rebalance(Buf);
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
				rebalance(Buf);
				return;
			}
			else 
				Buf = Buf->right;
		}
	
	}
	_size++;

}


template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::delete_first_key(KeyType key, Node* node)
{
	
	if (node == nullptr) return;
	if (key > node->key)
	{
		delete_first_key(key, node->right);
	}
	if (key < node->key)
	{
		delete_first_key(key, node->left);
	}
	if (key == node->key)
	{
		delete_node(node);
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::delete_node(Node* node)
{
	//если нет потомков
	if (node->left == nullptr && node->right == nullptr)
	{

		rebalance_delete(node);
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
		rebalance_delete(right);
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
		rebalance_delete(left);
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
		rebalance_delete(n->right);
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
		
		delete_node(l);
	}

	
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::rebalance_delete(Node* node)
{
	if (node->color == Color::Black && node->right == nullptr && node->left == nullptr)
	{
		first_delete_case(node);
		
	}

}

template<typename KeyType, typename ValueType>
inline ValueType RBTree<KeyType, ValueType>::private_find(const KeyType& Key, Node* cur)
{
	if (_head != nullptr)
	{
		
		if (Key != cur->key)
		{
			if (cur->left != nullptr)
			{
				private_find(Key, cur->left);
			}
			if (cur->right != nullptr)
			{
				private_find(Key, cur->right);
			}
		}
		else if (Key == cur->key)
		{
			return cur->value;
		}
		
	}
}

template<typename KeyType, typename ValueType>
inline bool RBTree<KeyType, ValueType>::boolean_find(const KeyType& Key, Node* cur)
{
	Node* buf = cur;
	if (_head != nullptr)
	{
		if (cur == nullptr) return false;
		else if (Key == cur->key)
			return true;
		else if (Key < cur->key)
			return boolean_find(Key, cur->left);
		else if (Key >= cur->key)
			return boolean_find(Key, cur->right);
		//return false;
		

	}
}

template<typename KeyType, typename ValueType>
inline ValueType RBTree<KeyType, ValueType>::find(const KeyType& Key)
{
	return private_find(Key, _head);
}

template<typename KeyType, typename ValueType>
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::find_node_max()
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
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::find_node_min()
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
inline void RBTree<KeyType, ValueType>::print_tree(Node* node)
{
	if (_head != nullptr)
	{
		cout << node->value << " " << node->key;
		print_color(node);
		cout << endl;
		if (node->left != nullptr)
		{
			print_tree(node->left);
		}
		if (node->right != nullptr)
		{
			print_tree(node->right);
		}
	}

}




template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::rebalance(Node* cur)
{
	first_add_case(cur);
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::copy_construct(Node* cur, Node* copy)
{
	if (copy != nullptr)
	{
		cur->left = copy->left;
		cur->right = copy->right;
		cur->value = copy->value;
		cur->key = copy->key;
		cur->color = copy->color;
		cur->parent = copy->parent;
		if (copy->left != nullptr)
		{
			return copy_construct(cur->left, copy->left);
		}
		if (copy->right != nullptr)
		{
			return copy_construct(cur->right, copy->right);
		}
	}
}

template<typename KeyType, typename ValueType>
inline void RBTree<KeyType, ValueType>::destruct(Node* cur)
{
	if (cur != nullptr)
	{
		if (cur->left != nullptr)
		{
			return destruct(cur->left);
		}
		if (cur->right != nullptr)
		{
			return destruct(cur->right);
		}
		delete cur;
	}
	
}

template<typename KeyType, typename ValueType>
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::Node::uncle(Node* cur) const
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
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::Node::grandpa(Node* cur) const
{
	if (!cur || !cur->parent)
	{
		return nullptr;
	}
	return cur->parent->parent;
}

template<typename KeyType, typename ValueType>
inline typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::Node::sibling(Node* cur) const
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
	Node* u = cur->uncle(cur);

		if ((u != nullptr) && (u->color == Color::Red))
		{
			cur->parent->color = Color::Black;
			u->color = Color::Black;
			Node* g = cur->grandpa(cur);
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
		Node* g = cur->grandpa(cur);
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
	Node* g = g = cur->grandpa(cur);
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
	Node* s = cur->sibling(cur);
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
	Node* s = cur->sibling(cur);
	
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
	Node* s = cur->sibling(cur);
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
	Node* s = cur->sibling(cur);
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
	Node* s = cur->sibling(cur);
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
inline void RBTree<KeyType, ValueType>::print_color(Node* cur)
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
	// ничего не удал€ем, т.к. агрегаци€, надеюсь тут тоже ничего удал€ть не надо
}
