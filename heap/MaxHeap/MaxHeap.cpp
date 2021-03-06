#ifndef __MAXHEAP_CPP__
#define __MAXHEAP_CPP__

#include <iostream>
using namespace std;
#include <assert.h>

#define MAX_HEAP_SIZE 30

template <class E>
class MaxHeap {
private:
	E *heap;
	int currentSize;
	int maxSize;
	void siftUp(int start);
	void siftDown(int start, int m);
public:
	MaxHeap(int sz=MAX_HEAP_SIZE);
	MaxHeap(E arr[], int n);
	~MaxHeap() { delete []heap; }
	bool insert(E x);
	bool removeMax(E& x);
	bool isEmpty() { return currentSize == 0; }
	bool isFull() { return currentSize == maxSize; }
	void clear() { currentSize = 0; }
};

template <class E>
MaxHeap<E>::MaxHeap(int sz)
{
	maxSize = MAX_HEAP_SIZE < sz ? sz : MAX_HEAP_SIZE;
	currentSize = 0;
	heap = new E[maxSize];
	assert(heap!=NULL);
}

template <class E>
MaxHeap<E>::MaxHeap(E arr[], int n)
{
	maxSize = MAX_HEAP_SIZE < n ? n : MAX_HEAP_SIZE;
	heap = new E[maxSize];
	assert(heap!=NULL);
	for(int i=0; i<n; i++)	heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while(currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template <class E>
void MaxHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2*i + 1;
	E temp = heap[i];
	while(j <= m)
	{
		if(j<m && heap[j]<heap[j+1])	j++;
		if(temp>=heap[j])	break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2*j + 1;
		}
	}
	heap[i] = temp;
}

template <class E>
void MaxHeap<E>::siftUp(int start)
{
	int j = start, i = (j-1)/2;
	E temp = heap[j];
	while(j>0)
	{
		if(heap[i] >= temp)	break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i-1)/2;
		}
	}
	heap[j] = temp;
}

template <class E>
bool MaxHeap<E>::insert(E x)
{
	if(isFull())
	{
		cout<<"Heap full!"<<endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template <class E>
bool MaxHeap<E>::removeMax(E& x)
{
	if(isEmpty())
	{
		cout<<"Heap empty!"<<endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap [currentSize-1];
	currentSize--;
	siftDown(0, currentSize-1);
	return true;
}


#endif
