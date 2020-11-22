#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXSIZE 100		//����Ԫ���������ֵ
#define MAXRC 20		//���������

typedef struct Triple
{
	int i,j;			//���±ꡢ���±�
	int e;				//����Ԫ��ֵ
}*pTriple;

typedef struct RLSMatrix
{
	Triple data[MAXSIZE+1];		//����Ԫ��Ԫ���data[0]δ��
	int rpos[MAXRC+1];			//���е�һ������Ԫ�ص�λ�ñ�
	int mu,nu,tu;				//����������������ͷ���Ԫ����
}*pRLSMatrix;

void CreateSMatrix(pRLSMatrix);
void PrintSMatrix(pRLSMatrix);
void CopySMatrix(pRLSMatrix,pRLSMatrix);
void AddSMatrix(pRLSMatrix,pRLSMatrix,pRLSMatrix);
void DestroySMatrix(pRLSMatrix);
void SubtSMatrix(pRLSMatrix,pRLSMatrix,pRLSMatrix);
void TransposeSMatrix(pRLSMatrix,pRLSMatrix);
void MultSMatrix(pRLSMatrix,pRLSMatrix,pRLSMatrix);

void main()
{
	RLSMatrix A,B,C;
/*	printf("��������A:\n");
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("�ɾ���A���ƾ���B:\n");
	CopySMatrix(&A,&B);
	PrintSMatrix(&B);
	DestroySMatrix(&B);
	printf("���پ���B��:\n");
	PrintSMatrix(&B);
	printf("��������B2:(�����A���С�������ͬ�����зֱ�Ϊ%d,%d)\n",A.mu,A.nu);
	CreateSMatrix(&B);
	PrintSMatrix(&B);
	printf("����C1(A+B):\n");
	AddSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("����C2(A+B):\n");
	SubtSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("����C3(A��ת��):\n");
	TransposeSMatrix(&A,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&B);
	DestroySMatrix(&A);
*/	printf("��������A2:\n");
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("��������B3:\n");
	CreateSMatrix(&B);
	PrintSMatrix(&B);
	printf("����C5(A*B):\n");
	MultSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&B);
	DestroySMatrix(&A);
}

void CreateSMatrix(pRLSMatrix A)
{
	int k,i;
	Triple T;
	printf("��������������������������Ԫ����");
	scanf("%d,%d,%d",&A->mu,&A->nu,&A->tu);
	A->data[0].i = 0;		//Ϊ���±Ƚ���׼��
	for(i=1;i<=A->tu;i++)
	{
		do
		{
			printf("�밴��˳�������%d������Ԫ�����ڵ���(1~%d),��(1~%d),Ԫ��ֵ:",i,A->mu,A->nu);
			scanf("%d,%d,%d",&T.i,&T.j,&T.e);
			k = 0;
			if(T.i<1 || T.i>A->mu || T.j<1 || T.j>A->nu)
			{
				k = 1;
			}
			if(T.i<A->data[i-1].i || (T.i==A->data[i-1].i&&T.j<=A->data[i-1].j))
			{
				k = 1;
			}
		}while(k);
		A->data[i] = T;
	}
	for(i=1;i<=A->tu;i++)
	{
		if(A->data[i].i>A->data[i-1].i)
		{
			for(T.i=0;T.i<A->data[i].i-A->data[i-1].i;T.i++)
			{
				A->rpos[A->data[i].i - T.i] = i;
			}
		}
	}
	for(i=A->data[A->tu].i+1;i<=A->mu;i++)
	{
		A->rpos[i] = A->tu+1; 
	}
}
/*
����A:
0 1 2 3
0 0 0 0
6 8 0 0
0 0 0 0
����1.A->tu=1ʱ,A->data[1].i=1,A->data[0]=0,����A->data[1].i>A->data[0].i
	  for(T.i=0,T.i<A->data[1].i-A->data[0].i=1;T.i++)
	  A->rpos[A->data[i].i-T.i=1-0=1] = 1;
	  �ó���һ�е�һ�������ַΪA->rpos[1] = 1
	2.A->tu=2ʱ,A->data[2].i=1,A->data[1]=1,����A->data[2].i==A->data[1].i��������
	3.A->tu=3ʱͬ��
	4.A->tu=4ʱ,A->data[4].i=3,A->data[3]=1,����A->data[4].i>A->data[3].i
	  for(T.i=0,T.i<A->data[4].i-A->data[3].i=2;T.i++)
	  A->rpos[A->data[i].i-T.i=3-0=3] = 4;
	  �ó������е�һ�������ַΪA->rpos[3] = 4;
	  T.i++;
	  A->rpos[A->data[i].i-T.i=3-1=2] = 4;
	  ���Եó��ڶ����׵�ַΪA->rpos[2] = 4;
*/

void CopySMatrix(pRLSMatrix A,pRLSMatrix B)
{
	*B = *A;
}

void AddSMatrix(pRLSMatrix A,pRLSMatrix B,pRLSMatrix C)
{
	int k,p,q;
	if(A->mu!=B->mu || A->mu!=B->mu)
	{
		exit(-1);
	}
	C->mu = A->mu;
	C->nu = A->nu;
	C->tu = 0;
	A->rpos[A->mu+1] = A->tu+1;							//Ϊ��������whileѭ����ʱ����
	B->rpos[B->mu+1] = B->tu+1;
	for(k=1;k<=A->mu;k++)								//����ÿһ��,kָʾ�к�
	{
		C->rpos[k] = C->tu+1;
		p = A->rpos[k];									//pָ��ʾM�����k�е�ǰԪ�ص����
		q = B->rpos[k];									//qָ��ʾN�����k�е�ǰԪ�ص����
		while(p<A->rpos[k+1] && q<B->rpos[k+1])			//A,B������е�k��Ԫ��δ����
		{
			if(A->data[p].j == B->data[q].j)			//A����ǰԪ�غ�B����ǰԪ�ص�����ͬ
			{
				C->data[C->tu+1].e = A->data[p].e+B->data[q].e;
				if(C->data[C->tu+1].e!=0)
				{
					C->tu++;
					C->data[C->tu].i = k;
					C->data[C->tu].j = A->data[p].j;
				}
				p++;
				q++;
			}
			else if(A->data[p].j<B->data[q].j)			//A����ǰԪ�ص���<B����ǰԪ�ص���
			{
				C->tu++;
				C->data[C->tu].e = A->data[p].e;
				C->data[C->tu].i = k;
				C->data[C->tu].j = A->data[p].j;
				p++;
			}
			else										//A����ǰԪ�ص���>B����ǰԪ�ص���
			{
				C->tu++;
				C->data[C->tu].e = B->data[q].e;
				C->data[C->tu].i = k;
				C->data[C->tu].j = B->data[q].j;
				q++;
			}
		}
		while(p<A->rpos[k+1])							//����A����k��δ�����Ԫ��
		{
			C->tu++;
			C->data[C->tu].e = A->data[p].e;
			C->data[C->tu].i = k;
			C->data[C->tu].j = A->data[p].j;
			p++;
		}
		while(q<B->rpos[k+1])							//����B����k��δ�����Ԫ��
		{
			C->tu++;
			C->data[C->tu].e = B->data[q].e;
			C->data[C->tu].i = k;
			C->data[C->tu].j = B->data[q].j;
			q++;
		}
	}
}

void SubtSMatrix(pRLSMatrix A,pRLSMatrix B,pRLSMatrix C)
{
	int i;
	if(A->mu!=B->mu || A->nu!=B->nu)
	{
		exit(-1);
	}
	for(i=1;i<B->tu;i++)
	{
		B->data[i].e *= -1;
	}
	AddSMatrix(A,B,C);
}

void TransposeSMatrix(pRLSMatrix A,pRLSMatrix C)
{
	int i,k;
	C->tu = 0;
	for(k=1;k<=A->nu;k++)
	{
		C->rpos[k] = C->tu+1;		
		for(i=1;i<=A->tu;i++)
		{
			if(A->data[i].j == k)
			{
				C->data[C->tu+1].e = A->data[i].e;
				C->data[C->tu+1].j = A->data[i].i;
				C->data[C->tu+1].i = k;
				C->tu++;
			}
		}
	}
	C->mu = A->nu;
	C->nu = A->mu;
}

/*
void TransposeSMatrix(pRLSMatrix A,pRLSMatrix C)
{
	int p,q,t,col,*num;
	num = (int*)malloc(sizeof(int)*(A->nu+1));
	C->mu = A->nu;
	C->nu = A->mu;
	C->tu = A->tu;
	if(C->tu)
	{
		for(col=1;col<=A->nu;col++)
		{
			num[col] = 0;
		}
		for(t=1;t<=A->tu;t++)
		{
			num[A->data[t].j]++;							//��A��ÿһ�зǷ���Ԫ�ظ���
		}
		C->rpos[1] = 1;
		for(col=2;col<=A->nu;col++)
		{
			C->rpos[col] = C->rpos[col-1]+num[col-1];	//��A�е�col�еĵ�һ������Ԫ��C->data�е����
		}
		for(col=1;col<=A->nu;col++)
		{
			num[col] = C->rpos[col];					//���������ת���뷨��ͬ��ͬ����rpos������Ϊ�ṹ����������ұ䣬�������һ��
		}
		for(p=1;p<=A->nu;p++)
		{
			col = A->data[p].j;
			q = num[col];
			C->data[q].i = A->data[p].j;
			C->data[q].j = A->data[p].i;
			C->data[q].e = A->data[p].e;
			num[col]++;
		}
	}
	free(num);
}
*/

void MultSMatrix(pRLSMatrix A,pRLSMatrix B,pRLSMatrix C)
{
	int arow,brow,p,q,ccol,ctemp[MAXRC+1];
	if(A->nu != B->mu)									//����A������Ӧ�;���B���������
	{
		exit(-1);
	}
	C->mu = A->mu;
	C->nu = B->nu;
	C->tu = 0;
	A->rpos[A->mu+1] = A->tu+1;
	B->rpos[B->mu+1] = B->tu+1;
	if(A->tu*B->tu != 0)
	{
		for(arow=1;arow<=A->mu;arow++)							//��A�ĵ�һ�п�ʼ�������һ�У�arow��A�ĵ�ǰ��
		{
			for(ccol=1;ccol<=B->nu;ccol++)
			{
				ctemp[ccol] = 0;
			}
			C->rpos[arow] = C->tu+1;							//C��ǰ�еĵ�һ��Ԫ��λ����һ�����һ��Ԫ��֮��

			for(p=A->rpos[arow];p<A->rpos[arow+1];p++)			//��A��ǰ����ÿһ������Ԫ��
			{
				brow = A->data[p].j;							//�ҵ���ӦԪ����B�е�����(��ϡ�������MultSMatrix��A->data[i].j==B->data[j].iȷ��������������˵Ĺ�ϵ��ͬ)
				for(q=B->rpos[brow];q<B->rpos[brow+1];q++)		//�ҵ�B�ж�Ӧ���е�Ԫ�����
				{
					ccol = B->data[q].j;						//�˻�Ԫ����C�е���
					ctemp[ccol] += A->data[p].e*B->data[q].e;	//��Ӧctemp[ccol]����ֵÿ�����
				}
			}
			//	���˫ѭ��������������˺��¾���ÿһ�Ų�ͬ�е�ֵ
			for(ccol=1;ccol<=C->nu;ccol++)
			{
				C->tu++;
				if(C->tu>MAXSIZE)
				{
					exit(-1);
				}
				C->data[C->tu].i = arow;
				C->data[C->tu].j = ccol;
				C->data[C->tu].e = ctemp[ccol];
			}
		}
	}
}

void PrintSMatrix(pRLSMatrix TSM)
{
	int i,j,k;
	for(i=1;i<=TSM->mu;i++)
	{
		for(j=1;j<=TSM->nu;j++)
		{
			k=1;
			while(k<=TSM->tu)
			{
				if(i==TSM->data[k].i && j==TSM->data[k].j)
				{
					printf("%d ",TSM->data[k].e);
					break;
				}
				k++;
			}
			if(k>TSM->tu)
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

/*
void PrintSMatrix(pRLSMatrix A)
{
	int i;
	printf("%d��%d��%d������Ԫ�ء�\n",A->mu,A->nu,A->tu);
	printf("�� �� Ԫ��ֵ\n");
	for(i=1;i<=A->tu;i++)
	{
		printf("%2d%4d%8d\n",A->data[i].i,A->data[i].j,A->data[i].e);
	}
	for(i=1;i<=A->mu;i++)
	{
		printf("��%d�еĵ�һ������Ԫ���Ǳ������%d��Ԫ��\n",i,A->rpos[i]);
	}
}
*/

void DestroySMatrix(pRLSMatrix A)
{
	A->mu = 0;
	A->nu = 0;
	A->tu = 0;
}