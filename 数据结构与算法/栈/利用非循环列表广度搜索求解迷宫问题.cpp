#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define M 5
#define N 5
#define D 8
#define QUEUELENGTH 100

typedef struct
{
	int x,y;
	int pre;
}QElemType,*qQElemType;

typedef struct Queue
{
	QElemType *Base;
	int front;
	int rear;
}Queue,*qQueue;

typedef struct Node
{
	struct Node *pNext;
	QElemType data;
}Node,*pNode;

typedef struct stack
{
	pNode bottom;
	pNode top;
}Stack,*pStack;

struct 
{
	int x,y;
#if	D == 8
}move[D] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
#endif
#if D == 4
}move[D] = {{0,1},{1,0},{0,-1},{-1,0}};
#endif

void init_Queue(qQueue Q,int length);
void en_Queue(qQueue Q,QElemType val);
QElemType de_Queue(qQueue Q);
int use_Queue(qQueue Q);

void init_Stack(pStack ST);
void push_Stack(pStack ST,QElemType push_num);
QElemType pop_Stack(pStack ST);
bool empty(pStack ST);

void main()
{
	int i,j;
	int maze[M][N];
	printf("%d行%列迷宫(不包括外墙)\n",M-2,N-2);
	for(i=0;i<N;i++)
	{
		maze[0][i] = 0;
		maze[M-1][i] = 0;
	}
	for(i=1;i<M-1;i++)
	{
		maze[i][0] = 0;
		maze[i][N-1] = 0;
	}
	printf("请按行输入迷宫结构!\n");
	for(i=1;i<M-1;i++)
	{
		for(j=1;j<N-1;j++)
		{
			printf("请输入第%d行第%d列的结构:",i,j);
			scanf("%d",&maze[i][j]);
		}
	}
	printf("迷宫结构(包括外墙):\n");
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			printf(" %d ",maze[i][j]);
		}
		printf("\n");
	}

	Queue Q;
	QElemType qf,qt;
	Stack S;
	int flag=1;
	int x1,y1;
	printf("请输入入口的行,列(左上角1,1)\n");
	scanf("%d,%d",&qf.x,&qf.y);
	printf("请输入出口的行,列(右下角为%d,%d)\n",M-2,N-2);
	scanf("%d,%d",&x1,&y1);
	qf.pre = -1;
	maze[qf.x][qf.y] = -1;
	init_Queue(&Q,QUEUELENGTH);
	en_Queue(&Q,qf);
	while(use_Queue(&Q) != 0 && flag)
	{
		qf = de_Queue(&Q);
		for(i=0;i<D;i++)
		{
			qt.x = qf.x + move[i].x;
			qt.y = qf.y + move[i].y;
			if(maze[qt.x][qt.y] == 1)
			{
				maze[qt.x][qt.y] = -1;
				qt.pre = Q.front - 1;
				en_Queue(&Q,qt);
				if(qt.x == x1 && qt.y == y1)
				{
					flag = 0;
					break;
				}
			}
		}
	}
	if(flag)
	{
		printf("没用路径可以到达!\n");
		exit(-1);
	}
	else
	{
		init_Stack(&S);
		i = Q.rear - 1;
		while(i>=0)
		{
			push_Stack(&S,Q.Base[i]);
			i = Q.Base[i].pre;
		}
		i = 0;
		while(!empty(&S))
		{
			qf = pop_Stack(&S);
			i++;
			maze[qf.x][qf.y] = i;
		}
		printf("走出的迷宫的一个方案:\n");
		for(i=1;i<M-1;i++)
		{
			for(j=1;j<N-1;j++)
			{
				printf("%3d",maze[i][j]);
			}
			printf("\n");
		}
	}

}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (qQElemType)malloc((length+1)*sizeof(qQElemType));
	if(Q->Base == NULL)
	{
		printf("空间分配失败!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,QElemType val)
{
	Q->Base[Q->rear] = val;
	Q->rear++;
}

QElemType de_Queue(qQueue Q)
{
	QElemType e = Q->Base[Q->front];
	Q->front++;
	return e;
}

int use_Queue(qQueue Q)
{
	return Q->rear - Q->front;
}

void init_Stack(pStack ST)
{
	pNode pStack_Head = (pNode)malloc(sizeof(Node));
	if(pStack_Head == NULL)
	{
		printf("分配内存失败!");
		exit(-1);
	}
	else
	{
		ST->bottom = pStack_Head;
		ST->top = pStack_Head;
		pStack_Head->pNext = NULL;
	}
}

void push_Stack(pStack ST,QElemType push_num)
{
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->data = push_num;
	ST->top->pNext = pNew;
	pNew->pNext = NULL;
	ST->top = pNew;
}

QElemType pop_Stack(pStack ST)
{
	QElemType e;
	pNode p = ST->bottom;
	while(p->pNext != ST->top)
	{
		p = p->pNext;
	}
	e = p->pNext->data;
	free(p->pNext);
	p->pNext = NULL;
	ST->top = p;
	return e;
}

bool empty(pStack ST)
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