
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000			//�����ÿռ�Ĵ�С(��WORD���ֽ���Ϊ��λ)
#define e 10				//��С����ռ��С

typedef struct WORD
{
	union
	{
		WORD *llink;		//ͷ����,ָ��ǰ���ڵ�
		WORD *uplink;		//�ײ���,ָ�򱾽ڵ�ͷ��
	};
	int tag;				//���־,0:����,1:ռ��,ͷ����β������
	int size;				//ͷ����,���С
	WORD *rlink;			//ͷ����,ָ��������
}WORD,head,foot,*Space;		//*Space:�������ÿռ�ָ������

#define FootLoc(p) ((p)+(p->size)-1)	//�������ĺ궨��,ָ��p��ָ���ĵײ�(���һ����)

void Print(Space);
Space AllocBoundTag(Space &,int n);
void PrintUser(Space p[]);
void Reclaim(Space &,Space &);

void main()
{
	Space pav,p;							//���п�ָ��
	Space v[MAX/e] = {NULL};				//ռ�ÿ�ָ������(��ʼ��Ϊ��)
	int n;
	printf("�ṹ��WORDΪ%d���ֽ�\n",sizeof(WORD));
	p = new WORD[MAX+2];					//new��C++�еĲ�����,��ͬ��p = (Space)malloc(sizof(WORD)*MAX);
	p->tag = 1;								//���õ�ַ�߽�,�Է����������ڿ�ʱ����
	pav = p+1;								//�����ÿռ��ı�ͷ
	pav->rlink = pav->llink = pav;			//��ʼ���������ÿռ�(һ������)
	pav->tag = 0;
	pav->size = MAX;
	p = FootLoc(pav);						//pָ��ײ���
	p->uplink = pav;
	p->tag = 0;
	(p+1)->tag = 1;							//���øߵ�ַ�߽�,�Է����������ڿ�ʱ����
	printf("��ʼ����,�������ÿռ��Ϊ:\n");
	Print(pav);
	n = 300;
	v[0] = AllocBoundTag(pav,n);
	printf("����%u���洢�ռ��,�����ÿռ��Ϊ:\n",n);
	Print(pav);
	PrintUser(v);
	n = 450;
	v[1] = AllocBoundTag(pav,n);
	printf("����%u���洢�ռ��,�����ÿռ��Ϊ:\n",n);
	Print(pav);
	PrintUser(v);
	n = 300;								//���䲻�ɹ�
	v[2] = AllocBoundTag(pav,n);
	printf("����%u���洢�ռ��(���ɹ�),pavΪ:\n",n);
	Print(pav);
	PrintUser(v);
	n = 242;
	v[2] = AllocBoundTag(pav,n);
	printf("����%u���洢�ռ��(�������),pavΪ:\n",n);
	Print(pav);
	PrintUser(v);
	printf("����v[0](%d)��(��pav��ʱ����),pavΪ:\n",v[0]->size);
	Reclaim(pav,v[0]);		//pavΪ��
	Print(pav);
	PrintUser(v);
	printf("1���س�������");
	getchar();
	printf("����v[2](%d)��(����������Ϊռ�ÿ�),pavΪ:\n",v[2]->size);
}

void Print(Space p)
{
	Space h,f;
	if(p)
	{
		h = p;				//hָ���һ������ͷ����(�׵�ַ)
		f = FootLoc(h);		//fָ���һ�����ĵײ���
		do
		{
			printf("��Ĵ�С=%d ����׵�ַ=0x%x ",h->size,f->uplink);	//��������Ϣ
			printf("���־=%d(0:���� 1:ռ��) �ڿ��׵�ַ=0x%x\n",h->tag,f+1);
			h = h->rlink;										  //ָ����һ������ͷ����(�׵�ַ)
			f = FootLoc(h);										  //fָ����һ�����ĵײ���	
		}while(h!=p);
	}
}

Space AllocBoundTag(Space &pav,int n)
{
	Space p,f;
	for(p=pav;p&&p->size<n&&p->rlink!=pav;p=p->rlink);		//���Ҳ�С��N�Ŀ��п�
	if(!p||p->size<n)										//�Ҳ���,���ؿ�ָ��
		return NULL;
	else													//pָ���ҵ��Ŀ��п�
	{
		f = FootLoc(p);										//ָ��ײ�
		pav = p->rlink;										//pavָ��*p���ĺ������
		if(p->size-n<=e)									//�������,������<=e��ʣ����
		{
			if(pav==p)
				pav = NULL;
			else											//�ڱ���ɾ������Ľ��
			{
				pav->llink = p->llink;
				p->llink->rlink = pav;
			}
			p->tag = f->tag = 1;							//�޸ķ������ͷ���͵ײ���־
		}
		else
		{
			f->tag = 1;										//�޸ķ����ĵײ���־
			p->size -= n;									//��ʣ����С
			f = FootLoc(p);									//ָ��ʣ���ײ�
			f->tag = 0;										//����ʣ���ײ�
			f->uplink = p;
			p = f+1;										//ָ�����ͷ��
			p->tag = 1;										//���÷���ͷ��
			p->size = n;
		}
		return p;											//���ط�����׵�ַ
	}
}

void PrintUser(Space p[])									//���p������ָ���ѷ���ռ�
{
	for(int i=0;i<MAX/e;i++)
	{
		if(p[i])											//ָ�벻Ϊ0(ָ��һ��ռ�ÿ�)
		{
			printf("��%d���׵�ַ=0x%x ",i,p[i]);				//��������Ϣ
			printf("��Ĵ�С=%d ��ͷ��־=%d(0:���� 1:ռ��)",p[i]->size,p[i]->tag);
			printf("��β��־=%d ��β��ַ0x%x\n",(FootLoc(p[i]))->tag,FootLoc(p[i]));
		}
	}
}

void Reclaim(Space &pav,Space &p)
{
	Space s=(p-1)->uplink,t=p+p->size;						//s,t�ֱ�ָ���ͷſ�������ڿ�(����ʱ)���׵�ַ
	int l=(p-1)->tag,r=(p+p->size)->tag;					//l��r�ֱ�ָʾ�ͷŵ������ڿ��Ƿ����
	if(!pav)												//�����ÿռ���
	{//���ͷſ���뵽pav��ָ�Ŀ����ñ���
		pav = p->llink = p->rlink = p;						//ͷ���������ָ�뼰pav��ָ���ͷſ�
		
	}
}