/*
 ============================================================================
 Name        : Sorting_Bubble.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef int item_type;

typedef enum{FAILURE,SUCCESS} status_code;

typedef struct Node
{
	item_type data;
	struct Node * next;
}node;

void Initialise(node * ptr)
{
	ptr->data=0;
	ptr->next=NULL;
}
node * CreateNode(item_type data)
{
	node *ptr;
	ptr=(node *)malloc(sizeof(node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
node * CreateList(item_type num)
{
	node *ptr,*lptr;
	int x=0;
	lptr=NULL;
	for(int i=0;i<num;i++)
	{
		printf("Enter the data\n");
		scanf("%d",&x);
		ptr=CreateNode(x);
		ptr->next=lptr;
		lptr=ptr;
	}
	return lptr;
}
void Traverse(struct Node *lptr)
{
	struct Node *ptr;
	ptr=lptr;
	if(ptr!=NULL)
	{
		while(ptr !=NULL)
		{
			printf("%d ",ptr->data);
			ptr=ptr->next;
		}
	}
	else
	{
		printf("LIST EMPTY\n");
	}

}
node * Bubble(node * head)
{
	node *trail,*middle,*ahead;
	trail=NULL;
	middle=NULL;
	ahead=NULL;
	trail=head;
	static int count=0;
	if(head!=NULL || head->next!=NULL)
	{

		middle=head;
		ahead=middle->next;
		if(ahead->data <middle->data )
		{
			middle->next=ahead->next;
			ahead->next=middle;
			trail=ahead;
			ahead=middle->next;

		}
		else
		{
			trail=middle;
			middle=ahead;
			ahead=ahead->next;


		}

		count++;
		head=trail;
		while(ahead!=NULL )
		{
			if(ahead->data < middle->data )
			{
				trail->next=ahead;
				middle->next=ahead->next;
				ahead->next=middle;
				trail=ahead;
				ahead=middle->next;
				//trail=middle;

			}
			else
			{
				trail=middle;
				middle=ahead;
				ahead=ahead->next;
			}
			count++;
		}

	}
//	printf("No of count required is: %d\n",count);

	return head;
}

int main(void)
{
	struct Node  *lptr,*ptr ;
	int y;
	printf("Enter the no of elelments to be inserted\n ");
	scanf("%d",&y);
	lptr=CreateList(y);
	printf("BEFORE SORTING IS:\n");
	Traverse(lptr);
	printf("\n");
	for(int i=0;i<y;i++)
	{
		lptr=Bubble(lptr);
	}
	printf("AFTER SORTING IS:\n");
	Traverse(lptr);



	return 0;
}
