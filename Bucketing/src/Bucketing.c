/*
 ============================================================================
 Name        : Bucketing.c
 Author      : Hardik & SUYASH
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10
typedef struct NODE
{
	int value;
	struct Node *next;
}node;
struct Bucket
{
	int value;
	node *next;
}bucket[TABLE_SIZE];

void initialise()
{
	for(int i=0;i<TABLE_SIZE;i++)
	{
		bucket[i].value=0;
		bucket[i].next=NULL;
	}

}
void insert()
{

	int key,index,hkey;
	printf("\nEnter a value to insert into hash table\n");
	scanf("%d",&key);
	node *insert;
	insert=(node *)malloc(sizeof(node));
	insert->next=NULL;
	insert->value=key;
	hkey=key%TABLE_SIZE;
	index=(hkey)%TABLE_SIZE;

	node *ptr;
	ptr=bucket[index].next;
	if(ptr!=NULL)
	{
		while(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next=insert;
	}
	else
	{
		bucket[index].next=insert;
	}

}

void search()
{

	int key,index,flag=0,hkey;
	printf("\nEnter the  element to be searched\n");
	scanf("%d",&key);
	hkey=key%TABLE_SIZE;
	index=(hkey)%TABLE_SIZE;
	node *ptr;
	ptr=bucket[index].next;
	if(ptr!=NULL)
	{
		while(ptr!=NULL && flag==0)
		{
			if(ptr->value==key)
			{
				printf("value is found at index %d",index);
				flag=1;
			}
			ptr=ptr->next;
		}
	}
	else
	{
		printf("\n Value not found\n");
	}

}
void delete()
{

	int key,index,i,flag=0,hkey;
	printf("\nEnter the element to be deleted\n");
	scanf("%d",&key);
	hkey=key%TABLE_SIZE;
	index=(hkey)%TABLE_SIZE;
	node *ptr,*prevptr;
	prevptr=NULL;
	ptr=bucket[index].next;
	if(ptr!=NULL)
	{
		while(ptr!=NULL && flag==0)
		{
			if(ptr->value==key)
			{
				printf("value is found at index %d",index);
				flag=1;
				prevptr->next=ptr->next;
				free(ptr);
			}
			prevptr=ptr;
			ptr=ptr->next;
		}
	}
	else
	{
		printf("\n Value not found\n");
	}




	printf("\n Value to be deleted does not exist\n");
}
void display()
{

  int i;

  printf("\n Elements in the hash table are \n");

  for(i=0;i< TABLE_SIZE; i++)
  {
	  printf("\n At index %d \t values are:\n",i);
	  node *ptr;
	  ptr=bucket[i].next;
	  while(ptr!=NULL)
	  {
		  printf("%d ->",ptr->value);
		  ptr=ptr->next;
	  }
	  printf("NULL");
  }

}


int main(void)
{
	initialise();
    int opt,i,flag=0;
    while(flag==0)
    {
        printf("\nPress any one option to perform \n1. Insert\n2. Display \n3. Search \n4. Delete \n5. Exit \n");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                insert();
                break;
            case 2:
                display();
                break;
            case 3:
                search();
                break;
            case 4:
                delete();
                break;
            case 5:
                flag=1;
                break;
            default :
                printf("Enter valid input.\n");
        }
    }



	return 0;
}
