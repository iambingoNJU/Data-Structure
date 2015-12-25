#ifndef __LINKEDSTACK_CPP__
#define __LINKEDSTACK_CPP__

#include <iostream>
using namespace std;

#include <assert.h>

template <class T>
struct LinkNode
{
	T data;
	LinkNode<T> *next;
	LinkNode(LinkNode<T> *ptr=NULL) { next=ptr;}
	LinkNode(const T& item,LinkNode<T> *ptr=NULL) { data=item; next=ptr; }
};

template <class T>
class LinkedStack
{
private:
	LinkNode<T> *head;
public:
	LinkedStack(): head(NULL) {}
	~LinkedStack() { clear(); }
	void push(const T& x);
	bool pop(T& x);
	bool getTop(T& x);
	bool isEmpty() { return head==NULL; }
	int getSize();
	void clear();
	void showme();
};

template <class T>
void LinkedStack<T>::clear()
{
	LinkNode<T> *temp=NULL;
	while(head!=NULL)
	{
		temp=head;
		head=head->next;
		delete temp;
	}
}

template <class T>
void LinkedStack<T>::push(const T& x)
{
	head=new LinkNode<T>(x,head);
	assert(head!=NULL);
}

template <class T>
bool LinkedStack<T>::pop(T& x)
{
	if(isEmpty())
		return false;
	LinkNode<T> *temp=head;
	head=head->next;
	x=temp->data;
	delete temp;
	return true;
}

template <class T>
bool LinkedStack<T>::getTop(T& x)
{
	if(isEmpty())
		return false;
	x=head->data;
	return true;
}

template <class T>
int LinkedStack<T>::getSize()
{
	LinkNode<T> *temp=head;
	int cnt=0;
	while(temp!=NULL)
	{
		cnt++;
		temp=temp->next;
	}
	return cnt;
}

template <class T>
void LinkedStack<T>::showme()
{
	cout<<"Stack elements from top to bottom:"<<endl;
	cout<<"("<<getSize()<<") [ ";
	LinkNode<T> *temp=head;
	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<"]"<<endl;
}


#endif
