// DS.Tree.c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
//Degree:节点的子树的个数
//树的度:树所有节点中最大的度数
//Leaf:度为0的节点
//Parent,Child,Sibling
//路径与路径长度
//Ancestor,Descendant
//Level,Depth

//儿子-兄弟表示法,二叉树
//深度为k的二叉树,最大的节点数为2^k-1
//n0 = n2+1;
//总节点数n0+ni+n2
//n0+n1+n2-1边数=0*n0+1*n1+2*n2
//所以n = n2+1

//完全二叉树可以用数组实现
//非根节点i的父节点在i/2
//i左儿子在2i,右儿子在2i+1
//成功了.用队列实现成功了!

#define MaxTree 10
#define ElementType int 
#define Tree int
#define NoInfo 0 
//***********************树的链表储存********************
typedef struct TreeNode
{
	ElementType Data;
	TreeNode* Left;
	TreeNode * Right;
}TreeNode,*BinTree;
typedef TreeNode Position;


//*********************堆栈********************
typedef struct Node
{
	BinTree Data;
	Node* Next;
}Node,*Stack;


//**********************队列*************************
typedef struct QNode
{
	Node *rear;
	Node *front;
}QNode, *Queue;

//**********************数组表示,静态链表***************
typedef struct TreeNode_S
{
	ElementType Element;
	Tree Left;
	Tree Right;	
}T1[MaxTree],T2[MaxTree];

//********************************函数原型************************

Stack CreatStack();
bool isEmpty(Stack S);
void Push(Stack &S, BinTree TN);
BinTree Pop(Stack &S);
void CreatQueue(Queue &PtrQ);
void Add(Queue &PtrQ, BinTree item);
BinTree Delete(Queue &PtrQ);
bool IsEmptyQ(Queue PtrQ);
void LevelOrderTraversal(BinTree BT);
void PreOrderTraversal(BinTree BT);
void InOrderTraversal(BinTree BT);
void PostOrderTraversal(BinTree BT);
void PreOrderTraversal_S(BinTree BT);
void InOrderTraversal_S(BinTree BT);
void PostOrderTraversal_S(BinTree BT);
void AddTreeNode_R(BinTree &BT, int data);
void AddTreeNode_L(BinTree &BT, int data);
int PostOrderGetHeight(BinTree BT);
bool CreateBiTree(BinTree &T);
bool ProOrderJude(BinTree BT);

Position Find(ElementType X, BinTree BST);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);
BinTree Insert(ElementType X, BinTree &BST);
BinTree Delete(ElementType X, BinTree &BST);
//----------------------******************main***************---------------------
int main()
{
	BinTree BT;
	CreateBiTree(BT);
	BinTree temp = BT;
	//for (int i = 0; i < 50; i+=2)
	//{

	//	AddTreeNode_L(temp, i);
	//	AddTreeNode_R(temp, i+1);
	//	temp = temp->Left;
	//}
	//printf("%d\t%d\t%d", BT->Data,BT->Left->Left->Left->Data,BT->Left->Right->Data);
	LevelOrderTraversal(BT);
	system("pause");
    return 0;
}

//------------------********************堆栈实现******************---------------------
Stack CreatStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(Node));
	S->Next = NULL;
	return S;
}
bool isEmpty(Stack S)
{
	return(S->Next == NULL);
}
//选择头插法进行Push,头结点是Top;
void Push(Stack &S, BinTree TN)
{
	Stack p = (Stack)malloc(sizeof(Node));
	p->Data = TN;
	p->Next = S->Next;
	S->Next = p;
}

BinTree Pop(Stack &S)
{
	Stack p;
	if (isEmpty(S)) { printf("栈为空"); return NULL; }
	else
	{
		p = S->Next;
		S->Next = p->Next;
		BinTree resualt = p->Data;
		free(p);
		return resualt;
	}
}

//*************************************队列实现************************************
bool IsEmptyQ(Queue PtrQ)
{
	if (PtrQ->front->Next == NULL)return true;
	else return false;
}
void Add(Queue &PtrQ, BinTree item)
{
	Node* q = (Node*)malloc(sizeof(Node));
	q->Data = item;
	q->Next = NULL;
	PtrQ->rear->Next = q;
	PtrQ->rear = q;
	
}
//带头结点的删除
BinTree Delete(Queue &PtrQ)
{
	Node* FrontCell;
	BinTree FrontElem;
	if (PtrQ->front->Next == NULL)
	{
		printf("队列空"); return NULL;
	}
	FrontCell = PtrQ->front->Next;//第一个节点
	PtrQ->front->Next = PtrQ->front->Next->Next;
	if (IsEmptyQ(PtrQ)) PtrQ->rear = PtrQ->front;
	FrontElem = FrontCell->Data; 
	free(FrontCell);
	return FrontElem;
}
void CreatQueue(Queue &PtrQ)
{
	Node* q = (Node*)malloc(sizeof(Node));
	q->Next = NULL;
	PtrQ->front = q;
	PtrQ->rear = q;
}

//二叉树遍历的核心问题,二维结构的线性化
//(1)从节点访问左右两个儿子的节点
//(2)在访问左儿子后,右儿子怎么办
//***************************************************************************
//***********************************递归遍历*****************************************
//**********************************************************************************

void PreOrderTraversal(BinTree BT)
{
	if (BT)
	{
		printf("%d\n", BT->Data);
		PreOrderTraversal(BT->Left);
		PreOrderTraversal(BT->Right);
	}
}

void InOrderTraversal(BinTree BT)
{
	if (BT)
	{
		InOrderTraversal(BT->Left);
		printf("%d\n",BT->Data);
		InOrderTraversal(BT->Right);
	}
}

void PostOrderTraversal(BinTree BT)
{
	if (BT)
	{
		PostOrderTraversal(BT->Left);		
		PostOrderTraversal(BT->Right);
		printf("%d\n", BT->Data);
	}
}
//***********************************************************************************
//*********************************非递归遍历,使用堆栈*******************************
//***********************************************************************************
//中序,遇到一个节点,就把他压栈,并遍历它的左子树
//当左子树遍历结束后,荣栈顶弹出这个结果并访问他
//然后按其右指针再去中序遍历该节点的有子树
void InOrderTraversal_S(BinTree BT)
{
	BinTree T = BT;
	Stack S = CreatStack();
	while (T || isEmpty(S))
	{
		while (T)//一直向左并将沿途的节点压入堆栈
		{
			Push(S, T);
			T = T->Left;
		}
		if (!isEmpty(S))
		{
			T = Pop(S);
			printf("%5d", T->Data);
			T=T->Right;//转向右子树
		}
	}
}
void PreOrderTraversal_S(BinTree BT)
{
	BinTree T = BT;
	Stack S = CreatStack();
	
	while (T || isEmpty(S))
	{
		while (T)
		{
			printf("%5d", T->Data);
			Push(S, T);
			T = T->Left;
		}
		if (!isEmpty(S))
		{
			T = Pop(S);
			T=T->Right;
		}
	}
}
void PostOrderTraversal_S(BinTree BT)
{
	BinTree T = BT;
	Stack S = CreatStack();
	BinTree Root = BT;
	while (T || isEmpty(S))
	{
		while (T)
		{
			Push(S, T);
			T = T->Left;
		}
		if (!isEmpty(S))
		{
			T = Pop(S);
			if (!T->Left) printf("%d", T->Left->Data);//出栈后回探左边
			BT = BT->Right;
		}
		
	}
	printf("%d", BT->Data);
}
//层序队列的遍历
void LevelOrderTraversal(BinTree BT)
{
	Queue Q = (Queue)malloc(sizeof(QNode)); 
	BinTree T;
	if (!BT)return;
	CreatQueue(Q);
	Add(Q, BT);
	while (!IsEmptyQ(Q))
	{
		T = Delete(Q);
		printf("%d\n", T->Data);
		if (T->Left)Add(Q, T->Left);
		if (T->Right)Add(Q, T->Right);
	}
}
//**********************************************************************************
//***************************************建立树的操作******************************
//*********************************************************************************
//二叉树的先序创建
bool CreateBiTree(BinTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ')T = NULL;
	else {
		if (!(T = new TreeNode))exit(EOVERFLOW);
		T->Data = ch;
		CreateBiTree(T->Left);
		CreateBiTree(T->Right);
	}
	return true;
}
void AddTreeNode_R(BinTree &BT, int data)
{
	BT->Right = (BinTree)malloc(sizeof(TreeNode));
	BT->Right->Data = data;
	BT->Right->Left = NULL;
	BT->Right->Right = NULL;
}
void AddTreeNode_L(BinTree &BT, int data)
{
	BT->Left = (BinTree)malloc(sizeof(TreeNode));
	BT->Left->Data = data;
	BT->Left->Left = NULL;
	BT->Left->Right = NULL;
}
//层序生成二叉树
BinTree CreateBinTree()
{
	ElementType Data;
	BinTree BT, T;
	Queue Q;
	CreatQueue(Q);
	scanf_s("%d",&Data);
	if (Data != NoInfo)
	{
		BT = (BinTree)malloc(sizeof(TreeNode));
		BT->Data = Data;
		BT->Left = BT->Right = NULL;
		Add(Q, BT);
	}
	else return NULL;
	while (!IsEmptyQ(Q))
	{
		T = Delete(Q);
		//读入左孩子
		scanf_s("%d",&Data);
		if (Data == NoInfo)T->Left = NULL;
		else {
			T->Left = (BinTree)malloc(sizeof(TreeNode));
			T->Left->Data = Data;
			T->Left->Right = T->Left->Right = NULL;
			Add(Q, T->Left);
		}
		//读入右孩子
		scanf_s("%d", &Data);
		if (Data == NoInfo)T->Right = NULL;
		else {
			T->Right = (BinTree)malloc(sizeof(TreeNode));
			T->Right->Data = Data;
			T->Right->Right = T->Left->Right = NULL;
			Add(Q, T->Right);
		}
	}
	return BT;
}
//***********************************************************************************
//**************************************求树的高度**********************************
//**********************************************************************************
//求一个数的高度必须知道左右树的高度,所以说用后序遍历
int PostOrderGetHeight(BinTree BT)
{
	int HL, HR, MaxH;
	if (BT)
	{	
		HL = PostOrderGetHeight(BT->Left);
		HR = PostOrderGetHeight(BT->Right);
		MaxH = (HL > HR) ? HL : HR;
		return (MaxH + 1);
	}
	else return 0;
}

//应用题5,二元运算表达式树遍历
//叶节点为运算数,非叶节点表示运算符
//后序遍历得到后缀表达式


//建立二叉树
//判断二叉树是否同构
//Tree BuildTree(TreeNode_S T[])
//{
//	Tree Root;
//	int N = 0;
//	int i;
//	char cl,cr;
//	scanf("%d\n", &N);
//	int check[N];
//	if (N)
//	{
//		for (i = 0; i < N; i++)check[i] = 0;
//		for (i = 0; i < N; i++)
//		{
//			scanf("%c%c%c\n", &T[i].Element, &cl, &cr);
//			if (cl != '-')
//			{
//				T[i].Left = cl - '0';
//				check[T[i].Left] = 1;
//			}
//			else T[i].Left = Null;
//			if (cr != '-')
//			{
//				T[i].Right = cr - '0';
//				check[T[i].Right] = 1;
//			}
//			else T[i].Right = Null;
//		}
//		for (i = 0; i < N; i++)
//			if (!check[i])break;
//		Root = i;
//	}
//	return i;
//}
//int Isomophic(Tree R1, Tree R2)
//{
//	if ((R1 == Null) && (R2 == Null))
//		return 1;
//	if ((R1 == Null) && (R2 != Null) || (R1 != Null) && (R2 == Null))
//		return 0;
//
//}

//尾递归都可用循环来实现

//***************************************************************************
//********************************二叉搜索树的操作***********************************
//*****************************************************************************
Position Find(ElementType X, BinTree BST)
{
	if (!BST)return ;
	if (X > BST->Data)return Find(X, BST->Right);
	else if (X < BST->Data) return Find(X, BST->Left);
	else return *BST;

}
Position IterFind(ElementType X, BinTree BST)
{
	while (BST)
	{
		if (X == BST->Data)return *BST;
		if (X > BST->Data)BST = BST->Right;
		else BST =  BST->Left;
	}
	return ;
}
Position FindMax(BinTree BST)
{
	if (BST)
		while (BST->Right)BST = BST->Right;
	return * BST;
}
Position FindMin(BinTree BST)
{
	if (BST)
		while (BST->Left)BST = BST->Left;
	return *BST;
}
BinTree Insert(ElementType X, BinTree &BST)
{
	if (!BST)
	{
		BST = (BinTree)malloc(sizeof(TreeNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else
	{
		if (X > BST->Data) BST->Right=Insert(X, BST->Right);
		else if (X < BST->Data)BST->Left=Insert(X, BST->Left);
	}
	return BST;
}
//删除叶节点
//删除只有一个儿子的节点
//删除有两个儿子的节点,用左子树的最大值或右子树的最小值来代替
//左子树的最大值和右子树的最小值一定最多有一个子节点

BinTree Delete(ElementType X, BinTree &BST)
{
	Position Tmp;
	if (!BST) printf("要删除的元素未找到");
	else if (X < BST->Data)BST->Left = Delete(X, BST->Left);
	else if (X > BST->Data)BST->Right = Delete(X, BST->Right);
	else {
		if (BST->Left&&BST->Right)//如果左右儿子节点都存在
		{
			Tmp = FindMin(BST->Right);//找右指数最小值
			BST->Data = Tmp.Data;
			BST->Right = Delete(BST->Data, BST->Right);
		}
		else//只有一个儿子节点存在或者都不存在
		{
			Tmp = *BST;
			if (!BST->Left)BST = BST->Left;
			else if (!BST->Right)BST = BST->Right;
			free(&Tmp);
		}
	}
	return BST;
}

//搜索树右边的节点有大于根节点!!!
//先用递归来实现
//并不是单单的比左右,而是比较子树中的左右,有子树的最小的,左子树中最大的,与他们的子树的根节点作比较;
bool ProOrderJude(BinTree BT)
{
	if (!BT)return true;
	
	int root = BT->Data;
	while (BT)
	{
		Position R = FindMin(BT->Right);
		Position L = FindMax(BT->Left);
		if (root>R.Data|| root>L.Data) return false;
		if (!ProOrderJude(BT->Left))return false;
		if (!ProOrderJude(BT->Right))return false;
	}
	return true;
}
