#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

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

/* Check to see if elements of an array are sorted */
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

/* Shuffle sequential elements of memory */
void shuffle(int *front, int *back)
{
	for (int *i = front; (back - i) > 1; i++)
	{
		int len = back - i;
		int rnd = rand() % len;
		Swap(i, i+rnd);
	}
}

/* Shuffle an array */
void shuffle(int *ary, int length)
{
	shuffle(ary, ary+length);
}

/* An implementation of bubble sort using a block of memory*/
void BubbleSort(int *front, int *back)
{
	if((front - back)>=0)
	{
		return;
	}
	bool sorted = false;
	while(!sorted)
	{
		sorted = true;

		for(int *i = front; (back - i - 1)>0; i++)
		{
			if(*i > *(i+1))
			{
				Swap(i,i+1);
				sorted = false;
			}
		}	
	}
}

/* A wrapper for BubbleSort which sorts an array */
void BubbleSort(int *ary, int length)
{
	int *ptrEnd = ary + length;
	BubbleSort(ary,ptrEnd);
}

/* An implementation of selection sort using a block of memory*/
void SelectionSort(int *front, int *back)
{
	if((front - back)>=0)
	{
		return;
	}
	int *min = front;
	for(int *i = front; (back - i)>0; i++)
	{
		if(*i < *min)
		{
			min = i;
		}
	}	
	Swap(front, min);
	SelectionSort(front+1,back);
}

/* A wrapper for SelectionSort which sorts an array */
void SelectionSort(int *ary, int length)
{
	int *ptrEnd = ary + length;
	SelectionSort(ary,ptrEnd);
}

/* An implementation of quick sort using a block of memory*/
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

/* A wrapper for Qsort which sorts an array */
void Qsort(int *ary, int length)
{
	int *ptrEnd = ary + length;
	Qsort(ary,ptrEnd);
}

/* An implementation of counting sort using a block of memory*/
void countingSort(int *front, int *back, int max)
{
	/* initialize the auxiliary array */
	int count[max];
	for(int i=0; i<max; i++)
	{
		count[i]=0;
	}

	for(int *i = front; (back - i)>0; i++)
	{
		count[*i] += 1;
	}

	int *it = front;
	for(int i=0; i<max; i++)
	{
		while(count[i]>0)
		{
			*it = i;
			it++;
			count[i] = count[i]-1;
		}
	}
}

/* A wrapper for countingSort which sorts an array */
void countingSort(int *ary, int length, int max)
{
	int *ptrEnd = ary + length;
	countingSort(ary, ptrEnd, max);
}

int main()
{

	cout << "\n";

	static int INT_MAX = 2147483647;
	int length = 10000;

	clock_t start;
	clock_t finish;
	double duration;

	srand(time(NULL));

	start = clock();

	int ary[length];

	for(int i = 0; i<length; i++)
	{
		int rnd = rand() % length;
		ary[i] = rnd;
	}

	finish = clock();
	duration = (finish - start)/ (double) CLOCKS_PER_SEC;


        bool sorted = IsSorted(ary,length);

	cout << "\n";
        if(!sorted)
	{
		cout<<"Created an unsorted list in time " << duration << " seconds\n\n";
	}
	else
	{
		cout<<"Failed to create an unsorted list\n\n";
		return -1;
	}

	start = clock();
	Qsort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"Qsort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"Qsort succesfully sorted the list in " << duration << " seconds\n\n";
	}

	start = clock();
	shuffle(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"succesfully re-shuffled the list in "<< duration <<" seconds\n\n";
	}
	else
	{
		cout<<"failed to reshuffle the list\n\n";
		return -1;
	}

	start = clock();
	BubbleSort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"BubbleSort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"BubbleSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}

	start = clock();
	shuffle(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"succesfully re-shuffled the list in "<< duration <<" seconds\n\n";
	}
	else
	{
		cout<<"failed to reshuffle the list\n\n";
		return -1;
	}

	start = clock();
	SelectionSort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"SelectionSort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"SelectionSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}

	start = clock();
	shuffle(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"succesfully re-shuffled the list in "<< duration <<" seconds\n\n";
	}
	else
	{
		cout<<"failed to reshuffle the list\n\n";
		return -1;
	}

	start = clock();
	countingSort(ary,length,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"countingSort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"countingSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}

	start = clock();
	shuffle(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"succesfully re-shuffled the list in "<< duration <<" seconds\n\n";
	}
	else
	{
		cout<<"failed to reshuffle the list\n\n";
		return -1;
	}
	
	return 0;
}
