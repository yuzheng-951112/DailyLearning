#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define MAXSTRLEN 40

typedef char SString[MAXSTRLEN+1];

void StrAssign(SString T,char *chars);
void Get_next(SString T,int nextval[]);
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

void Get_next(SString T,int nextval[])
{
	int i=1,j=0;
	nextval[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			i++;
			j++;
			if(T[i]!=T[j])
			{
				nextval[i]=j;
			}
			else
			{
				nextval[i]=nextval[j];
			}
		}
		else
		{
			j=nextval[j];
		}
	}
}
/*
1.T="ababaaaba"
			j	123456789			
		ģʽ��T ababaaaba			aaaaax  �������Ƚ�����ֱ�ӽ��ظ���a�Ĳ���ֱ��ȥ��(ababaaaba�п��Խ�"ab"����һ������"01"������)
	    next[j] 011234223			000005	
	 nextval[j] 010104210
1)��j=1ʱ,next[1]=0;
2)��j=2ʱ,��Ϊ�ڶ�λ�ַ�"b"��nextֵ��1,����һλ����"a",���ǲ����,����nextval[2]=next[2]=1;
3)��j=3ʱ,��Ϊ����λ�ַ�"a"��nextֵΪ1,�������һλ��"a"�Ƚϵ�֪�������,����nextval[3]=nextval[1]=0;��ͼ
			j   123
			T   aba
	  next[j]   011---->������1,��˲鿴T[1]�뱾λ�õ�T[3]�Ƿ����
   nextval[j]   010---->���T[1]=T[3],����nextval[3]=nextval[1]=0
4)j=4ʱ,����λ���ַ�"b"nextֵΪ2,������ڶ�λ��"b"��Ƚϵõ���������,���nextvak[4]=nextval[2]=1;��ͼ
			j   1234
			T   abab
	  next[j]   0112--->������2,��˲鿴T[2]�뱾λ�õ�T[4]�Ƿ����
   nextval[j]   0101--->��ΪT[2]=T[4],����nextval[4]=next[2]=1
5)��j=5ʱ,nextֵΪ3,������ַ�"a"��������ַ�"a"���,���nextval[5]=nextval[3]=0;
6)��j=6ʱ,nextֵΪ4,�������ַ�"a"����ĸ��ַ�"b"�����,���nextval[6]=j=4(j��ǰ����ֵΪ4);
7)��j=7ʱ,nextֵΪ2,���߸��ַ�"a"��ڶ����ַ�"b"�����,���nextval[7]=j=2;
8)��j=8ʱ,nextֵΪ2,�ھŸ��ַ�"b"��������ַ�"b"���,���nextval[8]=nextval[2]=1;
9)��j=9ʱ,nextֵΪ3,�ھŸ��ַ�"a"��������ַ�"a"���,���nextval[9]=nextval[3]=1��
�ܽ�:�Ľ�����KMP�㷨�������ڼ���nextֵ��ͬʱ�����aλ�ַ�����nextֵָ���bλ�ַ����,���aλ��nextval��ָ��bλ��nextvalֵ,�������,��
��aλ��nextvalֵ�������Լ�aλ��next��ֵ
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
			j = next[j];
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