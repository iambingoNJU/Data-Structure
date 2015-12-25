#ifndef __LINKEDLIST_CPP__
#define __LINKEDLIST_CPP__

#include <iostream>
using namespace std;

#include <assert.h>

template <class T>
struct LinkNode {
	T data;
	LinkNode<T> *next;
	LinkNode(LinkNode<T> *ptr=NULL) { next=ptr; }
	LinkNode(T item,LinkNode<T> *ptr=NULL) { data=item; next=ptr; }
};

template <class T>
class LinkedList
{
protected:
	LinkNode<T> *head;
public:
	LinkedList() { head=NULL; }
	LinkedList(T x) { head=new LinkNode<T>(x); }
	LinkedList(LinkedList<T>& L);
	~LinkedList() { clear(); }
	void clear();
	int lenth();
	LinkNode<T>* getHead() { return head; }
	LinkNode<T>* search(T x);
	LinkNode<T>* locate(int i);
	bool getData(int i,T& x);
	bool setData(int i,T x);
	bool insert(int i,T x);
	bool remove(int i,T& x);
	bool isEmpty() { return head==NULL; }
	void sort(int type=0);	//type==0 means from small to big, otherwise(type==1) the opposite.
	void input(T endFlag=0,int type=0); //type==0 means insert from head, type==1 means insert from tail.
	void output();
	int position(LinkNode<T> *dest);
	LinkedList<T>& operator=(LinkedList<T>& L);
	LinkedList<T>& operator+=(LinkedList<T>& L);
	LinkedList<T>& operator-=(LinkedList<T>& L);
	LinkedList<T>& operator*=(LinkedList<T>& L);
};

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& L)
{
	if(!L.isEmpty())
	{
		T temp;
		L.getData(0,temp);
		head=new LinkNode<T>(temp);
		LinkNode<T> *srcptr=(L.getHead())->next, *tail=head;
		while(srcptr!=NULL)
		{
			temp=srcptr->data;
			tail->next=new LinkNode<T>(temp);
			tail=tail->next;
			srcptr=srcptr->next;
		}
	}

}


template <class T>
void LinkedList<T>::clear()
{
	LinkNode<T> *temp;
	while(head!=NULL)
	{
		temp=head;
		head=head->next;
		delete temp;
	}
}

template <class T>
int LinkedList<T>::lenth()
{
	int cnt=0;
	LinkNode<T> *temp=head;
	while(temp!=NULL)
	{
		cnt++;
		temp=temp->next;
	}
	return cnt;
}

template <class T>
LinkNode<T>* LinkedList<T>::locate(int i)
{
	if(i<0 || i>=lenth()) return NULL;
	LinkNode<T> *temp=head;
	while(i>0)
	{
		temp=temp->next;
		i--;
	}
	return temp;
}

template <class T>
void LinkedList<T>::input(T endFlag,int type)
{
	if(type==0)
	{
		cout<<"Current list:"<<endl;
		output();
		cout<<"Please enter list elements(END with "<<endFlag<<"):"<<endl;
		T temp;
		LinkNode<T> *newNode;
		while((cin>>temp)&&(temp!=endFlag))
		{
			newNode=new LinkNode<T>(temp);
			assert(newNode!=NULL);
			newNode->next=head;
			head=newNode;
		}

	}
	else if(type==1)
	{
		cout<<"Current list:"<<endl;
		output();
		cout<<"Please enter list elements(END with "<<endFlag<<"):"<<endl;
		T temp;
		LinkNode<T> *newNode,*tail=locate(lenth()-1);
		while((cin>>temp)&&(temp!=endFlag))	
		{
			newNode=new LinkNode<T>(temp);
			assert(newNode!=NULL);
			if(tail==NULL)
			{
				tail=newNode;
				head=tail;
			}
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
	}
	else
		cout<<"You give 'input' a wrong arguments. It should be 0 or 1."<<endl; 
}


template <class T>
void LinkedList<T>::output()
{
	LinkNode<T> *temp=head;
	cout<<"List elements: "<<"("<<lenth()<<")[ ";
	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<"]"<<endl;
}

template <class T>
LinkNode<T>* LinkedList<T>::search(T x)
{
	LinkNode<T> *temp=head;
	while(temp!=NULL)
	{
		if(temp->data==x)
			break;
		temp=temp->next;
	}
	return temp;
}

template <class T>
bool LinkedList<T>::getData(int i,T& x)
{
	LinkNode<T> *temp=locate(i);
	if(temp==NULL)
		return false;
	x=temp->data;
	return true;
}

template <class T>
bool LinkedList<T>::setData(int i,T x)
{
	LinkNode<T> *temp=locate(i);
	if(temp==NULL)
		return false;
	temp->data=x;
	return true;
}

template <class T>
bool LinkedList<T>::insert(int i,T x)
{
	if(i==-1)
	{
		LinkNode<T> *newNode=new LinkNode<T>(x);
		newNode->next=head;
		head=newNode;
		return true;
	}
	LinkNode<T> *temp=locate(i);
	if(temp==NULL)
		return false;
	LinkNode<T> *newNode=new LinkNode<T>(x);
	newNode->next=temp->next;
	temp->next=newNode;
	return true;
}

template <class T>
bool LinkedList<T>::remove(int i,T& x)
{
	LinkNode<T> *temp=locate(i),*pre=locate(i-1);
	if(temp==NULL)
		return false;

	x=temp->data;
	if(pre==NULL)
		head=head->next;
	else
		pre->next=temp->next;
	delete temp;
	return true;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& L)
{
	clear();
	if(!L.isEmpty())
	{
		T temp;
		L.getData(0,temp);
		head=new LinkNode<T>(temp);
		LinkNode<T> *srcptr=(L.getHead())->next, *tail=head;
		while(srcptr!=NULL)
		{
			temp=srcptr->data;
			tail->next=new LinkNode<T>(temp);
			tail=tail->next;
			srcptr=srcptr->next;
		}
	}
	return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator-=(LinkedList<T>& L)
{
	LinkNode<T> *t1 = head, *t2;
	T temp;
	while(t1)
	{
		if(L.search(t1->data))
		{
			t2 = t1->next;
			remove(position(t1), temp);
			t1 = t2;
		}
		else
			t1 = t1->next;
	}

	return *this;
}


template <class T>
LinkedList<T>& LinkedList<T>::operator+=(LinkedList<T>& L)
{
	LinkNode<T> *t1 = head, *t2 = L.getHead(), *temp = NULL, *t3 = new LinkNode<T>;
	while(t1 && t2)
	{
		if(t1->data < t2->data)
		{
			t3->next = new LinkNode<T>(t1->data);
			t1 = t1->next;
		}
		else if(t1->data > t2->data)
		{
			t3->next = new LinkNode<T>(t2->data);
			t2 = t2->next;
		}
		else
		{
			t3->next = new LinkNode<T>(t1->data);
			t1 = t1->next;
			t2 = t2->next;
		}

		if(temp == NULL)	temp = t3;

		t3 = t3->next;
	}

	while(t1)
	{
		t3->next = new LinkNode<T>(t1->data);
		t1 = t1->next;

		if(temp == NULL)	temp = t3;
		t3 = t3->next;
	}
	while(t2)
	{
		t3->next = new LinkNode<T>(t2->data);
		t2 = t2->next;

		if(temp == NULL)	temp = t3;
		t3 = t3->next;
	}
	t3->next = NULL;

	clear();

	head = temp->next;
	delete temp;

	return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator*=(LinkedList<T>& L)
{
	LinkNode<T> *t1 = head, *t2 = L.getHead(), *temp = NULL, *t3 = new LinkNode<T>;
	while(t1 && t2)
	{
		if(t1->data < t2->data)
			t1 = t1->next;
		else if(t1->data > t2->data)
			t2 = t2->next;
		else
		{
			t3->next = new LinkNode<T>(t1->data);
			t1 = t1->next;
			t2 = t2->next;
			if(temp == NULL)	temp = t3;
			t3 = t3->next;
		}
	}

	t3->next = NULL;

	clear();

	head = temp->next;
	delete temp;

	return *this;
}

template <class T>
void LinkedList<T>::sort(int type)
{
	if(type!=0 && type!=1)
	{
		cout<<"You give 'sort' a wrong argument. It should be 0 or 1."<<endl;
		return;
	}
	int len=lenth();
	T temp1,temp2;
	while(len>1)
	{
		bool flag=false;
		for(int i=0;i<len-1;i++)
		{
			getData(i,temp1);
			getData(i+1,temp2);
			bool condition;
			if(type==0)
				condition=temp1>temp2;
			else
				condition=temp1<temp2;
			if(condition)
			{
				setData(i,temp2);
				setData(i+1,temp1);
				flag=true;
			}
		}
		if(!flag)	break;
		len--;
	}
}

template <class T>
int LinkedList<T>::position(LinkNode<T> *dest)
{
	LinkNode<T> *temp=head;
	int cnt=0;
	while(temp!=dest)
	{
		cnt++;
		temp=temp->next;
	}
	if(temp==dest)
		return cnt;
	else
		return -1;
}


#endif
