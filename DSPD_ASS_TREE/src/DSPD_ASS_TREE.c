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
#define RATIO 10 //percentage of bonus of good sold by child nodes

typedef enum{false,true} boolean;

typedef struct IBO_Node
{
	struct IBO_Node *parent;
	char Parent_IBO_id[ID_SIZE];
	int level;
	char IBO_id[ID_SIZE];
	int mentoring_score;
	int sale_score;
	int count_child;
	struct IBO_Node *child[COUNT];

}IBO;


typedef struct QUEUE_Node
{
	IBO *data;
	struct QUEUE_Node * next;
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

IBO *CreateNode(int level,char IBO_id[])
{
	IBO *temp;
	temp=(IBO *)malloc(sizeof(IBO));
	temp->parent=NULL;
	strcpy(temp->Parent_IBO_id,IBO_id);
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
IBO *Insert_child_IBO(IBO *parent_node)
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
			strcpy(parent_node->child[parent_node->count_child]->Parent_IBO_id,parent_node->IBO_id);
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
	}
	else if((level+1)<strlen(IBO_id))
	{
		int a=0;
		a=IBO_id[level+1]-'0'-1;
		if(root->child[a]!=NULL)
		{
			retval=Search_IBO(root->child[a],IBO_id,level+1);
		}
		a=(a+1)%COUNT;
		if(retval==NULL)
		{
			if(root->child[a]!=NULL)
			{
				retval=Search_IBO(root->child[a],IBO_id,level+1);
			}
			a=(a+1)%COUNT;
			if(retval==NULL)
			{
				if(root->child[a]!=NULL)
				{
					retval=Search_IBO(root->child[a],IBO_id,level+1);
				}
			}
		}
	}

	return retval;
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

void insert(queue *qptr,IBO *x)
{
	node *temp;
	temp=(node *)malloc(sizeof(node));
	temp->data=x;
	temp->next=NULL;
	if(temp==NULL)
	{
		printf("!!!!!!!INSERTION FAILED!!!!!!!");
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

IBO * delete(queue *qptr)
{
	node * ptr;
	IBO * retnode;
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
void printLevelOrder(IBO* root)
{
	queue s;
	Initialise(&s);
	IBO *temp = root;
	int level=0;
	while (temp!=NULL)
	{
		if(temp->level!=level)
		{
			printf("\n");
			level=temp->level;
		}
		printf("%s--%d	",temp->IBO_id,temp->level);

		for(int i=0;i<COUNT;i++)
		{
			if(temp->child[i]!=NULL)
			{
				insert(&s,temp->child[i]);
			}
		}
		/*Dequeue node and make it temp_node*/
		temp=delete(&s);
	}
}

void printDetailLevelOrder(IBO *root)
{
	queue s;
	Initialise(&s);
	IBO *temp = root;
	int level=0;
	while (temp!=NULL)
	{
		if(temp->level!=level)
		{
			printf("\n");
			level=temp->level;
		}
		printf("%s--%d--%d--%d\t",temp->IBO_id,temp->level,temp->mentoring_score,temp->sale_score);

		for(int i=0;i<COUNT;i++)
		{
			if(temp->child[i]!=NULL)
			{
				insert(&s,temp->child[i]);
			}
		}
		/*Dequeue node and make it temp_node*/
		temp=delete(&s);
	}

}

void Heightest_Scorer_level_wise(IBO *root)
{
	queue s;
	Initialise(&s);
	IBO *temp = root;
	int level=0;
	int max_score=0;
	IBO *max_scorer=NULL;

	while (temp!=NULL)
	{
		if(temp->level!=level)
		{
			printf("MAX SCORER OF THE LEVEL %d IS IBO ID %s WITH SCORE :%d",level,max_scorer->IBO_id,max_score);
			printf("\n");
			level=temp->level;
			max_score=0;
			max_scorer=NULL;
			if(temp->mentoring_score+temp->sale_score>=max_score)
			{
				max_score=temp->mentoring_score+temp->sale_score;
				max_scorer=temp;
			}
		}
		else
		{
			if(temp->mentoring_score+temp->sale_score>=max_score)
			{
				max_score=temp->mentoring_score+temp->sale_score;
				max_scorer=temp;
			}
		}

		for(int i=0;i<COUNT;i++)
		{
			if(temp->child[i]!=NULL)
			{
				insert(&s,temp->child[i]);
			}
		}
		/*Dequeue node and make it temp_node*/
		temp=delete(&s);
	}
	if(max_scorer!=NULL)
	{
		printf("MAX SCORER OF THE LEVEL %d IS IBO ID %s WITH SCORE :%d",level,max_scorer->IBO_id,max_score);
		printf("\n");
	}
	else
	{
		printf("!!!!!!!NO MAX SCORER FOUND!!!!!!!");
	}

}

int Max_Descendants(IBO *root)
{
	int LH,CH,RH,retval;
	if(root==NULL)
	{
		retval=0;
	}
	else if(root->count_child==0)
	{
		retval=0;
	}
	else
	{
		LH=Max_Descendants(root->child[0]);
		CH=Max_Descendants(root->child[1]);
		RH=Max_Descendants(root->child[2]);
		if(LH>RH)
		{
			if(LH>CH)
			{
				retval=1+LH;
			}
			else
			{
				retval=1+CH;
			}
		}
		else
		{
			if(RH>CH)
			{
				retval=1+RH;
			}
			else
			{
				retval=1+CH;
			}
		}

	}
	return retval;
}

void Max_Descendant_level_wise(IBO *root)
{
	queue s;
	Initialise(&s);
	IBO *temp = root;
	int level=0;
	int max_score=0;
	IBO *max_scorer=NULL;
	int count_temp=0;
	while (temp!=NULL)
	{
		if(temp->level!=level)
		{
			printf("MAX DESCENDANT AT THE LEVEL %d IS OF  IBO  ID %s I.E. :%d",level,max_scorer->IBO_id,max_score);
			printf("\n");
			level=temp->level;
			max_score=0;
			max_scorer=NULL;
			count_temp=Max_Descendants(temp);
			if(count_temp>=max_score)
			{
				max_score=count_temp;
				max_scorer=temp;
			}
		}
		else
		{
			count_temp=Max_Descendants(temp);
			if(count_temp>=max_score)
			{
				max_score=count_temp;
				max_scorer=temp;
			}
		}

		for(int i=0;i<COUNT;i++)
		{
			if(temp->child[i]!=NULL)
			{
				insert(&s,temp->child[i]);
			}
		}
		/*Dequeue node and make it temp_node*/
		temp=delete(&s);
	}
	if(max_scorer!=NULL)
	{
		printf("MAX DESCENDANT AT THE LEVEL %d IS OF  IBO  ID %s I.E. :%d",level,max_scorer->IBO_id,max_score);
		printf("\n");
	}
	else
	{
		printf("!!!!!!!NO MAX DESCENDANT FOUND!!!!!!!");
	}

}

void More_Points_Then_Mentor(IBO *root)
{
	queue s;
	Initialise(&s);
	IBO *temp = root;
	int parent_score=0,child_score=0;
	int flag=0;
	while (temp!=NULL)
	{
		parent_score=temp->mentoring_score+temp->sale_score;
		for(int i=0;i<COUNT;i++)
		{
			if(temp->child[i]!=NULL)
			{
				child_score=temp->child[i]->mentoring_score+temp->child[i]->sale_score;
				if(child_score>parent_score)
				{
					printf("CHILD IBO HAVING IB : %s HAS SCORE MORE THAN THE PARENT IBO : %s \n",temp->child[i]->IBO_id,temp->IBO_id);
					flag=1;
				}
			}
		}

		for(int i=0;i<COUNT;i++)
		{
			if(temp->child[i]!=NULL)
			{
				insert(&s,temp->child[i]);
			}
		}
		/*Dequeue node and make it temp_node*/
		temp=delete(&s);
	}
	if(flag==0)
	{
		printf("!!!!!!!NO CHILD HAS MAX SCORE THAN HIS PARENT!!!!!!!\n");
	}

}
void Write_Details(IBO *root);
IBO * Read_Details();
IBO *Insert_IBO(IBO *root,IBO *node,int level);
IBO *Sale_Record(IBO *root);
IBO * Delete_IBO(IBO *root,IBO *parent_node,IBO *child_node);

int main(void)
{
	IBO *root,*parent_node;
	root=NULL;
	parent_node=NULL;
	char IBO_id[ID_SIZE];

//	read details in file
	root=Read_Details();
	if(root==NULL)
	{
		root=CreateNode(0,"1");
	}
	int ch=0;
	do
	{
		if(root==NULL)
		{
				root=CreateNode(0,"1");
		}
		printf("ENTER THE CODE TO PERFORM THE FOLLOWING OPERATIONS :\n");
		printf("1:)FOR INSERTING A NEW IBO IN THE DATABASE :\n");
		printf("2:)DISPLAY THE NAMES OF HEIGHEST SCORER AT EACH LEVEL :\n");
		printf("3:)DISPLAY THE NAMES OF IBO WITH MAXIMUM DESCENDANTS AT EACH LEVEL :\n");
		printf("4:)DISPLAY THE NAMES OF IBO WHO HAVE MORE POINTS THAN MENTOR :\n");
		printf("5:)DELETE THE INSERTED IBO :\n");
		printf("6:)PRINT LEVEL ORDER DETAILS OF ALL IBO:\n");
		printf("7:)ENTER SALE RECORDS:\n");
		printf("ENTER -1 TO QUIT\n");
		scanf("%d",&ch);

		if(ch!=-1)
		{
			switch(ch)
			{
				case 1:
						{
							//	insert function in the IBO
							printf("ENTER THE PARENT ID :\n");
							scanf("%s",IBO_id);
							if(root!=NULL)
							{
								parent_node=Search_IBO(root,IBO_id,0);
								if(parent_node!=NULL)
								{
									Insert_child_IBO(parent_node);
								}
								else
								{
									printf("!!!!!!!NO SUCH PARENT NODE FOUND!!!!!!!\n");
								}
							}

							break;
						}
				case 2:
						{
							//	max_scorer_level_wise
							Heightest_Scorer_level_wise(root);
							break;
						}
				case 3:
						{
							//	max descendant level wise
							Max_Descendant_level_wise(root);
							break;
						}
				case 4:
						{
							// 	child having more score than parent
							More_Points_Then_Mentor(root);
							break;
						}
				case 5:
						{
							char IBO_id[ID_SIZE];
							printf("ENTER THE ID OF THE IBO TO BE DELETED:\n");
							scanf("%s",IBO_id);
							IBO *child_node=Search_IBO(root,IBO_id,0);
							if(child_node!=NULL)
							{
								IBO *parent_node=child_node->parent;
								root=Delete_IBO(root,parent_node,child_node);
								printf("!NODE WITH GIVEN ID DELETED SUCCESSFULY!\n");
							}
							else
							{
								printf("!!!!!!!NO NODE WITH GIVEN ID FOUND!!!!!!!\n");
							}
							break;
						}
				case 6:
						{
							printf("\nLEVEL BASED TRAVESRSAL OF TREE IS(ID--LEVEL--MENTOR_SCORE--SALE_SCORE):\n");
							printDetailLevelOrder(root);
							printf("\n");
							break;
						}
				case 7:
						{
							root=Sale_Record(root);
							break;
						}

				default:
						{
							printf("!!!!!!!!INVALID INPUT ENTER AGAIN!!!!!!!!\n");
							ch=0;
							break;
						}

			}
		}
		printf("\n");
	}while(ch!=-1);


//	write details in file
	Write_Details(root);

	return 0;
}

IBO * Delete_IBO(IBO *root,IBO *parent_node,IBO *child_node)
{
	if(parent_node!=NULL)
	{
		parent_node->mentoring_score+=child_node->mentoring_score;
		parent_node->sale_score+=child_node->sale_score;
	}
	parent_node=child_node;
	child_node=child_node->child[0];
	while(child_node!=NULL)
	{
		strcpy(parent_node->IBO_id,child_node->IBO_id);
		parent_node->mentoring_score=child_node->mentoring_score;
		parent_node->sale_score=child_node->sale_score;

		parent_node=child_node;
		child_node=child_node->child[0];

	}
	child_node=parent_node;
	parent_node=parent_node->parent;
	int i=0;
	if(parent_node!=NULL)
	{
		parent_node->count_child--;
		if(parent_node->child[0]==child_node)
		{
			i=1;
		}
		else if(parent_node->child[1]==child_node)
		{
			i=2;
		}
		else if(parent_node->child[2]==child_node)
		{
			i=3;
		}

		for(;i<COUNT;i++)
		{
			parent_node->child[i-1]=parent_node->child[i];
		}
		parent_node->child[2]=NULL;
	}
	if(child_node==root)
	{
		root=NULL;
	}
	free(child_node);

	return root;
}


IBO *Sale_Record(IBO *root)
{
	char IBO_id[ID_SIZE];
	char input[2];
	int value[]={10,20,30,40,50},cat,val;
	IBO *curr_ibo,*parent_node;
	do
	{
		printf("ENTER THE IBO ID TO ENTER SALE RECORD \n");
		scanf("%s",IBO_id);
		curr_ibo=Search_IBO(root,IBO_id,0);
		int sale=0;
		if(curr_ibo!=NULL)
		{
			char ans[2];
			do
			{
				printf("ENTER THE CATEGORY OF GOOD's:\n");
				do
				{
					scanf("%d",&cat);
					if(cat>5 || cat<=0)
					{
						printf("!!!!!!!!!!PRODUCT OUT OF CATEGORY!!!!!!!!!!\n");
					}
				}while(cat>5 || cat<=0);
				printf("ENTER THE QUANTITY OF GOOD's ( 0 to 5 ):\n");
				do
				{
					scanf("%d",&val);
				}while(val>5 || val<0);
				val=val*value[cat-1];
				curr_ibo->sale_score+=val;
				sale+=val;


				printf("DO YOU WANT TO PURCHASE MORE GOOD FROM THIS IBO (Y/N) ????\n");
				scanf("%s",ans);
			}while(!strcmp(ans,"Y") || !strcmp(ans,"y"));
			parent_node=curr_ibo->parent;
			while(parent_node!=NULL && sale!=0)
			{
				sale=(RATIO*sale)/100;
				parent_node->sale_score+=sale;
				parent_node=parent_node->parent;
			}
		}
		else
		{
			printf("IBO WITH THIS ID %s DOES NOT EXIST :\n",IBO_id);
		}

		printf("DO YOU WANT TO CONTINUE(Y/N)????\n");
		scanf("%s",input);
	}while(!strcmp(input,"Y") || !strcmp(input,"y"));

	return root;
}


IBO *Insert_IBO(IBO *root,IBO *node,int level)
{
	if(root==NULL)
	{
		root=node;
	}
	else
	{
		if(!strcmp(root->IBO_id,node->Parent_IBO_id))
		{
			root->child[node->IBO_id[level+1]-'0'-1]=node;
			root->count_child++;
			node->parent=root;
		}
		else
		{
			root->child[node->IBO_id[level+1]-'0'-1]=Insert_IBO(root->child[node->IBO_id[level+1]-'0'-1],node,level+1);

		}
	}
	return root;
}

IBO* Read_Details()
{
	IBO *root;
	root=NULL;
	FILE *fptr = fopen("record.txt", "r");
	if (fptr == NULL)
	{
		printf("NO SUCH FILE EXIST :");
	}
	else
	{
		IBO *temp;
		temp=NULL;
		temp=(IBO *)malloc(sizeof(IBO));
		if(fscanf(fptr,"%s%d%s%d%d",temp->Parent_IBO_id,&temp->level,temp->IBO_id,&temp->mentoring_score,&temp->sale_score)!=EOF)
		{
			root=temp;
			temp=(IBO *)malloc(sizeof(IBO));
			while(fscanf(fptr,"%s%d%s%d%d",temp->Parent_IBO_id,&temp->level,temp->IBO_id,&temp->mentoring_score,&temp->sale_score) !=EOF)
			{
				if(temp!=NULL)
				{
	//				fprintf(stdout,"%s\n",temp->Parent_IBO_id);
	//				fprintf(stdout,"%d\n",temp->level);
	//				fprintf(stdout,"%s\n",temp->IBO_id);
	//				fprintf(stdout,"%d\n",temp->mentoring_score);
	//				fprintf(stdout,"%d\n",temp->sale_score);

				//	insert node in the tree
					root=Insert_IBO(root,temp,0);

				}
				temp=(IBO *)malloc(sizeof(IBO));
			}
		}
	}
	fclose(fptr);

	return root;
}


void Write_Details(IBO *root)
{
	queue s;
	Initialise(&s);
	FILE *fptr = fopen("record.txt", "w");
	if (fptr == NULL)
	{
		printf("Could not open file");
	}
	else
	{
		IBO *temp = root;
		while (temp!=NULL)
		{
			fprintf(fptr,"%s\n",temp->Parent_IBO_id);
			fprintf(fptr,"%d\n",temp->level);
			fprintf(fptr,"%s\n",temp->IBO_id);
			fprintf(fptr,"%d\n",temp->mentoring_score);
			fprintf(fptr,"%d\n",temp->sale_score);

			for(int i=0;i<COUNT;i++)
			{
				if(temp->child[i]!=NULL)
				{
					insert(&s,temp->child[i]);
				}
			}
			/*Dequeue node and make it temp_node*/
			temp=delete(&s);
		}
	}

	fclose(fptr);
}
