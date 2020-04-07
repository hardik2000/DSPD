/*
 ============================================================================
 Name        : Sorting_Selection.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// C++ implementation of recursive selection sort
// for singly linked list | Swapping node links
#include <stdio.h>

struct Node
{
	int data;
	struct Node* next;
};
struct Node * CreateNode(int data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
struct Node * CreateList(int num)
{
	struct Node *ptr,*lptr;
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

struct Node * Selection_Sort(struct Node *head)
{
	struct Node *ptr,*currX,*prevX,*currY,*prevY;
	ptr=head;
	int count =0;
	struct Node * min, * minprev;
	min=NULL;
	minprev=NULL;
	if(ptr!=NULL || ptr->next!=NULL)
	{
		currX=ptr;
		prevX=CreateNode(-1);
		prevX->next=currX;
		currY=ptr->next;
		prevY=ptr;



		while(currX->next!=NULL)
		{
			min=currX;

			currY=currX->next;
			while(currY!=NULL)
			{
				if(currY->data <min->data)
				{
					min=currY;
					minprev=prevY;
				}
				prevY=currY;
				currY=currY->next;
				count++;
			}
			if(min==currX->next)
			{
				prevX->next=currX->next;
				currX->next=min->next;
				min->next=currX;

			}
			else if(min!=currX)
			{
				prevX->next=currX->next;
				currX->next=min->next;
				minprev->next=currX;
				min->next=prevX->next;
				prevX->next=min;
			}
			currX=min;
			currX=currX->next;
			if(prevX->data==-1)
			{
				ptr=prevX->next;
			}
			prevX=prevX->next;

		}
	}
	//Traverse(ptr);
//	printf("No of count required is: %d\n",count);
	return ptr;
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

int main()
{
	struct Node* head = NULL;
	int x;
	printf("Enter the no of elements to be inserted\n ");
	scanf("%d",&x);
	head=CreateList(x);
	printf("BEFORE SORTING IS:\n");
	Traverse(head);
	printf("\n");
	head=Selection_Sort(head);
	printf("AFTER SORTING IS:\n");
	Traverse(head);


	return 0;
}
