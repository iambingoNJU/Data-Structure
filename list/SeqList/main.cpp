#include <iostream>
using namespace std;

#include "SeqList.cpp"

int main()
{
	SeqList<int> sl1,sl2;
	int temp=5;

	cout<<"List default size: "<<sl1.size()<<endl;

	cout<<"Insert 0-9 from head into list."<<endl;
	for(int i=0;i<10;i++)
		sl1.insert(-1,i);
	sl1.output();

	cout<<"Search '5' in the list(return index): "<<sl1.search(temp)<<endl;

	cout<<"Locate the 10th element in the list(return index): "<<sl1.locate(10)<<endl;

	sl1.getData(3,temp);
	cout<<"Before setData, the 4th elements: "<<temp<<endl;
	sl1.setData(3,100);
	sl1.getData(3,temp);
	cout<<"After setData, the 4th elements: "<<temp<<endl;
	
	sl1.remove(3,temp);
	cout<<"After remove the 4th elements: "<<endl;
	sl1.output();

	sl1.clear();

	cout<<"Insert 0-9 from tail into list."<<endl;
	for(int i=0;i<10;i++)
		sl2.insert(sl2.lenth()-1,i);
	sl2.output();

	SeqList<int> sl3(sl2),sl4;
	sl4=sl2;
	sl3.output();
	sl4.output();
	
	sl4.clear();
	sl4.input(-1);
	sl4.output();

	return 0;
}
