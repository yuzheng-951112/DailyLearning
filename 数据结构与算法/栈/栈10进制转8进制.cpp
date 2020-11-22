#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	struct Node *pNext;
	int data;
}Node,*pNode;

typedef struct stack
{
	pNode bottom;
	pNode top;
}Stack,*pStack;


void init_Stack(pStack ST);
void push_Stack(pStack ST,int push_num);
void pop_Stack(pStack ST);
bool empty(pStack ST);
int length_Stack(pStack ST);

void main()
{
	unsigned num;
	pStack ST = (pStack)malloc(sizeof(Stack));
	init_Stack(ST);
	printf("待转换的数字 num=");
	scanf("%d",&num);
	while(num != 0)
	{
		push_Stack(ST,num%8);
		num = num/8;
	}

//	printf("\n%d",length_Stack(ST));
/*
	for(int i=0;i<=length_Stack(ST);i++)	//这里length_Stack(ST)是一个变量 随着每次pop_Stack(ST)而减少
	{
		pop_Stack(ST);
	}
*/
	while(!empty(ST))
	{
		pop_Stack(ST);
	}

//	printf("\n%d",length_Stack(ST));
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

void push_Stack(pStack ST,int push_num)
{
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->data = push_num;
	ST->top->pNext = pNew;
	pNew->pNext = NULL;
	ST->top = pNew;
}

void pop_Stack(pStack ST)
{
	pNode p = ST->bottom;
	while(p->pNext != ST->top)
	{
		p = p->pNext;
	}
	printf("->%d",p->pNext->data);
	free(p->pNext);
	p->pNext = NULL;
	ST->top = p;
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

int length_Stack(pStack ST)
{
	int i=0; 
	pNode p = ST->bottom;
	while(p != ST->top)
	{
		i++;
		p = p->pNext;
	}
	return i;
}
