#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "DynArray.h"

using namespace std;

template<typename T>
class Queue
{
private:
	DynArray<T> container;
	int head, tail;

	void shiftLeft();

public:
	Queue();

	bool empty() const;
	unsigned size();
	T front() const;
	T back() const;
	void push(const T& elm);
	T pop();
	void swap(int indexFirst, int indexSecond);
	void swapQueue(Queue<T> &other);

	void print() const; // used for testing
};

template<typename T>
Queue<T>::Queue() : container(), head(-1), tail(-1)
{}

template<typename T>
bool Queue<T>::empty() const
{
	return tail == -1;
}

template<typename T>
unsigned Queue<T>::size()
{
	if (container.getSize() == 0)
	{
		head = -1;
		tail = -1;
	}

	return container.getSize();
}

template<typename T>
T Queue<T>::front() const
{
	if (!empty())
	{
		return container[head];
	}
	else
	{
		cerr << "The queue is empty!" << endl;
		return T();
	}
}

template<typename T>
T Queue<T>::back() const
{
	if (!empty())
	{
		return container[tail];
	}
	else
	{
		cerr << "The queue is empty!" << endl;
		return T();
	}
}

template<typename T>
void Queue<T>::push(const T& elm)
{
	container.incrementSize();

	if (!empty())
	{
		container[++tail] = elm;
	}
	else
	{
		head = 0;
		tail = 0;
		container[tail] = elm;
	}
}

template<typename T>
T Queue<T>::pop()
{
	T x;
	if (!empty())
	{
		x = container[head];
		shiftLeft(); 
		/* 
		   We know that moving all the elements of the queue to the very 
		   beginning each time the head is poped out leads to a O(n^2) 
		   complexity but this was the only way to cope with the mess caused 
		   by the use of a circular queue and an expanding (dynamic) array
		   at the same time. Otherwise we would have a huge unused gap at 
		   the beginning of the queue's container which is a waste of precious 
		   memory. We are open for a better solution :)
		*/
		container.decrementSize();

		return x;
	}
	else
	{
		cerr << "The queue is empty!" << endl;
		return T();
	}
}

template<typename T>
void Queue<T>::swap(int indexFirst, int indexSecond)
{
	T temp = container[indexFirst];
	container[indexFirst] = container[indexSecond];
	container[indexSecond] = temp;
}

template<typename T>
void Queue<T>::swapQueue(Queue<T> &other)
{
	Queue <T> temp;
	temp.container = container;
	temp.head = head;
	temp.tail = tail;
	container = other.container;
	other.container = temp.container;
	head = other.head;
	other.head = temp.head;
	tail = other.tail;
	other.tail = temp.tail;
}

/* ANOTHER IDEA FOR THE FUNCTION swapQueue (but we had some problems with it)

template<typename T>
void Queue<T>::swapQueue(Queue<T> &other)
{
	int countElemQueue = size();
	int countElemOtherQueue = other.size();

	//while there are elements at least in one of the two queues
	while ((countElemQueue || countElemOtherQueue) && countElemQueue >= 0 && countElemOtherQueue >= 0)
	{
		// movе one element at a time from the head of this queue to the tail of the other queue
		if (!empty())
		{
			if (countElemQueue && !other.empty())
			{
				other.push(pop());
			}
			countElemQueue--;
		}
		else // if this queue is empty
		{
			// take all the elements of the other
			container = other.container;

			//delete all the elements of the other queue
			while (!other.empty())
			{
				other.pop();
			}
			// now this queue has elements and the other is empty
			break;

		}

		// movе one element at a time from the head of the other queue to the tail of this queue
		if (!other.empty())
		{
			if (countElemOtherQueue && !empty())
			{
				push(other.pop());
			}
			countElemOtherQueue--;

		}
		else // if the other queue is empty
		{
			// then it takes all the elements of this queue
			other.container = container;

			//delete all elements from this queue
			while (!empty())
			{
				pop();
			}
			// now the other queue has elements and this one is empty
			break;
		}
	}
}
*/

template<typename T>
void Queue<T>::print() const
{
	int size = container.getSize();

	if (size == 0)
	{
		cerr << "The queue is empty!" << endl;
	}
	else
	{
		for (int i = 0; i <size; i++)
		{
			cout << container[i] << " ";
		}
		cout << endl;
	}

}

template<typename T>
void Queue<T>::shiftLeft()
{
	int size = container.getSize();

	for (int i = 0; i < size - 1; i++)
	{
		container[i] = container[i + 1];
	}
	tail--;
}
#endif
