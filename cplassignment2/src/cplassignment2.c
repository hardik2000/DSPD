/*
 ============================================================================
 Name        : cplassignment2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define D 4
# define N 1000
typedef struct AllocateNodeTag
{
	char name[10];
	int location;
	int size;
	int words;
	struct AllocateNodeTag * next;
}AllocateNode;

typedef struct FreeNodeTag
{
	int location;
	int size;
	struct FreeNodeTag *next;
}FreeNode;

void MALLOC(AllocateNode **headAlloc,FreeNode **headFree,int size,char pname[])
{
	FreeNode *fptr,*mptr,*fprev;
	AllocateNode *aptr,*ptr_new,*prev;
	FreeNode *ptrbuddy;
	int msize;
	fptr = *(headFree);

	if(fptr!=NULL)
	{
		while(fptr->next!=NULL)
		{
			fptr=fptr->next;
		}
	}

	msize=(fptr)->size;
	printf("%d",msize);
	aptr=*headAlloc;
	fptr=*headFree;
	FreeNode *mptrprev;
	mptrprev=NULL;
	int flag=0;
	int wsize;
	fptr=*headFree;
	fprev=NULL;
	while((aptr!=NULL)&&(strcmp(pname,aptr->name)!=0))
	{
		aptr=aptr->next;
	}
	if(aptr==NULL)
	{
		aptr=*headAlloc;
		if(size%D==0)
		{
			wsize=size/D;
		}
		else
		{
			wsize=(int)(size/D)+1;
		}
		mptrprev=NULL;
		mptr=fptr;
		while((fptr!=NULL)&&(flag==0))
		{
			if(fptr->size==wsize)
			{
				mptrprev=fprev;
				mptr=fptr;
				flag=1;
			}
			else if(((fptr->size)<=msize)&&(fptr->size>=wsize))
			{
				mptrprev=fprev;
				mptr=fptr;
				msize=fptr->size;
			}
			fprev=fptr;
			fptr=fptr->next;
		}
		if(msize>=wsize)
		{
			ptr_new=(AllocateNode*)malloc(sizeof(AllocateNode));
			ptrbuddy=(FreeNode*)malloc(sizeof(FreeNode));
			ptrbuddy->size=0;
			strcpy(ptr_new->name,pname);
			ptr_new->size=size;
			ptr_new->words=wsize;
			ptr_new->location=mptr->location;
			ptr_new->next=NULL;
			aptr=*headAlloc;
			if(mptr->next==NULL)
			{
				ptrbuddy->size=wsize;
				ptrbuddy->location=mptr->location+wsize;
				ptrbuddy->next=NULL;
			}

			if(aptr==NULL)
			{
				*headAlloc=ptr_new;
			}
			else
			{
				prev=NULL;
				while((aptr!=NULL)&&(aptr->location<mptr->location))
				{
					prev=aptr;
					aptr=aptr->next;
				}
				if(prev==NULL)
				{
					*headAlloc=ptr_new;
					ptr_new->next=aptr;
				}
				else
				{
					prev->next=ptr_new;
					ptr_new->next=aptr;
				}
			}
			if(mptr->size==wsize)
			{
				if(mptr==(*headFree))
				{
					*headFree=mptr->next;
					free(mptr);
				}
				else
				{

					fprev->next=mptr->next;
					free(mptr);
				}
			}
			else
			{
				if(mptrprev!=NULL && ptrbuddy->size!=0)
				{
					mptrprev->next=ptrbuddy;
					ptrbuddy->next=mptr;
					//mptr->next=NULL;
				}
				else if(mptrprev==NULL &&ptrbuddy->size!=0)
				{
					*headFree=ptrbuddy;
					ptrbuddy->next=mptr;
					mptr->next=NULL;
				}
				mptr->size-=2*wsize;
				mptr->location+=2*wsize;
			}
			printf("Memory of size %d is allocated at location %d\n",ptr_new->size,ptr_new->location);
		}
		else
			printf("Heap is full\n");
	}
	else
	{
		printf("\nError:Pointer name already in use\n");
	}
}

void FREE(AllocateNode **headAlloc,FreeNode **headFree,char pname[])
{
	AllocateNode *aptr,*aprev;
	aptr=*headAlloc;
	FreeNode *fptr,*ptr_new,*fprev;
	fptr=*headFree;
	fprev=NULL;
	ptr_new=(FreeNode*)malloc(sizeof(FreeNode));
	while((aptr!=NULL)&&(strcmp(aptr->name,pname)!=0))
	{
		aprev=aptr;
		aptr=aptr->next;
	}
	if(aptr!=NULL)
	{
		ptr_new->location=aptr->location;
		ptr_new->size=aptr->words;
		ptr_new->next=NULL;
		while((fptr!=NULL)&&(fptr->location<ptr_new->location))
		{
			fprev=fptr;
			fptr=fptr->next;
		}
		if(fprev==NULL)
		{
			ptr_new->next=*headFree;
			*headFree=ptr_new;
		}
		else
		{
			fprev->next=ptr_new;
			ptr_new->next=fptr;
		}
		//Compaction
		int flag=0;
		while(flag==0)
		{
			flag=1;
			if((fprev!=NULL)&&((fprev->location+fprev->size)==ptr_new->location))
			{

				fprev->size+=ptr_new->size;
				fprev->next=fptr;
				free(ptr_new);
				ptr_new=fprev;
				flag=0;

				ptr_new=fprev->next;
			}
			if((fptr!=NULL)&&((ptr_new->location+ptr_new->size)==fptr->location))
			{
				ptr_new->size+=fptr->size;
				ptr_new->next=fptr->next;
				if(fptr->next==NULL)
					ptr_new->next=NULL;
				free(fptr);
				flag=0;
				//ptr_new=ptr_new->next;
				fptr=ptr_new->next;
			}


		}
		if(aptr==*headAlloc)
		{
			*headAlloc=aptr->next;
			free(aptr);
		}
		else
		{
			aprev->next=aptr->next;
			free(aptr);
		}
		printf("Location is freed\n");


	}
	else
	{
		printf("Not found\n");
	}
}
void PRINTALLOC(AllocateNode *head)
{
	AllocateNode * ptr;
	ptr=head;
	if(ptr!=NULL)
	{
		while(ptr!=NULL)
		{
			printf("Pointer name:%s\n",ptr->name);
			printf("Location:%d\n",ptr->location);
			printf("Size:%d\n",ptr->size);
			printf("Words used%d\n\n",ptr->words);
			ptr=ptr->next;
		}
	}else
	{
		printf("!!!!! NO ALLOCATION YET  !!!!!");
	}

}

void PRINTFREE(FreeNode *head)
{
	FreeNode * ptr;
	ptr=head;
	while(ptr!=NULL)
	{
		printf("Location:%d\n",ptr->location);
		printf("Size:%d\n",ptr->size*D);
		printf("Number of words:%d\n\n",ptr->size);
		ptr=ptr->next;
	}
}



int main(void)
{
	AllocateNode *headAlloc;
	headAlloc=NULL;
	FreeNode *headFree;
	headFree=(FreeNode*)malloc(sizeof(FreeNode));
	headFree->location=0;
	headFree->size=N;
	headFree->next=NULL;
	char pname[10];
	int choice,ch,size,flag=1;
	do
	{
		printf("*************************** CHOOSE ANY OPTION TO CONTINUE ***************************\n");
		printf("1.MALLOC\n");
		printf("2.FREE\n");
		printf("3.PRINT ALLOCATED LIST\n");
		printf("4.PRINT FREE LIST\n");
		printf("5.QUIT\n");
		printf("***************************\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("1.Integer\n");
				printf("2.Character\n");
				printf("3.Float\n");
				printf("4.Data type of specific size\n");
				scanf("%d",&ch);
				switch(ch)
				{
					case 1:
						printf("Name of pointer\n");
						scanf("%s",pname);
						size=4;
						break;
					case 2:
						printf("Name of pointer\n");
						scanf("%s",pname);
						size=1;
						break;
					case 3:
						printf("Name of pointer\n");
						scanf("%s",pname);
						size=8;
						break;
					case 4:
						printf("Name of pointer\n");
						scanf("%s",pname);
						printf("Enter the required size\n");
						scanf("%d",&size);
						break;
					default:
						printf("Enter valid option\n");
						break;
				}
				MALLOC(&headAlloc,&headFree,size,pname);
				break;
			case 2:
				printf("Enter name of pointer\n");
				scanf("%s",pname);
				FREE(&headAlloc,&headFree,pname);
				break;
			case 3:
				PRINTALLOC(headAlloc);
				break;
			case 4:
				PRINTFREE(headFree);
				break;
			case 5:
				flag=0;
				break;
			default:
				printf("!!!!!!  INVALID ENTRY ENTER AGAIN:  !!!!!!\n");
				flag=1;
		}
	}while(flag==1);


	return 0;
}
