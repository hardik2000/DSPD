/*
 ============================================================================
 Name        : reverse_recursive.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define Itemtype int
struct Node
{
	Itemtype data;
	struct Node *next;

};
typedef enum{FAILURE,SUCCESS} status_code;

struct Node * CreateNode(Itemtype data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
struct Node * CreateList(Itemtype num)
{
	struct Node *ptr,*lptr;
	lptr=NULL;
	for(int i=0;i<=num;i++)
	{
		ptr=CreateNode(i);
		ptr->next=lptr;
		lptr=ptr;
	}
	return lptr;
}
void Traverse(struct Node *lptr)
{
	struct Node *ptr;
	ptr=lptr;
	while(ptr !=NULL)
	{
		printf("%d ",ptr->data);
		ptr=ptr->next;
	}
}

struct Node * Reverse(struct Node *lptr)
{
	if(lptr==NULL || lptr->next==NULL)
	{
		return lptr;
	}
	struct Node * head=Reverse(lptr->next);

	lptr->next->next=lptr;

	lptr->next=NULL;
	return head;
}


int main(void)
{
	struct Node  *lptr ;
	lptr=CreateList(10);
	printf("String before reversal is:\n");
	Traverse(lptr);
	printf("\n");
	lptr=Reverse(lptr);
	printf("String after reversal is:\n");
	Traverse(lptr);


	return 0;
}
