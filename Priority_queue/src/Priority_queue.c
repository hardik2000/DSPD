/*
 ============================================================================
 Name        : Priority_queue.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define NUMP 5
typedef enum{FAILURE,SUCCESS} status_code;
typedef enum{false,true} boolean;
#define process int
typedef struct Node
{
	int data;
	struct Node * next;
}node;

typedef struct queue_tag
{
	node *front,*rear;

}Queue;


typedef struct PrQ_tag
{
	Queue PrQ[NUMP];

}Priority_Queue_type;

void Initialise(Queue *qptr)
{
	qptr->front=NULL;
	qptr->rear=NULL;
}


void Initialise_PQ(Priority_Queue_type *pqptr)
{
	for(int i=0;i<NUMP;i++)
	{
		Initialise(&pqptr->PrQ[i]);
	}
}

boolean IsQueueEmpty(Queue *qptr)
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
struct Node * CreateNode(int data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
status_code InsertQ(Queue *qptr,int x)
{
	status_code retval=SUCCESS;
	node *nptr=CreateNode(x);
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

status_code DeleteQ(int *x,Queue *qptr)
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

void Insert(process pr,int priority,Priority_Queue_type *pqptr)
{
	InsertQ(&(pqptr->PrQ[priority]),pr);
}
status_code Delete(process *prptr,Priority_Queue_type *pqptr)
{
	status_code sc=SUCCESS;
	int i=0;
	while(IsQueueEmpty(&(pqptr->PrQ[i])) && i<NUMP)
	{
		i++;
	}
	if(i<NUMP)
	{
		sc=DeleteQ(prptr,&pqptr->PrQ[i]);

	}
	else
	{
		sc=FAILURE;
	}
	return sc;
}
void Traverse(Queue *ptr)
{
	node *temp;
	temp=ptr->front;

	while(temp!=ptr->rear->next)
	{
		printf("%d -> ",temp->data);
		temp=temp->next;
	}
}

void TraversePr(Priority_Queue_type *pqptr)
{
	int i=0;
	while(i<5)
	{
		if((&pqptr->PrQ[i])->front!=NULL)
		{
			printf("THE DATA IN PRIORITY LEVEL %d IS :",i);
			Traverse(&pqptr->PrQ[i]);
			printf("NULL");
		}
		else
		{
			printf("THE DATA IN PRIORITY LEVEL  %d IS : NULL",i);
		}
		printf("\n");
		i++;

	}



}



int main(void)
{
	Priority_Queue_type *PQ;
	int *p;
	p=(int *)malloc(sizeof(int));
	*p=0;
	PQ=(Priority_Queue_type *)malloc(sizeof(Priority_Queue_type));
	Initialise_PQ(PQ);
	Insert(11,0,PQ);
	Insert(12,0,PQ);
	Insert(21,1,PQ);
	Insert(22,1,PQ);
	Insert(23,1,PQ);
	Insert(30,2,PQ);
	Insert(31,2,PQ);
	Insert(32,2,PQ);
	Insert(33,2,PQ);
	TraversePr(PQ);
	status_code sc=Delete(p,PQ);
	if(sc==SUCCESS)
	{
		printf("DELETED ELEMENT IS %d\n",*p);
	}
	TraversePr(PQ);










	return 0;
}
