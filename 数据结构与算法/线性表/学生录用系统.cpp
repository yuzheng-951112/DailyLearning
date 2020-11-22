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
	Stud student[4] = {{"��С��",790631,'m',18,"��91",0},{"�º�  ",790632,'f',20,"��91",1},{"����ƽ",790633,'m',21,"��91",0},{"������",790634,'m',17,"��91",2}};
	pNode pHead = NULL;
	pHead = init_Stud();
	build_Stud(pHead,student);
	
	while(flag)	
	{
		printf("1:���ṹ������student�еļ�¼��ѧ�ŷǽ������\n");
		printf("2:���ļ��еļ�¼��ѧ�ŷǽ����������\n");
		printf("3:���������¼�¼�������䰴ѧ�ŷǽ����������\n");
		printf("4:ɾ�������е�һ������ѧ�ŵļ�¼\n");
		printf("5:ɾ�������е�һ�����������ļ�¼\n");
		printf("6:�޸������е�һ������ѧ�ŵļ�¼\n");
		printf("7:�޸������е�һ�����������ļ�¼\n");
		printf("8:���������е�һ������ѧ�ŵļ�¼\n");
		printf("9:���������е�һ�����������ļ�¼\n");
		printf("10:��ʾ�������м�¼\n");
		printf("11:�������е����м�¼�����ļ�\n");
		printf("12:����\n");
		do
		{
			printf("ѡ��Ĳ���Ϊ:");
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
					rewind(fp);							//Ҫ��ȡ�ļ�����ص��ļ��Ŀ�ͷ��һ������Ҫ
					fread_file(pHead,fp);
				}
				fclose(fp);
				break;
		case 3:
				insert_Stud(pHead,readin_Stud());
				break;
		case 4:
				printf("������ɾ��ѧ����ѧ��:");
				scanf("%ld",&delete_num);
				delete_Stud_num(pHead,delete_num);
				break;
		case 5:	printf("������ɾ��ѧ��������:");
				scanf("%s",delete_name);
				delete_Stud_name(pHead,delete_name);
				break;
		case 6:printf("�������޸�ѧ����ѧ��:");
			   scanf("%ld",&modify_num);
			   modify_num_file(pHead,modify_num);
			   break;
		case 7:printf("�������޸�ѧ��������:");
			   scanf("%s",&modify_name);
			   modify_name_file(pHead,modify_name);
			   break;
		case 8:printf("���������ѧ����ѧ��:");
			   scanf("%ld",&find_num);
			   Find_Stud_num(pHead,find_num);
			   break;
		case 9:printf("���������ѧ��������:");
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
		printf("����ʧ��!");
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
		printf("����ʧ��!");
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
		printf("ѧ����Ϊ��!");
		exit(-1);
	}
	else
	{
		pNode p = pHead->pNext;
		printf("ѧ��   ����   ���   �Ա�   �༶   ����\n");
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
		printf("ѧ����������ʧ��!");
		exit(-1);
	}
	else
	{
		printf("������ѧ����ѧ��:");
		scanf("%ld",&stdentelem->num);
		printf("\n������ѧ��������:");
		scanf("%s",stdentelem->name);
		printf("\n������ѧ�����Ա�:");
		scanf("%*c%c",&stdentelem->sex);
		printf("\n������ѧ�������:");
		scanf("%d",&stdentelem->age);
		printf("\n������ѧ���İ༶:");
		scanf("%s",stdentelem->Class);
		printf("\n������ѧ���Ľ���״��");
		scanf("%d",&stdentelem->health);
	}
	return stdentelem;
}

void delete_Stud_num(pNode pHead,long int num)
{
	if(empty(pHead))
	{
		printf("ѧ����Ϊ��!");
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
			printf("ɾ��ʧ��!\n");
		}
	}
}

void delete_Stud_name(pNode pHead,char name[])
{
	if(empty(pHead))
	{
		printf("����Ϊ��!");
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
			printf("ɾ��ʧ��!\n");
		}
	}
}

void Find_Stud_num(pNode pHead,long int num)
{
	if(empty(pHead))
	{
		printf("����Ϊ��!\n");
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
			printf("�������Ҳ���!\n");
		}
	}
}

void Find_Stud_name(pNode pHead,char name[])
{
	if(empty(pHead))
	{
		printf("����Ϊ��!\n");
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
			printf("�������Ҳ���!\n");
		}
	}
}

void fwrite_file(pNode pHead,FILE *fp)
{
	if(empty(pHead))
	{
		printf("�洢�б�Ϊ��!\n");
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
			printf("ѧ����������ʧ��!");
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
		printf("ѧ����Ϊ��!");
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
			printf("������Ҫ�޸ĵ����ݣ����޸ĵİ��س�������\n");
			fflush(stdin);
			printf("������Ҫ�޸ĵ�����:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->name,s);
			}
			printf("������Ҫ�޸ĵ�ѧ��:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->num = atoi(s);
			}
			printf("������Ҫ�޸ĵ��Ա�:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->sex = s[0];
			}
			printf("������Ҫ�޸ĵ����:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->age = atoi(s);
			}
			printf("������Ҫ�޸ĵİ༶:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->Class,s);
			}
			printf("������Ҫ�޸ĵĽ���״��:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->health = atoi(s);
			}
		}
		else
		{
			printf("����������ѧ��!\n");
			exit(-1);
		}
		//fflush(stdin);
	}
}

void modify_name_file(pNode pHead,char name[])
{
	if(empty(pHead))
	{
		printf("ѧ����Ϊ��!");
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
			printf("������Ҫ�޸ĵ����ݣ����޸ĵİ��س�������\n");
			fflush(stdin);
			printf("������Ҫ�޸ĵ�����:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->name,s);
			}
			printf("������Ҫ�޸ĵ�ѧ��:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->num = atoi(s);
			}
			printf("������Ҫ�޸ĵ��Ա�:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->sex = s[0];
			}
			printf("������Ҫ�޸ĵ����:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->age = atoi(s);
			}
			printf("������Ҫ�޸ĵİ༶:");
			gets(s);
			if(strlen(s)>0)
			{
				strcpy(p->data->Class,s);
			}
			printf("������Ҫ�޸ĵĽ���״��:");
			gets(s);
			if(strlen(s)>0)
			{
				p->data->health = atoi(s);
			}
		}
		else
		{
			printf("��������������!\n");
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
