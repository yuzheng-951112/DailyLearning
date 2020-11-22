#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MaxKeyNum 25	//��������������(�ؼ��ʵ������)
#define MaxLineLen 51	//��Ŀ��(����+���)buf����󳤶�
#define	MaxWordNum 10	//�ʱ�(һ����Ĺؼ���)���������
#define MaxNoIdx 10		//���ô�(��ָ��д)������

//�ѷ�������
typedef struct HString	
{
	char *ch;
	int length;
}*pHString;

//�ض�����������
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

//������Ҫ�ṹ��
typedef struct WordListType		
{
	char *item[MaxWordNum];							//�ʱ�(�ַ���)ָ������	һ�����鵥Ԫ������һ���ַ�����ַ
	int wornum;										//�ʵ�����
}*pWordListType;

typedef struct NoIdxType
{
	char *item[MaxNoIdx];							//���ôʱ�ָ������
	int wornum;										//�ʵ�����
}*pNoIdxType;

typedef struct IdxTermType
{
	HString keyword;								//�ؼ���(�ѷ�������)
	LinkList* booklist;								//����������������
}*pIdxTermType;

typedef struct IdxListType
{
	IdxTermType item[MaxKeyNum+1];
	int wornum;										//�ؼ��ʸ���
}*pIdxListType;

//ȫ�ֱ���
char buf[MaxLineLen];								//��ǰ��Ŀ��(����'\0')
WordListType WDLIST;								//�ݴ�һ����Ĵʱ�
NoIdxType NOIDX;									//���ôʱ�

//���¶������Ա���
struct LinkList* init_struct();		//������ʼ��
struct Node* Init_Node();					//��������ʼ��
int MakeNode(pNode,int);				//��������ֵ����
void Append(LinkList*,pNode);			//������β�������
//�Ѵ��ĺ���
void Init_String(HString*);				//����ʼ��
void Assign_Str(HString*,char*);		//������
int Compare_Str(HString*,HString*);		//������С�Ƚ�
void Copy_Str(HString*,HString*);		//���ĸ���
//�������庯��
void InitIdxList(IdxListType*);
void ExtractKeyWord(int*);							//���䵥����Ŀ¼��WDLIST
void InsIdxList(IdxListType*,int);					//����ź͹ؼ��ʼ��뵽IDXLIST
void GetWord(int,HString*);							//����ؼ��ֵ�WD��
int Locate(IdxListType*,HString,int*);				//
void InsertNewKey(IdxListType*,int,HString);		//��Bookid.txt�в���ؼ���
void InsertBook(IdxListType*,int,int);				//��Bookid.txt�в�����Ŀ¼
void PutText(FILE*,IdxListType*);

void main()
{
	FILE *fp;
	IdxListType IDXLIST;	//�ؼ��ʱ�
	int BookNo;
	int k,i;

//�����ô���洢��NOIDX�ṹ���ļ���
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

//��ʼ��������idxlistΪ��
	if((fp=fopen("BookInfo.txt","r")) == NULL)
	{
		exit(-1);
	}
	InitIdxList(&IDXLIST);

//�������ݵ�IDXLIST
	while (!feof(fp) && !ferror(fp))			
	{
		fgets(buf,MaxLineLen,fp);
		ExtractKeyWord(&BookNo);
		InsIdxList(&IDXLIST,BookNo);
	}
	fclose(fp);

//��IDXLIST�е����ݷ��䵽BookIdx.txt�ļ���
	fp = fopen("BookIdx.txt","w");
	if(!fp)
	{
		exit(-1);
	}
	PutText(fp,&IDXLIST);
	fclose(fp);
}

//��������
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

void ExtractKeyWord(int *BookNo)		//��ȡ����
{
	int i,k,f=1;
	char *s1,*s2;
	for(i=0;i<WDLIST.wornum;i++)
	{
		free(WDLIST.item[i]);		//�������DAMAGE: after Normal block����ԭ������Ϊfree()�ͷ���δ����ֵ�����飬���磨a[5]=5��ʹ��c++��ͬѧ��֪����һ��5ά�Ķ�̬���飬����ʱӦ����0~4�����������a[5]��ֵ��û�г���������deleteʱ�Ż����
		WDLIST.item[i] = NULL;
	}
	WDLIST.wornum = 0;				//��ʼ���ʱ���Ϊ0(���㽫�������ʱ��Ž���)
	*BookNo = 100*(buf[0]-'0')+10*(buf[1]-'0')+(buf[2]-'0');
	s2 = &buf[2];
	do								//��ȡ��������ĸ�ַ�(�㷨)
	{
		s1 = s2+1;					//s1����ƶ�һ������
		s2 = strchr(s1,' ');		//s2ָ��s1�ĵ�һ���ո���û�У�����NULL
		if(!s2)
		{
			s2 = strchr(s1,'\n');		//s2ָ��buf�����һ���ַ�('\n')
			if(!s2)
			{
				s2 = strchr(s1,'\0');
			}
			f = 0;
		}
		k = s2-s1;
		if(s1[0]>='A'&& s1[0]<='Z')	//��������ĸΪ��д
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
					printf("����Ϊ���ô�!\n");
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

void GetWord(int i,HString* WD)		//����ؼ��ֵ�WD��
{
	Assign_Str(WD,WDLIST.item[i]);
}

int Locate(IdxListType *IDXLIST,HString WD,int *b)
{
	int i,m=0;
	for(i=IDXLIST->wornum;(m = Compare_Str(&IDXLIST->item[i].keyword,&WD))>0;--i);		//����StrCompare()������Ŀ����Ϊ��ȷ��IDXLIST.item[i].keywordΪ�գ�������һ����Bookid��Ĵ洢
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
	IDXLIST->item[IDXLIST->wornum+1].booklist = init_struct();	//IDXLIST.wornum���������ɹؼ��ʸ���
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

//�Ѵ��ĺ���
void Init_String(HString *Str)						//������ʼ��
{
	Str->ch = NULL;
	Str->length = 0;
}

void Assign_Str(HString* Str,char *t)				//�����ַ�
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
			printf("����ռ�ʧ��!\n");
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
		printf("��Ϊ��!\n");
	}
}

int Compare_Str(HString *Str,HString *Str1)			//�Ƚ��ַ�����С
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

void Copy_Str(HString *Str,HString *Str1)			//������
{
	Str->ch = (char*)malloc(Str1->length*sizeof(char));
	if(Str->ch == NULL)
	{
		printf("�ڴ����ʧ��!\n");
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

//���¶������Ա���
struct LinkList* init_struct()						//������ʼ��
{
	LinkList* TempPhead = (LinkList*)malloc(sizeof(LinkList));
	pNode pfirst = (pNode)malloc(sizeof(Node));
	if(TempPhead == NULL || pfirst == NULL)
	{
		printf("��ͷ����ʧ��!\n");
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
		printf("�ڴ����ʧ��!\n");
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
