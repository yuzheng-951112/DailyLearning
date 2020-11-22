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
void build_Stack(pStack ST);
void traverse_Stack(pStack ST);
void push_Stack(pStack ST,int push_num);
void pop_Stack(pStack ST);
void clear_Stack(pStack ST);
void destroy_Stack(pStack ST);
int length_Stack(pStack ST);

bool empty(pStack ST);

void main()
{
	int push_num,total;
	pStack ST = (pStack)malloc(sizeof(Stack));
	init_Stack(ST);
	build_Stack(ST);

	printf("请输入要入栈总数 total = ");
	scanf("%d",&total);
	for(int i=0;i<total;i++)
	{
		printf("请输入要入栈的数 push_num = ");
		scanf("%d",&push_num);
		push_Stack(ST,push_num);
	}


	printf("请输入要出栈总数 total = ");
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{
		pop_Stack(ST);
	}
	printf("\n");

//	clear_Stack(ST);
//	destroy_Stack(ST);

	traverse_Stack(ST);

	printf("\n%d",length_Stack(ST));
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

void build_Stack(pStack ST)
{
	int total,num;
	printf("请输入要栈入总数 total = ");
	scanf("%d",&total);
	
	pNode ptemp = ST->bottom;
	for(int i=0;i<total;i++)
	{
		pNode pNew = (pNode)malloc(sizeof(Node));
		printf("请输入要入栈的数 num = ");
		scanf("%d",&num);
		pNew->data = num;
		ptemp->pNext = pNew;
		pNew->pNext = NULL;
		ptemp = pNew;
	}
	ST->top = ptemp;
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

void traverse_Stack(pStack ST)
{
	if(empty(ST))
	{
		printf("栈为空!");
		exit(-1);
	}
	else
	{
		pNode p = ST->bottom->pNext;
		while(p != ST->top->pNext)
		{
			printf("->%d",p->data);
			p = p->pNext;
		}
	}
}

void clear_Stack(pStack ST)
{
	ST->top = ST->bottom;
}

void destroy_Stack(pStack ST)
{
	pNode p = ST->bottom->pNext,q;
	while(p)
	{
		q = p->pNext;
		free(p);
		p = q;
	}
	ST->top = ST->bottom;
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

