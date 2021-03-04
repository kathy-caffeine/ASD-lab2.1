#pragma once
template <typename T>
class RBTree
{
private:
	class RBNode
	{
	public:
		RBNode(T data, T key, RBNode* parent, RBNode* left, RBNode right) {
			this->data = data;
			this->key = key;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->color = true; // red
		};
		~RBNode() {
			delete;
		};
		T data;
		T key;
		RBNode* parent;
		RBNode* left, * right;
		bool color; // true - red, false - black
	};
	void add_first(T key, T data);

public:
	void insert(T key, T data);
	void remove(T key);
	T find(T key);
	void clear();
	void get_keys();
	void get_values();
	void print();
};

