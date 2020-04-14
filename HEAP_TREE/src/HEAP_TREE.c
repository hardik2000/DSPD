/*
 ============================================================================
 Name        : HEAP_TREE.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef struct Heap_Tree
{
	int *arr;
	int capacity;
	int heap_size;
}Heap;

Heap *Initialise(Heap *root,int cap)
{
	root=(Heap *)malloc(sizeof(Heap *));
	root->arr=(int *)malloc(sizeof(int)*cap);
	root->capacity=cap;
	root->heap_size=0;

	return root;
}

int parent(int i)
{
	return ((i-1)/2);
}

int child_left(int i)
{
	return ((2*i)+1);
}

int child_right(int i)
{
	return ((2*i)+2);
}

int getMin(Heap *h)
{
	return h->arr[0];
}

void swap(int *x,int *y)
{
	int temp=*x;
	*x=*y;
	*y=temp;
}

Heap *Insert_Key(Heap *h,int k)
{
	if(h->heap_size==h->capacity)
	{
		printf("\n OVERFLOW :COULD'N INSERT KEY\n");
	}
	else
	{
		h->heap_size++;
		int i=h->heap_size-1;
		h->arr[i]=k;
		while(i!=0 && h->arr[parent(i)]>h->arr[i])
		{
			swap(&h->arr[parent(i)],&h->arr[i]);
			i=parent(i);
		}
	}

	return h;
}


Heap * change_key(Heap *h,int i,int new_val)
{
	h->arr[i]=new_val;
	while(i!=0 && h->arr[parent(i)] > h->arr[i] )
	{
		swap(&h->arr[parent(i)],&h->arr[i]);
		i=parent(i);
	}

	return h;
}

Heap *MinHeapify(int i,Heap *h)
{
	int l=child_left(i);
	int r=child_right(i);
	int smallest=i;
	if(l<h->heap_size && h->arr[l]<h->arr[i])
	{
		smallest=l;
	}
	if(r<h->heap_size && h->arr[r]<h->arr[smallest])
	{
		smallest=r;
	}
	if(smallest!=i)
	{
		swap(&h->arr[i],&h->arr[smallest]);
		h=MinHeapify(smallest,h);
	}

	return h;
}

Heap *Delete_Min(Heap *h)
{
	if(h->heap_size<=0)
	{
		printf("HEAP IS EMPTY COULD'N DELETE MINIMUM\n");
	}
	else if(h->heap_size==1)
	{
		h->heap_size--;
	}
	else
	{
		h->arr[0]=h->arr[h->heap_size-1];
		h->heap_size--;
		h=MinHeapify(0,h);
	}

	return h;
}

Heap * Delete_Key(Heap *h,int i)
{
	change_key(h,i,-1);
	h=Delete_Min(h);
	return h;
}


int main(void)
{
	int n,x;
	printf("ENTER THE SIZE OF THE ARRAY\n");
	scanf("%d",&n);
	Heap *h;
	h=NULL;
	h=Initialise(h,n);
	printf("ENTER THE NO SERIALLY:\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		h=Insert_Key(h,x);
	}
	for(int i=0;i<n;i++)
	{
		printf("%d ",getMin(h));
		h=Delete_Min(h);
	}

	return 0;
}
