#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define NAMELEN 8
#define CLASSLEN 4

typedef struct Stud
{
	char name[NAMELEN+1];
	long int num;
	char sex;
	int age;
	char Class[CLASSLEN+1];
	int health;
}Stud,*pStud;

typedef struct Node
{
	struct Stud *data;
	struct Node *pNext;
}Node,*pNode;

struct Node* init_Stud();
void build_Stud(pNode pHead,pStud e);
void traverse_Stud(pNode pHead);
void insert_Stud(pNode pHead,pStud e);
void delete_Stud_num(pNode pHead,long int num);
void delete_Stud_name(pNode pHead,char name[]);
void Find_Stud_num(pNode pHead,long int num);
void Find_Stud_name(pNode pHead,char name[]);
void fwrite_file(pNode pHead,FILE *fp);
void fread_file(pNode pHead,FILE *fp);
void modify_num_file(pNode pHead,long int num);
void modify_name_file(pNode pHead,char name[]);
struct Stud* readin_Stud();
bool empty(pNode pHead);

void main()
{
	int i,flag;
	long int delete_num,find_num,modify_num;
	char delete_name[NAMELEN+1],find_name[NAMELEN+1],modify_name[NAMELEN+1];
	FILE *fp;
	Stud student[4] = {{"王小林",790631,'m',18,"计91",0},{"陈红  ",790632,'f',20,"计91",1},{"刘建平",790633,'m',21,"计91",0},{"张丽丽",790634,'m',17,"计91",2}};
	pNode pHead = NULL;
	pHead = init_Stud();
	build_Stud(pHead,student);
	
	while(flag)	
	{
		printf("1:将结构体数组student中的记录按学号非降序插入\n");
		printf("2:将文件中的记录按学号非降序插入链表\n");
		printf("3:键盘输入新纪录，并将其按学号非降序插入链表\n");
		printf("4:删除链表中第一个给定学号的记录\n");
		printf("5:删除链表中第一个给定姓名的记录\n");
		printf("6:修改链表中第一个给定学号的记录\n");
		printf("7:修改链表中第一个给定姓名的记录\n");
		printf("8:查找链表中第一个给定学号的记录\n");
		printf("9:查找链表中第一个给定姓名的记录\n");
		printf("10:显示链表所有记录\n");
		printf("11:将链表中的所有记录存入文件\n");
		printf("12:结束\n");
		do
		{
			printf("选择的操作为:");
			scanf("%d",&i);
		}while(i>12||i<0);
		printf("\n");
		switch(i)
		{
		case 1:	{
					for(int i=1;i<4;i++)
					{
						insert_Stud(pHead,student+i);
					}
					break;
				}
		case 2:if((fp = fopen("text.txt","a+") )== NULL)
				{
					fprintf(stderr,"%s","open failed!");
					exit(-1);
				}
				else
				{
					rewind(fp);							//要读取文件必须回到文件的开头这一步很重要
					fread_file(pHead,fp);
				}
				fclose(fp);
				break;
		case 3:
				insert_Stud(pHead,readin_Stud());
				break;
		case 4:
				printf("请输入删除学生的学号:");
				scanf("%ld",&delete_num);
				delete_Stud_num(pHead,delete_num);
				break;
		case 5:	printf("请输入删除学生的名字:");
				scanf("%s",delete_name);
				delete_Stud_name(pHead,delete_name);
				break;
		case 6:printf("请输入修改学生的学号:");
			   scanf("%ld",&modify_num);
			   modify_num_file(pHead,modify_num);
			   break;
		case 7:printf("请输入修改学生的名字:");
			   scanf("%s",&modify_name);
			   modify_name_file(pHead,modify_name);
			   break;
		case 8:printf("请输入查找学生的学号:");
			   scanf("%ld",&find_num);
			   Find_Stud_num(pHead,find_num);
			   break;
		case 9:printf("请输入查找学生的名字:");
			   scanf("%s",find_name);
			   Find_Stud_name(pHead,find_name);
			   break;
		case 10:traverse_Stud(pHead);
				break;
		case 11:if((fp = fopen("text.txt","a+") )== NULL)
				{
					fprintf(stderr,"%s","open failed!");
					exit(-1);
				}
				else
				{
					fwrite_file(pHead,fp);
				}
				fclose(fp);
				break;
		case 12:flag = 0;
				break;
		}
	}
}

struct Node* init_Stud()
{
	pNode pHead = (pNode)malloc(sizeof(Node));
	if(pHead == NULL)
	{
		printf("分配失败!");
		exit(-1);
	}
	else
	{
		pHead->pNext = NULL;
	}
	return pHead;
}

void build_Stud(pNode pHead,pStud e)
{
	pNode pNew = (pNode)malloc(sizeof(Node));
	if(pHead == NULL)
	{
		printf("分配失败!");
		exit(-1);
	}
	else
	{
		pNew->data = e;
		pHead->pNext = pNew;
		pNew->pNext = NULL;
	}
}

void traverse_Stud(pNode pHead)
{
	if(empty(pHead))
	{
		printf("学生表为空!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		printf("学号   姓名   年纪   性别   班级   健康\n");
		while(p)
		{
			printf("%6ld %3s %d %5c %9s %3d\n",p->data->num,p->data->name,p->data->age,p->data->sex,p->data->Class,p->data->health);
			p = p->pNext;
		}
	}
}

void insert_Stud(pNode pHead,pStud e)
{
	pNode p = pHead->pNext;
	pNode q = pHead;
	while(p&&e->name>p->data->name)
	{
		q = p;
		p = p->pNext;
	}
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->data = e;
	pNew->pNext = q->pNext;
	q->pNext = pNew;
}

struct Stud* readin_Stud()
{
	pStud stdentelem = (pStud)malloc(sizeof(Stud));
	if(stdentelem == NULL)
	{
		printf("学生名单建立失败!");
		exit(-1);
	}
	else
	{
		printf("请输入学生的学号:");
		scanf("%ld",&stdentelem->num);
		printf("\n请输入学生的姓名:");
		scanf("%s",stdentelem->name);
		printf("\n请输入学生的性别:");
		scanf("%*c%c",&stdentelem->sex);
		printf("\n请输入学生的年纪:");
		scanf("%d",&stdentelem->age);
		printf("\n请输入学生的班级:");
		scanf("%s",stdentelem->Class);
		printf("\n请输入学生的健康状况");
		scanf("%d",&stdentelem->health);
	}
	return stdentelem;
}

void delete_Stud_num(pNode pHead,long int num)
{
	if(empty(pHead))
	{
		printf("学生表为空!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		pNode q = pHead;
		while(p&&p->data->num != num)
		{
			q = p;
			p = p->pNext;
		}
		if(p)
		{
			q->pNext = p->pNext;
			free(p);
		}
		else
		{
			printf("删除失败!\n");
		}
	}
}

void delete_Stud_name(pNode pHead,char name[])
{
	if(empty(pHead))
	{
		printf("链表为空!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		pNode q = pHead;
		while(p&&strcmp(p->data->name, name) != 0)
		{
			q = p;
			p = p->pNext;
		}
		if(p)
		{	
			q->pNext = p->pNext;
			free(p);
		}
		else
		{
			printf("删除失败!\n");
		}
	}
}

void Find_Stud_num(pNode pHead,long int num)
{
	if(empty(pHead))
	{
		printf("链表为空!\n");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		while(p&&p->data->num != num)
		{
			p = p->pNext;
		}
		if(p)
		{
			printf("%6ld %3s %d %5c %9s %3d\n",p->data->num,p->data->name,p->data->age,p->data->sex,p->data->Class,p->data->health);
		}
		else
		{
			printf("输入名找不到!\n");
		}
	}
}

void Find_Stud_name(pNode pHead,char name[])
{
	if(empty(pHead))
	{
		printf("链表为空!\n");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		while(p&&strcmp(p->data->name, name) != 0)
		{
			p = p->pNext;
		}
		if(p)
		{
			printf("%6ld %3s %d %5c %9s %3d\n",p->data->num,p->data->name,p->data->age,p->data->sex,p->data->Class,p->data->health);
		}
		else
		{
			printf("输入名找不到!\n");
		}
	}
}

void fwrite_file(pNode pHead,FILE *fp)
{
	if(empty(pHead))
	{
		printf("存储列表为空!\n");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		while(p)
		{
			fwrite(p->data,sizeof(Stud),1,fp);
			p = p->pNext;
		}
	}
}

void fread_file(pNode pHead,FILE *fp)
{
	int count;
	do
	{
		pStud stdentelem = (pStud)malloc(sizeof(Stud));
		if(stdentelem == NULL)
		{
			printf("学生名单建立失败!");
			exit(-1);
		}
		else
		{
			count = fread(stdentelem,sizeof(Stud),1,fp);
			if(count>0)
			{
				insert_Stud(pHead,stdentelem);
			}
		}
	}while(count > 0);
}

void modify_num_file(pNode pHead,long int num)
{
	if(empty(pHead))
	{
		printf("学生表为空!");
		exit(-1);
	}
	else
	{
		char s[80];
		pNode p = pHead->pNext;
		while(p&&p->data->num != num)
		{
			p = p->pNext;
		}
		if(p)
		{
			printf("%6ld %3s %d %5c %9s %3d\n",p->data->num,p->data->name,p->data->age,p->data->sex,p->data->Class,p->data->health);
			printf("请输入要修改的内容，不修改的按回车键跳过\n");
			fflush(stdin);
			printf("请输入要修改的姓名:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->name,s);
			}
			printf("请输入要修改的学号:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->num = atoi(s);
			}
			printf("请输入要修改的性别:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->sex = s[0];
			}
			printf("请输入要修改的年纪:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->age = atoi(s);
			}
			printf("请输入要修改的班级:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->Class,s);
			}
			printf("请输入要修改的健康状况:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->health = atoi(s);
			}
		}
		else
		{
			printf("不出在输入学号!\n");
			exit(-1);
		}
		//fflush(stdin);
	}
}

void modify_name_file(pNode pHead,char name[])
{
	if(empty(pHead))
	{
		printf("学生表为空!");
		exit(-1);
	}
	else
	{
		char s[80];
		pNode p = pHead->pNext;
		while(p&&strcmp(p->data->name,name) != 0)
		{
			p = p->pNext;
		}
		if(p)
		{
			printf("%6ld %3s %d %5c %9s %3d\n",p->data->num,p->data->name,p->data->age,p->data->sex,p->data->Class,p->data->health);
			printf("请输入要修改的内容，不修改的按回车键跳过\n");
			fflush(stdin);
			printf("请输入要修改的姓名:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->name,s);
			}
			printf("请输入要修改的学号:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->num = atoi(s);
			}
			printf("请输入要修改的性别:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->sex = s[0];
			}
			printf("请输入要修改的年纪:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->age = atoi(s);
			}
			printf("请输入要修改的班级:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->Class,s);
			}
			printf("请输入要修改的健康状况:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->health = atoi(s);
			}
		}
		else
		{
			printf("不存在输入姓名!\n");
			exit(-1);
		}
	}
}

bool empty(pNode pHead)
{
	if(pHead->pNext == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
