#ifndef __SORT_CPP__
#define __SORT_CPP__

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

//***********************************************************************************//

#endif
