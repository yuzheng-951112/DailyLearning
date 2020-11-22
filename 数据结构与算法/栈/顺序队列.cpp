#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Queue
{
	int *Base;
	int front;
	int rear;
}Queue,*qQueue;

void init_Queue(qQueue Q,int length);
void en_Queue(qQueue Q,int val);
void traverse_Queue(qQueue Q);
int de_Queue(qQueue Q);
void clear_Queue(qQueue Q);
void destroy_Queue(qQueue Q);
bool EmptyQueue(qQueue Q);

void main()
{
	int length,en_length,de_length,en_num;
	Queue Q;
	printf("��������еĳ���:");
	scanf("%d",&length);
	init_Queue(&Q,length);

	printf("��������ӵĳ���:");
	scanf("%d",&en_length);

	while(1)
	{
		if(length-(Q.rear-Q.front) >= en_length && en_length >= 0)
		{
			break;
		}
		else
		{
			printf("ʣ�೤��Ϊ:%d",length-(Q.rear-Q.front));
			printf("������������ӳ���:");
			scanf("%d",&en_length);
		}
	}

	for(int i=0;i<en_length;i++)
	{
		printf("�����������:");
		scanf("%d",&en_num);
		en_Queue(&Q,en_num);
	}

	printf("��������ӵĳ���:");
	scanf("%d",&de_length);

	while(1)
	{
		if(Q.rear-Q.front >= de_length && de_length >= 0)
		{
			break;
		}
		else
		{
			printf("���ó���Ϊ:%d",Q.rear-Q.front);
			printf("������������ӳ���:");
			scanf("%d",&de_length);
		}
	}

	for(i=0;i<de_length;i++)
	{
		printf("->%d",de_Queue(&Q));
	}

	printf("\n");
	
	traverse_Queue(&Q);
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (int*)malloc((length+1)*sizeof(int));
	if(Q->Base == NULL)
	{
		printf("�ռ����ʧ��!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,int val)
{
	Q->Base[Q->rear] = val;
	Q->rear++;
}

int de_Queue(qQueue Q)
{
	int e = Q->Base[Q->front];
	Q->front++;
	return e;
}

void clear_Queue(qQueue Q)
{
	Q->rear = Q->front = 0;
}

void destroy_Queue(qQueue Q)
{
	if(Q->Base)
		free(Q->Base);
	Q->Base = NULL;
	Q->front = Q->rear = 0;
}

void traverse_Queue(qQueue Q)
{
	int r = Q->front;
	while(r != Q->rear)
	{
		printf("->%d",Q->Base[r]);
		r++;
	}
}

bool EmptyQueue(qQueue Q)
{
	if(Q->rear = Q->front)
		return true;
	else
		return false;
}