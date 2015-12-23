#include "AVLtree.cpp"
#include <string>

int main()
{
/*
	AVLtree<int,char> at;

	at.insert(15,'g');
	at.insert(12,'w');
	at.insert(10,'v');
	at.insert(9,'n');
	at.insert(8,'l');
	at.insert(7,'m');
	at.insert(5,'t');
	at.insert(4,'r');
	at.insert(3,'e');
	at.insert(2,'w');
	at.insert(1,'q');
	at.insert(11,'b');
	at.insert(16,'n');
	at.insert(13,'x');

	char temp;
	at.remove(4,temp);
	at.remove(9,temp);

	at.show();
*/
	AVLtree<string,int> at;

	at.insert("DEC",12);
	at.insert("FEB",2);
	at.insert("NOV",11);
	at.insert("OCT",10);
	at.insert("JUL",7);
	at.insert("SEP",9);
	at.insert("AUG",8);
	at.insert("APR",4);
	at.insert("MAR",3);
	at.insert("MAY",5);
	at.insert("JUN",6);
	at.insert("JAN",1);

	at.showInOrder();

	cout<<"height: "<<at.height()<<endl;
	cout<<"SEP data: "<<at.search("SEP")<<endl;
	cout<<"number: "<<at.size()<<endl;
	cout<<endl<<endl;

	int temp;
	at.remove("MAY",temp);
	at.remove("FEB",temp);
	at.show();
	cout<<"number: "<<at.size()<<endl;

	return 0;
}
