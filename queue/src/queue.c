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
# define MAX 5

typedef int item_type;

typedef enum{FAILURE,SUCCESS} status_code;

typedef struct queue_tag
{
	item_type items[MAX];
	int front;
	int rear;
	status_code EMPTY;
}queue;

void Initialise(queue* s)
{
	s->front=0;
	s->rear=-1;
	s->EMPTY=SUCCESS;
}

status_code insert(queue* s,int x)
{
	status_code retval=SUCCESS;
	if(s->front==((s->rear+1)%MAX) && (s->EMPTY==FAILURE))
	{
		retval=FAILURE;
	}
	else
	{
		s->rear=(s->rear+1)%MAX;
		s->items[s->rear]=x;
		s->EMPTY=FAILURE;
	}

	return retval;
}

status_code delete(int *x,queue *s)
{
	status_code retval=SUCCESS;
	if(s->EMPTY==SUCCESS)
	{
		retval=FAILURE;
	}
	else
	{
		*x=s->items[s->front];
		s->front=(s->front+1)%MAX;
		if( s->front== ((s->rear+1)%MAX) )
		{
			s->EMPTY=SUCCESS;
		}
	}

	return retval;
}
int main(void)
{
	item_type x;
	int n,i;
	queue s1;
	Initialise(&s1);
	status_code sc;
	for(i=0;i<5;i++)
	{
		printf("Enter the no be inserted");
		scanf("%d",&x);
		sc=insert(&s1,x);
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
		sc=delete(&x,&s1);
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
