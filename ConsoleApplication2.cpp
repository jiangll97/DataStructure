// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string.h>

struct AVLTreeNode
{
	int data;
	AVLTreeNode *Left;
	AVLTreeNode *Right;
	int Height;
};
typedef AVLTreeNode nAVLTree, *pAVLTree;
pAVLTree AVLInsertion(int nodeValue, pAVLTree pavl);
int GetAVLHeight(pAVLTree);
pAVLTree SingleLeftRotation(pAVLTree);
pAVLTree DoubleLeftRotation(pAVLTree);
pAVLTree SingleRightRotation(pAVLTree);
pAVLTree DoubleRightRotation(pAVLTree);
int Max(int hight1, int hight2);
using namespace std;

int main()
{
	int num;
	int i;
	int value;
	pAVLTree pAvl;
	pAvl = NULL;
	cin >> num;
	for (i = 0; i < num; i++)
	{
		cin >> value;
		pAvl = AVLInsertion(value, pAvl);
	}
	cout << pAvl->data;
	return 0;
}
pAVLTree AVLInsertion(int nodeValue, pAVLTree pAvl)
{
	if (pAvl == NULL)
	{
		pAvl = (pAVLTree)malloc(sizeof(nAVLTree));
		pAvl->Left = pAvl->Right = NULL;
		pAvl->data = nodeValue;
		pAvl->Height = 0;
	}
	else if (nodeValue < pAvl->data)//insert in the binary tree,smaller than the data.
	{
		pAvl->Left = AVLInsertion(nodeValue, pAvl->Left);
		if (GetAVLHeight(pAvl->Left) - GetAVLHeight(pAvl->Right) == 2)//Isn't AVLTree
		{
			if (nodeValue < pAvl->Left->data)
				pAvl = SingleLeftRotation(pAvl);
			else
				pAvl = DoubleLeftRotation(pAvl);
		}
	}
	else if (nodeValue>pAvl->data)
	{
		pAvl->Right = AVLInsertion(nodeValue, pAvl->Right);
		if (GetAVLHeight(pAvl->Right) - GetAVLHeight(pAvl->Left) == 2)
		{
			if (nodeValue > pAvl->Right->data)
				pAvl = SingleRightRotation(pAvl);
			else
				pAvl = DoubleRightRotation(pAvl);
		}
	}
	pAvl->Height = Max(GetAVLHeight(pAvl->Left), GetAVLHeight(pAvl->Right)) + 1;
	return pAvl;
}
pAVLTree SingleLeftRotation(pAVLTree A)
{
	pAVLTree B = A->Left;
	A->Left = B->Right;
	B ->Right = A;
	A->Height = Max(GetAVLHeight(A->Left), GetAVLHeight(A->Right)) + 1;
	B->Height = Max(GetAVLHeight(B->Left), A->Height) + 1;
	return B;
}
pAVLTree DoubleLeftRotation(pAVLTree A)
{
	A->Left = SingleRightRotation(A->Left);
	return SingleLeftRotation(A);
}
pAVLTree SingleRightRotation(pAVLTree A)
{
	pAVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetAVLHeight(A->Left), GetAVLHeight(A->Right)) + 1;
	B->Height = Max(GetAVLHeight(B->Right), A->Height) + 1;
	return B;
}
pAVLTree DoubleRightRotation(pAVLTree A)
{
	A->Right = SingleLeftRotation(A->Right);
	return SingleRightRotation(A);
}
int GetAVLHeight(pAVLTree pAvl)
{
	if (pAvl == NULL)
		return 0;
	else
		return pAvl->Height;
}
int Max(int hight1, int hight2)
{
	return hight1 > hight2 ? hight1 : hight2;
}