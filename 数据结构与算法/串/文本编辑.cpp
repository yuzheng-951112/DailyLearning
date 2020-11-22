#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_LEN 25		//�ļ��������
#define LINE_LEN 75		//ÿ���ַ����ֵ+1
#define NAME_LEN 50		//�ļ�����󳤶�(�����̷���·��)+1				//�ļ���������һ��Ҫȷ������ ��֤���鲻���

typedef struct HString
{
	char *ch;
	int length;
}*pHString;

//ȫ�ֱ���
HString T[MAX_LEN];		//����ṹ�����
char str[LINE_LEN],filename[NAME_LEN];		//str[LINE_LEN]����һ���ַ�������
FILE *fp;
int N=0;		//�ļ�����

void Init_String(HString *Str);
void Assign_Str(HString *Str,char *t);
void Copy_Str(HString *Str,HString *Str1);
int Index_Str(HString *Str,HString *Str1,int pos);
void Delete_Str(HString *Str,int pos,int len);
void Insert_Str(HString *Str,HString *Str1,int pos);
void Print_Str(HString *Str);
void Input();
void Open();
void Insert();
void Delete();
void Copy();
void Modify();
void search();
void Replase();
void save();
void List();

void main()
{
	int s=1,i,k;
	for(i=0;i<MAX_LEN;i++)
	{
		Init_String(&T[i]);
	}
	while(s)
	{
		printf("��ѡ��:    0.�����ļ����������ı�����\n");
		printf("	   1.���ļ�(�»��) 2.��ʾ�ļ�����\n");
		printf("	   3.������ 4.ɾ���� 5.������ 6�޸���\n");
		printf("	   7.�����ַ��� 8.�滻�ַ���\n");
		printf("	   9.�����˳� 10.�����༭\n");	
		scanf("%d",&k);
		switch(k)
		{
		case 0:Input();break;
		case 1:Open();break;
		case 2:List();break;
		case 3:Insert();break;
		case 4:Delete();break;
		case 5:Copy();break;
		case 6:Modify();break;
		case 7:search();break;
		case 8:Replase();break;
		case 9:save();break;
		case 10:s=0;break;
		}
	}
} 

void Input()
{
	printf("������Ҫ��:");
	scanf("%s%*c",filename);
	if((fp = fopen(filename,"r+")) == NULL)
	{
		fprintf(stderr,"file open err!\n");
		return;
	}
	else
	{
		printf("������Ҫ�洢������!\n");
		do{
			scanf("%s%*c",str);		//������ַ���str�Ӹ�ֵ��ʼ����'\0'
			fputs(str,fp);
			fprintf(fp,"\n");		//�ļ��л���
			printf("���س����м�������(���������ַ��س��Զ�����)");
		}while(getchar() == '\n');
	}
	memset(filename, 0, sizeof(filename));		//��ʼ������Ϊ'0'
	memset(str,0,sizeof(str));
	fclose(fp);
}

void Open()			
{
	if(filename[0])			//����Ҫ���ļ������ַ���Ϊ"0"(�������ļ������ļ������ַ�һ����Ϊ"0")
	{
		printf("�Ѵ��ڴ򿪵��ļ�!\n");
	}
	else
	{
		printf("������Ҫ�򿪵��ļ���(�ɰ����̷���·����������%d���ַ�):",NAME_LEN-1);		//NAME_LEN-1ԭ��Ϊ�ַ���ĩβ�н�������
		scanf("%s%*c",filename);		//%*c��Ϊ��ȥ���ַ�����β�Ľ�������ȷ���´����벻��ֱ������
		if(fp = fopen(filename,"r"))
		{
			printf("�ļ��򿪳ɹ�!\n");
			while (!feof(fp) && !ferror(fp))			//feof(fp)�ж��ļ��Ƿ񵽴��β ferror(fp)�ж��ļ��Ƿ����
			{
				strcpy(str,"\n");						//��ϸ��fgets�������
				fgets(str,LINE_LEN,fp);										
				Assign_Str(&T[N],str);
				N++;
				if(N>=MAX_LEN)
				{
					printf("�ļ�̫��!\n");
					return;
				}
			}
			fclose(fp);
		}
		else
		{
			printf("�ļ���ʧ�ܣ����������ļ���!\n");
		}
	}
	memset(filename, 0, sizeof(filename));
	memset(str,0,sizeof(str));
	fclose(fp);						//�ر��ļ�����ļ�����ʼ��
}

void Insert()
{
	int x,y,k;
	printf("���ڵ�X��ǰ����Y�У�������X.Y:");
	scanf("%d,%d",&x,&y);
	if(y+N>NAME_LEN)
	{
		printf("��������̫��!\n");
		return;
	}
	if(x>1 && x<N-1)
	{
		for(int i=N-1;i>=x-1;i--)
		{
			T[i+y] = T[i];
		}
		N+=y;
		fflush(stdin);
		printf("������Ҫ���������:\n");
		for(i=x-1;i<x-1+y;i++)
		{
			gets(str);
			k = strlen(str);
			str[k] = '\n';
			Init_String(&T[i]);
			Assign_Str(&T[i],str);
		}
	}
	else
	{
		printf("�����г�����Χ!\n");
	}
	memset(str,0,sizeof(str));
}

void Delete()
{
	int x,y,i;
	printf("�ӵ�X�п�ʼɾ��Y�У�������X.Y:");
	scanf("%d,%d",&x,&y);
	if(x>0 && x+y-1<N)
	{
		for(i=y+x-1;i<=N;i++)
		{
			T[i-y] = T[i];
		}
		for(i=N-y;i<N;i++)
		{
			Init_String(&T[i]);
		}
		N-=y;
	}
	else
	{
		printf("ɾ���г�����Χ!\n");
		return;
	}
}

void Copy()
{
	int x,y,z,i;
	printf("�ӵ�X������Y�в�����ԭZ��֮ǰ:��������x.y.z:");
	scanf("%d,%d,%d",&x,&y,&z);
	if(x+y-1<N && (x>0&&x<N-1) && (z>0&&z<N-1) && z+y<MAX_LEN)
	{
		HString Q[MAX_LEN];		//�ṹ������(��ᵽ�����У������������Զ��ͷ�)
		for(i=0;i<y;i++)
		{
			Init_String(&Q[i]);
			Copy_Str(&Q[i],&T[x-1+i]);
		}
		for(i=N-1;i>=z-1;i--)
		{
			T[i+y] = T[i];
		}
		for(i=0;i<y;i++)
		{
			T[i+z-1] = Q[i]; 
		}
	}
	else
	{
		printf("���ƴ���!\n");
		return;
	}
}

void Modify()
{
	int x,k;
	printf("��������޸ĵ��к�X:");
	scanf("%d",&x);
	if(x>0 && x<N)
	{
		printf("��X�е�����Ϊ:");
		Print_Str(&T[x-1]);
		fflush(stdin);
		printf("�������޸ĵ�����:");
		gets(str);
		k = strlen(str);
		str[k] = '\n';
		Assign_Str(&T[x-1],str);
	}
	else
	{
		printf("�кų�����Χ!\n");
	}
}

void search()
{
	int i,k;
	char b;
	printf("������Ҫ���ҵ��ַ���:");
	scanf("%s%*c",str);
	HString s;
	Init_String(&s);
	Assign_Str(&s,str);
	for(i=0;i<N;i++)
	{
		k = 1;
		while(k)
		{
			k = Index_Str(&T[i],&s,k);
			if(k)
			{
				printf("��%d��:",i+1);
				Print_Str(&T[i]);
				printf("��%d���ַ����ҵ�,�Ƿ����(Y/N)?:",k);
				scanf("%c%*c",&b);
				if(b=='Y' || b=='y')
				{
					k++;
				}
				else
				{
					i = N+i;
					break;
				}
			}
		}
	}
}

void Replase()
{
	int i,k;
	char b;
	HString s,t;
	printf("�������������ַ���:");
	scanf("%s%*c",str);
	Init_String(&s);
	Assign_Str(&s,str);
	printf("�������滻�ַ�:");
	scanf("%s%*c",str);
	Init_String(&t);
	Assign_Str(&t,str);
	for(i=0;i<N;i++)
	{
		k = 1;
		while(k)
		{
			k = Index_Str(&T[i],&s,k);
			if(k)
			{
				printf("��%d��:",i+1);
				Print_Str(&T[i]);
				printf("��%d���ַ����ҵ�,�Ƿ��滻(Y/N)?:",k);
				scanf("%c%*c",&b);
				if(b=='Y' || b=='y')
				{
					Delete_Str(&T[i],k,s.length);
					Insert_Str(&T[i],&t,k);
				}
				printf("�Ƿ�����滻(Y/N)?:");
				scanf("%c%*c",&b);
				if(b=='Y' || b=='y')
				{
					k = s.length+k;
				}
				else
				{
					i = N+i;
					break;
				}
			}
		}
	}
}

void save()
{
	int i;
	printf("������Ҫ��:");
	scanf("%s%*c",filename);
	if((fp = fopen(filename,"w")) == NULL)
	{
		fprintf(stderr,"file open err!\n");
		return;
	}
	else
	{
		for(i=0;i<N;i++)
		{
			T[i].ch[T[i].length] = '\0';
			fputs(T[i].ch,fp);			//fputs��'\0'Ϊ��β ����T[i]�ֶν�βû��'\0'
		}
	}
	memset(filename, 0, sizeof(filename));
	fclose(fp);

}

void List()
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("%d: ",i+1);
		Print_Str(&T[i]);
	}
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
	}
}