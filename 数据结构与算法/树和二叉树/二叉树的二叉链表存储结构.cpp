#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
#define QUEUEMAX 30

typedef struct BiTNode
{
	int data;
	BiTNode *lchild,*rchild;
}BiTNode,*pBiTNode;

typedef struct stack
{
	BiTNode *top;
	BiTNode *bottom;
	int stacksize;
}Stack,*pStack;

typedef struct Queue
{
	BiTNode *Base;
	int front;
	int rear;
}Queue,*qQueue;

void InitBiTree(pBiTNode &);
int BiTreeEmpty(pBiTNode);
int BiTreeDepth(pBiTNode);
char Root(pBiTNode);
void CreateBiTree(pBiTNode &);
void InOrderTraversel(pBiTNode);
void NoInOrderTraversel1(pBiTNode);
void NoInOrderTraversel2(pBiTNode);
void PostOrderTraverse(pBiTNode);
void levelTraverse(pStack,pStack,pBiTNode);
void LevelOrderTraverse(pBiTNode);
void LevelOrderTraverse1(pBiTNode);
pBiTNode Point(pBiTNode,char);
char Value(pBiTNode);
void Assign(pBiTNode,char);
char Parent(pBiTNode,char);
char LeftSibling(pBiTNode,char);
char RightSibling(pBiTNode,char);
char LeftChild(pBiTNode,char);
char RightChild(pBiTNode,char);
void PreOrderTraverse(pBiTNode);
void InsertChild(pBiTNode,int,pBiTNode);
void DeleteChild(pBiTNode,int);
void DestroyBiTree(pBiTNode &);

void init_Stack(pStack);
void push_Stack(pStack,pBiTNode);
void pop_Stack(pStack,pBiTNode);

int gettop(pStack,pBiTNode);
bool stackempty(pStack);

void init_Queue(qQueue,int);
void en_Queue(qQueue,pBiTNode);
void de_Queue(qQueue,pBiTNode);
bool EmptyQueue(qQueue);

void main()
{
	int i;
	char e1;
	pBiTNode T,S,p;
	InitBiTree(T);
	printf("����ն�������,���շ�?%d(1:�� 0:��)�������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	if((e1=Root(T))!='*')
		printf("�������ĸ�Ϊ:%c\n",e1);
	else
		printf("����,�޸�\n");
	printf("���������������(��:ab����'*'��ʾaΪ���ڵ�,bΪ�������Ķ�����):");
	CreateBiTree(T);
	printf("������������,���շ�?%d(1:�� 0:��)�������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	if((e1=Root(T))!='*')
		printf("�������ĸ�Ϊ:%c\n",e1);
	else
		printf("����,�޸�\n");
	printf("����ݹ����������:\n");
	InOrderTraversel(T);
/*	printf("\n����ǵݹ����������:\n");
	NoInOrderTraversel1(T);
	printf("\n����ǵݹ����������(��һ�ַ���):\n");
	NoInOrderTraversel2(T);
	printf("\n����ݹ����������:\n");
	PostOrderTraverse(T);
	printf("\n�������������:\n");
	LevelOrderTraverse(T);
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
	printf("�������������:\n");
	LevelOrderTraverse(T);
	printf("\n%c��˫����%c",e1,Parent(T,e1));
	printf("\n%c�����ֵ���%c",e1,RightSibling(T,e1));
	printf("\n%c�����ֵ���%c",e1,LeftSibling(T,e1));
	printf("\n%c���Ҷ�����%c",e1,RightChild(T,e1));
	printf("\n%c���������%c\n",e1,LeftChild(T,e1));*/
	printf("����һ��������Ϊ�յĶ�����S:\n");
	printf("���������������(��:ab����'*'��ʾaΪ���ڵ�,bΪ�����Ķ�����):");
	InitBiTree(S);
	fflush(stdin);
	CreateBiTree(S);
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

void InitBiTree(pBiTNode &T)
{
	T = NULL;
}

int BiTreeEmpty(pBiTNode T)
{
	if(T==NULL)
		return 1;
	else
		return 0;
}

int BiTreeDepth(pBiTNode T)
{
	int max=0,dep;
	if(!T)
		return 0;
	else
	{
		if(T->lchild!=NULL)
			if((dep=BiTreeDepth(T->lchild))>max)
				max = dep;
		if(T->rchild!=NULL)
			if((dep=BiTreeDepth(T->rchild))>max)
				max = dep;
	}
	return max+1;
}

char Root(pBiTNode T)
{
	if(BiTreeEmpty(T))
		return '*';
	else
		return T->data;
}

void CreateBiTree(pBiTNode &T)
{
	char e;
	scanf("%c",&e);
	if(e!='*')
	{
		if(!(T=(pBiTNode)malloc(sizeof(BiTNode))))
			exit(-1);
		else
		{
			T->data = e;
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
	else
		T = NULL;
}

void PreOrderTraverse(pBiTNode T)
{
	printf("%c ",T->data);
	if(T->lchild!=NULL)
		InOrderTraversel(T->lchild);
	if(T->rchild!=NULL)
		InOrderTraversel(T->rchild);
}

void InOrderTraversel(pBiTNode T)
{
	if(T->lchild!=NULL)
		InOrderTraversel(T->lchild);
	printf("%c ",T->data);
	if(T->rchild!=NULL)
		InOrderTraversel(T->rchild);
}

void NoInOrderTraversel1(pBiTNode T)		//�������������T�ķǵݹ�(���ÿ�ջ)		
{
	Stack S;
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));
	if(!p)
		exit(-1);
	init_Stack(&S);
	while(T || !stackempty(&S))
	{
		if(T)
		{
			push_Stack(&S,T);
			T = T->lchild;
		}
		else
		{
			pop_Stack(&S,p);			//pop_Stack(&S,T)�Ǵ���� T���û�з���ռ� ִ�д���
			printf("%c ",p->data);
			T = p->rchild;				//�����p��������Ƿ���Դ��ַ������p->rchild��ԭ��T�ж�Ӧ��ͬ
		}
	}
}

void NoInOrderTraversel2(pBiTNode T)
{
	Stack S;
	pBiTNode q,p = (pBiTNode)malloc(sizeof(BiTNode));
	if(!p)
		exit(-1);
	init_Stack(&S);
	push_Stack(&S,T);
	while(!stackempty(&S))
	{
		while(gettop(&S,p) && p->lchild!=NULL)
		{
			push_Stack(&S,p->lchild);
		}
		if(!stackempty(&S))
		{
			do
			{
				pop_Stack(&S,p);
				printf("%c ",p->data);
			}while(p->rchild==NULL && !stackempty(&S));			//****�������!stackempty(&S)���������p->rchild==NULL
			if(p->rchild!=NULL)
				push_Stack(&S,p->rchild);
		}
	}
}

void PostOrderTraverse(pBiTNode T)
{
	if(T->lchild!=NULL)
		PostOrderTraverse(T->lchild);
	if(T->rchild!=NULL)
		PostOrderTraverse(T->rchild);
	printf("%c ",T->data);
}

void levelTraverse(pStack S,pStack S1,pBiTNode p)
{
	while(!stackempty(S))
	{
		pop_Stack(S,p);
		if(p->rchild!=NULL)
		{
			printf("%c ",p->rchild->data);
			push_Stack(S1,p->rchild);
		}
		if(p->lchild!=NULL)
		{
			printf("%c ",p->lchild->data);
			push_Stack(S1,p->lchild);
		}
	}
}

void LevelOrderTraverse(pBiTNode T)
{
	int i=1;
	Stack S,S1;
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));
	if(!p)
		exit(-1);
	init_Stack(&S);
	init_Stack(&S1);;
	push_Stack(&S,T);
	printf("��1��:");
	printf("%c ",T->data);
	while(BiTreeDepth(T)>=i)
	{
		printf("\n��%d��:",i);
		levelTraverse(&S,&S1,p);
		if((i++)<=BiTreeDepth(T))
		{
			printf("\n��%d��:",i+1);
			levelTraverse(&S1,&S,p);
			i++;
		}
	}
}

void LevelOrderTraverse1(pBiTNode T)
{
	Queue q;
	pBiTNode a = (pBiTNode)malloc(sizeof(BiTNode));
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,a);
			printf("%c",a->data);
			if(a->lchild!=NULL)
				en_Queue(&q,a->lchild);
			if(a->rchild!=NULL)
				en_Queue(&q,a->rchild);
		}
	}
}

pBiTNode Point(pBiTNode T,char a)
{
	if(T->data == a)
		return T;
	else
	{
		if(T->lchild!=NULL)
			if(Point(T->lchild,a)!=NULL)
				return Point(T->lchild,a);
		if(T->rchild!=NULL)
			if(Point(T->rchild,a)!=NULL)
				return Point(T->rchild,a);
	}
	return NULL;
}

/*
pBiTNode Point(pBiTNode T,char a)
{
	Queue q;
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//��������p֮��,return��ȥ��p��ַ���Ƕ�ӦԴ��ַ
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//���ӣ�����Ԫ�ظ�ֵ��a
			if(p->data==a)
				return p;
			if(p->lchild)					//������
				en_Queue(&q,p->lchild);		//�������
			if(p->rchild)
				en_Queue(&q,p->rchild);
		}
	}
	return NULL;
}
*/

char Value(pBiTNode p)
{
	return p->data;
}

void Assign(pBiTNode T,char a)
{
	T->data = a;
}

char Parent(pBiTNode T,char e1)
{
	Queue q;
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//��������p֮��,return��ȥ��p��ַ���Ƕ�ӦԴ��ַ
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//���ӣ�����Ԫ�ظ�ֵ��a
			if((p->lchild&&p->lchild->data==e1)||(p->rchild&&p->rchild->data==e1))
				return p->data;
			else
			{
				if(p->lchild)					//������
					en_Queue(&q,p->lchild);		//�������
				if(p->rchild)
					en_Queue(&q,p->rchild);
			}
		}
	}
	return NULL;
}

char LeftSibling(pBiTNode T,char e1)
{
	Queue q;
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//��������p֮��,return��ȥ��p��ַ���Ƕ�ӦԴ��ַ
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//���ӣ�����Ԫ�ظ�ֵ��a
			if(p->rchild&&p->rchild->data==e1)
				return p->lchild->data;
			else
			{
				if(p->lchild)					//������
					en_Queue(&q,p->lchild);		//�������
				if(p->rchild)
					en_Queue(&q,p->rchild);
			}
		}
	}
	return '*';
}

char RightSibling(pBiTNode T,char e1)
{
	Queue q;
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//��������p֮��,return��ȥ��p��ַ���Ƕ�ӦԴ��ַ
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//���ӣ�����Ԫ�ظ�ֵ��a
			if(p->lchild&&p->lchild->data==e1)
				return p->rchild->data;
			else
			{
				if(p->lchild)					//������
					en_Queue(&q,p->lchild);		//�������
				if(p->rchild)
					en_Queue(&q,p->rchild);
			}
		}
	}
	return '*';
}

char LeftChild(pBiTNode T,char e1)
{
	if(Point(T,e1)->lchild!=NULL)
		return Point(T,e1)->lchild->data;
	else
		return '*';
}

char RightChild(pBiTNode T,char e1)
{
	if(Point(T,e1)->rchild!=NULL)
		return Point(T,e1)->rchild->data;
	else
		return '*';
}

void InsertChild(pBiTNode T,int pos,pBiTNode S)
{
	pBiTNode p;
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
	S->rchild = p;
}

void DestroyBiTree(pBiTNode &T)
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

void DeleteChild(pBiTNode T,int pos)
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

void init_Stack(pStack ST)
{
	ST->bottom = (BiTNode*)malloc(STACK_INIT_SIZE*sizeof(BiTNode));
	if(ST->bottom == NULL)
	{
		printf("ջ��ͷ��ַ����ʧ��!");
		exit(-1);
	}
	else
	{
		ST->top = ST->bottom;
		ST->stacksize = STACK_INIT_SIZE;
	}
}

void push_Stack(pStack ST,pBiTNode T)
{
	if(ST->top-ST->bottom>=ST->stacksize)
	{
		ST->bottom = (BiTNode*)realloc(ST->bottom,(ST->stacksize+STACKINCREMENT)*sizeof(BiTNode));		//realloc�����޸��Ѿ�����Ŀռ�
		if(ST->bottom == NULL)
		{
			printf("��̬�ڴ����ʧ��!");
			exit(-1);
		}
		ST->top = ST->bottom + ST->stacksize;
		ST->stacksize = ST->stacksize + STACKINCREMENT;
	}
	*(ST->top) = *T;					//��һ���ֽ����*(ST->top) = num;    ST->top++;
	ST->top++;
}

void pop_Stack(pStack ST,pBiTNode T)
{
	if(stackempty(ST))
	{
		printf("ջΪ�գ��޷���ջ!\n");
		exit(-1);
	}
	else
	{
		ST->top--;
		*T = *(ST->top);
	}
}

int gettop(pStack ST,pBiTNode T)
{
	if(ST->top>ST->bottom)
	{
		ST->top--;
		*T = *(ST->top);
		ST->top++;
		return 1;
	}
	else
		return 0;
}

bool stackempty(pStack ST)
{
	if(ST->bottom == ST->top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pBiTNode)malloc((length+1)*sizeof(Queue));
	if(Q->Base == NULL)
	{
		printf("�ռ����ʧ��!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,pBiTNode T)
{
	Q->Base[Q->rear] = *T;
	Q->rear++;
}

void de_Queue(qQueue Q,pBiTNode T)
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