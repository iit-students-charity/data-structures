#pragma once

#include <string>
#include <stack>
#include <vector>

using namespace std;



class tree
{
public:
	tree()
	{
		root = nullptr;
	}
	~tree()
	{
		clear();
		for (size_t i = 0; i < to_go.size(); i++)
			to_go.pop();
	}

	void file_read(string path);
	void add_leaf(int new_key, string new_data);
	void delete_node(int removable_key);
	void balance(void);
	void clear(void);

	string find(int wanted_key);
	int one_order_nodes(void);

	void print(void);
	


	class error : public exception
	{
	public:
		error()
		{
			status = "Something wrong.";
		}
		string status;
	};
	class file_error : public error
	{
	public:
		file_error()
		{
			massage = "Error: file was not open.";
		}
		file_error(string massage)
		{
			this->massage = massage;
		}
		string get_massage(void);
	private:
		string massage;
	};
	class empty_tree_error : public error
	{
	public:
		empty_tree_error()
		{
			massage = "Error: the tree is empty.";
		}
		empty_tree_error(string massage)
		{
			this->massage = massage;
		}
		string get_massage(void);
	private:
		string massage;
	};
	class not_found_error : public error
	{
	public:
		not_found_error()
		{
			massage = "Error: object not found.";
		}
		not_found_error(string massage)
		{
			this->massage = massage;
		}
		string get_massage(void);
	private:
		string massage;
	};
	class duplikate_key_error : public error
	{
	public:
		duplikate_key_error()
		{
			massage = "Error: duplikate key.";
		}
		duplikate_key_error(string massage)
		{
			this->massage = massage;
		}
		string get_massage(void);
	private:
		string massage;
	};
	
private:
	struct node
	{
		int key;
		string data;
		node* left;
		node* right;
	};
	struct node_info
	{
		int key;
		string data;
	};
	node *root;
	stack<node*> to_go;



	node* new_leaf(int new_key, string new_data);
	void clear(node *node);
	void balance_add(vector<node_info> list, vector<int> added, int left, int right);

	node* find_point(int wanted_key);
	node* find_prev(int wanted_key);

	bool add_only_son(node *node);
	bool is_no_son(node *node);
	node* is_only_son(node *node);
};