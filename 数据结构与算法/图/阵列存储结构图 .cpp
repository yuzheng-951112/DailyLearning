#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define true 1
#define false 0
#define INFINITY INT_MAX
#define MAX_NAME 5
#define MAX_INFO 20
#define MAX_VERTEX_NUM 20
enum GraphKind{DG,DN,AG,AN};        //{����ͼ��������������ͼ��������}��Ӧ{0,1,2,3}
/*
���ߵ�����
�����ڽӾ���Adjacency Matrix�����Ǳ�ʾ����֮�����ڹ�ϵ�ľ�����G=(V,E)��һ��ͼ������V={v1,v2,��,vn}��
    G���ڽӾ�����һ�������������ʵ�n�׷���
�����ٶ�����ͼ���ԣ��ڽӾ���һ���ǶԳƵģ��������Խ���һ��Ϊ�㣨�ڴ˽����������ͼ�������Խ��߲�һ��Ϊ0��
    ����ͼ��һ����ˡ�
������������ͼ�У���һ����i�Ķ�Ϊ��i������Ԫ�صĺͣ�������ͼ�ж���i�ĳ���Ϊ��i������Ԫ�صĺͣ������Ϊ��i������Ԫ�صĺ͡�
���������ڽӾ��󷨱�ʾͼ����Ҫn^2���ռ䣬��������ͼ���ڽӾ���һ�����жԳƹ�ϵ�����Կ۳��Խ���Ϊ���⣬
    ����Ҫ�洢�������λ��������ε����ݼ��ɣ���˽���Ҫn��n-1��/2���ռ䡣 
*/

typedef int BOOL;
BOOL visited[MAX_VERTEX_NUM];
typedef int VRType;
typedef char VertexType[MAX_VERTEX_NUM];
typedef char InfoType; 

typedef struct
{
    VRType adj;     //�����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ�
                    //�Դ�Ȩͼ����ΪȨֵ���ͣ�
    InfoType *info; //�û������Ϣ��ָ��
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM];    //��������
    AdjMatrix arcs;                     //�ڽӾ���
    int vexnum,arcnum;                  //ͼ�ĵ�Ȩ�������ͻ���
    GraphKind kind;                     //ͼ�������־
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

void CreateFAG(MGraph &);
int LocateVex(MGraph,VertexType);
void Display(MGraph);
void PutVex(MGraph &,VertexType,VertexType);    
void DFSTraverse(MGraph);
void DFS(MGraph,int);
void DFSTraverse1(MGraph);
void DFS1(MGraph,int);
int FirstAdjVex(MGraph,VertexType);
int NextAdjVex(MGraph,VertexType,VertexType);
void BFSTraverse(MGraph);
void CreateGraph(MGraph &);
void CreateDG(MGraph &); //��������ͼ

void CreateDN(MGraph &); //����������
void CreateAG(MGraph &); //��������ͼ
void CreateAN(MGraph &); //����������

void InsertVex(MGraph&,VertexType);             //�����µĶ���
void InsertArc(MGraph&,VertexType,VertexType);  //��������ͼ�ķ���
void DeleteArc(MGraph&,VertexType,VertexType);
void DestroyGraph(MGraph&);
void Deletevex(MGraph&,VertexType);

void init_QU(qQueue);
void enQU(qQueue,int);
void deQU(qQueue,int &);
bool empty(qQueue);

int main()
{
    int i,n,k,j;
    VertexType v1,v2;
    MGraph g;
    CreateFAG(g);
    Display(g);
    printf("�޸Ķ����ֵ��������ԭֵ ��ֵ:");
    scanf("%s%s",v1,v2);
    PutVex(g,v1,v2);
    printf("������������Ľ��(�ǵݹ�):\n");
    DFSTraverse(g);
    printf("\n������������Ľ��(�ݹ�):\n");
    DFSTraverse1(g);
    printf("\n������������Ľ��\n");
    BFSTraverse(g);
    printf("ɾ��һ���߻򻡣��������ɾ���߻򻡵Ļ�β ��ͷ:");
    scanf("%s%s",v1,v2);
    DeleteArc(g,v1,v2);
    Display(g);
    DestroyGraph(g);
    printf("�밴˳��ѡ������ͼ��������������ͼ��������\n");
    for(i=0;i<4;i++)
    {
        CreateGraph(g);
        Display(g);
        printf("�����¶��㣬�����붥���ֵ:");
        scanf("%s",v1);
        InsertVex(g,v1);
        printf("�������¶����йصĻ���ߣ������뻡�����:");
        scanf("%d",&n);
        for(k=0;k<n;k++)
        {
            printf("����һ�����ֵ:");
            scanf("%s",v2);
            if(g.kind<=1)
            {
                printf("��������ͼ��������������һ��ķ���(0:��ͷ 1:��β):");
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
        printf("ɾ�����㼰��صĻ���ߣ������붥���ֵ:");
        scanf("%s",v1);
        Deletevex(g,v1);
		Display(g);
    }   
    scanf("%d",&i);
	return 0;
}

void CreateFAG(MGraph &G)
{
    int i,j,k;
//    char filename[130];
    VertexType va,vb;
    FILE *graphlist;
    printf("�����������ļ���(f7-1.dat):");
  //  scanf("%s",filename);
    if((graphlist = fopen("D:\\VC++6.0\\VC++6.0\\MyProjects\\���ݽṹ\\ͼ\\ͼ������洢��ʾ\\f7-1.txt","a+"))!=NULL)
    {
        fscanf(graphlist,"%d",&G.vexnum);
        fscanf(graphlist,"%d",&G.arcnum);
        for(i=0;i<G.vexnum;i++)
            fscanf(graphlist,"%s",&G.vexs[i]);
        for(i=0;i<G.vexnum;i++)
        {
            for(j=0;j<G.vexnum;j++)
            {
                G.arcs[i][j].adj = 0;
                G.arcs[i][j].info = NULL;
            }
        }
        for(k=0;k<G.arcnum;k++)
        {
            fscanf(graphlist,"%s%s",va,vb);             //�ո����va��vb
            i = LocateVex(G,va);
            j = LocateVex(G,vb);
            G.arcs[i][j].adj = G.arcs[j][i].adj = 1;    //����ͼ
        }
        G.kind = AG;
        fclose(graphlist);
    }
	else
		exit(-1);
}

void Display(MGraph G)
{
    int i,j;
    char *s=(char*)malloc(7*sizeof(char)),
		 *s1=(char*)malloc(3*sizeof(char));
    switch(G.kind)
    {
        case DG:strcpy(s,"����ͼ\0");
                strcpy(s1,"��\0");
                break;
        case DN:strcpy(s,"������\0");
				strcpy(s1,"��\0");
				break;
		case AG:strcpy(s,"����ͼ\0");
				strcpy(s1,"�߽�\0");
				break;
		case AN:strcpy(s,"������\0");
				strcpy(s1,"��\0");     
    }
/*
#include<stdio.h>
#include<stdlib.h>

int main(void) {
    char s[]="123456789";
    char d[]="123";

    strcpy(d,s);

    printf("%s,\n%s",d,s);

    return 0;
}
�������123456789
       56789
�����漰���ڴ渲������d,s�ڴ��Ϊstrcpy()����ǰΪd 123\000,s 123456789\000
����strcpy()��d 1234,s 56789\000
������õİ취�Ƿ��䶯̬�ڴ�
char *s=(char*)malloc(7*sizeof(char)),
	 *s1=(char*)malloc(3*sizeof(char));
*/
    printf("\n%d������%d��%s��%s\n",G.vexnum,G.arcnum,s1,s);
    for(i=0;i<G.vexnum;i++)
    {
        printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
    }
    printf("G.arcs.adj:\n");
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            printf("%d ",G.arcs[i][j].adj);
        }
        printf("\n");
    }
    printf("G.arcs.info:\n");       //���G.arcs.info
    printf("����1(��β) ����2(��ͷ) ��%s��Ϣ:\n",s1);
    if(G.kind<2)					//����ͼ
    {
		for(i=0;i<G.vexnum;i++)
        {
            for(j=0;j<G.vexnum;j++)
            {
                if(G.arcs[i][j].info)
                printf("%5s %11s      %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
            }
        }
	}	
    else								//����ͼ
    {
        for(i=0;i<G.vexnum;i++)
        {
            for(j=i+1;j<G.vexnum;j++)	//����ͼj=i+1���Լ��ٱ����ظ���
            {
                if(G.arcs[i][j].info)
                printf("%5s %11s      %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
            }
        }
    }
}

int LocateVex(MGraph G,VertexType u)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(strcmp(u,G.vexs[i])==0)
            return i;
    }
    return -1;
}

void PutVex(MGraph &G,VertexType v1,VertexType v2)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(strcmp(G.vexs[i],v1)==0)
        {
            strcpy(G.vexs[i],v2);
            break;
        }
    }
}

void DFSTraverse(MGraph G)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        visited[i] = false;
    }
    printf("%s ",G.vexs[0]);
    visited[0] = true;
    for(i=0;i<G.vexnum-1;i++)
    {
            DFS(G,i);
    }
}

void DFS(MGraph G,int i)
{
    int j;
    for(j=0;j<G.vexnum;j++)
    {
        if(G.arcs[i][j].adj==1 && visited[j]==false)
        break;
    }
    visited[j] = true;
    printf("%s ",G.vexs[j]);
}

void DFSTraverse1(MGraph G)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        visited[i] = false;
    }
    for(i=0;i<G.vexnum;i++)
    {
        if(visited[i]==false)
            DFS1(G,i);
    }
}

void DFS1(MGraph G,int i)
{
    int w;
//    char *w2;
    VertexType v1,w1;
    visited[i] = true;
    printf("%s ",G.vexs[i]);
    strcpy(v1,G.vexs[i]);
    for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,G.vexs[w])))     //����ķ���ֵ�ǵ�ַ��ַ VertexType��char������ �׵�ַҲ�ǵ�ַ
    {
/*
w=FirstAdjVex(G,v1)���ҵ���Ӧ�ĵ�һ��adj==1�����
w=NextAdjVex(G,v1,strcpy(w1,GetVex(G,w)))���ҵ���һ����һ����Ӧadj==1����� �����v1��Ӧ�����У�strcpy(w1,GetVex(G,w))��Ӧ������
*/
        if(!visited[w])
            DFS1(G,w);
    }
}
/*
strcpy()����
char * __cdecl strcpy(char * dst, const char * src)
{
        char * cp = dst;
        while( *cp++ = *src++ )
                ;               // Copy src over dst 
        return( dst );
} 
����ֵ�Ǹ����ַ����ĵ�ַ
*/

void BFSTraverse(MGraph G)
{
    int v,u,w;
    VertexType w1,u1;
    Queue Q;
    for(v=0;v<G.vexnum;v++)
    {
        visited[v] = 0;
    }
    init_QU(&Q);
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
        {
            visited[v] = true;
            printf("%s ",G.vexs[v]);
            enQU(&Q,v);
            while(!empty(&Q))
            {
                deQU(&Q,u);
                strcpy(u1,G.vexs[u]);
                for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,G.vexs[w])))
                {
                    if(!visited[w])
                    {
                        visited[w] = true;
                        printf("%s ",G.vexs[w]);
                        enQU(&Q,w);
                    }
                }
            }
        }
    }
    printf("\n");
}

int FirstAdjVex(MGraph G,VertexType v)  //��������һ��������׸�adj==1����
{
    int i,j=0,k;
    k = LocateVex(G,v);
    if(G.kind==DN || G.kind==AN)        //��
        j = INFINITY;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.arcs[k][i].adj==1)
 //           if(visited[i]==false)
                return i;
    }
    return -1;
}

int NextAdjVex(MGraph G,VertexType v1,VertexType w)
{
    int i,j=0,k1,k2;
    k1 = LocateVex(G,v1);       //k1Ϊ��������λ��  ��Ӧ��
    k2 = LocateVex(G,w);        //k2Ϊ��������λ��  ��Ӧ��
    if(G.kind==DN || G.kind==AN)
        j = INFINITY;
    for(i=k2+1;i<G.vexnum;i++)
        if(G.arcs[k1][i].adj!=j)
            return i;
    return -1;
}

void DeleteArc(MGraph& G,VertexType v1,VertexType v2)
{
    int i,j;
    i = LocateVex(G,v1);     //β
    j = LocateVex(G,v2);     //ͷ
    if(i<0||j<0)
        exit(-1);
    if(G.kind%2==0)
        G.arcs[i][j].adj = 0;
    else
        G.arcs[i][j].adj = INFINITY;
    if(G.arcs[i][j].info)    //�����������Ϊβ�ͣ���Ϊͷ
    {
        free(G.arcs[i][j].info);
        G.arcs[i][j].info = NULL;
    }
    if(G.kind>=2)           //����ɾ���Գƻ�
    {
        G.arcs[j][i].adj = G.arcs[i][j].adj;
        G.arcs[j][i].info = NULL;
    }
    G.arcnum--;
}

void DestroyGraph(MGraph& G)
{
    int i,j;
    if(G.kind<2)
        for(i=0;i<G.vexnum;i++)
            for(j=0;j<G.vexnum;j++)
                if(G.kind==0&&G.arcs[i][j].adj==1||G.kind==1&&G.arcs[i][j].adj!=INFINITY)   //����ͼ�Ļ�||�������Ļ�
                    if(G.arcs[i][j].info)
                    {
                        free(G.arcs[i][j].info);
                        G.arcs[i][j].info = NULL;
                    }
    else
        for(i=0;i<G.vexnum;i++)
            for(j=i+1;j<G.vexnum;j++)
            {
                if(G.arcs[i][j].adj==1&&G.kind==2||G.arcs[i][j].adj!=INFINITY&&G.kind==3)       //����ͼ�ı�||�������ı�
                    if(G.arcs[i][j].info)
                    {
                        free(G.arcs[i][j].info);
                        G.arcs[i][j].info = G.arcs[i][j].info = NULL;
                    }
            }
    G.vexnum = 0;
    G.arcnum = 0;
}

void CreateGraph(MGraph &G)
{
    printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3)");
    scanf("%d",&G.kind);
    switch(G.kind)
    {
        case DG:CreateDG(G); //��������ͼ
			 break;
        case DN:CreateDN(G); //����������
			 break;
		case AG:CreateAG(G); //��������ͼ
			 break;
        case AN:CreateAN(G); //����������
			 break;
    }
}

void CreateDG(MGraph &G)
{
    int i,j,k,l,IncInfo;
    char s[MAX_INFO],*info;
    VertexType va,vb;
    printf("����������ͼG�Ķ�����,����,���Ƿ���������Ϣ(��:1 ��:0):");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("������%d�������ֵ(%d���ַ�):\n",G.vexnum,MAX_NAME);
    for(i=0;i<G.vexnum;i++)
    {
        scanf("%s",G.vexs[i]);
    }
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = 0;       //ͼ
            G.arcs[i][j].info = NULL;
        }
    }
    printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���):\n",G.arcnum);
    for(k=0;k<G.arcnum;k++)
    {
        scanf("%s%s%*c",va,vb);
        i = LocateVex(G,va);
        j = LocateVex(G,vb);
        G.arcs[i][j].adj = 1;
        if(IncInfo)
        {
            printf("������û��������Ϣ(%d���ַ�):",MAX_INFO);
            gets(s);
            l = strlen(s);
            if(l)
            {
                info =  (char*)malloc((l+1)*sizeof(char));
                strcpy(info,s);
                G.arcs[i][j].info = info;
            }
        }
    }
    G.kind = DG;
}

void CreateAG(MGraph &G)
{
	int i,j,l,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	printf("����������ͼG�Ķ���,����,���Ƿ�������Ϣ(��:1,��:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("������%d�������ֵ(%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vexs[i]);
	}
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���):\n",G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%s%s%*c",va,vb);
		i = LocateVex(G,va);
        j = LocateVex(G,vb);
		G.arcs[i][j].adj = 1;
		G.arcs[j][i].adj = 1;
		if(IncInfo)
		{
			printf("������û��������Ϣ(%d���ַ�):",MAX_INFO);
			gets(s);
			l = strlen(s);
			if(l)
			{
				info = (char*)malloc(sizeof(char)*(l+1));
				strcpy(info,s);
				G.arcs[i][j].info = info;
			}
		}
	}
	G.kind = AG;
}

void CreateDN(MGraph &G)
{
	int i,j,l,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	printf("����������ͼG�Ķ���,����,���Ƿ�������Ϣ(��:1,��:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("������%d�������ֵ(%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vexs[i]);
	}
	for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = INFINITY;       //��	
            G.arcs[i][j].info = NULL;
        }
    }
	printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���):\n",G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%s%s%d%*c",va,vb,&w);
		i = LocateVex(G,va);
        j = LocateVex(G,vb);
		G.arcs[i][j].adj = w;
		if(IncInfo)
		{
			printf("������û��������Ϣ(%d���ַ�):",MAX_INFO);
			gets(s);
			l = strlen(s);
			if(l)
			{
				info = (char*)malloc(sizeof(char)*(l+1));
				strcpy(info,s);
				G.arcs[i][j].info = info;
			}
		}
	}
	G.kind = DN;
}

void CreateAN(MGraph &G)
{
	int i,j,l,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	printf("����������ͼG�Ķ���,����,���Ƿ�������Ϣ(��:1,��:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("������%d�������ֵ(%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vexs[i]);
	}
	for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = INFINITY;       //��	
            G.arcs[i][j].info = NULL;
        }
    }
	printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���):\n",G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%s%s%d%*c",va,vb,&w);
		i = LocateVex(G,va);
        j = LocateVex(G,vb);
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = w;
		if(IncInfo)
		{
			printf("������û��������Ϣ(%d���ַ�):",MAX_INFO);
			gets(s);
			l = strlen(s);
			if(l)
			{
				info = (char*)malloc(sizeof(char)*(l+1));
				strcpy(info,s);
				G.arcs[i][j].info = info;
			}
		}
	}
	G.kind = AG;
}

void InsertVex(MGraph &G,VertexType v)
{
    int i;
    strcpy(G.vexs[G.vexnum],v);
    for(i=0;i<=G.vexnum;i++)
    {
        if(G.kind%2)    //��
        {
            G.arcs[G.vexnum][i].adj = INFINITY;
            G.arcs[i][G.vexnum].adj = INFINITY;
        }
        else
        {
            G.arcs[G.vexnum][i].adj = 0;
            G.arcs[i][G.vexnum].adj = 0;
        }
        G.arcs[G.vexnum][i].info = NULL;
        G.arcs[i][G.vexnum].info = NULL;
    }
    G.vexnum++;
}

void InsertArc(MGraph &G,VertexType v1,VertexType v2)
{
    int i,j,l;
    char *info,s[MAX_INFO];
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    if(i<0||j<0)
        exit(-1);
    G.arcnum++;
    if(G.kind%2)
    {
        printf("������˻���ߵ�Ȩֵ:");
        scanf("%d",G.arcs[i][j].adj);
    }
    else
        G.arcs[i][j].adj = 1;
    printf("�Ƿ��иû���ߵ������Ϣ(0:�� 1:��):");
    scanf("%d%*c",&i);
    if(i)
    {
        printf("������û���ߵ������Ϣ(%d���ַ�):",MAX_INFO);
        gets(s);
        l = strlen(s);
        if(l)
        {
            info = (char*)malloc(sizeof(char)*(l+1));
            strcpy(info,s);
            G.arcs[i][j].info = info;
        }
    }
    if(G.kind>1)    //����
    {
        G.arcs[i][j].adj = G.arcs[i][j].adj;
        G.arcs[i][j].info = G.arcs[i][j].info;      //ָ��ͬһ�������Ϣ
    }
}

void Deletevex(MGraph& G,VertexType v1)
{
    int i,j;
    j = LocateVex(G,v1);
    if(G.kind%2)
    {
        for(i=0;i<G.vexnum;i++)
        {
            if(G.arcs[j][i].adj != INFINITY)
            {
                G.arcnum--;
                G.arcs[j][i].adj = INFINITY;
                free(G.arcs[j][i].info);
                G.arcs[j][i].info = NULL;
            }
            if(G.kind>1)
            {
                G.arcs[i][j].adj = INFINITY;
                free(G.arcs[j][i].info);
                G.arcs[j][i].info = NULL;
            }
            else
            {
                if(G.arcs[i][j].adj != INFINITY)
                {
                    G.arcnum--;
                    G.arcs[i][j].adj = INFINITY;
                    free(G.arcs[i][j].info);
                    G.arcs[i][j].info = NULL;
                }
            }
        }
    }
    else
    {
        for(i=0;i<G.vexnum;i++)
        {
            if(G.arcs[j][i].adj == 1)
            {
                G.arcnum--;
                G.arcs[j][i].adj = 0;
                G.arcs[j][i].info = NULL;
            }
            if(G.kind>1)
            {
                G.arcs[i][j].adj = 0;
                G.arcs[j][i].info = NULL;
             }
            else
            {
                if(G.arcs[i][j].adj == 1)
                {
                    G.arcnum--;
                    G.arcs[i][j].adj = 0;
                    G.arcs[i][j].info = 0;
                }
            }
        }
    }
    G.vexnum--;
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