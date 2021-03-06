// DS.PriorityQueue.c.cpp: 定义控制台应用程序的入口点。
//
//**********************************************************************
//*                                                                    *
//*                          堆及其应用                                *
//*                                                                    *
//**********************************************************************
#include "stdafx.h"
#include <stdlib.h>
//用完全二叉树表示


typedef int ElementType;

typedef struct HeapStruct *MaxHeap,*MinHeap;
//有序性:根的位置为最大值;
struct HeapStruct {
	ElementType *Elements;/*储存堆元素的数组*/
	int Size;/*对的当前元素个数*/
	int Capacity;/*堆的最大容量*/
};

//哈夫曼树没有度为1的节点
//n个叶子节点的哈夫曼树共有2n-1个节点
//哈夫曼树的任一非叶节点的左右子树交换后仍是哈夫曼树
//对同一个权值可能同时构成两个不同的哈夫曼树
typedef struct TreeNode *HuffmanTree;
struct TreeNode {
	int Weight;
	HuffmanTree Left, Right;
};

MaxHeap CreateEmpryHeap(int Maxsize);
bool IsFull(MaxHeap MH);
void visitMaxHeap(MaxHeap H);
MaxHeap CreateMaxHeap();
bool IsEmpty(MaxHeap H);
ElementType DeleteMax(MaxHeap H);
MinHeap CreateMinHeap();
MinHeap CreateEmptyMinHeap(int Maxsize);
void visitMinHeap(MaxHeap H);

int main()
{
	MinHeap H= CreateMinHeap();
	visitMinHeap(H);
	system("pause");
    return 0;
}
MaxHeap CreateEmpryHeap(int Maxsize)
{
	MaxHeap H = (MaxHeap)malloc(sizeof(HeapStruct));
	H->Elements = (ElementType*)malloc((Maxsize) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = Maxsize;

	H->Elements[0] = 10000;/*定义哨兵,为大于堆中所有可能的元素值,便于以后的快速操作*/
	return H;
}
//T(N)=O(logN)
void Insert(MaxHeap H, ElementType item)
{
	int i;
	if (IsFull(H)) {
		printf("最大堆已满");
		return;
	}
	i = ++H->Size;
	//用完全二叉树的i/2为双亲节点
	for (; H->Elements[i/2] < item; i/=2)
	{
		H->Elements[i] = H->Elements[i / 2];/*向上过滤节点*/
	}
	H->Elements[i] = item;/*将item插入*/
}
bool IsFull(MaxHeap MH)
{
	if (MH->Capacity == MH->Size)return true;
	else return false;
}
//
ElementType DeleteMax(MaxHeap H)
{
	int Parent, Child;//parent为当前插入位置;
	ElementType MaxItem, temp;
	if (IsEmpty(H)) {
		printf("最大堆以空");
		return NULL;
	}
	MaxItem = H->Elements[1];
	temp = H->Elements[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
	{
		Child = Parent * 2;
		//给temp找一个位置
		if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))
		{
			Child++;//将Child的变量指向较大的儿子
		}
		//如果大,则位置为Parent.否则,将打的位置前移,向后找小的
		if (temp >= H->Elements[Child])break;
		else H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MaxItem;
}
bool IsEmpty(MaxHeap H)
{
	if (H->Size == 0)return true;
	else return false;
}

MaxHeap CreateMaxHeap()
{
	int N,i,r, Child,Parent,temptr;
	MaxHeap H;
	ElementType temp;
	printf("请输入堆的Size");
	scanf_s("%d", &N);
	H = CreateEmpryHeap(N);
	printf("请输入元素数据");
	for (i = 0; i < N; i++)
	{
		scanf_s("%d", &r);
		H->Elements[++H->Size] = r;
	}
	if (IsEmpty(H))
	{
		printf("最大堆以空");
		return NULL;
	}
	Parent = H->Size / 2;//倒数第一个有儿子的节点
	temp = H->Elements[Parent];
	while (Parent)
	{
		temptr = Parent;
		temp = H->Elements[Parent];

		for (; Parent * 2 <= H->Size; Parent = Child)
		{
			Child = Parent * 2;
			if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))
			{
				Child++;//将Child的变量指向较大的儿子
			}
			//如果是最大的位置,不变,否则交换位置;
			if (temp >= H->Elements[Child])break;
			else H->Elements[Parent] = H->Elements[Child];
		}
		H->Elements[Parent] = temp;
		Parent = temptr - 1;
	}
	return H;
}
void visitMaxHeap(MaxHeap H)
{
	for (int i = 0; i < H->Size; i++)
	{
		printf("***%d***\n", H->Elements[i + 1]);
	}
}
MinHeap CreateMinHeap()
{
	int N, i, r, Child, Parent, temptr;
	MinHeap H;
	ElementType temp;
	printf("请输入堆的Size");
	scanf_s("%d", &N);
	H = CreateEmptyMinHeap(N);
	
	printf("请输入元素数据");
	for (i = 0; i < N; i++)
	{
		scanf_s("%d", &r);
		H->Elements[++H->Size] = r;
	}
	Parent = H->Size / 2;//倒数第一个有儿子的节点
	temp = H->Elements[Parent];
	while (Parent)
	{
		temptr = Parent;
		temp = H->Elements[Parent];

		for (; Parent * 2 <= H->Size; Parent = Child)
		{
			Child = Parent * 2;
			if ((Child != H->Size) && (H->Elements[Child] > H->Elements[Child + 1]))
			{
				Child++;//将Child的变量指向较小的儿子
			}
			//如果是最小的位置,不变,否则交换位置;
			if (temp <= H->Elements[Child])break;
			else H->Elements[Parent] = H->Elements[Child];
		}
		H->Elements[Parent] = temp;
		Parent = temptr - 1;
	}
	return H;
}
MinHeap CreateEmptyMinHeap(int Maxsize)
{
	MinHeap H = (MinHeap)malloc(sizeof(HeapStruct));
	H->Elements = (ElementType*)malloc((Maxsize) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = Maxsize;

	H->Elements[0] = 0;/*定义哨兵,为小于堆中所有可能的元素值,便于以后的快速操作*/
	return H;
}
void visitMinHeap(MaxHeap H)
{
	for (int i = 0; i < H->Size; i++)
	{
		printf("***%d***\n", H->Elements[i + 1]);
	}
}