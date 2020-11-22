#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct OLNode
{
	int i,j;
	int e;
	struct OLNode *right,*down;
}*pOLNode;

typedef struct CrossList
{
	pOLNode *rhead,*chead;			//行和列链表头指向基地址(rhead,chead相当于数组，这里就是给头地址分配地址)
	int mu,nu,tu;
}*pCrossList;

void InitSMatrix(pCrossList);
void CreateSMatrix(pCrossList);
void DestroySMatrix(pCrossList);
void PrintSMatrix(pCrossList);
void CopySMatrix(pCrossList,pCrossList);
void AddSMatrix(pCrossList,pCrossList,pCrossList);
void SubtSMatrix(pCrossList,pCrossList,pCrossList);
void TransposeSMatrix(pCrossList,pCrossList);
void MultSMatrix(pCrossList,pCrossList,pCrossList);
void DelZero(pCrossList);

void main()
{
	CrossList A,B,C;
	InitSMatrix(&A);		//CrossList类型的变量在初次使用之前必须初始化
	InitSMatrix(&B);
/*	printf("创建矩阵A:");
	CreateSMatrix(&A);
	printf("矩阵A:\n");
	PrintSMatrix(&A);
	printf("由矩阵A复制矩阵B:\n");
	CopySMatrix(&A,&B);
	PrintSMatrix(&B);
	DestroySMatrix(&B);
	printf("销毁矩阵B后\n");
	PrintSMatrix(&B);
	printf("创建矩阵B2:(与矩阵A的行、列相同，行、列分别为)\n",A.mu,A.nu);
	CreateSMatrix(&B);
	printf("矩阵B2:\n");
	PrintSMatrix(&B);
	printf("矩阵C1(A+B):\n");
	InitSMatrix(&C);
	AddSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("矩阵C2(A-B):\n");
	SubtSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("矩阵C3(A的转置):\n");
	TransposeSMatrix(&A,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&B);
	DestroySMatrix(&A);*/
	printf("创建矩阵A2:\n");
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("创建矩阵B3:(行数应与矩阵的列数相同=%d)\n",A.nu);
	CreateSMatrix(&B);
	PrintSMatrix(&B);
	printf("矩阵C4(A*B):\n");
	MultSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&B);
	DestroySMatrix(&A);
}

void InitSMatrix(pCrossList A)
{
	A->rhead = A->chead = NULL;
	A->mu = A->nu = A->tu = 0;
}

void CreateSMatrix(pCrossList A)
{
	int i,j,k,m,n,t,e;
	pOLNode p,q;
	if(A->rhead)			//建议数组是否为NULL
	{
		DestroySMatrix(A);
	}
	printf("请输入稀疏矩阵的行数 列数 非零元个数:");
	scanf("%d,%d,%d",&m,&n,&t);
	A->mu = m;
	A->nu = n;
	A->tu = t;
	A->rhead = (pOLNode*)malloc((m+1)*sizeof(OLNode));
	if(!A->rhead)
	{
		exit(-1);
	}
	A->chead = (pOLNode*)malloc((n+1)*sizeof(OLNode));
	if(!A->chead)
	{
		exit(-1);
	}
	for(k=1;k<=m;k++)
	{
		A->rhead[k] = NULL;
	}
	for(k=1;k<=n;k++)
	{
		A->chead[k] = NULL;
	}
	printf("请按任意次序输入%d个非零元素的行 列 元素值:\n",A->tu);
	for(k=0;k<t;k++)
	{
		printf("输入第%d个结点行号、列号以及值：\n", k+1); 
		scanf("%d,%d,%d",&i,&j,&e);
		p = (OLNode*)malloc(sizeof(OLNode));
		if(!p)
		{
			exit(-1);
		}
		p->i = i;
		p->j = j;
		p->e = e;
		if(A->rhead[i]==NULL || A->rhead[i]->j>j)
		{
			p->right = A->rhead[i];
			A->rhead[i] = p;
		}
		else
		{
			for(q=A->rhead[i];q->right&&q->right->j<j;q=q->right);
			p->right = q->right;
			q->right = p;
		}
/*
矩阵A(0代表未分配的位置)
1 0 0 3
0 0 8 0
0 0 0 1
理解:if(A->rhead[i]==NULL || A->rhead[i]->j>j)
假设输入的i、j、e分别为2 2 3,这时A->rhead[i]->j=3>j=2,说明将要插入的i=2、j=3、e=3的位置在这一排的第一个地址位置
p->right=A->rhead[i]指向原来的首地址，A->rhead[i]=p原来首地址指向新插入的
理解:for(q=A->rhead[i];q->right&&q->right->j<j;q=q->right)
q=A->rhead[i]从这一排首地址开始,以q->right&&q->right->j<j作为限制q->right存在,并且用新插入的j>q->right->j找到位置;
*/
		if(A->chead[j]==NULL || A->chead[j]->i>i)
		{
			p->down = A->chead[j];
			A->chead[j] = p;
		}
		else
		{
			for(q=A->chead[j];q->down&&q->down->i<i;q=q->down);
			p->down = q->down;
			q->down = p;
		}
	}
	DelZero(A);
}

void CopySMatrix(pCrossList A,pCrossList B)
{
	int i;
	pOLNode p,q,q1,q2;
	if(B->rhead)
	{
		DestroySMatrix(A);
	}
	B->mu = A->mu;
	B->nu = A->nu;
	B->tu = A->tu;
	B->rhead = (pOLNode*)malloc((B->mu+1)*sizeof(OLNode));
	if(!B->rhead)
		exit(-1);
	B->chead = (pOLNode*)malloc((B->nu+1)*sizeof(OLNode));
	if(!B->chead)
		exit(-1);
	for(i=1;i<=B->mu;i++)
		B->rhead[i] = NULL;
	for(i=1;i<=B->nu;i++)
		B->chead[i] = NULL;
	for(i=1;i<=A->mu;i++)
	{
		p = A->rhead[i];
		while(p)
		{
			q = (OLNode*)malloc(sizeof(OLNode));
			if(!q)
				exit(-1);
			q->i = p->i;
			q->j = p->j;
			q->e = p->e;
			if(!B->rhead[i])
				B->rhead[i] = q1 = q;
			else
				q1 = q1->right = q;
			if(!B->chead[q->j])
			{
				B->chead[q->j] = q;
				q->down = NULL;				//确保尾部所指向的下一个down为NULL
			}
			else
			{
				q2 = B->chead[p->j];
				while(q2->down)
					q2 = q2->down;
				q2->down = q;
				q->down = NULL;
			}
			p = p->right;
		}
		q->right = NULL;					//确保尾部所指向的下一个right为NULL
	}
}

void AddSMatrix(pCrossList A,pCrossList B,pCrossList C)
{
	int i,k;
	pOLNode p,q,m,n;
	C->mu = A->mu;
	C->nu = A->nu;
	C->rhead = (pOLNode*)malloc((A->mu+1)*sizeof(OLNode));
	if(!C->rhead)
		exit(-1);
	C->chead = (pOLNode*)malloc((A->nu+1)*sizeof(OLNode));
	if(!C->chead)
		exit(-1);
	for(k=1;k<=A->mu;k++)
		C->rhead[k] = NULL;
	for(k=1;k<=A->nu;k++)
		C->chead[k] = NULL;
	for(i=1;i<=A->mu;i++)
	{
		p = A->rhead[i];
		q = B->rhead[i];
		while(p || q)
		{
			n = (OLNode*)malloc(sizeof(OLNode));
			if(q && p)
			{
				if(q->j == p->j)
				{
					n->e = q->e+p->e;
					n->i = i;
					n->j = q->j;
					q = q->right;
					p = p->right;
				}
				else if(q->j > p->j)
				{
					n->e = p->e;
					n->i = i;
					n->j = p->j;
					p = p->right;
				}
				else
				{
					n->e = q->e;
					n->i = i;
					n->j = q->j;
					q = q->right;
				}
			}
			else if(q && !p)
			{
				n->e = q->e;
				n->i = i;
				n->j = q->j;
				q = q->right;
			}
			else if(!q && p)
			{
				n->e = p->e;
				n->i = i;
				n->j = p->j;
				p = p->right;
			}
		if(C->rhead[i]==NULL || C->rhead[i]->j>n->j)
		{
			n->right = C->rhead[i];
			C->rhead[i] = n;
		}
		else
		{
			for(m=C->rhead[i];m->right&&m->right->j<n->j;m=m->right);
			n->right = m->right;
			m->right = n;
		}

		if(C->chead[n->j]==NULL || C->chead[n->j]->i>n->i)
		{
			n->down = C->chead[n->j];
			C->chead[n->j] = n;
		}
		else
		{
			for(m=A->chead[n->j];m->down&&m->down->i<i;m=m->down);
			n->down = m->down;
			m->down = n;
		}
		C->tu++;
		}
	}
}

void SubtSMatrix(pCrossList A,pCrossList B,pCrossList C)
{
	int i;
	CrossList D;
	pOLNode p;
	InitSMatrix(&D);
	CopySMatrix(B,&D);
	for(i=1;i<=D.mu;i++)
	{
		p = D.rhead[i];
		while(p)
		{
			p->e = -p->e;
			p = p->right;
		}
	}
	AddSMatrix(A,&D,C);
	DelZero(C);
	DestroySMatrix(&D);
}

void TransposeSMatrix(pCrossList A,pCrossList C)
{
	int u,i;
	pOLNode *head,p,q,r;
	if(C->rhead)
		DestroySMatrix(C);
	CopySMatrix(A,C);
	u = C->mu;
	C->mu = C->nu;
	C->nu = u;
	head = C->chead;
	C->rhead = C->chead;
	C->chead = head;
	for(u=1;u<=C->mu;u++)
	{
		p = C->rhead[u];
		while(p)
		{
			q = p->down;			//q指向下一个节点
			i = p->i;				//交换i和j
			p->i = p->j;
			p->j = i;
			r = p->down;			//交换down和right
			p->down = p->right;
			p->right = r;
			p = q;					//p指向下一个节点
		}
	}
}

void MultSMatrix(pCrossList A,pCrossList B,pCrossList C)
{
	int i,j,k,e;
	pOLNode p,q,n,m,n1,n2;
	C->mu = A->mu;
	C->nu = B->nu;
	C->tu = 0;
	C->rhead = (pOLNode*)malloc((A->mu+1)*sizeof(OLNode));
	if(!C->rhead)
		exit(-1);
	C->chead = (pOLNode*)malloc((B->nu+1)*sizeof(OLNode));
	if(!C->chead)
		exit(-1);
	for(k=1;k<=A->mu;k++)
		C->rhead[k] = NULL;
	for(k=1;k<=A->nu;k++)
		C->chead[k] = NULL;
	for(i=1;i<=B->nu;i++)
	{
		for(j=1;j<=B->nu;j++)
		{
			p = A->rhead[i];
			q = B->chead[j];
			e = 0;
			while(p && q)
			{	
				if(p->j == q->i)
				{
					e += p->e*q->e;
					q = q->down;
					p = p->right;
				}
				else if(q->i > p->j)
					p = p->right;
				else
					q = q->down;
			}
			if(e!=0)
			{
				if(!(n=(pOLNode)malloc(sizeof(OLNode))))
					exit(-1);
				n->down = NULL;
				n->right = NULL;
				n->e = e;
				n->i = i;
				n->j = j;
				if(!C->rhead[i])
					C->rhead[i] = n1 = n;
				else
					n1 = n1->right = n;
				if(!C->chead[j])
					C->chead[j] = n;
				else
				{
					n2 = C->chead[j];
					while(n2->down)
						n2 = n2->down;
					n2->down = n;
				}
				C->tu++;
			}
		}
	}
}

void DelZero(pCrossList A)
{
	int i;
	pOLNode p,q;
	for(i=1;i<=A->mu;i++)
	{
		if(A->rhead[i])								//这里是为了防止A->rhead[i]为空，访问A->rhead[i]->e未分配空间出错
		{
			if(A->rhead[i]->e == 0)
			{
				q = A->rhead[i];
				A->rhead[i] = A->rhead[i]->right;
				free(q);
			}
			p = A->rhead[i];
			while(p && p->right)					//这里按先p后p->right的方式检查，先检查p是为了防止p->right是未分配空间访问出错
			{
				if(p->right->e == 0)
				{
					q = p->right;
					p->right = p->right->right;
					free(q);
				}
				p = p->right;
			}
		}
	}
}

void PrintSMatrix(pCrossList A)
{
	pOLNode q;
	if(!A->tu)
	{
		printf("矩阵为空!\n");
	}
	else
	{
		for(int i=1;i<=A->mu;i++)
		{
			q = A->rhead[i];
			for(int j=1;j<=A->nu;j++)
			{
				if(q && q->j == j)				//if()语句中也是按顺序执行，为了防止q->j是未分配空间访问出错
				{
					printf("%d ",q->e);
					q = q->right;
				}
				else
				{
					printf("0 ");
				}
			}
			printf("\n");
		}
	}
}

void DestroySMatrix(pCrossList A)
{
	int i;
	OLNode *p,*q;
	for(i=1;i<A->nu;i++)
	{
		p = A->rhead[i];
		while(p)
		{
			q = p;
			p = p->right;
			free(q);
		}
	}
	free(A->chead);
	free(A->rhead);
	InitSMatrix(A);
}