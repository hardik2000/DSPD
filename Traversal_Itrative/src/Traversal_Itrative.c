/*
 ============================================================================
 Name        : Traversal_Itrative.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

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

void PrintLevel(Tree_Node * root, int level)
{
	if (root == NULL)
	{
		return;
	}
	else if (level == 1)
	{
		printf("%d ", root->data);
	}
	else if (level > 1)
	{
		PrintLevel(root->left, level-1);
		PrintLevel(root->right, level-1);
	}
}

void PrintOrder(Tree_Node * root)
{
	int h = Height(root);
	int i;
	for (i=1; i<=h; i++)
	{
		PrintLevel(root, i);
	}
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


int main()
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

	printf("LEVEL ORDER TRAVERSAL OF BINARY TREE IS \n");
	PrintOrder(root);

	return 0;
}
