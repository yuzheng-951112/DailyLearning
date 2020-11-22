#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRLEN 40

typedef char SString[MAXSTRLEN+1];

void StrAssign(SString T,char *chars);
int StrLength(SString T);
void StrPrint(SString T);
void StrCopy(SString T,SString S);
char StrCompare(SString T,SString S);
void Strconcat(SString T,SString S,SString H);			//合并两个字符串
void SubString(SString T,SString S,int i,int j);		//在主串中取子串
void StrDelete(SString T,int i,int j);					
void StrInsert(SString T,SString S,int i);
int Index(SString T,SString S,int pos);					//在串s1中找到s2对应的位置
void Strclear(SString T);
void Replace(SString T,SString S,SString H);

bool Strempty(SString T);

int main()
{
	int i,j,m;
	char k,c[MAXSTRLEN+1];
	SString s1,s2,s3;

	printf("请输入串s1:");
	gets(c);
	StrAssign(s1,c);
	StrPrint(s1);

	printf("请输入串s2:");
	gets(c);
	StrAssign(s2,c);
	StrPrint(s2);
/*
	k = StrCompare(s1,s2);
	if(k == 0)
	{
		printf("串s1=串s2");
	}
	else if(k > 0)
	{
		printf("串s1>串s2");
	}
	else
	{
		printf("串s1<串s2");
	}

	Strconcat(s1,s2,s3);
	printf("s1与s2串联的到的串s3为:");

	StrCopy(s1,s3);
	printf("s1复制的串s3为:");

//	Strclear(s3);
	printf("求串s2的子串,请输入串的起始位置,子串长度:");
	scanf("%d,%d",&i,&j);
	SubString(s3,s2,i,j);

	printf("从串s1中pos个字符起,删除len个字符,请输入pos,len:");
	scanf("%d,%d",&i,&j);
	StrDelete(s1,i,j);

	printf("在串s1的第pos个字符起,插入串s2,请输入pos:");
	scanf("%d",&i);
	StrInsert(s1,s2,i);

	printf("在主串s1第pos后找到子串s2对应的位置:");
	scanf("%d",&i);
	printf("s2在s1的第%d个匹配!\n",Index(s1,s2,i));
*/	
	SubString(s3,s2,1,1);
	StrPrint(s3);
	Replace(s1,s2,s3);
	StrPrint(s1);
	return 0;
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

void StrCopy(SString T,SString S)
{
	for(int i=0;i<=T[0];i++)
	{
		S[i] = T[i];
	}
	S[0] = T[0];
}

void Strconcat(SString T,SString S,SString H)
{
	int i;
	if(T[0]+S[0] > MAXSTRLEN)
	{
		for(i=1;i<=T[0];i++)
		{
			H[i] = T[i];
		}
		for(i=1;i<=MAXSTRLEN-T[0];i++)
		{
			H[T[0]+i] = S[i];
		}
		H[0] = MAXSTRLEN;
	}
	else
	{
		for(i=1;i<=T[0];i++)
		{
			H[i] = T[i];
		}
		for(i=1;i<=S[0];i++)
		{
			H[T[0]+i] = S[i];
		}
		H[0] = T[0] + S[0];
	}
}

void SubString(SString T,SString S,int i,int j)
{
	for(int k=1;k<=j;k++)
	{
		T[k] = S[k+i-1];
	}
	T[0] = j;
}

void StrDelete(SString T,int i,int j)
{
	if(j<=T[0]+1-i && j>=1 && i>=1 && i<=T[0])
	{
		for(int k=i;k+j<=T[0];k++)
		{
			T[k] = T[k+j];
		}
		T[0] = T[0] - j;
	}
	else
	{
		printf("非法删除!\n");
		exit(-1);
	}
}

void StrInsert(SString T,SString S,int i)
{
	int k,m = S[0];
	if(T[0]+S[0]<=MAXSTRLEN && i>0 && i<T[0])
	{
		for(k=1;k<=T[0]+1-i;k++)
		{
			S[k+S[0]] = T[i+k-1];
		}
		S[0] = S[0] + k;
		T[0] = T[0] - k;
		for(k=1;k<=S[0];k++)
		{
			T[i+k-1] = S[k]; 
		}
		T[0] = T[0] + S[0];
		S[0] = m;
	}
	else
	{
		printf("非法插入!\n");
		exit(-1);
	}
}

int Index(SString T,SString S,int pos)
{
	int i,j;
	if(pos<=T[0] && pos>=1)
	{
		i = pos;
		j = 1;
		while(j<=S[0] && i<=T[0])
		{
			if(S[j] == T[i])
			{
				i++;
				j++;
			}
			else
			{
				j = 1;
				i = i-j+2; 
			}
		}
		if(j > S[0])
		{
			return i-S[0];
		}
		else
		{
			return 0;
		}
	}
	else
	{
		printf("位置范围错误!\n");
		exit(-1);
	}
}

void Replace(SString T,SString S,SString H)
{
	int pos,i=1;
	while((pos = Index(T,H,i)) != 0)
	{
		StrDelete(T,pos,H[0]);
		StrInsert(T,S,pos);
		i = pos + S[0];
	}
}

char StrCompare(SString T,SString S)
{
	for(int i=1;i<T[0]&&i<S[0];i++)
	{
		if(S[i] != T[i])
		{
			return T[i] - S[i];
		}
	}
	return T[0] - S[0];
}

void Strclear(SString T)
{
	T[0] = 0;
}

bool Strempty(SString T)
{
	if(T[0] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}