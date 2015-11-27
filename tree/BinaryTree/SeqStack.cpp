#include <iostream>
using namespace std;

#include <assert.h>
#define STACKSIZE 50

template <class T>
class SeqStack
{
protected:
	T *elements;
	int top;
	int maxSize;
public:
	SeqStack(int sz=STACKSIZE);
	~SeqStack() {delete[] elements;}
	bool push(const T& x);
	bool pop(T& x);
	bool isEmpty() { return top==-1;}
	bool isFull() { return top==maxSize-1;}
	void showme();
};

template <class T>
SeqStack<T>::SeqStack(int sz):top(-1),maxSize(sz)
{
	elements=new T[maxSize];
	assert(elements!=NULL);
}

template <class T>
bool SeqStack<T>::push(const T& x)
{
	if(isFull())
		return false;
	elements[++top]=x;
	return true;
}

template <class T>
bool SeqStack<T>::pop(T& x)
{
	if(isEmpty())
		return false;
	x=elements[top--];
	return true;
}

template <class T>
void SeqStack<T>::showme()
{
	cout<<"("<<top+1<<")[ ";
	for(int i=0;i<=top;i++)
		cout<<elements[i]<<" ";
	cout<<"]"<<endl;
}
