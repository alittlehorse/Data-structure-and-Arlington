// DS.LinkedList.cpp: 定义控制台应用程序的入口点。
//顺序表大功告成
//链表的基本知识在7/10 2：24完成，嘿嘿

#include "stdafx.h"
#include<stdlib.h>
#define LISTSIZE 100
#define LISTINCREMENT 10
#define MAXSIZE 10
typedef struct
{
	char* elem;
	int length;
	int listsize;
}SqList;//顺序表
typedef struct LNode
{
	char data;
	struct LNode* next;
}LNode,*LinkList;//单链表

typedef struct
{
	char data;
	int cur;
}component, SLinkList[MAXSIZE];//静态链表

//双向链表
typedef struct DuLNode
{
	char data;
	DuLNode *prior;
	DuLNode *next;
}DuLNode, *DuLinkList;
 


bool InitList(SqList &L);
int LocateElem(SqList L, char x);
bool ListInsert_Sq(SqList &L, int i, char e);
bool ListDelete_Sq(SqList &L, int i, char &e);
bool GetElem(SqList L, int i, char &e);
void DestroyList(SqList &L);
bool ListEmpty(SqList L);
bool PriorElem(SqList L,char cur_e, char &pre_e);
bool NextElem(SqList L, char cur_e, char &pre_e);
bool List_Insert1(SqList &L, int i, char e);


//单链表
void CreateList_L1(LinkList &L, int n);//头插法，逆序构造
void CreateList_L2(LinkList &L, int n);//尾插法，顺序构造
//int LocateElem_L(LinkList L, char x);
bool ListInsert_L(LinkList &L, int i, char e);
bool ListDelete_L(LinkList &L, int i, char &e);
bool GetElem_L(LinkList L, int i, char &e);
//void DestroyList_L(LinkList &L);
//bool ListEmpty_L(LinkList L);
//bool NextNode(LinkList L, char cur_e, char &pre_e);
//循环链表

//双向链表

//静态链表,(1)所有的数据元素都存储在一个相邻的空间段,
//但相连的两个元素不一定处在一个相邻的空间里
//(2)修改指针域,就可以完成插入和删除的操作,不需要移动数据元素,
//但是也不能随机访问静态链表中的元素
//(3)一次性份分配所有的储存空间,限制了最大表长


//顺序表
int main()
{
	LinkList L;
	CreateList_L2(L, 3);
	char e1, e2, e3;
	GetElem_L(L, 1, e1);
	GetElem_L(L, 2, e2);
	GetElem_L(L, 3, e3);
	printf("%c\n", e1);
	printf("%x\n", e1);
	printf("%c\n", e2);
	printf("%c\n", e3);
	system("pause");
    return 0;
}
//对表本身操作
bool InitList(SqList &L)
{
	L.elem = (char*)malloc(LISTSIZE * sizeof(char));
	if (!L.elem)exit(EOVERFLOW);
	L.length = 0;
	L.listsize = LISTSIZE;
	return true;
}
//O(n)
int LocateElem(SqList L, char x)
{
	int i = 0;
	while (i <= L.length - 1 && L.elem[i] != x)
		i++;
	if (i > L.length - 1)return -1;
	else return i+1;
}

bool ListInsert_Sq(SqList &L, int i, char e)
{
	char* q = &L.elem[i - 1];
	for (char * p = &L.elem[L.length - 1]; p >= q; --p)
	{
		*(p + 1) = *p;
	}
	*q = e;
	++L.length;
	return true;
}
bool ListDelete_Sq(SqList &L,int i,char &e)
{
	if ((i < 1) || (i > L.length))return false;
	char* p = &(L.elem[i - 1]);//p为被删除的元素的位置
	e = *p;
	char* q = L.elem + L.length - 1;//表位位置
	for (++p; p <= q; ++p)*(p - 1) = *p;
	--L.length;
	return true;
}
bool GetElem(SqList L, int i,char &e)
{
	if (i > L.length)return false
		;
	e = L.elem[i - 1];
	return true;
}
void DestroyList(SqList &L)
{

}
bool ListEmpty(SqList L)
{
	if (L.length == 0)
	{
		return true;
	}
	else return false;
}
bool PriorElem(SqList L, char cur_e, char &pre_e)
{
	int i = LocateElem(L, cur_e);
	if (i > 1 && i < L.length+1)
	{
		pre_e = L.elem[i - 2];
		return true;
	}
	else return false;
}
bool NextElem(SqList L, char cur_e, char &pre_e)
{
	int i = LocateElem(L, cur_e);
	if (i > 0 && i < L.length)
	{
		pre_e = L.elem[i];
		return true;
	}
	else return false;
}
//嘿嘿，这是我自己写的，美滋滋
bool List_Insert1(SqList &L, int i,char e)
{
	if (i<1 || i>L.length + 1) { return false; }
	if (L.length >= L.listsize)
	{
		char* newbase = (char*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(char*));
		if (!newbase)return false
			;
		else L.elem = newbase;
		L.length += LISTINCREMENT;
	}
	char* p = &L.elem[i - 1];
	while (i <= L.length) { L.elem[i] = L.elem[i - 1]; i++; }
	*p = e;
	++L.length;
	return true;
}



bool GetElem_L(LinkList L, int i, char &e)
{
	LinkList p = L->next;//找到第一个节点
	int j = 1;
	while (p&&j < i)
	{
		p = p->next; ++j;
	}
	if (!p||j >i)return false;
	e = p->data;
	return true;
}
bool ListInsert_L(LinkList &L, int i, char e)
{
	LinkList p = L; int j = 0;
	while (p&&j < i - 1) { p=p->next; ++j; }//找到前置节点
	if (!p || j > i - 1) { return false; }//i小于1，或者大于表长加1，就是前置节点为null；
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e; s->next = p->next;
	p->next = s;
}
bool ListDelete_L(LinkList &L, int i, char &e)
{
	LinkList p = L; int j = 0;
	while (p&&j < i - i) { p = p->next; ++j; }
	if (!p || j > i - 1) return false
		;
	LinkList q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return true;
}
void CreateList_L1(LinkList &L, int n)//头插法
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = n; i >0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		printf_s("请输入第%d个字符\n", i);
		
		scanf_s("%c",&p->data);
		getchar();
		p->next = L->next; L->next = p;
	}
}
void CreateList_L2(LinkList &L,int n)
{
	L = (LinkList)malloc(sizeof(LNode));//头节点
	L->next = NULL;
	LinkList p, r = L;//p为接受节点，r为尾节点
	for (int i = 0; i < n; i++)
	{		
		p = (LinkList)malloc(sizeof(LNode));
		printf_s("请输入第%d个字符\n", i+1);
		scanf_s("%c", &p->data);
		getchar();
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

//静态单链表,还没有完成!!!

void InitSpace_SL(SLinkList &space)
{
	
	for (int i = 0; i < MAXSIZE - 1; i++)space[i].cur = i + 1;
	space[MAXSIZE - 1].cur = 0;
}
int Malloc_SL(SLinkList &space)
{
	int i = space[0].cur;
	//若备用链表非空,则返回分配的节点下标,否者返回0;
	if (space[0].cur)space[0].cur = space[i].cur;//头结点指向下一个节点
	return i;
}
void Free_SL(SLinkList &space, int k)
{
	space[k].cur = space[0].cur; space[0].cur = k;
}
void difference(SLinkList &space, int &S)
{
	InitSpace_SL(space);//初始化备用空间
	int S = Malloc_SL(space);
	int r = S;
	int m, n;
	scanf("%d,%d", m, n);
	for (int j = 1; j <= m; ++j)
	{
	}
}

//双向链表
bool GetPriorElem_DuL(DuLinkList L, int i,DuLinkList &O)
{
	DuLinkList p = L->next;
	if (i < 1)return false;
	for (int j = 1; j < i - 1; j++)//找到前置节点
	{
		if (!p||j>i)return false;
		p = p->next;
	}
	O = p;
	return true;
}
bool GetElem_DuL(DuLinkList L, int i, DuLinkList &O)
{
	DuLinkList h = L->next;
	if (i < 1)return false;
	for (int j = 1; j < i ; j++)
	{
		if (h== NULL||j>i)return false;
		h = h->next;
	}
	O = h;
	return true;
}
bool ListInsert_DuL(DuLinkList &L, int i, char e)
{
	DuLinkList p = (DuLinkList)malloc(sizeof(DuLNode));
	DuLinkList h ;//头结点
	if (!GetPriorElem_DuL(L, i, h))return false;
	p->data = e;
	p->next = h->next;
	h->next = p;
	p->next->prior = p;
	p->prior = h;
	//原则,在任意时刻,必须通过已知的两个节点可以找到另外一个节点
	return true;
}
bool ListDelete_DuL(DuLinkList &L, int i, char &e)
{
	DuLinkList p;
	if (!GetElem_DuL(L, i, p))return false;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p); return true;
}

LinkList Reverse(LinkList head,int K)
{
	int count;
	LinkList my_new = head->next;//第一个节点
	LinkList old = my_new->next;
	while (count <K)
	{
		LinkList temp = old->next;
		old->next = my_new;
		my_new = old;
		old = temp; 
		count++;
	}
	head->next->next = old;
	head->next = my_new;
	return  head;
}




