#ifndef __SEQQUEUE_CPP__
#define __SEQQUEUE_CPP__

#include <iostream>
#include <assert.h>
using namespace std;

const int defaultSize=50;

template <class T>
class SeqQueue
{
protected:
	int rear,front;
	T *elements;
	int maxSize;

public:
	SeqQueue(int sz=defaultSize);
	~SeqQueue() { delete[] elements;}
	bool enQueue(const T& x);
	bool deQueue(T& x);
	bool getFront(T& x);
	bool getRear(T& x);
	void showme();
	void clear() { front=0; rear=0;}
	bool isEmpty() { return front==rear;}
	bool isFull() { return (rear+1)%maxSize==front; }
	int getSize() { return (rear+maxSize-front)%maxSize; }
};


template <class T>
SeqQueue<T>::SeqQueue(int sz): front(0), rear(0), maxSize(sz)
{
	elements=new T[maxSize];
	assert(elements!=NULL);
}

template <class T>
bool SeqQueue<T>::enQueue(const T& x)
{
	if(isFull())
		return false;
	elements[rear]=x;
	rear=(rear+1)%maxSize;	
	return true;
}

template <class T>
bool SeqQueue<T>::deQueue(T &x)
{
	if(isEmpty())
		return false;
	x=elements[front];
	front=(front+1)%maxSize;
	return true;
}

template <class T>
bool SeqQueue<T>::getFront(T &x)
{
	if(isEmpty())
		return false;
	x=elements[front];
	return true;
}

template <class T>
bool SeqQueue<T>::getRear(T& x)
{
	if(isEmpty())
		return false;
	x=elements[rear-1];
	return true;
}

template <class T>
void SeqQueue<T>::showme()
{
	int cnt=getSize();
	cout<<"Queue elements from front to rear:"<<endl;
	cout<<"("<<cnt<<") [ ";
	for(int i=0;i<cnt;i++)
		cout<<elements[(front+i)%maxSize]<<" ";
	cout<<"]"<<endl;
}


#endif
