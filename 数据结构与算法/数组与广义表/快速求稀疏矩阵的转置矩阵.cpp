#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXSIZE 100

//��Ԫ����Ԫ
struct Triple
{
	int i,j;						
	int e;
}*pTriple;

//��Ԫ����
typedef struct TSMatrix
{
	Triple data[MAXSIZE];			//data[i]��������еĵ�Ԫ
	int i,j,tu;						//�С���(���ƶ�Ԫ������С�����)������Ԫ�ظ���(�涨��Ԫ�����е�Ԫ��)
}*pTSMatrix;

void CreateSMatrix(pTSMatrix);
void printSMatrix(pTSMatrix);
void FastTransposeSMatrix(pTSMatrix,pTSMatrix);
void DestroySMatrix(pTSMatrix);

void main()
{
	TSMatrix A,B;
	printf("��������A:");
	CreateSMatrix(&A);
	printSMatrix(&A);
	FastTransposeSMatrix(&A,&B);
	printf("����B(A�Ŀ���ת��):\n");
	printSMatrix(&B);
	DestroySMatrix(&A);
	DestroySMatrix(&B);

}

void CreateSMatrix(pTSMatrix TSM)
{
	int i,m,n,e,k;
	printf("�����������С��С�����Ԫ�ظ���:");
	scanf("%d,%d,%d",&TSM->i,&TSM->j,&TSM->tu);
	TSM->data[0].i = 0;
	for(i=1;i<=TSM->tu;i++)
	{
		do
		{
			printf("�밴��˳�������%d������Ԫ�����ڵ���(1~%d),��(1~%d),Ԫ��ֵ",i,TSM->i,TSM->j);
			scanf("%d,%d,%d",&m,&n,&e);
			k = 0;
			if(m<1 || m>TSM->i || n<1 || n>TSM->j)										//�л��г�����Χ
			{
				k = 1;
			}
			if(m<TSM->data[i-1].i ||(m == TSM->data[i-1].i&&n<=TSM->data[i-1].j))		//������ľ���Ԫ���������ڴ��в�С��֮ǰ���������߲�С�ڴ���
			{
				k = 1;
			}
		}while(k);
		TSM->data[i].i = m;
		TSM->data[i].j = n;
		TSM->data[i].e = e;
	}
}

void FastTransposeSMatrix(pTSMatrix A,pTSMatrix B)
{
	int p,q,t,col,*num,*cpot;
	num = (int*)malloc((A->j+1)*sizeof(int));	//�������� ��¼��Ԫ�������Ԫ�������
	cpot = (int*)malloc((B->j+1)*sizeof(int));	//�������� ��¼ת������Ԫ����Ԫ�ص�λ��(tu)
	B->i = A->j;
	B->j = A->i;
	B->tu = A->tu;
	if(B->tu)
	{
		for(col=1;col<=A->j;col++)
		{
			num[col] = 0;
		}
		for(t=1;t<=A->tu;t++)			//��¼ÿһ�з���Ԫ�صĸ���
		{
			++num[A->data[t].j];
		}
		cpot[1] = 1;
		for(col=2;col<=A->j;col++)
		{
			cpot[col] = cpot[col-1] + num[col-1];		//��col���е�һ������Ԫ����C->data�е����
		}
		for(p=1;p<=A->tu;p++)
		{
			col = A->data[p].j;
			q = cpot[col];
			B->data[q].i = A->data[p].j;
			B->data[q].j = A->data[p].i;
			B->data[q].e = A->data[p].e;
			++cpot[col];
		}
	}
	free(num);
	free(cpot);
}

void printSMatrix(pTSMatrix TSM)
{
	int i,j,k;
	for(i=1;i<=TSM->i;i++)
	{
		for(j=1;j<=TSM->j;j++)
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

void DestroySMatrix(pTSMatrix MS)
{
	MS->i = 0;
	MS->j = 0;
	MS->tu = 0;
}