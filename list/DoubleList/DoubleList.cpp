#ifndef __DOUBLELIST_CPP__
#define __DOUBLELIST_CPP__

#include <iostream>
using namespace std;

#include <assert.h>

template <class T>
struct DoubleNode {
	T data;
	DoubleNode<T> *next, *last;
	DoubleNode(DoubleNode<T> *l = NULL, DoubleNode<T> *n = NULL): last(l), next(n) {}
	DoubleNode(T value, DoubleNode<T> *l = NULL, DoubleNode<T> *n = NULL): data(value), last(l), next(n) {}
};

template <class T>
class DoubleList
{
protected:
	DoubleNode<T> *head;
public:
	DoubleList(T uniqueVal);
	~DoubleList() {}
	void clear();
	int lenth();
	bool isEmpty() { return head->next == head; }
	DoubleNode<T>* getHead() { return head; }
	DoubleNode<T>* search(T x);
	DoubleNode<T>* locate(int i, int d);
	bool insert(int i, T x, int d);
	bool remove(int i, T &x, int d);
	friend ostream& operator<<(ostream& out, DoubleList<T>& l)
	{
		out<<"("<<l.lenth()<<")[ ";
		DoubleNode<T> *temp = (l.getHead())->next;
		while(temp != l.getHead())
		{
			out<<temp->data<<" ";
			temp = temp->next;
		}
		out<<"]";
		return out;
	}
};

template <class T>
DoubleList<T>::DoubleList(T uniqueVal)
{
	head = new DoubleNode<T>(uniqueVal);
	assert(head != NULL);
	head->next = head->last = head;
}

template <class T>
void DoubleList<T>::clear()
{
	DoubleNode<T> *cur = head->next, *temp = NULL;
	while(cur != head)
	{
		temp = cur;
		cur = cur->next;
		delete temp;
	}
	
	head->next = head->last = head;
}

template <class T>
int DoubleList<T>::lenth()
{
	DoubleNode<T> *current = head->next;
	int cnt = 0;
	while(current != head)
	{
		current = current->next;
		cnt++;
	}
	return cnt;
}

template <class T>
DoubleNode<T>* DoubleList<T>::search(T x)
{
	DoubleNode<T> *temp = head->next;
	while(head != head && head->data != x)
		temp = temp->next;
	if(temp != head)	return temp;
	else	return NULL;
}

template <class T>
DoubleNode<T>* DoubleList<T>::locate(int i, int d)
{
	if(head->next == head || i == 0)	return head;
	DoubleNode<T> *temp;
	if(d == 0)	temp = head->last;
	else	temp = head->next;
	for(int k=1; k<i; k++)
		if(temp == head)	break;
		else if(d == 0)	temp = temp->last;
		else	temp = temp->next;
	if(temp != head)	return temp;
	else	return NULL;
}

template <class T>
bool DoubleList<T>::insert(int i, T x, int d)
{
	DoubleNode<T> *temp = locate(i, d);
	if(temp == NULL)	return false;
	DoubleNode<T> *newNode = new DoubleNode<T>(x);
	assert(newNode != NULL);
	if(d == 0)
	{
		newNode->last = temp->last;
		temp->last = newNode;
		newNode->last->next = newNode;
		newNode->next = temp;
	}
	else
	{
		newNode->next = temp->next;
		temp->next = newNode;
		newNode->next->last = newNode;
		newNode->last = temp;
	}
	return true;
}

template <class T>
bool DoubleList<T>::remove(int i, T &x, int d)
{
	DoubleNode<T> *temp = locate(i, d);
	if(temp == NULL)	return false;
	temp->next->last = temp->last;
	temp->last->next = temp->next;
	x = temp->data;
	delete temp;
	return true;
}

#endif
