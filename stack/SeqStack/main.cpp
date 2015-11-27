#include <iostream>
using namespace std;

#include "SeqStack.cpp"

int main()
{
	SeqStack<int> s;
	cout<<"Push 0~59 into stack."<<endl;
	for(int i=0;i<60;i++)
		s.push(i);
	cout<<"After push:"<<" size:"<<s.getSize()<<endl;
	s.showme();

	cout<<"Pop 20 elments out of stack."<<endl;
	int temp;
	for(int i=0;i<20;i++)
	{
		s.pop(temp);
		cout<<temp<<" ";
	}
	cout<<endl;
	cout<<"After pop:"<<endl;
	s.showme();

	s.getTop(temp);
	cout<<"top: "<<temp<<endl<<"size: "<<s.getSize()<<endl;

	s.clear();
	cout<<"After clear:"<<endl;
	s.showme();

	return 0;
}
