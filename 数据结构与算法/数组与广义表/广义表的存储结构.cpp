#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define MAXSTRLEN 40

typedef char SString[MAXSTRLEN+1];
typedef enum{
	ATOM, LIST	                          // ATOM==0:原子 LIST==1:子表                     
} ElemTag; 
typedef struct GLNode
{
	ElemTag tag;						//公共部分，用于区分原子结构和表节点
	union								//原子节点和表节点的联合部分
	{
		char atom;						//atom是原子的值域，
		struct
		{
			struct GLNode *hp,*tp;
		}ptr;							//ptr是表节点的指针域，prt.hp和prt.tp分别指向表头和表尾
	};
}*GList,GLNode;

void InitGList(GList &);
int GListDepth(GList);
int GListEmpty(GList);
int GListLength(GList);
void StrAssign(SString,char *);
void CreateGList(GList &,SString);
void sever(SString str,SString hstr);
void CopyGList(GList &,GList &);
void Traverse_GL(GList,void(*v)(char));
void Destroy_GL(GList);
GList GetHead(GList);
GList GetTail(GList);
void InsertFirst(GList &,GList);
void DeleteFirst_GL(GList &,GList &);
void visit(char e);

bool Strempty(SString T);
void StrCopy(SString T,SString S);
void Strclear(SString T);

void main()
{
	char p[80];
	SString t;
	GList L,M;									//这里要令初值为地址，同时InitGList函数必须用引用直接使原值L=NULL,不然在函数GListDepth中会出现A没有初始化为NULL的情况，同时A->tag也未设值，出现访问未分配地址的情况
	InitGList(L);
	InitGList(M);
	printf("空广义表L的深度=%d 1是否空? %d(1:是 0:否)\n",GListDepth(L),GListEmpty(L));
	printf("请输入广义表1(书写形式:空表:(),单原子:a,其他:(a,(b),b):\n");
	gets(p);
	StrAssign(t,p);
	CreateGList(L,t);							//这里不能直接导入地址，函数执行完后形参释放，内存虽然分配了，但是跟形参有关的内容全部释放
	printf("广义表L的长度=%d GListLength(L)");
	printf("广义表L的深度=%d 1是否空? %d(1:是 0:否)\n",GListDepth(L),GListEmpty(L));
	printf("遍历广义表1:\n");
	Traverse_GL(L,visit);						//这里的visit相当于一个函数
	printf("\n复制广义表m=1\n");
	CopyGList(L,M);
	printf("遍历广义表1:\n");
	Traverse_GL(M,visit);
	Destroy_GL(M);
	M = GetHead(L);
	printf("\nM是L的表尾,遍历广义表M:\n ");
	Traverse_GL(M,visit);
	Destroy_GL(M);
	M = GetTail(L);
	printf("\nM是L的表尾,遍历广义表M:\n ");
	Traverse_GL(M,visit);
	InsertFirst(M,L);
	printf("\n插入L为M的表头,遍历广义表M:\n");
	Traverse_GL(M,visit);
	printf("\n删除M的表头,遍历广义表M:\n");
	Destroy_GL(L);
	DeleteFirst_GL(M,L);
	Traverse_GL(M,visit);
	printf("\n");
//	Destroy_GL(M);
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

char StrCompare(SString T,SString S)
{
	for(int i=1;i<=T[0]&&i<=S[0];i++)
	{
		if(S[i] != T[i])
		{
			return T[i] - S[i];
		}
	}
	return T[0] - S[0];
}

int StrLength(SString T)
{
	return T[0];
}

void SubString(SString T,SString S,int i,int j)
{
	for(int k=1;k<=j;k++)
	{
		T[k] = S[k+i-1];
	}
	T[0] = j;
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

void Strclear(SString T)
{
	T[0] = 0;
}

void StrCopy(SString T,SString S)
{
	for(int i=0;i<=T[0];i++)
	{
		S[i] = T[i];
	}
	S[0] = T[0];
}

void InitGList(GList &A)
{
	A = NULL;
}

int GListLength(GList L)
{
	if(!L)
		return 0;
	else
	{
		int i=1;
		GList p;
		p = L;
		while(p->ptr.tp)
		{
			i++;
			p = p->ptr.tp;
		}
		return i;
	}
}

int GListDepth(GList A)
{
	int max,dep;
	GList pp;
	if(!A)
		return 1;								//这里的意思是存在空地址情况(),空表深度为1
	if(A->tag == ATOM)
		return 0;								//原子深度为0
	for(max=0,pp=A;pp;pp=pp->ptr.tp)			//递归算法
	{
		dep = GListDepth(pp->ptr.hp);
		if(dep>max)
			max = dep;
	}
	return max+1;
}

int GListEmpty(GList A)
{
	if(!A)
		return 1;
	else
		return 0;
}

void CreateGList(GList &A,SString S)
{
	SString sub,hsub,emp;
	GList p,q;
	StrAssign(emp,"()");
	if(!StrCompare(S,emp))
		A = NULL;
	else
	{
		if(!(A=(GList)malloc(sizeof(GLNode))))
			exit(-1);
		if(StrLength(S)==1)							//S为单原子
		{
			A->tag = ATOM;
			A->atom = S[1];							//创建单原子广义表
		}
		else
		{
			A->tag = LIST;
			p = A;
			SubString(sub,S,2,StrLength(S)-2);		//脱外层括号
			do
			{
				sever(sub,hsub);					//从sub中分离出表头串hsub，表尾sub
				CreateGList(p->ptr.hp,hsub);
				q = p;
				if(!Strempty(sub))
				{
					if(!(p=(GList)malloc(sizeof(GLNode))))
						exit(-1);
					p->tag = LIST;
					q->ptr.tp = p;
				}
			}while(!Strempty(sub));
			q->ptr.tp = NULL;
		}
	}

}

void sever(SString str,SString hstr) 
{
	int n,i,k;  
	SString ch,c1,c2,c3;
	n = StrLength(str);
	StrAssign(c1,",");
	StrAssign(c2,"(");
	StrAssign(c3,")");
	SubString(ch,str,1,1);
	for(i = 1,k = 0;i <= n && StrCompare(ch,c1) || k != 0; ++i)
	{ 
		SubString(ch, str, i, 1);
		if(!StrCompare(ch, c2))								//假设广义表((a,b),c),那么(a,b),c在(a,b)识别时k!=0使括号内的逗号不被检查
			++k;
		else if(!StrCompare(ch,c3))
			--k;
	}
	if(i <= n)
	{
		SubString(hstr, str, 1, i-2);
		SubString(str, str, i, n - i + 1);
	}
	else
	{
		StrCopy(str, hstr);
		Strclear(str);
	}
}

void CopyGList(GList &L,GList &M)
{
	if(!L)
		M = NULL;
	else
	{
		if(!(M=(GList)malloc(sizeof(GLNode))))
			exit(-1);
		M->tag = L->tag;
		if(L->tag==ATOM)
			M->atom = L->atom;
		else
		{
			CopyGList(L->ptr.hp,M->ptr.hp);
			CopyGList(L->ptr.tp,M->ptr.tp);
		}
	}
}

void Traverse_GL(GList L,void(*v)(char))						//这里相当于visit函数为void char *类型
{
	if(L)
		if(L->tag==ATOM)
			v(L->atom);
		else
		{
			Traverse_GL(L->ptr.hp,v);
			Traverse_GL(L->ptr.tp,v);
		}
}

GList GetHead(GList L)
{
	GList h;
	if(!L)
	{
		printf("空表无表头!\n");
		exit(-1);
	}
	CopyGList(L->ptr.hp,h);
	return h;
}

GList GetTail(GList L)
{
	GList h;
	if(!L)
	{
		printf("空表无表头!\n");
		exit(-1);
	}
	CopyGList(L->ptr.tp,h);
	return h;
}

void InsertFirst(GList &M,GList L)
{
	GList p = (GList)malloc(sizeof(GLNode));
	if(!p)
		exit(-1);
	p->tag = LIST;
	p->ptr.hp = L;
	p->ptr.tp = M;
	M = p;
}

void DeleteFirst_GL(GList &L,GList &e)
{
	GList p;
	e = L->ptr.hp;
	p = L;
	L = L->ptr.tp;
	free(p);
}

void Destroy_GL(GList L)
{
	GList q1,q2;
	if(L)
	{
		if(L->tag==ATOM)
		{
			free(L);
			L = NULL;
		}
		else
		{
			q1 = L->ptr.hp;
			q2 = L->ptr.tp;
			free(L);
			L = NULL;
			Destroy_GL(q1);
			Destroy_GL(q2);
		}
	}
}

void visit(char e)
{
	printf("%c ", e);
}
