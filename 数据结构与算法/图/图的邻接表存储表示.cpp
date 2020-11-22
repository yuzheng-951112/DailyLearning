#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 5
#define MAX_INFO 20
#define MAX_VERTEX_NUM 20

enum GraphKind{DG,DN,AG,AN};

typedef int InfoType;
typedef char VertexType[MAX_VERTEX_NUM];

struct ArcNode
{
	int adjvex;										//该弧所指向的顶点的位置
	ArcNode *nextarc;								//指向下一条弧的指针
	InfoType *info;									//网的权值指针
};//表节点

typedef struct
{
	VertexType data;								//顶点信息
	ArcNode *firstarc;								//第一个表节点的地址，指向第一条依附顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

struct ALGraph
{
	AdjList vertices;
	int vexnum,arcnum;								//图的当前顶点数
	int kind;										//图的种类标志
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

void CreateGraph(ALGraph &);
int LocateVex(ALGraph G,VertexType u);
void Display(ALGraph G);
void DeleteArc(ALGraph &,VertexType,VertexType);
void PutVex(ALGraph &,VertexType,VertexType);
void InsertArc(ALGraph &,VertexType,VertexType);
void InsertVex(ALGraph &,VertexType);
void DeleteVex(ALGraph &,VertexType);
void DFSTraverse(ALGraph,void(*Visit)(char*));
void BFSTraverse(ALGraph,void(*Visit)(char*));
void DFS(ALGraph,int v);
char *GetVex(ALGraph,int);
void DestroyGraph(ALGraph &);
int FirstAdjVex(ALGraph,VertexType);
int NextAdjVex(ALGraph,VertexType,VertexType);

void init_QU(qQueue);
void enQU(qQueue,int);
void deQU(qQueue,int&);
bool empty(qQueue);

void print(char *i);

bool visited[MAX_VERTEX_NUM];			//访问标志数组
void(*VisitFunc)(char*v);				//函数变量(全局量)


void main()
{

	int i,j,k,n;
	ALGraph g;
	VertexType v1,v2;
/*	printf("请选择有向图\n");
	CreateGraph(g);
	Display(g);
	printf("删除一条弧或边,请输入待删除边或弧的弧头 弧尾:");
	scanf("%s%s",v1,v2);
	DeleteArc(g,v1,v2);
	Display(g);
	printf("修改顶点的值,请输入原来值 新值");
	scanf("%s%s",v1,v2);
	PutVex(g,v1,v2);
	Display(g);
	printf("插入新顶点,请输入顶点的值:");
	scanf("%s",v1);
	InsertVex(g,v1);
	printf("插入新顶点有关的弧或边,请输入弧或边数:");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("请输入另一顶点的值:");
		scanf("%s",v2);
		printf("对于有向图,请输入另一顶点的方向(0:弧头 1弧尾):");
		scanf("%d",&j);
		if(j)
			InsertArc(g,v2,v1);
		else
			InsertArc(g,v1,v2);
	}
	Display(g);
	printf("删除顶点及相关的弧或边,请输入顶点的值:");
	scanf("%s",v1);
	DeleteVex(g,v1);
	Display(g);
	printf("深度优先搜索的结果:\n");
	DFSTraverse(g,print);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g,&print);
	DestroyGraph(g);*/
	printf("请顺序选择有向网,无向图,无向网");
	for(i=0;i<3;i++)
	{
		CreateGraph(g);
		Display(g);
		printf("插入新顶点,请输入顶点的值:");
		scanf("%s",v1);
		InsertVex(g,v1);
		printf("插入与新顶点有关的弧或边,请输入弧或边数:");
		scanf("%d",&n);
		for(k=0;k<n;k++)
		{
			printf("请输入另一项点的值:");
			scanf("%s",v2);
			if(g.kind<=1)
			{
				printf("对于有向网或图,请输入另一项点的方向(0:弧头 1:弧尾):");
					scanf("%d",&j);
				if(j)
					InsertArc(g,v2,v1);
				else
					InsertArc(g,v1,v2);
			}
			else
				InsertArc(g,v1,v2);
		}
		Display(g);
		printf("删除顶点及相关的弧或边,请输入顶点的值:");
		scanf("%s",v1);
		DeleteVex(g,v1);
		Display(g);
		DestroyGraph(g);
	}
}

void CreateGraph(ALGraph &G)
{
	int i,j,k;
	int w;											//权值
	VertexType va,vb;
	ArcNode *p;
	printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3):");
	scanf("%d",&G.kind);
	printf("请输入图的顶点数,边数:");
	scanf("%d,%d",&G.vexnum,&G.arcnum);
	printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	if(G.kind==1||G.kind==3)
		printf("请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔)");
	else
		printf("请顺序输入每条弧(边)的弧尾弧头(以空格作为间隔):\n");
	for(k=0;k<G.arcnum;k++)							//构造链表节点
	{
		if(G.kind==1||G.kind==3)
			scanf("%d%s%s",&w,va,vb);
		else
			scanf("%s%s",va,vb);
		i=LocateVex(G,va);							//弧尾
		j=LocateVex(G,vb);							//弧头
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		if(G.kind==1||G.kind==3)
		{
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w;
		}
		else
			p->info = NULL;
		p->nextarc = G.vertices[i].firstarc;		//插在表头
		G.vertices[i].firstarc=p;
		if(G.kind>=2)								//无向图或网,产生第二个表节点
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if(G.kind==3)
			{
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else
				p->info = NULL;						//无向图
			p->nextarc = G.vertices[j].firstarc;	//插在表头
			G.vertices[j].firstarc = p;
		}
	}
}

int LocateVex(ALGraph G,VertexType u)
{
	for(int i=0;i<G.vexnum;i++)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

void Display(ALGraph G)
{
	int i;
	ArcNode *p;
	switch(G.kind)
	{
	case 0:printf("有向图\n");
		   break;
	case 1:printf("有向网\n");
		   break;
	case 2:printf("无向图\n");
		   break;
	case 3:printf("无向网\n");
		   break;
	}
	printf("%d个顶点:\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertices[i].data);
	printf("\n%d条弧(边):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind<=1)				//有向
			{
				printf("%s->%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN)			//网
					printf(":%d",*(p->info));
			}
			else						//无向
			{
				if(i<p->adjvex)
				{
					printf("%s-%s",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN)		//网
						printf(":%d ",*(p->info));
				}
			}
			p = p->nextarc;
		}
		printf("\n");
	}
}

void DeleteArc(ALGraph &G,VertexType v1,VertexType v2)
{
	int i,j;
	ArcNode *p,*q;
	i = LocateVex(G,v1);
	j = LocateVex(G,v2);
	p = G.vertices[i].firstarc;
	if(p->adjvex==j)
	{
		q = p->nextarc;
		G.vertices[i].firstarc = q;
	}
	else
	{
		while(p&&p->adjvex!=j)
		{
			q = p;
			p = p->nextarc;
		}
		q->nextarc = p->nextarc;
		if(G.kind==1)
			free(p->info);
	}
	free(p);
	if(G.kind>1)
	{
		p = G.vertices[j].firstarc;
		if(p->adjvex==i)
		{
			q = p->nextarc;
			G.vertices[i].firstarc = q;
		}
		else
		{
			while(p&&p->adjvex!=i)
			{
				q = p;
				p = p->nextarc;
			}
			q->nextarc = p->nextarc;
		}
		if(G.kind==3)
			free(p->info);
		free(p);
	}
	G.arcnum--;
}

void PutVex(ALGraph &G,VertexType v1,VertexType v2)
{
	for(int i=0;i<G.vexnum;i++)
	{
		if(!strcmp(G.vertices[i].data,v1))
		{
			strcpy(G.vertices[i].data,v2);
			break;
		}
	}
}

void InsertVex(ALGraph &G,VertexType v1)
{
	strcpy(G.vertices[G.vexnum].data,v1);
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
}

void InsertArc(ALGraph &G,VertexType v1,VertexType v2)
{
	int i,j,w;
	ArcNode *q;
	i = LocateVex(G,v1);
	j = LocateVex(G,v2);
	q = (ArcNode *)malloc(sizeof(ArcNode));
	q->adjvex = j;
	if(G.kind<=1)
	{
		q->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = q;
		if(G.kind==1)
		{
			printf("请输入头弧(尾弧)%s尾弧(头弧)%s的权值:");
			scanf("%d",&w);
			q->info = (int *)malloc(sizeof(int));
			*(q->info) = w;
		}
	}
	else
	{
		q = (ArcNode *)malloc(sizeof(ArcNode));
		q->adjvex = i;
		q->nextarc = G.vertices[i].firstarc;
		G.vertices[j].firstarc = q;
		if(G.kind==3)
		{
			printf("请输入头弧(尾弧)%s尾弧(头弧)%s的权值:");
			scanf("%d",&w);
			q->info = (int *)malloc(sizeof(int));
			*(q->info) = w;
		}
	}
	G.arcnum++;
}

void DeleteVex(ALGraph &G,VertexType v1)
{
	int i,j;
	ArcNode *q,*p;
	i = LocateVex(G,v1);
	q = G.vertices[i].firstarc;
	while(q)
	{
		p = q;
		q = q->nextarc;
		if(G.kind%2)
			free(p->info);
		free(p);
		G.arcnum--;
	}
	G.vexnum--;
	for(j=i;j<G.vexnum;j++)
		G.vertices[j] = G.vertices[j+1];
	for(j=0;j<G.vexnum;j++)
	{
		q = G.vertices[j].firstarc;
		while(q)
		{
			if(q->adjvex=i)
			{
				if(q=G.vertices[j].firstarc)
				{
					G.vertices[j].firstarc = q->nextarc;
					if(G.kind%2)
						free(q->info)
					free(q);
					if(G.kind<2)
						G.arcnum--;
				}
				else
				{
					p = q->nextarc;
					if(G.kind%2)
						free(q->info);
					free(q);
					q
				}
			}
		}
	}
	else
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(j!=i)
			{
				q = G.vertices[j].firstarc;
				if(q->adjvex==i)
				{
					p = G.vertices[i].firstarc;
					G.vertices[j].firstarc = p->nextarc;
					if(G.kind==3)
						free(p->info);
					free(p);
				}
				while(q)
				{
					p = q;
					q = q->nextarc;
					if(q->adjvex = i)
					{
						p->nextarc = q->nextarc;
						if(G.kind==3)
							free(q->info);
						free(q);
					}
					q = p->nextarc;
				}
			}
		}
	}
}

void DFSTraverse(ALGraph G,void(*Visit)(char*))
{
	int w;
	VisitFunc = Visit;				//使用全局变量VisitFunc,使DFS不用设函数指针参数
	for(w=0;w<G.vexnum;w++)
		visited[w] = false;			//访问标志数组初始化
	for(w=0;w<G.vexnum;w++)
		if(!visited[w])
			DFS(G,w);				//对尚未访问的顶点调用DFS
	printf("\n");
}

void DFS(ALGraph G,int v)
{
	int w;
	VertexType v1,w1;
	strcpy(v1,GetVex(G,v));
	VisitFunc(G.vertices[v].data);
	visited[v] = true;
	for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,GetVex(G,w))))
		if(!visited[w])
			DFS(G,w);				//对v的尚未访问的
}

char *GetVex(ALGraph G,int w)
{
	if(w>=G.vexnum||w<0)
		exit(-1);
	return G.vertices[w].data;
}

int FirstAdjVex(ALGraph G,VertexType v1)
{
	ArcNode *p;
	int i;
	i = LocateVex(G,v1);			//i为顶点v1在图G中的序号
	p = G.vertices[i].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{
	ArcNode *p;
	int i,j;
	i = LocateVex(G,v);			//i为顶点w在图G中的序号
	j = LocateVex(G,w);			//j为顶点w在图G中的序号
	p = G.vertices[i].firstarc;
	while(p&&p->adjvex!=j)		//指针p不空且所指表节点不是w
		p = p->nextarc;
	if(!p||!p->nextarc)			//没找到w或w是最后一个零界点
		return -1;
	else
		return p->nextarc->adjvex;
}

void BFSTraverse(ALGraph G,void(*Visit)(char*))
{
	int w,v;
	VertexType u1,w1;
	Queue Q;
	for(v=0;v<G.vexnum;v++)
		visited[v] = false;
	for(v=0;v<G.vexnum;v++)
	{
		if(!visited[v])
		{
			visited[v] = true;
			Visit(G.vertices[v].data);
			enQU(&Q,v);
			while(!empty(&Q))
			{
				deQU(&Q,v);
				strcpy(u1,GetVex(G,v));
				for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,GetVex(G,w))))
					if(!visited[w])
					{
						visited[w] = true;
						Visit(G.vertices[w].data);
						enQU(&Q,w);
					}
			}
		}
	}
	printf("\n");
}

void DestroyGraph(ALGraph &G)
{
	int i;
	ArcNode *p,*q; 
	for(i=0;i<G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			q = p;
			p = p->nextarc;
			if(q->info!=NULL)
				free(q->info);
			free(q);
		}
		G.arcnum = 0;
		G.vexnum = 0;
	}
}

void print(char *i)
{
	printf("%s ",i);
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

/*										//标准答案
void DeleteArc(ALGraph &G,VertexType v,VertexType w)
{
	ArcNode *p,*q;
	int i,j;
	i = LocateVex(G,v);
	j = LocateVex(G,w);
	if(i<0||j<0||i==j)
		return 0;
	p = G.vertices[i].firstarc;			//p指向顶点v的第一条出弧
	while(p&&p->adjvex!=j)				//p不空且所指的弧不是待删除弧<v,w>
	{
		q = p;
		p = p->nextarc;
	}
	if(p&&p->adjvex==j)
	{
		if(p==G.vertices[i].firstarc)
			G.vertices[i].firstarc = p->nextarc;
		else
			q->nextarc = p->nextarc;	//指向下一条弧
		if(G.kind%2)					//网
			free(p->info);
		G.arcnum--;						//弧或边数减1
	}
	if(G.kind>=2)						//无向
	{
		p = G.vertices[j].firstarc;		//p指向顶点w的第一条出弧
		while(p&&p->adjvex!=i)			//p不空且所指的弧不是待删弧<w,v>
		{		//p指向下一条弧
			q = p;
			p = p->nextarc;
		}
		if(p&&p->adjvex==i)				//找到弧<w,v>
		{
			if(p==G.vertices[i].firstarc)		//p所指是第一条弧
				G.vertices[j].firstarc = p->nextarc;	//指向下一条弧
			else
				q->nextarc = p->nextarc;
			if(G.kind==3)						//无向图
				free(p->info);
			free(p);
		}
	}
}
*/
