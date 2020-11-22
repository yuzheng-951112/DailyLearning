#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define CHUNKSIZE 4
#define MAXSIZE 20

typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk *pnext;
}Chunk,*pChunk;

typedef struct LString
{
	struct Chunk *head,*tail;
	int curlen;
}LString,*pLString;

pLString Init_String();
void Assign_String(pLString Str,char *p);
void Print_String(pLString Str);
void Clear_String(pLString Str);
void Copy_String(pLString Str,pLString Str1);
void Sub_String(pLString Str,pLString Str1,int pos,int len);
void Concat_String(pLString Str,pLString Str1,pLString Str2);
int Index_String(pLString Str,pLString Str1,int pos);
void Delete_String(pLString Str,int pos,int len);
void Zip_String(pLString Str);
void Insert_String(pLString Str,pLString Str1,int pos);
void Replace_String(pLString Str,pLString Str1,pLString Str2);

bool empty(pLString Str);

void main()
	{
	int pos,len;
	char c[MAXSIZE],*p;
	pLString Str,Str1,Str2,Str3;
	Str = Init_String();
	Str1 = Init_String();
	Str2 = Init_String();
	Str3 = Init_String();

	printf("������Ҫ������ַ���a:");
	p = gets(c);
	Assign_String(Str,p);
	printf("�ַ���aΪ:");
	Print_String(Str);

	Copy_String(Str,Str1);
	printf("���ַ���a���Ƶ��ַ���bΪ:");
	Print_String(Str1);

	Concat_String(Str,Str1,Str2);
	printf("���ַ���a���ַ���b�ϲ�(��ȥ����䲿��)cΪ:");
	Print_String(Str2);

	Clear_String(Str2);
	printf("���a�ĵ�pos���ַ���,����Ϊlen���Ӵ�c,pos,len:");
	scanf("%d,%d",&pos,&len);
	Sub_String(Str,Str2,pos-1,len);
	printf("�Ӵ�cΪ:");
	Print_String(Str2);

	printf("������a��pos������Ѱ���ö�Ӧ�Ӵ�cλ��:");
	scanf("%d",&pos);
	printf("�Ӵ�c������a�е�λ��Ϊ%d:\n",Index_String(Str,Str2,pos-1));

	printf("������a��pos��ʼɾ��len����:");
	scanf("%d,%d",&pos,&len);
	Delete_String(Str,pos-1,len);
	printf("ɾ����aΪ:");
	Print_String(Str);

	fflush(stdin);
	printf("������Ҫ������ַ���d:");
	p = gets(c);
	Assign_String(Str3,p);
	printf("�ַ���dΪ:");
	Print_String(Str3);
	printf("�ڴ�a��pos����봮d:");
	scanf("%d",&pos);
	Insert_String(Str,Str3,pos-1);
	Print_String(Str);

	printf("��a����b�е�cΪ");
	Replace_String(Str1,Str,Str2);
	Print_String(Str1);
	
}

pLString Init_String()
{
	pLString Str = (pLString)malloc(sizeof(LString));
	pChunk pHeadnext = (pChunk)malloc(sizeof(Chunk));
	if(Str == NULL || pHeadnext == NULL)
	{
		printf("�ڴ����ʧ��");
		exit(-1);
	}
	Str->curlen = 0;
	Str->head = Str->tail = pHeadnext;
	pHeadnext->pnext =NULL;
	return Str;
}

void Assign_String(pLString Str,char *p)
{
	int i,j,k;
	pChunk q,ptemp = Str->tail;
	i = strlen(p);							//strlen�������ж���'\0'('\0'asciiΪ0)��βǰ���ܳ��� ��(char*)malloc(Str->curlen*sizeof(char))������'\0'��β�����Բ�����strlen(char��ָ��)
	if(!i ||strchr(p,' '))					//strche(p,' ');�жϷ����ַ������Ƿ���' '
	{
		printf("�������!\n");
		exit(-1);
	}
	Str->curlen = i;
	j = i/CHUNKSIZE;
	if(i%CHUNKSIZE)
	{
		j++;
	}
	for(i=0;i<j;i++)
	{
		q = (pChunk)malloc(sizeof(Chunk));
		if(!q)
		{
			printf("�ڴ����ʧ��!\n");
			exit(-1);
		}
		for(k=0;k<CHUNKSIZE && *p;k++)			//�ַ�������δ��������'��'   *pҲ���Ե�ͬ��*p != ' '
		{
			q->ch[k] = *p++;
		}
		if(!*p)
		{
			Str->tail = q;
			q->pnext = NULL;
			for(;k<CHUNKSIZE;k++)
			{
				q->ch[k] = ' ';
			}
		}
		ptemp->pnext = q;
		ptemp = q;
	}
}

void Clear_String(pLString Str)
{
	pChunk p = Str->head->pnext,q;
	while(p)
	{
		q = p->pnext;
		free(p);
		p = q;
	}
	Str->curlen = 0;
	Str->head->pnext = NULL;
	Str->tail = Str->head;
}

void Copy_String(pLString Str,pLString Str1)
{
	int k;
	if(!empty(Str1))
	{
		Clear_String(Str1);
	}
	pChunk ptemp = Str1->head,p = Str->head->pnext;
	while(p)
	{
		pChunk q = (pChunk)malloc(sizeof(Chunk));
		if(!q)
		{
			printf("��̬�ڴ����ʧ��!\n");
			exit(-1);
		}
		for(k=0;k<CHUNKSIZE;k++)
		{
			q->ch[k] = p->ch[k];
		}
		ptemp->pnext = q;
		ptemp = q;
		p = p->pnext;
	}
	Str1->tail = ptemp;
	ptemp->pnext = NULL;
	Str1->curlen = Str->curlen;
}

void Concat_String(pLString Str,pLString Str1,pLString Str2)
{
	pLString a,b;
	a = Init_String();
	b = Init_String();
	Copy_String(Str,a);
	Copy_String(Str1,b);
	a->tail->pnext = b->head->pnext;
	Str2->head->pnext = a->head->pnext;
	Str2->tail = b->tail;
//	Zip_String(Str2);
	Str2->curlen = a->curlen + b->curlen;
}

void Sub_String(pLString Str,pLString Str1,int pos,int len)
{
	int i,j,k,l=0;
	char *ctemp = (char*)malloc(len*sizeof(char));
	if(empty(Str))
	{
		printf("��Ϊ��!\n");
		exit(-1);
	}
	if(pos<=0 || pos>Str->curlen || len+pos-1>Str->curlen || len<0)
	{
		printf("λ�úͳ��ȷ�Χ����(1)!\n");
		exit(-1);
	}
	pChunk p = Str->head->pnext;
	i = pos/CHUNKSIZE+1;
	j = pos%CHUNKSIZE;
	for(k=1;k<i;k++)
	{
		p = p->pnext;
	}
	for(k=j;k<CHUNKSIZE && l!=len;k++)
	{
		*(ctemp+l) = p->ch[k];
		l++;
	}
	p = p->pnext;
	while(l != len)
	{
		for(k=0;k<CHUNKSIZE && l!=len;k++)
		{
			*(ctemp+l) =  p->ch[k];
			l++;
		}
		p = p->pnext;
	}
	i = len/CHUNKSIZE;
	if(j = len%CHUNKSIZE)
	{
		i++;
	}
	pChunk ptemp = Str1->head;
	for(l=0;l<i;l++)
	{
		pChunk q = (pChunk)malloc(sizeof(Chunk));
		if(l!=i-1 || j==0 )
		{
			for(k=0;k<CHUNKSIZE;k++)
			{
				q->ch[k] = *ctemp++; 
			}
		}
		else
		{
			for(k=0;k<j;k++)
			{
				q->ch[k] = *ctemp++;
			}
			for(k=j;k<CHUNKSIZE;k++)
			{
				q->ch[k] = ' ';
			}
		}
		ptemp->pnext = q;
		ptemp = q;
	}
	Str1->tail = ptemp;
	Str1->tail->pnext = NULL;
	Str1->curlen = len;
}

int Index_String(pLString Str,pLString Str1,int pos)
{
	int i,j,k,postemp;
	if(pos<0 || pos>Str->curlen)
	{
		printf("λ�÷�Χ����(2)!\n");
		exit(-1);
	}
	i = pos/CHUNKSIZE+1;
	j = pos%CHUNKSIZE;
	pChunk p = Str->head->pnext,p1 = Str1->head->pnext,ptemp,p1temp;
	for(k=1;k<i;k++)
	{
		p = p->pnext;
	}
	p1temp = p1;
	ptemp = p;
	postemp = j;
	i = 0;
	k--;
	while(1)
	{
		if(p1 == Str1->tail && i == Str1->curlen%CHUNKSIZE)
				break;
		if(p1->ch[i] == p->ch[j])
		{
			i++;
			j++;
			if(i == CHUNKSIZE && p1->pnext)
			{
				i = 0;
				p1 = p1->pnext;
			}
			if(j == CHUNKSIZE)
			{
				if(p->pnext)
				{
					j = 0;
					p = p->pnext;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			p = ptemp;
			p1 = p1temp; 
			postemp++;
			if(postemp == CHUNKSIZE)
			{
				if(p->pnext)
				{
					p = p->pnext;
					postemp = 0;
					ptemp = p;
					k++;
				}
				else
				{
					return 0;
				}
			}
			j = postemp;
			i = 0;
		}
	}
	return k*4+postemp+1;
}

void Delete_String(pLString Str,int pos,int len)
{
	int i,j,k,l;
	if(pos<0 || pos>Str->curlen-1 || len<0 || len+pos>Str->curlen)
	{
		printf("λ�úͳ��ȷ�Χ����(3)!\n");
		exit(-1);
	}
	else
	{
		i = pos/CHUNKSIZE+1;
		j = pos%CHUNKSIZE;
		pChunk p = Str->head->pnext;
		for(k=1;k<i;k++)
		{
			p = p->pnext;
		}
		for(l=0;l<len;l++)
		{
			p->ch[j] = ' ';
			if(j<CHUNKSIZE-1)
			{
				j++;
			}
			else
			{
				p = p->pnext;
				j = 0;	
			}
		}
		Zip_String(Str);
	}
}

void Zip_String(pLString Str)
{
	int j,i=0;
	pChunk p = Str->head->pnext;
	char *q = (char*)malloc((Str->curlen+1)*sizeof(char));
	while(p)
	{
		for(j=0;j<CHUNKSIZE;j++)
		{
			if(p->ch[j] != ' ')
			{
				*(q+i) = p->ch[j];
				i++;
			}
		}
		p = p->pnext;
	}
	*(q+i) = 0;						//�������� *(q+i) = '\0';
	Clear_String(Str);
	Assign_String(Str,q);
}

void Insert_String(pLString Str,pLString Str1,int pos)
{
	if(pos<0 || pos>Str->curlen)
	{
		printf("λ�÷�Χ����(4)!\n");
		exit(-1);
	}
	else
	{
		int i,j,l,k,n=0;
		char *q = (char*)malloc((Str->curlen+Str1->curlen+1)*sizeof(char));
		pChunk p = Str->head;
		i = pos/CHUNKSIZE+1;
		j = pos%CHUNKSIZE;
		for(k=0;k<i;k++)
		{
			p = p->pnext;
			for(l=0;l<CHUNKSIZE;l++)
			{
				*(q+n) = p->ch[l];
				n++;
				if(l+1==j && k==i-1)
				{
					break;
				}
			}
			l = 0;
		}
		pChunk p1 = Str1->head->pnext;
		while(p1)
		{
			for(l=0;l<CHUNKSIZE;l++)
			{
				*(q+n) = p1->ch[l];
				n++;
				if(p1==Str1->tail && l+1==Str1->curlen%CHUNKSIZE)
				{
					break;
				}
			}
			l = 0;
			p1 = p1->pnext;
		} 
		while(p && n != Str->curlen+Str1->curlen)				//����n != Str->curlen+Str1->curlen�ų��ڽ�β��������(��β������ǰ�ж�if(p==Str->tail && j+1==Str->curlen%CHUNKSIZE))
		{
			for(;j<CHUNKSIZE;j++)
			{
				*(q+n) = p->ch[j];
				n++;
				if(p==Str->tail && j+1==Str->curlen%CHUNKSIZE)
				{
					break;
				}
			}
			j = 0;
			p = p->pnext;
		}
		*(q+n) = 0;	
		Clear_String(Str);
		Assign_String(Str,q);
	}
}


void Replace_String(pLString Str,pLString Str1,pLString Str2)
{
	int pos,i = 1;
	while((pos=Index_String(Str,Str2,i-1)) != 0)
	{
		Delete_String(Str,pos-1,Str2->curlen);
		Insert_String(Str,Str1,pos-1);
		i = pos + Str1->curlen;
	}
}

void Print_String(pLString Str)
{
	if(empty(Str))
	{
		printf("��Ϊ��!\n");
		exit(-1);
	}
	int i;
	pChunk p = Str->head->pnext;
	while(p)
	{
		for(i=0;i<CHUNKSIZE;i++)
		{
			printf("%c",p->ch[i]);
		}
		p = p->pnext;
	}
	printf("\n");
}

bool empty(pLString Str)
{
	if(Str->head == Str->tail)
	{
		return true;
	}
	else
	{
		return false;
	}
}