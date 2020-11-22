#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define UINTMAX 1000;

typedef struct 
{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void HuffmanCoding(HuffmanTree &,HuffmanCode &,int*,int);
void select(HuffmanTree,int,int&,int&);
int min(HuffmanTree,int);

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int *w,n,i;
    printf("������Ȩֵ�ĸ���(>1)");
    scanf("%d",&n);
    w = (int*)malloc(n*sizeof(int));
    printf("����������%d��Ȩֵ(����):\n",n);
    for(i=0;i<=n-1;i++)
    {
        scanf("%d",w+i);
    }
    HuffmanCoding(HT,HC,w,n);
    for(i=1;i<=n;i++)
        puts(HC[i]);
    scanf("%d",&i);
    return 0;
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int* w,int n)
{
    int m,i,s1,s2,start;
    unsigned c,f;
    HuffmanTree p;
    char *cd;
    if(n<=1)
        exit(-1);
    m = 2*n-1;      //�����ڵ���ӽڵ������һ����m��
    HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for(p=HT+1,i=1;i<=n;i++,p++,w++)
    {
        (*p).weight = *w;
        (*p).parent = 0;
        (*p).lchild = 0;
        (*p).rchild = 0;
    }
    for(;i<=m;i++,p++)
        (*p).parent = 0;
    for(i=n+1;i<=m;i++)                 //�����շ�����
    {
        select(HT,i-1,s1,s2);           //s1,s2�ֱ�ΪparentΪ0��weight��С�������ڵ�
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //��Ҷ�ӵ���������ÿ���ַ��ĺշ���
    HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
    cd = (char*)malloc(n*sizeof(char));
    cd[n-1] = '\0';      //���������λ��
    for(i=1;i<=n;i++)
    {
        start = n-1;    //���������λ��
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)     //����ѭ������ǰn��������Ȩ�ض�Ӧ�ı���
        {
            if(HT[f].lchild==c)         //�ж������֧�����ҷ�֧
                cd[--start] = '0';
            else
                cd[--start] = '1';
            HC[i] = (char*)malloc((n-start)*sizeof(char));  //Ϊ��i���ַ��������ռ�
            strcpy(HC[i],&cd[start]);                       //��cd���Ʊ��봮��HC
        }
    }
    free(cd);     //�ͷŹ����ռ�
}

void select(HuffmanTree t,int i,int &s1,int &s2)
{
    int j;
    s1 = min(t,i);
    s2 = min(t,i);
    if(s1>s2)
    {
        j = s1;
        s1 = s2;
        s2 = j;
    }
}

int min(HuffmanTree t,int i)
{
    int j,flag;
    unsigned int k = UINTMAX;          //����ѡȡһ���϶���������Ȩ�ص���
    for(j=1;j<=i;j++)
    {
        if(t[j].weight<k&&t[j].parent==0)
            {
                k=t[j].weight;
                flag = j;
            }
    }
    t[flag].parent = 1;                 //�������ҵ���Сֵ��������ǣ��´����ҵ�ʱ��ͺ��������Сֵ���ҵ�Ϊ��Сֵ
    return flag;
}
