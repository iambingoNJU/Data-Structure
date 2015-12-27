#ifndef __SORT_CPP__
#define __SORT_CPP__

#include "../heap/MinHeap/MinHeap.cpp"

//***********************************************************************************//
/* bubble sort */

template <class T>
void bubble_sort(T s[], int n)
{	
	bool flag;
	for(int i=n; i>1; i--)
	{
		flag = false;
		for(int j=0; j<i-1; j++)
		{
			if(s[j] > s[j+1])
			{
				T temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
				flag = true;
			}
		}
		if(!flag)	break;
	}
}

//***********************************************************************************//
/* quick sort */

template <class T>
int quick_sort_partition(T s[], int low, int high)
{
	int pivotpos = low;
	T pivot = s[low];
	for(int i=low+1; i<=high; i++)
		if(s[i] < pivot)
		{
			pivotpos++;
			if(pivotpos != i)
			{
				T temp = s[i];
				s[i] = s[pivotpos];
				s[pivotpos] = temp;
			}
		}
	s[low] = s[pivotpos];
	s[pivotpos] = pivot;

	return pivotpos;
}

template <class T>
void quick_sort(T s[], int left, int right)
{
	if(left < right)
	{
		int pivotpos = quick_sort_partition(s, left, right);
		quick_sort(s, left, pivotpos-1);
		quick_sort(s, pivotpos+1, right);
	}
}

//***********************************************************************************//
/* insert sort */

template <class T>
void insert_sort(T s[], int left, int right)
{
	T temp;
	int i, j;
	for(i=left+1; i<=right; i++)
		if(s[i] < s[i-1])
		{
			temp = s[i];
			j = i-1;
			do {
				s[j+1] = s[j];
				j--;
			} while(j>=left && temp<s[j]);
			s[j+1] = temp;
		}
}

template <class T>
void binary_insert_sort(T s[], int left, int right)
{
	T temp;
	int low, high, middle;
	for(int i=left+1; i<=right; i++)
	{
		temp = s[i];
		low = left;
		high = i-1;
		while(low <= high)
		{
			middle = (low + high)/2;
			if(temp < s[middle])
				high = middle - 1;
			else
				low = middle + 1;
		}
		for(int k=i-1; k>=low; k--)	s[k+1] = s[k];
		s[low] = temp;
	}
}

template <class T>
void shell_sort(T s[], int left, int right)
{
	T temp;
	int i, j, gap = right - left + 1;
	do {
		gap = gap/3 +1;
		for(i=left+gap; i<=right; i++)
			if(s[i] < s[i-gap])
			{
				temp = s[i];
				j = i - gap;
				do {
					s[j+gap] = s[j];
					j -= gap;
				} while(j>=left && temp<s[j]);
				s[j+gap] = temp;
			}
	} while(gap > 1);
}

//***********************************************************************************//
/* select sort */

template <class T>
void select_sort(T s[], int left, int right)
{
	T temp;
	for(int i=left; i<right; i++)
	{
		int k = i;
		for(int j=i+1; j<=right; j++)
			if(s[j] < s[k])	k = j;

		if(k != i)
		{
			temp = s[k];
			s[k] = s[i];
			s[i] = temp;
		}
	}
}

template <class T>
void heap_sort(T s[], int sz)
{
	MinHeap<T> mh(s, sz);
	T temp;
	for(int i=0; i<sz; i++)
	{
		mh.removeMin(temp);
		s[i] = temp;
	}
}

//***********************************************************************************//

#endif
