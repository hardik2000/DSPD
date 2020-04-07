/*
 ============================================================================
 Name        : stack.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef int item_type;

typedef enum{FAILURE,SUCCESS} status_code;
typedef enum{false,true} boolean;

typedef struct Tree_Node_Tag
{
	int data;
	struct Tree_Node_Tag * left;
	struct Tree_Node_Tag * right;

}Tree_Node;

typedef struct Node
{
	item_type data;
	struct Node * next;
}node;

typedef struct queue_tag
{
	node *front,*rear;

}queue;

void Initialise(queue *qptr)
{
	qptr->front=NULL;
	qptr->rear=NULL;
}
boolean IsQueueEmpty(queue *qptr)
{
	boolean ret_val;
	if(qptr->front==NULL && qptr->rear==NULL)
	{
		ret_val=true;
	}
	else
	{
		ret_val=false;
	}

	return ret_val;
}
struct Node * CreateNode(item_type data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
status_code insert(queue *qptr,int x)
{
	status_code retval=SUCCESS;
	node * nptr=CreateNode(x);
	if(nptr==NULL)
	{
		retval=FAILURE;
	}
	else
	{
		if(IsQueueEmpty(qptr))
		{
			qptr->front=qptr->rear=nptr;
		}
		else
		{
			qptr->rear->next=nptr;
			qptr->rear=nptr;
		}
	}

	return retval;
}

status_code delete(int *x,queue *qptr)
{
	status_code retval=SUCCESS;
	node * ptr;
	if(IsQueueEmpty(qptr))
	{
		retval=FAILURE;
	}
	else
	{
		ptr=qptr->front;
		*x=ptr->data;
		qptr->front=(qptr->front)->next;
		free(ptr);
		if(qptr->front==NULL)
		{
			qptr->rear=NULL;
		}
	}

	return retval;
}
int main(void)
{
	item_type x;
	int i;
	queue s;
	Initialise(&s);
	status_code sc;
	for(i=0;i<5;i++)
	{
		printf("Enter the no be inserted");
		scanf("%d",&x);
		sc=insert(&s,x);
		if(sc==SUCCESS)
		{
			printf("\nElement pushed\n");
		}
		else
		{
			printf("\nElement not pushed\n");
		}

	}
	for(i=0;i<5;i++)
	{
		sc=delete(&x,&s);
		if(sc==SUCCESS)
		{
			printf("\nElement popped %d\n",x);
		}
		else
		{
			printf("\nElement not popped\n");
		}

	}




	return 0;
}
