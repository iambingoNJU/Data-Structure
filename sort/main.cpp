#include <iostream>
#include <string>
using namespace std;

#include "sort.cpp"

#define SIZE 7

template <class T>
void print(T s[], int sz, const char* comment)
{
	cout<<comment;
	for(int i=0; i<sz; i++)
		cout<<s[i]<<", ";
	cout<<endl;
}

int main()
{
	int s1[] = { 3, 1, 7, 9, 5, 10, 6 };
	string s2[] = { "hello", "world", "march", "huahua", "sort", "size", "namespace" };
	char s3[] = { 'h', 'b', 'a', 'n', 'v', 'x', 'm' };
	float s4[] = { 0, 5.523, 5.522, 5.521, 9.44, 100, 39.44 };
	
	bubble_sort(s1, SIZE);
	print(s1, SIZE, "bubble sort: ");

	insert_sort(s2, 0, SIZE-1);
	print(s2, SIZE, "insert sort: ");

	quick_sort(s3, 0, SIZE-1);
	print(s3, SIZE, "quick sort: ");

	quick_sort(s4, 0, SIZE-1);

	return 0;
}
