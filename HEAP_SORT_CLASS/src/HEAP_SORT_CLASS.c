/*
 ============================================================================
 Name        : HEAP_SORT_CLASS.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 15
typedef int key_type;
typedef int position;
typedef struct item_tag
{
	key_type key;
}Item_type;

typedef struct List_tag
{
	int count;
	Item_type data[MAX];
}List;

void print(List *listptr)
{
	for(int i=0;i<listptr->count;i++)
	{
		printf("%d ",listptr->data[i].key);
	}
	printf("\n");
}

void InsertHeap(Item_type current,int low,int high,List *listptr)
{
	position large;
	large=(2*low)+1;
	while(large<=high)
	{
		if((large<=high-1) && (listptr->data[large].key<listptr->data[large+1].key))
		{
			large++;
		}
		if(current.key>=listptr->data[large].key)
		{
			break;
		}
		else
		{
			listptr->data[low]=listptr->data[large];
			low=large;
			large=(2*low)+1;
		}
		print(listptr);

	}
	listptr->data[low]=current;

}

void Build_Heap(List *listptr)
{
	position low;
	print(listptr);
	printf("BUILD_HEAP BEGIN\n");
	for(low=(listptr->count)/2;low>=0;low--)
	{
		InsertHeap(listptr->data[low],low,listptr->count-1,listptr);
		print(listptr);

	}
}

void HeapSort(List *listptr)
{
	position u;
	Item_type current;
	Build_Heap(listptr);
	printf("BUILD_HEAP FINSISH\n");
	for(u=(listptr->count)-1;u>=1;u--)
	{

		current=listptr->data[u];
		listptr->data[u]=listptr->data[0];
		InsertHeap(current,0,u-1,listptr);
		print(listptr);

	}
}


int main(void)
{
	List *listptr;
	listptr=(List*)malloc(sizeof(List));
	listptr->count=11;
	listptr->data[0].key=66;
	listptr->data[1].key=84;
	listptr->data[2].key=49;
	listptr->data[3].key=56;
	listptr->data[4].key=67;
	listptr->data[5].key=83;
	listptr->data[6].key=69;
	listptr->data[7].key=49;
	listptr->data[8].key=50;
	listptr->data[9].key=50;
	listptr->data[10].key=83;
	listptr->data[11].key=65;
	//print(listptr);

	HeapSort(listptr);
	print(listptr);
		for(int i=0;i<13;i++)
		{
			printf("%c",listptr->data[i]);
		}
	return 0;
}
