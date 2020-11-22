#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXSIZE 100

//二元矩阵单元
struct Triple
{
	int i,j;						
	int e;
}*pTriple;

//二元矩阵
typedef struct TSMatrix
{
	Triple data[MAXSIZE];			//data[i]代表矩阵中的单元
	int i,j,tu;						//行、列(限制二元矩阵的行、列数)、非零元素个数(规定二元矩阵中的元素)
}*pTSMatrix;

void CreateSMatrix(pTSMatrix);
void printSMatrix(pTSMatrix);
void FastTransposeSMatrix(pTSMatrix,pTSMatrix);
void DestroySMatrix(pTSMatrix);

void main()
{
	TSMatrix A,B;
	printf("创建矩阵A:");
	CreateSMatrix(&A);
	printSMatrix(&A);
	FastTransposeSMatrix(&A,&B);
	printf("矩阵B(A的快速转置):\n");
	printSMatrix(&B);
	DestroySMatrix(&A);
	DestroySMatrix(&B);

}

void CreateSMatrix(pTSMatrix TSM)
{
	int i,m,n,e,k;
	printf("请输入矩阵的行、列、非零元素个数:");
	scanf("%d,%d,%d",&TSM->i,&TSM->j,&TSM->tu);
	TSM->data[0].i = 0;
	for(i=1;i<=TSM->tu;i++)
	{
		do
		{
			printf("请按行顺序输入第%d个非零元素所在的行(1~%d),列(1~%d),元素值",i,TSM->i,TSM->j);
			scanf("%d,%d,%d",&m,&n,&e);
			k = 0;
			if(m<1 || m>TSM->i || n<1 || n>TSM->j)										//行或列超出范围
			{
				k = 1;
			}
			if(m<TSM->data[i-1].i ||(m == TSM->data[i-1].i&&n<=TSM->data[i-1].j))		//新输入的矩阵单元必须满足在此行不小于之前的数，或者不小于此行
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
	num = (int*)malloc((A->j+1)*sizeof(int));	//生成数组 记录三元数组非零元素列序号
	cpot = (int*)malloc((B->j+1)*sizeof(int));	//生成数组 记录转换后三元数组元素的位置(tu)
	B->i = A->j;
	B->j = A->i;
	B->tu = A->tu;
	if(B->tu)
	{
		for(col=1;col<=A->j;col++)
		{
			num[col] = 0;
		}
		for(t=1;t<=A->tu;t++)			//记录每一列非零元素的个数
		{
			++num[A->data[t].j];
		}
		cpot[1] = 1;
		for(col=2;col<=A->j;col++)
		{
			cpot[col] = cpot[col-1] + num[col-1];		//第col列中第一个非零元素在C->data中的序号
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