/*
 ============================================================================
 Name        : AVL_TREE.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true} boolean;
typedef enum{FAILURE,SUCCESS} status_code;

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



void Visit(Tree_Node *root)
{
	printf("%d ",root->data);
}

void In_Order(Tree_Node *root)
{
	if(root!=NULL)
	{
		In_Order(root->left);
		Visit(root);
		In_Order(root->right);
	}
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

Tree_Node * Search_Recursion(Tree_Node *root,int k)
{
	Tree_Node *retval;
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
		else if(root->data < k)
		{
			retval=Search_Recursion(root->left,k);
		}
		else
		{
			retval=Search_Recursion(root->right,k);
		}

	}
	return retval;
}

Tree_Node * Search_Iteration(Tree_Node *root,int k)
{
	Tree_Node *retval;
	while(root!=NULL && root->data!=k)
	{

		if(root->data < k)
		{
			root=root->left;
		}
		else
		{
			root=root->right;
		}
	}
	retval=root;
	return retval;
}


Tree_Node * Rotate_Left(Tree_Node *root)
{
	Tree_Node *q;
	if(root!=NULL && root->right!=NULL)
	{
		q=root->right;
		root->right=q->left;
		q->left=root;
	}

	return q;
}

Tree_Node * Rotate_Right(Tree_Node *root)
{
	Tree_Node *q;
	if(root!=NULL && root->left!=NULL)
	{
		q=root->left;
		root->left=q->right;
		q->right=root;
	}

	return q;
}

int Height(Tree_Node *root)
{
	int LH,RH,retval;
	if(root==NULL)
	{
		retval=0;
	}
	else if(root->left==NULL && root->right==NULL)
	{
		retval=1;
	}
	else
	{
		LH=Height(root->left);
		RH=Height(root->right);
		if(LH>RH)
		{
			retval=1+LH;
		}
		else
		{
			retval=1+RH;
		}

	}
	return retval;
}
typedef enum{left,right}rotate;
Tree_Node * Balance(Tree_Node * root,rotate side)
{
	if(root!=NULL)
	{
		if(side==left)
		{
			root=Rotate_Left(root);
		}
		else if(side==right)
		{
			root=Rotate_Right(root);
		}
	}
	return root;
}

Tree_Node * Insert_recursion_bst(Tree_Node * root,Tree_Node *node)
{
	int insert=0;
	if(root==NULL)
	{
		root=node;
	}
	else
	{
		if(root->data <node->data)
		{
			root->right=Insert_recursion_bst(root->right,node);
			insert=1;
		}
		else
		{
			root->left=Insert_recursion_bst(root->left,node);
			insert=-1;
		}
		if(insert==-1)
		{
			int heightleft=0,heightright=0,balance_child=0,balance=0;
			heightleft=Height(root->left->left);
			heightright=Height(root->left->right);
			balance_child=heightright-heightleft;
			heightleft=Height(root->left);
			heightright=Height(root->right);
			balance=heightright-heightleft;
			if(balance==-2 && balance_child==-1)
			{
				root=Balance(root,right);
			}
			else if(balance==-2 && balance_child==1)
			{
				root->left=Balance(root->left,left);
				root=Balance(root,right);
			}
		}
		else if(insert==1)
		{
			int heightleft=0,heightright=0,balance_child=0,balance=0;
			heightleft=Height(root->right->left);
			heightright=Height(root->right->right);
			balance_child=heightright-heightleft;
			heightleft=Height(root->left);
			heightright=Height(root->right);
			balance=heightright-heightleft;
			if(balance==2 && balance_child==1)
			{
				root=Balance(root,left);
			}
			else if(balance==2 && balance_child==-1)
			{
				root->right=Balance(root->right,right);
				root=Balance(root,left);
			}
		}

	}

	return root;
}

void DeleteNode_C(Tree_Node **pp)
{
	Tree_Node *p,*q,*r;
	p=*pp;
	if(*pp==NULL)
	{
		printf("NOT POSSIBLE TO DELETE THIS NODE:\n");
	}
	else if(p->right==NULL)
	{
		*pp=p->left;
	}
	else if(p->left==NULL)
	{
		*pp=p->right;
	}
	else
	{
		r=q=p->left;
		while(q->right!=NULL)
		{
			r=q;
			q=q->right;
		}
		if(r!=q)
		{
			r->right=q->left;
			q->right=p->right;
			q->left=p->left;
			*pp=q;
			free(p);
		}
		else
		{
			q->right=p->right;
			*pp=q;
			free(p);
		}
	}

}


Tree_Node * Delete(Tree_Node *root,Tree_Node *prev,int k)
{
	int insert=0;
	if(root!=NULL)
	{
		if(prev==NULL)
		{
			if(root->data==k)
			{
				DeleteNode_C(&root);
				if(root!=NULL)
				{
					int heightleft=0,heightright=0,balance_child=0,balance=0;
					if(root->left!=NULL)
					{
						heightleft=Height(root->left->left);
						heightright=Height(root->left->right);
						balance_child=heightright-heightleft;
					}
					else
					{
						balance_child=0;
					}
					heightleft=Height(root->left);
					heightright=Height(root->right);
					balance=heightright-heightleft;
					if(balance==-2 && balance_child<=0)
					{
						root=Balance(root,right);
					}
					else if(balance==-2 && balance_child==1)
					{
						root->left=Balance(root->left,left);
						root=Balance(root,right);
					}
					if(root->right!=NULL)
					{
						heightleft=Height(root->right->left);
						heightright=Height(root->right->right);
						balance_child=heightright-heightleft;
					}
					else
					{
						balance_child=0;
					}
					heightleft=Height(root->left);
					heightright=Height(root->right);
					balance=heightright-heightleft;
					if(balance==2 && balance_child>=0)
					{
						root=Balance(root,left);
					}
					else if(balance==2 && balance_child==-1)
					{
						root->right=Balance(root->right,right);
						root=Balance(root,left);
					}
				}
				return root;
			}
		}
			if(root->data==k)
			{
				if(prev->left==root)
				{
					DeleteNode_C(&(prev->left));
					root=prev->left;
				}
				else
				{
					DeleteNode_C(&(prev->right));
					root=prev->right;
				}
			}
			else
			{
				if(root->data>k)
				{
					root->left=Delete(root->left,root,k);
					insert=-1;
				}
				else if(root->data<k)
				{
					root->right=Delete(root->right,root,k);
					insert=1;
				}
				if(insert==1)
				{
					int heightleft=0,heightright=0,balance_child=0,balance=0;
					if(root->left!=NULL)
					{
						heightleft=Height(root->left->left);
						heightright=Height(root->left->right);
						balance_child=heightright-heightleft;
					}
					else
					{
						balance_child=0;
					}
					heightleft=Height(root->left);
					heightright=Height(root->right);
					balance=heightright-heightleft;
					if(balance==-2 && balance_child<=0)
					{
						root=Balance(root,right);
					}
					else if(balance==-2 && balance_child==1)
					{
						root->left=Balance(root->left,left);
						root=Balance(root,right);
					}
				}
				else if(insert==-1)
				{
					int heightleft=0,heightright=0,balance_child=0,balance=0;
					if(root->right!=NULL)
					{
						heightleft=Height(root->right->left);
						heightright=Height(root->right->right);
						balance_child=heightright-heightleft;
					}
					else
					{
						balance_child=0;
					}
					heightleft=Height(root->left);
					heightright=Height(root->right);
					balance=heightright-heightleft;
					if(balance==2 && balance_child>=0)
					{
						root=Balance(root,left);
					}
					else if(balance==2 && balance_child==-1)
					{
						root->right=Balance(root->right,right);
						root=Balance(root,left);
					}
				}

			}
	}
	else
	{
		printf("VALUE DOESNT EXIST:");
	}
	return root;
}

int main(void)
{
	int value=0;
	Tree_Node *root2,*node;


	//sample input 35 20 10 5 15 25 50 45 70 65 90 -1

	//	10 20 15 25 30 16 18 19 -1

	//recursively insertion of tree
	root2=NULL;
	printf("ENTER THE VALUES SERIALLY (PRESS -1 to stop)\n");
	scanf("%d",&value);
	while(value!=-1)
	{
		node=(Tree_Node *)malloc(sizeof(Tree_Node));
		node->data=value;
		root2=Insert_recursion_bst(root2,node);

		printf("ENTER VALUES\n");
		scanf("%d",&value);

	}


	printf("\n IN_ORDER TRAVERSAL : ");
	In_Order(root2);
	printf("\n");

	printf("\n LEVEL_ORDER TRAVERSAL : ");
	printLevelOrder(root2);
	printf("\n");



	//delete the element 10 20 15 25 30 16 18 19 -1

	int key;
	printf("ENTER THE VALUE TO BE DELETED:\n");
	scanf("%d",&key);
	while(key!=-1)
	{
		root2=Delete(root2,NULL,key);



		printf("\n IN_ORDER TRAVERSAL : ");
		In_Order(root2);
		printf("\n");

		printf("\n LEVEL_ORDER TRAVERSAL : ");
		printLevelOrder(root2);
		printf("\n");

		printf("ENTER VALUES\n");
		scanf("%d",&key);

	}



	printf("\n IN_ORDER TRAVERSAL : ");
	In_Order(root2);
	printf("\n");

	printf("\n LEVEL_ORDER TRAVERSAL : ");
	printLevelOrder(root2);
	printf("\n");


	return 0;
}
