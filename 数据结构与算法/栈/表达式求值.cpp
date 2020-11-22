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
bool IN(char c);
char Precede(char x,char c);
char GetTop_Stack(pStack ST);
char Operate(char a,char theta,char b);

void main()
{
	pStack OPTR	= (pStack)malloc(sizeof(Stack)),
		   OPND = (pStack)malloc(sizeof(Stack));			//OPTR、OPNd分别用来寄存运算符号和运算数
	char a,b,c,x,theta;
	init_Stack(OPTR);
	push_Stack(OPTR,'#');		//
	init_Stack(OPND);
	c = getchar();
	x = GetTop_Stack(OPTR);
	while(c != '#' || x != '#')
	{
		if(IN(c))				//IN(c)判断c是否为符号数
		{
			switch(Precede(x,c))
			{
			case'<':push_Stack(OPTR,c);
					if(c != '#')
					{
						c = getchar();
					}
					break;
			case'=':x = pop_Stack(OPTR);
					if(c != '#')
					{
						c = getchar();
					}
					break;
			case'>':theta = pop_Stack(OPTR);
					b = pop_Stack(OPND);
					a = pop_Stack(OPND);
					push_Stack(OPND,Operate(a,theta,b));
					break;
			}
		}
		else if(c > '0' && c <= '9')
		{
			push_Stack(OPND,c);
			c = getchar();
		}
		else
		{
			printf("错误四");
			exit(-1);
		}
		x = GetTop_Stack(OPTR);
	}
	printf("%c",GetTop_Stack(OPND));
}

char Operate(char a,char theta,char b)
{
	char sum;
	a = a - 48;
	b = b - 48;
	switch(theta)
	{
	case'+':sum = a + b + 48;
			break;
	case'-':sum = a - b + 48;
			break;
	case'*':sum = a * b + 48;
			break;
	case'/':sum = a / b + 48;
			break;
	}
	return sum;
}

char Precede(char x,char c)
{
	char f;
	switch(c)
	{
	case'+':
	case'-':if(x == '(' || x == '#')	//'+' '-'的优先级高于'(' '#'
				f = '<';
			else
				f = '>';
			break;
	case'*':
	case'/':if(x == '*' || x == '/' || x == ')')							//'*' '/'的优先级低于'(' 和本身
				f = '>';
			else
				f = '<';
			break;
	case'(':if(x == ')')
			{
				printf("错误一");
				exit(-1);
			}
			else
			{
				f = '<';
			}
			break;
	case')':switch(x)
			{
			case'(':f = '=';
			break;
			case'#':printf("错误二");
			break;
			default:f = '>';
			}
			break;
	case'#':switch(x)
			{
			case'(':printf("错误三");
					exit(-1);
			case'#':f = '=';
					break;
			default:f = '>';
			}
			break;
	}
	return f;
}

bool IN(char c)
{
	switch(c)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'(':
	case')':
	case'#':return true;
	default:return false;
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

char GetTop_Stack(pStack ST)
{
	char e;
	pNode p = ST->bottom;
	while(p->pNext != ST->top)
	{
		p = p->pNext;
	}
	e = p->pNext->data;
	return e;
}