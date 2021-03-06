// DS.Sort.c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#define Cutoff 1000
typedef int ElementType;

typedef struct HeapStruct *MaxHeap, *MinHeap;
//有序性:根的位置为最大值;
struct HeapStruct {
	ElementType *Elements;/*储存堆元素的数组*/
	int Size;/*对的当前元素个数*/
	int Capacity;/*堆的最大容量*/
};

void Bubble_Sort(ElementType A[], int N);
void SWAP(ElementType &A, ElementType &B);
void printList(ElementType A[], int N);
void Insertion_Sort(ElementType A[], int N);
MinHeap CreateMinHeap(void);
MinHeap CreateEmptyMinHeap(int Maxsize);
void visitMinHeap(MinHeap H);
void Heap_Sort_Prioty(ElementType A[], int N);
MinHeap CreateMinHeapByList(ElementType A[], int N);
void PercDown(ElementType A[], int p, int N);
ElementType Median3(ElementType A[], int Left, int Right);
void Quicksort(ElementType A[], int Left, int Right);
void Quick_Sort(ElementType A[], int N);

int main()
{
	//printf("please input a randomal list");
	//scanf_s();
	int A[5] = { 15,4,3,2,1 };
	Heap_Sort_Prioty(A, 5);
	printList(A,5);
	system("pause");
    return 0;
}

//####################################################
//##############################最小堆的操作###############
//####################################################

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

	H->Elements[0] = 0;/*定义哨兵,为大于堆中所有可能的元素值,便于以后的快速操作*/
	return H;
}
void visitMinHeap(MinHeap H)
{
	for (int i = 0; i < H->Size; i++)
	{
		printf("***%d***\n", H->Elements[i + 1]);
	}
}
ElementType DeleteMin(MinHeap H)
{
	ElementType MinItem, temp;
	int Parent, Child;
	MinItem = H->Elements[1];
	temp = H->Elements[H->Size--];
	//给temp找一个位置parent;
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
	{
		Child = Parent * 2;
		//Child指向做有子节点最小的点;
		if ((Child != H->Size) && (H->Elements[Child] > H->Elements[Child] + 1))
		{
			Child++;
		}
		if (temp <= H->Elements[Child])break;
		else H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MinItem;
}
MinHeap CreateMinHeapByList(ElementType A[],int N)
{
	int  i, r, Child, Parent, temptr;
	MinHeap H;
	ElementType temp;
	H = CreateEmptyMinHeap(N);
	for (i = 0; i < N; i++)
	{		
		H->Elements[++H->Size] = A[i];
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
//############################################################
//#########################排序操作###########################
//############################################################

//############################################################
//####################逆序对##################################
//############################################################
//交换两个相邻的元素正好消去1个逆序对
//插入排序:T(N+I)=T(N+I);:I为逆序对数
//任意N个不同元素组成的序列平均具有N(N-1)/4个逆序对
//仅以交换相邻两元素来排序的算法,其平均时间复杂度为N^2


//冒泡排序,稳定
void Bubble_Sort(ElementType A[], int N)
{
	int P, i,flag;
	for (P = N - 1; P >= 0; P--)
	{
		flag = 0;
		for (i = 0; i < P; i++)
		{
			if (A[i] > A[i + 1]);
			{
				SWAP(A[i], A[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0)break;
	}
}

void SWAP(ElementType &A, ElementType &B)
{
	ElementType C;
	C = A;
	A = B;
	B = C;
}
void printList(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n",A[i]);
	}
}
void Insertion_Sort(ElementType A[], int N)
{
	int p,i;
	ElementType Tmp;
	for (p = 1; p < N; p++)
	{
		Tmp = A[p];
		for (i = p; i > 0 && A[i - 1] > Tmp; i--)
		{
			A[i] = A[i - 1];
		}
		A[i] = Tmp;
	}
}



//#####################希尔排序####################

void Shell_Sort(ElementType A[], int N)
{
	int D, P, i;
	ElementType Tmp;
	for (D = N / 2; D > 0; D /= 2)//确定间隔
	{
		for (P = D; P < N; P++)//插入排序
		{
			Tmp = A[P];
			for (i = P; i >= D && A[i - D] > Tmp; i -= D)
			{
				A[i] = A[i - D];
			}
		}
	}
}
//#############################堆排序#######################
void Heap_Sort(ElementType A[], int N)
{
	int i;
	MinHeap MH;
	MH = CreateMinHeapByList(A, N);
	ElementType *TmpA = new ElementType[N];
	for (i = 0; i < N; i++)
	{
		TmpA[i] = DeleteMin(MH);
	}
	for (i = 0; i < N; i++)
	{
		A[i] = TmpA[i];
	}
}
void Heap_Sort_Prioty(ElementType A[], int N)
{
	//TODO::(1)BuildHeap(2)DeleteMax(3)
	int i;
	for (i = N / 2-1; i > 0; i--)
	{
		PercDown(A, i, N);//建立最大堆;
	}
	for (i = N - 1; i > 0; i--)
	{
		SWAP(A[0], A[i]);
		PercDown(A, 0, i);
	}
}
//将N个元素以A[p]为根的子堆调整为最大堆
void PercDown(ElementType A[], int p, int N)
{
	int Parent, Child;
	ElementType X;
	X = A[p];
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
	{
		Child = Parent * 2+1;
		if ((Child != N - 1) && A[Child] < A[Child + 1])
		{
			Child++;
		}
		if (X >= A[Child])break;
		else {
			A[Parent] = A[Child];
		}
	}
	A[Parent] = X;
 }
//##################################################
//######################归并排序####################
//##################################################
void Merge(ElementType A[], ElementType TmpA[],int L,int R,int RightEnd)
{
	int LeftEnd, Tmp,NumElement,i;
	LeftEnd= R - 1;//左边终点位置,假设两列挨着
	Tmp = L;//存放结果数组的初始位置
	NumElement = RightEnd - L + 1;
	while (L <= LeftEnd && R <= RightEnd)
	{
		if (A[L] <= A[R])TmpA[Tmp++] = A[L++];
		else TmpA[Tmp++] = A[R++];
	}
	while (L <= LeftEnd)TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)TmpA[Tmp++] = A[R++];
	for (i = 0; i < NumElement; i++, RightEnd--)
	{
		A[RightEnd] = TmpA[RightEnd];
	}
}
void Merge1(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
	int LeftEnd, Tmp, NumElement, i;
	LeftEnd = R - 1;//左边终点位置,假设两列挨着
	Tmp = L;//存放结果数组的初始位置
	while (L <= LeftEnd && R <= RightEnd)
	{
		if (A[L] <= A[R])TmpA[Tmp++] = A[L++];
		else TmpA[Tmp++] = A[R++];
	}
	while (L <= LeftEnd)TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)TmpA[Tmp++] = A[R++];
}
//递归算法
void MSort(ElementType A[], ElementType TmpA[],int L,int RightEnd)
{
	int Center; 
	if (L<RightEnd)
	{
		Center = (L + RightEnd) / 2;
		MSort(A, TmpA, L, Center);
		MSort(A, TmpA, Center + 1, RightEnd);
		Merge(A, TmpA, L, Center + 1, RightEnd);
	}
}
//###################################################
//##################同一接口#########################
//###################################################
void Merge_sort(ElementType A[], int N)
{
	ElementType *TmpA;//
	TmpA =(ElementType*) malloc(N * sizeof(ElementType));
	if (TmpA != NULL)
	{
		MSort(A,TmpA,0,N-1);
		free(TmpA);
	}
	else printf("空间不足");
}
//非递归算法
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{
	//length为当前有序子列的长度
	int i,j;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
	{
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);
	}
	if (i + length < N)//归并最后两个子列
		Merge1(A, TmpA, i, i + length, N - 1);
	else
		for (j = i; j < N; j++)TmpA[j] = A[j];
}
void Merge1_Sort(ElementType A[], int N)
{
	int length = 1;
	ElementType *TmpA;
	TmpA = (ElementType*)malloc(N * sizeof(ElementType));
	if (TmpA != NULL)
	{
		while (length<N)
		{
			Merge_pass(A, TmpA, N, length);
			length *= 2;
			Merge_pass(TmpA, A, N, length);
			length *= 2;
		}
		free(TmpA);
	}
	else printf("空间不足");
}

//###################################################
//####################快速排序#######################
//####################################################

//三位选随机数
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])SWAP(A[Left],A[Right]);
	if (A[Left] > A[Right])SWAP(A[Left], A[Right]);
	if (A[Center] > A[Right])SWAP(A[Center], A[Right]);
	SWAP(A[Center], A[Right - 1]);//将pivot藏在右边
	//只需要考虑A[Left+1]到A[Right-2]的范围
	return A[Right - 1];
}

//子集划分
//对于小规模的数据,还不如插入排序快
//当递归的规模充分小时,停止递归,直接调用简单排序
//void QuickSort(ElementType A[],int N)
//{
//	pivot = 从A中选取一个主元;
//	将S= {A[]\pivot}分成两个独立子集
//	A=QuickSort(A1,N1)+pivot+QuickSort(A2,N2);
//}
void Quicksort(ElementType A[], int Left, int Right)
{
	ElementType Pivot;
	int i, j;
	if (Cutoff <= Right - Left) {
		Pivot = Median3(A, Left, Right);
		//因为上边将左右已经排好;只用取从Left+1到Right-2的部分
		//i = Left+1; j = Right - 2;
		
		//因为下面的循环时++i和--j,所以:
		i = Left; j = Right - 1;
		for (;;)
		{
			//当主元和某一个数据相等时,停下来交换
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)SWAP(A[i], A[j]);
			else break;
		}
		SWAP(A[i], A[Right - 1]);
		Quicksort(A, Left, i - 1);
		Quicksort(A, i + 1, Right);
	}
	else
		Insertion_Sort(A + Left, Right - Left + 1);
}
void Quick_Sort(ElementType A[], int N)
{
	Quicksort(A, 0, N - 1);
}

//###################################################
//###################表排序##########################
//###################################################



//基数排序
//次位优先排序
