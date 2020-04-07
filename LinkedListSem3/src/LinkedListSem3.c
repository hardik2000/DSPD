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
struct NOde * InsertAtEnd(int data,struct Node * lptr)
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
struct Node * Concatenate(struct Node *lptr1,struct Node *lptr2)
{
	struct Node *retptr , *ptr;
	if(lptr1==NULL)
	{
		retptr=lptr2;
	}
	else if(lptr2==NULL)
	{
		retptr=lptr1;
	}
	else
	{
		ptr=lptr1;
		while(ptr->next !=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next=lptr2;
		retptr=lptr1;
	}
	return retptr;
}
struct Node * Reverse(struct Node * lptr)
{
	struct Node *trail,*middle,*ahead;
	middle=NULL;
	ahead=lptr;
	while(ahead !=NULL)
	{
		trail=middle;
		middle=ahead;
		ahead=ahead->next;
		middle->next=trail;
	}

	return middle;
}

struct Node * ReverseRecur(struct Node *rptr,struct Node *dptr,struct Node *lptr)
{
	struct Node * ptr=NULL;
	ptr=dptr;
	if(ptr->next==NULL)
	{
		rptr=ptr;dptr=ptr;
	}
	else
	{
		dptr=ReverseRecur(rptr,dptr->next,lptr);
		dptr->next=ptr;
		dptr=ptr;


	}

	return dptr;
}



int main(void)
{
	struct Node  *lptr;
	lptr=CreateList(10);
	Traverse(lptr);
	printf("\n");
//	lptr=InsertAtStart(11,lptr);
//	int x=0;
//	Traverse(lptr);
//	int* a;
//	a=&x;
//	lptr=Deleteatstart(a,lptr);
//	printf("\n data deleted is %d \n",*a);
//	Traverse(lptr);
//
//	lptr=InsertAtStart(11,lptr);
//	Traverse(lptr);
//	status_code sc=DeleteAtStart(a,&lptr);
//	printf("\n status code is %d\n",sc);
//	Traverse(lptr);
//	printf("\n");
//	lptr=InsertAtEnd(11,lptr);
//	Traverse(lptr);
//	printf("\n");
//	cptr=CreateList(10);
//	Traverse(cptr);
//	printf("\n");
//
//	lptr=Concatenate(cptr,lptr);
//	Traverse(lptr);


	lptr=Reverse(lptr);
	printf("\n");
	Traverse(lptr);

	struct Node *rptr=NULL;
	lptr=ReverseRecur(rptr,lptr,lptr);
	lptr->next=NULL;
	Traverse(rptr);

	return 0;
}
