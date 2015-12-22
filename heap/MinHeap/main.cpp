#include "MinHeap.cpp"
#define ARR_SIZE 12

int main()
{
	int arr[] = { 3, 45, 23, 1, 29, 100, 40, 10, 30, 22, 0, -3 };

	MinHeap<int> mh(arr, ARR_SIZE);

	mh.insert(2);
	mh.insert(33);

	int temp;
	for(int i=0; i<ARR_SIZE+2; i++)
	{
		mh.min(temp);
		cout<<temp<<"->";
	}
	cout<<"\b\b  "<<endl;

	return 0;
}
