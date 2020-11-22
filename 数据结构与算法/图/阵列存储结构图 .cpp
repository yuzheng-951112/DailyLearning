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
enum GraphKind{DG,DN,AG,AN};        //{有向图，有向网，无向图，无向网}对应{0,1,2,3}
/*
二者的区别：
　　邻接矩阵（Adjacency Matrix）：是表示顶点之间相邻关系的矩阵。设G=(V,E)是一个图，其中V={v1,v2,…,vn}。
    G的邻接矩阵是一个具有下列性质的n阶方阵：
　　①对无向图而言，邻接矩阵一定是对称的，而且主对角线一定为零（在此仅讨论无向简单图），副对角线不一定为0，
    有向图则不一定如此。
　　②在无向图中，任一顶点i的度为第i列所有元素的和，在有向图中顶点i的出度为第i行所有元素的和，而入度为第i列所有元素的和。
　　③用邻接矩阵法表示图共需要n^2个空间，由于无向图的邻接矩阵一定具有对称关系，所以扣除对角线为零外，
    仅需要存储上三角形或下三角形的数据即可，因此仅需要n（n-1）/2个空间。 
*/

typedef int BOOL;
BOOL visited[MAX_VERTEX_NUM];
typedef int VRType;
typedef char VertexType[MAX_VERTEX_NUM];
typedef char InfoType; 

typedef struct
{
    VRType adj;     //顶点关系类型。对无权图，用1(是)或0(否)表示相邻否；
                    //对带权图，则为权值类型；
    InfoType *info; //该弧相关信息的指针
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    AdjMatrix arcs;                     //邻接矩阵
    int vexnum,arcnum;                  //图的当权顶点数和弧数
    GraphKind kind;                     //图的种类标志
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
void CreateDG(MGraph &); //构造有向图

void CreateDN(MGraph &); //构造有向网
void CreateAG(MGraph &); //构造无向图
void CreateAN(MGraph &); //构造无向网

void InsertVex(MGraph&,VertexType);             //插入新的顶点
void InsertArc(MGraph&,VertexType,VertexType);  //输入网或图的方向
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
    printf("修改顶点的值，请输入原值 新值:");
    scanf("%s%s",v1,v2);
    PutVex(g,v1,v2);
    printf("深度优先搜索的结果(非递归):\n");
    DFSTraverse(g);
    printf("\n深度优先搜索的结果(递归):\n");
    DFSTraverse1(g);
    printf("\n广度优先搜索的结果\n");
    BFSTraverse(g);
    printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头:");
    scanf("%s%s",v1,v2);
    DeleteArc(g,v1,v2);
    Display(g);
    DestroyGraph(g);
    printf("请按顺序选择有向图，有向网，无向图，无向网\n");
    for(i=0;i<4;i++)
    {
        CreateGraph(g);
        Display(g);
        printf("插入新顶点，请输入顶点的值:");
        scanf("%s",v1);
        InsertVex(g,v1);
        printf("插入与新顶点有关的弧或边，请输入弧或边数:");
        scanf("%d",&n);
        for(k=0;k<n;k++)
        {
            printf("请另一顶点的值:");
            scanf("%s",v2);
            if(g.kind<=1)
            {
                printf("对于有向图或网，请输入另一点的方向(0:弧头 1:弧尾):");
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
        printf("删除顶点及相关的弧或边，请输入顶点的值:");
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
    printf("请输入数据文件名(f7-1.dat):");
  //  scanf("%s",filename);
    if((graphlist = fopen("D:\\VC++6.0\\VC++6.0\\MyProjects\\数据结构\\图\\图的数组存储表示\\f7-1.txt","a+"))!=NULL)
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
            fscanf(graphlist,"%s%s",va,vb);             //空格隔开va和vb
            i = LocateVex(G,va);
            j = LocateVex(G,vb);
            G.arcs[i][j].adj = G.arcs[j][i].adj = 1;    //无向图
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
        case DG:strcpy(s,"有向图\0");
                strcpy(s1,"弧\0");
                break;
        case DN:strcpy(s,"有向网\0");
				strcpy(s1,"弧\0");
				break;
		case AG:strcpy(s,"无向图\0");
				strcpy(s1,"边界\0");
				break;
		case AN:strcpy(s,"无向网\0");
				strcpy(s1,"边\0");     
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
运行输出123456789
       56789
这里涉及到内存覆盖问题d,s内存段为strcpy()运行前为d 123\000,s 123456789\000
运行strcpy()后d 1234,s 56789\000
这里最好的办法是分配动态内存
char *s=(char*)malloc(7*sizeof(char)),
	 *s1=(char*)malloc(3*sizeof(char));
*/
    printf("\n%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);
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
    printf("G.arcs.info:\n");       //输出G.arcs.info
    printf("顶点1(弧尾) 顶点2(弧头) 该%s信息:\n",s1);
    if(G.kind<2)					//有向图
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
    else								//无向图
    {
        for(i=0;i<G.vexnum;i++)
        {
            for(j=i+1;j<G.vexnum;j++)	//无向图j=i+1可以减少遍历重复项
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
    for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,G.vexs[w])))     //这里的返回值是地址地址 VertexType是char型数组 首地址也是地址
    {
/*
w=FirstAdjVex(G,v1)是找到对应的第一个adj==1的情况
w=NextAdjVex(G,v1,strcpy(w1,GetVex(G,w)))是找到这一行下一个对应adj==1的情况 这里的v1对应的是行，strcpy(w1,GetVex(G,w))对应的是列
*/
        if(!visited[w])
            DFS1(G,w);
    }
}
/*
strcpy()函数
char * __cdecl strcpy(char * dst, const char * src)
{
        char * cp = dst;
        while( *cp++ = *src++ )
                ;               // Copy src over dst 
        return( dst );
} 
返回值是复制字符串的地址
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

int FirstAdjVex(MGraph G,VertexType v)  //用来找下一个顶点的首个adj==1的量
{
    int i,j=0,k;
    k = LocateVex(G,v);
    if(G.kind==DN || G.kind==AN)        //网
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
    k1 = LocateVex(G,v1);       //k1为顶点所在位置  对应行
    k2 = LocateVex(G,w);        //k2为顶点所在位置  对应列
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
    i = LocateVex(G,v1);     //尾
    j = LocateVex(G,v2);     //头
    if(i<0||j<0)
        exit(-1);
    if(G.kind%2==0)
        G.arcs[i][j].adj = 0;
    else
        G.arcs[i][j].adj = INFINITY;
    if(G.arcs[i][j].info)    //有向的是以行为尾巴，列为头
    {
        free(G.arcs[i][j].info);
        G.arcs[i][j].info = NULL;
    }
    if(G.kind>=2)           //无向，删除对称弧
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
                if(G.kind==0&&G.arcs[i][j].adj==1||G.kind==1&&G.arcs[i][j].adj!=INFINITY)   //有向图的弧||有向网的弧
                    if(G.arcs[i][j].info)
                    {
                        free(G.arcs[i][j].info);
                        G.arcs[i][j].info = NULL;
                    }
    else
        for(i=0;i<G.vexnum;i++)
            for(j=i+1;j<G.vexnum;j++)
            {
                if(G.arcs[i][j].adj==1&&G.kind==2||G.arcs[i][j].adj!=INFINITY&&G.kind==3)       //无向图的边||无向网的边
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
    printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3)");
    scanf("%d",&G.kind);
    switch(G.kind)
    {
        case DG:CreateDG(G); //构造有向图
			 break;
        case DN:CreateDN(G); //构造有向网
			 break;
		case AG:CreateAG(G); //构造无向图
			 break;
        case AN:CreateAN(G); //构造无向网
			 break;
    }
}

void CreateDG(MGraph &G)
{
    int i,j,k,l,IncInfo;
    char s[MAX_INFO],*info;
    VertexType va,vb;
    printf("请输入有向图G的顶点数,弧数,弧是否有其他信息(是:1 否:0):");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("请输入%d个顶点的值(%d个字符):\n",G.vexnum,MAX_NAME);
    for(i=0;i<G.vexnum;i++)
    {
        scanf("%s",G.vexs[i]);
    }
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = 0;       //图
            G.arcs[i][j].info = NULL;
        }
    }
    printf("请输入%d条弧的弧尾 弧头(以空格作为间隔):\n",G.arcnum);
    for(k=0;k<G.arcnum;k++)
    {
        scanf("%s%s%*c",va,vb);
        i = LocateVex(G,va);
        j = LocateVex(G,vb);
        G.arcs[i][j].adj = 1;
        if(IncInfo)
        {
            printf("请输入该弧的相关信息(%d个字符):",MAX_INFO);
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
	printf("请输入无向图G的顶点,边数,边是否含其他信息(是:1,否:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("请输入%d个顶点的值(%d个字符):\n",G.vexnum,MAX_NAME);
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
	printf("请输入%d条弧的弧尾 弧头(以空格作为间隔):\n",G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%s%s%*c",va,vb);
		i = LocateVex(G,va);
        j = LocateVex(G,vb);
		G.arcs[i][j].adj = 1;
		G.arcs[j][i].adj = 1;
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(%d个字符):",MAX_INFO);
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
	printf("请输入无向图G的顶点,边数,边是否含其他信息(是:1,否:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("请输入%d个顶点的值(%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vexs[i]);
	}
	for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = INFINITY;       //网	
            G.arcs[i][j].info = NULL;
        }
    }
	printf("请输入%d条弧的弧尾 弧头(以空格作为间隔):\n",G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%s%s%d%*c",va,vb,&w);
		i = LocateVex(G,va);
        j = LocateVex(G,vb);
		G.arcs[i][j].adj = w;
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(%d个字符):",MAX_INFO);
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
	printf("请输入无向图G的顶点,边数,边是否含其他信息(是:1,否:0)");
	scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
	printf("请输入%d个顶点的值(%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%s",G.vexs[i]);
	}
	for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = INFINITY;       //网	
            G.arcs[i][j].info = NULL;
        }
    }
	printf("请输入%d条弧的弧尾 弧头(以空格作为间隔):\n",G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		scanf("%s%s%d%*c",va,vb,&w);
		i = LocateVex(G,va);
        j = LocateVex(G,vb);
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = w;
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(%d个字符):",MAX_INFO);
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
        if(G.kind%2)    //网
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
        printf("请输入此弧或边的权值:");
        scanf("%d",G.arcs[i][j].adj);
    }
    else
        G.arcs[i][j].adj = 1;
    printf("是否有该弧或边的相关信息(0:无 1:有):");
    scanf("%d%*c",&i);
    if(i)
    {
        printf("请输入该弧或边的相关信息(%d个字符):",MAX_INFO);
        gets(s);
        l = strlen(s);
        if(l)
        {
            info = (char*)malloc(sizeof(char)*(l+1));
            strcpy(info,s);
            G.arcs[i][j].info = info;
        }
    }
    if(G.kind>1)    //无向
    {
        G.arcs[i][j].adj = G.arcs[i][j].adj;
        G.arcs[i][j].info = G.arcs[i][j].info;      //指向同一个相关信息
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