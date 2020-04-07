#include <stdio.h>
#include <stdlib.h>
struct node
	{
	int data;
	struct node *next;
};
void main()
{
	int n;
	int d;
	printf("Enter number of nodes \n");
	scanf("%d",&n);
	struct node *ptr,*nptr;
	ptr=NULL;
	int i=0;

	while(i<n)
	{
	nptr=(struct node*)malloc(sizeof(struct node));
	printf("Enter data \n");
	scanf("%d",&d);
	nptr->data=d;
	nptr->next=ptr;
	ptr=nptr;
	i++;
	}

	nptr=ptr;
	printf("Elements : \n");
	while(nptr!=NULL)
	{
	printf("%d ",nptr->data);
	nptr=nptr->next;
	}
	printf("\n");
}
