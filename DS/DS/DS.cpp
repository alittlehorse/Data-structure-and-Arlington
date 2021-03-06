// DS.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
typedef int ElementType;
typedef struct
{
	ElementType Data;
	int Parent;
}SetType;
#define MaxSize 100
int Find(SetType S[], ElementType X);
int main()
{
    return 0;
}
int Find(SetType S[], ElementType X)
{
	int i;
	for (i = 0; i < MaxSize&&S[i].Data != X; ++i);
	if (i > MaxSize)return -1;
	for (; S[i].Parent >= 0; i = S[i].Parent);
	return i; 
}
void Union(SetType S[], ElementType X1, ElementType X2)
{
	int Root1, Root2;
	Root1 = Find(S,X1);
	Root2 = Find(S, X2);
	if (Root1 != Root2||Root1==Root2==-1)S[Root2].Parent = Root1;
	Dwarf(S);
}
void Dwarf(SetType H[]) {

	for (int i = 0; i < MaxSize; ++i) {
		if (H[i].Parent > 0) {
			if (H[H[i].Parent].Parent > 0) {
				while (H[H[i].Parent].Parent > 0)
					H[i].Parent = H[H[i].Parent].Parent;
				H[H[i].Parent].Parent -= 1;
			}
		}
	}
}