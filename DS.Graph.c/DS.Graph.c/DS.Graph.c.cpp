// DS.Graph.c.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>


#define MaxVertexNum 100
#define INFINITY 65535
#define Maxsize 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

bool Visited[MaxVertexNum] = { false };
//---------------***************邻接矩阵*************--------------
typedef struct GNode *PtrToGNode;
//邻接矩阵的定义
struct GNode {
	int Nv;//顶点数
	int Ne;//边数
	WeightType G[MaxVertexNum][MaxVertexNum];//Is there a road or not
	DataType Data[MaxVertexNum];
	//住;若定点无数据,此时Data[]可以不用出现
};
typedef PtrToGNode MGraph;//以邻接矩阵存储的图的类型

//-------------********************邻接表********************-------------------

typedef struct ENode *PtrToENode;
struct ENode
{
	Vertex V1, V2;
	WeightType Weight;
};
typedef PtrToENode Edge;
//邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;//临近点下标
	WeightType Weight;
	PtrToAdjVNode Next;
};
//定点表头节点的定义
typedef struct VNode {
	PtrToAdjVNode FirstEdge;//边表头指针
	DataType Data;//存顶点的数据
}AdjList[MaxVertexNum];
//图结点的定义
typedef struct LGNode *PtrToLGNode;
struct LGNode {
	int Nv;//点数
	int Ne;//边数
	AdjList G;//表头结点
};
typedef PtrToLGNode LGraph;//以邻接表方式储存图类型

//-------**************队列*************--------------
typedef struct Node *PtrToNode;
struct Node {
	PtrToNode Next;
	Vertex V;
};
typedef PtrToNode Position;
typedef struct QNode* PtrToQNode;
struct QNode {
	Position Front, Rear;
	int MaxSize;
};
typedef PtrToQNode Queue;


//--------------------**************函数原型************----------------------
void AddQ(Queue Q, Vertex V);
Queue CreateQueue(int size);
Vertex DeletQ(Queue Q);
bool IsEmpty(Queue Q);
//------------------------------------------------------------------
MGraph CreateMGraph(int VertexNum);
void InsertEdge_M(MGraph Graph, Edge E);
MGraph BuildGraph();
LGraph CreateLGraph(int VertexNum);
void InsertEdge_L(LGraph Graph, Edge E);
LGraph BuildLGraph();
//----------------------------------------------------------------
void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex));
void DFS_M(MGraph Graph, Vertex V, void(*Visit)(Vertex));
void Visit(Vertex X);
void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex));
void BFS_L(LGraph Graph, Vertex S, void(*Visit)(Vertex));

//----------------------------************main****************-------------------
int main()
{
	LGraph LG;
	LG = BuildLGraph();
	BFS_L(LG, 0, Visit);
	system("pause");
    return 0;
}
//-------------------***************邻接矩阵的建立*********************-----------------------

MGraph BuildGraph()
{
	MGraph M;
	Edge E;
	int Nv, i;
	printf("输入点数\n");
	scanf_s("%d", &Nv);
	M = CreateMGraph(Nv);
	printf("\n输入行数\n");
	scanf_s("%d", &(M->Ne));
	if (M->Ne != 0)
	{
		E = (Edge)malloc(sizeof(ENode));
		for (i = 0; i<M->Ne; i++) {
			printf("\n输入边");
			scanf_s("%d%d%d", &E->V1, &E->V2, &E->Weight);
			InsertEdge_M(M, E);
		}

	}
	return M;
}

void InsertEdge_M(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = E->Weight;
	//当无向图是,还要插入边
	Graph->G[E->V2][E->V1] = E->Weight;
}
//Create a Max
MGraph CreateMGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(GNode));//建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V < Graph->Nv; V++)
	{
		for (W = 0; W < Graph->Nv; W++) Graph->G[V][W] = INFINITY;
	}
	return Graph;
}



//-----------------**********************邻接表的建立*************************----------------------
LGraph CreateLGraph(int VertexNum)
{
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(LGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V < Graph->Nv; V++)
	{
		Graph->G[V].FirstEdge = NULL;
	}
	return Graph;
}

void InsertEdge_L(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;
	NewNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	//将V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;



	//如果是无向表,还要插入边<V2,V1>
	NewNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	//将V1插入V2的表头
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}
//Build a graph using a table
LGraph BuildLGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	printf("输入点数\n");;
	scanf_s("%d", &Nv);
	Graph = CreateLGraph(Nv);
	printf("\n输入行数\n");
	scanf_s("%d", &(Graph->Ne));
	if (Graph->Ne != 0)
	{
		E = (Edge)malloc(sizeof(ENode));
		for (i = 0; i < Graph->Ne; i++)
		{
			printf("\n输入边\n");
			scanf_s("%d%d%d", &E->V1, &E->V2, &E->Weight);
			InsertEdge_L(Graph, E);
		}
	}
	return Graph;
}


//------------------*******************两种遍历************************----------------------
void Visit(Vertex X)
{
	printf("正在访问顶点%d\n",X);
}

//邻接表存储图的深度优先遍历
void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex))
{
	PtrToAdjVNode W;
	Visit(V);
	Visited[V] = true;
	for (W = Graph->G[V].FirstEdge; W; W = W->Next)//对于V的每个邻接点W->Adjv下标;
	{
		if (!Visited[W->AdjV]&&W!=NULL)
			DFS(Graph, W->AdjV, Visit);
	}
}
//邻接矩阵的深度优先遍历
void DFS_M(MGraph Graph, Vertex V, void(*Visit)(Vertex))
{
	Visit(V);
	Visited[V] = true;
	for (int i = 0; i < Graph->Nv; i++)//遍历V的所有邻接点
	{
		if ((Graph->G[V][i] != INFINITY)&&(Visited[i]==false))
		{
			DFS_M(Graph, i, Visit);
		}
	}
}

bool IsEdge(MGraph Graph,Vertex V,Vertex W)
{
	return Graph->G[V][W] < INFINITY ? true : false;
}
void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex))
{
	Queue Q;
	Vertex V, W;

	Q = CreateQueue(Maxsize);

	Visit(S);
	Visited[S] = true;
	AddQ(Q, S);

	while (!IsEmpty(Q))
	{
		V = DeletQ(Q);
		for (W = 0; W < Graph->Nv; W++)//for every Vertex;
		{
			//W是V的临近点并且还未访问
			if (!Visited[W] && IsEdge(Graph, V, W))
			{
				Visit(W);
				Visited[W] = true;
				AddQ(Q, W);
			}
		}
	}
}
//邻接表实现广度优先遍历
void BFS_L(LGraph Graph, Vertex S, void(*Visit)(Vertex))
{
	Vertex V;
	PtrToAdjVNode PVN;
	Queue Q = CreateQueue(Graph->Nv);
	AddQ(Q, S);
	Visit(S);
	Visited[S] = true;
	while (!IsEmpty(Q))
	{
		V = DeletQ(Q);
		PVN = Graph->G[V].FirstEdge;
		while (PVN != NULL)
		{
			if (Visited[PVN->AdjV] == false)
			{
				Visit(PVN->AdjV);
				Visited[PVN->AdjV] = true;
				AddQ(Q, PVN->AdjV);
			}
			PVN = PVN->Next;
		}
	}
}

//-------------*******************对列的基本操作***********************----------------
void AddQ(Queue Q, Vertex V)
{
	Position P = (Position)malloc(sizeof(Node));
	P->Next = NULL;
	P->V = V;
	//对列为空时需要特殊处理
	if (Q->Front ==NULL)
	{
		Q->Front = Q->Rear = P;
	}
	else {
		//不空是向尾插入,头不动
		Q->Rear->Next = P;
		Q->Rear = Q->Rear->Next;
	}

}
bool IsEmpty(Queue Q)
{
	return (Q->Front == NULL);
}
Vertex DeletQ(Queue Q)
{
	Position FrontCell;
	Vertex FrontElem;
	if (!IsEmpty(Q))
	{
		FrontCell = Q->Front;
		if (Q->Front == Q->Rear)
			Q->Front = Q->Rear = NULL;
		else
			Q->Front = Q->Front->Next;
		FrontElem = FrontCell->V;
		free(FrontCell);
		return FrontElem;
	}
	else
	{
		printf("队列为空");
		return NULL;
	}
}

Queue CreateQueue(int size)
{
	Queue Q = (Queue)malloc(sizeof(QNode));
	Q->Front = Q->Rear = NULL;
	Q->MaxSize = size;
	return Q;
}


