#include <iostream>
using namespace std;

#include "LinkedStack.cpp"

int main()
{
	LinkedStack<char> ls;

	cout<<"Push a-z into stack."<<endl;
	for(int i='a';i<='z';i++)
		ls.push((char)i);
	cout<<"After push:"<<endl;
	ls.showme();

	char temp;
	cout<<"Pop 10 elements out of stack."<<endl;
	for(int i=0;i<10;i++)
	{
		ls.pop(temp);
		cout<<temp<<" ";
	}
	cout<<endl<<"After pop:"<<endl;
	ls.showme();

	ls.getTop(temp);
	cout<<"top: "<<temp<<endl<<"size: "<<ls.getSize()<<endl;

	ls.clear();
	cout<<"After clear:"<<endl;
	ls.showme();

	return 0;
}
