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

	printf("请输主串s1:");
	gets(c);
	StrAssign(s1,c);
	StrPrint(s1);

	printf("请输子串s2:");
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

	printf("请输入搜索开始的位置:");
	scanf("%d",&pos);
	i = Index_KMP(s1,s2,pos,p);
	if(i)
	{
		printf("主串和子串在第%d个字符串处首次匹配\n",i);
	}
	else
	{
		printf("主串和子串匹配不\n");
	}
}

void StrAssign(SString T,char *chars)
{
	if(strlen(chars)>MAXSTRLEN)
	{
		printf("串长超过MAXSTRLEN!\n");
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
		模式串T ababaaaba			aaaaax  看起来比较明显直接将重复的a的步骤直接去掉(ababaaaba中可以将"ab"看成一个整体"01"绑起来)
	    next[j] 011234223			000005	
	 nextval[j] 010104210
1)当j=1时,next[1]=0;
2)当j=2时,因为第二位字符"b"的next值是1,而第一位就是"a",他们不相等,所以nextval[2]=next[2]=1;
3)当j=3时,因为第三位字符"a"的next值为1,所以与第一位的"a"比较得知他们相等,所以nextval[3]=nextval[1]=0;如图
			j   123
			T   aba
	  next[j]   011---->次数是1,因此查看T[1]与本位置的T[3]是否相等
   nextval[j]   010---->因此T[1]=T[3],所以nextval[3]=nextval[1]=0
4)j=4时,第四位的字符"b"next值为2,所以与第二位的"b"相比较得到结果是相等,因此nextvak[4]=nextval[2]=1;如图
			j   1234
			T   abab
	  next[j]   0112--->次数是2,因此查看T[2]与本位置的T[4]是否相等
   nextval[j]   0101--->因为T[2]=T[4],所以nextval[4]=next[2]=1
5)当j=5时,next值为3,第五个字符"a"与第三个字符"a"相等,因此nextval[5]=nextval[3]=0;
6)当j=6时,next值为4,第六个字符"a"与第四个字符"b"不相等,因此nextval[6]=j=4(j当前的数值为4);
7)当j=7时,next值为2,第七个字符"a"与第二个字符"b"不相等,因此nextval[7]=j=2;
8)当j=8时,next值为2,第九个字符"b"与第三个字符"b"相等,因此nextval[8]=nextval[2]=1;
9)当j=9时,next值为3,第九个字符"a"与第三个字符"a"相等,因此nextval[9]=nextval[3]=1。
总结:改进过的KMP算法，他是在计算next值的同时，如果a位字符与他next值指向的b位字符相等,则该a位的nextval就指向b位的nextval值,如果不等,则
该a位的nextval值就是他自己a位的next的值
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