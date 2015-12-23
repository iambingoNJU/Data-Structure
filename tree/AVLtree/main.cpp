#include "AVLtree.cpp"

int main()
{
	AVLtree<int,char> at;

	//at.insert(9,'n');
	//at.insert(8,'l');
	//at.insert(7,'m');
	//at.insert(5,'t');
	//at.insert(4,'r');
	//at.insert(3,'e');
	//at.insert(2,'w');
	//at.insert(1,'q');

	at.insert(1,'q');
	at.insert(2,'w');
	at.insert(7,'m');
	at.insert(8,'l');
	at.insert(9,'n');

	at.showInOrder();

	return 0;
}
