// DS.AVLTree.c.cpp: 定义控制台应用程序的入口点。

//*****************************************************************************
//*                                                                           *
//*                             二叉平衡树                                    *
//*                                                                           *
//*****************************************************************************
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
typedef char ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode {
	ElementType Data; /* 结点数据 */
	AVLTree Left;     /* 指向左子树 */
	AVLTree Right;    /* 指向右子树 */
	int Height;       /* 树高 */
};
typedef struct TreeNode *Tree;

struct TreeNode
{
	int v;
	Tree Left, Right;
	int flag;
};
Tree MakeTree(int N);
Tree Insert(char X, Tree BST);
bool Judge(Tree T, int N);
bool Search(Tree T, int s);
void ResetT(Tree &T);
void FreeTree(Tree &T);
int main()
{
	//TODO:读入N和L;
	//根据第一行序列见树
	//根据树T分别判别后面的L个序列是否能与T形成统一搜索树病输出结果
	int N, L, i;

	scanf_s("%d", &N);
	while (N)
	{
		scanf_s("%d", &L);
		Tree T = MakeTree(N);
		for (i = 0; i < L; i++)
		{
			if (Judge(T, N))printf("Yes\n");
			else printf("No\n");
			ResetT(T);//清除T中的标记flag
		}
		FreeTree(T);
		scanf_s("%d", &N);
	}
	return 0;
}
int Max(int a, int b)
{
	return a > b ? a : b;
}
int GetHeight(AVLTree A)
{
	return (A->Height);
}
AVLTree SingleLeftRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;

	return B;
}
AVLTree SingleRightRotation(AVLTree A)
{
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B; 
}
AVLTree DoubleLeftRightRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

  /* 将B与C做右单旋，C被返回 */
	A->Left = SingleRightRotation(A->Left);
	/* 将A与C做左单旋，C被返回 */
	return SingleLeftRotation(A);
}
AVLTree DoubleRightLeftRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

  /* 将B与C做右单旋，C被返回 */
	A->Right = SingleLeftRotation(A->Right);
	/* 将A与C做左单旋，C被返回 */
	return SingleRightRotation(A);
}



AVLTree Insert(AVLTree T, ElementType X)
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
	if (!T) { /* 若插入空树，则新建包含一个结点的树 */
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} /* if (插入空树) 结束 */

	else if (X < T->Data) {
		/* 插入T的左子树 */
		T->Left = Insert(T->Left, X);
		/* 如果需要左旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);      /* 左单旋 */
			else
				T = DoubleLeftRightRotation(T); /* 左-右双旋 */
	} /* else if (插入左子树) 结束 */

	else if (X > T->Data) {
		/* 插入T的右子树 */
		T->Right = Insert(T->Right, X);
		/* 如果需要右旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
			if (X > T->Right->Data)
				T = SingleRightRotation(T);     /* 右单旋 */
			else
				T = DoubleRightLeftRotation(T); /* 右-左双旋 */
	} /* else if (插入右子树) 结束 */

	  /* else X == T->Data，无须插入 */

	  /* 别忘了更新树高 */
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

	return T;
}

Tree MakeTree(int N)
{
	int i,r;
	Tree T, temp;
	if (!N)return NULL;
	scanf_s("%d", &r);
	T = (Tree)malloc(sizeof(TreeNode));
	T->flag = 0;
	T->v = r;
	T->Left = T->Right = NULL;
	for (i = 1; i < N; i++)
	{
		scanf_s("%d", &r);
		Insert(r, T);
	}
	return T;
}
Tree Insert(char X, Tree BST)
{
	if (!BST)
	{
		BST = (Tree)malloc(sizeof(TreeNode));
		BST->v = X;
		BST->Left = BST->Right = NULL;
	}
	else
	{
		if (X > BST->v) BST->Right = Insert(X, BST->Right);
		else if (X <= BST->v)BST->Left = Insert(X, BST->Left);
	}
	return BST;
}
bool Judge(Tree T, int N)
{
	int s,i;
	scanf_s("%d", &s);
	if (s == T->v)T->flag = 1;//第一个元素
	for (i = 1; i < N; i++)
	{
		scanf_s("%d", &s);
		if (!Search(T, s)) return false;
	}
	return true;
}
bool Search(Tree T, int s)
{
	if (s == T->v) { T->flag = 1; return true; }
	if (T->flag == 0&&s!= T->v)
	{
		return false;
	}
	else
	{
		if (s > T->v) return Search(T->Right, s);
		else return Search(T->Left, s);
	}
}
void ResetT(Tree &T)
{
	if (T)
	{
		T->flag = 0;
		ResetT(T->Left);
		ResetT(T->Right);
	}
}
void FreeTree(Tree &T)
{
	if (T==NULL) return;
	FreeTree(T->Left);
	FreeTree(T->Right);
	free(T);
}