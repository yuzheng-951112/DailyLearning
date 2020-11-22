#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
enum PointerTag{Link,Thread};		//Link(0):指针,Thread(1):线索

typedef struct BiThrNode
{
	char data;
	BiThrNode *lchild,*rchild;		//左右孩子指针
	PointerTag LTag,RTag;			//左右标志
}*BiThrTree;

BiThrTree pre;

void CreatrBiThrTree(BiThrTree &);
void InOrderThreading(BiThrTree &,BiThrTree);
void InThreading(BiThrTree);
void InOrderTraverse(BiThrTree);

void main()
{
	BiThrTree H,T;
	printf("请按先序输入二叉树(例如:ab三个空格表示a为根节点,b为左子树的二叉树)\n");
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
		InThreading(p->lchild);		//递归左子树线索化
		if(!p->lchild)
		{
			p->LTag = Thread;		//前驱线索
			p->lchild = pre;		//左孩子指针指向前驱
		}
		if(!pre->rchild)				//前驱没有右孩子
		{
			pre->RTag = Thread;		//后续线索
			pre->rchild = p;		//前驱右孩子指针向后续(当前节点p)
		}
		pre = p;					//保持pre指向p的前去(从递归最内层一次往前)
		InThreading(p->rchild);
	}
}

void InOrderThreading(BiThrTree &Thrt,BiThrTree	T)
{
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(-1);
	Thrt->LTag = Link;			//建头节点
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;		//右指针回指
	if(!T)						//如果左指针为空,则左指针回指
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