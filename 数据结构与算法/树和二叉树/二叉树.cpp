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
void Print(SqBiTree);			//逐层，按本层输出二叉树
void DeleteChild(SqBiTree,int,int);
void ClearBiTree(SqBiTree);

void main()
{
	int e,j;
	pos p;
	SqBiTree T,S;
	InitBiTree(T);
	CreateBiTree(T);
/*	printf("建立二叉树后,树空否?%d(1:是 0:否)\n",EmptyBiTree(T));
	printf("建立二叉树后,数的深度=%d\n",DepthBiTree(T));
	printf("二叉树的根为:%d\n",BootBiTree(T));
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("先序遍历二叉树:\n");
	PreOrderTraverse(T,1);
	printf("\n中序遍历二叉树:\n");
	InOrderTraverse(T,1);
	printf("\n后序遍历二叉树:\n");
	PostOrderTraverse(T,1);
	printf("\n请输入待修改的层号和序号:");
	scanf("%d,%d",&p.level,&p.order);
	e = Value(T,p);
	printf("带修改的值为%d,请输入新值:",e);
	scanf("%d",&e);
	Assign(T,p,e);
	printf("先序遍历二叉树:\n");
	PreOrderTraverse(T,1);
	printf("节点%d的双亲为%d:",e,Parent(T,e));
	printf("左右孩子分别为%d %d:",LeftChild(T,e),RightChild(T,e));
	printf("左右兄弟分别为%d %d:",LeftSibling(T,e),RightSibling(T,e));
	printf("建立右子树为空的树S:");*/
	InitBiTree(S);
	CreateBiTree(S);
	printf("树S插到树T中,请输入T中树的双亲节点,S为左(0)右(1)子树:");
	scanf("%d,%d",&e,&j);
	InsertChlid(T,S,e,j);
	Print(T);
	printf("删除子树，请输入待删除子树根节点的层号 本层序号 左(0)右(1)子树");
	scanf("%d,%d",&e,&j);
	DeleteChild(T,e,j);
	Print(T);
	ClearBiTree(T);
	printf("清除二叉树后，树空否?%d(1:是 0:否)\n",EmptyBiTree(T));
	printf("二叉树的根为:%d\n",BootBiTree(T));
}

void InitBiTree(SqBiTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
		T[i] = NIL;
}

void CreateBiTree(SqBiTree T)
{
	int i,n;
	/*			二叉树存储的是字符型
	char s[MAX_TREE_SIZE];
	printf("请按层输入节点的值(字符),空格表示空节点，节点数字<=%d:\n",MAX_TREE_SIZE);
	printf("例如 abcdefg\n");
	gets(s);
	n = strlen(s);
	for(i=0;i<=n;i++)
	{
		T[i] = s[i];
		if(i!=0 && T[(i+1)/2-1] == NIL && T[i]!=NIL)
		{
			printf("出现无双亲的非根节点%c\n",T[i]);
			exit(-1);
		}
	}
	for(i=n;i<MAX_TREE_SIZE;i++)
		T[i] = NIL;
	*/
	i=0;
	printf("请安层顺序输入节点的值(整型),0表示空节点,输入999结束,节点数<=%d\n",MAX_TREE_SIZE);
	while(1)
	{
		scanf("%d",&T[i]);
		if(T[i]==999)
				break;
		if(i!=0 && T[(i+1)/2-1]==NIL && T[i]!=NIL)//此节点(不空)无双亲且不是根
		{
			printf("出现无双亲的非根节点!\n");
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
		printf("二叉树为空!\n");
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
		printf("二叉树为空!\n");
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
		printf("二叉树为空!\n");
}

int Value(SqBiTree T,pos P)
{
	return	T[int(pow(2,P.level-1)+P.order-2)];		//这里pow一定要int型 不然会出错
}

void Assign(SqBiTree T,pos P,int e)
{
	int i=int(pow(2,P.level-1)+P.order-2);
	if(e!=NIL && T[(i+1)/2-1]==NIL)	
		printf("叶子非空但双亲为空!\n");
	else if(e==NIL && (T[i*2+1]!=NIL||T[i*2+2]!=NIL))
		printf("双亲为空但有叶子!\n");
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
		printf("子树为空!\n");
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
		printf("第%d层: ",i);
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