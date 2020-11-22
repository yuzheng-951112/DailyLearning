#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define QUEUEMAX 30

typedef struct BiTPNode
{
	char data;
	BiTPNode *parent,*lchild,*rchild;
}BiTPNode,*pBiTPNode;

typedef struct Queue
{
	BiTPNode *Base;
	int front;
	int rear;
}Queue,*qQueue;

void InitBitree(pBiTPNode &);
int BiTreeEmpty(pBiTPNode);
int BitreeDepth(pBiTPNode);
char Root(pBiTPNode);
//void Create(pBiTPNode &);
//void CreateBiTree(pBiTPNode &);
void CreateBiTree(pBiTPNode &,pBiTPNode);
void PreOrderTraverse(pBiTPNode);
void InOrderTraversel(pBiTPNode);
void PostOrderTraverse(pBiTPNode);
void Print(pBiTPNode);
void LevelOrderTraverse1(pBiTPNode);
pBiTPNode Point(pBiTPNode,char);
void InsertChild(pBiTPNode,int,pBiTPNode);
char Value(pBiTPNode);
void Assign(pBiTPNode,char);
char Parent(pBiTPNode,char);
char RightSibling(pBiTPNode,char);
char LeftSibling(pBiTPNode,char);
char RightChild(pBiTPNode,char);
char LeftChild(pBiTPNode,char);
void DeleteChild(pBiTPNode,char);
void DestroyBiTree(pBiTPNode);

void init_Queue(qQueue,int);
void en_Queue(qQueue,pBiTPNode);
void de_Queue(qQueue,pBiTPNode);
bool EmptyQueue(qQueue);

void main()
{
	int i;
	char e1;
	pBiTPNode T,S,p;
	InitBitree(T);
	printf("构造空二叉树后,树空否?%d(1:是 0:否)树的深度=%d\n",BiTreeEmpty(T),BitreeDepth(T));
	if((e1=Root(T))!='*')
		printf("二叉树的根为:%c\n",e1);
	else
		printf("树空,无根\n");
	printf("请先序输入二叉树(如:ab三个'*'表示a为根节点,b为左子树的二叉树):");
	CreateBiTree(T,NULL);
//	CreateBiTree(T,NULL);
	printf("构造空二叉树后,树空否?%d(1:是 0:否)树的深度=%d\n",BiTreeEmpty(T),BitreeDepth(T));
	if((e1=Root(T))!='*')
		printf("二叉树的根为:%c\n",e1);
	else
		printf("树空,无根\n");
	printf("\n中序非递归遍历二叉树:\n");
	InOrderTraversel(T);
	printf("\n后序递归遍历二叉树:\n");
	PostOrderTraverse(T);
	fflush(stdin);
	printf("\n层序遍历二叉树(另一种方法):\n");
	LevelOrderTraverse1(T);
	printf("\n请输入一个节点的值:");
	fflush(stdin);
	scanf("%c%*c",&e1);
	p = Point(T,e1);
	printf("节点的值为%c\n",Value(p));
	printf("欲改变此节点的值,请输入新值:");
	scanf("%c%*c",&e1);
	Assign(p,e1);
	printf("\n层序遍历二叉树(另一种方法):\n");
	LevelOrderTraverse1(T);
	printf("\n%c的双亲是%c",e1,Parent(T,e1));
	printf("\n%c的右兄弟是%c",e1,RightSibling(T,e1));
	printf("\n%c的左兄弟是%c",e1,LeftSibling(T,e1));
	printf("\n%c的右儿子是%c",e1,RightChild(T,e1));
	printf("\n%c的左儿子是%c\n",e1,LeftChild(T,e1));
	printf("构造一个右子树为空的二叉树S:\n");
	printf("请先序输入二叉树(如:ab三个'*'表示a为根节点,b为子树的二叉树):");
	InitBitree(S);
	CreateBiTree(S,NULL);
	printf("先序递归遍历二叉树S:\n");
	PreOrderTraverse(S);
	printf("树S插到树T中,请输入树T中树S的双亲节点 S为左(0)右(1)子树:");
	scanf("%*c%c,%d",&e1,&i);
	p = Point(T,e1);
	InsertChild(p,i,S);
	printf("先序递归遍历二叉树S:\n");
	PreOrderTraverse(T);
	printf("删除子树,请输入待删除子树的双亲节点 左(0)右(1)子树:");
	scanf("%*c%c,%d",&e1,&i);
	p = Point(T,e1);
	DeleteChild(p,i);
	printf("先序递归遍历二叉树S:\n");
	PreOrderTraverse(T);
	DestroyBiTree(T);
}

void InitBitree(pBiTPNode &T)
{
	T = NULL;
}

int BiTreeEmpty(pBiTPNode T)
{
	if(T==NULL)
		return 1;
	else
		return 0;
}

int BitreeDepth(pBiTPNode T)
{
	int i,j;
	if(!T)
		return 0;
	if(T->lchild)
		i = BitreeDepth(T->lchild);
	else
		i = 0;
	if(T->rchild)
		i = BitreeDepth(T->rchild);
	else
		j = 0;
	return i>j?i+1:j+1;
}

char Root(pBiTPNode T)
{
	if(BiTreeEmpty(T))
		return '*';
	else
		return T->data;
}

void CreateBiTree(pBiTPNode &T,pBiTPNode p)
{
	char e;
	scanf("%c",&e);
	if(e!='*')
	{
		if(!(T=(pBiTPNode)malloc(sizeof(BiTPNode))))
			exit(-1);
		else
		{
			T->data = e;
			T->parent = p;
			CreateBiTree(T->lchild,T);
			CreateBiTree(T->rchild,T);
		}
	}
	else
		T = NULL;
}

/*
void CreateBiTree(pBiTPNode &T)
{
	Queue q;
	pBiTPNode p = (pBiTPNode)malloc(sizeof(BiTPNode));
	if(!p)
		exit(-1);
	Create(T);
	if(T)
	{
		T->parent = NULL;	//根节点的双亲为"空"
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);							//这里要将de_Queue传地址 而不是传值 不然程序出错(修改de_Queue)用链队列
			if(p->lchild)
			{
				p->lchild->parent = p;
				en_Queue(&q,p->lchild);
			}
			if(p->rchild)
			{
				p->rchild->parent = p;
				en_Queue(&q,p->rchild);
			}
		}
	}
}

void Create(pBiTPNode &T)
{
	char e;
	scanf("%c",&e);
	if(e!='*')
	{
		if(!(T=(pBiTPNode)malloc(sizeof(BiTPNode))))
			exit(-1);
		else
		{
			T->data = e;
			Create(T->lchild);
			Create(T->rchild);
		}
	}
	else
		T = NULL;
}
*/

void PreOrderTraverse(pBiTPNode T)
{
	Print(T);
	if(T->lchild!=NULL)
		PreOrderTraverse(T->lchild);
	if(T->rchild!=NULL)
		PreOrderTraverse(T->rchild);
}

void InOrderTraversel(pBiTPNode T)
{
	if(T->lchild!=NULL)
		InOrderTraversel(T->lchild);
	Print(T);
	if(T->rchild!=NULL)
		InOrderTraversel(T->rchild);
}

void PostOrderTraverse(pBiTPNode T)
{
	if(T->lchild!=NULL)
		PostOrderTraverse(T->lchild);
	if(T->rchild!=NULL)
		PostOrderTraverse(T->rchild);
	Print(T);
}

void LevelOrderTraverse1(pBiTPNode T)
{
	Queue q;
	pBiTPNode a = (pBiTPNode)malloc(sizeof(BiTPNode));
	if(T)
	{
		printf("%c是根节点\n",T->data);
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,a);
			if(a->lchild!=NULL)
			{
				printf("%c是%c的左孩子\n",a->lchild->data,a->data);
				en_Queue(&q,a->lchild);
			}
			if(a->rchild!=NULL)
			{
				printf("%c是%c的左孩子\n",a->rchild->data,a->data);
				en_Queue(&q,a->rchild);
			}
		}
	}
}

pBiTPNode Point(pBiTPNode T,char a)
{
	if(T->data == a)
		return T;
	else
	{
		if(T->lchild!=NULL)
			if(Point(T->lchild,a)!=NULL)
			{
				return Point(T->lchild,a);
			}
			else
			{
				if(T->rchild!=NULL)
					if(Point(T->rchild,a)!=NULL)
						return Point(T->rchild,a);
			}
	}
	return NULL;
}

char Value(pBiTPNode p)
{
	return p->data;
}

void Assign(pBiTPNode T,char a)
{
	T->data = a;
}

char Parent(pBiTPNode T,char a)
{
	return Point(T,a)->parent->data;
}

char RightSibling(pBiTPNode T,char a)
{
	if(Point(T,a)->parent->rchild!=NULL)
		return Point(T,a)->parent->rchild->data;
	else
		return '*';
}

char LeftSibling(pBiTPNode T,char a)
{
	if(Point(T,a)->parent->lchild!=NULL)
		return Point(T,a)->parent->lchild->data;
	else
		return '*';
}

char RightChild(pBiTPNode T,char a)
{
	if(Point(T,a)->rchild!=NULL)
		return Point(T,a)->rchild->data;
	else
		return '*';
}
char LeftChild(pBiTPNode T,char a)
{
	if(Point(T,a)->lchild!=NULL)
		return Point(T,a)->lchild->data;
	else
		return '*';
}

void InsertChild(pBiTPNode T,int pos,pBiTPNode S)
{
	pBiTPNode p;
	if(pos==0)
	{
		p = T->lchild;
		T->lchild = S;
	}
	else if(pos==1)
	{
		p = T->rchild;
		T->rchild = S;
	}
	S->parent = T;
	S->rchild = p;
}

void DeleteChild(pBiTPNode T,int pos)
{
	if(pos==0)
	{
		T->lchild = NULL;
	}
	else if(pos==1)
	{
		T->rchild = NULL;
	}
}

void DestroyBiTree(pBiTPNode T)
{
	if(T!=NULL)
	{
		if(T->lchild)
			DestroyBiTree(T->lchild);
		if(T->rchild)
			DestroyBiTree(T->rchild);
		free(T);
		T = NULL;
	}
}

void Print(pBiTPNode T)
{
	if(T->parent==NULL)
		printf("%c是根节点\n",T->data);
	else
	{
		if(T->parent->lchild == T)
			printf("%c是%c的左孩子\n",T->data,T->parent->data);
		if(T->parent->rchild == T)
			printf("%c是%c的右孩子\n",T->data,T->parent->data);
	}
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pBiTPNode)malloc((length+1)*sizeof(BiTPNode));
	if(Q->Base == NULL)
	{
		printf("空间分配失败!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,pBiTPNode T)
{
	Q->Base[Q->rear] = *T;
	Q->rear++;
}

void de_Queue(qQueue Q,pBiTPNode T)
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

/*
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

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

void init_QU(qQueue QU);
void enQU(qQueue QU,int num);
void traverse_QU(qQueue QU);
int deQU(qQueue QU);
int length_QU(qQueue QU);
bool empty(qQueue QU);
void clear_QU(qQueue QU);
void destroy(qQueue QU);

void main()
{
	int ennum,denum,into_total;
	qQueue QU = (qQueue)malloc(sizeof(Queue));
	init_QU(QU);

	printf("请输入入队数:");
	scanf("%d",&into_total);
	for(int i=0;i<into_total;i++)
	{
		printf("请输入入队数值:");
		scanf("%d",&ennum);
		enQU(QU,ennum);
	}

	printf("出队数值为:%d\n",deQU(QU));
//	clear_QU(QU);
	destroy(QU);

//	traverse_QU(QU);
}

void init_QU(qQueue QU)
{
	qQNode head_Node = (qQNode)malloc(sizeof(QNode));
	if(head_Node == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	QU->front = head_Node;
	QU->rear = QU->front;
	head_Node->pNext = NULL;
	head_Node->data = 0;
}

void enQU(qQueue QU,int num)
{
	qQNode pNew = (qQNode)malloc(sizeof(QNode));
	if(pNew == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	pNew->data = num;
	QU->rear->pNext = pNew;
	QU->rear = pNew;
	pNew->pNext = NULL;
	QU->front->data++;
}

int deQU(qQueue QU)
{
	qQNode q = QU->front->pNext;
	QU->front->pNext = q->pNext;
	int e = q->data;
	free(q);
	QU->front->data--;
	if(QU->front->data == 0)
	{
		QU->rear = QU->front;
	}
	return e;
}

void traverse_QU(qQueue QU)
{
	if(empty(QU))
	{
		printf("列队为空!\n");
		exit(-1);
	}
	printf("列队总长度为:%d\n",QU->front->data);
	qQNode q = QU->front->pNext;
	while(q)
	{
		printf("->%d",q->data);
		q = q->pNext;
	}
}

int length_QU(qQueue QU)
{
	return QU->front->data;
}

void clear_QU(qQueue QU)
{
	QU->rear = QU->front;
	QU->front->data = 0;
}

void destroy(qQueue QU)
{
	while(QU->front)
	{
		QU->rear = QU->front->pNext;
		free(QU->front);
		QU->front = QU->rear;
	}
}

bool empty(qQueue QU)
{
	if(QU->rear == QU->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}
*/