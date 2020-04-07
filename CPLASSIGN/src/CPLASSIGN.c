/*
 ============================================================================
 Name        : CPLASSIGN.c
 Author      : HARDIK
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define SIZE 1597     //144
#define N 18         //13
int FIB[N];

typedef struct AllocateNodeTag
{
	char name[10];
	int index;
	int size;
	struct AllocateNodeTag * next;
}AllocNode;

typedef struct FreeNodeTag
{
	int index;
	int size;
	struct FreeNodeTag *next;
}FreeNode;

struct FREEPTRS
{
	int fib;
	FreeNode * lptr;

}FREEPTRS[N];

void  fibgen()
{
	int a,b,c;
	a=0;
	c=0;
	b=1;
	int i=0;
	FIB[0]=0;
	FIB[1]=1;
	i=2;
	while(c<SIZE)
	{
		c=a+b;
		FIB[i]=c;
		i++;
		a=b;
		b=c;
	}
}
void Initialise(struct FREEPTRS FREEPTRS[],FreeNode *ptr)
{
	int i;
	for(i=0;i<N;i++)
	{
		FREEPTRS[i].fib=FIB[i];
		FREEPTRS[i].lptr=NULL;
	}
	FREEPTRS[i-1].lptr=ptr;
}
int binarySearch(struct FREEPTRS arr[],int l, int r,int x)
{
    if (r > l)
    {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid].fib == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid].fib > x)
            return binarySearch(arr, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
    else
    {
    	return l;
    }

    // We reach here when element is not
    // present in array
}

AllocNode * MALLOC(AllocNode *headAlloc,int size,char name[])
{
	int pos=binarySearch(FREEPTRS,2,N-1,size);
	FreeNode *ptr,*temp;
	int done=0;
	AllocNode *prev,*ahead;
	if(FREEPTRS[pos].fib<size)
	{
		pos++;
	}
	do
	{
		if(FREEPTRS[pos].lptr!=NULL)
		{
			AllocNode *alloc;
			alloc=(AllocNode *)malloc(sizeof(AllocNode));
			strcpy(alloc->name,name);
			temp= FREEPTRS[pos].lptr;
			alloc->size=temp->size;
			alloc->index=temp->index;
			prev=NULL;
			ahead=headAlloc;
			if(ahead!=NULL)
			{
				while(ahead!=NULL && ahead->index<alloc->index)
				{
					prev=ahead;
					ahead=ahead->next;
				}
				if(prev==NULL)
				{
					headAlloc=alloc;
					alloc->next=ahead;
				}
				else
				{
					prev->next=alloc;
					alloc->next=ahead;
				}
			}
			else
			{
				headAlloc=alloc;
			}
			FREEPTRS[pos].lptr=temp->next;
			free(temp);
			done=1;

		}
		else
		{


			int i=pos,flag=0;
			for(;i<N && flag==0;i++)
			{
				if(FREEPTRS[i].lptr!=NULL)
				{
					flag=1;
				}
			}
			i=i-1;
			if(flag==0)
			{
				printf("Heap is full\n");
				done=1;

			}
			else
			{
				ptr=FREEPTRS[i].lptr;
				//printf("%d",FREEPTRS[i].fib);

				FreeNode *smallmalloc,*largemalloc;
				smallmalloc=(FreeNode *)malloc(sizeof(FreeNode));
				largemalloc=(FreeNode *)malloc(sizeof(FreeNode));
				smallmalloc->index=ptr->index;
				smallmalloc->size=FIB[i-2];




				smallmalloc->next=NULL;
				largemalloc->index=ptr->index+smallmalloc->size;
				largemalloc->size=FIB[i-1];
				largemalloc->next=NULL;

	//			printf("%d	%d	%d	%d",smallmalloc->index,smallmalloc->size,largemalloc->index,largemalloc->size);

				if(smallmalloc->size < size)
				{
					AllocNode *alloc;
					alloc=(AllocNode *)malloc(sizeof(AllocNode));
					strcpy(alloc->name,name);
					alloc->size=largemalloc->size;
					alloc->index=largemalloc->index;
					//add largemalloc in headAlloc and smallmalloc in freeptrs
					prev=NULL;
					ahead=headAlloc;
					if(ahead!=NULL)
					{
						while(ahead!=NULL && ahead->index<alloc->index)
						{
							prev=ahead;
							ahead=ahead->next;
						}
						if(prev==NULL)
						{
							headAlloc=alloc;
							alloc->next=ahead;
						}
						else
						{
							prev->next=alloc;
							alloc->next=ahead;
						}
					}
					else
					{
						headAlloc=alloc;
					}

					free(largemalloc);

					FreeNode *freetemp,*freetempprev;
					freetemp=FREEPTRS[i-2].lptr;
					if(freetemp!=NULL)
					{
						while(freetemp!=NULL && freetemp->index<smallmalloc->index)
						{
							freetempprev=freetemp;
							freetemp=freetemp->next;
						}
						if(freetempprev==NULL)
						{
							FREEPTRS[i-2].lptr=smallmalloc;
							smallmalloc->next=freetemp;
						}
						else
						{
							freetempprev->next=smallmalloc;
							smallmalloc->next=freetemp;
						}

					}
					else
					{
						FREEPTRS[i-2].lptr=smallmalloc;
						smallmalloc->next=NULL;
					}

				//	printf("hello");

					done=1;
				}
				else if (smallmalloc->size>=size && i-3>=0 && size>FIB[i-3])
				{
					//	allocate smallmalloc without buddy
					AllocNode *alloc;
					alloc=(AllocNode *)malloc(sizeof(AllocNode));
					strcpy(alloc->name,name);
					alloc->size=smallmalloc->size;
					alloc->index=smallmalloc->index;
					prev=NULL;
					ahead=headAlloc;
					if(ahead!=NULL)
					{
						while(ahead!=NULL && ahead->index<alloc->index)
						{
							prev=ahead;
							ahead=ahead->next;
						}
						if(prev==NULL)
						{
							headAlloc=alloc;
							alloc->next=ahead;
						}
						else
						{
							prev->next=alloc;
							alloc->next=ahead;
						}
					}
					else
					{
						headAlloc=alloc;
					}
					free(smallmalloc);

					FreeNode *freetemp,*freetempprev;
					freetemp=FREEPTRS[i-1].lptr;
					if(freetemp!=NULL)
					{
						while(freetemp!=NULL && freetemp->index<largemalloc->index)
						{
							freetempprev=freetemp;
							freetemp=freetemp->next;
						}
						if(freetempprev==NULL)
						{
							FREEPTRS[i-1].lptr=largemalloc;
							largemalloc->next=freetemp;
						}
						else
						{
							freetempprev->next=largemalloc;
							largemalloc->next=freetemp;
						}

					}
					else
					{
						FREEPTRS[i-1].lptr=largemalloc;
						largemalloc->next=NULL;
					}
					done=1;
				}
				else
				{
					//add largemalloc to free list and break smallmalloc further

					FreeNode *freetemp,*freetempprev;
					freetemp=FREEPTRS[i-2].lptr;
					if(freetemp!=NULL)
					{
						while(freetemp!=NULL && freetemp->index<smallmalloc->index)
						{
							freetempprev=freetemp;
							freetemp=freetemp->next;
						}
						if(freetempprev==NULL)
						{
							FREEPTRS[i-2].lptr=smallmalloc;
							smallmalloc->next=freetemp;
						}
						else
						{
							freetempprev->next=smallmalloc;
							smallmalloc->next=freetemp;
						}

					}
					else
					{
						FREEPTRS[i-2].lptr=smallmalloc;
						smallmalloc->next=NULL;
					}
				//	free(smallmalloc);

					freetemp=FREEPTRS[i-1].lptr;
					if(freetemp!=NULL)
					{
						while(freetemp!=NULL && freetemp->index<largemalloc->index)
						{
							freetempprev=freetemp;
							freetemp=freetemp->next;
						}
						if(freetempprev==NULL)
						{
							FREEPTRS[i-1].lptr=largemalloc;
							largemalloc->next=freetemp;
						}
						else
						{
							freetempprev->next=largemalloc;
							largemalloc->next=freetemp;
						}

					}
					else
					{
						FREEPTRS[i-1].lptr=largemalloc;
						largemalloc->next=NULL;
					}

				//	free(largemalloc);

					done=0;

				}
				FREEPTRS[i].lptr=ptr->next;
				free(ptr);


			}
		}
	}while(done==0);
		return headAlloc;
}




void check(struct FREEPTRS FREEPTRS[],AllocNode *headAlloc)
{
	int i=2;FreeNode *ptr,*alloc;
	alloc=(FreeNode *)malloc(sizeof(FreeNode));
	if(headAlloc==NULL)
	{
		while(i<N-1)
		{
			ptr=FREEPTRS[i].lptr;
			while(ptr!=NULL)
			{
				FREEPTRS[i].lptr=ptr->next;
				free(ptr);
				ptr=FREEPTRS[i].lptr;
			}

			i++;
		}
		alloc->size=FIB[i];
		alloc->index=0;
		alloc->next=NULL;
		FREEPTRS[i].lptr=alloc;
	}

}



void FREE(struct FREEPTRS FREEPTRS[],AllocNode **headAlloc,char name[])
{
	FreeNode *freeptr,*freenode,*freenodeprev;
	freeptr=(FreeNode *)malloc(sizeof(FreeNode));
	AllocNode *ptr,*prevptr;
	prevptr=NULL;
	ptr=*headAlloc;
	if(ptr==NULL)
	{
		printf("!!!!!!!!!!!!!!!!!!!EMPTY ALLOCATED LIST!!!!!!!!!!!!!!!!!!!\n");
		return;
	}
	else
	{
		while(ptr!=NULL && strcmp(ptr->name,name)!=0)
		{
			prevptr=ptr;
			ptr=ptr->next;
		}
		if(ptr==NULL)
		{
			printf("!!!!!!!!!!!!!!!!!!!NOT FOUND IN ALLOCATED LIST!!!!!!!!!!!!!!!!!!!\n");
			return;
		}
		else
		{
			//printf("FOUND");
			if(prevptr!=NULL)
			{
				printf("LOCATION WITH NAME %s IS FREED\n",name);
				prevptr->next=ptr->next;
			}
			else
			{
				printf("LOCATION WITH NAME %s IS FREED\n",name);
				*headAlloc=ptr->next;;
			}

		}

	}
	freeptr->index=ptr->index;
	freeptr->size=ptr->size;
	freeptr->next=NULL;
	int i=2,inserted=0;
	freenodeprev=NULL;
	while(i<N && inserted==0 )
	{
		if(FREEPTRS[i].fib==ptr->size)
		{
			freenode=FREEPTRS[i].lptr;
			if(freenode==NULL)
			{
				FREEPTRS[i].lptr=freeptr;
				inserted=1;
			}
			else
			{
				while(freenode!=NULL && freenode->index<ptr->index)
				{
					freenodeprev=freenode;
					freenode=freenode->next;
				}
				if(freenodeprev==NULL)
				{
					freeptr->next=freenode;
					FREEPTRS[i].lptr=freeptr;
				}
				else
				{
					freenodeprev->next=freeptr;
					freeptr->next=freenode;
				}
				inserted=1;
			}
		}
		i++;
	}
	//logic of merging


	//freenodeprev    freeptr   freenode
		//FreeNode *freenodeprevprev;
		i=i-1;
		int j,flagdone=0;
		int a,b;
		FreeNode *tfree,*tfreeprev;
		//freenodeprevprev=NULL;
	if(i==2)
	{
		int flag=0;
		freenodeprev=NULL;
		freeptr=FREEPTRS[i].lptr;
		if(freeptr!=NULL)
		{
			freenode=freeptr->next;
			while(freenode!=NULL && flag==0)
			{
				if(freeptr->index+1==freenode->index)
				{
					flag=1;
				}
				else
				{
					freenodeprev=freeptr;
					freeptr=freenode;
					freenode=freenode->next;
				}
			}
			if(flag==1)
			{
				freeptr->size=2;
				if(freenodeprev!=NULL)
				{
					freenodeprev->next=freenode->next;
				}
				else
				{
					FREEPTRS[i].lptr=freenode->next;

				}
			}


		}
		if(flag==1)
		{
			freenode=NULL;
			freenodeprev=NULL;

			freenode=FREEPTRS[i+1].lptr;
			if(freenode==NULL)
			{
				FREEPTRS[i+1].lptr=freeptr;

			}
			else
			{
				while(freenode!=NULL && freenode->index<freeptr->index)
				{
					freenodeprev=freenode;
					freenode=freenode->next;
				}
				if(freenodeprev==NULL)
				{
					FREEPTRS[i+1].lptr=freeptr;
					freeptr->next=freenode;
				}
				else
				{
					freenodeprev->next=freeptr;
					freeptr->next=freenode;
				}
			}
		}



		i++;


	}



		do
		{
			flagdone=0;
			j=i-1;
			tfree=FREEPTRS[j].lptr;
			tfreeprev=NULL;
			while(tfree!=NULL && flagdone==0 && i>=2)
			{
				a=tfree->index;
				b=freeptr->index;
				if(a+tfree->size==b || a==b+freeptr->size)
				{

					if(tfreeprev==NULL)
					{
						FREEPTRS[j].lptr=tfree->next;
						tfree->next=NULL;

					}
					else
					{
						tfreeprev->next=tfree->next;
						tfree->next=NULL;
					}
					if(freenodeprev==NULL)
					{
						FREEPTRS[i].lptr=freenode;
						freeptr->next=NULL;
					}
					else
					{
						freenodeprev->next=freenode;
						freeptr->next=NULL;
					}

					flagdone=1;

					freeptr->size+=tfree->size;
					if(a+tfree->size==b)
					{
						freeptr->index=a;
					}
					freenode=FREEPTRS[i+1].lptr;
					freenodeprev=NULL;

					while(freenode!=NULL && freenode->index<freeptr->index)
					{
						freenodeprev=freenode;
						freenode=freenode->next;
					}
					if(freenodeprev==NULL)
					{
						freeptr->next=freenode;
						FREEPTRS[i+1].lptr=freeptr;
					}
					else
					{
						freenodeprev->next=freeptr;
						freeptr->next=freenode;
					}

				}
				tfreeprev=tfree;
				tfree=tfree->next;
			}
			if(flagdone==1)
			{
				i=i+1;
			}
			else if(flagdone==0 && i<N-1)
			{
				j=i+1;
				tfree=FREEPTRS[j].lptr;
				tfreeprev=NULL;
				while(tfree!=NULL && flagdone==0)
				{
					a=tfree->index;
					b=freeptr->index;
					if(a+tfree->size==b || a==b+freeptr->size)
					{
						if(tfreeprev==NULL)
						{
							FREEPTRS[j].lptr=tfree->next;
							tfree->next=NULL;

						}
						else
						{
							tfreeprev->next=tfree->next;
							tfree->next=NULL;
						}
						if(freenodeprev==NULL)
						{
							FREEPTRS[i].lptr=freenode;
							freeptr->next=NULL;
						}
						else
						{
							freenodeprev->next=freenode;
							freeptr->next=NULL;
						}

						flagdone=1;

						freeptr->size+=tfree->size;
						if(a+tfree->size==b)
						{
							freeptr->index=a;
						}
						freenode=FREEPTRS[i+2].lptr;
						freenodeprev=NULL;

						while(freenode!=NULL && freenode->index<freeptr->index)
						{
							freenodeprev=freenode;
							freenode=freenode->next;
						}
						if(freenodeprev==NULL)
						{
							freeptr->next=freenode;
							FREEPTRS[i+2].lptr=freeptr;
						}
						else
						{
							freenodeprev->next=freeptr;
							freeptr->next=freenode;
						}

					}
					tfreeprev=tfree;
					tfree=tfree->next;
				}
				i=i+2;

			}



		//	i++;


		}while(flagdone==1 && i<N);




	check(FREEPTRS,*headAlloc);





	free(ptr);
}







void PRINTALLOC(AllocNode *head)
{
	AllocNode * ptr;
	ptr=head;
	if(ptr!=NULL)
	{
		while(ptr!=NULL)
		{
			printf("Pointer name:%s\n",ptr->name);
			printf("LocationFront:%d\n",ptr->index);
			printf("LocationEnd:%d\n",ptr->index+ptr->size-1);
			printf("Size:%d\n",ptr->size);
			ptr=ptr->next;
			printf("\n");
		}
	}else
	{
		printf("!!!!! NO ALLOCATION YET  !!!!!\n");
	}

}

void PRINTFREE(struct FREEPTRS FREEPTR[])
{
	FreeNode *free;
	int i=2;
	while(i<N)
	{
		if(FREEPTRS[i].lptr!=NULL)
		{
			free=FREEPTRS[i].lptr;
			printf("SIZE %d IS:\n",FREEPTRS[i].fib);
			while(free!=NULL)
			{
				printf("LOCATIONFRONT=%d\tLOCATIONEND=%d\tSIZE=%d\n",free->index,free->index+free->size-1,free->size);
				free=free->next;
			}
			printf("\n");
		}


		i++;
	}


}






int main()
{
	FreeNode *ptr;
	fibgen();
	ptr=(FreeNode *)malloc(sizeof(FreeNode));
	ptr->index=0;
	ptr->next=NULL;
	ptr->size=SIZE;

	Initialise(FREEPTRS,ptr);

	AllocNode *headAlloc;
	headAlloc=NULL;
	char pname[10];
	int choice,size,flag=1;
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
						printf("Name of pointer\n");
						AllocNode *ptr;
						int found =0;

						do
						{
							found=0;
							scanf("%s",pname);
							ptr=headAlloc;
							while(ptr!=NULL && found==0)
							{
								if(strcmp(ptr->name,pname)==0)
								{
									found=1;
								}
								ptr=ptr->next;
								if(found==1)
								{
									printf("!!!!!!!!!!!!!!!!!!!INVALID NAME :PLEASE ENTER A VALID NAME!!!!!!!!!!!!!!!!!!!\n");
								}
							}
						}while(found);
						do
						{
							printf("Enter the required size(ALWAYS LESS THAN %d)\n",SIZE);
							scanf("%d",&size);
						}
						while(size>SIZE && size<=0);
						headAlloc=MALLOC(headAlloc,size,pname);
						break;
				case 2:
						printf("Enter name of pointer\n");
						scanf("%s",pname);
						FREE(FREEPTRS,&headAlloc,pname);
						break;
				case 3:
						printf("THE ALLOCATED LISTS AVAILABLE ARE:\n");
						PRINTALLOC(headAlloc);
						break;
				case 4:
						printf("THE FREE LISTS AVAILABLE ARE:\n");
						PRINTFREE(FREEPTRS);
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
