/*
 ============================================================================
 Name        : pre_post.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


typedef char item_type;

typedef enum{FAILURE,SUCCESS} status_code;
typedef enum{false,true} boolean;

typedef struct Node
{
	item_type data;
	struct Node * next;
}node;

typedef struct stack_tag
{
	node * top;

}stack;

typedef struct queue_tag
{
	node *front,*rear;

}queue;


void Initialisestack(stack *sptr)
{
	sptr->top=NULL;
}

void Initialisequeue(queue *qptr)
{
	qptr->front=NULL;
	qptr->rear=NULL;
}

struct Node * CreateNode(item_type data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
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


status_code insert(queue *qptr,item_type x)
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





status_code pop(item_type *x,stack * sptr)
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

status_code delete(item_type *x,queue *qptr)
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
int prec(char c)
{
    if(c == '*')
    {
    	return 2;
    }
    else if(c == '/')
    {
    	return 2;
    }
    else if(c == '+')
    {
    	return 1;
    }
    else if(c == '-')
    {
    	return 1;
    }
    else
    {
    	return -1;
    }

}





int main(void)
{
	int i,ch,countch=0,countsign=0;
	status_code sc;
	stack sptr;
	queue output;
	Initialisestack(&sptr);

	Initialisequeue(&output);
	char *str;
	str=(char *)malloc(sizeof(char)*20);
	char c,sign;

	printf("INPUT THE STRING");
	scanf("%s",str);
	i=0;
	while(str[i]!='\0')
	{
		c=str[i];
	 // printf("%c",c);

		ch=prec(c);
	//	printf("%d",ch);

		if(ch==-1)
		{
			sc=insert(&output,c);
			if(sc==SUCCESS)
			{
				//printf("\nElement pushed\n");
			}
			else
			{
				//printf("\nElement not pushed\n");
			}
			countch++;
		}
		else if(ch==2)
		{
			countsign++;
			sc=pop(&sign,&sptr);
			if(sc==SUCCESS)
			{
				if(prec(sign)==2 && sc==SUCCESS)
				{
					insert(&output,sign);
				}
				else
				{
					push(&sptr,sign);

				}
			}
			push(&sptr,c);
		}
		else if(ch==1)
		{
			countsign++;
			sc=pop(&sign,&sptr);
			if(sc==SUCCESS)
			{
				if(prec(sign)==1 && sc==SUCCESS)
				{
					insert(&output,sign);

				}
				else
				{
					push(&sptr,sign);

				}
			}
			push(&sptr,c);
		}
		if(countch>=countsign)
		{
			countsign=countch-1;
			while(!IsEmpty(&sptr) && countsign>0)
			{
				pop(&sign,&sptr);
				insert(&output,sign);
				countsign--;
			}
			countsign=1;
			countch=0;
		}

		i++;
	}
	while(!IsEmpty(&sptr))
	{
		pop(&sign,&sptr);
		insert(&output,sign);
	}

	while(!IsQueueEmpty(&output))
	{
		status_code sc;
		sc=delete(&c,&output);
		if(sc==SUCCESS)
		{
			printf("%c",c);
		}
		else
		{
			printf("\nElement not popped\n");
		}

	}

	return 0;
}
