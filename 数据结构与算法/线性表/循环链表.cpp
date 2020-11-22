#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}Node,*pNode;

pNode init_struct();
pNode build_struct(pNode pTail);
void traverse_struct(pNode pTail);
pNode ListInsert(pNode pTail,int pos,int data);
void getelem_struct(pNode pTail);
void findpos_strcut(pNode pTail);
pNode merge_struct(pNode pTail,pNode pTail1);
pNode union_struct(pNode pTail,pNode pTail1);
void sort_struct(pNode pTail);
void write_file(pNode pTail);
void read_file(pNode pTail);

int length_struct(pNode pTail);
bool empty(pNode pTail);

void main()
{
	int pos,data;
	pNode pTail = NULL,pTail1 = NULL;
	pTail = init_struct();
	pTail = build_struct(pTail);

//	printf("请输入要插入的节点位置 pos = ");
//	scanf("%d",&pos);
//	printf("请输入要插入的节点数值 val = ");
//	scanf("%d",&data);
//	pTail = ListInsert(pTail,pos,data);
//	getelem_struct(pTail);
//	findpos_strcut(pTail);
	pTail1 = init_struct();
	pTail1 = build_struct(pTail1);
//	merge_struct(pTail,pTail1);
    pTail = union_struct(pTail,pTail1);
	sort_struct(pTail);
	write_file(pTail);
	read_file(pTail);
	traverse_struct(pTail);
}

pNode init_struct()
{
	pNode pTail = (pNode)malloc(sizeof(Node));
	if(pTail == NULL)
	{
		printf("尾指针建立失败!\n");
		exit(-1);
	}
	else
	{
		pTail->pNext = pTail;
	}
	return pTail;
}

pNode build_struct(pNode pTail)
{
	int len;
	printf("请输入建立节点的个数 len = ");
	scanf("%d",&len);
	for(int i=0;i<len;i++)
	{
		pNode pNew = (pNode)malloc(sizeof(Node));
		printf("请输入新建节点的值 val = ");
		scanf("%d",&pNew->data);
		if(pNew == NULL)
		{
			printf("新表建立失败!\n");
			exit(-1);
		}
		else
		{
			pNew->pNext = pTail->pNext;
			pTail->pNext = pNew;
			pTail = pNew;
		}
	}
	return pTail;
}

pNode ListInsert(pNode pTail,int pos,int data)
{
	int j=0;
	if(pos<1||pos>length_struct(pTail)+2)
	{
		printf("超出插入范围!");
		exit(-1);
	}
	else
	{
		if(pos<=length_struct(pTail)+1 && pos>=1)
		{
			pNode p = pTail->pNext;
			while(j<pos-1)
			{
				p = p->pNext;
				j++;
			}
			pNode pNew = (pNode)malloc(sizeof(Node));
			pNew->data = data;
			pNew->pNext = p->pNext;
			p->pNext = pNew;
		}
		else
		{
			pNode pNew = (pNode)malloc(sizeof(Node));
			pNew->data = data;
			pNew->pNext = pTail->pNext;
			pTail->pNext = pNew;
			pTail = pNew;
		}
	}
	return pTail;
}

void getelem_struct(pNode pTail)
{
	int pos,j=0;
	pNode p = pTail->pNext;
	printf("请输入要查找的节点位置 pos = ");
	scanf("%d",&pos);
	if(pos<1||pos>length_struct(pTail)+1)
	{
		printf("超出插入范围!");
		exit(-1);
	}
	else
	{
		while(j<pos)
		{
			p = p->pNext;
			j++;
		}
		printf("查找结点的数值为 val = %d\n",p->data);
	}
}

void findpos_strcut(pNode pTail)
{
	int elemval,j=1;
	pNode p = pTail->pNext,q = p->pNext;
	printf("请输入要查找的数值 elemval = ");
	scanf("%d",&elemval);
	while(p != pTail && elemval != q->data )
	{
		p = p->pNext;
		q = p->pNext;
		j++;
	}
	if(p == pTail)
	{
		printf("不存在要查找的数值!\n");
		exit(-1);
	}
	else
	{
		printf("要查找数字的位置为 pos = %d\n",j);
	}
}

pNode merge_struct(pNode pTail,pNode pTail1)
{
	pNode q = pTail1->pNext;
	pTail1->pNext = pTail->pNext->pNext;
	pTail->pNext->pNext = q->pNext;
	free(q);
	pTail = pTail1;
	return pTail;
}

pNode union_struct(pNode pTail,pNode pTail1)
{
	printf("->%d\n",length_struct(pTail1));
	pNode p1 = pTail1->pNext->pNext;
	for(int i=1;i<=length_struct(pTail1)+1;i++)
	{
		int j=1;
		pNode p = pTail->pNext,q = p->pNext;
		while(p != pTail && p1->data != q->data)
		{
			p = p->pNext;
			q = p->pNext;
			j++;
		}
		printf("%d \n",j);
		if(j>length_struct(pTail)+1)
		{
			pTail = ListInsert(pTail,length_struct(pTail)+2,p1->data);
		}
		p1 = p1->pNext;
	}
	return pTail;
}

void sort_struct(pNode pTail)
{
	int swap;
	for(int i=0;i<length_struct(pTail);i++)
	{
		pNode p = pTail->pNext->pNext;
		for(int j=0;j<length_struct(pTail)-i;j++)
		{
			if(p->data > p->pNext->data)
			{
				swap = p->data;
				p->data = p->pNext->data;
				p->pNext->data = swap;
			}
			p = p->pNext;
		}
	}
}

void write_file(pNode pTail)
{
	FILE *fp;

	if((fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/text.txt","w+")) == NULL)
	{
		printf("文件打开失败!\n");
		exit(-1);
	}
	else
	{
		pNode p = pTail->pNext,q = p->pNext;
		fprintf(fp,"%d\n",length_struct(pTail)+1);
		do
		{
			fprintf(fp,"%d\n",q->data);
			p = p->pNext;
			q = p->pNext;
		}while(p != pTail);
		fclose(fp);
	}
}

void read_file(pNode pTail)
{
	FILE *fp;

	if((fp = fopen("D:/VC++6.0【win10可用】/VC++6.0/MyProjects/text.txt","r")) == NULL)
	{
		printf("文件打开失败!\n");
		exit(-1);
	}
	else
	{
		int data,total;
		fscanf(fp,"%d",&total);
		printf("文件中数字总数为: %d\n",total);
		for(int i=0;i<length_struct(pTail)+1;i++)
		{
			fscanf(fp,"%d",&data);
			printf("%d\n",data);
		}
	}
}

void traverse_struct(pNode pTail)
{
	if(empty(pTail))
	{
		printf("链表为空!\n");
		exit(-1);
	}
	else
	{
		pNode p = pTail->pNext->pNext;
		for(int i=0;i<length_struct(pTail)+1;i++)
		{
			printf("%d ",p->data);
			p = p->pNext;
		}
	}
}

int length_struct(pNode pTail)
{
	int i=0;
	pNode p = pTail->pNext;
	while(p->pNext != pTail)
	{
		i++;
		p = p->pNext;
	}
	return i;
}

bool empty(pNode pTail)
{
	if(pTail->pNext == pTail)
	{
		return true;
	}
	else
	{
		return false;
	}
}
