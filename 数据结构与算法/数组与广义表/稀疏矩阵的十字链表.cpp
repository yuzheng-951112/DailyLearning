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
	pOLNode *rhead,*chead;			//�к�������ͷָ�����ַ(rhead,chead�൱�����飬������Ǹ�ͷ��ַ�����ַ)
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
	InitSMatrix(&A);		//CrossList���͵ı����ڳ���ʹ��֮ǰ�����ʼ��
	InitSMatrix(&B);
/*	printf("��������A:");
	CreateSMatrix(&A);
	printf("����A:\n");
	PrintSMatrix(&A);
	printf("�ɾ���A���ƾ���B:\n");
	CopySMatrix(&A,&B);
	PrintSMatrix(&B);
	DestroySMatrix(&B);
	printf("���پ���B��\n");
	PrintSMatrix(&B);
	printf("��������B2:(�����A���С�����ͬ���С��зֱ�Ϊ)\n",A.mu,A.nu);
	CreateSMatrix(&B);
	printf("����B2:\n");
	PrintSMatrix(&B);
	printf("����C1(A+B):\n");
	InitSMatrix(&C);
	AddSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("����C2(A-B):\n");
	SubtSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("����C3(A��ת��):\n");
	TransposeSMatrix(&A,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&B);
	DestroySMatrix(&A);*/
	printf("��������A2:\n");
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("��������B3:(����Ӧ������������ͬ=%d)\n",A.nu);
	CreateSMatrix(&B);
	PrintSMatrix(&B);
	printf("����C4(A*B):\n");
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
	if(A->rhead)			//���������Ƿ�ΪNULL
	{
		DestroySMatrix(A);
	}
	printf("������ϡ���������� ���� ����Ԫ����:");
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
	printf("�밴�����������%d������Ԫ�ص��� �� Ԫ��ֵ:\n",A->tu);
	for(k=0;k<t;k++)
	{
		printf("�����%d������кš��к��Լ�ֵ��\n", k+1); 
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
����A(0����δ�����λ��)
1 0 0 3
0 0 8 0
0 0 0 1
���:if(A->rhead[i]==NULL || A->rhead[i]->j>j)
���������i��j��e�ֱ�Ϊ2 2 3,��ʱA->rhead[i]->j=3>j=2,˵����Ҫ�����i=2��j=3��e=3��λ������һ�ŵĵ�һ����ַλ��
p->right=A->rhead[i]ָ��ԭ�����׵�ַ��A->rhead[i]=pԭ���׵�ַָ���²����
���:for(q=A->rhead[i];q->right&&q->right->j<j;q=q->right)
q=A->rhead[i]����һ���׵�ַ��ʼ,��q->right&&q->right->j<j��Ϊ����q->right����,�������²����j>q->right->j�ҵ�λ��;
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
				q->down = NULL;				//ȷ��β����ָ�����һ��downΪNULL
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
		q->right = NULL;					//ȷ��β����ָ�����һ��rightΪNULL
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
			q = p->down;			//qָ����һ���ڵ�
			i = p->i;				//����i��j
			p->i = p->j;
			p->j = i;
			r = p->down;			//����down��right
			p->down = p->right;
			p->right = r;
			p = q;					//pָ����һ���ڵ�
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
		if(A->rhead[i])								//������Ϊ�˷�ֹA->rhead[i]Ϊ�գ�����A->rhead[i]->eδ����ռ����
		{
			if(A->rhead[i]->e == 0)
			{
				q = A->rhead[i];
				A->rhead[i] = A->rhead[i]->right;
				free(q);
			}
			p = A->rhead[i];
			while(p && p->right)					//���ﰴ��p��p->right�ķ�ʽ��飬�ȼ��p��Ϊ�˷�ֹp->right��δ����ռ���ʳ���
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
		printf("����Ϊ��!\n");
	}
	else
	{
		for(int i=1;i<=A->mu;i++)
		{
			q = A->rhead[i];
			for(int j=1;j<=A->nu;j++)
			{
				if(q && q->j == j)				//if()�����Ҳ�ǰ�˳��ִ�У�Ϊ�˷�ֹq->j��δ����ռ���ʳ���
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