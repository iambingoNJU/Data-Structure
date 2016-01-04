#ifndef __SEQLIST_CPP__
#define __SEQLIST_CPP__

#include <iostream>
using namespace std;

#define SEQLIST_SIZE 50
const int increment=10;

template <class T>
class SeqList
{
protected:
	T *data;
	int maxSize;
	int last;
	bool resize(int size);

public:
	SeqList(int size=SEQLIST_SIZE);
	SeqList(SeqList<T>& L);
	~SeqList(){delete[] data;}
	int size() const { return maxSize; }
	int lenth() const { return last; }
	int search(T x) const;
	int locate(int i) const;
	bool getData(int i,T& x) const;
	bool setData(int i,T x);
	bool insert(int i,T x);
	bool remove(int i,T& x);
	bool isEmpty() { return last==0; }
	bool isFull() { return last==maxSize; }
	void clear() { last=0; }
	void input(T endFlag);
	void output();
	SeqList<T>& operator=(SeqList<T>& L);	
};

template <class T>
bool SeqList<T>::resize(int size)
{
	if(size<=0)
	{
		cout<<"Invalid array size!\n";
		return false;
	}
	T *newdata=new T[size];
	if(newdata==NULL)
	{
		cout<<"resize error!"<<endl;
		return false;
	}
	else
	{
		maxSize=size;
		for(int i=0;i<last;i++)
			newdata[i]=data[i];
		delete []data;
		data=newdata;
		return true;
	}
}

template <class T>
SeqList<T>::SeqList(int size)
{
	if(size>0)
	{
		maxSize=size;
		last=0;
		data=new T[maxSize];
		if(data==NULL)
			cout<<"Memory allocation error!"<<endl;
	}
}

template <class T>
SeqList<T>::SeqList(SeqList<T>& L)
{
	maxSize=L.size();
	last=L.lenth();
	data=new T[maxSize];
	if(data==NULL)
		cout<<"Memory allocation error!"<<endl;
	for(int i=0;i<last;i++)
		L.getData(i,data[i]);
}


template <class T>
int SeqList<T>::search(T x) const
{
	for(int i=0;i<last;i++)
		if(data[i]==x)
			return i;
	return -1;
}


template <class T>
int SeqList<T>::locate(int i) const
{
	if(i>=0 && i<last)
		return i;
	else
		return -1;
}


template <class T>
bool SeqList<T>::getData(int i,T &x) const
{
	if(i>=0 && i<last)
	{
		x=data[i];
		return true;
	}
	else
		return false;
}


template <class T>
bool SeqList<T>::setData(int i,T x)
{
	if(i>=0 && i<maxSize)
	{
		data[i]=x;
		return true;
	}
	else
		return false;
}


template <class T>
bool SeqList<T>::insert(int i,T x)
{
	if(i>=-1 && i<last)
	{
		if(isFull())	resize(maxSize+increment);
		for(int j=last-1;j>i;j--)
			data[j+1]=data[j];
		data[i+1]=x;

		last++;
		return true;
	}
	else
		return false;
}


template <class T>
bool SeqList<T>::remove(int i,T &x)
{
	if(i>=0 && i<last)
	{
		x=data[i];
		for(int j=i;j<last-1;j++)
			data[j]=data[j+1];

		last--;
		return true;
	}
	else
		return false;
}


template <class T>
void SeqList<T>::input(T endFlag)
{
	T buf;
	cout<<"Please enter the list elements(END with "<<endFlag<<"):\n";
	while(cin>>buf && buf!=endFlag)
	{
		if(isFull())
			if(!resize(maxSize+increment))
			{
				cout<<"memory allocation error when resize!\n";
				break;
			}

		data[last]=buf;
		last++;
	}
}


template <class T>
void SeqList<T>::output()
{
	if(last==0)
		cout<<"NULL"<<endl;
	else
	{
		cout<<"List elements: "<<endl<<"("<<last<<") [ ";
		for(int i=0;i<last;i++)
			cout<<data[i]<<" ";
		cout<<"]"<<endl;
	}
}

template <class T>
SeqList<T>& SeqList<T>::operator=(SeqList<T>& L)
{
	last=L.lenth();
	maxSize=L.size();
	data=new T[maxSize];
	if(data==NULL)
	{
		cout<<"Memory allocation error!"<<endl;
		return *this;
	}
	for(int i=0;i<last;i++)
		L.getData(i,data[i]);

	return *this;
}


#endif
