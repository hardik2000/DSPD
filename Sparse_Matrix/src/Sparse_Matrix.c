/*
 ============================================================================
 Name        : Priority_queue.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef enum{FAILURE,SUCCESS} status_code;
typedef enum{false,true} boolean;
#define NUM_COL 4
#define NUM_ROW 4

typedef struct SM_Node_tag
{
	int data;
	int row,col;
	struct SM_Node_tag *right;
	struct SM_Node_tag  *down;
}NODE;

typedef struct SM_Row_tag
{
	int row;
	struct SM_Node_tag *right;
	struct SM_Node_tag  *down;
}NODE_ROW;

typedef struct SM_Col_tag
{
	int col;
	struct SM_Node_tag *right;
	struct SM_Node_tag  *down;
}NODE_COL;

typedef struct SM_type
{
	struct SM_Row_tag  ROWPTR[NUM_ROW];
	struct SM_Col_tag  COLPTR[NUM_COL];

}SM_type;



void Intialise_SM_type(SM_type * smptr)
{

	for(int i=0;i<NUM_ROW;i++)
	{
		smptr->ROWPTR[i].right=NULL;
		smptr->ROWPTR[i].down=NULL;
		smptr->ROWPTR[i].row=0;
	}

	for(int i=0;i<NUM_COL;i++)
	{

		smptr->COLPTR[i].right=NULL;
		smptr->COLPTR[i].down=NULL;
		smptr->COLPTR[i].col=0;
	}
}

void Intialise_SM_Node_tag(struct SM_Node_tag *smnptr)
{
	smnptr->data=smnptr->col=smnptr->row=0;
	smnptr->right=smnptr->down=NULL;
}

NODE * CreateNode(int d,int i,int j)
{
	NODE *ptr;
	ptr=(NODE *)malloc(sizeof(NODE));
	ptr->data=d;
	ptr->row=i;
	ptr->col=j;
	ptr->right=ptr->down=NULL;
	return ptr;
}

void Traverserow(NODE *rptr)
{
	NODE *ptr;
	ptr=rptr;
	while(ptr !=NULL)
	{
		printf("%d -> ",ptr->data);
		ptr=ptr->right;
	}
	printf("NULL");
}
void Traversecol(NODE_COL *cptr)
{
	NODE *ptr;
	ptr=cptr->down;
	while(ptr !=NULL)
	{
		printf("%d -> ",ptr->data);
		ptr=ptr->down;
	}
	printf("NULL");
}
int main(void)
{
	int i,j,data;
	NODE *ptr,*temp;
	SM_type *a;
	a=(SM_type *)malloc(sizeof(SM_type));
	ptr=(NODE *)malloc(sizeof(NODE));
	temp=(NODE *)malloc(sizeof(NODE));

	Intialise_SM_Node_tag(ptr);
	Intialise_SM_Node_tag(temp);
	Intialise_SM_type(a);

	printf("ENTER THE VALUES IN THE MATRIC ROW WISE");
	for(i=0;i<NUM_ROW;i++)
	{
		for(j=0;j<NUM_COL;j++)
		{
			scanf("%d",&data);
			if(data!=0)
			{
				ptr=CreateNode(data,i,j);
				a->ROWPTR[i].row=i;
				temp=a->ROWPTR[i].right;
				if(temp==NULL)
				{
					a->ROWPTR[i].right=ptr;
				}
				else
				{
					while(temp->right!=NULL)
					{
						temp=temp->right;
					}
					temp->right=ptr;
					ptr->right=NULL;
				}
				a->COLPTR[j].col=j;
				temp=a->COLPTR[j].down;
				if(temp==NULL)
				{
					a->COLPTR[j].down=ptr;
				}
				else
				{
					while(temp->down!=NULL)
					{
						temp=temp->down;
					}
					temp->down=ptr;
					ptr->down=NULL;
				}
			}
		}
	}
	for(i=0;i<NUM_ROW;i++)
	{
			printf("THE CONTENT OF ROW NO %d IS : ",i);
			Traverserow((a->ROWPTR[i]).right);
			printf("\n");
	}

	for(j=0;j<NUM_COL;j++)
	{
			printf("THE CONTENT OF COL NO %d IS : ",j);
			Traversecol(&(a->COLPTR[j]));
			printf("\n");
	}
	return 0;
}
