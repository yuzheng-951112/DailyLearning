#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define MAX_NAME 5
#define MAX_INFO 20
typedef char InfoType;
typedef char VertexType[MAX_VERTEX_NUM];
bool visited[MAX_VERTEX_NUM];
void(*VisitedFunc)(char*v);				//函数变量(全局量)

struct ArcBox
{
	int tailvex,headvex;		//该弧的尾和头顶点的职位
	ArcBox *hlink,*tlink;		//分别为弧头相同和弧尾相同的弧的链域
	InfoType *info;				//该弧相关信息的指针(可无)
};

struct VexNode
{
	VertexType data;
	ArcBox *firstin,*firstout;	//分别指向该项顶点第一条入弧和出弧
};

struct OLGraph
{
	VexNode xlist[MAX_VERTEX_NUM];//表头向量(数组)
	int vexnum,arcnum;			  //有向图的当前顶点数和弧数
};

typedef struct QNode
{
	int data;
	struct QNode *pNext;
}QNode,*qQNode;

typedef struct Queue
{
	qQNode front;
	qQNode rear;
}Queue,*qQueue;

void GreateDG(OLGraph &);
int LocateVex(OLGraph,VertexType);
void Display(OLGraph );
void PutVex(OLGraph &,VertexType,VertexType);
void InsertVex(OLGraph &,VertexType);
void InsertArc(OLGraph &,VertexType,VertexType);
void DeleteArc(OLGraph &,VertexType,VertexType);
void DFSTraverse(OLGraph,void(*Visit)(VertexType));
void DFS(OLGraph,int);
void BFSTraverse(OLGraph,void(*Visit)(VertexType));
void DestroyGraph(OLGraph &);
int FirstAdjVex(OLGraph,VertexType);
int NextAdjVex(OLGraph,VertexType,VertexType);
VertexType& GetVex(OLGraph,int u);
void DestroyGraph(OLGraph &);
void visit(char *s);

void init_QU(qQueue);
void enQU(qQueue,int);
void deQU(qQueue,int &);
bool empty(qQueue);

void main()
{
	int j,k,n;
	OLGraph g;
	VertexType v1,v2;
	GreateDG(g);
	Display(g);
	printf("修改顶点的值,请输入原值、新值:");
	scanf("%s%s",v1,v2);
	PutVex(g,v1,v2);
	printf("插入新顶点,请输入顶点的值:");
	scanf("%s",v1);
	InsertVex(g,v1);
	printf("插入与新顶点有关的弧,请输入弧数:");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("请输入另一顶点的值 另一顶点的方向(0:弧头 1:弧尾):");
		scanf("%s%d",v2,&j);
		if(j)
			InsertArc(g,v2,v1);
		else
			InsertArc(g,v1,v2);
	}
	Display(g);
	printf("删除一条弧,请输入待删除弧的弧头 弧尾:");
	scanf("%s%s",v1,v2);
	DeleteArc(g,v1,v2);
	Display(g);
	printf("深度优先搜索的结果:\n");
	DFSTraverse(g,&visit);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g,&visit);
	DestroyGraph(g);
}

int LocateVex(OLGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(!strcmp(G.xlist[i].data,u))
			return i;
	return -1;
}

void GreateDG(OLGraph &G)
{
	int i,j,k;
	int IncInfo;
	char str[MAX_INFO];
	ArcBox *p;
	VertexType v1,v2;
	printf("请输入有向图的顶点数,弧数,弧是否含其他信息(是:1,否:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_VERTEX_NUM);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",&G.xlist[i].data);		//输入顶点值
		G.xlist[i].firstin = NULL;			//初始化指针
		G.xlist[i].firstout = NULL;
	}
	printf("请输入%d条弧的弧头和弧头尾(空格为间隔):\n",G.arcnum);
	for(k=0;k<G.arcnum;k++)
	{
		scanf("%s%s",&v1,&v2);				//确定v1和v2在G中的位置
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));
		p->tailvex = j;
		p->headvex = i;
		p->hlink = G.xlist[j].firstin;		//完成在入弧和出弧链表表头的插入
		p->tlink = G.xlist[i].firstout;
		G.xlist[j].firstin = G.xlist[i].firstout = p;
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符):",MAX_INFO);
			scanf("%s",str);
			p->info = (InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
			strcpy(p->info,str);
		}
		else
			p->info = NULL;
	}
}

void PutVex(OLGraph &G,VertexType v1,VertexType v2)
{
	int i;
	i = LocateVex(G,v1);
	strcpy(G.xlist[i].data,v2);
}

void InsertVex(OLGraph &G,VertexType v1)
{
	strcpy(G.xlist[G.vexnum].data,v1);
	G.xlist[G.vexnum].firstin = NULL;
	G.xlist[G.vexnum].firstout = NULL;
	G.vexnum++;
}

void InsertArc(OLGraph &G,VertexType v1,VertexType v2)
{
	int i,j;
	int IncInfo;
	char str[MAX_INFO];
	ArcBox *p;
	i = LocateVex(G,v1);
	j = LocateVex(G,v2);
	p = (ArcBox *)malloc(sizeof(ArcBox));
	p->headvex = i;
	p->tailvex = j;
	p->tlink = G.xlist[i].firstout;
	p->hlink = G.xlist[j].firstin;
	G.xlist[i].firstout = G.xlist[j].firstin = p;
	printf("插入的弧是否含有信息(0:否,1:是):");
	scanf("%d",&IncInfo);
	if(IncInfo)
	{
		printf("请输入该弧的相关信息(<%d个字符):",MAX_INFO);
		scanf("%s",str);
		p->info = (InfoType*)malloc((strlen(str)+1)*sizeof(InfoType));
		strcpy(p->info,str);
	}
	else
		p->info = NULL;	
	G.arcnum++;
}

void DeleteArc(OLGraph &G,VertexType v1,VertexType v2)
{
	int i,j;
	ArcBox *p,*q;
	i = LocateVex(G,v1);
	j = LocateVex(G,v2);
	p = G.xlist[i].firstout;
	while(p->tailvex!=j)
	{	
		q = p;
		p = p->hlink;
	}
	if(p==G.xlist[i].firstout)
		G.xlist[i].firstout = p->tlink;	
	else
		q->hlink = p->hlink;
	p = G.xlist[j].firstin;
	while(p->headvex!=i)
	{
		q = p;
		p = p->hlink;
	}
	if(p==G.xlist[j].firstin)
		G.xlist[j].firstin = p->tlink;
	else
		q->tlink = p->tlink;
	if(p->info)
		free(p->info);
	free(p);
	G.arcnum--;
}

void DFSTraverse(OLGraph G,void(*Visit)(VertexType))
{
	int i;
	VisitedFunc = Visit;
	for(i=0;i<G.vexnum;i++)
		visited[i] = false;
	for(i=0;i<G.vexnum;i++)
		if(!visited[i])
			DFS(G,i);
	printf("\n");
}

void DFS(OLGraph G,int i)
{
	ArcBox *p;
	visited[i] = true;
	VisitedFunc(G.xlist[i].data);
	p = G.xlist[i].firstout;
	while(p&&visited[p->tailvex])
		p = p->tlink;
	if(p&&!visited[p->tailvex])
		DFS(G,p->tailvex);
}

void BFSTraverse(OLGraph G,void(*Visit)(VertexType))
{
	int w,v;
	VertexType u1,w1;
	Queue Q;
	init_QU(&Q);
	for(v=0;v<G.vexnum;v++)
		visited[v] = false;
	for(v=0;v<G.vexnum;v++)
	{
		if(!visited[v])
		{
			visited[v] = true;
			Visit(G.xlist[v].data);
			enQU(&Q,v);
			while(!empty(&Q))
			{
				deQU(&Q,v);
				strcpy(u1,GetVex(G,v));
				for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,GetVex(G,w))))
					if(!visited[w])
					{
						visited[w] = true;
						Visit(G.xlist[w].data);
						enQU(&Q,w);
					}
			}
		}
	}
}

int FirstAdjVex(OLGraph G,VertexType v)
{
	int i;
	ArcBox *p;
	i = LocateVex(G,v);
	p = G.xlist[i].firstout;
	if(p)
		return p->tailvex;
	else
		return -1;
}

int NextAdjVex(OLGraph G,VertexType v,VertexType w)
{
	int i,j;
	ArcBox *p;
	i = LocateVex(G,v);
	j = LocateVex(G,w);
	p = G.xlist[i].firstout;
	while(p&&p->tailvex!=j)
		p = p->tlink;
	if(p)
		p = p->tlink;
	if(p)
		return p->tailvex;
	else
		return -1;
}

VertexType& GetVex(OLGraph G,int u)
{
	return G.xlist[u].data; 
}

void Display(OLGraph G)
{
	int i;
	ArcBox *p;
	printf("有向图的%d个顶点分别为:\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.xlist[i].data);
	printf("\n有向图的%d个弧或边分别为:\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p = G.xlist[i].firstout;
		while(p)
		{
			printf("%s->%s",G.xlist[p->headvex].data,G.xlist[p->tailvex].data);
			if(p->info)
				printf(":%s",p->info);
			printf("\n");
			p = p->tlink;
		}
	}
}

void DestroyGraph(OLGraph &G)
{
	int i;
	ArcBox *p,*q;
	for(i=0;i<G.vexnum;i++)
	{
		p = G.xlist[i].firstout;
		while(p)
		{
			q = p;
			p = p->tlink;
			if(q->info)
				free(q->info);
			free(q);
		}
	}
	G.arcnum = 0;
	G.vexnum = 0;
}

void init_QU(qQueue QU)
{
	qQNode head_Node = (qQNode)malloc(sizeof(QNode));
	if(head_Node == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	QU->front = QU->rear = head_Node;
	head_Node->pNext = NULL;
}
	
void enQU(qQueue QU,int T)
{
	qQNode pNew = (qQNode)malloc(sizeof(QNode));
	if(pNew == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	pNew->data = T;
	QU->rear->pNext = pNew;
	QU->rear = pNew;
	pNew->pNext = NULL;
}

void deQU(qQueue QU,int &T)
{
	qQNode q = QU->front->pNext;
	if(empty(QU))
		exit(-1);
	QU->front->pNext = q->pNext;
	T = q->data;
	free(q);
	if(QU->rear == q)
		QU->rear = QU->front;
}

bool empty(qQueue QU)
{
	if(QU->rear == QU->front)
		return true;
	else
		return false;
}

void visit(char* s)
{
	printf("%s ",s);
}