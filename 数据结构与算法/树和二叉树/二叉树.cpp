#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_TREE_SIZE 100
#define NIL 0
typedef int SqBiTree[MAX_TREE_SIZE];

typedef struct position
{
	int level,order;
}pos;

void InitBiTree(SqBiTree);
void CreateBiTree(SqBiTree);
int EmptyBiTree(SqBiTree);
int DepthBiTree(SqBiTree);
int BootBiTree(SqBiTree);
int LengthAtomBiTree(SqBiTree);
void LevelOrderTraverse(SqBiTree);
void PreOrderTraverse(SqBiTree,int);
void PreTraverse(SqBiTree,int);
void InOrderTraverse(SqBiTree,int);
void InTraverse(SqBiTree,int);
void PostOrderTraverse(SqBiTree,int);
void PostTraverse(SqBiTree,int);
int Value(SqBiTree,pos);
void Assign(SqBiTree,pos,int);
int findpos(SqBiTree T,int e);
int Parent(SqBiTree,int);
int LeftChild(SqBiTree,int);
int RightChild(SqBiTree,int);
int LeftSibling(SqBiTree,int);
int RightSibling(SqBiTree,int);
void InsertChlid(SqBiTree,SqBiTree,int,int);
void Move(SqBiTree,SqBiTree,int,int);
void Print(SqBiTree);			//��㣬���������������
void DeleteChild(SqBiTree,int,int);
void ClearBiTree(SqBiTree);

void main()
{
	int e,j;
	pos p;
	SqBiTree T,S;
	InitBiTree(T);
	CreateBiTree(T);
/*	printf("������������,���շ�?%d(1:�� 0:��)\n",EmptyBiTree(T));
	printf("������������,�������=%d\n",DepthBiTree(T));
	printf("�������ĸ�Ϊ:%d\n",BootBiTree(T));
	printf("�������������:\n");
	LevelOrderTraverse(T);
	printf("�������������:\n");
	PreOrderTraverse(T,1);
	printf("\n�������������:\n");
	InOrderTraverse(T,1);
	printf("\n�������������:\n");
	PostOrderTraverse(T,1);
	printf("\n��������޸ĵĲ�ź����:");
	scanf("%d,%d",&p.level,&p.order);
	e = Value(T,p);
	printf("���޸ĵ�ֵΪ%d,��������ֵ:",e);
	scanf("%d",&e);
	Assign(T,p,e);
	printf("�������������:\n");
	PreOrderTraverse(T,1);
	printf("�ڵ�%d��˫��Ϊ%d:",e,Parent(T,e));
	printf("���Һ��ӷֱ�Ϊ%d %d:",LeftChild(T,e),RightChild(T,e));
	printf("�����ֱֵܷ�Ϊ%d %d:",LeftSibling(T,e),RightSibling(T,e));
	printf("����������Ϊ�յ���S:");*/
	InitBiTree(S);
	CreateBiTree(S);
	printf("��S�嵽��T��,������T������˫�׽ڵ�,SΪ��(0)��(1)����:");
	scanf("%d,%d",&e,&j);
	InsertChlid(T,S,e,j);
	Print(T);
	printf("ɾ���������������ɾ���������ڵ�Ĳ�� ������� ��(0)��(1)����");
	scanf("%d,%d",&e,&j);
	DeleteChild(T,e,j);
	Print(T);
	ClearBiTree(T);
	printf("��������������շ�?%d(1:�� 0:��)\n",EmptyBiTree(T));
	printf("�������ĸ�Ϊ:%d\n",BootBiTree(T));
}

void InitBiTree(SqBiTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
		T[i] = NIL;
}

void CreateBiTree(SqBiTree T)
{
	int i,n;
	/*			�������洢�����ַ���
	char s[MAX_TREE_SIZE];
	printf("�밴������ڵ��ֵ(�ַ�),�ո��ʾ�սڵ㣬�ڵ�����<=%d:\n",MAX_TREE_SIZE);
	printf("���� abcdefg\n");
	gets(s);
	n = strlen(s);
	for(i=0;i<=n;i++)
	{
		T[i] = s[i];
		if(i!=0 && T[(i+1)/2-1] == NIL && T[i]!=NIL)
		{
			printf("������˫�׵ķǸ��ڵ�%c\n",T[i]);
			exit(-1);
		}
	}
	for(i=n;i<MAX_TREE_SIZE;i++)
		T[i] = NIL;
	*/
	i=0;
	printf("�밲��˳������ڵ��ֵ(����),0��ʾ�սڵ�,����999����,�ڵ���<=%d\n",MAX_TREE_SIZE);
	while(1)
	{
		scanf("%d",&T[i]);
		if(T[i]==999)
				break;
		if(i!=0 && T[(i+1)/2-1]==NIL && T[i]!=NIL)//�˽ڵ�(����)��˫���Ҳ��Ǹ�
		{
			printf("������˫�׵ķǸ��ڵ�!\n");
			exit(-1);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE)
	{
		T[i] = NIL;
		i++;
	}
}

int EmptyBiTree(SqBiTree T)
{
	if(T[0]==NIL)
		return 0;
	else
		return 1;
}

int DepthBiTree(SqBiTree T)
{
	int i,j=1;
	for(i=MAX_TREE_SIZE-1;i>0;i--)
	{
		if(T[i]!=NIL)
			break;
	}
	do
		j++;
	while(i>=pow(2,j));
	return j;
}

int LengthAtomBiTree(SqBiTree T)
{
	for(int i=MAX_TREE_SIZE-1;T[i]==0;i--);
	return i;
}

int BootBiTree(SqBiTree T)
{
	if(EmptyBiTree(T))
		return -1;
	else
		return T[0];
}

void LevelOrderTraverse(SqBiTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
		if(T[i]!=0)
			printf("%d ",T[i]);
	printf("\n");
}

void PreTraverse(SqBiTree T,int e)
{
	printf("%d ",T[e]);
	if(T[2*e+1]!=NIL)
		PreTraverse(T,2*e+1);
	if(T[2*e+2]!=NIL)
		PreTraverse(T,2*e+2);
}

void PreOrderTraverse(SqBiTree T,int e)
{
	if(EmptyBiTree(T))
	{
		printf("%d ",T[0]);
		PreTraverse(T,e);
		PreTraverse(T,e+1);
	}
	else
		printf("������Ϊ��!\n");
}

void InTraverse(SqBiTree T,int e)
{
	if(T[2*e+1]!=NIL)
		InTraverse(T,2*e+1);
	printf("%d ",T[e]);
	if(T[2*e+2]!=NIL)
		InTraverse(T,2*e+2);
}

void InOrderTraverse(SqBiTree T,int e)
{
	if(EmptyBiTree(T))
	{
		InTraverse(T,e);
		printf("%d ",T[0]);
		InTraverse(T,e+1);
	}
	else
		printf("������Ϊ��!\n");
}

void PostTraverse(SqBiTree T,int e)
{
	if(T[2*e+1]!=NIL)
		PostTraverse(T,2*e+1);
	if(T[2*e+2]!=NIL)
		PostTraverse(T,2*e+2);
	printf("%d ",T[e]);
}

void PostOrderTraverse(SqBiTree T,int e)
{
	if(EmptyBiTree(T))
	{
		PostTraverse(T,e);
		PostTraverse(T,e+1);
		printf("%d ",T[0]);
	}
	else
		printf("������Ϊ��!\n");
}

int Value(SqBiTree T,pos P)
{
	return	T[int(pow(2,P.level-1)+P.order-2)];		//����powһ��Ҫint�� ��Ȼ�����
}

void Assign(SqBiTree T,pos P,int e)
{
	int i=int(pow(2,P.level-1)+P.order-2);
	if(e!=NIL && T[(i+1)/2-1]==NIL)	
		printf("Ҷ�ӷǿյ�˫��Ϊ��!\n");
	else if(e==NIL && (T[i*2+1]!=NIL||T[i*2+2]!=NIL))
		printf("˫��Ϊ�յ���Ҷ��!\n");
	else
		T[i] = e;
}

int findpos(SqBiTree T,int e)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
	{
		if(T[i]==e)
			return i;
	}
	return 0;
}

int Parent(SqBiTree T,int e)
{
	if(findpos(T,e)==0)
		return 0;
	else
		return T[(findpos(T,e)+1)/2-1];
}

int LeftChild(SqBiTree T,int e)
{
	if(findpos(T,e)==0)
		return 0;
	else
		return T[findpos(T,e)*2+1];
}

int RightChild(SqBiTree T,int e)
{
	if(findpos(T,e)==0)
		return 0;
	else
		return T[findpos(T,e)*2+2];
}

int LeftSibling(SqBiTree T,int e)
{
	if(findpos(T,e)==0)
		return 0;
	if(!(findpos(T,e)%2))
		return T[findpos(T,e)-1];
	else
		return 0;
}

int RightSibling(SqBiTree T,int e)
{
	if(findpos(T,e)==0)
		return 0;
	if((findpos(T,e))%2)
		return T[findpos(T,e)-1];
	else
		return 0;
}

void InsertChlid(SqBiTree T,SqBiTree S,int e,int j)
{
	int i,k;
	i=findpos(T,e);
	k = 2*i+1+j;
	if(T[k]!=0)
			Move(T,T,2*k+2,k);
	Move(T,S,k,0);
}

void Move(SqBiTree T,SqBiTree S,int i,int j)
{
	if(S[j*2+1]!=NIL)
		Move(T,S,i*2+1,j*2+1);
	if(S[j*2+2]!=NIL)
		Move(T,S,i*2+2,j*2+2);
	T[i] = S[j];
}

void Delete(SqBiTree T,int i)
{
	if(T[i*2+1]!=NIL)
		Delete(T,i*2+1);
	if(T[i*2+2]!=NIL)
		Delete(T,i*2+2);
	T[i] = 0;
}

void DeleteChild(SqBiTree T,int e,int j)
{
	int i,k;
	i=findpos(T,e);
	k = 2*i+1+j;
	if(T[k]==0)
	{
		printf("����Ϊ��!\n");
		exit(-1);
	}
	else
		Delete(T,k);
}

void Print(SqBiTree T)
{
	int i,k,j;
	for(i=1;LengthAtomBiTree(T)>pow(2,i)-2;i++)
	{
		printf("��%d��: ",i);
		j=1;
		for(k=int(pow(2,i-1)-1);k<=pow(2,i)-2;k++)
		{
			if(T[k]!=0)
			{
				printf("%d:%d ",j,T[k]);
			}
			j++;
		}
		printf("\n");
	}
}

void ClearBiTree(SqBiTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
		T[i] = NIL;
}	