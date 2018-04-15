/*
	Name: Krishna Kumar Dey
	Roll:201601046
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct GRAPH
{
	int V;
	int *A;
}GRAPH;

int *DFS,**B,*D,max1=0;
int kl[4];
int *deg;
GRAPH *buildUWGraph (int n)
{
	GRAPH *G;
	G=(GRAPH *)malloc(sizeof(GRAPH));
	G->V=n;
	G->A=(int *)malloc((n*n)*sizeof(int));
	int i,c=0;
	for (i = 0; i < n*n; i++)
	{
		if(i!=0 && i%n==0)
		{
			c++;
		}
		if(i%n>=c)
		{
			if((i-c)%n==0)
			{
				G->A[i]=0;
			}
			else
			{
				G->A[i]=rand()%6;
			}
		}
		else
		{
			G->A[i]=G->A[(n*(i%n))+c];
		}
	}
	return G;
}

int nodeDegree(GRAPH *graph, int n)
{
	int i,degree=0,c=0;
	deg=(int *)malloc(n*sizeof(int));
	for(i=0;i<n*n;i++)
	{
		if(graph->A[i]!=0)
		{
			degree++;
		}
		if(i!=0 && (i+1)%n==0)
		{
			deg[c]=degree;
			printf("NODE %d : %d degrees\n",c+1,deg[c] );
			degree=0;
			c++;
		}
	}
}
void pathK(int V[],GRAPH *graph,int k,int count,int v)
{
	int c,j,X,n;	
	c=v;
	V[c]=1;
	kl[count]=v;
	//printf("%d  %d\n",count,c );
	if(count==k)
	{
		
		for(j=0;j<4;j++)
		{
			printf("%d",kl[j]);
			if(j<3)
				printf(" -> ");
		}
		printf("\n");
		V[c]=0;
	}
	else
	{
		n=graph->V;
	    for(j=0;j<n;j++)
	    {
	    	X=(n*c)+j;
	    	if(V[j]==0 && graph->A[X]!=0)
	    	{	
	        	pathK(V,graph,k,count+1,j);
	    	}
	   	}
	   	V[c]=0;
    }
}
void printPathsOfLengthK(GRAPH *graph, int k)
{
	int i;
	int *V;
	int c=0;
	V=(int *)malloc(graph->V*sizeof(int));
	for(i=0;i<graph->V;i++)
	{
		V[i]=0;
	}
	for(i=0;i<graph->V;i++)
	{
		pathK(V,graph,k,c,i);
	}
}

void depthforsearch(int A[],int i,int n)
{
	int c,j,X;
	printf("%d",i%n );
	c=i%n;
	DFS[c]=1;    
    for(j=0;j<n;j++)
    {
    	X=(n*c)+j;
    	if(DFS[X%n]==0 && A[X]!=0)
    	{
    		//printf("%d X: %d\n",c,X);
      		printf(" -> ");
       		B[c][X%n]=A[X];
       		B[X%n][c]=A[X];
        	depthforsearch(A,X,n);
    	}
   	}
}


void performTraversalDFS (GRAPH *graph)
{
	depthforsearch(graph->A,0,graph->V);
}

void longestpath(int Vis[],int max[],int trav[],GRAPH *graph,int count,int v)
{
	int c,j,X,n;
	
	n=graph->V;	
	//printf("%d\n",n);
	c=v;
	Vis[c]=1;
	trav[count]=v;
	count+=1;
	if(max1<count)
	{
		max1=count;
		for(j=0;j<=max1;j++)
		{
			max[j]=trav[j];
		}
	}
	for(j=0;j<n;j++)
	{
	    X=(n*c)+j;
	    if(Vis[j]==0 && graph->A[X]!=0)
		{	
		   	longestpath(Vis,max,trav,graph,count,j);
		   	count-=1;
		}
   	}
   	Vis[c]=0;
	
	
}
void findLongestPath(GRAPH *graph)
{
	int i;
	int *trav,*max,count=0,*vis;
	vis=(int *)malloc(graph->V*sizeof(int));
	trav=(int *)malloc(graph->V*sizeof(int));
	max=(int *)malloc(graph->V*sizeof(int));
	for(i=0;i<graph->V;i++)
	{
		vis[i]=0;
	}
	for(i=0;i<graph->V;i++)
	{
		longestpath(vis,max,trav,graph,count,i);
	}
	for(i=0;i<max1;i++)
	{
		printf("%d",max[i] );
		if(i<max1-1)
			printf(" -> ");
	}
	printf("\nrespective degrees:\n");
	for (i = 0; i < max1; i++)
	{
		printf("%d",deg[max[i]] );
		if(i<max1-1)
			printf(" -- ");
	}
}

void deletenode(GRAPH *graph)
{
	int i,j;
	for(j=0;j<graph->V;j++)
	{
		if(D[j]==1)
		{
			for(i=0;i<graph->V;i++)
				graph->A[j*graph->V+i]=-1;
			for(i=0;i<graph->V;i++)
				graph->A[j+graph->V*i]=-1;
		}
	}
}

void deleteKdegreeVertices(GRAPH *graph, int k)
{
	int i,degree=0,c=0,n;
	n=graph->V;
	for(i=0;i<n*n;i++)
	{
		if(graph->A[i]!=0)
		{
			degree++;
		}
		if(i!=0 && (i+1)%n==0)
		{
			if(degree==k)
				D[c]=1;
			degree=0;
			c++;
		}
	}
}


int main(int argc, char const *argv[])
{
	time_t t;
	srand((unsigned)time(&t));
	int n=(argc>1)?atoi(argv[1]):5;
	int i,j,c=0;
	GRAPH * G=buildUWGraph(n);

	printf("\n-----------CREATING GRAPH AND ITS ADJECENCY MATRIX-------------\n\n");
	for ( i = 0; i < n*n; ++i)
	{
		printf("%d ",G->A[i] );
		if(i!=0 && (i+1)%n==0)
		{
			printf("\n");
		}
	}

	printf("\n-----------PRINTING THE DEGREE OF EACH NODE -------------------\n\n");
	nodeDegree(G,n);
	DFS=(int *)malloc(n*sizeof(int));
	B=(int **)malloc(n*sizeof(int *));
	D=(int *)malloc(n*sizeof(int));
	for ( i = 0; i < n; i++)
	{
			DFS[i]=0;
			D[i]=0;
			B[i]=(int *)malloc(n*sizeof(int));
			for (j= 0; j < n; j++)
			{
				B[i][j]=0;
			}
	}

	printf("\n-----------DEPTH FOR SEARCH IN THE GRAPH ----------------------\n\n");
	performTraversalDFS(G);
	printf("\n\n");
	for ( i = 0; i < n; i++)
	{
		for (j= 0; j < n; j++)
		{
			printf("%d ",B[i][j] );
		}
		printf("\n");
	}
	printf("\n");
	
	printf("\n-----------NO OF PATHS OF LENGTH 'K'---------------------------\n\n");
	printPathsOfLengthK(G,3);
	printf("\n");

	printf("\n-----------DELETING ALL NODES WITH DEGREE 'n'---------------------------\n\n");
	deleteKdegreeVertices(G,2);
	deletenode(G);
	for ( i = 0; i < n*n; ++i)
	{	
		if(G->A[i]>=0)
		{
			printf("%d ",G->A[i] );
			c=1;
		}
		if(i!=0 && (i+1)%n==0 && c==1)
		{
			printf("\n");
			c=0;
		}
	}
	printf("\n-----------FIND LONGEST PATH---------------------------\n\n");
	findLongestPath(G);
	return 0;
}