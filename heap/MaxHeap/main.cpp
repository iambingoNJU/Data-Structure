#include "MaxHeap.cpp"
#define ARR_SIZE 15

int main()
{
	int arr[] = { 2, 5, 8, 3, 45, 23, 1, 29, 100, 40, 10, 30, 22, 0, -3 };

	MaxHeap<int> mh(arr, ARR_SIZE);

	mh.insert(-6);
	mh.insert(39);

	int temp;
	for(int i=0; i<ARR_SIZE+2; i++)
	{
		mh.removeMax(temp);
		cout<<temp<<"->";
	}
	cout<<"\b\b  "<<endl;

	return 0;
}
