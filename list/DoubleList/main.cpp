#include "DoubleList.cpp"

int main()
{
	DoubleList<int> dl(-1);

	for(int i=0; i<10; i++)
		dl.insert(i, i+10, 1);

	for(int i=0; i<5; i++)
		dl.insert(i, i, 0);

	cout<<dl<<endl;

	int temp;
	for(int i=0; i<5; i++)
	{
		dl.remove(i+1, temp, i%2);
		cout<<temp<<" ";
	}
	cout<<endl;

	cout<<dl<<endl;

	return 0;
}
