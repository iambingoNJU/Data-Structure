#include <iostream>
using namespace std;

#include "BSTree.cpp"

template <class K, class T>
struct AVLnode: public BinTreeNode<K,T> {
	int bf;
	AVLnode() : bf(0) { leftChild=NULL; rightChild=NULL;}
	//AVLnode() : BinTreeNode(), bf(0) {}
	//AVLnode(K k,T d,AVLnode<K,T> *l=NULL,AVLnode<K,T> *r=NULL) : bf(0) { key=k; data=d; leftChild=l; rightChild=r;}
};

template <class K,class T>
class AVLtree : public BSTree<K,T> {
public:
	AVLtree() : BSTree() {}
	//bool insert(K k,T d) { return insert(k,d,root);
	//bool remove(K k,T &d) { return remove(k,d,root);
	//int height() { return height(root); }
protected:
/*	AVLnode<K,T>* search(K k);
	bool insert(K k,T d,AVLnode<K,T>* &ptr);
	bool remove(K k,T &d,AVLnode<K,T>* &ptr);
	void rotateL(AVLnode<K,T>* &ptr);
	void rotateR(AVLnode<K,T>* &ptr);
	void rotateLR(AVLnode<K,T>* &ptr);
	void rotateRL(AVLnode<K,T>* &ptr);
	int height(AVLnode<K,T>* ptr);
	*/
};
