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