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
char pop_Stack(pStack ST);
void traverse_Stack(pStack ST);
bool empty(pStack ST);

void main()
{
	char str[80],*p,e;
	pStack ST = (pStack)malloc(sizeof(Stack));
	if(ST == NULL)
	{
		printf("�ڴ����ʧ��!");
		exit(-1);
	}
	init_Stack(ST);
	p = gets(str);
	while(*p)
	{	
		switch(*p)
		{
		case '(':push_Stack(ST,*p);
				p++;
				break;
		case ')':if(ST->bottom != ST->top)
				{
					e = pop_Stack(ST);
					if(e == '(')
					{
						printf("����С����ƥ��ɹ�!\n");
					}
					else
					{
						printf("����С����ƥ��ʧ��!\n");
						push_Stack(ST,e);
					}
				}
				else
				{
					printf("����С����ƥ��ʧ��!\n");
				}
				p++;
				break;
		case '[':push_Stack(ST,*p);
				p++;
				break;
		case ']':if(ST->bottom != ST->top)
				{
					e = pop_Stack(ST);
					if(e == '[')
					{
						printf("����������ƥ��ɹ�!\n");
					}
					else
					{
						printf("����������ƥ��ʧ��!\n");
						push_Stack(ST,e);
					}
				}
				else
				{
					printf("����������ƥ��ʧ��!\n");
				}
				p++;
				break;
		case '{':push_Stack(ST,*p);
				p++;
				break;
		case '}':if(ST->bottom != ST->top)
				{
					e = pop_Stack(ST);
					if(e == '{')
					{
						printf("���Ҵ�����ƥ��ɹ�!\n");
					}
					else
					{
						printf("���Ҵ�����ƥ��ʧ��!\n");
						push_Stack(ST,e);
					}
				}
				else
				{
					printf("���Ҵ�����ƥ��ʧ��!\n");
				}
				p++;
				break;
		default:p++;
				break;
		}
	}
	if(ST->bottom != ST->top)
	{	
		e = pop_Stack(ST);
		if(e == '(' || e == '[' || e == '{')
		{
			printf("ƥ��ʧ��!\n");
		}
	}
}

void init_Stack(pStack ST)
{
	pNode pStack_Head = (pNode)malloc(sizeof(Node));
	if(pStack_Head == NULL)
	{
		printf("�����ڴ�ʧ��!");
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

char pop_Stack(pStack ST)
{
	char e;
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

void traverse_Stack(pStack ST)
{
	if(ST->bottom == ST->top)
	{
		printf("ջΪ��!");
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