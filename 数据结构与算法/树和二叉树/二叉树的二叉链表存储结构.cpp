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
	printf("构造空二叉树后,树空否?%d(1:是 0:否)树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	if((e1=Root(T))!='*')
		printf("二叉树的根为:%c\n",e1);
	else
		printf("树空,无根\n");
	printf("请先序输入二叉树(如:ab三个'*'表示a为根节点,b为左子树的二叉树):");
	CreateBiTree(T);
	printf("建立二叉树后,树空否?%d(1:是 0:否)树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	if((e1=Root(T))!='*')
		printf("二叉树的根为:%c\n",e1);
	else
		printf("树空,无根\n");
	printf("中序递归遍历二叉树:\n");
	InOrderTraversel(T);
/*	printf("\n中序非递归遍历二叉树:\n");
	NoInOrderTraversel1(T);
	printf("\n中序非递归遍历二叉树(另一种方法):\n");
	NoInOrderTraversel2(T);
	printf("\n后序递归遍历二叉树:\n");
	PostOrderTraverse(T);
	printf("\n层序遍历二叉树:\n");
	LevelOrderTraverse(T);
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
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("\n%c的双亲是%c",e1,Parent(T,e1));
	printf("\n%c的右兄弟是%c",e1,RightSibling(T,e1));
	printf("\n%c的左兄弟是%c",e1,LeftSibling(T,e1));
	printf("\n%c的右儿子是%c",e1,RightChild(T,e1));
	printf("\n%c的左儿子是%c\n",e1,LeftChild(T,e1));*/
	printf("构造一个右子树为空的二叉树S:\n");
	printf("请先序输入二叉树(如:ab三个'*'表示a为根节点,b为子树的二叉树):");
	InitBiTree(S);
	fflush(stdin);
	CreateBiTree(S);
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

void NoInOrderTraversel1(pBiTNode T)		//中序遍历二叉树T的非递归(利用客栈)		
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
			pop_Stack(&S,p);			//pop_Stack(&S,T)是错误的 T最后没有分配空间 执行错误
			printf("%c ",p->data);
			T = p->rchild;				//这里的p无需纠结是否是源地址，这里p->rchild和原来T中对应相同
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
			}while(p->rchild==NULL && !stackempty(&S));			//****这里添加!stackempty(&S)是限制最后p->rchild==NULL
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
	printf("第1层:");
	printf("%c ",T->data);
	while(BiTreeDepth(T)>=i)
	{
		printf("\n第%d层:",i);
		levelTraverse(&S,&S1,p);
		if((i++)<=BiTreeDepth(T))
		{
			printf("\n第%d层:",i+1);
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
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//这里命名p之后,return回去的p地址不是对应源地址
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//出队，队列元素赋值给a
			if(p->data==a)
				return p;
			if(p->lchild)					//有左孩子
				en_Queue(&q,p->lchild);		//入队左孩子
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
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//这里命名p之后,return回去的p地址不是对应源地址
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//出队，队列元素赋值给a
			if((p->lchild&&p->lchild->data==e1)||(p->rchild&&p->rchild->data==e1))
				return p->data;
			else
			{
				if(p->lchild)					//有左孩子
					en_Queue(&q,p->lchild);		//入队左孩子
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
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//这里命名p之后,return回去的p地址不是对应源地址
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//出队，队列元素赋值给a
			if(p->rchild&&p->rchild->data==e1)
				return p->lchild->data;
			else
			{
				if(p->lchild)					//有左孩子
					en_Queue(&q,p->lchild);		//入队左孩子
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
	pBiTNode p = (pBiTNode)malloc(sizeof(BiTNode));		//这里命名p之后,return回去的p地址不是对应源地址
	if(T)
	{
		init_Queue(&q,QUEUEMAX);
		en_Queue(&q,T);
		while(!EmptyQueue(&q))
		{
			de_Queue(&q,p);					//出队，队列元素赋值给a
			if(p->lchild&&p->lchild->data==e1)
				return p->rchild->data;
			else
			{
				if(p->lchild)					//有左孩子
					en_Queue(&q,p->lchild);		//入队左孩子
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
		printf("栈的头地址创建失败!");
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
		ST->bottom = (BiTNode*)realloc(ST->bottom,(ST->stacksize+STACKINCREMENT)*sizeof(BiTNode));		//realloc用于修改已经分配的空间
		if(ST->bottom == NULL)
		{
			printf("动态内存分配失败!");
			exit(-1);
		}
		ST->top = ST->bottom + ST->stacksize;
		ST->stacksize = ST->stacksize + STACKINCREMENT;
	}
	*(ST->top) = *T;					//这一步分解就是*(ST->top) = num;    ST->top++;
	ST->top++;
}

void pop_Stack(pStack ST,pBiTNode T)
{
	if(stackempty(ST))
	{
		printf("栈为空，无法出栈!\n");
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
		printf("空间分配失败!\n");
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