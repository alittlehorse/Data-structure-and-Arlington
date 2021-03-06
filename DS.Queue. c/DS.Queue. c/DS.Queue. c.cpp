// DS.Queue. c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#define Maxsize 100
//循环队列
//front指向队列第一个的前一个
//rear指向最后一个item
typedef struct QNode {
	char Data[Maxsize];
	int rear;
	int front;
}QNode,*Queue;

//链表实现
typedef struct Node
{
	char data;
	Node* next;
}Node,*QueuePtr; 

//再头删除,在尾插入
typedef struct QLNode
{
	Node *rear;
	Node *front;
}QLNode,*LQueue;

void AddQ(Queue PtrQ, char item);
char DeletQ(Queue PtrQ);
char DeleteQ1(LQueue &PtrQ);
void AddQ1(LQueue &PtrQ, char item);
void visit(LQueue PtrQ);
void CreatQueue(LQueue &PtrQ);
int main()
{
	LQueue Q = (LQueue)malloc(sizeof(QLNode));
	CreatQueue(Q);
	char a, b, c;
	a = 'a';
	b = 'b';
	c = 'c';
	AddQ1(Q,a );
	AddQ1(Q, b);
	AddQ1(Q, c);
	visit(Q);
	DeleteQ1(Q);
	visit(Q);
	getchar();
    return 0;
}

void AddQ(Queue PtrQ, char item)
{
	if ((PtrQ->rear + 1) % Maxsize == PtrQ->front)
	{
		printf("队列满");
		return;
	}
	PtrQ->rear = (PtrQ->rear + 1) % Maxsize;
	PtrQ->Data[PtrQ->rear] = item;
}
char DeletQ(Queue PtrQ)
{
	if (PtrQ->front == PtrQ->rear)
	{
		printf("队列空");
		return NULL;
	}
	else
	{
		PtrQ->front = (PtrQ->front + 1) % Maxsize;
		return PtrQ->Data[PtrQ->front];
	}
}
//带头结点
char DeleteQ1(LQueue &PtrQ)
{
	Node *FrontCell;
	char FrontElem;
	if (PtrQ->front == NULL) { printf("队列空"); return NULL; }
	FrontCell = PtrQ->front;
	PtrQ->front = PtrQ->front->next;
	FrontElem = FrontCell->data;
	free(FrontCell);
	return FrontElem;
}
//带头结点的插入;
void AddQ1(LQueue &PtrQ, char item)
{
	Node* q = (Node*)malloc(sizeof(Node));
	q->data = item;
	q->next = NULL;
	PtrQ->rear->next = q; 
	PtrQ->rear = q;	
}
void visit(LQueue PtrQ)
{
	Node* q = PtrQ->front->next;//第一个元素
	char item;
	while (q != NULL)
	{
		item = q->data;
		printf("%c\n", item);
		q = q->next;
	}
}
void CreatQueue(LQueue &PtrQ)
{
	Node* q = (Node*)malloc(sizeof(Node));
	q->next = NULL;
	PtrQ->front = q;
	PtrQ->rear = q;
}

