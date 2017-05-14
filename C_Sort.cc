#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

/* Check to see if elements of memory are sorted */
bool IsSorted(int *front, int *back)
{
	for (int *i = front; (back - i) > 1; i++)
	{
		if(*i > *(i+1))
		{
			return false;
		}
	}
	return true;
}

/* Check to see if elements of and array is sorted */
bool IsSorted(int *ary, int length)
{
	return IsSorted(ary,ary+length);
}

/*Swap two integers in memory*/
void Swap(int *x, int *y)
{
	int z = *x;
	*x = *y;
	*y = z;
	return;
}

/* An implementation of Qsort using a block of memory*/
void Qsort(int *front, int *back)
{
	if((front - back)>=0)
	{
		return;
	}
	int *it;
	it = front;
	for(int *i = front; (back - i)>0; i++)
	{
		if(*i <= *(back-1))
		{
			Swap(i,it);
			it++;
		}
	}

	Qsort(front,it - 1);
	Qsort(it,back);
	return;
}

/* A Wrapper for Qsort */
void Qsort(int *ary, int length)
{
	int *ptrEnd = ary + length;
	Qsort(ary,ptrEnd);
}

int main()
{

	cout << "\n";

	static int INT_MAX = 2147483647;
	int length = 1000000;

	srand(time(NULL));
	int ary[length];

	for(int i = 0; i<length; i++)
	{
		int rnd = rand() % length;
		ary[i] = rnd;
	}

	cout << "\n";
	cout << IsSorted(ary,length);
	cout << "\n\n";

	Qsort(ary,length);

	cout << "\n";
	cout << IsSorted(ary,5);
	cout << "\n\n";
	
	return 0;
}
