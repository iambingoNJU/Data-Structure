#include <iostream>
using namespace std;

#include <assert.h>
#define STACKSIZE 50
#define STACKINCREAMENT 20

template <class T>
class SeqStack
{
protected:
	T *elements;
	int top;
	int maxSize;
	void overflowProcess();
public:
	SeqStack(int sz=STACKSIZE);
	~SeqStack() {delete[] elements;}
	void push(T& x);
	bool pop(T& x);
	bool getTop(T& x);
	int getSize() { return top+1;}
	void clear() { top=-1;}
	bool isEmpty() { return top==-1;}
	bool isFull() { return top==maxSize-1;}
	void showme();
};

template <class T>
void SeqStack<T>::overflowProcess()
{
	T *newArray=new T[maxSize+STACKINCREAMENT];
	assert(newArray!=NULL);
	for(int i=0;i<=top;i++)
		newArray[i]=elements[i];
	maxSize+=STACKINCREAMENT;
	delete[] elements;
	elements=newArray;
}

template <class T>
SeqStack<T>::SeqStack(int sz):top(-1),maxSize(sz)
{
	elements=new T[maxSize];
	assert(elements!=NULL);
}

template <class T>
void SeqStack<T>::push(T& x)
{
	if(isFull())
		overflowProcess();
	elements[++top]=x;
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
	cout<<"Stack elements from bottom to top:"<<endl<<"("<<top+1<<")[ ";
	for(int i=0;i<=top;i++)
		cout<<elements[i]<<" ";
	cout<<"]"<<endl;
}

template <class T>
bool SeqStack<T>::getTop(T& x)
{
	if(isEmpty())
		return false;
	x=elements[top];
	return true;
}
