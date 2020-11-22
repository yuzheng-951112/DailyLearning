#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_LEN 25		//文件最大行数
#define LINE_LEN 75		//每行字符最大值+1
#define NAME_LEN 50		//文件名最大长度(包括盘符、路径)+1				//文件名数字数一定要确定够大 保证数组不溢出

typedef struct HString
{
	char *ch;
	int length;
}*pHString;

//全局变量
HString T[MAX_LEN];		//数组结构体变量
char str[LINE_LEN],filename[NAME_LEN];		//str[LINE_LEN]代表一个字符串长度
FILE *fp;
int N=0;		//文件行数

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
		printf("请选择:    0.创建文件并且输入文本内容\n");
		printf("	   1.打开文件(新或旧) 2.显示文件内容\n");
		printf("	   3.插入行 4.删除行 5.拷贝行 6修改行\n");
		printf("	   7.查找字符串 8.替换字符串\n");
		printf("	   9.存盘退出 10.放弃编辑\n");	
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
	printf("请输入要打开:");
	scanf("%s%*c",filename);
	if((fp = fopen(filename,"r+")) == NULL)
	{
		fprintf(stderr,"file open err!\n");
		return;
	}
	else
	{
		printf("请输入要存储的数据!\n");
		do{
			scanf("%s%*c",str);		//这里的字符串str从赋值开始就以'\0'
			fputs(str,fp);
			fprintf(fp,"\n");		//文件中换行
			printf("单回车换行继续输入(输入其他字符回车自动结束)");
		}while(getchar() == '\n');
	}
	memset(filename, 0, sizeof(filename));		//初始化数组为'0'
	memset(str,0,sizeof(str));
	fclose(fp);
}

void Open()			
{
	if(filename[0])			//这里要求文件的首字符不为"0"(存在于文件夹中文件的首字符一定不为"0")
	{
		printf("已存在打开的文件!\n");
	}
	else
	{
		printf("请输入要打开的文件名(可包括盘符、路径、不超过%d个字符):",NAME_LEN-1);		//NAME_LEN-1原因为字符串末尾有结束符号
		scanf("%s%*c",filename);		//%*c是为了去除字符串结尾的结束符，确保下次输入不被直接跳过
		if(fp = fopen(filename,"r"))
		{
			printf("文件打开成功!\n");
			while (!feof(fp) && !ferror(fp))			//feof(fp)判断文件是否到达结尾 ferror(fp)判断文件是否出错
			{
				strcpy(str,"\n");						//详细见fgets函数详解
				fgets(str,LINE_LEN,fp);										
				Assign_Str(&T[N],str);
				N++;
				if(N>=MAX_LEN)
				{
					printf("文件太大!\n");
					return;
				}
			}
			fclose(fp);
		}
		else
		{
			printf("文件打开失败，请重输入文件名!\n");
		}
	}
	memset(filename, 0, sizeof(filename));
	memset(str,0,sizeof(str));
	fclose(fp);						//关闭文件完成文件名初始化
}

void Insert()
{
	int x,y,k;
	printf("请在第X行前插入Y行，请输入X.Y:");
	scanf("%d,%d",&x,&y);
	if(y+N>NAME_LEN)
	{
		printf("插入行数太多!\n");
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
		printf("请输入要插入的内容:\n");
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
		printf("插入行超过范围!\n");
	}
	memset(str,0,sizeof(str));
}

void Delete()
{
	int x,y,i;
	printf("从第X行开始删除Y行，请输入X.Y:");
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
		printf("删除行超过范围!\n");
		return;
	}
}

void Copy()
{
	int x,y,z,i;
	printf("从第X行起复制Y行插入在原Z行之前:请输入下x.y.z:");
	scanf("%d,%d,%d",&x,&y,&z);
	if(x+y-1<N && (x>0&&x<N-1) && (z>0&&z<N-1) && z+y<MAX_LEN)
	{
		HString Q[MAX_LEN];		//结构体数组(归结到数组中，函数结束后自动释放)
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
		printf("复制错误!\n");
		return;
	}
}

void Modify()
{
	int x,k;
	printf("请输入待修改的行号X:");
	scanf("%d",&x);
	if(x>0 && x<N)
	{
		printf("第X行的内容为:");
		Print_Str(&T[x-1]);
		fflush(stdin);
		printf("请输入修改的内容:");
		gets(str);
		k = strlen(str);
		str[k] = '\n';
		Assign_Str(&T[x-1],str);
	}
	else
	{
		printf("行号超出范围!\n");
	}
}

void search()
{
	int i,k;
	char b;
	printf("请输入要查找的字符串:");
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
				printf("第%d行:",i+1);
				Print_Str(&T[i]);
				printf("第%d个字符处找到,是否继续(Y/N)?:",k);
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
	printf("请输入待代替的字符串:");
	scanf("%s%*c",str);
	Init_String(&s);
	Assign_Str(&s,str);
	printf("请输入替换字符:");
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
				printf("第%d行:",i+1);
				Print_Str(&T[i]);
				printf("第%d个字符处找到,是否替换(Y/N)?:",k);
				scanf("%c%*c",&b);
				if(b=='Y' || b=='y')
				{
					Delete_Str(&T[i],k,s.length);
					Insert_Str(&T[i],&t,k);
				}
				printf("是否继续替换(Y/N)?:");
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
	printf("请输入要打开:");
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
			fputs(T[i].ch,fp);			//fputs以'\0'为结尾 这里T[i]字段结尾没有'\0'
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

void Copy_Str(HString *Str,HString *Str1)
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
		printf("删除范围错误!\n");
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
		printf("插入范围错误!\n");
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
		printf("串为空!\n");
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