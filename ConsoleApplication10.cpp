// ConsoleApplication10.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<stdlib.h>
#define MAX 100001
#define MaxDigit 4
#define Radix 10
using namespace std;
typedef long ElementType;
typedef struct Node *PtrToNode;
void Swap(ElementType *a, ElementType *b);
void PercDown(ElementType A[], long p, long N);
void HeapSort(ElementType A[], long N);
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);
void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd);
void MergeSort(ElementType A[], int N);
ElementType Median3(ElementType A[], int Left, int Right);
void Qsort(ElementType A[], int Left, int Right);
void QuickSort(ElementType A[], int N);
int GetDigit(int X, int D);
void LSDRadixSort(ElementType A[], int N);

void Swap(ElementType *a, ElementType *b)
{
	ElementType t = *a;
	*a = *b;
	*b = t;
}
void PercDown(ElementType A[], long p, long N)
{
	int Parent, Child;
	ElementType X;

	X = A[p];
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
	{
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child] < A[Child + 1]))
			Child++;
		if (X >= A[Child]) break;
		else
			A[Parent] = A[Child];
	}
	A[Parent] = X;
}
void HeapSort(ElementType A[], long N)
{
	long i;
	for (i = N / 2 - 1; i >= 0; i--)//Build the maxheap.
		PercDown(A, i, N);
	for (i = N - 1; i > 0; i--)
	{
		Swap(&A[0],&A[i]);
		PercDown(A, 0, i);
	}
}
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
	int LeftEnd, NumElements, Tmp;
	int i;
	LeftEnd = R - 1;
	Tmp = L;
	NumElements = RightEnd - L + 1;
	while (L <= LeftEnd&&RightEnd)
	{
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++];
		else
			TmpA[Tmp++] = A[R++];
	}
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++];
	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd];
}
void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd)
{
	int Center;
	if (L < RightEnd)
	{
		Center = (L + RightEnd) / 2;
		Msort(A, TmpA, L, Center);
		Msort(A, TmpA, Center + 1, RightEnd);
		Merge(A, TmpA, L, Center + 1, RightEnd);
	}
}
void MergeSort(ElementType A[], int N)
{
	ElementType *TmpA;
	TmpA = (ElementType*)malloc(N*sizeof(ElementType));
	if (TmpA != NULL)
	{
		Msort(A, TmpA, 0, N - 1);
		free(TmpA);
	}
	else
		cout << "The space isn't enough.";
}
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);
	/*Now A[Left]<=A[Center]<=A[Right]*/
	Swap(&A[Center], &A[Right] - 1);
	return A[Right - 1];
}
void Qsort(ElementType A[], int Left, int Right)
{
	int Pivot, Cutoff, Low, High;
	if (Cutoff <= Right - Left)
	{
		Pivot = Median3(A, Left, Right);
		Low = Left; High = Right - 1;
		while (1)
		{
			while (A[++Low] < Pivot);
			while (A[--High] > Pivot);
			if (Low < High) Swap(&A[Low], &A[High]);
			else break;
		}
		Swap(&A[Low], &A[Right - 1]);
		Qsort(A, Left, Low - 1);
		Qsort(A, Low + 1, Right);
	}
	else;
}
void QuickSort(ElementType A[], int N)
{
	Qsort(A, 0, N - 1);
}
struct Node {
	int Key;
	PtrToNode next;
};
struct HeadNode {
	PtrToNode Head, tail;
};
typedef struct HeadNode Bucket[Radix];
int GetDigit(int X, int D)
{
	int d, i;
	for (i = 1; i < D; i++)
	{
		d = X%Radix;
		X /= Radix;
	}
	return D;
}
void LSDRadixSort(ElementType A[], int N)
{
	int D, Di, i;
	Bucket B;
	PtrToNode tmp, p, List = NULL;
	for (i = 0; i < Radix; i++)
		B[i].Head = B[i].tail = NULL;
	for (i = 0; i < N; i++)
	{
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->Key = A[i];
		tmp->next = List;
		List = tmp;
	}
	for (D = 1; D <= MaxDigit; D++)
	{
		p = List;
		while (p)
		{
			Di = GetDigit(p->Key, D);
			tmp = p; p = p->next;
			tmp->next = NULL;
			if (B[Di].Head == NULL)
				B[Di].Head = B[Di].tail = tmp;
			else
			{
				B[Di].tail->next = tmp;
				B[Di].tail = tmp;
			}
		}
		List = NULL;
		for (Di = Radix - 1; Di >= 0; Di--)
		{
			if (B[Di].Head)
			{
				B[Di].tail->next = List;
				List = B[Di].Head;
				B[Di].Head = B[Di].tail = NULL;
			}
		}
	}
	for (i = 0; i < N; i++)
	{
		tmp = List;
		List = List->next;
		A[i] = tmp->Key;
		free(tmp);
	}
}

int main()
{
	long N, A[MAX];
	cin >> N;
	long i;
	for (i = 0; i < N; i++)
		cin >> A[i];
	HeapSort(A, N);
	for (i = 0; i < N-1; i++)
		cout << A[i]<<" ";
	cout << A[i];
    return 0;
}

