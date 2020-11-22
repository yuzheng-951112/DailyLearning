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
	printf("�������A!\n");
	CreateSMatrix(&A);
	printSMatrix(&A);
	printf("�ɾ���A���ƾ���B:\n");
	CopySMatrix(A,&B);
	printSMatrix(&B);
	DestroySMatrix(&B);
	printf("���پ����:\n");
	printSMatrix(&B);
	printf("��������B2:(�����A���С�������ͬ���С��зֱ�Ϊ%d,%d)\n",A.i,A.j);
	CreateSMatrix(&B);
	printSMatrix(&B);
/*	printf("����C(A+B):\n");
	AddSMatrix(&A,&B,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
	printf("����C2(A-B):\n");
	SubtSMatrix(&A,&B,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
	printf("����C3(A��ת�þ���)\n");
	TransposeSMatrix(&A,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
	DestroySMatrix(&A);
	DestroySMatrix(&B);
	printf("��������A2:\n");
	CreateSMatrix(&A);
	printSMatrix(&A);
	printf("��������B3:(����Ӧ������A2��������ͬ=%d)\n",A.j);
	CreateSMatrix(&B);
	printSMatrix(&B);
	printf("����C5(A*B):\n");
*/	MultSMatrix(&A,&B,&C);
	printSMatrix(&C);
	DestroySMatrix(&C);
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

void CopySMatrix(TSMatrix A,pTSMatrix B)
{
	*B = A;								//�����ǽ������ֵcopy,�����Ӻ����������β�A,B���ͷ���Ҳ��Ӱ��
}

/*
TSMatrix A,B;
��ʼ���Ǹ��ṹ����
����һ:
void CopySMatrix(TSMatrix A,pTSMatrix B)
{
	*B = A;								
}
pTSMatrix A,B;
��ʼ���Ǹ��ṹ���ַ
������:
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
�鱾��:
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
	Mp = &M->data[1];		//Mp�ĳ�ֵָ�����M�ķ���Ԫ���׵�ַ
	Np = &N->data[1];		//Np�ĳ�ֵָ�����N�ķ���Ԫ���׵�ַ
	Me = &M->data[M->tu];	//Meָ�����M�ķ���Ԫ��β��ַ
	Ne = &N->data[N->tu];	//Neָ�����N�ķ���Ԫ��β��ַ
	Qh = Qe = Q->data;		//Qh��Qe�ĳ�ֵָ�����Q�ķ���Ԫ���׵�ַ��ǰһ��ַ
	while(Mp<=Me && Np<=Ne)
	{
		Qe++;
		switch(comp(Mp->i,Np->i))
		{
		case 1:*Qe = *Mp;
				Mp++;
				break;
		case 0:switch(comp(Mp->j,Np->j))	//M��N����ǰ����Ԫ�ص�����ȣ������Ƚ���
			   {
				case 1:*Qe = *Mp;
						Mp++;
						break;
				case 0:*Qe = *Mp;
						Qe->e += Np->e;
						if(!Qe->e)			//Ԫ��ֵΪ0��������ѹ������
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
	if(Mp>Me)		//����M��Ԫ��ȫ���������
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
	Q->tu = Qe-Qh;	//����Q�ķ���Ԫ�ظ���
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
				if(A->data[p].j == col)					//����data.j������������(�����Ϳ��԰�CreateSMatrix�����н��������˳��)
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
	int i,j,h=A->i,l=B->j,Qn=0;				//h,l�ֱ�Ϊ����Q���С���ֵ,QnΪ����Q�ķ���Ԫ�ظ���,��ֵΪ0
	int *Qe;
	if(A->j != B->i)
	{
		exit(-1);
	}
	C->i = A->i;
	C->j = B->j;
	Qe = (int *)malloc(h*l*sizeof(int));	//QeΪ����Q����ʱ����
	//����Q�ĵ�i��j�е�Ԫ��ֵ����*(Qe+(i-1)*l+j-1)�У���ֵΪ0			����Qe[0]�����һ��*��һ�� Qe[1]�����һ��*�ڶ��� Qe[2]��Qe[3]һ������
	for(i=0;i<h*l;i++)
	{
		*(Qe+i) = 0;					//����ֵ0
	}
	for(i=1;i<=A->tu;i++)				//����Ԫ����ˣ�����ۼӵ�Qe
	{
		for(j=1;j<B->tu;j++)
		{
			if(A->data[i].j==B->data[j].i)							//A->data[i].j==B->data[j].iȷ��������������˵Ĺ�ϵ
			{
				*(Qe+(A->data[i].i-1)*l+B->data[j].j-1) += A->data[i].e*B->data[j].e;		//A->data[i].i-1)*l+B->data[j].j-1ȷ����Ӧ�������������Qe�е�λ��
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
����A			����B
3 4 5 0			6 9	1 
6 0 5 0			5 2 0 
7 7 8 9			0 0 1 
				2 0 0
�ֱ���A��B��1~tuΪѭ�� ����A->data[i].j==B->data[j].i��ʱ������ˣ�����A->tu=3��ʱ��A->data[A->tu].j=3Ҳ���Ǿ����A������,����B�ĵ�������ˣ�
Ҳ����B->data[B->tu].i=3ʱ��ͬʱ��˵Ľ���洢��*(Qe+(i-1)*l+j-1)�У����˫ѭ�����䵽�µľ�����
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
�鱾��:
void printSMatrix(pTSMatrix TSM)
{
	int i;
	printf("%d��%d��%d������Ԫ�ء�\n",TSM->i,TSM->j,TSM->tu);
	printf("�� �� Ԫ��ֵ\n");
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