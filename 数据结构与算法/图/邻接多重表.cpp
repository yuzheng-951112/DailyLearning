#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define MAX_NAME 3
#define MAX_INFO 80
typedef char InfoType;
typedef char VertexType[MAX_NAME];
enum VisitIf{unvisited,visited};

struct EBox
{
	VisitIf mark;			//���ʱ��
	int ivex,jvex;			//�ñ����������������λ��
	EBox *ilink,*jlink;		//�ֱ�ָ�������������������һ����
	InfoType *info;			//�ñ���Ϣָ��
};

struct VexBox
{
	VertexType data;
	EBox *firstedge;		//ָ���һ�����������ı�
};

struct AMLGraph
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum;		//����ͼ�ĵ�ǰ�������ͱ���
};

void CreateGraph(AMLGraph &);
int LocateVex(AMLGraph,VertexType);
void PutVex(AMLGraph,VertexType,VertexType);
void InsertVex(AMLGraph&,VertexType);
void InsertArc(AMLGraph&,VertexType,VertexType);
void Display(AMLGraph);
void DFSTraverse(AMLGraph,void(*visit)(char*));

void(*VisitedFunc)(char*v);
void visit(char *);

void main()
{
	int k,n;
	AMLGraph g;
	VertexType v1,v2;
	CreateGraph(g);
	Display(g);
	printf("�޸Ķ����ֵ,������ԭֵ ��ֵ:");
	scanf("%s%s",v1,v2);
	PutVex(g,v1,v2);
	printf("�����¶���,�����붥���ֵ:");
	scanf("%s",v1);
	InsertVex(g,v1);
	printf("�������¶����йصı�,���������:");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("��������һ�����ֵ:");
		scanf("%s",v2);
		InsertArc(g,v1,v2);
	}
	Display(g);
	printf("������������Ľ��:\n");
	DFSTraverse(g,visit);
	printf("������������Ľ��:\n");
	BFSTraverse(g,visit);
	DestroyGraph(g);
}

int LocateVex(AMLGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(u,G.adjmulist[i].data)==0)
			return i;
	return -1;
}

void CreateGraph(AMLGraph &G)
{
	int i,j,k,l,IncInfo;
	char s[MAX_INFO];
	VertexType va,vb;
	EBox *p;
	printf("����������ͼG�Ķ�����,���������Ƿ�������Ϣ(��:0,��:1)");
	scanf("%d,%d,%d",&G.vexnum,&G.edgenum,&IncInfo);
	printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.adjmulist[i].data);
		G.adjmulist[i].firstedge = NULL;
	}
	printf("��˳������ÿ���ߵ������˵�(�Կո���Ϊ���):\n");
	for(k=0;k<G.edgenum;i++)
	{
		scanf("%s%s%*c",va,vb);		//%*c�Ե��س�����
		i = LocateVex(G,va);
		j = LocateVex(G,vb);
		p = (EBox*)malloc(sizeof(EBox));
		p->mark = unvisited;
		p->ivex = i;
		p->jvex = j;
		p->info = NULL;
		p->ilink = G.adjmulist[i].firstedge;
		G.adjmulist[i].firstedge = p;
		p->jlink = G.adjmulist[j].firstedge;
		G.adjmulist[j].firstedge = p;
		if(IncInfo)
		{
			printf("������û��������Ϣ(<%d���ַ�):",MAX_INFO);
			gets(s);
			l = strlen(s);
			if(l)
			{
				p->info = (char*)malloc((l+1)*sizeof(char));
				strcpy(p->info,s);
			}
		}
	}
}

void PutVex(AMLGraph G,VertexType v,VertexType w)
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(!strcmp(G.adjmulist[i].data,v))
		{
			strcpy(G.adjmulist[i].data,w);
		}
	}
}

void InsertVex(AMLGraph& G,VertexType v1)
{
	strcpy(G.adjmulist[G.vexnum].data,v1);
	G.adjmulist[G.vexnum].firstedge = NULL;
	G.vexnum++;
}

void InsertArc(AMLGraph& G,VertexType v1,VertexType v2)
{
	int i,j,l,IncInfo;
	char s[MAX_INFO];
	EBox *p;
	i = LocateVex(G,v1);
	j = LocateVex(G,v2);
	p = (EBox *)malloc(sizeof(EBox));
	p->ivex = i;
	p->jvex = j;
	p->ilink = G.adjmulist[i].firstedge;
	G.adjmulist[i].firstedge = p;
	p->jlink = G.adjmulist[j].firstedge;
	G.adjmulist[j].firstedge = p;
	printf("%s->%s�Ƿ�������Ϣ(��:0,��:1):",G.adjmulist[i].data,G.adjmulist[j].data);
	scanf("%d",&IncInfo);
	if(IncInfo)
	{
		printf("������û��������Ϣ(<%d���ַ�):",MAX_INFO);
		gets(s);
		l = strlen(s);
		p->info = (char *)malloc((l+1)*sizeof(char));
		strcpy(p->info,s);
	}
	G.edgenum++;
}

void DFSTraverse(AMLGraph,void(*visit)(char*))
{
	
}

void Display(AMLGraph G)	//�ѵ�
{
	int i;
	EBox *p;
	MarkUnvisited(G);		//�ñߵķ��ʱ��Ϊδ������
	printf("%d������:\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.adjmulist[i].data);
	printf("%d����:\n",G.edgenum);
	for(i=0;i<G.vexnum;i++)
	{
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			if(p->ivex==i)
			{
				printf("%s-%s",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
				p->mark = visited;
				if(p->info)
					printf("�����Ϣ:%s",p->info);
			}
		}
		p = p->ilink;
	}
	else
	{
		if(!p->mark)
		{
			printf("%s-%s",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
			p->mark = visited;
			if(p->info)
				printf("�����Ϣ:%s",p->info);
		}
		p = p->jlink;
		printf("\n");
	}
}

void visit(char *s)
{
	printf("%s",s);
}