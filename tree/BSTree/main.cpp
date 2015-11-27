#include "BSTree.cpp"
#include <string>

int main()
{
	BSTree<int,float> tree;
	BinTreeNode<int,float> s[]={ {2,9.9},{1,103.23},{3,23.54},{0,0.0},{0,0.0},{0,0.0},{0,0.0} };
	tree.create1(s);
	tree.showInOrder();
	cout<<tree.search(3)<<endl;

	tree.remove(3);
	tree.showLevelOrder();

	tree.remove(2);
	tree.showLevelOrder();

	tree.remove(1);
	tree.showLevelOrder();

	return 0;
}
