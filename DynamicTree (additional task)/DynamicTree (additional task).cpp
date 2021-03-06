#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Tree.h"

using namespace std;

void print_options(void);

int main()
{
	tree bereza;
	char option;
	bool exit = false;
	int key;
	string data, path;

	while (!exit)
	{
		print_options();
		cout << "#============== Current tree ===============#" << endl;
		bereza.print();
		cout << "#===========================================#" << endl;
		option = _getch();
		switch (option)
		{
		case '1':
			try
			{
				cout << "Input new key: ";
				cin >> key;
				cout << "Input new data: ";
				cin >> data;
				bereza.add_leaf(key, data);
			}
			catch (tree::duplikate_key_error error)
			{
				cout << error.get_massage() << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::error error)
			{
				cout << error.status << endl;
				cout << "Press any key...";
				_getch();
			}
			break;
		case '2':
			cout << "Input key to delete: ";
			cin >> key;
			try
			{
				bereza.delete_node(key);
			}
			catch (tree::not_found_error error)
			{
				cout << error.get_massage() << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::error error)
			{
				cout << error.status << endl;
				cout << "Press any key...";
				_getch();
			}
			break;
		case '3':
			cout << "Input path to file: ";
			cin >> path;
			try
			{
				bereza.clear();
				bereza.file_read(path);
			}
			catch (tree::file_error error)
			{
				cout << error.get_massage() << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::error error)
			{
				cout << error.status << endl;
				cout << "Press any key...";
				_getch();
			}
			break;
		case '4':
			bereza.clear();
			break;
		case '5':
			try
			{
				bereza.balance();
			}
			catch (tree::error error)
			{
				cout << error.status << endl;
				cout << "Press any key...";
				_getch();
			}
			break;
		case '6':
			cout << "Input key to find: ";
			cin >> key;
			try
			{
				cout << "Data in key " << key << " is: " << bereza.find(key) << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::empty_tree_error error)
			{
				cout << error.get_massage() << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::not_found_error error)
			{
				cout << error.get_massage() << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::error error)
			{
				cout << error.status << endl;
				cout << "Press any key...";
				_getch();
			}
			break;
		case '7':
			try
			{
				cout << "One order nodes: " << bereza.one_order_nodes() << endl;
				cout << "Press any key...";
				_getch();
			}
			catch (tree::error error)
			{
				cout << error.status << endl;
				cout << "Press any key...";
				_getch();
			}
			break;
		case '0':
			exit = true;
			break;
		default:
			break;
		}
	}
	bereza.clear();
	return 0;
}



void print_options(void)
{
	system("cls");
	cout << "#================= Options =================#" << endl;
	cout << "<1> - Add new leaf" << endl;
	cout << "<2> - Delete node" << endl;
	cout << "<3> - Load tree from the file" << endl;
	cout << "<4> - Clear tree" << endl;
	cout << "<5> - Balance tree" << endl;
	cout << "<6> - Find data by key" << endl;
	cout << "<7> - Count one order nodes" << endl;
	cout << "<0> - Exit" << endl;
}