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
}

/* A wrapper for Qsort which sorts an array */
void Qsort(int *ary, int length)
{
	int *ptrEnd = ary + length;
	Qsort(ary,ptrEnd);
}

/* Return the minimum of two numbers */
int min(int x, int y)
{
	if(x<y)
	{
		return x;
	}
	return y;
}

/* An implementation of merge sort using a block of memory */
void MergeSort(int *front, int *back, int *tmp)
{
	int len = back - front;
	int *tmp2 = tmp + len;

	if(len==2)
	{
		if(*front > *(front+1))
		{
			Swap(front,front+1);
		}
		return;
	}
	if(len <= 1)
	{
		return;
	}
	int half = len/2;
	MergeSort(front, front+half, tmp);
	MergeSort(front+half, back, tmp);
	int *it1=front;
	int *it2=front+half;

	/* merge */
	for(int *i= tmp; (tmp2-i)>0; i++)
	{
		if((it1-front)<half and (it2-(front+half))<(back-(front+half)) and *it1<=*it2)
		{
			*i = *it1;
			it1++;
		}
		else if((it1-front)<half and (it2-(front+half))<(back-(front+half)) and *it1>*it2)
		{
			*i = *it2;
			it2++;
		}
		else if((it1-front)>=half)
		{
			*i = *it2;
			it2++;
		}
		else
		{
			*i = *it1;
			it1++;
		}
	}

	/* Write merged list back to the original array */
	for(int *i=tmp;(tmp2-i)>0;i++)
	{
		*(front + (i-tmp)) = *i;
	}
	
}

/* A wrapper for MergeSort which sorts an array */
void MergeSort(int *ary, int length)
{
	int tmp[length];
	int *ptrEnd = ary + length;
	MergeSort(ary, ptrEnd, tmp);
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
	int length = 5000;

	clock_t start;
	clock_t finish;
	double duration;

	srand(time(NULL));

	int ary[length];
	int ary_check[length];

	for(int i = 0; i<length; i++)
	{
		ary[i] = i;
		ary_check[i] = i;
	}

	start = clock();
	shuffle(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	bool sorted = IsSorted(ary,length);

        if(!sorted)
	{
		cout<<"succesfully re-shuffled the list in "<< duration <<" seconds\n\n";
	}
	else
	{
		cout<<"failed to reshuffle the list\n\n";
		return -1;
	}

	
	/* Test Qsort */

	start = clock();
	Qsort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);
	bool changed = false;

	for(int i=0; i<length; i++)
	{
		if(ary[i] != ary_check[i])
		{
			changed = true;
		}
	}

	if(changed)
	{
		cout<<"list was altered by Qsort\n\n";
	}
	else if(!sorted)
	{
		cout<<"Qsort unsuccesful\n\n";
	}
	else
	{
		cout<<"Qsort succesfully sorted the list in " << duration << " seconds\n\n";
	}

	/* re-shuffle the list */
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

	/* Test BubbleSort */
	start = clock();
	BubbleSort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);
	changed = false;

	for(int i=0; i<length; i++)
	{
		if(ary[i] != ary_check[i])
		{
			changed = true;
		}
	}

	if(changed)
	{
		cout<<"list was altered by BubbleSort\n\n";
	}
	else if(!sorted)
	{
		cout<<"BubbleSort unsuccesful\n\n";
	}
	else
	{
		cout<<"BubbleSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}

	/* re-shuffle the list */
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

	/* Test SelectionSort */
	start = clock();
	SelectionSort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);
	changed = false;

	for(int i=0; i<length; i++)
	{
		if(ary[i] != ary_check[i])
		{
			changed = true;
		}
	}

	if(changed)
	{
		cout<<"list was altered by SelectionSort\n\n";
	}
	else if(!sorted)
	{
		cout<<"SelectionSort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"SelectionSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}

	/* re-shuffle the list */
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

	/* Test countingSort */
	start = clock();
	countingSort(ary,length,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);
	changed = false;

	for(int i=0; i<length; i++)
	{
		if(ary[i] != ary_check[i])
		{
			changed = true;
		}
	}

	if(changed)
	{
		cout<<"list was altered by countingSort\n\n";
	}
	else if(!sorted)
	{
		cout<<"countingSort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"countingSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}

	/* re-shuffle the list */
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

	/* Test MergeSort */
	start = clock();
	MergeSort(ary,length);
	finish = clock();

	duration = (finish - start)/ (double) CLOCKS_PER_SEC;
	sorted = IsSorted(ary,length);
	changed = false;

	for(int i=0; i<length; i++)
	{
		if(ary[i] != ary_check[i])
		{
			changed = true;
		}
	}

	if(changed)
	{
		cout<<"list was altered by MergeSort\n\n";
	}
	else if(!sorted)
	{
		cout<<"MergeSort unsuccesful\n\n";
		return -1;
	}
	else
	{
		cout<<"MergeSort succesfully re-sorted the list in " << duration << " seconds\n\n";
	}
	
	return 0;
}
