//============================================================================
// Name        : Segment_Trees.cpp
// Author      : Hardik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
typedef struct treenode
{
	int data;
	int l,r;
	struct treenode *left;
	struct treenode *right;

}treenode;
treenode* initialise()
{
	treenode* retval;
	retval=(treenode*)malloc(sizeof(treenode));
	retval->data=0;
	retval->l=0;
	retval->r=0;
	retval->left=NULL;
	retval->right=NULL;
	return retval;
}

treenode* fun(int *arr,int l,int r)
{
	treenode* rettree;
	rettree=initialise();
	if(l==r)
	{
		rettree->data=arr[l];
		rettree->l=l;
		rettree->r=r;
		rettree->left=NULL;
		rettree->right==NULL;
	}
	else
	{
		int mid=(l+r)/2;
		rettree->left=fun(arr,l,mid);
		rettree->right=fun(arr,mid+1,r);
		rettree->data=rettree->left->data+rettree->right->data;
		rettree->l=l;
		rettree->r=r;
	}
	return rettree;
}
int sol(treenode* node,int l,int r)
{
	int sum=0;
	if(node->l>=l && node->r<=r)
	{
		return node->data;
	}
	else if(node->r<l || node->l>r)
	{
		sum=0;
	}
	else
	{
		sum=sol(node->left,l,r);
		sum+=sol(node->right,l,r);
	}
	return sum;
}
void Visit(treenode *root)
{
	printf("data=%d l=%d r=%d\n",root->data,root->l,root->r);
}
void Pre_Order(treenode *root)
{
	if(root!=NULL)
	{
		Visit(root);
		Pre_Order(root->left);
		Pre_Order(root->right);
	}
}
int main()
{
	int *arr;
	int size;
	cout<<"ENTER THE SIZE\n";
	cin>>size;
	arr=(int*)malloc(sizeof(int)*size);
	cout<<"ENTER THE NOS\n";
	for(int i=0;i<size;i++)
	{
		cin>>arr[i];
	}
	int l=0,r=0;
	treenode *node=fun(arr,0,size-1);
	//Pre_Order(node);
	do
	{
		cout<<"ENTER QUERIES\n";
		cin>>l>>r;
		if(l!=-1 && r!=-1)
		{
			cout<<sol(node,l,r)<<"\n";
		}
	}while(l!=-1);


	return 0;
}
