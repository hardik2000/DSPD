/*
 ============================================================================
 Name        : Tree.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define KARY 5
typedef enum{index,data} TYPE;
typedef enum{false,true} boolean;
typedef enum{FAILURE,SUCCESS} status_code;

typedef struct Tree_Node_Tag
{
	int data;
	struct Tree_Node_Tag * left;
	struct Tree_Node_Tag * right;

}Tree_Node;

typedef struct Tree_Node_B_Tag
{
	int DI[KARY-1];
	struct Tree_Node_B_Tag * Ptrs[KARY];

}B_Tree_Node;

typedef struct Tree_Node_B_Data
{
    int DI[3];
    struct Tree_Node_Data *front,*rear;
}B_Data_Node;

typedef struct Tree_Node_B_Plus_Tag
{
    TYPE type;
    union
	{
    	struct Tree_Node_Index
    	{
    		int DI[2];
    		TYPE node_type;
    		union
			{
    			struct Tree_Node_B_Tag * Ptrs[3];
    			struct Tree_Node_B_Data * ptr;
			};

    	}Index;
    	struct Tree_Node_Data
    	{
    		int DI[3];
    		struct Tree_Node_Data *front,*rear;
    	}Data;

	};


}B_Plus_Tree_Node;

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

void Visit(Tree_Node *root)
{
	printf("%d ",root->data);
}
void Pre_Order(Tree_Node *root)
{
	if(root!=NULL)
	{
		Visit(root);
		Pre_Order(root->left);
		Pre_Order(root->right);
	}
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

void Post_Order(Tree_Node *root)
{
	if(root!=NULL)
	{
		Post_Order(root->left);
		Post_Order(root->right);
		Visit(root);
	}
}

int Num_Node(Tree_Node *root)
{
	int retval=0;
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
		retval=1+Num_Node(root->left)+Num_Node(root->right);
	}
	return retval;
}

int Num_Leaves(Tree_Node *root)
{
	int retval=0;
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
		retval=Num_Leaves(root->left)+Num_Leaves(root->right);
	}
	return retval;
}


Tree_Node * Mirror(Tree_Node * root)
{
	Tree_Node *temp;
	if(root!=NULL)
	{
		if(root->left!=NULL && root->right!=NULL)
		{
			temp=root->left;
			root->left=root->right;
			root->right=temp;
			root->left=Mirror(root->left);
			root->right=Mirror(root->right);
		}

	}

	return root;
}

Tree_Node * Copy(Tree_Node * root)
{
	Tree_Node *retval;
	if(root!=NULL)
	{
		retval=(Tree_Node *)malloc(sizeof(Tree_Node));
		retval->data=root->data;
		if(root->left!=NULL && root->right!=NULL)
		{
			retval->left=Copy(root->left);
			retval->right=Copy(root->right);
		}
	}
	return retval;
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

Tree_Node * Insert_bst(Tree_Node *root,Tree_Node * node)
{
	Tree_Node * p;
	int flag=0;
	p=root;
	while(p!=NULL && flag==0)
	{
		if(node->data < p->data)
		{
			if(p->left==NULL)
			{
				p->left=node;
				flag=1;
			}
			else
			{
				p=p->left;
			}
		}
		else
		{
			if(p->right==NULL)
			{
				p->right=node;
				flag=1;
			}
			else
			{
				p=p->right;
			}
		}
	}
	if(root==NULL)
	{
		root=node;
	}
	return root;
}

Tree_Node * Insert_recursion_bst(Tree_Node * root,Tree_Node *node)
{
	if(root==NULL)
	{
		root=node;
	}
	else
	{
		if(root->data <node->data)
		{
			root->right=Insert_recursion_bst(root->right,node);
		}
		else
		{
			root->left=Insert_recursion_bst(root->left,node);
		}
	}



	return root;
}

void DeleteNode_A(Tree_Node **pp)
{
	Tree_Node *p,*q;
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
		for(q=p->left;q->right!=NULL;q=q->right)
		{

		}
		*pp=p->left;
		q->right=p->right;
		free(p);
	}

}

void DeleteNode_B(Tree_Node **pp)
{
	Tree_Node *p,*q;
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
		for(q=p->right;q->left!=NULL;q=q->left)
		{

		}
		*pp=p->right;
		q->left=p->left;
		free(p);
	}

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

void DeleteNode_D(Tree_Node **pp)
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
		r=q=p->right;
		while(q->left!=NULL)
		{
			r=q;
			q=q->left;
		}
		if(r!=q)
		{
			r->left=q->right;
			q->left=p->left;
			q->right=p->right;
			*pp=q;
			free(p);
		}
		else
		{
			q->left=p->left;
			*pp=q;
			free(p);
		}
	}


}






Tree_Node * Delete(Tree_Node *root,int k)
{
	Tree_Node *p,*prev;
	p=root;
	int done=0;
	if(root->data==k)
	{
		DeleteNode_C(&root);
	}
	else
	{
		while(!done)
		{
			if(p->data!=k && p!=NULL)
			{
				if(p->data>k)
				{
					prev=p;
					p=p->left;
				}
				else
				{
					prev=p;
					p=p->right;
				}
			}
			else
			{
				if(prev->left==p)
				{
					DeleteNode_C(&(prev->left));
					done=1;
				}
				else
				{
					DeleteNode_C(&(prev->right));
					done=1;
				}
			}
		}
	}

	return root;
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
boolean exact_copy(Tree_Node *root,Tree_Node *child_root)
{
	boolean retval=false;
	if(root!=NULL && child_root!=NULL)
	{
		if(root->data!=child_root->data)
		{
			retval=false;
		}
		else
		{
			retval=exact_copy(root->left,child_root->left);
			if(retval==true)
			{
				retval=exact_copy(root->right,child_root->right);
			}
		}
	}
	else if(root==NULL && child_root==NULL)
	{
		retval=true;
	}


	return retval;
}
boolean subtree(Tree_Node *root,Tree_Node *child_root)
{
	boolean retval=false;
	if(root!=NULL && child_root!=NULL)
	{
		if(root->data==child_root->data)
		{
			retval=exact_copy(root,child_root);
		}
		else
		{
			retval=subtree(root->left,child_root);
			if(retval==false)
			{
				retval=subtree(root->right,child_root);
			}
		}
	}
	return retval;
}

int Height(Tree_Node *root)
{
	int LH,RH,retval;
	if(root==NULL)
	{
		retval=-1;
	}
	else if(root->left==NULL && root->right==NULL)
	{
		retval=0;
	}
	else
	{
		LH=Num_Leaves(root->left);
		RH=Num_Leaves(root->right);
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





Tree_Node * Search_Recursion_level(Tree_Node *root,int k)
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
int Sum_Tree(Tree_Node *root)
{
	int sumleft=0,sumright=0,sum=0;
	if(root!=NULL)
	{
		sumleft=Sum_Tree(root->left);
		//printf("%d:left=%d\n",root->data,sumleft);
		sumright=Sum_Tree(root->right);
		//printf("%d:right=%d\n",root->data,sumright);
		if(sumleft==-1 || sumright==-1)
		{
			sum=-1;
		}
		else
		{
			if(sumleft==0 && sumright==0)
			{
				sum=root->data;
			}
			else
			{
				if(sumleft+sumright==root->data)
				{
					sum=sumleft+sumright+root->data;
				}
				else
				{
					sum=-1;
				}
			}
		}
	}
	else
	{
		sum=0;
	}
	//printf("sum=%d\n",sum);
	return sum;
}
//input 100 50 50 25 25 25 25 12 13 12 13 12 13 12 13 -1
status_code Check_Sum_Tree(Tree_Node *root)
{
	status_code retval=SUCCESS;
	int sumleft=0,sumright=0;
	if(root!=NULL)
	{
		sumleft=Sum_Tree(root->left);
		sumright=Sum_Tree(root->right);
		if(sumleft==-1 || sumright==-1)
		{
			retval=FAILURE;
		}
		else
		{
			if(sumleft+sumright==root->data)
			{
				retval=SUCCESS;
			}
			else
			{
				retval=FAILURE;
			}
		}
	}

	return retval;
}




int main(void)
{
//	int value;
//	Tree_Node *root1,*root2,*node;
//
//	//iterative insertion of binary tree
//	root1=NULL;
//	printf("ENTER THE VALUES SERIALLY (PRESS -1 to stop)\n");
//	scanf("%d",&value);
//	while(value!=-1)
//	{
//		node=(Tree_Node *)malloc(sizeof(Tree_Node));
//		node->data=value;
//		root1=Insert_bst(root1,node);
//		printf("ENTER VALUES\n");
//		scanf("%d",&value);
//	}

//
//	printf("PRE_ORDER TARVAERSAL : ");
//	Pre_Order(root);
//	printf("\n IN_ORDER TRAVERSAL : ");
//	In_Order(root1);
//	printf("\n POST_ORDER TRAVERSAL : ");
//	Post_Order(root);
//	printf("\n");



	//sample input 35 20 10 5 15 25 50 45 70 65 90 -1



	//recursively insertion of tree
//	root2=NULL;
//	printf("ENTER THE VALUES SERIALLY (PRESS -1 to stop)\n");
//	scanf("%d",&value);
//	while(value!=-1)
//	{
//		node=(Tree_Node *)malloc(sizeof(Tree_Node));
//		node->data=value;
//		root2=Insert_recursion_bst(root2,node);
//		printf("ENTER VALUES\n");
//		scanf("%d",&value);
//	}



//	printf("PRE_ORDER TARVAERSAL : ");
//	Pre_Order(root2);
//	printf("\n IN_ORDER TRAVERSAL : ");
//	In_Order(root2);
//	printf("\n POST_ORDER TRAVERSAL : ");
//	Post_Order(root2);
//	printf("\n");
//

	//delete the element

//	int key;
//	printf("ENTER THE VALUE TO BE DELETED:\n");
//	scanf("%d",&key);
//	root=Delete(root,key);
//	printf("\n IN_ORDER TRAVERSAL : ");
//	In_Order(root);


	//to check whether subtree exist or not

//	boolean ans;
//	ans=subtree(root1,root2);
//	if(ans==true)
//	{
//		printf("YES SUBTREE EXIST");
//	}
//	else
//	{
//		printf("NO SUBTREE DOESN'T EXIST");
//	}

	//to check whether exact copy or not
//
//	boolean ans;
//	ans=exact_copy(root1,root2);
//	if(ans==true)
//	{
//		printf("YES EXACT TREE EXIST");
//	}
//	else
//	{
//		printf("NO EXACT TREE DOESN'T EXIST");
//	}


	//level order tree creation
	int value;
	Tree_Node *root1,*node;
	queue q;
	Initialise(&q);
	//iterative insertion of binary tree
	root1=NULL;
	printf("ENTER VALUES\n");
	scanf("%d",&value);
	while(value!=-1)
	{
		node=(Tree_Node *)malloc(sizeof(Tree_Node));
		node->data=value;
		root1=Insert_level(root1,node,&q);
		printf("ENTER VALUES\n");
		scanf("%d",&value);

	}

	//level order traversal of tree

	printf("\n IN_ORDER TRAVERSAL : ");
	printLevelOrder(root1);
	printf("\n");




	//code to check whether a tree is a sum tree or not

	status_code sc=Check_Sum_Tree(root1);
	if(sc==SUCCESS)
	{
		printf("SUM TREE\n");
	}
	else
	{
		printf("NO SUM TREE\n");
	}





	return 0;
}
