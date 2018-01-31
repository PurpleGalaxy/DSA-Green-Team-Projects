#ifndef DYNARRAY_H
#define DYNARRAY_H

#include<iostream>

using namespace std;

template <typename T>
class DynArray
{
private:
	unsigned int size;
	unsigned int capacity;
	T* content;

	void copy(const DynArray<T>& other);
	void destroy();

public:
	DynArray();
	DynArray(const DynArray<T>& other);
	DynArray<T>& operator=(const DynArray<T>& other);
	~DynArray();

	void incrementSize();
	void decrementSize();
	int getSize() const;
	int getCapacity() const;
	T& operator[] (int n) const;

	void resize();
	bool empty() const;
};

template<typename T>
void DynArray<T>::copy(const DynArray<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	content = new T[capacity];

	for (int i = 0; i < size; i++)
	{
		content[i] = other.content[i];
	}
}

template<typename T>
void DynArray<T>::destroy()
{
	delete[] content;
}


template<typename T>
DynArray<T>::DynArray()
{
	size = 0;
	capacity = 4;
	content = new T[capacity];
}

template<typename T>
DynArray<T>::DynArray(const DynArray<T>& other)
{
	copy(other);
}

template<typename T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

template<typename T>
DynArray<T>::~DynArray()
{
	destroy();
}

template<typename T>
int DynArray<T>::getSize() const
{
	return size;
}

template<typename T>
int DynArray<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
T& DynArray<T>::operator[] (int n) const
{
	if (n >= 0)
	{
		return content[n];
	}
	else
	{
		cerr << "Invalid index" << endl;
		exit(1);
	}

}

template<typename T>
void DynArray<T>::resize()
{
	int oldCapacity = capacity;
	T* temp = content;
	capacity *= 2;
	content = new T[capacity];

	for (int i = 0; i < oldCapacity; i++)
	{
		content[i] = temp[i];
	}

	delete[] temp;
}

template<typename T>
bool DynArray<T>::empty() const
{
	return size == 0;
}

template<typename T>
void DynArray<T>::incrementSize()
{
	if (size == capacity)
	{
		resize();
		size++;
	}
	else
		size++;
}

template<typename T>
void DynArray<T>::decrementSize()
{
	size--;
}

#endif