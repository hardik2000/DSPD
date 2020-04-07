/*
 ============================================================================
 Name        : DSPD_ASS_TREE.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define ID_SIZE 9
#define COUNT 3

typedef struct Node
{
	struct Node *parent;
	int level;
	char IBO_id[ID_SIZE];
	int mentoring_score;
	int sale_score;
	int count_child;
	struct Node *child[COUNT];

}IBO;

IBO *CreateNode(int level,char IBO_id[])
{
	IBO *temp;
	temp=(IBO *)malloc(sizeof(IBO));
	temp->parent=NULL;
	temp->level=level;
	strcpy(temp->IBO_id,IBO_id);
	temp->mentoring_score=0;
	temp->sale_score=0;
	temp->count_child=0;
	for(int i=0;i<COUNT;i++)
	{
		temp->child[i]=NULL;
	}

	return temp;
}
IBO *Insert_IBO(IBO *parent_node)
{
	if(parent_node==NULL)
	{
		char IBO_id[ID_SIZE];
		strcpy(IBO_id,"1");
		parent_node=CreateNode(0,IBO_id);
	}
	else
	{
		if(parent_node->count_child<3)
		{
			char IBO_id[ID_SIZE];
			int i;
			for(i=0;parent_node->IBO_id[i]!='\0';i++)
			{
				IBO_id[i]=parent_node->IBO_id[i];
			}
			IBO_id[i]=(char)(parent_node->count_child+1+'0');
			IBO_id[i+1]='\0';
			printf("YOUR NEW IBO ID IS:\n");
			printf("%s\n",IBO_id);
			parent_node->child[parent_node->count_child]=CreateNode(parent_node->level+1,IBO_id);
			parent_node->child[parent_node->count_child]->parent=parent_node;
			parent_node->count_child++;
			if(parent_node->count_child==1 || parent_node->count_child==2)
			{
				parent_node->mentoring_score+=100;
			}
			else if(parent_node->count_child==3)
			{
				parent_node->mentoring_score+=200;
			}
			parent_node=parent_node->parent;
			while(parent_node!=NULL)
			{
				parent_node->mentoring_score+=10;
				parent_node=parent_node->parent;
			}
		}
		else
		{
			printf("!!!!!!!PARENT NODE FULL INSERT SOMEWHERE ELSE!!!!!!!\n");
		}
	}
	return parent_node;
}

IBO *Search_IBO(IBO *root,char IBO_id[],int level)
{
	IBO *retval;
	retval=NULL;
	if(root==NULL)
	{
		retval=NULL;
	}
	else if(!strcmp(root->IBO_id,IBO_id))
	{
		retval=root;
//		printf("%s",retval->IBO_id);
	}
	else if(root->child[(int)IBO_id[level+1]-'0'-1]!=NULL)
	{
		if(!strcmp(root->child[(int)IBO_id[level+1]-'0'-1]->IBO_id,IBO_id))
		{
			retval=root->child[(int)IBO_id[level+1]-'0'-1];
//			printf("%s",retval->IBO_id);
		}
		else
		{
			retval=Search_IBO(root->child[(int)IBO_id[level+1]-'0'-1],IBO_id,level+1);
//			printf("%s",retval->IBO_id);
		}
	}
	else
	{
		printf("!!!!!!!NO SUCH PARENT NODE FOUND!!!!!!!\n");
	}
	return retval;
}

int main(void)
{
	IBO *root,*parent_node;
	root=NULL;
	parent_node=NULL;
	char IBO_id[ID_SIZE];

	root=CreateNode(0,"1");


//	insert function in the IBO


	printf("ENTER THE PARENT ID :\n");
	scanf("%s",IBO_id);

	do
	{
		if(root!=NULL)
		{
			parent_node=Search_IBO(root,IBO_id,0);
			if(parent_node!=NULL)
			{
//				printf("%s",parent_node->IBO_id);
				Insert_IBO(parent_node);
			}
		}
		printf("ENTER THE PARENT ID :\n");
		scanf("%s",IBO_id);

	}while(strcmp(IBO_id,"-1"));






	return 0;
}