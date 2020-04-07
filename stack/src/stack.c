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

typedef struct stack_tag
{
	item_type items[MAX];
	int top;
}stack;

void Initialise(stack* s)
{
	s->top=0;
}

status_code push(stack* s,int x)
{
	status_code retval=SUCCESS;
	if(s->top==MAX)
	{
		retval=FAILURE;
	}
	else
	{
		s->items[s->top]=x;
		s->top++;
	}

	return retval;
}

status_code pop(int *x,stack *s)
{
	status_code retval=SUCCESS;
	if(s->top==0)
	{
		retval=FAILURE;
	}
	else
	{
		s->top--;

		*x=s->items[s->top];

	}

	return retval;
}
int main(void)
{
	item_type x;
	int n,i;
	stack s1;
	Initialise(&s1);
	status_code sc;
	for(i=0;i<5;i++)
	{
		printf("Enter the no be inserted");
		scanf("%d",&x);
		sc=push(&s1,x);
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
		sc=pop(&x,&s1);
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
