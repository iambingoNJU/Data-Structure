#include <iostream>
#include <string>
using namespace std;

#include "sort.cpp"

#define SIZE 7

typedef struct st1 {
	int id;
	string str;
	bool operator==(st1 s) { return id == s.id; }
	bool operator<(st1 s) { return id < s.id; }
	bool operator<=(st1 s) { return id <= s.id; }
	void operator=(st1 s) { id = s.id;	str = s.str; }
	friend ostream& operator<<(ostream& out, st1 s) { return out<<s.id<<"->"<<s.str; }
} st1;

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
	double s5[] = { 5.33, 8.21, 99.3, 35.484, 29.132, 100.00, 54.2 };
	st1 s6[] = { {3,"333"}, {4, "4444"}, {1, "1"}, {9, "999999999"}, {7, "7777777"}, {6, "666666"}, {8, "88888888"} };
	
	bubble_sort(s1, SIZE);
	print(s1, SIZE, "bubble sort: ");

	insert_sort(s2, 0, SIZE-1);
	print(s2, SIZE, "insert sort: ");

	binary_insert_sort(s3, 0, SIZE-1);
	print(s3, SIZE, "binary insert sort: ");

	shell_sort(s4, 0, SIZE-1);
	print(s4, SIZE, "shell sort: ");

	heap_sort(s5, SIZE);
	print(s5, SIZE, "heap sort: ");

	select_sort(s6, 0, SIZE-1);
	print(s6, SIZE, "select sort: ");

	return 0;
}
