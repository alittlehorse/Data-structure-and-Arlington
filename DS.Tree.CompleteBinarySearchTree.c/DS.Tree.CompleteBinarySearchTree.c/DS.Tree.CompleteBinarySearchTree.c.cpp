// DS.Tree.CompleteBinarySearchTree.c.cpp: 定义控制台应用程序的入口点。
//

#include<stdlib.h>
#include<math.h>
#include "stdafx.h"
#define MaxSize 20
//***************************************************
//*                完全搜索二叉树                   *
//***************************************************
//完全二叉树的数组存储性质非常完美;
//TODO:排序,根据完全二叉树个特性,找出根节点
int T[MaxSize] = { -1 };
int A[MaxSize] = { -1 };
void solve(int ALeft, int Aright, int TRoot);
int GetLeftLength(int n);
int main()
{
	int N;
	qsort(A,N,sizeof(int),compare);
	solve(0,N-1,0);

    return 0;
}
//输入序列为A,结果树是T
void solve(int ALeft, int Aright, int TRoot)
{
	int n, L, LeftTRoot, RightTRoot;
	n = Aright - ALeft + 1;//传入个数
	if (n == 0)return;
	L = GetLeftLength(n);
	T[TRoot] = A[ALeft + L];
	LeftTRoot = TRoot * 2 + 1;
	RightTRoot = LeftTRoot + 1;
	solve(ALeft, ALeft+L -1, LeftTRoot);
	solve(ALeft+L+1 , Aright, RightTRoot);

}
int compare(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
} 
int GetLeftLength(int n)
{
	int H, L, X;
	H = (int)log2(n+1);
	X = n + 1 - pow(2, H);
	if (X > pow(2, H - 1))X = pow(2, H - 1);
	L = pow(2, H - 1) - 1 + X;
	return L;
}