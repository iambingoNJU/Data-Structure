#include <iostream>
using namespace std;

#include "LinkedList.cpp"

int main()
{
	int temp;
	LinkedList<int> list1,list2;
	cout<<"Insert 0-9 into list from head."<<endl;
	for(int i=0;i<10;i++)
		list1.insert(-1,i);
	list1.output();

	cout<<"Insert 10-19 into list from tail."<<endl;
	for(int i=10;i<20;i++)
		list1.insert(list1.lenth()-1,i);
	list1.output();

	cout<<" number 0 is the "<<list1.position(list1.search(0))<<" number in the list."<<endl;

	list1.setData(3,100);
	cout<<"After set the third number to 100."<<endl;
	list1.output();
	
	list1.sort(1);
	cout<<"After sort list."<<endl;
	list1.output();

	list1.getData(3,temp);
	cout<<"Get the third number:"<<temp<<endl;

	list1.remove(0,temp);
	cout<<"After remove the first element."<<endl;
	list1.output();

	LinkedList<int> list3(list1);
	cout<<"list3: ";
	list3.output();

	list2=list3;
	cout<<"list2: ";
	list2.output();

	list1.clear();
	cout<<"After clear."<<endl;
	list1.output();

	cout<<"Create a list.(insert from tail)"<<endl;
	list2.input(0,1);
	list2.output();

	return 0;
}
