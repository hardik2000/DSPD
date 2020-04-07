/*
 ============================================================================
 Name        : CPL_TREE.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef enum{index,data} TYPE;
typedef enum{false,true} boolean;

typedef struct Tree_Node_Tag
{
	int data;
	boolean mark;
	int flag;
	struct Tree_Node_Tag * left;
	struct Tree_Node_Tag * right;

}Tree_Node;

typedef struct Node
{
	Tree_Node *data;
	struct Node * next;
}node;

typedef struct queue_tag
{
	node *front,*rear;

}queue;

void Initialise(queue *qptr)
{
	qptr->front=NULL;
	qptr->rear=NULL;
}

boolean IsQueueEmpty(queue *qptr)
{
	boolean ret_val;
	if(qptr->front==NULL && qptr->rear==NULL)
	{
		ret_val=true;
	}
	else
	{
		ret_val=false;
	}

	return ret_val;
}
void insert(queue *qptr,Tree_Node *x)
{
	node *temp;
	temp=(node *)malloc(sizeof(node));
	temp->data=x;
	temp->next=NULL;
	if(temp==NULL)
	{
	}
	else
	{
		if(IsQueueEmpty(qptr))
		{
			qptr->front=qptr->rear=temp;
		}
		else
		{
			qptr->rear->next=temp;
			qptr->rear=temp;
		}
	}

}

Tree_Node * delete(queue *qptr)
{
	node * ptr;
	Tree_Node * retnode;
	if(IsQueueEmpty(qptr))
	{
		retnode=NULL;
	}
	else
	{
		ptr=qptr->front;
		retnode=(ptr->data);
		qptr->front=(qptr->front)->next;
		free(ptr);
		if(qptr->front==NULL)
		{
			qptr->rear=NULL;
		}
	}

	return retnode;
}


Tree_Node * Insert_level(Tree_Node * root,Tree_Node *node,queue *qptr)
{
	if (root == NULL)
	{
		root = node;
	}else if (qptr->front->data->left == NULL)
	{
		qptr->front->data->left = node;
	}
	else
	{
		qptr->front->data->right = node;
		delete(qptr);
	}

	insert(qptr,node);

	return root;

}
void printLevelOrder_data(Tree_Node* root)
{
	queue s;
	Initialise(&s);
	Tree_Node *temp = root;

	if(temp!=NULL)
	{
		while (temp!=NULL)
		{
			printf("%d ",temp->data);

			/*Enqueue left child */
			if (temp->left!=NULL)
			insert(&s,temp->left);

			/*Enqueue right child */
			if (temp->right!=NULL)
			insert(&s,temp->right);

			/*Dequeue node and make it temp_node*/
			temp=delete(&s);
		}
		}
	else
	{
		printf("NULL");
	}
}

void printLevelOrder_mark(Tree_Node* root)
{
	queue s;
	Initialise(&s);
	Tree_Node *temp = root;

	if(temp!=NULL)
	{
		while (temp!=NULL)
		{
			printf("%d ",temp->mark);

			/*Enqueue left child */
			if (temp->left!=NULL)
			insert(&s,temp->left);

			/*Enqueue right child */
			if (temp->right!=NULL)
			insert(&s,temp->right);

			/*Dequeue node and make it temp_node*/
			temp=delete(&s);
		}
	}
	else
	{
		printf("NULL");
	}
}




Tree_Node * Mark_Sweep(Tree_Node * root)
{
	Tree_Node *curr,*prev,*temp;
	curr=root;
	prev=NULL;
	int done=1;
	if(root!=NULL)
	{
		do
		{
			done=1;

			curr->mark=true;
			if(curr->left!=NULL)
			{
				if(curr->left->mark==false)
				{
					temp=prev;
					prev=curr;
					curr=curr->left;
					prev->left=temp;
					done=0;
					prev->flag=0;
				}
			}

			if(curr->right!=NULL && done==1)
			{
				if(curr->right->mark==false)
				{
					temp=prev;
					prev=curr;
					curr=curr->right;
					prev->right=temp;
					done=0;
					prev->flag=1;
				}
			}

			if(prev!=NULL && done==1)
			{
				if(prev->flag==0)
				{
					temp=prev->left;
					prev->left=curr;
					curr=prev;
					prev=temp;
					done=0;
				}
				else if(prev->flag==1)
				{
					temp=prev->right;
					prev->right=curr;
					curr=prev;
					prev=temp;
					done=0;
				}
			}
		}while(done==0);
	}
	else
	{
		printf("NULL");
	}
	return root;
}

int main(void)
{
	//sample input 35 20 10 5 15 25 50 45 70 65 90 -1
	int value;
	Tree_Node *root,*node;
	root=NULL;
	queue q;
	Initialise(&q);

	printf("ENTER THE VALUES SERIALLY (PRESS -1 to stop)\n");
	scanf("%d",&value);
	while(value!=-1)
	{
		node=(Tree_Node *)malloc(sizeof(Tree_Node));
		node->data=value;
		node->mark=false;
		node->flag=-1;		
		root=Insert_level(root,node,&q);

		printf("ENTER VALUES\n");
		scanf("%d",&value);
	}

	printf("\nLEVEL_ORDER TRAVERSAL BEFORE TRAVERSAL:	");
	if(root!=NULL)
	{
		printLevelOrder_data(root);
	}
	else
	{
		printf("NULL");
	}
	printf("\n");
	if(root!=NULL)
	{
		printLevelOrder_mark(root);
	}
	else
	{
		printf("NULL");
	}
	printf("\n");

	//mark sweep function
	root=Mark_Sweep(root);
	printf("\n");


	printf("\nLEVEL_ORDER TRAVERSAL AFTER TRAVERSAL:	");
	if(root!=NULL)
	{
		printLevelOrder_data(root);
	}
	else
	{
		printf("NULL");
	}
	printf("\n");
	if(root!=NULL)
	{
		printLevelOrder_mark(root);
	}
	else
	{
		printf("NULL");
	}
	printf("\n");


	return 0;
}
