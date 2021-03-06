// DS.Stack.c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10
typedef struct SNode
{
	char Data[MaxSize];
	int Top;
}SNode, *Stack;

//*****************************************************
//***********************用一个数组实现双堆栈************
//*****************************************************
typedef struct {
	char Data[MaxSize];
	int Top1;
	int Top2;
}*DStack;

typedef struct SLNode *SLStack;
//***************************************************
//*********************链式存储结构******************
//***************************************************
struct SLNode
{
	char Data;
	SLNode* Next;
};

void Push(Stack PtrS, char item);
char Pop(Stack PtrS);
//对于一个数组-两个堆栈的操作
void PushD(DStack PtrS, char item, int Tag);
char PopD(DStack PtrS, int Tag);

bool isEmpty(SLStack S);
void PushSL(SLStack &S, char item);
char PopSL(SLStack &S);

int main()
{
    return 0;
}
void Push(Stack PtrS, char item)
{
	if (PtrS->Top == MaxSize - 1)//全部放满
	{
		printf("Stack is full"); return;
	}
	else
	{
		PtrS->Data[++(PtrS->Top)] = item;
		return;
	}

}
char Pop(Stack PtrS)
{
	if (PtrS->Top >= 0)
	{
		char item;
		item = PtrS->Data[PtrS->Top];
		--PtrS->Top;
		return item;
	}
	else { printf("Stack is empty!"); return; }
}

//Tag==1位堆栈1,其余为堆栈2;
void PushD(DStack PtrS, char item, int Tag)
{
	if ((PtrS->Top1) -(PtrS->Top2)==1)
	{
		printf("堆栈满"); return;
	}
	if (Tag == 1)
	{
		PtrS->Data[++(PtrS->Top1)] = item;
	}
	else {
		PtrS->Data[--(PtrS->Top2)] = item;
	}
}

char PopD(DStack PtrS,int Tag)
{
	if (Tag == 1)
	{
		if (PtrS->Top1 == -1) { printf("堆栈1为空"); return NULL; }
		else
		{
			
			return PtrS->Data[(PtrS->Top1)++];
		}
	}
	else
	{
		if (PtrS->Top2 == MaxSize) { printf("堆栈2为空"); return NULL; }
		else
		{
			++PtrS->Top2;
			return PtrS->Data[(PtrS->Top2)++];
		}

	}
}

SLStack CreatStack()
{
	SLStack S;
	S = (SLStack)malloc(sizeof(SLNode));
	S->Next = NULL;
	return S;
}
bool isEmpty(SLStack S)
{
	return(S->Next == NULL);
}
//选择头插法进行Push,头结点是Top;
void PushSL(SLStack &S, char item)
{
	SLStack p=(SLStack) malloc(sizeof(SLNode));
	p->Data = item;
	p->Next = S->Next;
	S->Next = p;
}

char PopSL(SLStack &S)
{
	SLStack p;
	if (isEmpty(S)) { printf("栈为空"); return NULL; }
	else
	{
		p = S->Next;
		S->Next = p->Next;
		char resualt = p->Data;
		free(p);
		return resualt;
	}
}


//从头到尾读取中缀表达式的每个对象
// 运算数,直接输出
//左括号,压入堆栈
//右括号:将栈顶运算符弹出并输出,指导遇到左括号
//运算符:优先级大于栈顶的优先级,压栈
//优先级小于等于栈顶的运算符时,将栈顶运算符弹出并输出;在比较较新的栈顶运算符,指导该运算符大于栈顶运算符的优先级位置,
//然后将该运算符压栈
//等到全部处理完,讲站中的运算符一并输出

char* Fh(char* c)
{
	char* temp = c;
	SLStack SS1 = CreatStack();
	SLStack SS2 = CreatStack();
	while (*temp != '\0')
	{
		&temp + 4;
		
	}
}
