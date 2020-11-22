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
void push_Stack(pStack ST,int push_num);
void pop_Stack(pStack ST);
void clear_Stack(pStack ST);
void traverse_Stack(pStack ST);
void copy(FILE *fp,pStack ST);

void main()
{
	FILE *fp;
	fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/text,txt","w");
	char ch;
	pStack ST = (pStack)malloc(sizeof(Stack));
	init_Stack(ST);
	ch = getchar();
	while(ch != EOF)
	{
		while(ch != EOF && ch != '\n')		//以空格为单位完成对每行的筛选
		{
			switch(ch)
			{
			case'#':pop_Stack(ST);
					break;
			case'@':clear_Stack(ST);
					break;
			default:push_Stack(ST,ch);
			}
			ch = getchar();
		}
		traverse_Stack(ST);
		copy(fp,ST);
		clear_Stack(ST);
		if(ch != EOF)
		{
			ch = getchar();
		}
	}
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
//	printf("%c",p->pNext->data);
	free(p->pNext);
	p->pNext = NULL;
	ST->top = p;
}

void clear_Stack(pStack ST)
{
	ST->top = ST->bottom;
}

void traverse_Stack(pStack ST)
{
	if(ST->top == ST->bottom)
	{
		printf("栈为空!");
		exit(-1);
	}
	else
	{
		pNode p = ST->bottom->pNext;
		while(p != ST->top->pNext)
		{
			printf("%c",p->data);
			p = p->pNext;
		}
	}
	printf("\n");
}

void copy(FILE *fp,pStack ST)
{
	if(ST->top == ST->bottom)
	{
		printf("栈为空!");
		exit(-1);
	}
	else
	{
		pNode p = ST->bottom->pNext;
		while(p != ST->top->pNext)
		{
			fprintf(fp,"%c",p->data);
			p = p->pNext;
		}
	}
	fputc('\n',fp);
}