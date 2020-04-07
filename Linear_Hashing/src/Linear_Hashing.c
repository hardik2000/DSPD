/*
 ============================================================================
 Name        : Linear_Hashing.c
 Author      : Hardik & SUYASH
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include<stdlib.h>
#define TABLE_SIZE 10

int h[TABLE_SIZE]={NULL};

void insert()
{

int key,index,i,flag=0,hkey;
printf("\nEnter a value to insert into hash table\n");
scanf("%d",&key);
hkey=key%TABLE_SIZE;
for(i=0;i<TABLE_SIZE;i++)
{
	index=(hkey+i)%TABLE_SIZE;

    if(h[index] == NULL)
    {
    	h[index]=key;
        break;
    }

}

	if(i == TABLE_SIZE)
	{
		printf("\n Element cannot be inserted .Array full\n");
	}
}
void search()
{

	int key,index,i,flag=0,hkey;
	printf("\nEnter the  element to be searched\n");
	scanf("%d",&key);
	hkey=key%TABLE_SIZE;
	for(i=0;i<TABLE_SIZE; i++)
	{
		index=(hkey+i)%TABLE_SIZE;
		if(h[index]==key)
		{
			printf("value is found at index %d",index);
			break;
		}
	}
	if(i == TABLE_SIZE)
	{
		printf("\n Value  not found\n");
	}
}
void delete()
{

	int key,index,i,flag=0,hkey;
	printf("\nEnter the element to be deleted\n");
	scanf("%d",&key);
	hkey=key%TABLE_SIZE;
	for(i=0;i<TABLE_SIZE; i++)
	{
		index=(hkey+i)%TABLE_SIZE;
		if(h[index]==key)
		{
			printf("value is found at index %d",index);
			h[index]=NULL;
			break;
		}
	}
	if(i == TABLE_SIZE)
	{
		printf("\n Value to be deleted does not exist\n");
	}
}
void display()
{

  int i;

  printf("\n Elements in the hash table are \n");

  for(i=0;i< TABLE_SIZE; i++)
  {
	  printf("\n At index %d \t value =  %d",i,h[i]);
  }

}
int main()
{
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
