/*
 ============================================================================
 Name        : Sorting_Ielection.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// C++ implementation of recursive selection sort
// for singly linked list | Swapping node links
#include <stdio.h>
static int count=0,count1=0;

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
void sortedInsert(struct Node** head_ref, struct Node* lptr)
{
	struct Node *current,*ptr;
    ptr=*head_ref;
    if (ptr == NULL || (ptr)->data >= lptr->data)
    {
        lptr->next = ptr;
        ptr = lptr;
        count++;
    }
    else
    {
        current = ptr;
        while (current->next!=NULL && current->next->data < lptr->data)
        {
            current = current->next;
            count++;
        }
        lptr->next = current->next;
        current->next = lptr;
    }

    *head_ref=ptr;
}

struct Node * InsertionSort(struct Node **head_ref)
{
    struct Node *sorted = NULL;

    struct Node *current = *head_ref;
    while (current != NULL)
    {
        struct Node *next = current->next;

        sortedInsert(&sorted, current);

        current = next;
        count1++;
    }
  //  printf("No of count required is: %d\n",count*count1);

    head_ref = &sorted;
    return sorted;
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
	head=InsertionSort(&head);


	printf("AFTER SORTING IS:\n");
	Traverse(head);


	return 0;
}
