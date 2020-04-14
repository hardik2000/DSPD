/*
 ============================================================================
 Name        : B_TREE.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define KARY 5
#define MIN_CHILD 2

typedef struct Tree_Node_B_Tag
{
	int count_value;
	int count_child;
	int DI[KARY-1];
	struct Tree_Node_B_Tag * Ptrs[KARY];

}B_Tree;

B_Tree *Initialise(B_Tree *node)
{
	node->count_value=0;
	node->count_child=0;
	for(int i=0;i<KARY-1;i++)
	{
		node->DI[i]=0;
	}
	for(int i=0;i<KARY;i++)
	{
		node->Ptrs[i]=0;
	}

	return node;
}



int main(void)
{








	return 0;
}
