#include "stdafx.h"
#include <iostream>
#include <conio.h>

using namespace std;

struct stack					//	head 1 |
{								//		 2 V next:	  1 -> 2 -> 3 -> 4 -> 5 -> nullptr
	int data;					//		 3
	stack *next, *head;			//		 4
								//		 5
	stack()
	{
		head = nullptr;
		next = nullptr;
		data = NULL;
	}
};

void clean(stack *&myStack);
int clean(stack *&firstPoint, stack *&secondPoint);
void push(stack *&myStack, int info);
int pop(stack *myStack);
int peek(stack *myStack);
void print(stack *myStack);
int size(stack *myStack);
void sort_adress(stack *&myStack);
void sort_data(stack *&myStack);
int task9(stack *&myStack);
void ret(stack *minPointer, stack *maxPointer, stack *&st);



void clean(stack *&myStack)
{
	stack *temp = nullptr;

	while (myStack->head != nullptr)
	{
		temp = myStack->head;
		myStack->head = myStack->head->next;
		delete temp;
	}

	return;
}



int clean(stack *&firstPoint, stack *&secondPoint)
{
	if (firstPoint == secondPoint)
		return 0;

	bool trueOrder = false;
	stack *temp = firstPoint;
	while (temp->next != nullptr)
	{
		if (temp == secondPoint)
		{
			trueOrder = true;
			break;
		}
		temp = temp->next;
	}

	if (!trueOrder)
	{
		return 0;
	}

	stack *del = firstPoint->next;
	stack *last = secondPoint;
	int delNumber = 0;
	temp = nullptr;
	
	while (del != last)
	{
		temp = del;
		del = del->next;
		firstPoint->next = del;
		delete temp;
		delNumber++;
	}

	return delNumber;
}



void push(stack *&myStack, int info)		
{
	stack *newNode = new stack;
	newNode->data = info;
	newNode->next = myStack->head;
	myStack->head = newNode;

	return;
}



int pop(stack *myStack)
{
	if (size(myStack) == 0)
		return 0;
	stack *temp = myStack->head->next;
	int info = myStack->head->data;
	delete myStack->head;
	myStack->head = temp;

	return info;
}



int peek(stack *myStack)
{
	return myStack->head->data;
}



void print(stack *myStack)
{
	stack *temp = myStack->head;

	while (temp != nullptr)
	{
		cout << temp->data << " ";
		if (temp == myStack->head)			// Указывать голову			
			cout << "(head) ";				//
		temp = temp->next;
	}
	cout << endl;

	return;
}



int size(stack *myStack)
{
	if (myStack->head == nullptr)
		return 0;

	stack *temp = myStack->head;
	int counter = 0;

	while (temp != nullptr)
	{
		temp = temp->next;
		counter++;
	}

	return counter;
}



void sort_adress(stack *&myStack)
{
	if (size(myStack) == 0 || size(myStack) == 1)
		return;

	push(myStack, 0);

	stack *temp = myStack->head;
	stack *swap1 = nullptr, *swap2 = nullptr;

	for (int i = 0; i < size(myStack); i++)
	{
		temp = myStack->head;
		while (temp->next->next != nullptr)
		{
			if (temp->next->data > temp->next->next->data)
			{
				swap1 = temp->next->next;
				swap2 = temp->next->next->next;
				temp->next->next->next = temp->next;
				temp->next->next = swap2;
				temp->next = swap1;
			}
			temp = temp->next;
		}
	}

	pop(myStack);
	return;
}



void sort_data(stack *&myStack)
{
	if (size(myStack) == 0 || size(myStack) == 1)
		return;

	stack *temp = myStack->head;
	int swap;

	for (int i = 0; i < size(myStack); i++)
	{
		temp = myStack->head;
		while (temp->next != nullptr)
		{
			if (temp->data > temp->next->data)
			{
				swap = temp->data;
				temp->data = temp->next->data;
				temp->next->data = swap;
			}
			temp = temp->next;
		}
	}

	return;
}



int task9(stack *&myStack)								// Удаление всех элементов между максимальным и минимальным, возврат их количества
{
	stack *temp = myStack->head;
	stack *minPointer = nullptr, *maxPointer = nullptr;
	int max = -99999, min = 99999;
	int delNumber = 0;
	bool min_max_order = true, max_min_order = false;

	while (temp != nullptr)
	{
		if (temp->data > max)
		{
			max = temp->data;
			maxPointer = temp;
			min_max_order = true;
			max_min_order = false;
		}
		if (temp->data < min)
		{
			min = temp->data;
			minPointer = temp;
			min_max_order = false;
			max_min_order = true;
		}
		temp = temp->next;
	}

	if (maxPointer == minPointer)
		return 0;
	if (min_max_order)
	{
		stack *newStack = new stack;
		ret(minPointer, maxPointer, newStack);			// Вызывать функцию ret для максимального и минимального значения
		cout << "New stack" << endl;					//
		print(newStack);								//
		delNumber = clean(minPointer, maxPointer);
	}
	else
	{
		stack *newStack = new stack;
		ret(maxPointer, minPointer, newStack);			//
		cout << "New stack" << endl;					//
		print(newStack);								//
		delNumber = clean(maxPointer, minPointer);
	}
	return delNumber;
}



void ret(stack *minPointer, stack *maxPointer, stack *&newStack)					// Заполнение нового стека эементами старого, расположенными между двумя
{																					// заданными, без изменения адресов
	stack *temp = minPointer->next, *temp2 = newStack->head, *last = nullptr;

	newStack->head = temp;

	while (temp != maxPointer)
	{
		temp2 = temp;
		temp = temp->next;
		last = temp2;
		temp2 = temp2->next;
	}
	last->next = nullptr;

	return;
}



int main()
{
	stack *myStack = new stack;

	push(myStack, 1);
	push(myStack, 2);
	push(myStack, 4);
	push(myStack, 3);
	push(myStack, 5);
	push(myStack, 9);
	push(myStack, 4);
	push(myStack, 6);
	push(myStack, 1);
	push(myStack, 8);
	cout << "Initial stack:" << endl;
	print(myStack);

	sort_data(myStack);
	cout << "Sorted stack (data):" << endl;
	print(myStack);

	clean(myStack);
	cout << "Cleaned stack:" << endl;
	print(myStack);

	for (int i = 0; i < 10; i++)
		push(myStack, i);
	cout << "New stack:" << endl;
	print(myStack);

	sort_adress(myStack);
	cout << "Sorted stack (adress):" << endl;
	print(myStack);

	clean(myStack);
	push(myStack, 5);
	push(myStack, 5);
	push(myStack, 5);
	push(myStack, 9);
	push(myStack, 1);
	push(myStack, 2);
	push(myStack, 3);
	push(myStack, 4);
	push(myStack, 0);
	push(myStack, 5);
	cout << "New stack:" << endl;
	print(myStack);

	int delNumber = task9(myStack);
	cout << "Processed stack (deleted " << delNumber << " elements):" << endl;
	print(myStack);

	clean(myStack);
	delete myStack;
	_getch();
    return 0;
}