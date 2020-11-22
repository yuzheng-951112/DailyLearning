#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Queue
{
	int *Base;
	int front;
	int rear;
	int len;
}Queue,*qQueue;

void init_Queue(qQueue Q,int length);
void en_Queue(qQueue Q,int val);
int de_Queue(qQueue Q);
int use_Queue(qQueue Q);
void traverse_Queue(qQueue Q);
void clear_Queue(qQueue Q);
void clear_Queue(qQueue Q);
void destroy_Queue(qQueue Q);

void main()
{
	Queue Q;
	int length,en_length,de_length,en_num;
	printf("�������жӳ���:");
	scanf("%d",&length);
	init_Queue(&Q,length);

	printf("��������ӳ���:");
	scanf("%d",&en_length);

	while(1)
	{
		if((Q.len-1-use_Queue(&Q)) >= en_length && en_length >= 0)
		{
			break;
		}
		else
		{
			printf("ʣ����пռ�Ϊ%d\n",Q.len-1-use_Queue(&Q));
			printf("������������ӳ���:");
			scanf("%d",&en_length);
		}
	}
	
	for(int i=0;i<en_length;i++)
	{
		printf("������Ҫ��ӵ�����:");
		scanf("%d",&en_num);
		en_Queue(&Q,en_num);
	}

	printf("������Ҫ���Եĳ���:");
	scanf("%d",&de_length);
	
	while(1)
	{
		if(de_length >= 0 && de_length <= use_Queue(&Q))
		{
			break;
		}
		else
		{
			printf("���ö��пռ�Ϊ%d",use_Queue(&Q));
			printf("������������г���:");
			scanf("%d",&de_length);
		}
	}

	for(i=0;i<de_length;i++)
	{
		printf("->%d",de_Queue(&Q));
	}

	printf("\n");

//	clear_Queue(&Q);
//	destroy_Queue(&Q);

	traverse_Queue(&Q);
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (int*)malloc(sizeof(int)*length);
	Q->front = 0;
	Q->rear = 0;
	Q->len = length;
}

void en_Queue(qQueue Q,int val)
{
	Q->Base[Q->rear] = val;
	Q->rear = (Q->rear+1)%Q->len;
}

int de_Queue(qQueue Q)
{
	int e;
	e = Q->Base[Q->front];
	Q->front = (Q->front+1)%Q->len;
	return e;
}

void clear_Queue(qQueue Q)
{
	Q->front = Q->rear = 0;

}

void destroy_Queue(qQueue Q)
{
	if(Q->Base)
		free(Q->Base);
	Q->Base = NULL;
	Q->front = Q->rear = 0;
}

int use_Queue(qQueue Q)
{
	return (Q->rear - Q->front + Q->len)%Q->len;
}

void traverse_Queue(qQueue Q)
{
	if(use_Queue(Q) == 0)
	{
		printf("����Ϊ��!\n");
		exit(-1);
	}
	int r = Q->front;
	while(r != Q->rear)
	{
		printf("->%d",Q->Base[r]);
		r = (r+1)%Q->len;
	}
}