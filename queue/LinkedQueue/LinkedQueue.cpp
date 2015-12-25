#ifndef __LINKEDQUEUE_CPP__
#define __LINKEDQUEUE_CPP__

#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
struct LinkNode
{
	T data;
	LinkNode<T> *next;
	LinkNode(LinkNode<T> *ptr=NULL) { next=ptr;}
	LinkNode(const T& item,LinkNode<T> *ptr=NULL) { data=item; next=ptr; }
};

template <class T>
class LinkedQueue
{
protected:
	LinkNode<T> *front,*rear;
	
public:
	LinkedQueue(): front(NULL),rear(NULL) {}
	~LinkedQueue() { clear(); }
	bool enQueue(const T& x);
	bool deQueue(T& x);
	bool getFront(T& x);
	bool getRear(T& x);
	void clear();
	bool isEmpty() { return front==NULL;}
	int getSize();
	void showme();
};

template <class T>
void LinkedQueue<T>::clear()
{
	LinkNode<T> *temp;
	while(front!=NULL)
	{
		temp=front;
		front=front->next;
		delete temp;
	}
}

template <class T>
bool LinkedQueue<T>::enQueue(const T& x)
{
	if(front==NULL)
	{
		front=rear=new LinkNode<T>(x);
		if(front==NULL)	return false;
	}
	else
	{
		rear->next=new LinkNode<T>(x);
		if(rear->next==NULL)	return false;
		rear=rear->next;
	}
	return true;
}

template <class T>
bool LinkedQueue<T>::deQueue(T& x)
{
	if(isEmpty())
		return false;
	LinkNode<T> *temp=front;
	x=front->data;
	front=front->next;
	delete temp;
	return true;
}

template <class T>
bool LinkedQueue<T>::getFront(T& x)
{
	if(isEmpty())
		return false;
	x=front->data;
	return true;
}

template <class T>
bool LinkedQueue<T>::getRear(T& x)
{
	if(isEmpty())
		return false;
	x=rear->data;
	return true;
}

template <class T>
int LinkedQueue<T>::getSize()
{
	int cnt=0;
	LinkNode<T> *temp=front;
	while(temp!=NULL)
	{
		cnt++;
		temp=temp->next;
	}
	return cnt;
}

template <class T>
void LinkedQueue<T>::showme()
{
	cout<<"Queue elements from front to rear:"<<endl;
	cout<<"("<<getSize()<<") [ ";
	LinkNode<T> *temp=front;
	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<"]"<<endl;
}


#endif
