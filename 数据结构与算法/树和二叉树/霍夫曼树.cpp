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
    printf("请输入权值的个数(>1)");
    scanf("%d",&n);
    w = (int*)malloc(n*sizeof(int));
    printf("请依次输入%d个权值(整型):\n",n);
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
    m = 2*n-1;      //树根节点和子节点加起来一共有m个
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
    for(i=n+1;i<=m;i++)                 //建立赫夫曼树
    {
        select(HT,i-1,s1,s2);           //s1,s2分别为parent为0且weight最小的两个节点
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //从叶子到根逆向求每个字符的赫夫曼
    HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
    cd = (char*)malloc(n*sizeof(char));
    cd[n-1] = '\0';      //编码结束符位置
    for(i=1;i<=n;i++)
    {
        start = n-1;    //编码结束符位置
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)     //这里循环生成前n个子树的权重对应的编码
        {
            if(HT[f].lchild==c)         //判断是左分支还是右分支
                cd[--start] = '0';
            else
                cd[--start] = '1';
            HC[i] = (char*)malloc((n-start)*sizeof(char));  //为第i个字符编码分配空间
            strcpy(HC[i],&cd[start]);                       //从cd复制编码串到HC
        }
    }
    free(cd);     //释放工作空间
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
    unsigned int k = UINTMAX;          //这里选取一个肯定大于所有权重的数
    for(j=1;j<=i;j++)
    {
        if(t[j].weight<k&&t[j].parent==0)
            {
                k=t[j].weight;
                flag = j;
            }
    }
    t[flag].parent = 1;                 //这里是找到最小值后做个标记，下次在找的时候就忽略这个最小值，找的为次小值
    return flag;
}
