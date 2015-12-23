#include <iostream>
#include "../../stack/LinkedStack/LinkedStack.cpp"
using namespace std;

template <class K, class T>
struct AVLnode {
	K key;
	T data;
	int bf;
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

	AVLnode<K,T>* search(K k, AVLnode<K,T> *subTree);
	bool insert(K k,T d,AVLnode<K,T>* &ptr);
	bool remove(K k,T &data,AVLnode<K,T>* &ptr);
	int height(AVLnode<K,T>* subTree);
	int size(AVLnode<K,T>* subTree);
	void show(AVLnode<K,T>* subTree);

public:
	AVLtree(): root(NULL) {}
	bool isEmpty() { return root == NULL; }
	bool insert(K k,T d) { return insert(k,d,root); }
	bool remove(K k,T &d) { return remove(k,d,root); }
	int height() { return height(root); }
	int size() { return size(root); }
	void showInOrder() { inOrder(root, print); }
	void show() { show(root); }
	T search(K k) { AVLnode<K,T> *temp = search(k, root); return temp ? temp->data : 0; }
};

template <class K, class T>
void AVLtree<K,T>::rotateL(AVLnode<K,T>* &ptr)
{
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
bool AVLtree<K,T>::insert(K k, T data, AVLnode<K,T>* &ptr)
{
	AVLnode<K,T> *pr = NULL, *p = ptr, *q;
	LinkedStack<AVLnode<K,T>* > st;
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

	p = new AVLnode<K,T>(k,data);
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
		if(q->key > pr->key)	q->leftChild = pr;
		else	q->rightChild = pr;
	}

	return true;
}

template <class K, class T>
bool AVLtree<K,T>::remove(K k, T &data, AVLnode<K,T>* &ptr)
{
	AVLnode<K,T> *pr = NULL, *p = ptr, *q, *ppr;
	int d, dd = 0;
	LinkedStack<AVLnode<K,T>* > st;
	while(p)
	{
		if(k == p->key)	break;
		pr = p;
		st.push(pr);
		if(k < p->key)	p = p->leftChild;
		else	p = p->rightChild;
	}

	if(p == NULL)	return false;	//Unable to find it.
	if(p->leftChild && p->rightChild)	// p has two children.
	{
		pr = p;
		st.push(pr);
		q = p->leftChild;
		while(q->rightChild)
		{
			pr = q;
			st.push(pr);
			q = q->rightChild;
		}
		p->key = q->key;
		p->data = q->data;
		p = q;
	}

	if(p->leftChild)	q = p->leftChild;
	else	q = p->rightChild;

	if(pr == NULL) ptr = q;		//Node to be deleted is root.
	else
	{
		if(pr->leftChild == p)	pr->leftChild = q;
		else	pr->rightChild = q;
		while(st.pop(pr))
		{
			if(pr->rightChild == q)		pr->bf--;
			else	pr->bf++;
			if(st.getTop(ppr))
				dd = (ppr->leftChild == pr) ? -1 : 1;
			else
				dd = 0;
			
			if(pr->bf == 1 || pr->bf == -1)	break;
			if(pr->bf != 0)
			{
				if(pr->bf < 0) { d = -1; q = pr->leftChild; }
				else	{ d = 1; q = pr->rightChild; }
				if(q->bf == 0)
				{
					if(d == -1)
					{
						rotateR(pr);
						pr->bf = 1;
						pr->leftChild->bf = -1;
					}
					else
					{
						rotateL(pr);
						pr->bf = -1;
						pr->rightChild->bf = 1;
					}
					break;
				}
				if(q->bf == d)
				{
					if(d == -1)	rotateR(pr);
					else	rotateL(pr);
				}
				else
				{
					if(d == -1)	rotateLR(pr);
					else	rotateRL(pr);
				}
				if(dd == -1)	ppr->leftChild = pr;
				else if(dd == 1)	ppr->rightChild = pr;
			}
			q = pr;
		}

		if(st.isEmpty())	ptr = pr;
	}

	data = p->data;
	delete p;
	return true;
}

template <class K, class T>
AVLnode<K,T>* AVLtree<K,T>::search(K k, AVLnode<K,T> *subTree)
{
	if(subTree)
	{
		if(subTree->key == k)
			return subTree;
		else if(subTree->key < k)
			return search(k, subTree->rightChild);
		else
			return search(k, subTree->rightChild);
	}
	else
		return NULL;
}

template <class K, class T>
int AVLtree<K,T>::height(AVLnode<K,T>* subTree)
{
	if(subTree == NULL)
		return 0;
	else
	{
		int i = height(subTree->leftChild);
		int j = height(subTree->rightChild);
		return (i < j) ? j+1 : i+1;
	}
}

template <class K, class T>
int AVLtree<K,T>::size(AVLnode<K,T>* subTree)
{
	if(subTree == NULL)
		return 0;
	else
		return 1 + size(subTree->leftChild) + size(subTree->rightChild);
}

template <class K, class T>
void AVLtree<K,T>::show(AVLnode<K,T>* subTree)
{
	if(subTree)
	{
		cout<<subTree->key<<"\t";
		if(subTree->leftChild)
			cout<<subTree->leftChild->key;
		cout<<"\t";
		if(subTree->rightChild)
			cout<<subTree->rightChild->key;
		cout<<"\t";
		cout<<endl;

		if(subTree->leftChild)
			show(subTree->leftChild);
		if(subTree->rightChild)
			show(subTree->rightChild);
	}

}

