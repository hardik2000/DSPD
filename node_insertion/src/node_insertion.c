/*
 ============================================================================
 Name        : LinkedListSem3.c
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
struct Node * Deletion(struct Node *lptr)
{
	struct Node *ptr;
	while(lptr !=NULL)
	{
		ptr=lptr;
		lptr=ptr->next;
		free(ptr);
	}
	printf("All Deleted Successfully");
	return lptr;
}
struct Node * InsertAtStart(int data,struct Node * lptr) //generic function
{
	struct Node *ptr;
	ptr=CreateNode(data);
	ptr->next=lptr;
	lptr=ptr;

	return lptr;
}

struct Node * InsertAtMiddle(int data,struct Node * lptr)
{
	struct Node *ptr;
	ptr=CreateNode(data);

	struct Node *slow,*fast,*temp;
	slow=lptr;
	fast=lptr->next->next;
	while(fast!=NULL)
	{

		slow=slow->next;
		fast=fast->next;
		if(fast!=NULL)
		{
			fast=fast->next;
		}
	}
	temp=slow->next;
	slow->next=ptr;
	ptr->next=temp;

	return lptr;
}

struct Node * InsertAtEnd(int data,struct Node * lptr)
{
	struct Node *ptr,*nptr;
	nptr=CreateNode(data);
	ptr=lptr;
	if(ptr==NULL)
	{
		lptr=nptr;
	}
	else
	{
		while(ptr->next !=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next=nptr;
	}
	return lptr;

}





struct Node * Deleteatstart(int* datadel,struct Node * lptr) //loop hole what if it is null
{
	struct Node *ptr;
	ptr=lptr;
	*datadel=ptr->data;
	lptr=ptr->next;
	free(ptr);

	return lptr;
}

status_code DeleteAtStart(Itemtype *datadel,struct Node ** lpptr) //generic delete at start
{
	status_code sc=SUCCESS;
	struct Node *ptr,*lptr;
	lptr=*lpptr;
	if(*lpptr==NULL)
	{
		sc=FAILURE;
	}
	else
	{
		ptr=lptr;
		lptr=lptr->next;
		*datadel=ptr->data;
		free(ptr);
		*lpptr=lptr;
	}
	return sc;

}
struct Node * DeleteAtEnd(Itemtype * datadel,struct Node * lptr)
{
	struct Node * ptr,*prev;
	if(lptr!=NULL)
	{
		prev=NULL;
		ptr=lptr;
		while(ptr->next!=NULL)
		{
			prev=ptr;
			ptr=ptr->next;
		}
		if(prev!=NULL)
		{
			prev->next=NULL;
		}
		else
		{
			lptr=NULL;
		}
		*datadel=ptr->data;
		free(ptr);
	}

	return lptr;
}




int main(void)
{
	struct Node  *lptr ;
	lptr=CreateList(10);
	printf("\nLIST CREATED IS:\n");
	Traverse(lptr);
	printf("\nLIST AFTER INSERTION AT START \n");
	lptr=InsertAtStart(11,lptr);
	Traverse(lptr);
	printf("\nLIST AFTER INSERTION AT MIDDLE \n");
	lptr=InsertAtMiddle(11,lptr);
	Traverse(lptr);
	printf("\nLIST AFTER INSERTION AT END \n");
	lptr=InsertAtEnd(11,lptr);
	Traverse(lptr);




	return 0;
}
