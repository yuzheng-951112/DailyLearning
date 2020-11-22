#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	struct Node* pNext;
	struct Node* pbefore;
	int data;
}Node,*pNode;

pNode init_struct();
void build_struct(pNode pHead);
void traverse_struct(pNode pHead);
int length_struct(pNode pHead);
int findpos_struct(pNode pHead,int elem);
int findelem_struct(pNode pHead,int pos);
void sort_struct(pNode pHead);
void merge_struct(pNode pHead,pNode pHead1);
void union_struct(pNode pHead,pNode pHead1);
void insert_struct(pNode pHead,int pos,int elem);
void delete_struct(pNode pHead,int pos);
void clear_struct(pNode pHead);
void write_struct(pNode pHead);
void read_struct(pNode pHead);

bool empty(pNode pHead);

void main()
{
	int findelem,pos,findpos,elem,insert_pos,insert_elem,delete_pos;
	pNode pHead = NULL;
//	pNode pHead1 = NULL;
	pHead = init_struct();
//	pHead1 = init_struct();
	build_struct(pHead);
//	build_struct(pHead1);
//	union_struct(pHead,pHead1);
//	merge_struct(pHead,pHead1);
//	sort_struct(pHead);
//	clear_struct(pHead);
	write_struct(pHead);
	read_struct(pHead);

/*
	printf("������ɾ����λ��:");
	scanf("%d",&delete_pos);
	delete_struct(pHead,delete_pos);

	printf("����������λ��:");
	scanf("%d",&insert_pos);
	printf("��������������:");
	scanf("%d",&insert_elem);
	insert_struct(pHead,insert_pos,insert_elem);

	printf("������Ҫ���ҵ�Ԫ��:");
	scanf("%d",&findelem);
	pos = findpos_struct(pHead,findelem);
	printf("��Ӧλ��Ϊ:%d\n",pos);

	printf("������Ҫ���ҵ�λ��:");
	scanf("%d",&findpos);
	elem = findelem_struct(pHead,findpos);
	printf("��ӦԪ��Ϊ:%d",elem);
*/
	traverse_struct(pHead);
}

pNode init_struct()
{
	pNode pHead = (pNode)malloc(sizeof(Node));
	if(pHead == NULL)
	{
		printf("��ͷ����ʧ��!\n");
		exit(-1);
	}
	pHead->pbefore = pHead;
	pHead->pNext = pHead;
	return pHead;
}

void build_struct(pNode pHead)
{
	int len,num;
	printf("�����뽨������ĳ��� = ");
	scanf("%d",&len);
	pNode p = pHead;
	for(int i=0;i<len;i++)
	{
		pNode pNew = (pNode)malloc(sizeof(Node));
		printf("�������½��ڵ����ֵ = ");
		scanf("%d",&num);
		pNew->data = num;
		p->pNext = pNew;
		pNew->pNext = pHead;
		pNew->pbefore = p;
		p = pNew;
		pHead->pbefore = pNew;
	}
}

int length_struct(pNode pHead)
{
	if(empty(pHead))
	{
		printf("����Ϊ��!");
		exit(-1);
	}
	else
	{
		int j = 1;
		pNode p = pHead->pNext;
		while(p->pNext != pHead)
		{
			j++;
			p = p->pNext;
		}
		return j;
	}
}

int findpos_struct(pNode pHead,int elem)
{
	if(empty(pHead))
	{
		printf("����Ϊ��,û�ж�ӦԪ��!");
		exit(-1);
	}
	else
	{
		int j = 1;
		pNode p = pHead->pNext;
		while(p != pHead && elem != p->data)
		{
			j++;
			p = p->pNext;
		}
		if(j>length_struct(pHead))
		{
			printf("û�ж�ӦԪ��!\n");
		}
		else
		{
			return j;
		}
	}
}

int findelem_struct(pNode pHead,int pos)
{
	if(empty(pHead))
	{
		printf("����Ϊ��,û�ж�ӦԪ��!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		for(int i=1;i<pos;i++)
		{
			p = p->pNext;
		}
		return p->data;
	}
}

void insert_struct(pNode pHead,int pos,int elem)
{
	if(pos<1 && pos>length_struct(pHead)+1)
	{
		printf("���벻�ڷ�Χ!\n");
		exit(-1);
	}
	else
	{
		pNode pNew = (pNode)malloc(sizeof(Node));
		pNew->data = elem;
		pNode ptemp = pHead;
		for(int i=0;i<pos-1;i++)
		{
			ptemp = ptemp->pNext;
		}
			pNew->pbefore = ptemp;
			pNew->pNext = ptemp->pNext;
			ptemp->pNext->pbefore = pNew;
			ptemp->pNext = pNew;
	}
}

void delete_struct(pNode pHead,int pos)
{
	if(pos<1 && pos>length_struct(pHead))
	{
		printf("ɾ�����ڷ�Χ!\n");
		exit(-1);
	}
	else
	{
		pNode ptemp = pHead;
		for(int i=0;i<pos-1;i++)
		{
			ptemp = ptemp->pNext;
		}
		pNode qtemp = ptemp->pNext;
		qtemp->pNext->pbefore = ptemp;
		ptemp->pNext = qtemp->pNext;
		free(qtemp);
	}
}

void clear_struct(pNode pHead)
{
	pNode q,p = pHead->pNext;
	while(p != pHead)
	{
		q = p->pNext;
		free(p);
		p = q;
	}
	pHead->pbefore = pHead;
	pHead->pNext = pHead;
}

void sort_struct(pNode pHead)
{
	int swap,i,j;
	for(i=0;i<length_struct(pHead)-1;i++)
	{
		pNode p = pHead->pNext;
		for(j=0;j<length_struct(pHead)-i-1;j++)
		{
			if(p->data > p->pNext->data)
			{
				swap = p->data;
				p->data = p->pNext->data;
				p->pNext->data = swap;
				p = p->pNext;
			}
		}
	}
}

void merge_struct(pNode pHead,pNode pHead1)
{
	pNode p = pHead->pNext;
	while(p->pNext != pHead)
	{
		p = p->pNext;
	}
	pNode p1 = pHead1->pNext;
	pNode p2 = pHead1->pbefore;
	p->pNext = p1;
	p->pbefore = p2;
	p->pbefore->pNext = pHead;
}


void union_struct(pNode pHead,pNode pHead1)
{
	pNode p1 = pHead1->pNext;
	while(p1 != pHead1)
	{
		pNode p = pHead->pNext;
		while(p != pHead && p1->data != p->data)
		{
			p = p->pNext;
		}
		if(p == pHead)
		{
			insert_struct(pHead,length_struct(pHead)+1,p1->data);
		}
		p1 = p1->pNext;
	}
}

void write_struct(pNode pHead)
{
	FILE *fp;

	if((fp = fopen("D:/VC++6.0��win10���á�/VC++6.0/MyProjects/text.txt","w+")) == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(-1);
	}
	else
	{
		fprintf(fp,"%d\n",length_struct(pHead));
		pNode p = pHead->pNext;
		for(int i=0;i<length_struct(pHead);i++)
		{
			fprintf(fp,"%d\n",p->data);
			p = p->pNext;
		}
		fclose(fp);
	}
}

void read_struct(pNode pHead)
{
	FILE *fp;

	if((fp = fopen("D:/VC++6.0��win10���á�/VC++6.0/MyProjects/text.txt","r")) == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(-1);
	}
	else
	{
		int total,num;
		fscanf(fp,"%d",&total);
		printf("������Ч�ڵ����Ϊ:%d\n",total);
		for(int i=0;i<length_struct(pHead);i++)
		{
			fscanf(fp,"%d",&num);
			printf("->%d",num);
		}
		fclose(fp);
	}
	printf("\n");
}

void traverse_struct(pNode pHead)
{
	if(empty(pHead))
	{
		printf("����Ϊ��!\n");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		do
		{
			printf("->%d",p->data);
			p = p->pNext;
		}while(p != pHead);
	}
	printf("\n");
}

bool empty(pNode pHead)
{
	if(pHead->pNext == pHead)
	{
		return true;
	}
	else
	{
		return false;
	}
}
