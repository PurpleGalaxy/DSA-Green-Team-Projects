#ifndef LINK_LIST_H
#define LINK_LIST_H

template <class T>
struct elem_link {
	T inf;
	elem_link<T> *link;
};
template <class T>
class LList
{
private:
	elem_link<T> *start;
	elem_link<T> *end;
	elem_link<T> *current;
	void CopyList(LList<T> const &);
	void DeleteList();

public:
	LList();
	LList(LList<T> const &);
	LList& operator= (LList<T> const &);
	~LList();
	void IterStart(elem_link<T> *p = NULL);
	elem_link<T>* Iter();
	void ToEnd(T const &);
	void InsertAfter(elem_link<T>*, T const &);
	void InsertBefore(elem_link<T>*, T const &);
	bool DeleteAfter(elem_link<T>*, T &);
	bool DeleteBefore(elem_link<T>*, T &);
	void DeleteElem(elem_link<T>*, T &);
	void print();
	int length();
	void concat(LList<T> const& list);
};

template <class T>
LList<T>::LList()
{
	start = NULL;
	end = NULL;
}

template <class T>
LList<T>::~LList()
{
	DeleteList();
}

template <class T>
LList<T>::LList(LList<T> const & list)
{
	CopyList(list);
}

template <class T>
LList<T>& LList<T>::operator=(LList<T> const & list)
{
	if (this != &list)
	{
		DeleteList();
		CopyList(list);
	}
	return *this;
}

template <class T>
void LList<T>::DeleteList()
{
	elem_link<T> *p;
	while (start) {
		p = start;
		start = start->link;
		delete p;
	}
	end = NULL;
}

///
/// Copies all elements of a list
///
template <class T>
void LList<T>::CopyList(LList<T> const & list)
{
	start = end = NULL;
	if (list.start) {
		elem_link<T> *p = list.start;
		while (p) {
			ToEnd(p->inf);
			p = p->link;
		}
	}
}

template <class T>
void LList<T>::IterStart(elem_link<T> *p)
{
	if (p) current = p;
	else current = start;
}
template <class T>
elem_link<T>* LList<T>::Iter()
{
	elem_link<T> *p = current;
	if (current) current = current->link;
	return p;
}

template <class T>
void LList<T>::ToEnd(T const & x)
{
	current = end;
	end = new elem_link<T>;
	end->inf = x;
	end->link = NULL;
	if (current) current->link = end;
	else start = end;
}

template <class T>
void LList<T>::InsertAfter(elem_link<T> *p, T const & x)
{
	elem_link<T> *q = new elem_link<T>;
	q->inf = x;
	q->link = p->link;
	if (p == end) end = q;
	p->link = q;
}

template <class T>
void LList<T>::InsertBefore(elem_link<T> *p, T const & x)
{
	elem_link<T> *q = new elem_link<T>;
	*q = *p;
	if (p == end) end = q;
	p->inf = x;
	p->link = q;
}

template <class T>
bool LList<T>::DeleteAfter(elem_link<T> *p, T & x)
{
	if (p->link) {
		elem_link<T> *q = p->link;
		x = q->inf;
		p->link = q->link;
		if (q == end) end = p;
		delete q;
		return 1;
	}
	return 0;
}

template <class T>
void LList<T>::DeleteElem(elem_link<T> *p, T & x)
{
	if (p == start) {
		x = p->inf;
		if (start == end) {
			start = end = NULL;
		}
		else start = start->link;
		delete p;
	}
	else {
		elem_link<T> *q = start;
		while (q->link != p) q = q->link;
		DeleteAfter(q, x);
	}
}

template <class T>
bool LList<T>::DeleteBefore(elem_link<T> *p, T & x)
{
	if (p != start) {
		elem_link<T> *q = start;
		while (q->link != p) q = q->link;
		DeleteElem(q, x);
		return 1;
	}
	return 0;
}
template <class T>
void LList<T>::print()
{
	elem_link<T>* p = start;
	while (p) {
		cout << p->inf << " ";
		p = p->link;
	}
	cout << endl;
}

template <class T>
int LList<T>::length()
{
	int n = 0;
	elem_link<T>* p = start;
	while (p) {
		n++;
		p = p->link;
	}
	return n;
}
template <class T>
void LList<T>::concat(LList<T> const & list)
{
	elem_link<T> *p = list.start;
	while (p) {
		ToEnd(p->inf);
		p = p->link;
	}
}
#endif
