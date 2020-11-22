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
void Strconcat(SString T,SString S,SString H);			//�ϲ������ַ���
void SubString(SString T,SString S,int i,int j);		//��������ȡ�Ӵ�
void StrDelete(SString T,int i,int j);					
void StrInsert(SString T,SString S,int i);
int Index(SString T,SString S,int pos);					//�ڴ�s1���ҵ�s2��Ӧ��λ��
void Strclear(SString T);
void Replace(SString T,SString S,SString H);

bool Strempty(SString T);

int main()
{
	int i,j,m;
	char k,c[MAXSTRLEN+1];
	SString s1,s2,s3;

	printf("�����봮s1:");
	gets(c);
	StrAssign(s1,c);
	StrPrint(s1);

	printf("�����봮s2:");
	gets(c);
	StrAssign(s2,c);
	StrPrint(s2);
/*
	k = StrCompare(s1,s2);
	if(k == 0)
	{
		printf("��s1=��s2");
	}
	else if(k > 0)
	{
		printf("��s1>��s2");
	}
	else
	{
		printf("��s1<��s2");
	}

	Strconcat(s1,s2,s3);
	printf("s1��s2�����ĵ��Ĵ�s3Ϊ:");

	StrCopy(s1,s3);
	printf("s1���ƵĴ�s3Ϊ:");

//	Strclear(s3);
	printf("��s2���Ӵ�,�����봮����ʼλ��,�Ӵ�����:");
	scanf("%d,%d",&i,&j);
	SubString(s3,s2,i,j);

	printf("�Ӵ�s1��pos���ַ���,ɾ��len���ַ�,������pos,len:");
	scanf("%d,%d",&i,&j);
	StrDelete(s1,i,j);

	printf("�ڴ�s1�ĵ�pos���ַ���,���봮s2,������pos:");
	scanf("%d",&i);
	StrInsert(s1,s2,i);

	printf("������s1��pos���ҵ��Ӵ�s2��Ӧ��λ��:");
	scanf("%d",&i);
	printf("s2��s1�ĵ�%d��ƥ��!\n",Index(s1,s2,i));
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
		printf("�Ƿ�ɾ��!\n");
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
		printf("�Ƿ�����!\n");
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
		printf("λ�÷�Χ����!\n");
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