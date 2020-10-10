/*
 ============================================================================
 Name        : Graph_class.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//Adjacency list representation
#include <stdio.h>
#include <stdlib.h>
#define MAX 15
#define INT_MAX 10000
typedef enum{false,true}Boolean;
typedef enum{FAILURE,SUCCESS} status_code;
typedef int vertex;
typedef int item_type;

Boolean visited[MAX];

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



typedef struct edge_tag
{
	vertex endpoint;
	struct edge_tag* nextEdge;
	struct edge_tag* self;
}Edge;

typedef struct Graph
{
	int N;
	Edge* edgelist[MAX];
}Graph;

void initialise(Graph* g)
{
	g->N=0;
	for(int i=0;i<MAX;i++)
	{
		g->edgelist[i]=NULL;
	}
}
void makeedge(Graph* g,int x,int y)
{
	Edge *X,*Y;
	X=(Edge*)malloc(sizeof(Edge));
	Y=(Edge*)malloc(sizeof(Edge));
	X->endpoint=x;
	X->nextEdge=NULL;
	X->self=g->edgelist[x];
	Y->endpoint=y;
	Y->nextEdge=NULL;
	Y->self=g->edgelist[y];
	Edge* temp;
	temp=g->edgelist[x];
	if(temp==NULL)
	{
		g->edgelist[x]=Y;
	}
	else
	{
		while(temp->nextEdge!=NULL)
		{
			temp=temp->nextEdge;
		}
		temp->nextEdge=Y;
	}
	temp=g->edgelist[y];
	if(temp==NULL)
	{
		g->edgelist[y]=X;
	}
	else
	{
		while(temp->nextEdge!=NULL)
		{
			temp=temp->nextEdge;
		}
		temp->nextEdge=X;
	}
}

void makeedge_directed(Graph* g,int x,int y)
{
	Edge *Y;
	Y=(Edge*)malloc(sizeof(Edge));
	Y->endpoint=y;
	Y->nextEdge=NULL;
	Y->self=g->edgelist[y];
	Edge* temp;
	temp=g->edgelist[x];
	if(temp==NULL)
	{
		g->edgelist[x]=Y;
	}
	else
	{
		while(temp->nextEdge!=NULL)
		{
			temp=temp->nextEdge;
		}
		temp->nextEdge=Y;
	}

}


void printgraph(Graph g)
{

	Edge* temp;
	for(int i=0;i<g.N;i++)
	{
		temp=g.edgelist[i];
		printf("%d ->",i);
		while(temp!=NULL)
		{
			printf("%d ->",temp->endpoint);
			temp=temp->nextEdge;
		}
		printf("NULL\n");
	}
}

void visit(vertex v)
{
	printf("%d ",v);
}

void Traverse(Graph* g ,vertex v)
{
	visited[v]=true;
	visit(v);
	Edge* temp;
	temp=g->edgelist[v];
	while(temp!=NULL)
	{
		if(!visited[temp->endpoint])
		{
			Traverse(g,temp->endpoint);
		}
		temp=temp->nextEdge;
	}
}


void DFS(Graph* g)
{
	for(vertex i=0;i<g->N;i++)
	{
		visited[i]=false;
	}
	for(vertex i=0;i<g->N;i++)
	{
		if(!visited[i])
		{
			Traverse(g,i);
		}
	}
}

void BFS(Graph* g)
{

	queue s;
	Initialise(&s);
	status_code sc;
	for(vertex i=0;i<g->N;i++)
	{
		visited[i]=false;
	}
	for(vertex i=0;i<g->N;i++)
	{
		if(!visited[i])
		{
			sc=insert(&s,i);
			do
			{
				sc=delete(&i,&s);
				if(!visited[i])
				{
					visited[i]=true;
					visit(i);
					Edge* temp=g->edgelist[i];
					while(temp!=NULL)
					{
						if(!visited[temp->endpoint])
						{
							sc=insert(&s,temp->endpoint);
						}
						temp=temp->nextEdge;
					}
				}

			}while(!IsQueueEmpty(&s));

		}
	}

}

void TOPOSORT(Graph* g)
{
	int pred[g->N];
	for(vertex i=0;i<g->N;i++)
	{
		visited[i]=false;
	}
	for(int i=0;i<g->N;i++)
	{
		pred[i]=0;
	}
	for(int i=0;i<g->N;i++)
	{
		Edge* temp=g->edgelist[i];
		while(temp!=NULL)
		{
			pred[temp->endpoint]++;
			temp=temp->nextEdge;
		}
	}
	int flg=0,flg1=0;
	do
	{
		flg=0;flg1=0;
		int i=0;
		for(i=0;i<g->N && flg==0;i++)
		{
			if(pred[i]==0 && !visited[i])
			{
				flg=1;
			}
		}
		i--;
		if(flg==1)
		{
			visit(i);
			visited[i]=true;
			Edge* temp=g->edgelist[i];
			while(temp!=NULL)
			{
				pred[temp->endpoint]--;
				temp=temp->nextEdge;
			}
		}
		for(int j=0;j<g->N && flg1==0;j++)
		{
			if(!visited[j])
				flg1=1;
		}
	}while(flg1);
}

void makeedge_weight(Graph *g2,int x,int y,int weight,int** cost)
{
	Edge *Y;
	Y=(Edge*)malloc(sizeof(Edge));
	cost[x][y]=weight;
	Y->endpoint=y;
	Y->nextEdge=NULL;
	Y->self=g2->edgelist[y];
	Edge* temp;
	temp=g2->edgelist[x];
	if(temp==NULL)
	{
		g2->edgelist[x]=Y;
	}
	else
	{
		while(temp->nextEdge!=NULL)
		{
			temp=temp->nextEdge;
		}
		temp->nextEdge=Y;
	}

}


void Dijsktra(Graph *g,int n,int** cost,int u,int end)
{
	int Dist[MAX],Prev[MAX];
	vertex v,w;
	int i;
	for(i=0;i<g->N;i++)
	{
		visited[i]=false;
		Dist[i]=cost[u][i];
		Prev[i]=u;
	}

	visited[u]=true;
	Dist[u]=0;				//self distancing is
	for(i=0;i<g->N;i++)
	{
		int min=INT_MAX;
		for(w=0;w<g->N;w++)
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
		visited[v]=true;
		for(w=0;w<n;w++)
		{
			if(visited[w]==false)
			{
				if(Dist[v]+cost[v][w]<Dist[w])
				{
					Dist[w]=Dist[v]+cost[v][w];
					Prev[w]=v;
				}
			}
		}

	}
	if(Dist[end]!=INT_MAX)
	{
		printf("THE SHORTEST DISTANCE FROM NODE %d TO NODE %d IS:%d\n",u,end,Dist[end]);
		printf("THE SHORTEST DISTANCE PATH FROM  NODE %d TO NODE %d IS:\n",u,end);
		int key=end;
		printf("%d<-",key);
		while(Prev[key]!=u)
		{
			printf("%d<-",Prev[key]);
			key=Prev[key];
		}
		printf("%d",u);
	}
	else
	{
		printf("NO SUCH PATH EXIST\n");
	}
}

void APSP(int **cost,int **Dist,Graph *g)
{
	int i,j,k;
	for(i=0;i<g->N;i++)
	{
		for(j=0;j<g->N;j++)
		{
			Dist[i][j]=cost[i][j];

		}
	}//till this we have calculated A^-1[i][j]
	for(k=0;k<g->N;k++)
	{
		for(i=0;i<g->N;i++)
		{
			for(j=0;j<g->N;j++)
			{
				if(Dist[i][j]>(Dist[i][k]+Dist[k][j]))
				{
					Dist[i][j]=Dist[i][k]+Dist[k][j];
				}

			}
		}
	}
	for(i=0;i<g->N;i++)
	{
		for(j=0;j<g->N;j++)
		{
			printf("%d-->",Dist[i][j]);

		}
		printf("\n");
	}

}

int main(void)
{
//	Graph g,g1;
	int x,a,b;
//	printf("ENTER THE NUMBER OF EDGES<10\n");
//	scanf("%d",&x);
//	initialise(&g);
//	g.N=x;
//	initialise(&g1);
//	g1.N=x;
//	printf("ENTER THE NUMBER OF EDGES U WANT TO ENTER\n");
//	scanf("%d",&x);
//	for(int i=0;i<x;i++)
//	{
//		printf("ENTER TEH EDGE:\n");
//		scanf("%d%d",&a,&b);
//		makeedge(&g,a,b);
//		makeedge_directed(&g1,a,b);
//		printf("\n");
//	}
//	printf("ADJACENECY LIST FOR THE ABOVE METRICS IS AS FOLLOWS:\n");
//	printgraph(g);
//	printf("DEPTH FIRST SEARCH FOR THE ABOVE TREE IS AS FOLLOW:\n");
//	DFS(&g);
//	printf("\n");
//	printf("BREADTH FIRST SEARCH FOR THE ABOVE TREE IS AS FOLLOW:\n");
//	BFS(&g);
//
//	printf("TOPOLOGICAL SEARCH BEGINS:\n");
//	printf("ADJACENECY LIST FOR THE ABOVE METRICS IS AS FOLLOWS:\n");
//	printgraph(g1);
//	printf("TOPOLOGICAL SEARCH FOR THE ABOVE TREE IS AS FOLLOW:\n");
//	TOPOSORT(&g1);

	//code to input weighted graph
//	Graph g2;
//	int weight=0;
//	printf("ENTER THE NUMBER OF EDGES<10\n");
//	scanf("%d",&x);
//	initialise(&g2);
//	g2.N=x;
//	printf("ENTER THE NUMBER OF EDGES U WANT TO ENTER\n");
//	scanf("%d",&x);
//	int **cost,**Dist;
//	cost=(int**)malloc(sizeof(int*)*g2.N);
//	Dist=(int**)malloc(sizeof(int*)*g2.N);
//
//	for(int j=0;j<g2.N;j++)
//	{
//		cost[j]=(int*)malloc(sizeof(int)*g2.N);
//		Dist[j]=(int*)malloc(sizeof(int)*g2.N);
//
//		for(int k=0;k<g2.N;k++)
//		{
//			cost[j][k]=INT_MAX;
//			Dist[j][k]=0;
//		}
//	}
//	for(int i=0;i<x;i++)
//	{
//		printf("ENTER THE EDGE ALONG WITH WEIGHTS:\n");
//		scanf("%d%d%d",&a,&b,&weight);
//		makeedge_weight(&g2,a,b,weight,cost);
//		printf("\n");
//	}
//	printf("ENTER THE FIRST NODE AND THE END NODE");
//	scanf("%d%d",&a,&b);
//	//calling dijkstra algorithm
//	Dijsktra(&g2,g2.N,cost,a,b);




	//APSP CODE
	Graph g2;
	int weight=0;
	printf("ENTER THE NUMBER OF EDGES<10\n");
	scanf("%d",&x);
	initialise(&g2);
	g2.N=x;
	printf("ENTER THE NUMBER OF EDGES U WANT TO ENTER\n");
	scanf("%d",&x);
	int **cost,**Dist;
	cost=(int**)malloc(sizeof(int*)*g2.N);
	Dist=(int**)malloc(sizeof(int*)*g2.N);

	for(int j=0;j<g2.N;j++)
	{
		cost[j]=(int*)malloc(sizeof(int)*g2.N);
		Dist[j]=(int*)malloc(sizeof(int)*g2.N);

		for(int k=0;k<g2.N;k++)
		{
			if(j==k)
				cost[j][k]=0;
			else
				cost[j][k]=INT_MAX;
			Dist[j][k]=0;
		}
	}
	for(int i=0;i<x;i++)
	{
		printf("ENTER THE EDGE ALONG WITH WEIGHTS:\n");
		scanf("%d%d%d",&a,&b,&weight);
		makeedge_weight(&g2,a,b,weight,cost);
		printf("\n");
	}

	printf("SEE RESULT FOR ALL PAIR SSHORTEST PATH ALGORITHM\n");
	APSP(cost,Dist,&g2);

	return 0;
}
//input for given adjacency list
//8 10 0 1 0 2 1 3 1 4 2 5 2 6 3 7 4 7 5 7 6 7
//
//0 ->1 ->2 ->NULL
//1 ->0 ->3 ->4 ->NULL
//2 ->0 ->5 ->6 ->NULL
//3 ->1 ->7 ->NULL
//4 ->1 ->7 ->NULL
//5 ->2 ->7 ->NULL
//6 ->2 ->7 ->NULL
//7 ->3 ->4 ->5 ->6 ->NULL


/*
10
14
0
1
0
2
0
3
1
4
2
4
2
5
3
5
3
7
4
6
5
6
5
8
7
8
6
9
8
9
*/


//
//6
//11
//0 1 50
//1 2 10
//0 2 45
//0 3 10
//3 0 20
//1 3 15
//3 4 15
//4 1 20
//4 2 35
//2 4 30
//5 4 5


//3
//5
//0 1 4
//1 0 6
//1 2 2
//0 2 11
//2 0 3




