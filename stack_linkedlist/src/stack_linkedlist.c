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

typedef struct Node
{
	item_type data;
	struct Node * next;
}node;

typedef struct stack_tag
{
	node * top;

}stack;
void Initialise(stack *sptr)
{
	sptr->top=NULL;
}
struct Node * CreateNode(item_type data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
status_code push(stack *sptr,item_type x)
{
	status_code retval=SUCCESS;
	node * nptr=CreateNode(x);

	if(nptr==NULL)
	{
		retval=FAILURE;
		printf("STACK OVERFLOW\n");
	}
	else
	{
		nptr->next=sptr->top;
		sptr->top=nptr;
	}
	return retval;
}
status_code IsEmpty(stack *sptr)
{
	status_code sc=FAILURE;
	if(sptr->top==NULL)
	{
		sc=SUCCESS;

	}

	return sc;
}

status_code pop(int *x,stack * sptr)
{
	status_code retval=SUCCESS;
	node * ptr;
	if(IsEmpty(sptr))
	{
		retval=FAILURE;
	}
	else
	{
		ptr=sptr->top;
		*x=ptr->data;
		sptr->top=(sptr->top)->next;
		free(ptr);
	}
	return retval;
}
int main(void)
{
	item_type x;
	int i;
	stack sptr;
	Initialise(&sptr);
	status_code sc;
	for(i=0;i<5;i++)
	{
		printf("Enter the no be inserted");
		scanf("%d",&x);
		sc=push(&sptr,x);
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
		sc=pop(&x,&sptr);
		if(sc==SUCCESS)
		{
			printf("\nElement popped %d\n",x);
		}
		else
		{
			printf("\nElement not pushed\n");
		}

	}
	return 0;
}
