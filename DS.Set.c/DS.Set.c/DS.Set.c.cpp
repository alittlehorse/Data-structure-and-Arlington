// DS.Set.c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#define MaxSize 100
typedef int ElementType;
typedef int SetName;/*用根节点下标作为集合名称*/
typedef ElementType SetType[MaxSize];

SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName Root1, SetName Root2);
void Initialization(SetType S, int n);
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int n);

int main()
{
	SetType  S;
	int n;
	char in;
	printf("请输入元素的个数");
	scanf_s("%d\n", &n);
	Initialization(S,n);
	do {
		scanf_s("%c", &in);
		switch (in) {
			case'I':Input_connection(S); break;
			case'C':Check_connection(S); break;
			case'S':Check_network(S, n); break;		
		}
	} while (in != 'S');
    return 0;
}
//集合的简化表示
//对应关系为N-1
SetName Find(SetType S, ElementType X)//路径压缩
{
	if (S[X], 0) return X;
	else
		return S[X] = Find(S, S[X]);//尾递归,易于转换为循环
}
void Union(SetType S, SetName Root1, SetName Root2)
{
	int N1, N2;
	N1 = Find(S,Root1);
	N2 = Find(S, Root2);
	if (S[N2] < S[N1])//N2高 
		S[N1] = N2;
	else
	{
		if (S[N2] == S[N1])S[N1]--;
		S[N2] = N1;
	}
	if (N1 != N2) 	S[N2] = N1;
}
void Initialization(SetType S,int n)
{
	for (int i = 0; i < n; i++)S[i] = -1;
}

void Input_connection(SetType S)
{
	SetName SN1, SN2;
	scanf_s("%d%d", &SN1, &SN2);
	Union(S, SN1, SN2);

}
void Check_connection(SetType S)
{
	SetName SN1, SN2,N2,N1;
	scanf_s("%d%d", &SN1, &SN2);
	N1 = Find(S,SN1);
	N2 = Find(S, SN2);
	if (N1 == N2)printf("Yes\n");
	else printf("No\n");
}
void Check_network(SetType S, int n)
{
	int i, counter = 0;
	for (i = 1; i < n; i++)
	{
		if (S[i] < 0)counter++;
	}
	if (counter == 1)printf("the network is connect.\n");
	else printf("There are %d Components.\n", counter);
}

//