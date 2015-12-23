#include <iostream>
#include "../../queue/SeqQueue/SeqQueue.cpp"
using namespace std;

#define EndMark 0

template <class K, class T>
struct BinTreeNode
{
	K key;
	T data;
	BinTreeNode<K,T> *leftChild, *rightChild;
	BinTreeNode(): leftChild(NULL), rightChild(NULL) {}
	BinTreeNode(K k,T x,BinTreeNode<K,T> *l=NULL,BinTreeNode<K,T> *r=NULL): key(k), data(x), leftChild(l), rightChild(r) {}
};

template <class K, class T>
void print(BinTreeNode<K,T> *p)
{
	cout<<p->key<<"-"<<p->data<<endl;
}

template <class K, class T>
class BSTree
{
protected:
	BinTreeNode<K,T> *root;
	void destroy(BinTreeNode<K,T> *subTree);
	void preOrder(BinTreeNode<K,T> *subTree, void (*visit)(BinTreeNode<K,T> *p));
	void inOrder(BinTreeNode<K,T> *subTree, void (*visit)(BinTreeNode<K,T> *p));
	void postOrder(BinTreeNode<K,T> *subTree, void (*visit)(BinTreeNode<K,T> *p));
	void levelOrder(void (*visit)(BinTreeNode<K,T> *p));
	bool isBST(BinTreeNode<K,T>* subTree);
	BinTreeNode<K,T>* search(K k, BinTreeNode<K,T> *subTree); 
	bool insert(K k,T x,BinTreeNode<K,T> *&t);
	bool remove(K k,BinTreeNode<K,T> *&t);
public:
	BSTree(): root(NULL) {}
	~BSTree() { destroy(root);}
	bool isEmpty() { return root==NULL;}
	bool create1(BinTreeNode<K,T> *s);
	void create2();
	void showLevelOrder() { levelOrder(print); }
	void showInOrder() { inOrder(root,print); }
	bool isBST() { return isBST(root); }
	T search(K k) { BinTreeNode<K,T> *temp=search(k,root); return temp!=NULL? temp->data : 0; }
	bool insert(K k,T x) { return insert(k,x,root); }
	bool remove(K k) { return remove(k,root); }
	void max();
};

template <class K, class T>
void BSTree<K,T>::preOrder(BinTreeNode<K,T> *subTree,void (*visit)(BinTreeNode<K,T> *p))
{
	if(subTree)
	{
		visit(subTree);
		inOrder(subTree->leftChild,visit);
		inOrder(subTree->rightChild,visit);
	}
}

template <class K, class T>
void BSTree<K,T>::inOrder(BinTreeNode<K,T> *subTree,void (*visit)(BinTreeNode<K,T> *p))
{
	if(subTree)
	{
		inOrder(subTree->leftChild,visit);
		visit(subTree);
		inOrder(subTree->rightChild,visit);
	}
}

template <class K, class T>
void BSTree<K,T>::postOrder(BinTreeNode<K,T> *subTree,void (*visit)(BinTreeNode<K,T> *p))
{
	if(subTree)
	{
		inOrder(subTree->leftChild,visit);
		inOrder(subTree->rightChild,visit);
		visit(subTree);
	}
}

template <class K, class T>
void BSTree<K,T>::levelOrder(void (*visit)(BinTreeNode<K,T> *p))
{
	SeqQueue<BinTreeNode<K,T>*> Q;
	BinTreeNode<K,T> *temp=root;
	Q.enQueue(temp);
	while(Q.deQueue(temp))
	{
		visit(temp);
		if(temp->leftChild)		Q.enQueue(temp->leftChild);
		if(temp->rightChild)	Q.enQueue(temp->rightChild);
	}
}

template <class K, class T>
void BSTree<K,T>::destroy(BinTreeNode<K,T> *subTree)
{
	if(subTree!=NULL)
	{
		destroy(subTree->leftChild);
		destroy(subTree->rightChild);
		delete subTree;
	}
}

template <class K, class T>
bool BSTree<K,T>::create1(BinTreeNode<K,T> *s)
{
	if(s[0].key==EndMark)	return false;

	root=new BinTreeNode<K,T>(s[0].key,s[0].data);

	SeqQueue<BinTreeNode<K,T>*> q;
	BinTreeNode<K,T> *temp;
	int i=1;
	q.enQueue(root);
	while(q.deQueue(temp))
	{

		if(s[i].key!=EndMark)
		{
			BinTreeNode<K,T> *l=new BinTreeNode<K,T>(s[i].key,s[i].data);
			temp->leftChild=l;
			q.enQueue(l);
		}
		else
			temp->leftChild=NULL;
		i++;

		if(s[i].key!=EndMark)
		{
			BinTreeNode<K,T> *r=new BinTreeNode<K,T>(s[i].key,s[i].data);
			temp->rightChild=r;
			q.enQueue(r);
		}
		else
			temp->rightChild=NULL;

		i++;
	}

	return true;
}

template <class K, class T>
void BSTree<K,T>::create2()
{
	K k;
	T d;
	destroy(root);
	cin>>k;
	while(k!=EndMark)
	{
		cin>>d;
		insert(k,d,root);
		cin>>k;
	}
}

template <class K, class T>
bool BSTree<K,T>::isBST(BinTreeNode<K,T> *subTree)
{
	if(subTree)
	{
		bool check1,check2,check3,check4;
		if(subTree->leftChild)
		{
			check1=subTree->leftChild->key < subTree->key;
			BinTreeNode<K,T> *temp1=subTree->leftChild;
			while(temp1->rightChild)
				temp1=temp1->rightChild;
			check3=temp1->key < subTree->key;
		}
		else
		{
			check1=true;
			check3=true;
		}

		if(subTree->rightChild)
		{
			check2=subTree->rightChild->key > subTree->key;
			BinTreeNode<K,T> *temp2=subTree->rightChild;
			while(temp2->leftChild)
				temp2=temp2->leftChild;
			check4=temp2->key > subTree->key;
		}
		else
		{
			check2=true;
			check4=true;
		}


		return check1 && check2 && check3 && check4 && isBST(subTree->leftChild) && isBST(subTree->rightChild);
	}

	return true;
}

template <class K, class T>
BinTreeNode<K,T>* BSTree<K,T>::search(K k, BinTreeNode<K,T> *subTree)
{
	if(subTree==NULL)	return NULL;
	else if(k < subTree->key)		return search(k,subTree->leftChild);
	else if(k > subTree->key)		return search(k,subTree->rightChild);
	else	return subTree;
}

template <class K, class T>
bool BSTree<K,T>::insert(K k,T x,BinTreeNode<K,T> *&t)
{
	if(t==NULL)
	{
		t=new BinTreeNode<K,T>(k,x);
		assert(t);
		return true;
	}		
	else if(k < t->key)
		return insert(k,x,t->leftChild);
	else if(k > t->key)
		return insert(k,x,t->rightChild);
	else	return false;
}

template <class K, class T>
bool BSTree<K,T>::remove(K k,BinTreeNode<K,T> *&t)
{
	if(t!=NULL)
	{
		if(k < t->key)	return remove(k,t->leftChild);
		else if( k > t->key)	return remove(k,t->rightChild);
		else
		{
			BinTreeNode<K,T> *temp;
			if(t->leftChild && t->rightChild)
			{
				temp=t->rightChild;
				while(temp->leftChild)	temp=temp->leftChild;
				t->key=temp->key;
				t->data=temp->data;
				return remove(t->key,t->rightChild);
			}
			else
			{
				temp=t;
				if(t->leftChild)	t=t->leftChild;
				else	t=t->rightChild;
				delete temp;
				return true;
			}
		}
	}

	return false;
}

template <class K, class T>
void BSTree<K,T>::max()
{
	BinTreeNode<K,T> *temp=root;
	if(root==NULL)
		return;
	
	int cnt=1;
	while(temp->rightChild!=NULL)
	{
		temp=temp->rightChild;
		cnt++;
	}

	cout<<temp->key<<"-"<<temp->data<<endl<<"Height: "<<cnt<<endl;
}
