#include <iostream>
using namespace std;

#include <assert.h>

template <class T>
struct DoubleNode {
	T data;
	DoubleNode<T> *next,*last;
	DoubleNode(DoubleNode<T> *l=NULL,DoubleNode<T> *n=NULL):last(l),next(n) {}
	DoubleNode(T value,DoubleNode<T> *l=NULL,DoubleNode<T> *n=NULL):data(value),last(l),next(n) {}
};

template <class T>
class DoubleList
{
protected:
	DoubleNode<T> *head,*tail;
public:
	DoubleList():head(NULL),tail(NULL) {}
	~DoubleList() { clear(); }
	void clear();
};
