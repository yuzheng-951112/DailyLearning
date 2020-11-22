#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* pNext;
}Node,*pNode;

struct LinkList
{
	int len;
	struct Node* pNodeHead;
	struct Node* pNodeTail;
};

struct LinkList* init_struct();
void build_list(LinkList* pHead);
void traverse_list(LinkList* pHead);
int length_list(LinkList* pHead);
void insert_list(LinkList* pHead,int pos,int elem);
void delete_list(LinkList* pHead,int pos);
void clear_list(LinkList* pHead);
void findelem_list(LinkList* pHead,int pos);
void findpos_list(LinkList* pHead,int elem);
void merge_list(LinkList* pHead,LinkList* pHead1);
void union_list(LinkList* pHead,LinkList* pHead1);
void write_list(LinkList* pHead);
void read_list(LinkList* pHead);

bool empty(LinkList* pHead);

void main()
{
	int insert_pos,insert_elem,delete_pos,delete_elem,find_pos,find_elem;
	LinkList *pHead,*pHead1;
	pHead = init_struct();
//	pHead1 = init_struct();
	build_list(pHead);
//	build_list(pHead1);
/*
	printf("请输入要插入数的位置:");
	scanf("%d",&insert_pos);
	printf("请输入要插入数的数值:");
	scanf("%d",&insert_elem);
	insert_list(pHead,insert_pos,insert_elem);

	printf("请输入要删除数的位置:");
	scanf("%d",&delete_pos);
	delete_list(pHead,delete_pos);

	printf("请输入要找的位置:");
	scanf("%d",&find_pos);
	findelem_list(pHead,find_pos);
	
	printf("请输入要找的数字:");
	scanf("%d",&find_elem);
	findpos_list(pHead,find_elem);
*/

//	merge_list(pHead,pHead1);
//	union_list(pHead,pHead1);

//	clear_list(pHead);

	write_list(pHead);
	read_list(pHead);

//	traverse_list(pHead);
}

struct LinkList* init_struct()
{
	LinkList* TempPhead = (LinkList*)malloc(sizeof(LinkList));
	pNode pfirst = (pNode)malloc(sizeof(Node));
	if(TempPhead == NULL || pfirst == NULL)
	{
		printf("表头类型失败!\n");
		exit(-1);
	}
	else
	{
		TempPhead->pNodeHead = pfirst;
		TempPhead->pNodeTail = pfirst;
		TempPhead->len = 0;
		pfirst->pNext = NULL;
	}
	return TempPhead;
}

void build_list(LinkList* pHead)
{
	int len,num;
	printf("请输入要建立链表的长度:");
	scanf("%d",&len);
	pNode p = pHead->pNodeHead;
	for(int i=0;i<len;i++)
	{
		pNode pNew = (pNode)malloc(sizeof(Node));
		if(pNew == NULL)
		{
			printf("链表建立失败!\n");
			exit(-1);
		}
		else
		{
			printf("请输入插入的数:");
			scanf("%d",&num);
			pNew->data = num;
			pNew->pNext = NULL;
			p->pNext = pNew;
			pHead->pNodeTail = pNew;
		}
		p = pNew;
	}
	pHead->len = len;
}

void insert_list(LinkList* pHead,int pos,int elem)
{
	if(pos<1 && pos>length_list(pHead)+1)
	{
		printf("插入超出范围!\n");
		exit(-1);
	}
	else
	{
		int j=0;
		pNode p = pHead->pNodeHead;
		while(j<pos-1)
		{
			p = p->pNext;
			j++;
		}
		pNode pNew = (pNode)malloc(sizeof(Node));
		pNew->data = elem;
		pNew->pNext = p->pNext;
		p->pNext = pNew;
		if(p == pHead->pNodeTail)
		{
			pHead->pNodeTail = pNew;
		}
		pHead->len++;
	}
}

void delete_list(LinkList* pHead,int pos)
{
	if(pos<1 && pos>length_list(pHead))
	{
		printf("删除超出范围!\n");
		exit(-1);
	}
	else
	{
		int j=0;
		pNode p = pHead->pNodeHead;
		while(j<pos-1)
		{
			p = p->pNext;
			j++;
		}
		pNode q = p->pNext;
		p->pNext = p->pNext->pNext;
		free(q);
		pHead->len--;
	}	
}

void clear_list(LinkList* pHead)
{
	if(empty(pHead))
	{
		printf("链表为空!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNodeHead->pNext;
		pNode q = p;
		while(p)
		{
			p = p->pNext;
			free(q);
			q = p;
		}
		pHead->pNodeTail = pHead->pNodeHead;
		pHead->len = 0;
	}
}

void findelem_list(LinkList* pHead,int pos)
{
	pNode p = pHead->pNodeHead->pNext;
	for(int i=1;i<pos;i++)
	{
		p = p->pNext;
	}
	printf("第%d位置的数是%d\n",pos,p->data);
}

void findpos_list(LinkList* pHead,int elem)
{
	pNode p = pHead->pNodeHead->pNext;
	int j = 1;
	while(p && p->data != elem)
	{
		p = p->pNext;
		j++;
	}
	printf("要找的数字的位置为%d:\n",j);
}

void merge_list(LinkList* pHead,LinkList* pHead1)
{
	pHead->pNodeTail->pNext = pHead1->pNodeHead->pNext;
	pHead->pNodeTail = pHead1->pNodeTail;
	pHead->len = pHead->len + pHead1->len;
	free(pHead1->pNodeHead);
	free(pHead1);
}

void union_list(LinkList* pHead,LinkList* pHead1)
{
	pNode p1 = pHead1->pNodeHead->pNext;
	while(p1)
	{
		pNode p = pHead->pNodeHead->pNext;
		while(p && p->data != p1->data)
		{
			p = p->pNext;
		}
		if(p == NULL)
		{
			insert_list(pHead,length_list(pHead)+1,p1->data);
		}
		p1 = p1->pNext;
	}
}

void write_list(LinkList* pHead)
{
	FILE *fp;

	if((fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/text.txt","w+")) == NULL)
	{
		printf("文件代开失败!\n");
		exit(-1);
	}
	else
	{
		fprintf(fp,"%d\n",pHead->len);
		pNode p = pHead->pNodeHead->pNext;
		for(int i=0;i<pHead->len;i++)
		{
			fprintf(fp,"%d\n",p->data);
			p = p->pNext;
		}
		fclose(fp);
	}
}

void read_list(LinkList* pHead)
{
	FILE *fp;

	if((fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/text.txt","r")) == NULL)
	{
		printf("文件代开失败!\n");
		exit(-1);
	}
	else
	{
		int total,num;
		fscanf(fp,"%d",&total);
		printf("total = %d\n",total);
		for(int i=0;i<pHead->len;i++)
		{
			fscanf(fp,"%d",&num);
			printf("->%d",num);
		}
		fclose(fp);
	}
	printf("\n");
}

int length_list(LinkList* pHead)
{
	int i=1;
	pNode p = pHead->pNodeHead->pNext;
	while(p != pHead->pNodeTail)
	{
		p = p->pNext;
		i++;
	}
	return i;
}

void traverse_list(LinkList* pHead)
{
	if(empty(pHead))
	{
		printf("链表为空!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNodeHead->pNext;
		for(int i=0;i<length_list(pHead);i++)
		{
			printf("->%d",p->data);
			p = p->pNext;
		}
	}
}

bool empty(LinkList* pHead)
{
	if(pHead->pNodeHead == pHead->pNodeTail)
	{
		return true;
	}
	else
	{
		return false;
	}
}