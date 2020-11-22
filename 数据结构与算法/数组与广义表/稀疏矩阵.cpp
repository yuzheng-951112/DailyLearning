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
void CopySMatrix(TSMatrix,pTSMatrix);
void DestroySMatrix(pTSMatrix);
void AddSMatrix(pTSMatrix,pTSMatrix,pTSMatrix);
//int comp(int c1,int c2);
void SubtSMatrix(pTSMatrix,pTSMatrix,pTSMatrix);
void MultSMatrix(pTSMatrix,pTSMatrix,pTSMatrix);
void TransposeSMatrix(pTSMatrix,pTSMatrix);

void main()
{
	TSMatrix A,B,C;
	printf("创造矩阵A!\n");
	CreateSMatrix(&A);
	printSMatrix(&A);
	printf("由矩阵A复制矩阵B:\n");
	CopySMatrix(A,&B);
	printSMatrix(&B);
	DestroySMatrix(&B);
	printf("销毁矩阵后:\n");
	printSMatrix(&B);
	printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A.i,A.j);
	CreateSMatrix(&B);
	printSMatrix(&B);
/*	printf("矩阵C(A+B):\n");
	AddSMatrix(&A,&B,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
	printf("矩阵C2(A-B):\n");
	SubtSMatrix(&A,&B,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
	printf("矩阵C3(A的转置矩阵)\n");
	TransposeSMatrix(&A,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&A);
	DestroySMatrix(&B);
	printf("创建矩阵A2:\n");
	CreateSMatrix(&A);
	printSMatrix(&A);
	printf("创建矩阵B3:(行数应与矩阵的A2的列数相同=%d)\n",A.j);
	CreateSMatrix(&B);
	printSMatrix(&B);
	printf("矩阵C5(A*B):\n");
*/	MultSMatrix(&A,&B,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
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

void CopySMatrix(TSMatrix A,pTSMatrix B)
{
	*B = A;								//这里是将里面的值copy,就算子函数结束了形参A,B都释放了也不影响
}

/*
TSMatrix A,B;
初始化是个结构体用
方法一:
void CopySMatrix(TSMatrix A,pTSMatrix B)
{
	*B = A;								
}
pTSMatrix A,B;
初始化是个结构体地址
方法二:
pTSMatrix CopySMatrix(pTSMatrix A,pTSMatrix B)
{
	B = A;
	return B;
}
*/

void AddSMatrix(pTSMatrix A,pTSMatrix B,pTSMatrix C)
{
	int i,j,x,y,k=1;
	for(i=1;i<=A->i;i++)
	{
		for(j=1;j<=A->j;j++)
		{
			x=1,y=1;
			while(x<=A->tu)
			{
				if(i==A->data[x].i && j==A->data[x].j)
				{
					break;	
				}
				x++;
			}
			while(y<=B->tu)
			{
				if(i==B->data[y].i && j==B->data[y].j)
				{
					break;	
				}
				y++;
			}
			if(x<=A->tu && y==B->tu+1)
			{
				C->data[k] = A->data[x];
				k++;
			}
			else if(x==A->tu+1 && y<=B->tu)
			{
				C->data[k] = B->data[y];
				k++;
			}
			else if(x<A->tu && y<B->tu)
			{
				if((C->data[k].e = A->data[x].e+B->data[y].e) != 0)
				{
					C->data[k].i = i;
					C->data[k].j = j;
					k++;
				}
			}
		}
	}
	C->i = A->i;
	C->j = A->j;
	C->tu = k;
}

/*
书本答案:
void AddSMatrix(pTSMatrix M,pTSMatrix N,pTSMatrix Q)
{
	Triple *Mp,*Me,*Np,*Ne,*Qh,*Qe;
	if(M->i != M->i)
	{
		return exit(-1);
	}
	if(M->j != M->i)
	{
		return exit(-1);
	}
	Q->i = M->i;
	Q->j = M->j;
	Mp = &M->data[1];		//Mp的初值指向矩阵M的非零元素首地址
	Np = &N->data[1];		//Np的初值指向矩阵N的非零元素首地址
	Me = &M->data[M->tu];	//Me指向矩阵M的非零元素尾地址
	Ne = &N->data[N->tu];	//Ne指向矩阵N的非零元素尾地址
	Qh = Qe = Q->data;		//Qh、Qe的初值指向矩阵Q的非零元素首地址的前一地址
	while(Mp<=Me && Np<=Ne)
	{
		Qe++;
		switch(comp(Mp->i,Np->i))
		{
		case 1:*Qe = *Mp;
				Mp++;
				break;
		case 0:switch(comp(Mp->j,Np->j))	//M、N矩阵当前非零元素的行相等，继续比较列
			   {
				case 1:*Qe = *Mp;
						Mp++;
						break;
				case 0:*Qe = *Mp;
						Qe->e += Np->e;
						if(!Qe->e)			//元素值为0，不存入压缩矩阵
						{
							Qe--;
						}
						Mp++;
						Np++;
						break;
				case -1:*Qe = *Np;
						Np++;
						break;
			   }
				break;
		case -1:*Qe = *Np;
				break;
		}
	}
	if(Mp>Me)		//矩阵M的元素全部处理完毕
	{
		while(Np<=Ne)
		{
			Qe++;
			*Qe = *Np;
			Np++;
		}
	}
	if(Np>Ne)
	{
		while(Mp<=Me)
		{
			Qe++;
			*Qe = *Mp;
			Mp++;
		}
	}
	Q->tu = Qe-Qh;	//矩阵Q的非零元素个数
}

int comp(int c1,int c2)
{
	int i;
	if(c1<c2)
	{
		i = 1;
	}
	else if(c1==c2)
	{
		i = 0;
	}
	else
	{
		i = -1;
	}
	return i;
}
*/

void SubtSMatrix(pTSMatrix A,pTSMatrix B,pTSMatrix C)
{
	int i;
	for(i=1;i<=B->tu;i++)
	{
		B->data[i].e *= -1; 
	}
	AddSMatrix(A,B,C);
}

void TransposeSMatrix(pTSMatrix A,pTSMatrix C)
{
	int q,p,col;
	C->i = A->j;
	C->j = A->i;
	C->tu = A->tu;
	if(C->tu)
	{
		q = 1;
		for(col=1;col<=A->j;col++)
		{
			for(p=1;p<=A->tu;p++)
			{
				if(A->data[p].j == col)					//按照data.j的数来排列行(这样就可以按CreateSMatrix函数中建立矩阵的顺序)
				{
					C->data[q].i = A->data[p].j;
					C->data[q].j = A->data[p].i;
					C->data[q].e = A->data[p].e;
					q++;
				}
			}
		}
	}
}
/*
void MultSMatrix(pTSMatrix A,pTSMatrix B,pTSMatrix C)
{
	int i,j,l,sum,x,y,k=1;
	for(i=1;i<=A->i;i++)
	{
		for(l=1;l<=B->j;l++)
		{
			sum = 0;
			for(j=1;j<=A->j;j++)
			{
				x=1,y=1;
				while(x<=A->tu)
				{
					if(i==A->data[x].i && j==A->data[x].j)
					{
						break;	
					}
					x++;
				}
				if(x<=A->tu)
				{
					while(y<=B->tu)
					{
						if(l==B->data[y].j && j==B->data[y].i)
						{
							break;
						}
						y++;
					}
				}
				if(x<=A->tu && y<=B->tu)
				{
					sum = sum + A->data[x].e*B->data[y].e;
				}
			}
			if(sum != 0)
			{
				C->data[k].i = i;
				C->data[k].j = l;
				C->data[k].e = sum;
				k++;
			}
		}
	}
	C->i = C->j = A->i;
	C->tu = k;
}
*/

void MultSMatrix(pTSMatrix A,pTSMatrix B,pTSMatrix C)
{
	int i,j,h=A->i,l=B->j,Qn=0;				//h,l分别为矩阵Q的行、列值,Qn为矩阵Q的非零元素个数,初值为0
	int *Qe;
	if(A->j != B->i)
	{
		exit(-1);
	}
	C->i = A->i;
	C->j = B->j;
	Qe = (int *)malloc(h*l*sizeof(int));	//Qe为矩阵Q的临时数组
	//矩阵Q的第i行j列的元素值存于*(Qe+(i-1)*l+j-1)中，处值为0			数组Qe[0]代表第一行*第一列 Qe[1]代表第一行*第二列 Qe[2]、Qe[3]一次类推
	for(i=0;i<h*l;i++)
	{
		*(Qe+i) = 0;					//赋初值0
	}
	for(i=1;i<=A->tu;i++)				//矩阵元素相乘，结果累加到Qe
	{
		for(j=1;j<B->tu;j++)
		{
			if(A->data[i].j==B->data[j].i)							//A->data[i].j==B->data[j].i确定数组行列能相乘的关系
			{
				*(Qe+(A->data[i].i-1)*l+B->data[j].j-1) += A->data[i].e*B->data[j].e;		//A->data[i].i-1)*l+B->data[j].j-1确定对应行列相乘在数组Qe中的位置
			}
		}
	}
	for(i=1;i<=A->i;i++)
	{
		for(j=1;j<=B->j;j++)
		{
			if(*(Qe+(i-1)*l+j-1)!=0)
			{
				Qn++;
				C->data[Qn].e = *(Qe+(i-1)*l+j-1);
				C->data[Qn].i = i;
				C->data[Qn].j = j;
			}
		}
	}
	free(Qe);
	C->tu = Qn;

/*
矩阵A			矩阵B
3 4 5 0			6 9	1 
6 0 5 0			5 2 0 
7 7 8 9			0 0 1 
				2 0 0
分别以A、B的1~tu为循环 满足A->data[i].j==B->data[j].i的时候能相乘，比如A->tu=3的时候A->data[A->tu].j=3也就是矩阵的A第三列,能与B的第三行相乘，
也就是B->data[B->tu].i=3时，同时相乘的结果存储在*(Qe+(i-1)*l+j-1)中，最后双循环分配到新的矩阵中
*/

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

/*
书本答案:
void printSMatrix(pTSMatrix TSM)
{
	int i;
	printf("%d行%d列%d个非零元素。\n",TSM->i,TSM->j,TSM->tu);
	printf("行 列 元素值\n");
	for(i=1;i<=TSM->tu)
	{
		printf("%2d%4d%8d\n",TSM->data[i].i,TSM->data[i].j,TSM->data[i].e);
	}
}
*/

void DestroySMatrix(pTSMatrix MS)
{
	MS->i = 0;
	MS->j = 0;
	MS->tu = 0;
}