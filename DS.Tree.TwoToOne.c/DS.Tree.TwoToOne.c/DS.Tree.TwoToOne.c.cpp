// DS.Tree.TwoToOne.c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define MaxSize 10
//应用题6,有两种遍历需确定二叉树,必须有中序遍历才行
//**********************************************************
//*******************前序遍历和中序遍历决定后序遍历*****************
//**********************************************************
int pre[MaxSize]= { 0 };
int post[MaxSize] = { 0 };
int in[MaxSize] = { 0 };
int main()
{
    return 0;
}


void solve(int preL, int inL, int postL, int n)
{
	int root, L, R,i;
	if (n == 0)return;
	if (n == 1) { post[postL] = pre[preL]; return; } 
	root = pre[preL];
	post[postL + n - 1] = root;
	for (i = 0; i < n; i++)
	{
		if (in[inL + i] == root) break;
	}
	L = i; R = n - L - 1;
	solve(preL+1,inL,postL,L);
	solve(preL + L + 1, inL + L + 1, postL + L, R);
}