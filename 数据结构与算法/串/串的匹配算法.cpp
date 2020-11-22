��#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define MAXSTRLEN 40

typedef char SString[MAXSTRLEN+1];

void StrAssign(SString T,char *chars);
void Get_next(SString T,int next[]);
int Index_KMP(SString S,SString T,int pos,int next[]);
int StrLength(SString T);
void StrPrint(SString T); 

void main()
{
	int i,j,*p,pos;
	char c[MAXSTRLEN+1];
	SString s1,s2;

	printf("��������s1:");
	gets(c);
	StrAssign(s1,c);
	StrPrint(s1);

	printf("�����Ӵ�s2:");
	gets(c);
	StrAssign(s2,c);
	StrPrint(s2);

	i = StrLength(s2);
	p = (int*)malloc(i*sizeof(int));
	Get_next(s2,p);
	for(j=1;j<=i;j++)
	{
		printf("%d ",*(p+j));
	}
	printf("\n");

	printf("������������ʼ��λ��:");
	scanf("%d",&pos);
	i = Index_KMP(s1,s2,pos,p);
	if(i)
	{
		printf("�������Ӵ��ڵ�%d���ַ������״�ƥ��\n",i);
	}
	else
	{
		printf("�������Ӵ�ƥ�䲻\n");
	}
}

void StrAssign(SString T,char *chars)
{
	if(strlen(chars)>MAXSTRLEN)
	{
		printf("��������MAXSTRLEN!\n");
		exit(-1);
	}
	else
	{
		T[0] = strlen(chars);
		for(int i=1;i<=T[0];i++)
		{
			T[i] = chars[i-1];
		}
	}
}

int StrLength(SString T)
{
	return T[0];
}

void StrPrint(SString T)
{
	for(int i=1;i<T[0]+1;i++)
	{
		printf("%c",T[i]);
	}
	printf("\n");
}

void Get_next(SString T,int next[])
{
	int i=1,j=0;
	next[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			i++;
			j++;
			next[i]=j;					//T[i]��ʾ��׺�ĵ����ַ���T[j]��ʾǰ׺�ĵ����ַ�
		}
		else
		{
			j=next[j];					//���ַ�����ͬ����jֵ����
		}
	}
}
/*
��next�ظ�����һ������ʱ���൱��ĳ����ĸ���ظ����֣���s2��aabaaaabaa 3�������Σ�Ϊ6��7��8����λ�ã�
�ڵ�һ�����ֳ��������֮ǰ�����ǳ���1 ��s2��abcdabcd 1����4�� ��Ϊ2��3��4��5λ�ã�

		{ 0 ��j=1ʱ
next[j] | MAX {K|1<k<j,��'P1......pk-1'='Pj-k+1......Pj-1'}���˼��ϲ���ʱ
		{ 1,�������

1.T="abcdex"
		j	123456
	ģʽ��T abcdex
	next[j] 011111
1)��j=1ʱ,next[1]=0;
2)��j=2ʱ,j��1��j-1��ֻ���ַ�"a",�����������next[2]=1;
3)��j=3ʱ,j��1��j-1����"ab",��Ȼ"a"��"b"�����,���������,next[3]=1;
4)�Ժ�ͬ��,�������մ�T����next[j]Ϊ011111
2.T="abcabx"
		j	123456
	ģʽ��T abcabx
	next[j] 011123
1)��j=1ʱ,next[1]=0;
2)��j=2ʱ,j��1��j-1��ֻ���ַ�"a",�����������next[2]=1;
3)��j=3ʱ,j��1��j-1����"ab",��Ȼ"a"��"b"�����,���������,next[3]=1;
4)��j=4ʱ,ͬ��,next[4]=1;
5)��j=5ʱ,��ʱj��1��j-1�Ĵ���"abca",ǰ׺�ַ�"a"���׺�ַ�"a"���,��˿��������kֵΪ2����'P1......pk-1'='Pj-k+1......Pj-1',�õ�p1=p4�����next[5]=2;
6)��j=6ʱ,j��1��j-1�Ĵ���"abcab",����ǰ׺�ַ�"ab"���׺"ab"���,����next[6]=3
*/

int Index_KMP(SString S,SString T,int pos,int next[])
{
	int i=pos,j=1;
	while(i<=S[0] && j<T[0])
	{
		if(j==0 || S[i]==T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];			//j�˻غ��ʵ�λ��,i��ֵ����
		}
	}
	if(j>T[0])
	{
		return i-j+1;
	}
	else
	{
		return 0;
	}
}