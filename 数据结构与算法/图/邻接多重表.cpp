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
	VisitIf mark;			//访问标记
	int ivex,jvex;			//该边依附的两个顶点的位置
	EBox *ilink,*jlink;		//分别指向依附这两个顶点的下一条边
	InfoType *info;			//该边信息指针
};

struct VexBox
{
	VertexType data;
	EBox *firstedge;		//指向第一条依附该项点的边
};

struct AMLGraph
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum;		//无向图的当前顶点数和边数
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
	printf("修改顶点的值,请输入原值 新值:");
	scanf("%s%s",v1,v2);
	PutVex(g,v1,v2);
	printf("插入新顶点,请输入顶点的值:");
	scanf("%s",v1);
	InsertVex(g,v1);
	printf("插入与新顶点有关的边,请输入边数:");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("请输入另一顶点的值:");
		scanf("%s",v2);
		InsertArc(g,v1,v2);
	}
	Display(g);
	printf("深度优先搜索的结果:\n");
	DFSTraverse(g,visit);
	printf("广度优先搜索的结果:\n");
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
	printf("请输入无向图G的顶点数,边数，边是否含其他信息(是:0,否:1)");
	scanf("%d,%d,%d",&G.vexnum,&G.edgenum,&IncInfo);
	printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.adjmulist[i].data);
		G.adjmulist[i].firstedge = NULL;
	}
	printf("请顺序输入每条边的两个端点(以空格作为间隔):\n");
	for(k=0;k<G.edgenum;i++)
	{
		scanf("%s%s%*c",va,vb);		//%*c吃掉回车符号
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
			printf("请输入该弧的相关信息(<%d个字符):",MAX_INFO);
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
	printf("%s->%s是否含其他信息(是:0,否:1):",G.adjmulist[i].data,G.adjmulist[j].data);
	scanf("%d",&IncInfo);
	if(IncInfo)
	{
		printf("请输入该弧的相关信息(<%d个字符):",MAX_INFO);
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

void Display(AMLGraph G)	//难点
{
	int i;
	EBox *p;
	MarkUnvisited(G);		//置边的访问标记为未被访问
	printf("%d个顶点:\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.adjmulist[i].data);
	printf("%d条边:\n",G.edgenum);
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
					printf("相关信息:%s",p->info);
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
				printf("相关信息:%s",p->info);
		}
		p = p->jlink;
		printf("\n");
	}
}

void visit(char *s)
{
	printf("%s",s);
}