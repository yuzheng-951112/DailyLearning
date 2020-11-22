#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	struct Node *pNext;
	int data;
}Node,*pNode;

typedef struct Stack
{
	pNode top;
	pNode bottom;
}Stack,*pStack;

void init_Stack(pStack ST);
void build_Stack(pStack ST);
void push_Stack(pStack ST,int push_num);
void pop_Stack(pStack ST);
void traverse_Stack(pStack ST);
void clear_Stack(pStack ST);
void destroy_Stack(pStack ST);

void main()
{
	int i,total,push_num;
	pStack ST = (pStack)malloc(sizeof(Stack));
	init_Stack(ST);
	build_Stack(ST);

	printf("请输入入栈数=");
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{
		printf("请输入入栈的数=");
		scanf("%d",&push_num);
		push_Stack(ST,push_num);
	}

	printf("请输入出栈数=");
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{
		pop_Stack(ST);
	}
	printf("\n");

	traverse_Stack(ST);
}

void init_Stack(pStack ST)
{
	pNode Stack_Head = (pNode)malloc(sizeof(Node));
	if(Stack_Head == NULL)
	{
		printf("头节点分配失败!\n");
		exit(-1);
	}
	else
	{
		ST->bottom = Stack_Head;
		ST->top = ST->bottom;
		Stack_Head->pNext = NULL;
	}
}

void build_Stack(pStack ST)
{
	int total,num;
	printf("请输入入栈数=");
	scanf("%d",&total);
	for(int i=0;i<total;i++)
	{
		pNode pNew = (pNode)malloc(sizeof(Node));
		if(pNew == NULL)
		{
			printf("内存分配失败!\n");
			exit(-1);
		}
		else
		{
			printf("请输入入栈的数=");
			scanf("%d",&num);
			pNew->data = num;
			pNew->pNext = ST->top;
			ST->top = pNew;
		}
	}
}

void push_Stack(pStack ST,int push_num)
{
	pNode pNew = (pNode)malloc(sizeof(Node));
	if(pNew == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	else
	{
		pNew->data = push_num;
		pNew->pNext = ST->top;
		ST->top = pNew;
	}
}

void pop_Stack(pStack ST)
{
	printf("->%d",ST->top->data);
	pNode ptemp = ST->top;
	ST->top = ptemp->pNext;
	free(ptemp);
}

void traverse_Stack(pStack ST)
{
	pNode p = ST->top;
	while(p != ST->bottom)
	{
		printf("->%d",p->data);
		p = p->pNext;
	}
}

void clear_Stack(pStack ST)
{
	ST->top = ST->bottom;
}

void destroy_Stack(pStack ST)
{
	pNode q = ST->top,p;
	while(q != ST->bottom)
	{
		p = q->pNext;
		free(q);
		q = p;
	}
	free(ST->bottom);
	ST->bottom = NULL;
	ST->top = ST->bottom;
}

bool empty(pStack ST)
{
	if(ST->top == ST->bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}