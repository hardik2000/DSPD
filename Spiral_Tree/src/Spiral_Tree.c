/*
 ============================================================================
 Name        : Spiral_Tree.c
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


typedef struct Tree_Node_Tag
{
	int data;
	struct Tree_Node_Tag * left;
	struct Tree_Node_Tag * right;

}Tree_Node;


typedef struct Node
{
	Tree_Node *data;
	struct Node * next;
}node;

typedef struct stack_tag
{
	node * top;
}stack;
void Initialise(stack *sptr)
{
	sptr->top=NULL;
}
struct Node * CreateNode(Tree_Node *data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
status_code push(stack *sptr,Tree_Node *x)
{
	status_code retval=SUCCESS;
	node * nptr=CreateNode(x);

	if(nptr==NULL)
	{
		retval=FAILURE;
		printf("STACK OVERFLOW\n");
	}
	else
	{
		nptr->next=sptr->top;
		sptr->top=nptr;
	}
	return retval;
}
status_code IsEmpty(stack *sptr)
{
	status_code sc=FAILURE;
	if(sptr->top==NULL)
	{
		sc=SUCCESS;
	}

	return sc;
}

Tree_Node * pop(stack * sptr)
{
	Tree_Node *retnode;
	node * ptr;
	if(IsEmpty(sptr))
	{
		retnode=NULL;
	}
	else
	{
		ptr=sptr->top;
		retnode=(ptr->data);
		sptr->top=(sptr->top)->next;
		free(ptr);
	}
	return retnode;
}

Tree_Node * Insert_recursion(Tree_Node * root,Tree_Node *node)
{
	if(root==NULL)
	{
		root=node;
	}
	else
	{
		if(root->data <node->data)
		{
			root->right=Insert_recursion(root->right,node);
		}
		else
		{
			root->left=Insert_recursion(root->left,node);
		}
	}

	return root;
}

void printSpiralOrder(Tree_Node* root)
{
	stack sptr1,sptr2;
	status_code sc;
	Initialise(&sptr1);
	Initialise(&sptr2);
	Tree_Node *temp;
	temp= root;
	int flag=1;
	while (temp!=NULL)
	{
		printf("%d ", temp->data);

		if(flag==0)
		{
			/*Enqueue left child */
			if (temp->left!=NULL)
			{
				push(&sptr2,temp->left);
			}


			/*Enqueue right child */
			if (temp->right!=NULL)
			{
				push(&sptr2,temp->right);
			}

			temp=pop(&sptr1);
			if(temp!=NULL)
			{

			}
			else
			{
					temp=pop(&sptr2);
					if(temp!=NULL)
					{
						if(flag==0)
						{
							flag=1;
						}
						else if(flag==1)
						{
							flag=0;
						}
					}
					else
					{
						temp=NULL;
					}
			}



		}
		else if(flag==1)
		{
			/*Enqueue left child */
			if (temp->right!=NULL)
				push(&sptr1,temp->right);

			/*Enqueue right child */
			if (temp->left!=NULL)
				push(&sptr1,temp->left);

			temp=pop(&sptr2);
			if(temp!=NULL)
			{

			}
			else
			{
				/*Dequeue node and make it temp_node*/
					temp=pop(&sptr1);
					if(temp!=NULL)
					{
						if(flag==0)
						{
							flag=1;
						}
						else if(flag==1)
						{
							flag=0;
						}
					}
					else
					{
						temp=NULL;
					}

			}

		}
	}
}


int main(void)
{
	int value;
	Tree_Node *root,*node;
	root=NULL;

//sample input 10 8 12 6 7 11 13 -1
//
//	printf("ENTER THE VALUES SERIALLY (PRESS -1 to stop)\n");
//	scanf("%d",&value);
//	while(value!=-1)
//	{
//		node=(Tree_Node *)malloc(sizeof(Tree_Node));
//		node->data=value;
//		node->left=NULL;
//		node->right=NULL;
//		root=Insert_recursion(root,node);
//		printf("ENTER VALUES\n");
//		scanf("%d",&value);
//	}



	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=10;
	node->left=NULL;
	node->right=NULL;
						root=node;
	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=20;
	node->left=NULL;
	node->right=NULL;
						root->left=node;
	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=30;
	node->left=NULL;
	node->right=NULL;
						root->right=node;
	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=40;
	node->left=NULL;
	node->right=NULL;
						root->left->left=node;
	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=60;
	node->left=NULL;
	node->right=NULL;
						root->left->right=node;
	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=50;
	node->left=NULL;
	node->right=NULL;
						root->left->right->left=node;
	node=(Tree_Node *)malloc(sizeof(Tree_Node));
	node->data=85;
	node->left=NULL;
	node->right=NULL;

						root->left->right->right=node;



	printf("LEVEL BASED TRAVESRSAL OF BST IS:\n");
	printSpiralOrder(root);
	//In_Order(root);

	return 0;
}
