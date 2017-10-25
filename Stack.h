#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include "DynArray.h"

using namespace std;

template <typename T>
class Stack
{
private:
	DynArray<T> container;
	int indexOfTop;

public:
	Stack();

	void push(T const& value);
	T pop();
	T top() const;
	bool empty() const;
	unsigned size();
	void swap(int index1, int index2);
	void swapStack(Stack<T> &other);

	void print() const; // used for testing
};


template <typename T>
Stack<T>::Stack() : container(), indexOfTop(-1)
{}

template <typename T>
void Stack<T>::push(T const& elm)
{
	container.incrementSize();

	indexOfTop++;
	container[indexOfTop] = elm;
}

template <typename T>
T Stack<T>::pop()
{
	if (empty())
	{
		cerr << "Trying to pop the top element out of an empty stack!" << endl;
		return T();
	}
	return container[indexOfTop--];
}

template <typename T>
T Stack<T>::top() const
{
	if (empty())
	{
		cerr << "Trying to peek at the top of an empty stack!" << endl;
		return T();
	}
	return container[indexOfTop];
}

template <typename T>
bool Stack<T>::empty() const
{
	return indexOfTop == -1;
}

template <typename T>
unsigned Stack<T>::size()
{
	if (container.getSize() == 0)
	{
		indexOfTop = -1;
	}
	return container.getSize();
}

template <typename T>
void Stack<T>::swap(int index1, int index2)
{
	T temp;
	temp = container[index1];
	container[index1] = container[index2];
	container[index2] = temp;
}

template <typename T>
void Stack<T>::swapStack(Stack<T> &other)
{
	Stack<T> tempStack;
	int tempIndex = indexOfTop;
	tempStack.container = container;
	container = other.container;
	indexOfTop = other.indexOfTop;
	other.container = tempStack.container;
	other.indexOfTop = tempIndex;
}

template <typename T>
void Stack<T>::print() const
{
	if (indexOfTop == -1)
		cerr << "The stack is empty" << endl;
	else
	{
		for (int i = 0; i <= indexOfTop; ++i)
		{
			cout << container[i] << " ";
		}
		cout << endl;
	}
}

#endif