#ifndef __BINARYTREE_CPP__
#define __BINARYTREE_CPP__

#include <iostream>
using namespace std;

#define EndMark '#'
#include "../../queue/SeqQueue/SeqQueue.cpp"
#include "../../stack/SeqStack/SeqStack.cpp"

template <class T>
struct BinTreeNode
{
	T data;
	BinTreeNode<T> *leftChild, *rightChild;
	BinTreeNode(): leftChild(NULL), rightChild(NULL) {}
	BinTreeNode(T x,BinTreeNode<T> *l=NULL,BinTreeNode<T> *r=NULL): data(x), leftChild(l), rightChild(r) {}
};

template <class T>
class BinaryTree
{
protected:
	BinTreeNode<T> *root;
	void destroy(BinTreeNode<T> *subTree);
	int howManyLeaves(BinTreeNode<T> *subTree);
	void exchange(BinTreeNode<T> *subTree);
	void preOrder(BinTreeNode<T> *subTree);
	void preOrder_1rec(BinTreeNode<T> *subTree);
	int depth(BinTreeNode<T> *subTree);
	int level(BinTreeNode<T> *subTree,BinTreeNode<T> *dest);
public:
	BinaryTree(): root(NULL) {}
	~BinaryTree() { destroy(root);}
	bool isEmpty() { return root==NULL;}
	bool create(T *str);
	void levelOrder();
	void preOrder() { preOrder(root);}
	void preOrder_1rec() { preOrder_1rec(root);}
	void preOrder_0rec();
	int howManyLeaves() { return howManyLeaves(root);}
	void exchange() { exchange(root);}
	int maxDepth() { return depth(root);}
};

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *subTree)
{
	if(subTree!=NULL)
	{
		destroy(subTree->leftChild);
		destroy(subTree->rightChild);
		delete subTree;
	}
}

template <class T>
bool BinaryTree<T>::create(T *s)
{
	if(s[0]==EndMark)	return false;

	root=new BinTreeNode<T>;
	root->data=s[0];

	SeqQueue<BinTreeNode<T>*> q;
	BinTreeNode<T> *temp;
	int i=1;
	q.enQueue(root);
	while(q.deQueue(temp))
	{

		if(s[i]!=EndMark)
		{
			BinTreeNode<T> *l=new BinTreeNode<T>;
			l->data=s[i];		
			temp->leftChild=l;
			q.enQueue(l);
		}
		else
			temp->leftChild=NULL;

		if(s[i+1]!=EndMark)
		{
			BinTreeNode<T> *r=new BinTreeNode<T>;
			r->data=s[i+1];
			temp->rightChild=r;
			q.enQueue(r);
		}
		else
			temp->rightChild=NULL;

		i+=2;
	}

	return true;
}

template <class T>
void BinaryTree<T>::levelOrder()
{
	SeqQueue<BinTreeNode<T>*> q;
	BinTreeNode<T> *p=root;
	q.enQueue(p);
	while(q.deQueue(p))
	{
		cout<<p->data;
		if(p->leftChild!=NULL) q.enQueue(p->leftChild);
		if(p->rightChild!=NULL) q.enQueue(p->rightChild);
	}
}

template <class T>
void BinaryTree<T>::exchange(BinTreeNode<T> *subTree)
{
	if(subTree!=NULL)
	{
		BinTreeNode<T> *temp=subTree->leftChild;
		subTree->leftChild=subTree->rightChild;
		subTree->rightChild=temp;

		exchange(subTree->leftChild);
		exchange(subTree->rightChild);
	}
}

template <class T>
int BinaryTree<T>::howManyLeaves(BinTreeNode<T> *subTree)
{
	if(subTree==NULL)
		return 0;
	else 
	{
		if((subTree->leftChild==NULL)&&(subTree->rightChild==NULL))
			return 1;
		else
			return howManyLeaves(subTree->leftChild)+howManyLeaves(subTree->rightChild);
	}
}

template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> *subTree)
{
	if(subTree!=NULL)
	{
		cout<<subTree->data;
		cout<<level(root,subTree);
		preOrder(subTree->leftChild);
		preOrder(subTree->rightChild);
	}
}

template <class T>
void BinaryTree<T>::preOrder_1rec(BinTreeNode<T> *subTree)
{
	while(subTree!=NULL)
	{
		cout<<subTree->data;
		preOrder_1rec(subTree->leftChild);
		subTree=subTree->rightChild;
	}
}

template <class T>
void BinaryTree<T>::preOrder_0rec()
{
	SeqStack<BinTreeNode<T>*> s;
	BinTreeNode<T> *temp=root;
	s.push(temp);
	while(s.pop(temp))
	{
		cout<<temp->data;
		if(temp->rightChild!=NULL)
			s.push(temp->rightChild);
		if(temp->leftChild!=NULL)
			s.push(temp->leftChild);
	}
}

template <class T>
int BinaryTree<T>::depth(BinTreeNode<T> *subTree)
{
	if(subTree==NULL)
		return 0;
	else
	{
		int i=depth(subTree->leftChild);
		int j=depth(subTree->rightChild);
		return (i<j)?j+1:i+1;
	}
}

template <class T>
int BinaryTree<T>::level(BinTreeNode<T> *subTree, BinTreeNode<T> *dest)
{
	int r;
	if(subTree==NULL)
		return 0;
	if(subTree==dest)
		return 1;
	else if(r=level(subTree->leftChild,dest))
		return 1+r;
	else if(r=level(subTree->rightChild,dest))
		return 1+r;
	else
		return 0;
}


#endif
