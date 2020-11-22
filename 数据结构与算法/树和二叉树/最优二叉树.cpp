#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct CSNodn
{
    char data;
    CSNodn *firstchild,*nextsibling;
}CSNodn,*CSTree;

typedef struct QNode
{
	CSTree QNodedata;
	struct QNode *pNext;
}QNode,*qQNode;

typedef struct Queue
{
	qQNode front;
	qQNode rear;
}Queue,*qQueue;

void InitTree(CSTree &);
bool TreeEmpty(CSTree);
char Root(CSTree);
int TreeDepth(CSTree);
void CreateTree(CSTree &);
void PreOrderTraverse(CSTree);
CSTree Point(CSTree,char);
void Assign(char,CSTree);
void PostOrderTraverse(CSTree);
char Parent(CSTree,char);
char LeftChild(CSTree,char);
char RightSibling(CSTree,char);
void LevelOrderTraverse(CSTree);
void InsertChild(CSTree,CSTree,int,CSTree);
void DeleteChild(CSTree,CSTree,int);
void DestroyTree(CSTree);

void init_QU(qQueue);
void enQU(qQueue,CSTree);
void deQU(qQueue QU,CSTree &);
bool empty(qQueue);

int main()
{
    int i;
    CSTree T,S,p;
    char e,e1;
    InitTree(T);
    printf("构造空树后，树空否？%d(1:是 0:否) 树根为%c 树的深度为%d\n",TreeEmpty(T),Root(T),TreeDepth(T));
    CreateTree(T);
	printf("构造树T后，树空否？%d(1:是 0:否) 树根为%c 树的深度为%d\n",TreeEmpty(T),Root(T),TreeDepth(T));
	printf("先根遍历树T:\n");
	PreOrderTraverse(T);
	printf("请输入待修改的节点的值 新值:");
	scanf("%c%*c%c%*c",&e,&e1);
	p = Point(T,e);
	Assign(e1,p);
	printf("先根遍历树T:\n");
	PreOrderTraverse(T);
	printf("\n后根遍历树T:\n");
	PostOrderTraverse(T);
	printf("\n%c的双亲是%c,长子是%c,下一个兄弟是%c",e1,Parent(T,e1),LeftChild(T,e1),RightSibling(T,e1));
	printf("\n建立树S:\n");
	InitTree(S);
	CreateTree(S);
	printf("层序遍历树S:\n");
	LevelOrderTraverse(S);
	printf("\n将树S插到树T中，请输入T中S的双亲节点 子树序号:");
	scanf("%c%*c%d",&e,&i);
	p = Point(T,e);
	InsertChild(T,p,i,S);
	printf("层序遍历树T:\n");
	LevelOrderTraverse(T);
	printf("\n删除树T中节点e的第i棵子树，请输入e i:");
	fflush(stdin);
	scanf("%c%d",&e,&i);
	p = Point(T,e);
	DeleteChild(T,p,i);
	printf("层序遍历树T:\n");
	LevelOrderTraverse(T);
	DestroyTree(T);
	scanf("%d",&i);
    return 0;
}

void InitTree(CSTree &T)
{
    T = NULL;
}

bool TreeEmpty(CSTree T)
{
    if(T==NULL)
        return true;
    else
        return false;    
}

char Root(CSTree T)
{
    if(!TreeEmpty(T))
        return T->data;
    else
        return '*';
}

int TreeDepth(CSTree T)
{
	int j;
	CSTree p1;
    if(TreeEmpty(T))
		return 0;
	else
	{
		j=TreeDepth(T->firstchild);
		p1 = T->nextsibling;
		while(p1)
		{
			if(TreeDepth(p1->firstchild)>j)
				j =  TreeDepth(p1->firstchild);
			p1 = p1->nextsibling;
		}
		return j+1;
	}
	
}

void CreateTree(CSTree &T)
{
	int i,l;
    char e,e1[20];
    CSTree p,p1;
    Queue q;
    init_QU(&q);
    printf("请输入根节点:");
    scanf("%c%*c",&e);
    if(!(T=(CSTree)malloc(sizeof(CSNodn))))
        exit(-1);
    T->data = e;
	T->nextsibling = NULL;
    enQU(&q,T);
    while(!empty(&q))
    {
        deQU(&q,p);
		printf("请按长幼顺序输入节点%c的所有孩子:",p->data);
		gets(e1);
		if((l=strlen(e1))>0)
		{
			if(!(p->firstchild = (CSTree)malloc(sizeof(CSNodn))))
			exit(-1);
			p1 = p->firstchild;
			p1->data = e1[0];
			enQU(&q,p1);
			for(i=1;i<l;i++)
			{
				if(!(p1->nextsibling=(CSTree)malloc(sizeof(CSNodn))))
        			exit(-1);
				p1 = p1->nextsibling;
				p1->data = e1[i];
				enQU(&q,p1);
			}
			p1->nextsibling = NULL;
		}
		else
			p->firstchild = NULL;
	}
}

void PreOrderTraverse(CSTree T)
{
	printf("%c ",T->data);
	if(T->firstchild)
		PreOrderTraverse(T->firstchild);
	if(T->nextsibling)
		PreOrderTraverse(T->nextsibling);
}

void PostOrderTraverse(CSTree T)
{
	if(T->firstchild)
		PostOrderTraverse(T->firstchild);
	printf("%c ",T->data);
	if(T->nextsibling)
		PostOrderTraverse(T->nextsibling);
}

void LevelOrderTraverse(CSTree T)
{
	int i=1;
    CSTree p,p1;
    Queue q;
    init_QU(&q);
	printf("S第%d层为:%c",i,T->data);
	i++;
	enQU(&q,T);
	while(!empty(&q))
	{
		deQU(&q,p);
		if((p1=p->firstchild)!=NULL)
		{
			printf("\nS第%d层为:",i);
			i++;
			while(p1)
			{
				printf("%c ",p1->data);
				enQU(&q,p1);
				p1 = p1->nextsibling;
			}
		}
	}
}

CSTree Point(CSTree T,char e)
{
	if(T->data==e)
		return T;
	else
	{
		if(T->firstchild)
			if(Point(T->firstchild,e)!=NULL)
				return Point(T->firstchild,e);
		if(T->nextsibling)
			if(Point(T->nextsibling,e))
				return Point(T->nextsibling,e);
	}
	return NULL;
}

void Assign(char e,CSTree p)
{
	p->data = e;
}

char Parent(CSTree T,char e)
{
	int i,j=1;
    CSTree p,p1;
	if(T->data==e)
		return '*';
    Queue q;
    init_QU(&q);
	enQU(&q,T);
	while(!empty(&q)&&j==1)
	{
		deQU(&q,p);
		if(p->firstchild)
		{
			p1 = p->firstchild;
			enQU(&q,p1);
			while(p1)
			{
				if(p1->data==e)
				{
					j=0;
					break;
				}
				p1 = p1->nextsibling;
				if(p1)
					enQU(&q,p1);
			}
		}
	}
	return p->data;
}

char LeftChild(CSTree T,char e)
{
	if(Point(T,e))
		if(Point(T,e)->firstchild!=NULL)
			return Point(T,e)->firstchild->data;
		else
			return '*';
	else
		return '*';
}

char RightSibling(CSTree T,char e)
{
	if(Point(T,e))
		if(Point(T,e)->nextsibling!=NULL)
			return Point(T,e)->nextsibling->data;
		else
			return '*';
	else
		return '*';
}

void InsertChild(CSTree T,CSTree p,int i,CSTree S)
{
	int j;
	CSTree q,q1;
	if(T)
	{
		if(i==1)
		{
			q = p->firstchild;
			p->firstchild = S;
			S->nextsibling = q;
		}
		else
		{
			q = p->firstchild;
			for(j=1;j<i-1;j++)
			{
				q = q->nextsibling;
			}
			q1 = q->nextsibling;
			q->nextsibling = S;
			S->nextsibling = q1;
		}
	}
	else
		exit(-1);	
}

void DeleteChild(CSTree T,CSTree p,int i)
{
	int j;
	CSTree q,q1;
	if(T)
	{
		if(i==1)
		{
			q = p->firstchild->nextsibling;
			p->firstchild = q;
		}
		else
		{
			q = p->firstchild;
			for(j=1;j<i-1;j++)
			{
				q = q->nextsibling;
			}
			q1 = q->nextsibling->nextsibling;
		    q->nextsibling = q1;
		}
	}
	else
		exit(-1);
}

void DestroyTree(CSTree T)
{
	if(T)
	{
		if(T->firstchild)
			DestroyTree(T->firstchild);
		if(T->nextsibling)
			DestroyTree(T->nextsibling);
		free(T);
		T = NULL;
	}
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
	
void enQU(qQueue QU,CSTree T)
{
	qQNode pNew = (qQNode)malloc(sizeof(QNode));
	if(pNew == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	pNew->QNodedata = T;
	QU->rear->pNext = pNew;
	QU->rear = pNew;
	pNew->pNext = NULL;
}

void deQU(qQueue QU,CSTree &T)
{
	qQNode q = QU->front->pNext;
	if(empty(QU))
		exit(-1);
	QU->front->pNext = q->pNext;
	T = q->QNodedata;
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
