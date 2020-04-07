/*
 ============================================================================
 Name        : String_count_level.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true} boolean;
typedef enum{FAILURE,SUCCESS}status_code;

typedef struct Tree_Node_Tag
{
	char data;
	int count;
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





Tree_Node * Search_Recursion(Tree_Node *root,char k)
{
	Tree_Node *retval;
	retval=NULL;
	if(root==NULL)
	{
		retval=NULL;
	}
	else
	{
		if(root->data==k)
		{
			retval=root;
		}
		else
		{
			retval=Search_Recursion(root->left,k);
			if(retval==NULL)
			{
				retval=Search_Recursion(root->right,k);
			}
		}

	}
	return retval;
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
void printLevelOrder(Tree_Node* root)
{
	queue s;
	Initialise(&s);
	Tree_Node *temp = root;

	while (temp!=NULL)
	{
		printf("%c%d ", temp->data,temp->count);

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
	char value;
	Tree_Node *root1,*node;
	queue q;
	Initialise(&q);
	//iterative insertion of binary tree
	root1=NULL;
	int i=0;
	char input[20];
	scanf("%s",input);
	value=input[i];
	while(value!='\0')
	{
		node=Search_Recursion(root1,value);
		if(node==NULL)
		{
			node=(Tree_Node *)malloc(sizeof(Tree_Node));
			node->data=value;
			node->count=1;
			root1=Insert_level(root1,node,&q);
		}
		else
		{
			node->count++;
		}
		i++;
		value=input[i];
	}
	printf("\n IN_ORDER TRAVERSAL : ");
	printLevelOrder(root1);
	printf("\n");

	//sample input xzxaxbcddc






	return 0;
}



