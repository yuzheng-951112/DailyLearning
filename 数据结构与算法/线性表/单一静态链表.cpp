#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct
{
	int num;
	int cur;
}component,SLinklist[MAXSIZE];

void create_list(SLinklist L);
void init_list(SLinklist L,int len);
int length_list(SLinklist L);
int malloc_list(SLinklist L);
void insert_list(SLinklist L,int index);
void delete_list(SLinklist L,int index);
int get_list_num(SLinklist L,int index);
void sort_list_num(SLinklist L);
void traverse_list(SLinklist L);
bool empty_list(SLinklist L);
bool full_list(SLinklist L);


void main()
{
	int len,insert_index,delete_index,get_index;
	SLinklist L;
	create_list(L);

	printf("请输入要建立链表的长度 len:");
	scanf("%d",&len);
	init_list(L,len);

	traverse_list(L);

	printf("\n请输入要插入链表的位置 insert_index:");
	scanf("%d",&insert_index);
	insert_list(L,insert_index);

	traverse_list(L);

	printf("\n请输入要删除链表的位置 delete_index:");
	scanf("%d",&delete_index);
	delete_list(L,delete_index);

	sort_list_num(L);
	traverse_list(L);

	printf("\n请输入要删除链表的位置 get_index:");
	scanf("%d",&get_index);
	printf("%d",get_list_num(L,get_index));
	

}

void create_list(SLinklist L)
{
	L[MAXSIZE-1].cur = 0;
	for(int i=0;i<MAXSIZE-1;i++)
	{
		L[i].cur = i+1;
	}
}

void init_list(SLinklist L,int len)
{
	if(len<1||len>MAXSIZE-2)
	{
		printf("初始化的个数已经超过了，请从新输入len=");
		scanf("%d",&len);
	}
	for(int i=1;i<=len;i++)
	{
		scanf("%d",&L[i].num);
	}
	L[0].cur = len+1;
	L[MAXSIZE-1].cur = 1;
	L[len].cur = 0;
}

int length_list(SLinklist L)
{
	int j=0,k = L[MAXSIZE-1].cur;
	do
	{
		k = L[k].cur;
		j++;
	}while(L[k].cur);
	return j;
}

int malloc_list(SLinklist L)
{
	int k = L[0].cur;
	L[0].cur = L[k].cur;
	return k;
}

void free_list(SLinklist L,int k)
{
	L[k].cur = L[0].cur;
	L[0].cur = k;
}

void insert_list(SLinklist L,int index)
{
	if(index<1||index>length_list(L)+1)
	{
		printf("插入位置不在范围!");
		exit(-1);
	}
	else
	{
		int num,k=MAXSIZE-1;
		int j = malloc_list(L);
		printf("输入要插入的数字:");
		scanf("%d",&num);
		L[j].num = num;
		for(int i=1;i<index;i++)
		{
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;
		L[k].cur = j;
	}
}

void delete_list(SLinklist L,int index)
{
	if(index<1||index>length_list(L)+1)
	{
		printf("插入位置不在范围!");
		exit(-1);
	}
	else
	{
		int m,k=MAXSIZE-1;
		for(int i=1;i<index;i++)
		{
			k = L[k].cur;
		}
		m = L[k].cur;
		L[k].cur = L[m].cur;
		free_list(L,m);
	}
}

int get_list_num(SLinklist L,int index)
{
	if(index<1||index>length_list(L)+1)
	{
		printf("插入位置不在范围!");
		exit(-1);
	}
	else
	{
		int k=MAXSIZE-1;
		for(int i=0;i<index;i++)
		{
			k = L[k].cur;
		}
		return L[k].num;
	}
}

void sort_list_num(SLinklist L)
{
	int m,k=MAXSIZE-1;
	for(int i=0;i<length_list(L)-1;i++)
	{
		for(int j=0;j<length_list(L)-i-1;j++)
		{
			if(L[j].num>L[j+1].num)
			{
				m = L[j].num;
				L[j].num = L[j+1].num;
				L[j+1].num = m;
			}
		}
	}
}

void traverse_list(SLinklist L)
{
	int k=L[MAXSIZE-1].cur;

	if(k == 0)
	{
		printf("链表为空!\n");
		exit(-1);
	}
	else
	{
		for(int i=0;i<length_list(L)+1;i++)
		{
			printf("->%d",L[k].num);
			k = L[k].cur;
		}
	}
}

bool empty_list(SLinklist L)
{
	if(L[MAXSIZE-1].cur == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool full_list(SLinklist L)
{
	if(L[0].cur == MAXSIZE-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}