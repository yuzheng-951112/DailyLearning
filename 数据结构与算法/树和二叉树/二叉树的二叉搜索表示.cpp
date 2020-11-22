#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
enum PointerTag{Link,Thread};		//Link(0):ָ��,Thread(1):����

typedef struct BiThrNode
{
	char data;
	BiThrNode *lchild,*rchild;		//���Һ���ָ��
	PointerTag LTag,RTag;			//���ұ�־
}*BiThrTree;

BiThrTree pre;

void CreatrBiThrTree(BiThrTree &);
void InOrderThreading(BiThrTree &,BiThrTree);
void InThreading(BiThrTree);
void InOrderTraverse(BiThrTree);

void main()
{
	BiThrTree H,T;
	printf("�밴�������������(����:ab�����ո��ʾaΪ���ڵ�,bΪ�������Ķ�����)\n");
	CreatrBiThrTree(T);
	InOrderThreading(H,T);
	InOrderTraverse(H);
}

void CreatrBiThrTree(BiThrTree &T)
{
	char h;
	scanf("%c",&h);
	if(h=='*')
		T = NULL;
	else
	{
		if(!(T=(BiThrTree)malloc(sizeof(BiThrNode))))
			exit(-1);
		T->data = h;
		CreatrBiThrTree(T->lchild);
		if(T->lchild)
			T->LTag = Link;
		CreatrBiThrTree(T->rchild);
		if(T->rchild)
			T->RTag = Link;
	}
}

void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);		//�ݹ�������������
		if(!p->lchild)
		{
			p->LTag = Thread;		//ǰ������
			p->lchild = pre;		//����ָ��ָ��ǰ��
		}
		if(!pre->rchild)				//ǰ��û���Һ���
		{
			pre->RTag = Thread;		//��������
			pre->rchild = p;		//ǰ���Һ���ָ�������(��ǰ�ڵ�p)
		}
		pre = p;					//����preָ��p��ǰȥ(�ӵݹ����ڲ�һ����ǰ)
		InThreading(p->rchild);
	}
}

void InOrderThreading(BiThrTree &Thrt,BiThrTree	T)
{
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(-1);
	Thrt->LTag = Link;			//��ͷ�ڵ�
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;		//��ָ���ָ
	if(!T)						//�����ָ��Ϊ��,����ָ���ָ
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
}

void InOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link)
			p = p->lchild;
		printf("%c->",p->data);
		while(p->RTag==Thread && p->rchild!=T)
		{
			p = p->rchild;
			printf("%c->",p->data);
		}
		p = p->rchild;
	}
}