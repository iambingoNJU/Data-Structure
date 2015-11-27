#include <iostream>
using namespace std;

#include "LinkedQueue.cpp"

int main()
{
	LinkedQueue<int> q;
	cout<<"EnQueue 0-19."<<endl;
	for(int i=0;i<20;i++)
		q.enQueue(i);
	cout<<"After enQueue:"<<endl;
	q.showme();

	cout<<"DeQueue 10 elements out from queue."<<endl;
	int x,y;
	for(int i=0;i<10;i++)
	{
		q.deQueue(x);
		cout<<x<<" ";
	}
	cout<<endl;
	cout<<"After deQueue:"<<endl;
	q.showme();

	q.getFront(x);
	q.getRear(y);
	cout<<"top: "<<x<<endl<<"rear: "<<y<<endl<<"size: "<<q.getSize()<<endl;

	q.clear();
	cout<<"After clear:"<<endl;
	q.showme();

	return 0;
}
