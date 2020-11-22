#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_TREE_SIZE 100
#define QUEUE_SIZE 50

typedef struct PTNode
{
	char data;
	int parent;
}*pPTNode;

typedef struct PTree#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_TREE_SIZE 100
#define QUEUE_SIZE 50

typedef struct PTNode
{
	char data;
	int parent;
}*pPTNode;

typedef struct PTree
{
	PTNode nodes[MAX_TREE_SIZE];
	int n;							//�ڵ���
}*pPTree;

typedef struct Queue
{
	PTNode *Base;
	int front;
	int rear;
}Queue,*qQueue;

void InitTree(pPTree);
bool TreeEmpty(pPTree);
char Root(pPTree);
int TreeDepth(pPTree);
void CreatrTree(pPTree);
void TraverseTree(pPTree);
void Assign(pPTree,char,char);
char Parent(pPTree,char);
char LeftChild(pPTree,char);
char RightSibling(pPTree,char);
void InsertChild(pPTree,char,int,pPTree);
void Print(pPTree);
void DeleteChild(pPTree,char,int);

void init_Queue(qQueue,int);
void en_Queue(qQueue,pPTNode);
void de_Queue(qQueue,pPTNode);
bool EmptyQueue(qQueue);

int main()
{
	int i;
	char e1,e2;
	PTree T,H;
	InitTree(&T);
	printf("����������,���շ�?%d(1:�� 0:��) ���ĸ�Ϊ%c �������Ϊ%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	CreatrTree(&T);
	printf("������T��,���շ�?%d(1:�� 0:��) ���ĸ�Ϊ%c �������Ϊ%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	printf("�������T\n");
	TraverseTree(&T);
	printf("\n��������޸ĵĽڵ��ֵ ��ֵ:");
	scanf("%c%*c%c%*c",&e1,&e2);
	Assign(&T,e1,e2);
	printf("\n������޸ĺ����T\n");
	TraverseTree(&T);
	printf("\n%c��˫����%c,������%c,��һ���ֵ���%c\n",e2,Parent(&T,e2),LeftChild(&T,e2),RightSibling(&T,e2));
	printf("������H\n");
	InitTree(&H);
	CreatrTree(&H);
	printf("�������T\n");
	TraverseTree(&H);
	printf("����H�嵽��H��,������T�е�˫�׽ڵ� �������:");
	scanf("%c%d%*c",&e1,&i);
	InsertChild(&T,e1,i,&H);
	Print(&T);
	printf("ɾ����T�нڵ�e�ĵ�i��������������e i:");
	scanf("%c%d%*c",&e1,&i);
	DeleteChild(&T,e1,i);
	Print(&T);
	scanf("%c%d%*c",&e1,&i);
	return 0;
}

void InitTree(pPTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
	{
		T->nodes[i].data = 0;
		T->nodes[i].parent = 0;
		T->n = 0;
	}
}

bool TreeEmpty(pPTree T)
{
	if(T->n==0)
		return true;
	else
		return false;
}

char Root(pPTree T)
{
	if(T->n!=0)
		return T->nodes[0].data;
	else
		return '*';
}

int TreeDepth(pPTree T)
{
	int i=1,j=T->nodes[T->n-1].parent;
	if(T->n==0)
		return 0;
	else
	{
		while(j!=-1)
		{
			j = T->nodes[j].parent;
			i++;
		}
		return i;
	}
}

void CreatrTree(pPTree T)
{
	Queue q;
	PTNode p,qq;
	int i=1,j,l;
	char c[MAX_TREE_SIZE];				//��ʱ��ź��ӽڵ�
	init_Queue(&q,QUEUE_SIZE);
	printf("��������ڵ�('*'Ϊ��):");
	scanf("%c%*c",&T->nodes[0].data);	//���ڵ����Ϊ0
	if(T->nodes[0].data!='*')
	{
		T->nodes[0].parent = -1;		//���ڵ���˫��
		qq.data = T->nodes[0].data;
		qq.parent = 0;
		en_Queue(&q,&qq);
		while(i<MAX_TREE_SIZE && !EmptyQueue(&q))
		{
			de_Queue(&q,&qq);				//����һ���ڵ�
			printf("�밴����˳������ڵ�%c�����к���:",qq.data);
			gets(c);
			l = strlen(c);
			for(j=0;j<l;j++)
			{
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.parent;
				p.data = c[j];
				p.parent = i;
				en_Queue(&q,&p);
				i++;
			}
		}
		if(i>MAX_TREE_SIZE)
		{
			printf("�ڵ���������������\n");
			exit(-1);
		}
		T->n = i;
	}
	else
		T->n = 0;
}

void TraverseTree(pPTree T)
{
	for(int i=0;i<T->n;i++)
	{
		printf("->%c",T->nodes[i].data);
	}
}

void Assign(pPTree T,char e1,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e1;i++);
	T->nodes[i].data = e2;
}

char Parent(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2;i++);
	return T->nodes[T->nodes[i].parent].data;
}

char LeftChild(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[T->nodes[i].parent].data!=e2 && i<T->n;i++);
	if(i<T->n)
		return T->nodes[i].data;
	else
		return '*';
}

char RightSibling(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2 && i<T->n;i++);
	if(i!=T->n && T->nodes[i+1].parent == T->nodes[i].parent)
		return T->nodes[i+1].data;
	else
		return '*';
}

void InsertChild(pPTree T,char e1,int pos,pPTree H)						//pos��������λ��
{
	int j,l,k,f=1,n=0;
	PTNode t;
	if(!TreeEmpty(T))
	{
			for(j=0;T->nodes[j].data!=e1 && j<T->n;j++);
		l = j + 1;				//���c��p�ĵ�һ�������������
		if(pos>1)
		{
			for(k=j+1;k<T->n;k++)
				if(T->nodes[k].parent == j)
				{
					n++;		//��������1
					if(n == pos-1)	//�ҵ�e1�ĵ�pos-1�����ӣ������Ϊk
						break;
				}
			l = k + 1;
		}//e1�����Ϊj��H����l��
		if(l<T->n)
			for(k=T->n-1;k>=l;k--)
			{
				T->nodes[k+H->n] = T->nodes[k];			//���ν����l�Ժ�Ľڵ�����ƶ�H->n��λ��
				if(T->nodes[k].parent>=l)
					T->nodes[k+H->n].parent +=H->n;		//���ν����l�Ժ�Ľڵ�ĸ��ڵ�����ƶ�H->n��Ϊλ��
			}
		for(k=0;k<H->n;k++)
		{
			T->nodes[l+k].data = H->nodes[k].data;		//���ν�H�е����ݲ��뵽T��l�Ժ��λ��
			T->nodes[l+k].parent = H->nodes[k].parent+l;//���ν�H�еĸ��ڵ�λ�ò��뵽T���Ժ��λ��(����+l���¸��ڵ��λ��)
		}
		T->nodes[l].parent = j;
		T->n += H->n;
		while(f)				//�Ӳ����֮�󣬽��ڵ��԰�������
		{		
			f = 0;
			for(j=1;j<T->n-1;j++)
			{
				if(T->nodes[j].parent>T->nodes[j+1].parent)		//�Ƚ�˫�׽��λ�ô�С
				{
					t = T->nodes[j];
					T->nodes[j] = T->nodes[j+1];
					T->nodes[j+1] = t;
					f = 1;
					for(k=j;k<T->n;k++)							//�ڶ�����λ�õ�����ͬʱ�����������и��ڵ�λ��
						if(T->nodes[k].parent == j)
							T->nodes[k].parent++;
						else if(T->nodes[k].parent == j+1)
							T->nodes[k].parent--;
				}
			}
		}
	}
	else
	{
		printf("��Ϊ��!\n");
		exit(-1);
	}
	
}

void DeleteChild(pPTree T,char e1,int pos)
{
	int i,j,k;
	Queue q;
	PTNode p;
	init_Queue(&q,QUEUE_SIZE);
	for(i=0;T->nodes[T->nodes[i].parent].data!=e1 && i<T->n;i++);
	if(i!=T->n)
	{
		en_Queue(&q,&T->nodes[i+pos-1]);
		T->nodes[i+pos-1].parent = T->n;
	}
	while(!EmptyQueue(&q)&&i<T->n)
	{
		de_Queue(&q,&p);
		for(j=i;j<T->n;j++)
		{
			if(T->nodes[T->nodes[j].parent].data == p.data)
			{
				en_Queue(&q,&T->nodes[j]);
				T->nodes[j].parent = T->n;
			}
		}
		i = j;
	}
	for(i=0;i<T->n;i++)
	{
		for(j=0;j<=i;j++)
		{
			if(T->nodes[j].parent>T->nodes[j+1].parent)
			{
				p = T->nodes[j];
				T->nodes[j] = T->nodes[j+1];
				T->nodes[j+1] = p;
				for(k=j;k<T->n;k++)							//�ڶ�����λ�õ�����ͬʱ�����������и��ڵ�λ��
					if(T->nodes[k].parent == j)
						T->nodes[k].parent++;
					else if(T->nodes[k].parent == j+1)
						T->nodes[k].parent--;
			}
		}
	}
	T->n -= q.rear;
}

void Print(pPTree T)
{
	printf("***�ڵ�***˫��***\n");
	printf("***%c*** ***\n",T->nodes[0].data);
	for(int i=1;i<T->n;i++)
	{
		printf("***%c***%c***\n",T->nodes[i].data,T->nodes[T->nodes[i].parent].data);
	}
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pPTNode)malloc((length+1)*sizeof(PTNode));
	if(Q->Base == NULL)
	{
		printf("�ռ����ʧ��!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,pPTNode T)
{
	Q->Base[Q->rear] = *T;
	Q->rear++;
}

void de_Queue(qQueue Q,pPTNode T)
{
	*T = Q->Base[Q->front];
	Q->front++;
}

bool EmptyQueue(qQueue Q)
{
	if(Q->rear == Q->front)
		return true;
	else
		return false;
}


{
	PTNode nodes[MAX_TREE_SIZE];
	int n;							//�ڵ���
}*pPTree;

typedef struct Queue
{
	PTNode *Base;
	int front;
	int rear;
}Queue,*qQueue;

void InitTree(pPTree);
bool TreeEmpty(pPTree);
char Root(pPTree);
int TreeDepth(pPTree);
void CreatrTree(pPTree);
void TraverseTree(pPTree);
void Assign(pPTree,char,char);
char Parent(pPTree,char);
char LeftChild(pPTree,char);
char RightSibling(pPTree,char);
void InsertChild(pPTree,char,int,pPTree);

void init_Queue(qQueue,int);
void en_Queue(qQueue,pPTNode);
void de_Queue(qQueue,pPTNode);
bool EmptyQueue(qQueue);

void main()
{
	int i;
	char e1,e2;
	PTree T,H;
	InitTree(&T);
	printf("����������,���շ�?%d(1:�� 0:��) ���ĸ�Ϊ%c �������Ϊ%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	CreatrTree(&T);
	printf("������T��,���շ�?%d(1:�� 0:��) ���ĸ�Ϊ%c �������Ϊ%d\n",TreeEmpty(&T),Root(&T),TreeDepth(&T));
	printf("�������T\n");
	TraverseTree(&T);
	printf("\n��������޸ĵĽڵ��ֵ ��ֵ:");
	scanf("%c%*c%c%*c",&e1,&e2);
	Assign(&T,e1,e2);
	printf("\n������޸ĺ����T\n");
	TraverseTree(&T);
	printf("\n%c��˫����%c,������%c,��һ���ֵ���%c\n",e2,Parent(&T,e2),LeftChild(&T,e2),RightSibling(&T,e2));
	printf("������H\n");
	InitTree(&H);
	CreatrTree(&H);
	printf("�������T\n");
	TraverseTree(&T);
	printf("����H�嵽��H��,������T�е�˫�׽ڵ� �������:");
	scanf("%c%d%*c",&e,&i);
	InsertChild(T,e,i,H);
	Print(T);

}

void InitTree(pPTree T)
{
	for(int i=0;i<MAX_TREE_SIZE;i++)
	{
		T->nodes[i].data = 0;
		T->nodes[i].parent = 0;
		T->n = 0;
	}
}

bool TreeEmpty(pPTree T)
{
	if(T->n==0)
		return true;
	else
		return false;
}

char Root(pPTree T)
{
	if(T->n!=0)
		return T->nodes[0].data;
	else
		return '*';
}

int TreeDepth(pPTree T)
{
	int i=1,j=T->nodes[T->n-1].parent;
	if(T->n==0)
		return 0;
	else
	{
		while(j!=-1)
		{
			j = T->nodes[j].parent;
			i++;
		}
		return i;
	}
}

void CreatrTree(pPTree T)
{
	Queue q;
	PTNode p,qq;
	int i=1,j,l;
	char c[MAX_TREE_SIZE];					//��ʱ��ź��ӽڵ�
	init_Queue(&q,QUEUE_SIZE);
	printf("��������ڵ�('*'Ϊ��):");
	scanf("%c%*c",&T->nodes[0].data);		//���ڵ����Ϊ0
	if(T->nodes[0].data!='*')
	{
		T->nodes[0].parent = -1;			//���ڵ���˫��
		qq.data = T->nodes[0].data;
		qq.parent = 0;
		en_Queue(&q,&qq);
		while(i<MAX_TREE_SIZE && !EmptyQueue(&q))
		{
			de_Queue(&q,&qq);				//����һ���ڵ�
			printf("�밴����˳������ڵ�%c�����к���:",qq.data);
			gets(c);
			l = strlen(c);
			for(j=0;j<l;j++)
			{
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.parent;
				p.data = c[j];
				p.parent = i;
				en_Queue(&q,&p);
				i++;
			}
		}
		if(i>MAX_TREE_SIZE)
		{
			printf("�ڵ���������������\n");
			exit(-1);
		}
		T->n = i;
	}
	else
		T->n = 0;
}

void TraverseTree(pPTree T)
{
	for(int i=0;i<T->n;i++)
	{
		printf("->%c",T->nodes[i].data);
	}
}

void Assign(pPTree T,char e1,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e1;i++);
	T->nodes[i].data = e2;
}

char Parent(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2;i++);
	return T->nodes[T->nodes[i].parent].data;
}

char LeftChild(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[T->nodes[i].parent].data!=e2 && i<T->n;i++);
	if(i<T->n)
		return T->nodes[i].data;
	else
		return '*';
}

char RightSibling(pPTree T,char e2)
{
	int i;
	for(i=0;T->nodes[i].data!=e2 && i<T->n;i++);
	if(i!=T->n && T->nodes[i+1].parent == T->nodes[i].parent)
		return T->nodes[i+1].data;
	else
		return '*';
}

void InsertChild(pPTree T,char e1,int pos,pPTree H)				//pos��������λ��
{
	int i,j=-1,k;												//iΪ��Tÿ������ߵ�����(���и��ڵ�),j�����һ���׸����ڵ�λ��(j��ʼ��Ϊ-1������ڵ�)
	while()
	{
		for(i=0;T->nodes[T->nodes[i].parent].data!=e1;i++);		//�ҵ���T�и��ڵ���e1������ߵ�����
		for();		//��H��ÿ��Ҫ����T�еĸ���
		for(k=T->n-1;k>i+pos-1;k--)
			T->nodes[k+]
	}
	
}

void init_Queue(qQueue Q,int length)
{
	Q->Base = (pPTNode)malloc((length+1)*sizeof(PTNode));
	if(Q->Base == NULL)
	{
		printf("�ռ����ʧ��!\n");
		exit(-1);
	}
	Q->front = 0;
	Q->rear = 0;
}

void en_Queue(qQueue Q,pPTNode T)
{
	Q->Base[Q->rear] = *T;
	Q->rear++;
}

void de_Queue(qQueue Q,pPTNode T)
{
	*T = Q->Base[Q->front];
	Q->front++;
}

bool EmptyQueue(qQueue Q)
{
	if(Q->rear == Q->front)
		return true;
	else
		return false;
}

