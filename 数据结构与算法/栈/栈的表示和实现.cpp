#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2

typedef struct stack
{
	int *top;
	int *bottom;
	int stacksize;
}Stack,*pStack;

void init_Stack(pStack ST);
void push_Stack(pStack ST,int num);
void traverse_Stack(pStack ST);
void pop_Stack(pStack ST);
void destroy_Stack(pStack ST);
void clear_Stack(pStack ST);

bool empty(pStack ST);

void main()
{
	int push_total,pop_total,num;
	pStack ST = (pStack)malloc(sizeof(Stack));
	if(ST == NULL)
	{
		printf("��̬�ڴ����ʧ��!");
		exit(-1);
	}
	init_Stack(ST);
	printf("������Ҫ��ջ�ĸ��� push_total = ");
	scanf("%d",&push_total);
	for(int i=0;i<push_total;i++)
	{
		printf("��������ջ������ num = ");
		scanf("%d",&num);
		push_Stack(ST,num);
	}

	printf("������Ҫ��ջ�ĸ��� pop_total = ");
	scanf("%d",&pop_total);
	for(i=0;i<pop_total;i++)
	{
		pop_Stack(ST);
	}

	destroy_Stack(ST);

	traverse_Stack(ST);
}

void init_Stack(pStack ST)
{
	ST->bottom = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
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

void push_Stack(pStack ST,int num)
{
	if(ST->top-ST->bottom>=ST->stacksize)
	{
		ST->bottom = (int*)realloc(ST->bottom,(ST->stacksize+STACKINCREMENT)*sizeof(int));
		if(ST->bottom == NULL)
		{
			printf("��̬�ڴ����ʧ��!");
			exit(-1);
		}
		ST->top = ST->bottom + ST->stacksize;
		ST->stacksize = ST->stacksize + STACKINCREMENT;
	}
	*(ST->top)++ = num;					//��һ���ֽ����*(ST->top) = num;    ST->top++;
}

void pop_Stack(pStack ST)
{
	if(empty(ST))
	{
		printf("ջΪ�գ��޷���ջ!\n");
		exit(-1);
	}
	else
	{
		printf("->%d",*(ST->top-1));
		ST->top--;
	}
}

void destroy_Stack(pStack ST)
{
	free(ST->bottom);
	ST->bottom = NULL;
	ST->top = NULL;
	ST->stacksize = 0;
}

void clear_Stack(pStack ST)	//���óɿ�ջ
{
	ST->top = ST->bottom;
}

void traverse_Stack(pStack ST)
{
	int* ptemp = ST->bottom;
	while(ptemp != ST->top)
	{
		printf("->%d",*ptemp);
		ptemp++;
	}
	printf("\n");
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