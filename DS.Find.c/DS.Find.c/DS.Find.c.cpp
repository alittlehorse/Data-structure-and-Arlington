// DS.Find.c.cpp: 定义控制台应用程序的入口点。
//


//**************************************二分查找********************************
//**************************************顺序查找********************************
//**************************************索引查找********************************
//**************************************散列************************************
//**************************************平衡查找树******************************
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct List
{
	int length;
	int data[MAXSIZE];
}List,*PList;


//***************************************************函数原型**************************
void InputData(PList L, int m);
void visit(List L);

//O(logN),但是必须是有序的
int BinarySearch(List A, int K);


//****************************************************************************************
int main()
{
	List L;
	L.length = 0;
	InputData(&L, 5);
	visit(L);
	int i = BinarySearch(L, 3);
	printf("\n找到第%d个", i);
	system("pause");
    return 0;
}
//****************8二分查找,数据元素的下标从零开始***********************
int BinarySearch(List A, int K)
{
	int left, right, mid, NoFound = -1;
	left = 0;            //初始左边界	
	right = A.length-1;  //初始右边界
	while (left <= right)          //当left>right时,循环才终止
	{
		mid = (left + right) / 2;
		if (K < A.data[mid]) right = mid - 1;
		else if (K > A.data[mid])left = mid + 1;
		else return mid;
	}
	return NoFound;
}
void InputData(PList L,int m)
{
	for (int i = 1; i <= m; i++)
	{
		printf("请输入第%d个数字",i);
		scanf_s("%d",&L->data[i-1]);
		L->length++;
	}
	return;
}
void visit(List L)
{
	for (int i = 1; i <= L.length; i++)
	{
		printf("%d", L.data[i - 1]);
	}
	return;
}

