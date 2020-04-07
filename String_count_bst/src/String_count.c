/*
 ============================================================================
 Name        : String_count.c
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
	char data;
	int count;
	struct Tree_Node_Tag * left;
	struct Tree_Node_Tag * right;

}Tree_Node;


void Visit(Tree_Node *root)
{
	printf("%c%d ",root->data,root->count);
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
			if(k < root->data)
			{
				retval=Search_Recursion(root->left,k);
			}
			else
			{
				retval=Search_Recursion(root->right,k);
			}
		}

	}
	return retval;
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



int main(void)
{
	char value;
	Tree_Node *root1,*node;

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
			root1=Insert_recursion(root1,node);
		}
		else
		{
			node->count++;
		}
		i++;
		value=input[i];
	}
	printf("\n IN_ORDER TRAVERSAL : ");
	In_Order(root1);
	printf("\n");

	//sample input xzxaxbcddc






	return 0;
}
