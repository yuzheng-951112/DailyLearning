#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAXLENGTH 25

typedef int Maze_Type[MAXLENGTH][MAXLENGTH];
Maze_Type m;
int curstep = 1;

struct Pos
{
	int x;
	int y;
};

struct maze_elem
{
	int ord;
	struct Pos seat;
	int di;
};

typedef struct Node
{
	struct Node *pNext;
	struct maze_elem data;
}Node,*pNode;

typedef struct stack
{
	pNode bottom;
	pNode top;
}Stack,*pStack;

void init_Stack(pStack ST);
void push_Stack(pStack ST,struct maze_elem push_num);
struct maze_elem pop_Stack(pStack ST);
void printf_maze(int x,int y);
bool MazePath(struct Pos begin,struct Pos end);
bool empty(pStack ST);
bool Pass(struct Pos cerpos);
void FootPrint(struct Pos curpos);
struct Pos NextPos(struct Pos curpos,int di);
void MarkPrint(struct Pos seat);

void main()
{
	int i,j,x,y,x1,y1;
	struct Pos begin,end; 

	printf("请输入迷宫的行数,列数(包括外墙):");
	scanf("%d,%d",&x,&y);
	for(i=0;i<x;i++)
	{
		m[0][i] = 0;
		m[x-1][i] = 0;
	}
	for(j=i;j<y-1;j++)
	{
		m[j][0] = 0;
		m[j][y-1] = 0;
	}
	for(i=1;i<x-1;i++)
	{
		for(j=1;j<y-1;j++)
		{
			m[i][j] = 1;
		}
	}
	printf("请输入迷宫内墙元素:");
	scanf("%d",&j);
	printf("请依次输入迷宫内墙每个单元的行数,列数:\n");
	for(i=1;i<=j;i++)
	{
		scanf("%d,%d",&x1,&y1);
		m[x1][y1] = 0;
	}
	printf("迷宫结构如下!\n");
	printf_maze(x,y);
	printf("请输入起点的行数,列数:");
	scanf("%d,%d",&begin.x,&begin.y);
	printf("请输入重点的行数,列数:");
	scanf("%d,%d",&end.x,&end.y);
	if(MazePath(begin,end))
	{
		printf("此迷宫从入口到出口的一条路径如下\n");
		printf_maze(x,y);
	}
	else
	{
		printf("此迷宫没有从入口到出口的路径\n");
	}
}

void printf_maze(int x,int y)
{
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			printf("%d  ",m[i][j]);
		}
		printf("\n");
	}
}

bool MazePath(struct Pos begin,struct Pos end)
{
	struct maze_elem elem;
	pStack ST = (pStack)malloc(sizeof(Stack));
	init_Stack(ST);
	Pos curpos;
	curpos = begin;
	do
	{
		if(Pass(curpos))
		{
			FootPrint(curpos);
			elem.ord = curstep;
			elem.seat.x = curpos.x;
			elem.seat.y = curpos.y;
			elem.di = 0;
			push_Stack(ST,elem);
			curstep++;
			if(curpos.x == end.x && curpos.y == end.y)
				return true;
			curpos = NextPos(curpos,elem.di);
		}
		else
		{
			if(!empty(ST))
			{
				elem = pop_Stack(ST);
				curpos.x = elem.seat.x;
				curpos.y = elem.seat.y;
				curstep--;
				while(elem.di == 3 && !empty(ST))
				{
					MarkPrint(elem.seat);
					elem = pop_Stack(ST);
					curstep--;
				}
				if(elem.di<3)
				{
					elem.di++;
					push_Stack(ST,elem);
					curstep++;
					curpos = NextPos(curpos,elem.di);
				}
			}
		}
	}while(!empty(ST));
	return false;
}

bool Pass(struct Pos cerpos)
{
	if(m[cerpos.x][cerpos.y] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FootPrint(struct Pos curpos)
{
	m[curpos.x][curpos.y] = curstep;
}

void MarkPrint(struct Pos seat)
{
	m[seat.x][seat.y] = -1;
}

struct Pos NextPos(struct Pos curpos,int di)
{
	struct Pos direc[4] = {{0,1},{1,0},{0,-1},{-1,0}}; //代表东西南北
	curpos.x = curpos.x + direc[di].x;
	curpos.y = curpos.y + direc[di].y;
	return curpos;
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

void push_Stack(pStack ST,struct maze_elem push_num)
{
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->data = push_num;
	ST->top->pNext = pNew;
	pNew->pNext = NULL;
	ST->top = pNew;
}

struct maze_elem pop_Stack(pStack ST)
{
	struct maze_elem e;
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