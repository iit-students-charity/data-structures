#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Tree.h"

using namespace std;



void tree::add_leaf(int new_key, string new_data)
{
	if (root == nullptr)
	{
		root = new node;
		root->key = new_key;
		root->data = new_data;
		root->right = nullptr;
		root->left = nullptr;
		return;
	}

	node *temp = root;
	node *to_leaf = nullptr;
	bool found = false;

	while (temp != nullptr && !found)
	{
		to_leaf = temp;
		if (temp->key == new_key)
		{
			throw duplikate_key_error();
			return;
		}
		else
		{
			if (temp->key > new_key)
				temp = temp->left;
			else
				temp = temp->right;
		}
	}

	if (!found)
	{
		if (to_leaf->key > new_key)
			to_leaf->left = new_leaf(new_key, new_data);
		else
			to_leaf->right = new_leaf(new_key, new_data);
	}
}

tree::node* tree::new_leaf(int new_key, string new_data)
{
	node *temp = new node;
	temp->key = new_key;
	temp->data = new_data;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}

void tree::delete_node(int removable_key)
{
	node *max_left = nullptr, *max_left_prev = nullptr, *left_branch = nullptr;
	node *prev = find_prev(removable_key);
	node *node = find_point(removable_key);
	bool del_root = false;
	if (node == nullptr)
	{
		throw not_found_error("Error: removable key was not found.");
		return;
	}
	if (prev == nullptr)
		del_root = true;

	if (is_no_son(node))
	{
		if (del_root)
		{
			delete node;
			root = nullptr;
			return;
		}
		else
		{
			if (prev->right != nullptr && prev->right->key == removable_key)
				prev->right = nullptr;
			else
				prev->left = nullptr;
			delete node;
			return;
		}
	}

	if (is_only_son(node) != nullptr)
	{
		if (del_root)
		{
			root = is_only_son(node);
			delete node;
			return;
		}
		else
		{
			if (prev->left != nullptr && prev->left->key == removable_key)
				prev->left = is_only_son(node);
			else
				prev->right = is_only_son(node);
			delete node;
			return;
		}
	}
	else
	{
		if (del_root)
		{
			max_left = node->left;
			while (max_left->right != nullptr)
				max_left = max_left->right;

			left_branch = max_left->left;
			max_left_prev = find_prev(max_left->key);
			if (max_left_prev == node)
				max_left_prev->left = left_branch;
			else
				max_left_prev->right = left_branch;

			max_left->left = node->left;
			max_left->right = node->right;

			root = max_left;

			delete node;
		}
		else
		{
			max_left = node->left;
			while (max_left->right != nullptr)
				max_left = max_left->right;

			left_branch = max_left->left;
			max_left_prev = find_prev(max_left->key);
			if (max_left_prev == node)
				max_left_prev->left = left_branch;
			else
				max_left_prev->right = left_branch;

			if (prev->left != nullptr && prev->left->key == removable_key)
				prev->left = max_left;
			else
				prev->right = max_left;

			max_left->left = node->left;
			max_left->right = node->right;

			delete node;
		}
	}
}

void tree::clear(void)
{
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		clear(root->left);
	if (root->right != nullptr)
		clear(root->right);
	delete root;
	root = nullptr;
}

void tree::clear(node *node)
{
	if (node->left != nullptr)
		clear(node->left);
	if (node->right != nullptr)
		clear(node->right);
	delete node;
}

void tree::balance(void)
{
	if (root == nullptr)
		return;

	vector<node_info> tree_list;
	node_info buffer;
	node *temp = nullptr;
	vector<int> added;
	int left, right;

	to_go.push(root);
	while (!to_go.empty())
	{
		temp = to_go.top();
		to_go.pop();
		if (temp->left != nullptr)
			to_go.push(temp->left);
		if (temp->right != nullptr)
			to_go.push(temp->right);

		buffer.key = temp->key;
		buffer.data = temp->data;
		tree_list.push_back(buffer);
	}

	for (size_t i = 0; i < tree_list.size() - 1; i++)
	{
		int k = i;
		for (size_t j = i + 1; j < tree_list.size(); j++)
		{
			if (tree_list[j].key > tree_list[k].key)
				k = j;
		}
		buffer = tree_list[k];
		tree_list[k] = tree_list[i];
		tree_list[i] = buffer;
	}

	clear();
	left = 0;
	right = tree_list.size();
	balance_add(tree_list, added, left, right);
}

void tree::balance_add(vector<node_info> list, vector<int> added, int left,  int right)
{
	if (left == right)
		return;

	int mid;
	bool add = true;

	mid = (left + right) / 2;
	for (size_t i = 0; i < added.size(); i++)
	{
		if (mid == added[i])
		{
			add = false;
			break;
		}
	}
	if (add)
	{
		add_leaf(list[mid].key, list[mid].data);
		added.push_back(mid);
		balance_add(list, added, left, mid);
		balance_add(list, added, mid, right);
	}
}



string tree::find(int wanted_key)
{
	if (root == nullptr)
	{
		throw empty_tree_error();
		return "";
	}

	node *temp = root;

	while (temp != nullptr)
	{
		if (temp->key == wanted_key)
			return temp->data;
		if (temp->key > wanted_key)
			temp = temp->left;
		else
			temp = temp->right;
	}

	throw not_found_error("Error: wanted key was not found.");
	return "";
}

tree::node* tree::find_point(int wanted_key)
{
	node *temp = root;

	while (temp != nullptr)
	{
		if (temp->key == wanted_key)
			return temp;
		if (temp->key > wanted_key)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return nullptr;
}

tree::node* tree::find_prev(int wanted_key)
{
	node *temp = root;
	node *prev = nullptr;

	while (temp != nullptr)
	{
		if (temp->key == wanted_key)
			return prev;
		prev = temp;
		if (temp->key > wanted_key)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return nullptr;
}



int tree::one_order_nodes(void)
{
	if (root == nullptr)
		return 0;

	node *node, *temp = root;
	int counter = 0;

	to_go.push(root);
	while (!to_go.empty())
	{
		node = to_go.top();
		to_go.pop();
		if (add_only_son(node))
			counter++;
	}

	return counter;
}

bool tree::add_only_son(node *node)
{
	if (node->left == nullptr && node->right != nullptr)
	{
		to_go.push(node->right);
		return true;
	}
	if (node->left != nullptr && node->right == nullptr)
	{
		to_go.push(node->left);
		return true;
	}
	if (node->left != nullptr && node->right != nullptr)
	{
		to_go.push(node->left);
		to_go.push(node->right);
		return false;
	}

	return false;
}



bool tree::is_no_son(node *node)
{
	if (node->left == nullptr && node->right == nullptr)
		return true;

	return false;
}

tree::node* tree::is_only_son(node *node)
{
	if (node->left == nullptr && node->right != nullptr)
		return node->right;
	if (node->left != nullptr && node->right == nullptr)
		return node->left;
	
	return nullptr;
}



void tree::print(void)
{
	if (root == nullptr)
	{
		cout << "Root: <none>" << endl;
		return;
	}
	node *temp = nullptr;
	
	to_go.push(root);
	while (!to_go.empty())
	{
		temp = to_go.top();
		to_go.pop();
		if (temp == root)
			cout << "Root: ";
		cout << temp->key << ": " << temp->data << endl;
		if (temp->left != nullptr)
		{
			cout << "Left: " << temp->left->key << endl;
			to_go.push(temp->left);
		}
		else
			cout << "Left: <none>" << endl;
		if (temp->right != nullptr)
		{
			cout << "Right: " << temp->right->key << endl;
			to_go.push(temp->right);
		}
		else
			cout << "Right: <none>" << endl;
		if (to_go.size() != 0)
			cout << "-----------------------------*" << endl;
	}
}

void tree::file_read(string path)
{
	ifstream file(path, ios_base::in);
	if (!file.is_open())
	{
		throw file_error();
		return;
	}
	string str;
	int key;

	while (file >> str)
	{
		key = stoi(str);
		file >> str;
		add_leaf(key, str);
	}
}



string tree::file_error::get_massage(void)
{
	return massage;
}

string tree::empty_tree_error::get_massage(void)
{
	return massage;
}

string tree::not_found_error::get_massage(void)
{
	return massage;
}

string tree::duplikate_key_error::get_massage(void)
{
	return massage;
}