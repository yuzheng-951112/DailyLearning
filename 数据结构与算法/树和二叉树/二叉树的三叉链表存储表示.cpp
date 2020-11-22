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
	printf("����ն�������,���շ�?%d(1:�� 0:��)�������=%d\n",BiTreeEmpty(T),BitreeDepth(T));
	if((e1=Root(T))!='*')
		printf("�������ĸ�Ϊ:%c\n",e1);
	else
		printf("����,�޸�\n");
	printf("���������������(��:ab����'*'��ʾaΪ���ڵ�,bΪ�������Ķ�����):");
	CreateBiTree(T,NULL);
//	CreateBiTree(T,NULL);
	printf("����ն�������,���շ�?%d(1:�� 0:��)�������=%d\n",BiTreeEmpty(T),BitreeDepth(T));
	if((e1=Root(T))!='*')
		printf("�������ĸ�Ϊ:%c\n",e1);
	else
		printf("����,�޸�\n");
	printf("\n����ǵݹ����������:\n");
	InOrderTraversel(T);
	printf("\n����ݹ����������:\n");
	PostOrderTraverse(T);
	fflush(stdin);
	printf("\n�������������(��һ�ַ���):\n");
	LevelOrderTraverse1(T);
	printf("\n������һ���ڵ��ֵ:");
	fflush(stdin);
	scanf("%c%*c",&e1);
	p = Point(T,e1);
	printf("�ڵ��ֵΪ%c\n",Value(p));
	printf("���ı�˽ڵ��ֵ,��������ֵ:");
	scanf("%c%*c",&e1);
	Assign(p,e1);
	printf("\n�������������(��һ�ַ���):\n");
	LevelOrderTraverse1(T);
	printf("\n%c��˫����%c",e1,Parent(T,e1));
	printf("\n%c�����ֵ���%c",e1,RightSibling(T,e1));
	printf("\n%c�����ֵ���%c",e1,LeftSibling(T,e1));
	printf("\n%c���Ҷ�����%c",e1,RightChild(T,e1));
	printf("\n%c���������%c\n",e1,LeftChild(T,e1));
	printf("����һ��������Ϊ�յĶ�����S:\n");
	printf("���������������(��:ab����'*'��ʾaΪ���ڵ�,bΪ�����Ķ�����):");
	InitBitree(S);
	CreateBiTree(S,NULL);
	printf("����ݹ����������S:\n");
	PreOrderTraverse(S);
	printf("��S�嵽��T��,��������T����S��˫�׽ڵ� SΪ��(0)��(1)����:");
	scanf("%*c%c,%d",&e1,&i);
	p = Point(T,e1);
	InsertChild(p,i,S);
	printf("����ݹ����������S:\n");
	PreOrderTraverse(T);
	printf("ɾ������,�������ɾ��������˫�׽ڵ� ��(0)��(1)����:");
	scanf("%*c%c,%d",&e1,&i);
	p = Point(T,e1);
	DeleteChild(p,i);
	printf("����ݹ����������S:\n");
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
		T->parent = NULL;	//���ڵ��˫��Ϊ"��"
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);							//����Ҫ��de_Queue����ַ �����Ǵ�ֵ ��Ȼ�������(�޸�de_Queue)��������
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
		printf("%c�Ǹ��ڵ�\n",T->data);
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,a);
			if(a->lchild!=NULL)
			{
				printf("%c��%c������\n",a->lchild->data,a->data);
				en_Queue(&q,a->lchild);
			}
			if(a->rchild!=NULL)
			{
				printf("%c��%c������\n",a->rchild->data,a->data);
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
		printf("%c�Ǹ��ڵ�\n",T->data);
	else
	{
		if(T->parent->lchild == T)
			printf("%c��%c������\n",T->data,T->parent->data);
		if(T->parent->rchild == T)
			printf("%c��%c���Һ���\n",T->data,T->parent->data);
	}
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pBiTPNode)malloc((length+1)*sizeof(BiTPNode));
	if(Q->Base == NULL)
	{
		printf("�ռ����ʧ��!\n");
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

	printf("�����������:");
	scanf("%d",&into_total);
	for(int i=0;i<into_total;i++)
	{
		printf("�����������ֵ:");
		scanf("%d",&ennum);
		enQU(QU,ennum);
	}

	printf("������ֵΪ:%d\n",deQU(QU));
//	clear_QU(QU);
	destroy(QU);

//	traverse_QU(QU);
}

void init_QU(qQueue QU)
{
	qQNode head_Node = (qQNode)malloc(sizeof(QNode));
	if(head_Node == NULL)
	{
		printf("�ڴ����ʧ��!\n");
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
		printf("�ڴ����ʧ��!\n");
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
		printf("�ж�Ϊ��!\n");
		exit(-1);
	}
	printf("�ж��ܳ���Ϊ:%d\n",QU->front->data);
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