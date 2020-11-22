#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}Node,*pNode;

void initlist(pNode L);
bool empty(pNode L);
void listinsert(pNode L,int i);
int listlength(pNode L);

void main()
{
	pNode L;
	initlist(L);
	listinsert(L,5);

}

void Initial_SCL_tail(Node* L){
 *L = (LinkList)malloc(sizeof(struct Node));
 if(!(*L)){
  printf("Error:Initial:malloc!\n");
  exit(1);
 }
 (*L)->next = *L;
}

void Create_SCLtail(LinkList* L,int number){
 int i;
 LinkList new;
 LinkList tail = *L;
 printf("---Create LinkList---\n");
 for(i = 1;i <= number; i++){
  new = (LinkList)malloc(sizeof(struct Node));
  if(!new){
   printf("Error:Create_SCLtail:malloc:%d\n",i);
   exit(1);
  }
  printf("please enter %d element: ",i);
  scanf("%d",&(new->data));
  tail->next = new;
  new->next = (*L);
  tail = new;
 }
 *L = new;
}
int listlength(pNode L)
{
	int i=0;
	pNode p=L->pNext;
	while(p!=L)
	{
		i++;
		p=p->pNext;
	}
	return i;
}

bool empty(pNode L)
{
	if(L->pNext == L)
	{
		return true;
	}
	else
	{
		return false;
	}
}