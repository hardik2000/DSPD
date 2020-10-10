/*
 ============================================================================
 Name        : DSPD_ASS_GRAPH.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define INT_MAX 1000000				//maximum distance (in a way infinity)
#define Weight_Max 1000000			//maximum weight allowed
typedef enum{false,true}Boolean;
typedef enum{FAILURE,SUCCESS}status_code;
typedef int vertex;
typedef int item_type;

typedef struct edge_tag
{
	vertex dest;
	int weight;
	struct edge_tag* nextEdge;
}Edge;

typedef struct node_tag
{
	vertex node;
	Edge* edgelist;
	struct node_tag* down;
}Node;

typedef struct Graph
{
	Node* nodes;
}Graph;

void Initialise_graph(Graph* g)
{
	g->nodes=NULL;
}

Node* find(int node_name,Graph *g);

void insert_node(int node_name ,Graph* g)
{
	Node *tmp;
	tmp=(Node*)malloc(sizeof(Node));
	tmp->node=node_name;
	tmp->down=NULL;
	tmp->edgelist=NULL;
	tmp->down=g->nodes;
	g->nodes=tmp;
	return ;
}

void delete_node(int node_name,Graph* g)
{
	Node *tmp,*q;
	int flg=0;
	if(g->nodes->node==node_name)
	{
		tmp=g->nodes;
		g->nodes=g->nodes->down;
		flg=1;
	}
	q=g->nodes;
	while(q->down->down!=NULL && flg==0)
	{
		if(q->down->node==node_name)
		{
			tmp=q->down;
			q->down=tmp->down;
			flg=1;
		}
		q=q->down;
	}
	if(q->down->node==node_name && flg==0)
	{
		tmp=q->down;
		q->down=NULL;
	}
	free(tmp);
	//deleting all node_edges
	Node* temp;
	temp=g->nodes;
	while(temp!=NULL)
	{
		Edge *curr,*prev;
		curr=temp->edgelist;
		prev=NULL;
		int found=0;
		while(curr!=NULL && found==0)
		{
			if(curr->dest==node_name)
			{
				if(prev==NULL)
				{
					temp->edgelist=curr->nextEdge;
					free(curr);
					found=1;
				}
				else
				{
					prev->nextEdge=curr->nextEdge;
					free(curr);
					found=1;
				}
			}
			else
			{
				prev=curr;
				curr=curr->nextEdge;
			}
		}
		temp=temp->down;
	}
	return ;
}

Boolean insert_edge(int u,int v,int weight,Graph *g)
{
	Boolean retval=true;
	Node *locu,*locv;
	Edge *ptr,*tmp;
	locu=find(u,g);
	locv=find(v,g);
	if(locu==NULL)
	{
		printf("SOURCE NODE DOES NOT EXIST ! FIRST INSERT NODE %d \n",u);
		retval=false;
	}
	else if(locv==NULL)
	{
		printf("SOURCE NODE DOES NOT EXIST ! FIRST INSERT NODE %d \n",v);
		retval=false;
	}
	else
	{
		tmp=(Edge*)malloc(sizeof(Edge));
		tmp->dest=v;
		tmp->nextEdge=NULL;
		tmp->weight=weight;

		ptr=locu->edgelist;
		if(locu->edgelist==NULL)
		{
			locu->edgelist=tmp;
		}
		else
		{
			while(ptr->nextEdge!=NULL)
			{
				ptr=ptr->nextEdge;
			}
			ptr->nextEdge=tmp;
		}
	}
	return retval;
}

Node* find(int node,Graph *g)
{
	Node *ptr,*loc;
	loc=NULL;
	ptr=g->nodes;
	int found=0;
	while(ptr!=NULL && found==0)
	{
		if(node==ptr->node)
		{
			loc=ptr;
			found=1;
		}
		ptr=ptr->down;
	}
	return loc;
}

void delete_edge(int u,int v,Graph* g)
{
	Node *locu;
	Edge *curr,*prev;
	locu=find(u,g);

	if(locu==NULL )
	{
		printf("SOURCE NODE NOT FOUND ! CREATE THE SOURCE NODE FIRST \n");
		return;
	}
	curr=locu->edgelist;
	prev=NULL;
	int found=0;
	while(curr!=NULL && found==0)
	{
		if(curr->dest==v)
		{
			if(prev==NULL)
			{
				locu->edgelist=curr->nextEdge;
			}
			else
			{
				prev->nextEdge=curr->nextEdge;
			}
			found=1;
			free(curr);
		}
		else
		{
			prev=curr;
			curr=curr->nextEdge;
		}
	}
	if(found==0)
		printf("THIS EDGE IS NOT PRESENT IN THE GRAPH \n");
	else
		printf("EDGE FROM %d TO %d DELETED SUCCESSFULLY \n",u,v);
}

void display(Graph *g)
{
	Node *ptr;
	Edge *q;

	ptr=g->nodes;
	while(ptr!=NULL)
	{
		printf("%d ->",ptr->node);
		q=ptr->edgelist;
		while(q!=NULL)
		{
			printf(" %d(%d)->",q->dest,q->weight);
			q=q->nextEdge;
		}
		printf("\n");
		ptr=ptr->down;
	 }
}

typedef struct Node
{
	item_type data;
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
Boolean IsQueueEmpty(queue *qptr)
{
	Boolean ret_val;
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
struct Node * CreateNode(item_type data)
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}
status_code insert(queue *qptr,int x)
{
	status_code retval=SUCCESS;
	node * nptr=CreateNode(x);
	if(nptr==NULL)
	{
		retval=FAILURE;
	}
	else
	{
		if(IsQueueEmpty(qptr))
		{
			qptr->front=qptr->rear=nptr;
		}
		else
		{
			qptr->rear->next=nptr;
			qptr->rear=nptr;
		}
	}

	return retval;
}

status_code delete(int *x,queue *qptr)
{
	status_code retval=SUCCESS;
	node * ptr;
	if(IsQueueEmpty(qptr))
	{
		retval=FAILURE;
	}
	else
	{
		ptr=qptr->front;
		*x=ptr->data;
		qptr->front=(qptr->front)->next;
		free(ptr);
		if(qptr->front==NULL)
		{
			qptr->rear=NULL;
		}
	}

	return retval;
}

int size(Graph *g)
{
	Node *ptr;
	ptr=g->nodes;
	int retval=0;
	while(ptr!=NULL)
	{
		if(ptr->node>retval)
			retval=ptr->node;
		ptr=ptr->down;
	}

	return retval;
}

void visit(vertex v)
{
	printf("%d ",v);
}

status_code Traverse(Graph* g ,vertex v,Boolean *visited,int MAX,int key)
{
	status_code retval=FAILURE;
	visited[v]=true;
	Node *temp;
	Edge *ptr;
	temp=find(v,g);
	if(temp!=NULL)
	{
		if(key!=-1)
		{
			if(v==key)
				retval=SUCCESS;
		}
		else
		{
			visit(v);
		}
		if(retval==FAILURE)
		{
			ptr=temp->edgelist;
			while(ptr!=NULL && retval==FAILURE)
			{
				if(!visited[ptr->dest])
				{
					retval=Traverse(g,ptr->dest,visited,MAX,key);
				}
				ptr=ptr->nextEdge;
			}
		}

	}
	return retval;
}


status_code DFS(Graph* g,Boolean *visited,int MAX,int key)
{
	status_code sc=FAILURE;
	for(vertex i=0;i<=MAX && sc==FAILURE;i++)
	{
		if(!visited[i])
		{
			sc=Traverse(g,i,visited,MAX,key);
		}
	}
	return sc;
}

status_code BFS(Graph* g,Boolean* visited,int MAX,int key)
{
	status_code retval=FAILURE;
	queue s;
	Initialise(&s);
	for(vertex i=0;i<=MAX && retval==FAILURE;i++)
	{
		if(!visited[i])
		{
			insert(&s,i);
			do
			{
				delete(&i,&s);
				Node *ptr=find(i,g);
				if(!visited[i] && ptr!=NULL)
				{
					visited[i]=true;
					if(key!=-1)
					{
						if(i==key)
							retval=SUCCESS;
					}
					else
					{
						visit(i);
					}
					if(retval==FAILURE)
					{
						Edge* temp=ptr->edgelist;
						while(temp!=NULL)
						{
							if(!visited[temp->dest])
							{
								insert(&s,temp->dest);
							}
							temp=temp->nextEdge;
						}
					}
				}
				else
				{
					visited[i]=true;
				}

			}while(!IsQueueEmpty(&s) && retval==FAILURE);

		}
	}
	return retval;
}

Boolean is_cycle_exist(Graph *g,Boolean *visited,int MAX)
{
	Boolean retval=false;
	queue s;
	Initialise(&s);
	status_code sc;
	for(vertex i=0;i<=MAX && !retval;i++)
	{
		for(int i=0;i<=MAX;i++)
		{
			visited[i]=false;
		}
		sc=insert(&s,i);
		do
		{
			int x;
			sc=delete(&x,&s);
			Node *ptr=find(x,g);
			if(!visited[x] && ptr!=NULL)
			{
				visited[x]=true;
				Edge* temp=ptr->edgelist;
				while(temp!=NULL)
				{
					sc=insert(&s,temp->dest);
					temp=temp->nextEdge;
				}
			}
			else if(visited[x]==false)
			{
				visited[x]=true;
			}
			else if(x==i && ptr!=NULL)
			{
				retval=true;
			}

		}while(!IsQueueEmpty(&s) && !retval);

	}

	return retval;
}

void TOPOSORT(Graph* g,Boolean *visited,int MAX)
{
	int *pred,*exist;
	pred=(int*)malloc(sizeof(int)*(MAX+1));
	exist=(int*)malloc(sizeof(int)*(MAX+1));

	for(int i=0;i<=MAX;i++)
	{
		pred[i]=0;
		exist[i]=0;
	}
	Node  *ptr;
	ptr=NULL;
	ptr=g->nodes;
	while(ptr!=NULL)
	{
		exist[ptr->node]=1;
		Edge* temp=ptr->edgelist;
		while(temp!=NULL)
		{
			pred[temp->dest]++;
			temp=temp->nextEdge;
		}
		ptr=ptr->down;
	}
	int flg=0,flg1=0;
	do
	{
		flg=0;flg1=0;
		int i=0;
		for(i=0;i<=MAX && flg==0;i++)
		{
			if(pred[i]==0 && !visited[i] && exist[i]==1)
			{
				flg=1;
			}
		}
		i--;
		if(flg==1)
		{
			visit(i);
			visited[i]=true;
			Edge* temp=find(i,g)->edgelist;
			while(temp!=NULL)
			{
				pred[temp->dest]--;
				temp=temp->nextEdge;
			}
		}
		for(int j=0;j<=MAX && flg1==0;j++)
		{
			if(!visited[j] && exist[j]==1)
				flg1=1;
		}
	}while(flg1==1 && flg==1);
	if(flg==0 && flg1==1)
	{
		printf("!!!!! NO RESULT EXIST !!!!!\n");
	}
}

void Dijsktra(Graph *g,int u,Boolean *visited,int MAX)
{
	int *Dist,*Prev;
	Dist=(int*)malloc(sizeof(int)*(MAX+1));
	Prev=(int*)malloc(sizeof(int)*(MAX+1));
	vertex v;
	int i;
	Node *ptr,*temp;
	ptr=find(u,g);
	if(ptr==NULL)
	{
		printf("SOURCE NODE  DOES NOT EXIST:\n");
		return ;
	}
	Edge *tmp;
	tmp=ptr->edgelist;
	for(i=0;i<=MAX;i++)
	{
		visited[i]=true;
		Dist[i]=INT_MAX;
		Prev[i]=u;
	}
	Dist[ptr->node]=0;
	while(tmp!=NULL)
	{
		Dist[tmp->dest]=tmp->weight;
		tmp=tmp->nextEdge;
	}
	temp=g->nodes;
	while(temp!=NULL)
	{
		visited[temp->node]=false;
		temp=temp->down;
	}
	visited[u]=true;
	int flg=0;
	for(i=0;i<=MAX && flg==0;i++)
	{
		v=-1;
		int min=INT_MAX;
		for(vertex w=0;w<=MAX;w++)
		{
			if(visited[w]==false)
			{
				if(Dist[w]<min)
				{
					min=Dist[w];
					v=w;
				}
			}

		}
		if(v==-1)
		{
			flg=1;
		}
		else
		{
			visited[v]=true;
			for(vertex w=0;w<=MAX;w++)
			{
				if(visited[w]==false)
				{
					Edge *t=find(v,g)->edgelist;
					int found=0,cost=INT_MAX;
					while(t!=NULL && found==0)
					{
						if(t->dest==w)
						{
							cost=t->weight;
							found=1;
						}
						t=t->nextEdge;
					}
					if(Dist[v]+cost<Dist[w])
					{
						Dist[w]=Dist[v]+cost;
						Prev[w]=v;
					}
				}
			}
		}

	}
	for(int i=0;i<=MAX;i++)
	{
		if(Dist[i]!=INT_MAX)
		{
			printf("(%d,%d)>>>%d\t\t",u,i,Dist[i]);
			int key=i;
			printf("%d<--",key);
			while(Prev[key]!=u)
			{
				printf("%d<--",Prev[key]);
				key=Prev[key];
			}
			printf("%d\n",u);
		}
		else
		{
			printf("NO SUCH PATH EXIST FROM NODE %d TO %d \n",u,i);
		}
	}
}

Boolean check_strongly_connected(Graph *g,Boolean *visited,int MAX)
{
	Boolean retans=true;

	for(int i=0;i<=MAX;i++)
	{
		visited[i]=true;
	}

	Node *ptr;
	ptr=g->nodes;
	while(ptr!=NULL)
	{
		visited[ptr->node]=false;
		ptr=ptr->down;
	}
	queue s;
	Initialise(&s);
	int i=g->nodes->node;
	if(!visited[i])
	{
		insert(&s,i);
		do
		{
			delete(&i,&s);
			Node *ptr=find(i,g);
			if(!visited[i] && ptr!=NULL)
			{
				visited[i]=true;
				Edge* temp=ptr->edgelist;
				while(temp!=NULL)
				{
					if(!visited[temp->dest])
					{
						insert(&s,temp->dest);
					}
					temp=temp->nextEdge;
				}
			}
			else
			{
				visited[i]=true;
			}
		}while(!IsQueueEmpty(&s));
	}
	for(int i=0;i<=MAX && retans;i++)
	{
		if(visited[i]==false)
		{
			retans=false;
		}
	}
	if(retans)
	{
		printf("GRAPH IS STRONGLY CONNECTED \n");
	}
	else
	{
		printf("GRAPH IS NOT STRONGLY CONNECTED \n");
	}
	return retans;
}

Boolean check_weekly_connected(Graph *g,Boolean *visited,int MAX)
{
	Boolean retans=true;
	Graph *g_temp;
	g_temp=(Graph*)malloc(sizeof(Graph));
	Initialise_graph(g_temp);

	for(int i=0;i<=MAX;i++)
	{
		visited[i]=true;
	}

	Node *ptr;
	ptr=g->nodes;
	while(ptr!=NULL)
	{
		insert_node(ptr->node,g_temp);
		ptr=ptr->down;
	}
	ptr=g->nodes;
	while(ptr!=NULL)
	{
		visited[ptr->node]=false;
		Edge *tmp=ptr->edgelist;
		while(tmp!=NULL)
		{
			insert_edge(ptr->node,tmp->dest,tmp->weight,g_temp);
			insert_edge(tmp->dest,ptr->node,tmp->weight,g_temp);
			tmp=tmp->nextEdge;
		}
		ptr=ptr->down;
	}
	queue s;
	Initialise(&s);
	int i=g_temp->nodes->node;
	if(!visited[i])
	{
		insert(&s,i);
		do
		{
			delete(&i,&s);
			Node *ptr=find(i,g_temp);
			if(!visited[i] && ptr!=NULL)
			{
				visited[i]=true;
				Edge* temp=ptr->edgelist;
				while(temp!=NULL)
				{
					if(!visited[temp->dest])
					{
						insert(&s,temp->dest);
					}
					temp=temp->nextEdge;
				}
			}
			else
			{
				visited[i]=true;
			}
		}while(!IsQueueEmpty(&s));
	}
	for(int i=0;i<=MAX && retans;i++)
	{
		if(visited[i]==false)
		{
			retans=false;
		}
	}
	if(retans)
	{
		printf("GRAPH IS WEEKLY CONNECTED \n");
	}
	else
	{
		printf("GRAPH IS NOT WEEKLY CONNECTED \n");
	}
	return retans;
}

void printpath(int i,int j,int** path)
{
	if(path[i][j]==i)
	{
		printf("%d->",path[i][j]);
	}
	else
	{
		printpath(i,path[i][j],path);
		printpath(path[i][j],j,path);
	}
}

void APSP(int **cost,int **Dist,Graph *g,int MAX)
{
	int **path;
	path=(int**)malloc(sizeof(int*)*(MAX+1));
	int i,j,k;
	for(i=0;i<=MAX;i++)
	{
		path[i]=(int*)malloc(sizeof(int)*(MAX+1));
		for(j=0;j<=MAX;j++)
		{
			if(i!=j)
			{
				Dist[i][j]=cost[i][j];
			}
			else
			{
				Dist[i][j]=0;
			}
			path[i][j]=i;
		}
	}//till this we have calculated A^-1[i][j]
	printf("\n");
	for(k=0;k<=MAX;k++)
	{
		for(i=0;i<=MAX;i++)
		{
			for(j=0;j<=MAX;j++)
			{
				if(Dist[i][j]>(Dist[i][k]+Dist[k][j]))
				{
					Dist[i][j]=Dist[i][k]+Dist[k][j];
					path[i][j]=k;
				}

			}
		}
	}
	for(i=0;i<=MAX;i++)
	{
		for(j=0;j<=MAX;j++)
		{
			if(Dist[i][j]!=INT_MAX)
			{
				printf("(%d,%d)>>>%d\t\t",i,j,Dist[i][j]);
				printpath(i,j,path);
				printf("%d",j);
				printf("\n");
			}
		}
		printf("\n");
	}

}

Graph *Prims_mst(Graph *g,Boolean *visited,int MAX)
{
	Graph *g_temp;
	g_temp=(Graph*)malloc(sizeof(Graph));
	Initialise_graph(g_temp);
	int count_node=0,count_edge=0;
	Node *ptr;
	Edge *tmp;
	ptr=g->nodes;
	int min=MAX;
	while(ptr!=NULL)
	{
		insert_node(ptr->node,g_temp);
		count_node++;
		if(ptr->node<min)
		{
			min=ptr->node;
		}
		ptr=ptr->down;
	}
	int weight=0;
	int flg=0;
	int u,v,temp_weight;
	visited[min]=true;
	while(count_edge<(count_node-1) && flg==0)
	{
		int found=0;
		temp_weight=Weight_Max;
		ptr=find(min,g);
		tmp=ptr->edgelist;
		while(tmp!=NULL)
		{
			if(visited[tmp->dest]==false)
			{
				if(tmp->weight < temp_weight)
				{
					temp_weight=tmp->weight;
					u=min;
					v=tmp->dest;
					found=1;
				}
			}
			tmp=tmp->nextEdge;
		}
		if(found==0)
		{
			flg=1;
		}
		else
		{
			insert_edge(u,v,temp_weight,g_temp);
			weight+=temp_weight;
			count_edge++;
			visited[v]=true;
			min=v;
		}
	}
	if(count_edge==(count_node-1))
	{
		printf("Minimum spanning tree cost is %d \n",weight);
		display(g_temp);
	}
	else
	{
		printf("No Spanning tree exist\n");
	}
	return g_temp;
}

void PrintPath(Graph *g,int u, int d,Boolean *visited,int *path, int path_index)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    if (u == d)
    {
    	int i;
        for (i = 0; i<path_index-1; i++)
        {
        	printf("%d--",path[i]);
        }
        printf("%d",path[i]);
        printf("\n");
    }
    else
    {
    	Edge *tmp=find(u,g)->edgelist;;
        while(tmp!=NULL)
    	{
        	if (!visited[tmp->dest])
        	{
        		PrintPath(g , tmp->dest , d, visited, path, path_index);
        	}
        	tmp=tmp->nextEdge;
    	}
    }
    path_index--;
    visited[u] = false;
}


void PrintAllPaths(int s, int d,Graph *g,int MAX)
{
    Boolean *visited;
    visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
    int *path;
    path=(int*)malloc(sizeof(int)*(MAX+1));

    int path_index = 0;
    for (int i = 0; i <=MAX; i++)
        visited[i] = false;

    PrintPath(g , s , d, visited, path, path_index);
    printf("These are the only path that exist between %d to %d\n",s,d);
}


int main(void)
{
	Graph *g;
	g=(Graph*)malloc(sizeof(Graph));
	Initialise_graph(g);
	int choice;
	int node,origin,destin;
	int flg=0;
	do
	{
		printf("1.Insert a node\n");
		printf("2.Insert an edge\n");
		printf("3.Delete a node\n");
		printf("4.Delete an edge\n");
		printf("5.Print via Depth first,Breadth First and Topological sort\n");
		printf("6.Display Adjacency List\n");
		printf("7.Check Cycle\n");
		printf("8.Check whether graph is connected or not\n");
		printf("9.Shortest path between fix node and all other nodes\n");
		printf("10.Shortest path between all node and all other nodes\n");
		printf("11.Search element via BFS and DFS \n");
		printf("12.Calculate and Display the minimum spanning subtree\n");
		printf("13.Print all possible path between a pair of nodes\n");
		printf("14.Quit\n");

		printf("Enter your choice : \n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				{
					printf("Enter a node to be inserted : \n");
					scanf("%d",&node);
					insert_node(node,g);
					printf("NODE %d INSERTED SUCCESSFULLY \n",node);
					break;
				}
			case 2:
				{
					char str[2];
					int weight=0;
					printf("You want an undirected(U)/directed(D) edge : \n");
					scanf("%s",str);
					printf("You want a weighted(enter weight)/unweighted(enter 0) edge: \n");
					scanf("%d",&weight);
					printf("Enter an edge to be inserted(vertex1,vertex2) : \n");
					scanf("%d %d",&origin,&destin);
					if(!strcmp(str,"U") || !strcmp(str,"u"))
					{
						if(insert_edge(origin,destin,weight,g))
						{
							printf("NODE INSERTED FROM %d TO %d WITH WEIGHT %d \n",origin,destin,weight);
						}
						if(insert_edge(destin,origin,weight,g))
						{
							printf("NODE INSERTED FROM %d TO %d WITH WEIGHT %d \n",destin,origin,weight);
						}
					}
					else
					{
						if(insert_edge(origin,destin,weight,g))
						{
							printf("NODE INSERTED FROM %d TO %d WITH WEIGHT %d \n",destin,origin,weight);
						}
					}
					break;
				}
			case 3:
				{
					printf("Enter a node to be deleted : \n");
					scanf("%d",&node);
					Node *ptr=find(node,g);
					if(ptr!=NULL)
					{
						delete_node(node,g);
					}
					printf("NODE %d DELETED \n",node);
					break;
				}
			case 4:
				{
					printf("Enter an edge to be deleted : \n");
					scanf("%d %d",&origin,&destin);
					delete_edge(origin,destin,g);
					break;
				}
			case 5:
				{
					int MAX=size(g);
					Boolean *visited;
					visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					printf("DEPTH FIRST SEARCH RESULT WILL BE :\n");
					DFS(g,visited,MAX,-1);
					printf("\n");

					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					printf("BREADTH FIRST SEARCH RESULT WILL BE :\n");
					BFS(g,visited,MAX,-1);
					printf("\n");

					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					if(is_cycle_exist(g,visited,MAX))
					{
						printf("!!!!!CYCLE EXIST!!!!!\n");
					}
					else
					{
						for(int i=0;i<=MAX;i++)
						{
							visited[i]=false;
						}
						printf("TOPOLOGICAL SORT RESULT WILL BE :\n");
						TOPOSORT(g,visited,MAX);
						printf("\n");
					}
					break;
				}
			case 6:
				{
					display(g);
					break;
				}
			case 7:
				{
					int MAX=size(g);
					Boolean *visited;
					visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					if(is_cycle_exist(g,visited,MAX))
					{
						printf("!!!!!CYCLE EXIST!!!!!\n");
					}
					else
					{
						printf("CYCLE DOES NOT EXIST!!!!!\n");
					}
					break;
				}
			case 8:
				{
					int MAX=size(g);
					Boolean *visited,*visited_2;
					visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					check_strongly_connected(g,visited,MAX);
					visited_2=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					check_weekly_connected(g,visited_2,MAX);
					break;
				}
			case 9:
				{
					int MAX=size(g);
					Boolean *visited;
					visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					int u;
					printf("ENTER THE SOURCE VERTEX(ENTER ONLY THOSE NODES THAT EXIST) \n");
					scanf("%d",&u);
					Dijsktra(g,u,visited,MAX);
					break;
				}
			case 10:
				{
					int MAX=size(g);
					int **cost,**Dist;
					cost=(int**)malloc(sizeof(int*)*(MAX+1));
					Dist=(int**)malloc(sizeof(int*)*(MAX+1));
					for(int i=0;i<=MAX;i++)
					{
						cost[i]=(int*)malloc(sizeof(int)*(MAX+1));
						Dist[i]=(int*)malloc(sizeof(int)*(MAX+1));
						for(int j=0;j<=MAX;j++)
						{
							cost[i][j]=INT_MAX;
							Dist[i][j]=0;
						}
					}
					Node *ptr;
					Edge *tmp;
					ptr=g->nodes;
					while(ptr!=NULL)
					{
						tmp=ptr->edgelist;
						while(tmp!=NULL)
						{
							cost[ptr->node][tmp->dest]=tmp->weight;
							tmp=tmp->nextEdge;
						}
						ptr=ptr->down;
					}

					APSP(cost,Dist,g,MAX);
					break;
				}
			case 11:
				{
					int MAX=size(g);
					Boolean *visited;
					visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					int key=0;
					printf("ENTER THE ELEMENT TO BE SEARCHED:\n");
					scanf("%d",&key);
					if( DFS(g,visited,MAX,key) == SUCCESS)
					{
						printf("ELEMENT EXIST WHEN SEARCHED VIA DFS\n");
					}
					else
					{
						printf("ELEMENT DOES NOT EXIST WHEN SEARCHED VIA DFS\n");
					}
					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					if( BFS(g,visited,MAX,key) == SUCCESS)
					{
						printf("ELEMENT EXIST WHEN SEARCHED VIA BFS\n");
					}
					else
					{
						printf("ELEMENT DOES NOT EXIST WHEN SEARCHED VIA BFS\n");
					}
					break;
				}
			case 12:
				{
					int MAX=size(g);
					Boolean *visited;
					visited=(Boolean*)malloc(sizeof(Boolean)*(MAX+1));
					for(int i=0;i<=MAX;i++)
					{
						visited[i]=false;
					}
					Prims_mst(g,visited,MAX);
					break;
				}
			case 13:
				{
					int MAX=size(g);
					int s,d;
					printf("ENTER THE SOURCE AND DESTINATION VERTEX(ENTER ONLY THOSE NODES THAT EXIST) :\n");
					scanf("%d%d",&s,&d);
					PrintAllPaths( s, d,g,MAX);
					break;
				}
			case 14:
				{
					flg=1;
					break;
				}
			default:
				{
					printf("WRONG CHOICE\n");
					break;
				}
			 }
	}while(true && flg==0);



	return 0;
}


//1 0 1 1 1 2 2 d 4 0 1 2 d 6 1 0 2 d 2 1 2 2 d 3 2 0 2 d 11 0 2
//
//
//
//1 0 1 1 1 2 1 3 1 4 1 5 2 d 50 0 1 2 d 10 1 2 2 d 45 0 2 2 d 10 0 3 2 d 20 3 0 2 d 15 1 3 2 d 15 3 4 2 d 20 4 1 2 d 35 4 2 2 d 30 2 4 2 d 5 5 4
//
//
//
//
//
//
//1 0 1 1 1 2 1 3 2 u 3 0 1 2 u 2 1 2 2 u 2 2 3 2 u 3 3 0 2 u 3 0 2
//
//
//
//
//
//
//
//
//1 0 1 1 1 2 1 3 1 4 1 5 1 6 2 u 28 0 1 2 u 16 1 2 2 u 14 1 62 u 18 6 3 2 u 12 2 3 2 u 24 6 4 2 u 22 4 3 2 u 25 4 5 2 u 10 5 0 2 u 14 1 6
//
//
//
//
//1 1 1 2 1 3 1 4 1 5 1 6 2 u 4 1 2 2 u 20 2 3 2 u 10 3 4 2 u 25 4 5 2 u 7 5 6 2 u 8 1 6 2 u 16 6 2 2 u 5 6 3 2 u 6 5 3
