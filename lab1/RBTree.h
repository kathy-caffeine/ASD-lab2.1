#pragma once
#include "Stack.h"
#include "Stack.cpp"
#include <iostream>
using namespace std;

template <typename T>
class RBTree
{
private:
	class RBNode
	{
	public:
		RBNode(T data, T key, bool color, RBNode* parent, RBNode* left, RBNode* right) {
			this->data = data;
			this->key = key;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->color = color; // red
		};
		~RBNode() {};
		T data;
		T key;
		RBNode* parent;
		RBNode* left;
		RBNode *right;
		bool color; // true - red, false - black
	};

	class dft_Iterator // depth-first traverse
	{
	private:
		Stack<RBNode*> stack;
		RBNode* current;
		RBNode* nil;
	public:
		dft_Iterator(RBNode* root = nullptr, RBNode* nil = nullptr) {
			this->nil = nil;
			current = root;
			stack.push(current);
		}
		RBNode* next() {
			if (!has_next()) {
				throw "No more elements";
			}
			RBNode* temp = current;
			if (current->right != nil) //add right tree to stack
			{
				stack.push(current->right);
			}
			if (current->left != nil) //go left
			{
				current = current->left;
			}
			else { // if can't
				current = stack.pop();
			}
			return temp;
		}
		bool has_next() {
			if (!stack.isEmpty())
				return true;
			else
				return false;
		}
		~dft_Iterator() {};
	};

	void set_root(T key, T data) {
		RBNode* tmp = new RBNode(data, key, false, nil, nil, nil);
		root = tmp;
		root->parent = nil;
		root->color = false; // black root's color
		nil->color = false; // black nill's color
	};

	RBNode* root;
	RBNode* nil = new RBNode(0, 0, false, nil, nil, nil);
	size_t size;

public:
	RBTree() {
		root = nil;
		size = 0;
	};

	~RBTree() {
		clear();
		delete root;
		size = 0;
	};

	void left(RBNode* newNode) {
		if (newNode->right == nullptr)
			return;
		else
		{
			RBNode* y = newNode->right;
			if (y->left != nullptr)
			{
				newNode->right = y->left;
				y->left->parent = newNode;
			}
			else
				newNode->right = nullptr;
			if (newNode->parent != nullptr)
				y->parent = newNode->parent;
			if (newNode->parent == nullptr)
				root = y;
			else
			{
				if (newNode == newNode->parent->left)
					newNode->parent->left = y;
				else
					newNode->parent->right = y;
			}
			y->left = newNode;
			newNode->parent = y;
		}
	};

	void right(RBNode* newNode) {
		if (newNode->left == nullptr)
			return;
		else
		{
			RBNode* y = newNode->left;
			if (y->right != nullptr)
			{
				newNode->left = y->right;
				y->right->parent = newNode;
			}
			else
				newNode->left = nullptr;
			if (newNode->parent != nullptr)
				y->parent = newNode->parent;
			if (newNode->parent == nullptr)
				root = y;
			else
			{
				if (newNode == newNode->parent->left)
					newNode->parent->left = y;
				else
					newNode->parent->right = y;
			}
			y->right = newNode;
			newNode->parent = y;
		}
	};

	void coloring(RBNode* node) {
		if (node == root)
		{
			node->color = false;
			return;
		}
		RBNode* uncle;
		while ((node->parent->color) && (node != root)) //red parent 
		{
			if (node->parent == node->parent->parent->left) //if parent is a left child
			{
				uncle = node->parent->parent->right;
				if (uncle->color) //if uncle is red too
				{
					node->parent->color = false; //repaint parent and uncle
					uncle->color = false;
					node->parent->parent->color = true; //repaint grand parent 
					node = node->parent->parent; //check grand parent 
				}
				else { //if uncle is not red
					if (node == node->parent->right) { // if  node is a right child
						node = node->parent;
						left(node);
					}
					node->parent->color = false;
					node->parent->parent->color = true;  //repaint grand parent 
					right(node->parent->parent);
				}
			}
			else { 
				uncle = node->parent->parent->left;
				if (uncle->color)
				{
					node->parent->color = false;
					uncle->color = false;
					node->parent->parent->color = true;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						right(node);
					}
					node->parent->color = false;
					node->parent->parent->color = true;
					left(node->parent->parent);
				}
			}
		}
		root->color = false;
	}

	bool is_empty() {
		return (root == nullptr);
	};

	void insert(T key, T data) {
		if (root == nil) // add root
		{
			root = new RBNode(key, data, false, nil, nil, nil);
		}
		else {
			RBNode* newNode = new RBNode(key, data, true, nil, nil, nil);
			RBNode* parent = root;
			RBNode* leaf = nullptr;
			while (parent != nil)
			{
				leaf = parent;
				if (parent->key < newNode->key)
					parent = parent->right;
				else
					parent = parent->left;
			}
			newNode->parent = leaf;
			if (leaf != nullptr){
				if (leaf->key < newNode->key)
					leaf->right = newNode;
				else
					leaf->left = newNode;
				coloring(newNode);
			}
		}
		size++;
	};

	RBNode* find(T key) {
		RBNode* x = root;
		while (x->key != key)// find key to remove
		{
			if ((x == nil) || (x == nullptr))
			{
				throw out_of_range("Element not found");
			}
			if (x->key < key)
				x = x->right;
			else
				x = x->left;
		}

		return x;
	};

	void fix(RBNode* node) {
		if (node) {
			RBNode* brother;
			while ((node != root) && (node->color == false))
			{
				if (node == node->parent->left) //if node is a left child
				{
					brother = node->parent->right;
					if (brother->color) //if brother is red
					{
						brother->color = false;
						node->parent->color = true; //swap parent's and brother's colors
						left(node->parent);
						brother = node->parent->right;
					}
					if ((brother->left->color == false) && (brother->right->color == false)) //both brother child black
					{
						brother->color = true;
						node = node->parent;
					}
					else {
						if (brother->right->color == false)
						{
							brother->left->color = false;
							brother->color = true;
							right(brother);
							brother = node->parent->right;
						}
						brother->color = node->parent->color;
						node->parent->color = false;
						brother->right->color = false;
						left(node->parent);
						node = root;
					}
				}
				else {  //as in the previous if, but in the other direction
					brother = node->parent->left;
					if (brother->color)
					{
						brother->color = false;
						node->parent->color = true;
						right(node->parent);
						brother = node->parent->left;
					}
					if ((brother->right->color == false) && (brother->left->color == false))
					{
						brother->color = true;
						node = node->parent;
					}
					else {
						if (brother->left->color == false)
						{
							brother->right->color = false;
							brother->color = true;
							right(brother);
							brother = node->parent->left;
						}
						brother->color = node->parent->color;
						node->parent->color = false;
						brother->left->color = false;
						right(node->parent);
						node = root;
					}
				}
			}
			node->color = false; //root color
		}
	};

	void remove(T remKey) {
		RBNode* node = find(remKey);
		if (node == nullptr) return; // if there is no such node we cant delete it
		// if we had node, we can delete it
		size--;
		RBNode* nodeA;
		RBNode* nodeB;
		if ((node->left == nil) || (node->right == nil)) // if node has <2 children
			nodeA = node;
		else { 
			nodeA = node->right;
			while (nodeA->left != nil) {
				nodeA = nodeA->left; //looking for node to swap
			}
		}
		if (nodeA->left != nil) { //fix node
			nodeB = nodeA->left;
		}
		else {
			nodeB = nodeA->right;
		}

		nodeB->parent = nodeA->parent;
		if (nodeA->parent != nil) // if nodeA is not root
		{
			if (nodeA == nodeA->parent->left) {
				nodeA->parent->left = nodeB;
			}
			else {
				nodeA->parent->right = nodeB;
			}
		}
		else { // if nodeA is root
			root = nodeB;
		}
		if (nodeA != node)
		{
			node->key = nodeA->key;
			node->data = nodeA->data;
		}
		if (nodeA->color == false) //avoiding red parent
		{
			fix(nodeB);
		}
		delete nodeA;
	};

	void clear(){
		while ((root != nil) && (root != nullptr))
			remove(root->key);
		root = nil;
		size = 0;
	};

	size_t get_size() {
		return size;
	};

	T* get_keys() {
		dft_Iterator i(root, nil);
		T* arr = new T[size];
		int arrI = 0;
		RBNode* cur;
		while (i.has_next())
		{
			cur = i.next();
			arr[arrI] = cur->key;
			arrI++;
		}
		return arr;
	};

	T* get_data() {
		dft_Iterator i(root, nil);
		T* arr = new T[size];
		int arrI = 0;
		RBNode* cur;
		while (i.has_next())
		{
			cur = i.next();
			arr[arrI] = cur->data;
			arrI++;
		}
		return arr;
	};

	void print() {
		dft_Iterator i(root, nil);
		RBNode* cur;
		while (i.has_next())
		{
			cur = i.next();
			cout << cur->key << " " << endl;
		}
		cout << endl;
	};
};

