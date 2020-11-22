#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>
#define DIM 8

typedef struct Array
{
	int *base;			//数组元素地址
	int dim;			//数组维数
	int *bounds;		//数组维界地址
	int *constans;		//数组映像函数常量地址
}*pArray;
/*
假设Array = Arr[2][3][4] 则bounds中存放(2,3,4);
对于二维数组来说，Arr.constans[1]是每个元素所占的长度，Arr.constans[0]是每行元素所占的长度，故对于第i行j列的元素，在数组的位置为
(i*Arr.constans[0]+j*Arr.constans[1]),多维数组可以一次类推。对于每维确定的数组，若提前计算好(初始化数组时)constans的各个值，在求
基址时带入公式计算
*/

struct Array* Init_Arr(int,...);
void Assign(pArray,int,...);
int Value(pArray,...);
void Locate(pArray,va_list,int*);

void main()
{
	int i,j,k,e,dim=3,bounds1=2,bounds2=3,bounds3=4;
	pArray Arr;
	Arr = Init_Arr(dim,bounds1,bounds2,bounds3);
	printf("Arr->bounds = ");
	for(i=0;i<Arr->dim;i++)
	{
		printf("%d ",Arr->bounds[i]);
	}
	printf("\nArr->constans = ");
	for(i=0;i<Arr->dim;i++)
	{
		printf("%d ",Arr->constans[i]);
	}
	printf("\n");
	for(i=0;i<bounds1;i++)
	{
		for(j=0;j<bounds2;j++)
		{
			for(k=0;k<bounds3;k++)
			{
				Assign(Arr,i*100+j*10+k,i,j,k);
				e = Value(Arr,i,j,k);
				printf("Arr[%d][%d][%d] = %d ",i,j,k,e);
			}
			printf("\n");
		}
		printf("\n");
	}
}

struct Array* Init_Arr(int dim,...)
{
	int elemtotal=1;
	va_list ap;
	va_start(ap,dim);								//va_start();自动采集传给本函数的可变参数，并连带他的数目
	if(dim<1 || dim>DIM)
	{
		printf("数组维数超过范围!\n");
		exit(-1);
	}
	pArray Arr = (pArray)malloc(sizeof(Array)*1);
	Arr->dim = dim;
	if(!(Arr->bounds = (int*)malloc(sizeof(int)*dim)))
	{
		printf("数组维界地址分配失败!\n");
		exit(-1);
	}
	for(int i=0;i<dim;i++)
	{
		Arr->bounds[i] = va_arg(ap,int);
		if(Arr->bounds[i]<0)
		{
			exit(-1);
		}
		elemtotal *= Arr->bounds[i];				//元素的总数
	}
	va_end(ap);
	if(!(Arr->base = (int*)malloc(sizeof(int)*elemtotal)))
	{
		printf("数组元素分配失败!\n");
		exit(-1);
	}
	if(!(Arr->constans = (int*)malloc(sizeof(int*)*dim)))
	{
		printf("数组映像函数常量分配失败!\n");
		exit(-1);
	}
	Arr->constans[dim-1] = 1;
	for(i=dim-2;i>=0;--i)
	{
		Arr->constans[i] = Arr->constans[i+1] * Arr->bounds[i+1];
	}
	return Arr;
}

void Assign(pArray Arr,int e,...)
{
	int pos;
	va_list ap;
	va_start(ap,e);
	Locate(Arr,ap,&pos);
	*(Arr->base+pos) = e;
}

int Value(pArray Arr,...)
{
	int pos;
	va_list ap;
	va_start(ap,Arr);
	Locate(Arr,ap,&pos);
	return *(Arr->base+pos);
}

void Locate(pArray Arr,va_list ap,int* pos)
{
	int i,ind;
	*pos = 0;
	for(i=0;i<Arr->dim;i++)
	{
		ind = va_arg(ap,int);
		if(ind<0 || ind>=Arr->bounds[i])
		{
			exit(-1);
		}
		*pos += Arr->constans[i]*ind;
	}
}

/*
#include <stdarg.h>
#include <stdio.h>

void print(int arg,...)
{
	va_list ap;
	va_start(ap,arg);
	for(int i=0;i<arg;i++)
	{
		printf("%d ",va_arg(ap,int));
	}
	va_end(ap);
}

void main()
{
	print(4,1,2,3,4);
}
*/