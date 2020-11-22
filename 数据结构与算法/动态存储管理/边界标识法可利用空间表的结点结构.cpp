
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000			//可利用空间的大小(以WORD的字节数为单位)
#define e 10				//最小分配空间大小

typedef struct WORD
{
	union
	{
		WORD *llink;		//头部域,指向前驱节点
		WORD *uplink;		//底部域,指向本节点头部
	};
	int tag;				//块标志,0:空闲,1:占用,头部和尾部均有
	int size;				//头部域,块大小
	WORD *rlink;			//头部域,指向后续结点
}WORD,head,foot,*Space;		//*Space:可以利用空间指针类型

#define FootLoc(p) ((p)+(p->size)-1)	//带参数的宏定义,指向p所指结点的底部(最后一个字)

void Print(Space);
Space AllocBoundTag(Space &,int n);
void PrintUser(Space p[]);
void Reclaim(Space &,Space &);

void main()
{
	Space pav,p;							//空闲块指针
	Space v[MAX/e] = {NULL};				//占用块指针数组(初始化为空)
	int n;
	printf("结构体WORD为%d个字节\n",sizeof(WORD));
	p = new WORD[MAX+2];					//new是C++中的操作符,等同于p = (Space)malloc(sizof(WORD)*MAX);
	p->tag = 1;								//设置低址边界,以防查找左右邻块时出错
	pav = p+1;								//可利用空间表的表头
	pav->rlink = pav->llink = pav;			//初始化可以利用空间(一个整块)
	pav->tag = 0;
	pav->size = MAX;
	p = FootLoc(pav);						//p指向底部域
	p->uplink = pav;
	p->tag = 0;
	(p+1)->tag = 1;							//设置高地址边界,以防查找左右邻块时出错
	printf("初始化后,可以利用空间表为:\n");
	Print(pav);
	n = 300;
	v[0] = AllocBoundTag(pav,n);
	printf("分配%u个存储空间后,可利用空间表为:\n",n);
	Print(pav);
	PrintUser(v);
	n = 450;
	v[1] = AllocBoundTag(pav,n);
	printf("分配%u个存储空间后,可利用空间表为:\n",n);
	Print(pav);
	PrintUser(v);
	n = 300;								//分配不成功
	v[2] = AllocBoundTag(pav,n);
	printf("分配%u个存储空间后(不成功),pav为:\n",n);
	Print(pav);
	PrintUser(v);
	n = 242;
	v[2] = AllocBoundTag(pav,n);
	printf("分配%u个存储空间后(整块分配),pav为:\n",n);
	Print(pav);
	PrintUser(v);
	printf("回收v[0](%d)后(当pav空时回收),pav为:\n",v[0]->size);
	Reclaim(pav,v[0]);		//pav为空
	Print(pav);
	PrintUser(v);
	printf("1按回车键继续");
	getchar();
	printf("回收v[2](%d)后(左右邻区均为占用块),pav为:\n",v[2]->size);
}

void Print(Space p)
{
	Space h,f;
	if(p)
	{
		h = p;				//h指向第一个结点的头部域(首地址)
		f = FootLoc(h);		//f指向第一个结点的底部域
		do
		{
			printf("块的大小=%d 块的首地址=0x%x ",h->size,f->uplink);	//输出结点信息
			printf("块标志=%d(0:空闲 1:占用) 邻块首地址=0x%x\n",h->tag,f+1);
			h = h->rlink;										  //指向下一个结点的头部域(首地址)
			f = FootLoc(h);										  //f指向下一个结点的底部域	
		}while(h!=p);
	}
}

Space AllocBoundTag(Space &pav,int n)
{
	Space p,f;
	for(p=pav;p&&p->size<n&&p->rlink!=pav;p=p->rlink);		//查找不小于N的空闲块
	if(!p||p->size<n)										//找不到,返回空指针
		return NULL;
	else													//p指向找到的空闲块
	{
		f = FootLoc(p);										//指向底部
		pav = p->rlink;										//pav指向*p结点的后续结点
		if(p->size-n<=e)									//整块分配,不保留<=e的剩余量
		{
			if(pav==p)
				pav = NULL;
			else											//在表中删除分配的结点
			{
				pav->llink = p->llink;
				p->llink->rlink = pav;
			}
			p->tag = f->tag = 1;							//修改分配结点的头部和底部标志
		}
		else
		{
			f->tag = 1;										//修改分配块的底部标志
			p->size -= n;									//置剩余块大小
			f = FootLoc(p);									//指向剩余块底部
			f->tag = 0;										//设置剩余块底部
			f->uplink = p;
			p = f+1;										//指向分配头部
			p->tag = 1;										//设置分配头部
			p->size = n;
		}
		return p;											//返回分配块首地址
	}
}

void PrintUser(Space p[])									//输出p数组所指的已分配空间
{
	for(int i=0;i<MAX/e;i++)
	{
		if(p[i])											//指针不为0(指向一个占用块)
		{
			printf("块%d的首地址=0x%x ",i,p[i]);				//输出结点信息
			printf("块的大小=%d 块头标志=%d(0:空闲 1:占用)",p[i]->size,p[i]->tag);
			printf("块尾标志=%d 块尾地址0x%x\n",(FootLoc(p[i]))->tag,FootLoc(p[i]));
		}
	}
}

void Reclaim(Space &pav,Space &p)
{
	Space s=(p-1)->uplink,t=p+p->size;						//s,t分别指向释放块的左、右邻块(空闲时)的首地址
	int l=(p-1)->tag,r=(p+p->size)->tag;					//l、r分别指示释放的左、右邻块是否空闲
	if(!pav)												//可利用空间表空
	{//将释放块加入到pav所指的可利用表中
		pav = p->llink = p->rlink = p;						//头部域的两个指针及pav均指向释放块
		
	}
}