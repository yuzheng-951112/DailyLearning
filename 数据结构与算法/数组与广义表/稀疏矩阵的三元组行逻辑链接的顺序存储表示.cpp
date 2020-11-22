#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXSIZE 100		//非零元个数的最大值
#define MAXRC 20		//最大行列数

typedef struct Triple
{
	int i,j;			//行下标、列下标
	int e;				//非零元素值
}*pTriple;

typedef struct RLSMatrix
{
	Triple data[MAXSIZE+1];		//非零元三元组表，data[0]未用
	int rpos[MAXRC+1];			//各行第一个非零元素的位置表
	int mu,nu,tu;				//矩阵的行数、列数和非零元个数
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
/*	printf("创建矩阵A:\n");
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("由矩阵A复制矩阵B:\n");
	CopySMatrix(&A,&B);
	PrintSMatrix(&B);
	DestroySMatrix(&B);
	printf("销毁矩阵B后:\n");
	PrintSMatrix(&B);
	printf("创建矩阵B2:(与矩阵A的行、列数相同，行列分别为%d,%d)\n",A.mu,A.nu);
	CreateSMatrix(&B);
	PrintSMatrix(&B);
	printf("矩阵C1(A+B):\n");
	AddSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("矩阵C2(A+B):\n");
	SubtSMatrix(&A,&B,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	printf("矩阵C3(A的转置):\n");
	TransposeSMatrix(&A,&C);
	PrintSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&B);
	DestroySMatrix(&A);
*/	printf("创建矩阵A2:\n");
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("创建矩阵B3:\n");
	CreateSMatrix(&B);
	PrintSMatrix(&B);
	printf("矩阵C5(A*B):\n");
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
	printf("请输入矩阵的行数，列数，非零元素数");
	scanf("%d,%d,%d",&A->mu,&A->nu,&A->tu);
	A->data[0].i = 0;		//为以下比较做准备
	for(i=1;i<=A->tu;i++)
	{
		do
		{
			printf("请按行顺序输入第%d个非零元素所在的行(1~%d),列(1~%d),元素值:",i,A->mu,A->nu);
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
矩阵A:
0 1 2 3
0 0 0 0
6 8 0 0
0 0 0 0
分析1.A->tu=1时,A->data[1].i=1,A->data[0]=0,所以A->data[1].i>A->data[0].i
	  for(T.i=0,T.i<A->data[1].i-A->data[0].i=1;T.i++)
	  A->rpos[A->data[i].i-T.i=1-0=1] = 1;
	  得出第一行第一个非零地址为A->rpos[1] = 1
	2.A->tu=2时,A->data[2].i=1,A->data[1]=1,所以A->data[2].i==A->data[1].i结束程序
	3.A->tu=3时同上
	4.A->tu=4时,A->data[4].i=3,A->data[3]=1,所以A->data[4].i>A->data[3].i
	  for(T.i=0,T.i<A->data[4].i-A->data[3].i=2;T.i++)
	  A->rpos[A->data[i].i-T.i=3-0=3] = 4;
	  得出第三行第一个非零地址为A->rpos[3] = 4;
	  T.i++;
	  A->rpos[A->data[i].i-T.i=3-1=2] = 4;
	  所以得出第二行首地址为A->rpos[2] = 4;
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
	A->rpos[A->mu+1] = A->tu+1;							//为方便后面的while循环临时设置
	B->rpos[B->mu+1] = B->tu+1;
	for(k=1;k<=A->mu;k++)								//对于每一行,k指示行号
	{
		C->rpos[k] = C->tu+1;
		p = A->rpos[k];									//p指出示M矩阵第k行当前元素的序号
		q = B->rpos[k];									//q指出示N矩阵第k行当前元素的序号
		while(p<A->rpos[k+1] && q<B->rpos[k+1])			//A,B矩阵均有第k行元素未处理
		{
			if(A->data[p].j == B->data[q].j)			//A矩阵当前元素和B矩阵当前元素的列相同
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
			else if(A->data[p].j<B->data[q].j)			//A矩阵当前元素的列<B矩阵当前元素的列
			{
				C->tu++;
				C->data[C->tu].e = A->data[p].e;
				C->data[C->tu].i = k;
				C->data[C->tu].j = A->data[p].j;
				p++;
			}
			else										//A矩阵当前元素的列>B矩阵当前元素的列
			{
				C->tu++;
				C->data[C->tu].e = B->data[q].e;
				C->data[C->tu].i = k;
				C->data[C->tu].j = B->data[q].j;
				q++;
			}
		}
		while(p<A->rpos[k+1])							//处理A矩阵k行未处理的元素
		{
			C->tu++;
			C->data[C->tu].e = A->data[p].e;
			C->data[C->tu].i = k;
			C->data[C->tu].j = A->data[p].j;
			p++;
		}
		while(q<B->rpos[k+1])							//处理B矩阵k行未处理的元素
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
			num[A->data[t].j]++;							//求A中每一列非非零元素个数
		}
		C->rpos[1] = 1;
		for(col=2;col<=A->nu;col++)
		{
			C->rpos[col] = C->rpos[col-1]+num[col-1];	//求A中第col中的第一个非零元素C->data中的序号
		}
		for(col=1;col<=A->nu;col++)
		{
			num[col] = C->rpos[col];					//这个跟快速转置想法相同不同的是rpos这里作为结构体变量不能乱变，所以添加一步
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
	if(A->nu != B->mu)									//矩阵A的列数应和矩阵B的行数相等
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
		for(arow=1;arow<=A->mu;arow++)							//从A的第一行开始，到最后一行，arow是A的当前行
		{
			for(ccol=1;ccol<=B->nu;ccol++)
			{
				ctemp[ccol] = 0;
			}
			C->rpos[arow] = C->tu+1;							//C当前行的第一个元素位于上一行最后一个元素之后

			for(p=A->rpos[arow];p<A->rpos[arow+1];p++)			//对A当前行中每一个非零元素
			{
				brow = A->data[p].j;							//找到对应元素在B中的行数(与稀疏矩阵中MultSMatrix的A->data[i].j==B->data[j].i确定数组行列能相乘的关系相同)
				for(q=B->rpos[brow];q<B->rpos[brow+1];q++)		//找到B中对应行中的元素相乘
				{
					ccol = B->data[q].j;						//乘积元素在C中的列
					ctemp[ccol] += A->data[p].e*B->data[q].e;	//对应ctemp[ccol]的数值每次相加
				}
			}
			//	这个双循环代表两矩阵相乘后新矩阵每一排不同列的值
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
	printf("%d行%d列%d个非零元素。\n",A->mu,A->nu,A->tu);
	printf("行 列 元素值\n");
	for(i=1;i<=A->tu;i++)
	{
		printf("%2d%4d%8d\n",A->data[i].i,A->data[i].j,A->data[i].e);
	}
	for(i=1;i<=A->mu;i++)
	{
		printf("第%d行的第一个非零元素是本矩阵第%d个元素\n",i,A->rpos[i]);
	}
}
*/

void DestroySMatrix(pRLSMatrix A)
{
	A->mu = 0;
	A->nu = 0;
	A->tu = 0;
}