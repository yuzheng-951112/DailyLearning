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
	int adjvex;										//�û���ָ��Ķ����λ��
	ArcNode *nextarc;								//ָ����һ������ָ��
	InfoType *info;									//����Ȩֵָ��
};//��ڵ�

typedef struct
{
	VertexType data;								//������Ϣ
	ArcNode *firstarc;								//��һ����ڵ�ĵ�ַ��ָ���һ����������Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

struct ALGraph
{
	AdjList vertices;
	int vexnum,arcnum;								//ͼ�ĵ�ǰ������
	int kind;										//ͼ�������־
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

bool visited[MAX_VERTEX_NUM];			//���ʱ�־����
void(*VisitFunc)(char*v);				//��������(ȫ����)


void main()
{

	int i,j,k,n;
	ALGraph g;
	VertexType v1,v2;
/*	printf("��ѡ������ͼ\n");
	CreateGraph(g);
	Display(g);
	printf("ɾ��һ�������,�������ɾ���߻򻡵Ļ�ͷ ��β:");
	scanf("%s%s",v1,v2);
	DeleteArc(g,v1,v2);
	Display(g);
	printf("�޸Ķ����ֵ,������ԭ��ֵ ��ֵ");
	scanf("%s%s",v1,v2);
	PutVex(g,v1,v2);
	Display(g);
	printf("�����¶���,�����붥���ֵ:");
	scanf("%s",v1);
	InsertVex(g,v1);
	printf("�����¶����йصĻ����,�����뻡�����:");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("��������һ�����ֵ:");
		scanf("%s",v2);
		printf("��������ͼ,��������һ����ķ���(0:��ͷ 1��β):");
		scanf("%d",&j);
		if(j)
			InsertArc(g,v2,v1);
		else
			InsertArc(g,v1,v2);
	}
	Display(g);
	printf("ɾ�����㼰��صĻ����,�����붥���ֵ:");
	scanf("%s",v1);
	DeleteVex(g,v1);
	Display(g);
	printf("������������Ľ��:\n");
	DFSTraverse(g,print);
	printf("������������Ľ��:\n");
	BFSTraverse(g,&print);
	DestroyGraph(g);*/
	printf("��˳��ѡ��������,����ͼ,������");
	for(i=0;i<3;i++)
	{
		CreateGraph(g);
		Display(g);
		printf("�����¶���,�����붥���ֵ:");
		scanf("%s",v1);
		InsertVex(g,v1);
		printf("�������¶����йصĻ����,�����뻡�����:");
		scanf("%d",&n);
		for(k=0;k<n;k++)
		{
			printf("��������һ����ֵ:");
			scanf("%s",v2);
			if(g.kind<=1)
			{
				printf("������������ͼ,��������һ���ķ���(0:��ͷ 1:��β):");
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
		printf("ɾ�����㼰��صĻ����,�����붥���ֵ:");
		scanf("%s",v1);
		DeleteVex(g,v1);
		Display(g);
		DestroyGraph(g);
	}
}

void CreateGraph(ALGraph &G)
{
	int i,j,k;
	int w;											//Ȩֵ
	VertexType va,vb;
	ArcNode *p;
	printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3):");
	scanf("%d",&G.kind);
	printf("������ͼ�Ķ�����,����:");
	scanf("%d,%d",&G.vexnum,&G.arcnum);
	printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	if(G.kind==1||G.kind==3)
		printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���)");
	else
		printf("��˳������ÿ����(��)�Ļ�β��ͷ(�Կո���Ϊ���):\n");
	for(k=0;k<G.arcnum;k++)							//��������ڵ�
	{
		if(G.kind==1||G.kind==3)
			scanf("%d%s%s",&w,va,vb);
		else
			scanf("%s%s",va,vb);
		i=LocateVex(G,va);							//��β
		j=LocateVex(G,vb);							//��ͷ
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		if(G.kind==1||G.kind==3)
		{
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w;
		}
		else
			p->info = NULL;
		p->nextarc = G.vertices[i].firstarc;		//���ڱ�ͷ
		G.vertices[i].firstarc=p;
		if(G.kind>=2)								//����ͼ����,�����ڶ�����ڵ�
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if(G.kind==3)
			{
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else
				p->info = NULL;						//����ͼ
			p->nextarc = G.vertices[j].firstarc;	//���ڱ�ͷ
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
	case 0:printf("����ͼ\n");
		   break;
	case 1:printf("������\n");
		   break;
	case 2:printf("����ͼ\n");
		   break;
	case 3:printf("������\n");
		   break;
	}
	printf("%d������:\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertices[i].data);
	printf("\n%d����(��):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind<=1)				//����
			{
				printf("%s->%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN)			//��
					printf(":%d",*(p->info));
			}
			else						//����
			{
				if(i<p->adjvex)
				{
					printf("%s-%s",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN)		//��
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
			printf("������ͷ��(β��)%sβ��(ͷ��)%s��Ȩֵ:");
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
			printf("������ͷ��(β��)%sβ��(ͷ��)%s��Ȩֵ:");
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
	VisitFunc = Visit;				//ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ�����
	for(w=0;w<G.vexnum;w++)
		visited[w] = false;			//���ʱ�־�����ʼ��
	for(w=0;w<G.vexnum;w++)
		if(!visited[w])
			DFS(G,w);				//����δ���ʵĶ������DFS
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
			DFS(G,w);				//��v����δ���ʵ�
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
	i = LocateVex(G,v1);			//iΪ����v1��ͼG�е����
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
	i = LocateVex(G,v);			//iΪ����w��ͼG�е����
	j = LocateVex(G,w);			//jΪ����w��ͼG�е����
	p = G.vertices[i].firstarc;
	while(p&&p->adjvex!=j)		//ָ��p��������ָ��ڵ㲻��w
		p = p->nextarc;
	if(!p||!p->nextarc)			//û�ҵ�w��w�����һ������
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
		printf("�ڴ����ʧ��!\n");
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
		printf("�ڴ����ʧ��!\n");
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

/*										//��׼��
void DeleteArc(ALGraph &G,VertexType v,VertexType w)
{
	ArcNode *p,*q;
	int i,j;
	i = LocateVex(G,v);
	j = LocateVex(G,w);
	if(i<0||j<0||i==j)
		return 0;
	p = G.vertices[i].firstarc;			//pָ�򶥵�v�ĵ�һ������
	while(p&&p->adjvex!=j)				//p��������ָ�Ļ����Ǵ�ɾ����<v,w>
	{
		q = p;
		p = p->nextarc;
	}
	if(p&&p->adjvex==j)
	{
		if(p==G.vertices[i].firstarc)
			G.vertices[i].firstarc = p->nextarc;
		else
			q->nextarc = p->nextarc;	//ָ����һ����
		if(G.kind%2)					//��
			free(p->info);
		G.arcnum--;						//���������1
	}
	if(G.kind>=2)						//����
	{
		p = G.vertices[j].firstarc;		//pָ�򶥵�w�ĵ�һ������
		while(p&&p->adjvex!=i)			//p��������ָ�Ļ����Ǵ�ɾ��<w,v>
		{		//pָ����һ����
			q = p;
			p = p->nextarc;
		}
		if(p&&p->adjvex==i)				//�ҵ���<w,v>
		{
			if(p==G.vertices[i].firstarc)		//p��ָ�ǵ�һ����
				G.vertices[j].firstarc = p->nextarc;	//ָ����һ����
			else
				q->nextarc = p->nextarc;
			if(G.kind==3)						//����ͼ
				free(p->info);
			free(p);
		}
	}
}
*/
