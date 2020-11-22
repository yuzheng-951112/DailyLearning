、#include <stdio.h>
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
			next[i]=j;					//T[i]表示后缀的单个字符，T[j]表示前缀的单个字符
		}
		else
		{
			j=next[j];					//若字符不相同，则j值回溯
		}
	}
}
/*
当next重复出现一个数次时，相当于某个字母在重复出现，如s2：aabaaaabaa 3出现三次（为6、7、8三个位置）
在第一轮数字出排列完成之前，都是出现1 如s2：abcdabcd 1出现4次 （为2、3、4、5位置）

		{ 0 当j=1时
next[j] | MAX {K|1<k<j,且'P1......pk-1'='Pj-k+1......Pj-1'}当此集合不空时
		{ 1,其他情况

1.T="abcdex"
		j	123456
	模式串T abcdex
	next[j] 011111
1)当j=1时,next[1]=0;
2)当j=2时,j由1到j-1就只有字符"a",属于其他情况next[2]=1;
3)当j=3时,j由1到j-1串是"ab",显然"a"与"b"不相等,属其他情况,next[3]=1;
4)以后同理,所以最终此T串的next[j]为011111
2.T="abcabx"
		j	123456
	模式串T abcabx
	next[j] 011123
1)当j=1时,next[1]=0;
2)当j=2时,j由1到j-1就只有字符"a",属于其他情况next[2]=1;
3)当j=3时,j由1到j-1串是"ab",显然"a"与"b"不相等,属其他情况,next[3]=1;
4)当j=4时,同上,next[4]=1;
5)当j=5时,此时j由1到j-1的串是"abca",前缀字符"a"与后缀字符"a"相等,因此可以推算出k值为2（由'P1......pk-1'='Pj-k+1......Pj-1',得到p1=p4）因此next[5]=2;
6)当j=6时,j由1到j-1的串是"abcab",由于前缀字符"ab"与后缀"ab"相等,所以next[6]=3
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
			j = next[j];			//j退回合适的位置,i的值不变
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