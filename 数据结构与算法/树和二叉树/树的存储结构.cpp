#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_TREE_SIZE 100
#define QUEUE_SIZE 50

typedef struct PTNode
{
	char data;
	int parent;
}*pPTNode;

typedef struct PTree#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_TREE_SIZE 100
#define QUEUE_SIZE 50

typedef struct PTNode
{
	char data;
	int parent;
}*pPTNode;

typedef struct PTree
{
	PTNode nodes[MAX_TREE_SIZE];
	int n;							//节点数
}*pPTree;

typedef struct Queue
{
	PTNode *Base;
	int front;
	int rear;
}Queue,*qQueue;

void InitTree(pPTree);
bool TreeEmpty(pPTree);
char Root(pPTree);
int TreeDepth(pPTree);
void CreatrTree(pPTree);
void TraverseTree(pPTree);
void Assign(pPTree,char,char);
char Parent(pPTree,char);
char LeftChild(pPTree,char);
char RightSibling(pPTree,char);
void InsertChild(pPTree,char,int,pPTree);
void Print(pPTree);
void DeleteChild(pPTree,char,int);

void init_Queue(qQueue,int);
void en_Queue(qQueue,pPTNode);
void de_Queue(qQueue,pPTNode);
bool EmptyQueue(qQueue);

int main()
{
	int i;
	char e1,e2;
	PTree T,H;
	InitTree(&T);
	printf("建立空树后,树空否?%d(1:是 0:否) 树的根为%c 树的深度为%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	CreatrTree(&T);
	printf("建立树T后,树空否?%d(1:是 0:否) 树的根为%c 树的深度为%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	printf("层遍历树T\n");
	TraverseTree(&T);
	printf("\n请输入待修改的节点的值 新值:");
	scanf("%c%*c%c%*c",&e1,&e2);
	Assign(&T,e1,e2);
	printf("\n层遍历修改后的树T\n");
	TraverseTree(&T);
	printf("\n%c的双亲是%c,长子是%c,下一个兄弟是%c\n",e2,Parent(&T,e2),LeftChild(&T,e2),RightSibling(&T,e2));
	printf("建立树H\n");
	InitTree(&H);
	CreatrTree(&H);
	printf("层遍历树T\n");
	TraverseTree(&H);
	printf("将树H插到树H中,请输入T中的双亲节点 子树序号:");
	scanf("%c%d%*c",&e1,&i);
	InsertChild(&T,e1,i,&H);
	Print(&T);
	printf("删除树T中节点e的第i棵子树，请输入e i:");
	scanf("%c%d%*c",&e1,&i);
	DeleteChild(&T,e1,i);
	Print(&T);
	scanf("%c%d%*c",&e1,&i);
	return 0;
}

void InitTree(pPTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
	{
		T->nodes[i].data = 0;
		T->nodes[i].parent = 0;
		T->n = 0;
	}
}

bool TreeEmpty(pPTree T)
{
	if(T->n==0)
		return true;
	else
		return false;
}

char Root(pPTree T)
{
	if(T->n!=0)
		return T->nodes[0].data;
	else
		return '*';
}

int TreeDepth(pPTree T)
{
	int i=1,j=T->nodes[T->n-1].parent;
	if(T->n==0)
		return 0;
	else
	{
		while(j!=-1)
		{
			j = T->nodes[j].parent;
			i++;
		}
		return i;
	}
}

void CreatrTree(pPTree T)
{
	Queue q;
	PTNode p,qq;
	int i=1,j,l;
	char c[MAX_TREE_SIZE];				//临时存放孩子节点
	init_Queue(&q,QUEUE_SIZE);
	printf("请输入根节点('*'为空):");
	scanf("%c%*c",&T->nodes[0].data);	//根节点序号为0
	if(T->nodes[0].data!='*')
	{
		T->nodes[0].parent = -1;		//根节点无双亲
		qq.data = T->nodes[0].data;
		qq.parent = 0;
		en_Queue(&q,&qq);
		while(i<MAX_TREE_SIZE && !EmptyQueue(&q))
		{
			de_Queue(&q,&qq);				//出队一个节点
			printf("请按长幼顺序输入节点%c的所有孩子:",qq.data);
			gets(c);
			l = strlen(c);
			for(j=0;j<l;j++)
			{
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.parent;
				p.data = c[j];
				p.parent = i;
				en_Queue(&q,&p);
				i++;
			}
		}
		if(i>MAX_TREE_SIZE)
		{
			printf("节点数超过数组容量\n");
			exit(-1);
		}
		T->n = i;
	}
	else
		T->n = 0;
}

void TraverseTree(pPTree T)
{
	for(int i=0;i<T->n;i++)
	{
		printf("->%c",T->nodes[i].data);
	}
}

void Assign(pPTree T,char e1,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e1;i++);
	T->nodes[i].data = e2;
}

char Parent(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2;i++);
	return T->nodes[T->nodes[i].parent].data;
}

char LeftChild(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[T->nodes[i].parent].data!=e2 && i<T->n;i++);
	if(i<T->n)
		return T->nodes[i].data;
	else
		return '*';
}

char RightSibling(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2 && i<T->n;i++);
	if(i!=T->n && T->nodes[i+1].parent == T->nodes[i].parent)
		return T->nodes[i+1].data;
	else
		return '*';
}

void InsertChild(pPTree T,char e1,int pos,pPTree H)						//pos代表插入的位子
{
	int j,l,k,f=1,n=0;
	PTNode t;
	if(!TreeEmpty(T))
	{
			for(j=0;T->nodes[j].data!=e1 && j<T->n;j++);
		l = j + 1;				//如果c是p的第一棵树，则插入在
		if(pos>1)
		{
			for(k=j+1;k<T->n;k++)
				if(T->nodes[k].parent == j)
				{
					n++;		//孩子数加1
					if(n == pos-1)	//找到e1的第pos-1个孩子，其序号为k
						break;
				}
			l = k + 1;
		}//e1的序号为j，H插在l处
		if(l<T->n)
			for(k=T->n-1;k>=l;k--)
			{
				T->nodes[k+H->n] = T->nodes[k];			//依次将序号l以后的节点向后移动H->n个位置
				if(T->nodes[k].parent>=l)
					T->nodes[k+H->n].parent +=H->n;		//依次将序号l以后的节点的父节点向后移动H->n个为位置
			}
		for(k=0;k<H->n;k++)
		{
			T->nodes[l+k].data = H->nodes[k].data;		//依次将H中的数据插入到T中l以后的位置
			T->nodes[l+k].parent = H->nodes[k].parent+l;//依次将H中的父节点位置插入到T中以后的位置(这里+l是新父节点的位置)
		}
		T->nodes[l].parent = j;
		T->n += H->n;
		while(f)				//从插入点之后，将节点仍按层排序
		{		
			f = 0;
			for(j=1;j<T->n-1;j++)
			{
				if(T->nodes[j].parent>T->nodes[j+1].parent)		//比较双亲结点位置大小
				{
					t = T->nodes[j];
					T->nodes[j] = T->nodes[j+1];
					T->nodes[j+1] = t;
					f = 1;
					for(k=j;k<T->n;k++)							//在儿子树位置调整后，同时调整孙子树中父节点位置
						if(T->nodes[k].parent == j)
							T->nodes[k].parent++;
						else if(T->nodes[k].parent == j+1)
							T->nodes[k].parent--;
				}
			}
		}
	}
	else
	{
		printf("树为空!\n");
		exit(-1);
	}
	
}

void DeleteChild(pPTree T,char e1,int pos)
{
	int i,j,k;
	Queue q;
	PTNode p;
	init_Queue(&q,QUEUE_SIZE);
	for(i=0;T->nodes[T->nodes[i].parent].data!=e1 && i<T->n;i++);
	if(i!=T->n)
	{
		en_Queue(&q,&T->nodes[i+pos-1]);
		T->nodes[i+pos-1].parent = T->n;
	}
	while(!EmptyQueue(&q)&&i<T->n)
	{
		de_Queue(&q,&p);
		for(j=i;j<T->n;j++)
		{
			if(T->nodes[T->nodes[j].parent].data == p.data)
			{
				en_Queue(&q,&T->nodes[j]);
				T->nodes[j].parent = T->n;
			}
		}
		i = j;
	}
	for(i=0;i<T->n;i++)
	{
		for(j=0;j<=i;j++)
		{
			if(T->nodes[j].parent>T->nodes[j+1].parent)
			{
				p = T->nodes[j];
				T->nodes[j] = T->nodes[j+1];
				T->nodes[j+1] = p;
				for(k=j;k<T->n;k++)							//在儿子树位置调整后，同时调整孙子树中父节点位置
					if(T->nodes[k].parent == j)
						T->nodes[k].parent++;
					else if(T->nodes[k].parent == j+1)
						T->nodes[k].parent--;
			}
		}
	}
	T->n -= q.rear;
}

void Print(pPTree T)
{
	printf("***节点***双亲***\n");
	printf("***%c*** ***\n",T->nodes[0].data);
	for(int i=1;i<T->n;i++)
	{
		printf("***%c***%c***\n",T->nodes[i].data,T->nodes[T->nodes[i].parent].data);
	}
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pPTNode)malloc((length+1)*sizeof(PTNode));
	if(Q->Base == NULL)
	{
		printf("空间分配失败!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,pPTNode T)
{
	Q->Base[Q->rear] = *T;
	Q->rear++;
}

void de_Queue(qQueue Q,pPTNode T)
{
	*T = Q->Base[Q->front];
	Q->front++;
}

bool EmptyQueue(qQueue Q)
{
	if(Q->rear == Q->front)
		return true;
	else
		return false;
}


{
	PTNode nodes[MAX_TREE_SIZE];
	int n;							//节点数
}*pPTree;

typedef struct Queue
{
	PTNode *Base;
	int front;
	int rear;
}Queue,*qQueue;

void InitTree(pPTree);
bool TreeEmpty(pPTree);
char Root(pPTree);
int TreeDepth(pPTree);
void CreatrTree(pPTree);
void TraverseTree(pPTree);
void Assign(pPTree,char,char);
char Parent(pPTree,char);
char LeftChild(pPTree,char);
char RightSibling(pPTree,char);
void InsertChild(pPTree,char,int,pPTree);

void init_Queue(qQueue,int);
void en_Queue(qQueue,pPTNode);
void de_Queue(qQueue,pPTNode);
bool EmptyQueue(qQueue);

void main()
{
	int i;
	char e1,e2;
	PTree T,H;
	InitTree(&T);
	printf("建立空树后,树空否?%d(1:是 0:否) 树的根为%c 树的深度为%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	CreatrTree(&T);
	printf("建立树T后,树空否?%d(1:是 0:否) 树的根为%c 树的深度为%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	printf("层遍历树T\n");
	TraverseTree(&T);
	printf("\n请输入待修改的节点的值 新值:");
	scanf("%c%*c%c%*c",&e1,&e2);
	Assign(&T,e1,e2);
	printf("\n层遍历修改后的树T\n");
	TraverseTree(&T);
	printf("\n%c的双亲是%c,长子是%c,下一个兄弟是%c\n",e2,Parent(&T,e2),LeftChild(&T,e2),RightSibling(&T,e2));
	printf("建立树H\n");
	InitTree(&H);
	CreatrTree(&H);
	printf("层遍历树T\n");
	TraverseTree(&T);
	printf("将树H插到树H中,请输入T中的双亲节点 子树序号:");
	scanf("%c%d%*c",&e,&i);
	InsertChild(T,e,i,H);
	Print(T);

}

void InitTree(pPTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
	{
		T->nodes[i].data = 0;
		T->nodes[i].parent = 0;
		T->n = 0;
	}
}

bool TreeEmpty(pPTree T)
{
	if(T->n==0)
		return true;
	else
		return false;
}

char Root(pPTree T)
{
	if(T->n!=0)
		return T->nodes[0].data;
	else
		return '*';
}

int TreeDepth(pPTree T)
{
	int i=1,j=T->nodes[T->n-1].parent;
	if(T->n==0)
		return 0;
	else
	{
		while(j!=-1)
		{
			j = T->nodes[j].parent;
			i++;
		}
		return i;
	}
}

void CreatrTree(pPTree T)
{
	Queue q;
	PTNode p,qq;
	int i=1,j,l;
	char c[MAX_TREE_SIZE];					//临时存放孩子节点
	init_Queue(&q,QUEUE_SIZE);
	printf("请输入根节点('*'为空):");
	scanf("%c%*c",&T->nodes[0].data);		//根节点序号为0
	if(T->nodes[0].data!='*')
	{
		T->nodes[0].parent = -1;			//根节点无双亲
		qq.data = T->nodes[0].data;
		qq.parent = 0;
		en_Queue(&q,&qq);
		while(i<MAX_TREE_SIZE && !EmptyQueue(&q))
		{
			de_Queue(&q,&qq);				//出队一个节点
			printf("请按长幼顺序输入节点%c的所有孩子:",qq.data);
			gets(c);
			l = strlen(c);
			for(j=0;j<l;j++)
			{
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.parent;
				p.data = c[j];
				p.parent = i;
				en_Queue(&q,&p);
				i++;
			}
		}
		if(i>MAX_TREE_SIZE)
		{
			printf("节点数超过数组容量\n");
			exit(-1);
		}
		T->n = i;
	}
	else
		T->n = 0;
}

void TraverseTree(pPTree T)
{
	for(int i=0;i<T->n;i++)
	{
		printf("->%c",T->nodes[i].data);
	}
}

void Assign(pPTree T,char e1,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e1;i++);
	T->nodes[i].data = e2;
}

char Parent(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2;i++);
	return T->nodes[T->nodes[i].parent].data;
}

char LeftChild(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[T->nodes[i].parent].data!=e2 && i<T->n;i++);
	if(i<T->n)
		return T->nodes[i].data;
	else
		return '*';
}

char RightSibling(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2 && i<T->n;i++);
	if(i!=T->n && T->nodes[i+1].parent == T->nodes[i].parent)
		return T->nodes[i+1].data;
	else
		return '*';
}

void InsertChild(pPTree T,char e1,int pos,pPTree H)				//pos代表插入的位子
{
	int i,j=-1,k;												//i为树T每层最左边的子树(带有根节点),j存放上一层首个父节点位置(j初始化为-1代表根节点)
	while()
	{
		for(i=0;T->nodes[T->nodes[i].parent].data!=e1;i++);		//找到树T中父节点是e1的最左边的子树
		for();		//是H中每层要插入T中的个数
		for(k=T->n-1;k>i+pos-1;k--)
			T->nodes[k+]
	}
	
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pPTNode)malloc((length+1)*sizeof(PTNode));
	if(Q->Base == NULL)
	{
		printf("空间分配失败!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,pPTNode T)
{
	Q->Base[Q->rear] = *T;
	Q->rear++;
}

void de_Queue(qQueue Q,pPTNode T)
{
	*T = Q->Base[Q->front];
	Q->front++;
}

bool EmptyQueue(qQueue Q)
{
	if(Q->rear == Q->front)
		return true;
	else
		return false;
}

