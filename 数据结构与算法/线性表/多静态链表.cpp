#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct
{
	int num;
	int cur;
}component,SLinklist[MAXSIZE];

void init_space(SLinklist L);
int init_list(SLinklist L);
int malloc(SLinklist L);
void insert_list(SLinklist L,int n,int i,int e);
bool empty_list(SLinklist L,int n);
int length_list(SLinklist L,int n);
void claer_list(SLinklist L,int n);
void traverse_list(SLinklist L,int n);
void get_listelem(SLinklist L,int n,int pos);
void delete_listelem(SLinklist L,int n,int pos);
void free(SLinklist L,int n);
void union_list(SLinklist L,int La,int Lb,int Lc);
bool cmp_list(SLinklist L,int Lb_num,int La);
void merge_list(SLinklist L,int La,int Lb,int Lc);
void sort_list(SLinklist L,int n);
void write_list(SLinklist L,int n);
void read_list(SLinklist L,int n);

void main()
{
	int get_pos,delete_pos,insert_num;
	SLinklist L;
	init_space(L);
	int La = init_list(L);
	int Lb = init_list(L);
	int Lc = init_list(L);
	
	printf("La表是否为空?%d(1:空 0:否)\n",empty_list(L,La));
	printf("La表的表长=%d\n",length_list(L,La));
	for(int j=1;j<=5;j++)
	{
		printf("请输入%d插入的数 insert_num =",j);
		scanf("%d",&insert_num);
		insert_list(L,La,j,insert_num);
	}
	printf("在空表La的表头依次插入1~5后 La:");
	traverse_list(L,La);
	
	printf("Lb表是否为空?%d(1:空 0:否)\n",empty_list(L,Lb));
	printf("Lb表的表长=%d\n",length_list(L,Lb));
	for(j=1;j<=5;j++)
	{	
		printf("请输入%d插入的数 insert_num =",j);
		scanf("%d",&insert_num);
		insert_list(L,Lb,j,insert_num);
	}
	printf("在空表Lb的表尾一次插入1~5后 Lb=");
	traverse_list(L,Lb);
	
//	claer_list(L,La);
//	printf("清空La后 La = ");
//	traverse_list(L,La);
//	printf("La表是否为空?%d(1:空 0:否)\n",empty_list(L,La));
//	printf("La表的表长=%d\n",length_list(L,La));

	do
	{
		printf("请输入要得到表的编号 get_pos =");
		scanf("%d",&get_pos);
	}while(get_pos<1||get_pos>length_list(L,Lb)+1);
	get_listelem(L,Lb,get_pos);

	do
	{
		printf("请输入要得到表的编号 delete_pos =");
		scanf("%d",&delete_pos);
	}while(delete_pos<1||delete_pos>length_list(L,Lb)+1);
	delete_listelem(L,Lb,delete_pos);

	traverse_list(L,Lb);

	printf("Lc表是否为空?%d(1:空 0:否)\n",empty_list(L,Lc));
	printf("Lc表的表长=%d\n",length_list(L,Lc));
//	union_list(L,La,Lb,Lc);
	merge_list(L,La,Lb,Lc);

	sort_list(L,Lc);

	write_list(L,Lc);

	read_list(L,Lc);

	traverse_list(L,Lc);
}

void init_space(SLinklist L)
{
	for(int i=0;i<MAXSIZE-1;i++)
	{
		L[i].cur = i+1;
	}
	L[MAXSIZE-1].cur = 0;
}

int init_list(SLinklist L)
{
	int j = malloc(L);
	L[j].cur = 0;
	return j;
}

int malloc(SLinklist L)
{
	int i = L[0].cur;
	L[0].cur = L[i].cur;
	return i;
}

void free(SLinklist L,int n)
{
	L[n].cur = L[0].cur;
	L[0].cur = n;
}

bool empty_list(SLinklist L,int n)
{
	if(L[n].cur == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int length_list(SLinklist L,int n)
{
	int i=0;
	while(L[n].cur != 0)
	{
		n = L[n].cur;
		i++;
	}
	return i;
}

void insert_list(SLinklist L,int n,int i,int e)
{
	int j,w,k=n;
	if(i<1||i>length_list(L,n)+1)
	{
		printf("插入不在范围!");
		exit(-1);
	}
	else
	{
		j = malloc(L);
		if(j)
		{
			L[j].num = e;
			for(w=1;w<i;w++)
			{
				k = L[k].cur;
			}
			L[j].cur = L[k].cur;
			L[k].cur = j;
		}
	}
}

void traverse_list(SLinklist L,int n)
{
	int i = L[n].cur;
	while(i)
	{
		printf("%d ",L[i].num);
		i = L[i].cur;
	}
	printf("\n");
}

void get_listelem(SLinklist L,int n,int pos)
{
	if(empty_list(L,n))
	{
		printf("\n链表为空!");
		exit(-1);
	}
	else
	{
		for(int i=0;i<pos;i++)
		{
			n = L[n].cur;
		}
		printf("编号对应的数字为 num = %d\n",L[n].num);
	}
}

void delete_listelem(SLinklist L,int n,int pos)
{
	int k;
	if(empty_list(L,n))
	{
		printf("\n链表为空!");
		exit(-1);
	}
	else
	{
		for(int i=0;i<pos-1;i++)
		{
			n = L[n].cur;
		}
		k = L[n].cur;
		L[n].cur = L[k].cur;
		free(L,k);
	}
}

void union_list(SLinklist L,int La,int Lb,int Lc)
{
	int insert_num,n=La,m=Lb;
	for(int i=1;i<length_list(L,La)+1;i++)
	{
		n = L[n].cur;
		insert_list(L,Lc,i,L[n].num);
	}
	for(i=1;i<length_list(L,Lb)+1;i++)
	{	
		m = L[m].cur;
		if(cmp_list(L,L[m].num,La))
		{
			insert_list(L,Lc,1,L[m].num);
		}
	}
}

void merge_list(SLinklist L,int La,int Lb,int Lc)
{
	int insert_num,n=La,m=Lb;
	for(int i=1;i<length_list(L,La)+1;i++)
	{
		n = L[n].cur;
		insert_list(L,Lc,i,L[n].num);
	}
	for(i=1;i<length_list(L,Lb)+1;i++)
	{
		m = L[m].cur;
		insert_list(L,Lc,1,L[m].num);
	}
}

void sort_list(SLinklist L,int n)
{
	int k,w;
	for(int i=0;i<length_list(L,n)-1;i++)
	{
		int m = n;
		do
		{
			if(L[m].num > L[L[m].cur].num)
			{
				w = L[m].num;
				L[m].num = L[L[m].cur].num;
				L[L[m].cur].num = w;
			}
			m = L[m].cur;
		}while(L[m].cur != 0);
	}
}

bool cmp_list(SLinklist L,int Lb_num,int La)
{
	int n = L[La].cur,i=0;
	while(L[n].num != Lb_num && i<length_list(L,La)+1)
	{
		n = L[n].cur;
		i++;
	}
	if(i>=length_list(L,La)+1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void write_list(SLinklist L,int n)
{
	FILE *fp;
	int k = n;
	if((fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/静态链表/text.txt","w+")) == NULL)
	{
		printf("文件打开失败!\n");
		exit(-1);
	}
	else
	{
		n = L[n].cur;
		for(int i=1;i<length_list(L,k)+1;i++)
		{
			printf("向文档里插入的数字为%d\n",L[n].num);
			fprintf(fp,"%d\n",L[n].num);
			n = L[n].cur;
		}
	}
	fclose(fp);
}

void read_list(SLinklist L,int n)
{
	FILE *fp;
	int k = n , num;
	if((fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/静态链表/text.txt","r")) == NULL)
	{
		printf("文件打开失败!\n");
		exit(-1);
	}
	else
	{
		for(int i=1;i<length_list(L,k)+1;i++)
		{
			fscanf(fp,"%d",&num);
			printf("->%d",num);
		}
		printf("\n");
	}
}

void claer_list(SLinklist L,int n)
{
	int j,k,i=L[n].cur;
	L[n].cur = 0;
	k = L[0].cur;
	L[0].cur = i;
	while(i)
	{
		j = i;
		i = L[i].cur;
	}
	L[j].cur = k;
	printf("\n");
}