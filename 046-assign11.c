/*
	Name: Krishna Kumar Dey
	Roll: 201601046
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "046-trie.h"
typedef struct  node
{
	int index;
	struct node *next;
}NODE;

typedef struct list
{
	int index;
	int degree;
	NODE *head;
}LIST;

typedef struct
{
	int V;
	LIST *A;
}GRAPH;


/* Function to add edge 'j' in the linked list of edge 'i' */
void addedge(int i,int j,GRAPH *G)
{
	NODE *edge;
	edge=(NODE *)malloc(sizeof(NODE));		/* allocating memory to the node */
	edge->index=j;							/* assigning the index of the edge to the node */
	G->A[i].degree++;						/* increasing the degree of edge 'i' as edge 'j' is connected to it */  
	edge->next=G->A[i].head;				/* creating stack */
	G->A[i].head=edge;						/* creating stack */
}

/* Function to print the graph */
void printgraph(GRAPH *G)
{
	int i;
	NODE *edge;
	for (i = 0; i < G->V; i++)
	{
		edge=G->A[i].head;
		printf("Edges Connected With node %d ( degree = %d ) are : ",i,G->A[i].degree);
		while(edge!=NULL)
		{
			printf("%d",edge->index );
			edge=edge->next;
			if(edge!=NULL)
				printf(" , ");
		}	
		printf("\n");
	}
}

/* Function to build the graph */
GRAPH *buildUndirectedGraph(int n)
{
	GRAPH *G;
	int i,j,value;
	G=(GRAPH *)malloc(sizeof(GRAPH));		/* allocating memory to graph */
	G->V=n;									/* adding no of nodes in the graph */
	G->A=(LIST *)malloc(n*sizeof(LIST));	/* allocating memory for n nodes in graph */

	for (i = 0; i < n; i++)
	{
		G->A[i].index=i;					/* assigning the index value to node 'i' */
		G->A[i].head=NULL;					/* assigning NULL to head pointer of node 'i' */
		G->A[i].degree=0;					/* assigning the initial degree to be zero */
	}

	for (i = 0; i < n; i++)
	{
		for (j=i+1 ; j < n; j++)
		{
			value=rand()%2;					/* randomly generating the edge weights i.e. 0 or 1 */
			if(value)
			{
				addedge(i,j,G);				/* calling addedge function which will add edge 'j' in the linked list of edge 'i' */
				addedge(j,i,G);				/* calling addedge function which will add edge 'i' in the linked list of edge 'j' */
			}
		}
	}
	printgraph(G);							/* calling the print graph function */
	return G;
}

/* FUnction to create the spanning Tree */
void createspTree(GRAPH *G,int edge,int V[],GRAPH *ST)
{
	NODE *path;
	int index;
	V[edge]=1;								/* assigning the edge 'edge' as visited */
	path=G->A[edge].head;					/* assigning the adress of the root node to pointer path */
	printf("%d ",edge);
	while(path!=NULL)
	{
		index=path->index;					/* assigning the index of the connected edge to variable 'index' */
		if (!V[index])						/* checking if edge 'index' is unvisited */
		{
			addedge(edge,index,ST);			/* calling addedge function which will add edge 'index' in the linked list of edge 'edge' */
			addedge(index,edge,ST);			/* calling addedge function which will add edge 'edge' in the linked list of edge 'index' */
			createspTree(G,index,V,ST);		/* recurrsively calling the function */
		}
		path=path->next;					/* moving the path pointer to next node */
	}
}

GRAPH *getSpanningTree(GRAPH *graph)
{
	int *V,i,n;
	GRAPH *ST;
	n=graph->V;								/* no of nodes in the graph */
	V=(int *)malloc(graph->V*sizeof(int));	/* allocating memory to array which will store Visited/Non-visited details */ 
	ST=(GRAPH *)malloc(sizeof(GRAPH));		/* allocating memory to spanning tree(graph) */
	ST->V=n;								/* adding no of nodes in the spanning tree(graph) */
	ST->A=(LIST *)malloc(n*sizeof(LIST));	/* allocating memory for n nodes in spanning tree(graph) */

	for (i = 0; i < n; i++)
	{
		ST->A[i].index=i;					/* assigning the index value to node 'i' */
		ST->A[i].head=NULL;					/* assigning NULL to head pointer of node 'i' */
		ST->A[i].degree=0;					/* assigning the initial degree to be zero */
	}

	for (i = 0; i < n; i++)
	{
		V[i]=0;								/* making all edges as unvisited */
	}

	for (i = 0; i < n; i++)
	{
		if(!V[i] && graph->A[i].degree>0)	/* checking if the edge is unvisited and atleast one edge is conected to it */
		{	
			createspTree(graph,i,V,ST);		/* calling the create spanning tree function */
		}
	}
	printf("\n\n");
	printgraph(ST);							/* calling the printing of graph function to print the spanning tree(graph) */
	return ST;
}


/* FUNCTION TO FIND THE SHORTEST PATH */
void shortestpath(int edge,int cur[],GRAPH *G,int count,int V[],int dest)
{
	int i,index;
	NODE *path;
	if(count>6)
	{
		return;
	}
	cur[count]=edge;
	V[edge]=1;
	if(edge==dest)
	{
		for (i = 0; i < count+1; i++)
		{
			printf("%d ",cur[i] );
			if(i<count)
				printf("-> ");
		}
		printf("\n");
		V[edge]=0;
	}
	else
	{
		path=G->A[edge].head;	
		while(path!=NULL)
		{
			index=path->index;					/* assigning the index of the connected edge to variable 'index' */
			if (!V[index])						/* checking if edge 'index' is unvisited */
			{
				shortestpath(index,cur,G,count+1,V,dest);
			}
			path=path->next;
		}
		V[edge]=0;
	}
}

/*
	function to find all shortest paths between any 2 vertices in a graph
	such that the total sum of the edges weights is less than or equal to 6.
*/
void *findShortestPathsL6(GRAPH *graph, int source, int dest)
{
	int *V,i,n,*cur;
	NODE *path;
	n=graph->V;									/* no of nodes in the graph */
	V=(int *)malloc(graph->V*sizeof(int));		/* allocating memory to array which will store Visited/Non-visited details */ 
	path=graph->A[source].head;					/* assigning the address of the root node of the source edge */
	cur=(int *)malloc(graph->V*sizeof(int));	/* allocating memory to array which will store index of Visited edges */ 

	for (i = 0; i < n; i++)
	{
		V[i]=0;									/* making all edges as unvisited */
	}
	V[source]=1;
	cur[0]=source;
	while(path!=NULL)
	{
		shortestpath(path->index,cur,graph,1,V,dest);
		path=path->next;
	}
}

int main(int argc, char const *argv[])
{
	time_t t;
	int n,x,y,i,k=3;
	char names[201][50];
	srand((unsigned)time(&t));
	GRAPH *G,*ST;
	n=(argc>1)?atoi(argv[1]):10;		/* if value of n is given through terminal else consider 10 */
	printf("\n ''' Considering n=10 as output may not be shown in one terminal for all shortest path. We can give any value of 'n' trough terminal. '''\n\n");
	printf("\n------------------ Defining a GRAPH (undirected & weighted) and representing the graph as an adjacency list ---------------------\n \n");
	G=buildUndirectedGraph(n);

	printf("\n------------------ Create a spanning tree of the above & print the degree of each node in the spanning tree.---------------------\n \n");
	ST=getSpanningTree(G);

	x=rand()%n;
	y=rand()%n;

	printf("\n------------------ shortest paths between %d and %d is ---------------------\n \n",x,y);
	if(x==y)
		printf("same Nodes\n");
	else
		findShortestPathsL6(G,x,y);

	printf("\n------------------ Load the names given in the text file ''names-authors.txt''  using TRIE sdata structure.-------\n \n");
	loadnames(names);
	printf("\n------------------ to find the common prefix in these names in such a way that the size of the common prefix is greater than k-------\n \n");
	loadingontrie(names,k);
	return 0;
}