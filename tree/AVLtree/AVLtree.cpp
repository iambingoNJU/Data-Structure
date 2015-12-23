#include <iostream>
using namespace std;

#include "SeqStack.cpp"

template <class K, class T>
struct AVLnode {
	int bf;
	K key;
	T data;
	AVLnode<K,T> *leftChild, *rightChild;
	
	AVLnode(): leftChild(NULL), rightChild(NULL), bf(0) {}
	AVLnode(K k,T d,AVLnode<K,T> *l=NULL,AVLnode<K,T> *r=NULL) : key(k), data(d), leftChild(l), rightChild(r), bf(0) {}
};

template <class K,class T>
void print(AVLnode<K,T> *p)
{
	cout<<"key: "<<p->key<<" --- data: "<<p->data<<" --- bf: "<<p->bf<<endl;
}

template <class K,class T>
class AVLtree {
protected:
	AVLnode<K,T> *root;

	void rotateL(AVLnode<K,T>* &ptr);
	void rotateR(AVLnode<K,T>* &ptr);
	void rotateLR(AVLnode<K,T>* &ptr);
	void rotateRL(AVLnode<K,T>* &ptr);

	void preOrder(AVLnode<K,T> *subTree, void (*visit)(AVLnode<K,T> *p));
	void inOrder(AVLnode<K,T> *subTree, void (*visit)(AVLnode<K,T> *p));
	void postOrder(AVLnode<K,T> *subTree, void (*visit)(AVLnode<K,T> *p));

	AVLnode<K,T>* search(K k);
	bool insert(K k,T d,AVLnode<K,T>* &ptr);
	bool remove(K k,T &d,AVLnode<K,T>* &ptr);
	int height(AVLnode<K,T>* ptr);

public:
	AVLtree(): root(NULL) {}
	bool insert(K k,T d) { return insert(k,d,root); }
	bool remove(K k,T &d) { return remove(k,d,root); }
	int height() { return height(root); }
	void showInOrder() { inOrder(root, print); }
};

template <class K, class T>
void AVLtree<K,T>::rotateL(AVLnode<K,T>* &ptr)
{
	cout<<"rotateL."<<endl;
	AVLnode<K,T> *subL = ptr;
	ptr = subL->rightChild;
	subL->rightChild = ptr->leftChild;
	ptr->leftChild = subL;
	ptr->bf = 0;
	subL->bf = 0;
}

template <class K, class T>
void AVLtree<K,T>::rotateR(AVLnode<K,T>* &ptr)
{
	cout<<"rotateR."<<endl;
	AVLnode<K,T> *subR = ptr;
	ptr = subR->leftChild;
	subR->leftChild = ptr->rightChild;
	ptr->rightChild = subR;
	ptr->bf = 0;
	subR->bf = 0;
}

template <class K, class T>
void AVLtree<K,T>::rotateLR(AVLnode<K,T>* &ptr)
{
	cout<<"rotateLR."<<endl;
	AVLnode<K,T> *subR = ptr, *subL = ptr->leftChild;
	ptr = subL->rightChild;

	subL->rightChild = ptr->leftChild;
	ptr->leftChild = subL;
	if(ptr->bf <= 0)
		subL->bf = 0;
	else
		subL->bf = -1;

	subR->leftChild = ptr->rightChild;
	ptr->rightChild = subR;
	if(ptr->bf == -1)
		subR->bf = 1;
	else
		subR->bf = 0;

	ptr->bf = 0;
}

template <class K, class T>
void AVLtree<K,T>::rotateRL(AVLnode<K,T>* &ptr)
{
	cout<<"rotateRL."<<endl;
	AVLnode<K,T> *subL = ptr, *subR = ptr->rightChild;
	ptr = subR->leftChild;

	subR->leftChild = ptr->rightChild;
	ptr->rightChild = subR;
	if(ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;

	subL->rightChild = ptr->leftChild;
	ptr->leftChild = subL;
	if(ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;

	ptr->bf = 0;
}

template <class K, class T>
void AVLtree<K,T>::preOrder(AVLnode<K,T> *subTree, void (*visit)(AVLnode<K,T> *p))
{
	if(subTree)
	{
		visit(subTree);
		inOrder(subTree->leftChild, visit);
		inOrder(subTree->rightChild, visit);
	}
}

template <class K, class T>
void AVLtree<K,T>::inOrder(AVLnode<K,T> *subTree, void (*visit)(AVLnode<K,T> *p))
{
	if(subTree)
	{
		inOrder(subTree->leftChild, visit);
		visit(subTree);
		inOrder(subTree->rightChild, visit);
	}
}

template <class K, class T>
void AVLtree<K,T>::postOrder(AVLnode<K,T> *subTree, void (*visit)(AVLnode<K,T> *p))
{
	if(subTree)
	{
		inOrder(subTree->leftChild, visit);
		inOrder(subTree->rightChild, visit);
		visit(subTree);
	}
}

template <class K, class T>
bool AVLtree<K,T>::insert(K k, T d, AVLnode<K,T>* &ptr)
{
	AVLnode<K,T> *pr = NULL, *p = ptr, *q;
	SeqStack<AVLnode<K,T>* > st;
	while(p)
	{
		if(p->key == k)	return false;
		pr = p;
		st.push(pr);
		if(k < p->key)
			p = p->leftChild;
		else
			p = p->rightChild;
	}

	p = new AVLnode<K,T>(k,d);
	assert(p != NULL);
	
	if(pr == NULL)	//Empty tree.
	{
		ptr = p;
		return true;
	}

	if(k < pr->key)
		pr->leftChild = p;
	else
		pr->rightChild = p;

	while(st.pop(pr))
	{
		if(p == pr->leftChild)
			pr->bf--;
		else
			pr->bf++;

		if(pr->bf == 0)	break;
		if(pr->bf == 1 || pr->bf == -1)	p = pr;
		else
		{
			int d = (pr->bf < 0) ? -1 : 1;
			if(p->bf == d)
				if(d == -1)	rotateR(pr);
				else	rotateL(pr);
			else
				if(d == -1)	rotateLR(pr);
				else	rotateRL(pr);
			break;
		}
	}

	if(st.isEmpty())	
		ptr = pr;
	else
	{
		st.getTop(q);
		if(q->data > pr->data)	q->leftChild = pr;
		else	q->rightChild = pr;
	}

	return true;
}
