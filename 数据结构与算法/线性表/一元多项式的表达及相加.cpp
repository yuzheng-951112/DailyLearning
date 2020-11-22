#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

typedef struct DataType
{
	float coef;
	int expn;
}elemType;

typedef struct List
{
	struct DataType data;
	struct List *pPrior;
	struct List *pNext;
}List,*pList;

pList init_List();
void create_List(pList pHead);
int length_List(pList pHead);
void traverse_List(pList pHead);
double getvalue_List(pList pHead);
void clear_List(pList pHead);
void lastadd_List(pList pHead,float coef,int expn);
void delete_List(pList pHead,int pos);
void add_List(pList pHead,pList pHead1);
void sub_List(pList pHead,pList pHead1);
void mul_List(pList pHead,pList pHead1);
void div_List(pList pHead,pList pHead1);

bool empty(pList pHead);

void main()
{
	int m,expn,pos,i;
	float coef;
	pList pHead = NULL,pHead1 = NULL;
	pHead = init_List();
	create_List(pHead);
	pHead1 = init_List();
	create_List(pHead1);
/*
	printf("请输入插入last的系数和指数:");
	scanf("%f %d",&coef,&expn);
	lastadd_List(pHead,coef,expn);
	traverse_List(pHead);

	printf("请输入要删除数字的位置 pos=");
	scanf("%d",&pos);
	delete_List(pHead,pos);
	traverse_List(pHead);

	add_List(pHead,pHead1);
	sub_List(pHead,pHead1);*/
	mul_List(pHead,pHead1);
//	div_List(pHead,pHead1);
}

pList init_List()
{
	pList pHead = (pList)malloc(sizeof(List));
	if(pHead == NULL)
	{
		printf("建表失败!\n");
		exit(-1);
	}
	else
	{
		pHead->pNext = pHead;
		pHead->pPrior = pHead;
	}
	return pHead;
}

void create_List(pList pHead)
{
	float coef;
	int m,expn;
	pList ptemp = pHead;
	printf("请输入多项式的项数:");
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		pList pNew = (pList)malloc(sizeof(List));
		printf("请输入第%d的系数和指数:",i+1);
		scanf("%f %d",&coef,&expn);
		pNew->data.coef = coef;
		pNew->data.expn = expn;
		ptemp->pNext = pNew;
		pNew->pNext = pHead;
		pNew->pPrior = ptemp;
		ptemp = pNew;
	}
	pHead->pPrior = ptemp;
}

int length_List(pList pHead)
{
	int i = 1;
	pList p = pHead->pNext;
	while(p != pHead->pPrior)
	{
		p = p->pNext;
		i++;
	}
	return i;
}

void traverse_List(pList pHead)
{
	if(empty(pHead))
	{
		printf("多项式为空!");
		exit(-1);
	}
	else
	{
		pList p = pHead->pNext;
		for(int i=0;i<length_List(pHead);i++)
		{
			if(p->data.coef>=0)
			{
				printf("%.2f*x^%d",p->data.coef,p->data.expn);
			}
			else
			{
				printf("(%.2f)*x^%d",p->data.coef,p->data.expn);
			}
			p = p->pNext;
			if(i != length_List(pHead)-1)
			{
				printf("+");
			}
		}
	}
}

double getvalue_List(pList pHead)
{
	double sum = 0;
	double x;
	printf("\n");
	pList p = pHead->pNext;
	for(int i=0;i<length_List(pHead);i++)
	{
		printf("请输入带入参数x = ");
		scanf("%lf",&x);
		sum = sum + p->data.coef*pow(x,p->data.expn);
		p = p->pNext;
	}
	return sum;
}

void add_List(pList pHead,pList pHead1)
{
	pList p1 = pHead1->pNext;
	while(p1 != pHead1)
	{
		pList p = pHead->pNext,q;
		while(p != pHead && p->data.expn != p1->data.expn)
		{
			p = p->pNext;
		}
		q = p1->pNext;
		if(p->data.expn == p1->data.expn)
		{
			p->data.coef = p->data.coef + p1->data.coef;
		}
		else
		{
			lastadd_List(pHead,p1->data.coef,p1->data.expn);
		}
		free(p1);
		p1 = q;
	}
	traverse_List(pHead);
	printf("%lf",getvalue_List(pHead));
}

void sub_List(pList pHead,pList pHead1)
{
	pList p1 = pHead1->pNext;
	while(p1 != pHead1)
	{
		pList p = pHead->pNext,q;
		while(p != pHead && p->data.expn != p1->data.expn)
		{
			p = p->pNext;
		}
		q = p1->pNext;
		if(p->data.expn == p1->data.expn)
		{
			p->data.coef = p->data.coef - p1->data.coef;
		}
		else
		{
			lastadd_List(pHead,-(p1->data.coef),p1->data.expn);
		}
		free(p1);
		p1 = q;
	}
	traverse_List(pHead);
	printf("%lf",getvalue_List(pHead));
}

void mul_List(pList pHead,pList pHead1)
{
	double sum;
	float coef;
	int expn;
	printf("[");
	traverse_List(pHead);
	printf("]*[");
	traverse_List(pHead);
	printf("]");
	printf("=");

	int i=0;
	pList pHead2;
	pHead2 = init_List();
//	create_List(pHead2);
	pList p1 = pHead1->pNext,p2;
	while(p1 != pHead1)
	{
		pList p = pHead->pNext,q;
		while(p != pHead)
		{
			coef = p->data.coef*p1->data.coef;
			expn = p->data.expn+p1->data.expn;
			p2 = pHead2->pNext;
			while(i<length_List(pHead2) && p2->data.expn != expn)
			{
				p2 = p2->pNext;
				i++;
			}
			if(expn == p2->data.expn)
			{
				p2->data.coef = p2->data.coef + coef;
			}
			else
			{
				lastadd_List(pHead2,coef,expn);
			}
			p = p->pNext;
		}
		q = p1->pNext;
		free(p1);
		p1 = q;
	}
	traverse_List(pHead2);
	sum = getvalue_List(pHead2);
	printf("%lf",sum);
}

void div_List(pList pHead,pList pHead1)
{
	double sum;
	printf("[");
	traverse_List(pHead);
	printf("]/[");
	traverse_List(pHead);
	printf("]");
	sum = getvalue_List(pHead)*getvalue_List(pHead1);
	printf("%lf",sum);
}

void lastadd_List(pList pHead,float coef,int expn)
{
	pList p = pHead->pPrior;
	pList pNew = (pList)malloc(sizeof(List));
	pNew->data.coef = coef;
	pNew->data.expn = expn;
	p->pNext = pNew;
	pNew->pPrior = p;
	pNew->pNext = pHead;
	pHead->pPrior = pNew;
}

void clear_List(pList pHead)
{
	pList p = pHead->pNext,q;
	while(p->pNext != pHead)
	{
		q = p->pNext;
		free(p);
		p = q;
	}
}

void delete_List(pList pHead,int pos)
{
	if(pos<1 || pos>length_List(pHead))
	{
		printf("删除不在范围!");
		exit(-1);
	}
	else
	{
		int i=1;
		pList p = pHead->pNext;
		while(i<pos-1)
		{
			i++;
			p = p->pNext;
		}
		pList q = p->pNext;
		p->pNext = q->pNext;
		q->pNext->pPrior = p;
		free(q);
	}
}

bool empty(pList pHead)
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