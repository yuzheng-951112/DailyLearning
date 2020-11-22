#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MaxKeyNum 25	//索引表的最大容量(关键词的最大数)
#define MaxLineLen 51	//书目申(书名+书号)buf的最大长度
#define	MaxWordNum 10	//词表(一本书的关键词)的最大容量
#define MaxNoIdx 10		//常用词(仅指大写)的数量

//堆分配类型
typedef struct HString	
{
	char *ch;
	int length;
}*pHString;

//重定义线性链表
typedef struct Node
{
	int data;
	struct Node* pNext;
}Node,*pNode;

struct LinkList
{
	int len;
	struct Node* pNodeHead;
	struct Node* pNodeTail;
};

//搜索主要结构体
typedef struct WordListType		
{
	char *item[MaxWordNum];							//词表(字符串)指针数组	一个数组单元里面存放一个字符串地址
	int wornum;										//词的数量
}*pWordListType;

typedef struct NoIdxType
{
	char *item[MaxNoIdx];							//常用词表指针数组
	int wornum;										//词的数量
}*pNoIdxType;

typedef struct IdxTermType
{
	HString keyword;								//关键词(堆分配类型)
	LinkList* booklist;								//存放书号索引的链表
}*pIdxTermType;

typedef struct IdxListType
{
	IdxTermType item[MaxKeyNum+1];
	int wornum;										//关键词个数
}*pIdxListType;

//全局变量
char buf[MaxLineLen];								//当前书目串(包括'\0')
WordListType WDLIST;								//暂存一本书的词表
NoIdxType NOIDX;									//常用词表

//重新定义线性表函数
struct LinkList* init_struct();		//函数初始化
struct Node* Init_Node();					//线性链初始化
int MakeNode(pNode,int);				//线性链数值分配
void Append(LinkList*,pNode);			//线性链尾添加子链
//堆串的函数
void Init_String(HString*);				//串初始化
void Assign_Str(HString*,char*);		//串分配
int Compare_Str(HString*,HString*);		//两串大小比较
void Copy_Str(HString*,HString*);		//串的复制
//搜索主体函数
void InitIdxList(IdxListType*);
void ExtractKeyWord(int*);							//分配单行书目录到WDLIST
void InsIdxList(IdxListType*,int);					//将书号和关键词加入到IDXLIST
void GetWord(int,HString*);							//分配关键字到WD中
int Locate(IdxListType*,HString,int*);				//
void InsertNewKey(IdxListType*,int,HString);		//向Bookid.txt中插入关键词
void InsertBook(IdxListType*,int,int);				//向Bookid.txt中插入书目录
void PutText(FILE*,IdxListType*);

void main()
{
	FILE *fp;
	IdxListType IDXLIST;	//关键词表
	int BookNo;
	int k,i;

//将常用词语存储到NOIDX结构体文件中
	if((fp=fopen("NoIdx.txt","r")) == NULL)
	{
		exit(-1);
	}
	fscanf(fp,"%d",&NOIDX.wornum);
	for(k=0;k<NOIDX.wornum;k++)
	{
		fscanf(fp,"%s",buf);
		i = strlen(buf);
		NOIDX.item[k] = (char*)malloc(i*sizeof(char));
		strcpy(NOIDX.item[k],buf);
	}
	fclose(fp);

//初始化搜索表idxlist为空
	if((fp=fopen("BookInfo.txt","r")) == NULL)
	{
		exit(-1);
	}
	InitIdxList(&IDXLIST);

//分配数据到IDXLIST
	while (!feof(fp) && !ferror(fp))			
	{
		fgets(buf,MaxLineLen,fp);
		ExtractKeyWord(&BookNo);
		InsIdxList(&IDXLIST,BookNo);
	}
	fclose(fp);

//将IDXLIST中的数据分配到BookIdx.txt文件中
	fp = fopen("BookIdx.txt","w");
	if(!fp)
	{
		exit(-1);
	}
	PutText(fp,&IDXLIST);
	fclose(fp);
}

//搜索函数
void InitIdxList(IdxListType *TemList)
{
	int i;
	for(i=0;i<MaxKeyNum+1;i++)
	{
		TemList->item[i].booklist = init_struct();
		Init_String(&TemList->item[i].keyword);
		TemList->wornum = 0;
	}
}

void ExtractKeyWord(int *BookNo)		//提取书名
{
	int i,k,f=1;
	char *s1,*s2;
	for(i=0;i<WDLIST.wornum;i++)
	{
		free(WDLIST.item[i]);		//这里出现DAMAGE: after Normal block错误原因是因为free()释放了未被赋值的数组，比如（a[5]=5。使用c++的同学都知道，一个5维的动态数组，调用时应该是0~4，但是这里给a[5]赋值并没有出错，反而是delete时才会出错）
		WDLIST.item[i] = NULL;
	}
	WDLIST.wornum = 0;				//初始化词表长度为0(方便将待搜索词表存放进来)
	*BookNo = 100*(buf[0]-'0')+10*(buf[1]-'0')+(buf[2]-'0');
	s2 = &buf[2];
	do								//提取书名的字母字符(算法)
	{
		s1 = s2+1;					//s1向后移动一个单词
		s2 = strchr(s1,' ');		//s2指向s1的第一个空格，如没有，返回NULL
		if(!s2)
		{
			s2 = strchr(s1,'\n');		//s2指向buf的最后一个字符('\n')
			if(!s2)
			{
				s2 = strchr(s1,'\0');
			}
			f = 0;
		}
		k = s2-s1;
		if(s1[0]>='A'&& s1[0]<='Z')	//单词首字母为大写
		{
			WDLIST.item[WDLIST.wornum] = (char*)malloc((k+1)*sizeof(char));
			for(i=0;i<k;i++)
			{
				WDLIST.item[WDLIST.wornum][i] = s1[i];
			}
			WDLIST.item[WDLIST.wornum][k] = '\0';
			for(i=0;i<NOIDX.wornum;i++)
			{
				if(!strcmp(WDLIST.item[WDLIST.wornum],NOIDX.item[i]))
				{
					printf("单词为常用词!\n");
					break;
				}
			}
			if(i != NOIDX.wornum)
			{
				free(WDLIST.item[WDLIST.wornum]);
				WDLIST.item[WDLIST.wornum] = NULL;
			}
			else
			{
				WDLIST.wornum++;	
			}
		}
	}while(f);
}

void InsIdxList(IdxListType *IDXLIST,int BookNo)
{
	int i,b,j;
	HString WD;
	Init_String(&WD);
	for(i=0;i<WDLIST.wornum;i++)
	{
		GetWord(i,&WD);
		j = Locate(IDXLIST,WD,&b);
		if(!b)
		{
			InsertNewKey(IDXLIST,j,WD);
		}
		InsertBook(IDXLIST,j,BookNo);
	}
}

void GetWord(int i,HString* WD)		//分配关键字到WD中
{
	Assign_Str(WD,WDLIST.item[i]);
}

int Locate(IdxListType *IDXLIST,HString WD,int *b)
{
	int i,m=0;
	for(i=IDXLIST->wornum;(m = Compare_Str(&IDXLIST->item[i].keyword,&WD))>0;--i);		//这里StrCompare()函数的目的是为了确定IDXLIST.item[i].keyword为空，方便下一步的Bookid表的存储
	if(m == 0)
	{
		*b = 1;
		return i;
	}
	else
	{
		*b = 0;
		return i+1;
	}
}

void InsertNewKey(IdxListType *IDXLIST,int i,HString WD)		
{
	int j;
	IDXLIST->item[IDXLIST->wornum+1].booklist = init_struct();	//IDXLIST.wornum留下来当成关键词个数
	for(j=IDXLIST->wornum;j>=i;--j)								
	{
		IDXLIST->item[j+1] = IDXLIST->item[j];
	}
	Init_String(&IDXLIST->item[i].keyword);
	Copy_Str(&IDXLIST->item[i].keyword,&WD);
	IDXLIST->item[i].booklist = init_struct();
	IDXLIST->wornum++;
}

void InsertBook(IdxListType *IDXLIST,int j,int BookNo)
{
	 pNode p;
	 p = Init_Node();
	 if(!MakeNode(p,BookNo))
	 {
		 exit(-1);
	 }
	 Append(IDXLIST->item[j].booklist,p);
}

void PutText(FILE *fp,IdxListType *IDXLIST)
{
	pNode p;
	fprintf(fp,"%d\n",IDXLIST->wornum);
	for(int i=1;i<=IDXLIST->wornum;i++)
	{
		p = IDXLIST->item[i].booklist->pNodeHead->pNext;
		fprintf(fp,"%d\n",IDXLIST->item[i].booklist->len);
		for(int j=0;j<IDXLIST->item[i].booklist->len;j++)
		{
			fprintf(fp,"%d ",p->data);
			p = p->pNext;	
		}
		for(j=0;j<IDXLIST->item[i].keyword.length;j++)
		{
			fprintf(fp,"%c",IDXLIST->item[i].keyword.ch[j]);
		}
		fprintf(fp,"\n");
	}
}

//堆串的函数
void Init_String(HString *Str)						//函数初始化
{
	Str->ch = NULL;
	Str->length = 0;
}

void Assign_Str(HString* Str,char *t)				//分配字符
{
	int i,j;
	if(Str->ch)
	{
		free(Str->ch);
	}
	i = strlen(t);
	if(i)
	{
		Str->ch = (char*)malloc(i*sizeof(char));
		if(!Str->ch)
		{
			printf("分配空间失败!\n");
			exit(-1);
		}
		for(j=0;j<i;j++)
		{
			Str->ch[j] = t[j];
		}
		Str->length = i;
	}
	else
	{
		printf("串为空!\n");
	}
}

int Compare_Str(HString *Str,HString *Str1)			//比较字符串大小
{
	for(int i=0;i<Str->length && i<Str1->length;i++)
	{
		if(Str->ch[i] != Str1->ch[i])
		{
			return Str->ch[i] - Str1->ch[i];
		}
	}
	return Str->length - Str1->length;
}

void Copy_Str(HString *Str,HString *Str1)			//串复制
{
	Str->ch = (char*)malloc(Str1->length*sizeof(char));
	if(Str->ch == NULL)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	else
	{
		for(int i=0;i<Str1->length;i++)
		{
			Str->ch[i] = Str1->ch[i];
		}
		Str->length = Str1->length;
	}
}

//重新定义线性表函数
struct LinkList* init_struct()						//函数初始化
{
	LinkList* TempPhead = (LinkList*)malloc(sizeof(LinkList));
	pNode pfirst = (pNode)malloc(sizeof(Node));
	if(TempPhead == NULL || pfirst == NULL)
	{
		printf("表头类型失败!\n");
		exit(-1);
	}
	else
	{
		TempPhead->pNodeHead = pfirst;
		TempPhead->pNodeTail = pfirst;
		TempPhead->len = 0;
		pfirst->pNext = NULL;
	}
	return TempPhead;
}

struct Node* Init_Node()
{
	pNode p = (pNode)malloc(sizeof(Node));
	if(!p)
	{
		printf("内存分配失败!\n");
		exit(-1);
	}
	p->data = NULL;
	p->pNext = NULL;
	return p;
}

int MakeNode(pNode p,int e)
{
	if(!p)
	{
		return -1;
	}
	p->data = e;
	return 1;
}

void Append(LinkList* L, pNode p)
{
	L->pNodeTail->pNext = p;
	L->pNodeTail = p;
	L->len = L->len+1;
}
