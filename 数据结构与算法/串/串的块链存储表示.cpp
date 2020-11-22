#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define CHUNKSIZE 4

typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk* pNext; 
}Chunk,*pChunk;

typedef struct LString
{
	Chunk *head,*tail;
	int curlen;
}LString,*pLString;

void Init_String(pLString);
void Assign_String(pLString,char*);
bool Empty_String(pLString);
int Length_String(pLString);
void Print_String(pLString);
void Copy_String(pLString,pLString);				//重点 结构体可以整体复制
void Replace_String(pLString,pLString,pLString);
int Index_String(pLString,pLString,int);
void Sub_String(LString,pLString,int);
int Compara_String(pLString,pLString);
void Delete_Str(pLString,int,int);

void main()
{
	char *s1="ABCDEFGH",*s2="12345",*s3="",*s4="asd#tr",*s5="ABCD";
	LString Stra,Strb,Strc,Strd;
	Init_String(&Stra);
	Init_String(&Strb);

	printf("初始化字符串t1后,串t1空否? %d(1:空 0:否) 串长=%d\n",Empty_String(&Stra),Length_String(&Stra));
	Assign_String(&Stra,s1);
	printf("串t1为:");
	Print_String(&Stra);

	printf("初始化字符串t2后,串t2空否? %d(1:空 0:否) 串长=%d\n",Empty_String(&Strb),Length_String(&Strb));
	Assign_String(&Strb,s2);
	printf("串t2为:");
	Print_String(&Strb);

	Copy_String(&Strc,&Stra);				//Copy函数免去了初始化
	printf("串t3为:");
	Print_String(&Strc);

	Init_String(&Strd);
	Assign_String(&Strd,s5);
	printf("串t4为:");
	Print_String(&Strd);

	Replace_String(&Strc,&Strd,&Strb);
	printf("用串t2取代串t3中的串t4,串t3为:");
	Print_String(&Strc);


}

void Init_String(pLString Str)
{
	Str->curlen = 0;
	Str->head = NULL;
	Str->tail = NULL;
}

void Assign_String(pLString Str,char *chars)
{
	int i,j,k,l;
	Chunk *p,*q;
	i = strlen(chars);
	if(!i || strchr(chars,' '))
	{
		printf("字符串中存在空格!");
		exit(-1);
	}
	Str->curlen = i;
	j = i/CHUNKSIZE;
	if(i%CHUNKSIZE)
	{
		j++;
	}
	for(k=0;k<j;k++)
	{
		p = (pChunk)malloc(sizeof(Chunk));
		if(!p)
		{
			printf("内存分配失败!");
			exit(-1);
		}
		if(k == 0)
		{
			Str->head = q = p;
		}
		else
		{
			q->pNext = p;
			q = p;
		}
		for(l=0;l<CHUNKSIZE && chars;l++)
		{
			*(q->ch+l) = *chars++;
		}
		if(!*chars)
		{
			Str->tail = q;
			p->pNext = NULL;
			for(;l<CHUNKSIZE;l++)
			{
				*(q->ch+l) = ' ';
			}
		}
	}
}

void Copy_String(pLString Str1,pLString Str2)
{
	pChunk h = Str2->head,p,q;
	Str1->curlen = Str2->curlen;
	if(h)
	{
		p = Str1->head = (pChunk)malloc(sizeof(Chunk));
		*p = *h;
		h = h->pNext;
		while(h)
		{
			q = p;
			p = (pChunk)malloc(sizeof(Chunk));
			q->pNext = p;
			*p = *h;							//复制整个结构体
			h = h->pNext;
		}
		p->pNext = NULL;
		Str1->tail = p;
	}
}

void Sub_String(pLString sub,pLString Str,int pos,int len)
{
	Chunk *p,*q;
	int i,k,n,flag=1;
	if(pos<1 || pos>Str->curlen || len<0 || len+pos-1>Str->curlen)
	{
		printf("位置和长度范围错误!");
		exit(-1);
	}
	n = len/CHUNKSIZE;
	if(len%CHUNKSIZE)
	{
		n++;
	}
	p = (pChunk)malloc(sizeof(Chunk));
	sub->head = p;
	for(i=0;i<n;i++)
	{
		q = (pChunk)malloc(sizeof(Chunk));
		p->pNext = q;
		p = q;
	}
	p->pNext = NULL;
	sub->tail = p;
	sub->curlen = len;
	for(i=len%CHUNKSIZE;i<CHUNKSIZE;i++)
	{
		*(p->ch+i) = ' ';
	}
	q = sub->head;
	i = 0;
	p = Str->head;
	n = 0;
	while(flag)
	{
		for(k=0;k<CHUNKSIZE;k++)
		{
			if(*(p->ch+k) != ' ')
			{
				n++;
				if(n>=pos && n<=pos+len-1)
				{
					if(i == CHUNKSIZE)
					{
						q = q->pNext;
						i = 0;
					}
					*(q->ch+i) = *(p->ch+k);
					i++;
					if(n == pos+len+-1)
					{
						flag = 0;
						break;
					}
				}
			}
		}
		p = p->pNext;
	}
}

int Compara_String(pLString Str1,pLString Str2)
{
	int i=0;
	pChunk ps = Str1->head,pt = Str2->head;
	int js = 0;jt = 0;
	while(i < Str1->curlen && )
	{
		i++;
		while(*(ps->ch+js) == ' ')		//跳过空白符
		{
			js++;
			if(js == CHUNKSIZE)
			{
				ps = ps->pNext;
				js = 0;
			}
		}
		while(*(ps->ch+js) == ' ')
		{
			jt++;
			if(jt == CHUNKSIZE)
			{
				pt = pt->pNext;
				jt = 0;
			}
		}
		if(*(ps->ch+js) != *(pt->ch+jt))
		{
			return *(ps->ch+js) - *(pt->ch+jt);
		}
		else
		{
			js++;
			if(js == CHUNKSIZE)
			{
				ps = ps->pNext;
				js = 0;
			}
			jt++;
			if(jt == CHUNKSIZE)
			{
				pt = pt->pNext;
				jt = 0;
			}
		}
	}
	return Str1->curlen - Str2->curlen;
}

int Index_String(pLString Str1,pLString Str2,int pos)
{
	int i,n,m;
	LString sub;
	if(pos>=1 && pos<=Length_String(Str1))
	{
		n = Length_String(Str1);
		m = Length_String(Str2);
		i = pos;
		while(i+m-1<=n)				//子串长度+位置<=主串
		{
			Sub_String(&sub,Str1,i,m);
			if(Compare_String(&sub,Str2) != 0)
			{
				i++;
			}
			else
			{
				return i;
			}
		}
	}
}

void Delete_Str(pLString Str1,int pos,int len)
{
	
}

void Replace_String(pLString Str1,pLString Str2,pLString Str3)
{
	int i=1;
	if(Empty_String(Str2))
	{
		printf("被取代串为空!");
		exit(-1);
	}
	do
	{
		i = Index_String(Str1,Str2,i);
		if(i)
		{
			Delete_Str(Str1,i,Length_Str(Str2));
			Insert_Str();
		}
	}while(i);
}

void Print_String(pLString Str)
{
	int i=0,j;
	pChunk h = Str->head;
	while(i < Str->curlen)
	{
		for(j=0;j<CHUNKSIZE;j++)
		{
			if(*(h->ch+j) != ' ')
			{
				printf("%c",*(h->ch+j));
				i++;
			}
		}
		h = h->pNext;
	}
	printf("\n");
}

int Length_String(pLString Str)
{
	return Str->curlen;
}

bool Empty_String(pLString Str)
{
	if(Str->curlen)
	{
		return false;
	}
	else
	{
		return true;
	}
}