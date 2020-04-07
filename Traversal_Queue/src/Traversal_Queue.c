/*
 ============================================================================
 Name        : Traversal_Queue.c
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

status_code insert(queue *qptr,Tree_Node *x)
{
	status_code retval=SUCCESS;
	node *temp;
	temp=(node *)malloc(sizeof(node));
	temp->data=x;
	temp->next=NULL;
	if(temp==NULL)
	{
		retval=FAILURE;
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

	return retval;
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

void printLevelOrder(Tree_Node* root)
{
	queue s;
	Initialise(&s);
	Tree_Node *temp = root;

	while (temp!=NULL)
	{
		printf("%d ", temp->data);

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


int main(void)
{
	int value;
	Tree_Node *root,*node;
	root=NULL;
	printf("ENTER THE VALUES SERIALLY (PRESS -1 to stop)\n");
	scanf("%d",&value);
	while(value!=-1)
	{
		node=(Tree_Node *)malloc(sizeof(Tree_Node));
		node->data=value;
		root=Insert_recursion(root,node);
		printf("ENTER VALUES\n");
		scanf("%d",&value);
	}
	printf("LEVEL BASED TRAVESRSAL OF BST IS:\n");
	printLevelOrder(root);


	return 0;
}
