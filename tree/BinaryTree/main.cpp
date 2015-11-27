#include <iostream>
using namespace std;

#include "BinaryTree.cpp"

int main()
{
	char str[100];
	while(cin>>str)
	{
		BinaryTree<char> t;
		t.create(str);

		t.preOrder_1rec();
		cout<<endl;
		t.preOrder_0rec();
		cout<<endl;
	}
}
