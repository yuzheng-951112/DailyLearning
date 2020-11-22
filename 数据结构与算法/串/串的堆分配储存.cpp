#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 20

typedef struct HString
{
	char *ch;
	int length;
}*pHString;

void Init_String(HString *Str);
void Assign_Str(HString *Str,char *t);
void Print_Str(HString *Str);
int Compare_Str(HString *Str,HString *Str1);
void Concat_Str(HString *Str,HString *Str1,HString *Str2);
void Replace_Str(HString *Str,HString *Str1,HString *Str2);
void Clear_Str(HString *Str);
void Sub_Str(HString *Str,HString *Str1,int pos,int len);
void Copy_Str(HString *Str,HString *Str1);
void Insert_Str(HString *Str,HString *Str1,int pos);
void Delete_Str(HString *Str,int pos,int len);
int Index_Str(HString *Str,HString *Str1,int pos);

void main()
{
	int pos,len;
	char c[MAXSIZE],*p;
	HString t,s,r;
	Init_String(&t);
	Init_String(&s);
	Init_String(&r);

	printf("������Ҫ�������ַ���t:");
	p = gets(c);
	Assign_Str(&t,p);
	printf("�ַ���tΪ:");
	Print_Str(&t);

	printf("������Ҫ�������ַ���s:");
	p = gets(c);
	Assign_Str(&s,p);
	printf("�ַ���sΪ:");
	Print_Str(&s);

	if(Compare_Str(&t,&s) > 0)
	{
		printf("t��>s��\n");
	}
	else if(Compare_Str(&t,&s) == 0)
	{
		printf("t��=s��\n");
	}
	else
	{
		printf("t��<s��\n");
	}

	Concat_Str(&t,&s,&r);
	printf("����t�ʹ�s�ϲ�Ϊ��rΪ:");
	Print_Str(&r);

	Clear_Str(&r);
	printf("���������ַ���t��ȡ�õ��Ӵ���λ�úͳ���:");
	scanf("%d,%d",&pos,&len);
	Sub_Str(&r,&t,pos,len);
	printf("�ַ���rΪ:");
	Print_Str(&r);

	Clear_Str(&r);
	printf("���ַ���s���Ƶ��ַ���r");
	Copy_Str(&r,&s);
	printf("�ַ���rΪ:");
	Print_Str(&r);
	
	printf("���������ַ���t�в����ַ�����λ��:");
	scanf("%d",&pos);
	Insert_Str(&t,&s,pos);
	printf("�ַ���tΪ:");
	Print_Str(&t);

	printf("���������ַ���r��ɾ���ַ�����λ�úͳ���:");
	scanf("%d,%d",&pos,&len);
	Delete_Str(&r,pos,len);
	printf("�ַ���rΪ:");
	Print_Str(&r);

	Print_Str(&t);
	Print_Str(&s);
	printf("������ָ��λ�ú��ַ���t��һ�γ����ַ���s��λ��:");
	scanf("%d",&pos);
	printf("�Ӵ�s������t�ж�Ӧ��λ��Ϊ%d:\n",Index_Str(&t,&s,pos));

	fflush(stdin);
	Clear_Str(&r);
	printf("������Ҫ�������ַ���r:");
	p = gets(c);
	Assign_Str(&r,p);
	printf("�ַ���rΪ:");
	Print_Str(&r);
	printf("���������ַ���s��ɾ���ַ�����λ�úͳ���:");				//ɾ���ַ����е�һ���������滻���ַ�
	scanf("%d,%d",&pos,&len);
	Delete_Str(&s,pos,len);
	printf("�ַ���sΪ:");
	Print_Str(&s);
	Replace_Str(&t,&s,&r);
	printf("���滻���tΪ:");
	Print_Str(&t);
}

void Init_String(HString *Str)
{
	Str->ch = NULL;
	Str->length = 0;
}

void Assign_Str(HString* Str,char *t)
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

int Compare_Str(HString *Str,HString *Str1)
{
	for(int i=0;i<Str->length && i<Str1->length;i++)
	{
		if(Str->ch[i] != Str1->ch[i])
		{
			return Str->ch[i] - Str1->ch[i];
		}
	}
	return Str->length - Str->length;
}

void Concat_Str(HString *Str,HString *Str1,HString *Str2)
{
	Str2->ch = (char*)malloc((Str->length + Str1->length)*sizeof(char));
	if(Str2->ch == NULL)
	{
		printf("�ռ����ʧ��!\n");
		exit(-1);
	}
	else
	{
		for(int i=0;i<Str->length;i++)
		{
			Str2->ch[i] = Str->ch[i];
		}
		for(i=0;i<Str1->length;i++)
		{
			Str2->ch[i+Str->length] = Str1->ch[i];
		}
		Str2->length = Str->length + Str1->length;
	}
}

void Sub_Str(HString *Str,HString *Str1,int pos,int len)
{
	if(pos>=0 && pos<=Str1->length-1 && pos+len+1<=Str1->length)
	{
		Str->ch = (char*)malloc(len*sizeof(char));
		if(Str->ch == NULL)
		{
			printf("�ڴ����ʧ��!\n");
			exit(-1);
		}
		else
		{
			for(int i=0;i<len;i++)
			{
					Str->ch[i] = Str1->ch[pos+i-1];
			}
			Str->length = len;
		}
	}
	else
	{
		printf("�Ӵ�λ�úͳ��ȷ�Χ����!\n");
		exit(-1);
	}
}

void Copy_Str(HString *Str,HString *Str1)
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

void Insert_Str(HString *Str,HString *Str1,int pos)
{
	if(pos>=0 && pos<Str->length)
	{
		for(int i=Str->length-1;i>=pos-1;i--)
		{
			Str->ch[i+Str1->length] = Str->ch[i];
		}
		for(i=0;i<Str1->length;i++)
		{
			Str->ch[pos+i-1] = Str1->ch[i];
		}
		Str->length = Str->length + Str1->length;
	}
	else
	{
		printf("���뷶Χ����!\n");
		exit(-1);
	}
}

void Delete_Str(HString *Str,int pos,int len)
{
	if(pos>=1 && pos<=Str->length)
	{
		for(int i=0;i<Str->length-pos+1-len;i++)
		{
			Str->ch[pos-1+i] = Str->ch[pos-1+i+len];
		}
		Str->length = Str->length - len;
	}
	else
	{
		printf("ɾ����Χ����!\n");
		exit(-1);
	}
}

int Index_Str(HString *Str,HString *Str1,int pos)
{
	int i = pos-1,j = 0;
	while(i<Str->length && j<Str1->length)
	{
		if(Str->ch[i] == Str1->ch[j])
		{
			j++;
			i++;
		}
		else
		{
			i = i-j+1;
			j = 0;
		}
	}
	if(j>=Str1->length)
	{
		return i - Str1->length + 1;
	}
	else
	{
		return 0;
	}
}

void Replace_Str(HString *Str,HString *Str1,HString *Str2)
{
	int pos,i = 1;
	while((pos = Index_Str(Str,Str1,i-1)) != 0)
	{
		Delete_Str(Str,pos,Str1->length);
		Insert_Str(Str,Str2,pos);
		i = pos + Str1->length; 
	}
}

void Clear_Str(HString *Str)
{
	free(Str->ch);
	Str->ch = NULL;
	Str->length = 0;
}

void Print_Str(HString *Str)
{
	if(Str->length == 0)
	{
		printf("��Ϊ��!\n");
		exit(-1);
	}
	else
	{
		for(int i=0;i<Str->length;i++)
		{
			printf("%c",Str->ch[i]);
		}
		printf("\n");
	}
}