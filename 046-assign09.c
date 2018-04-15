/*
	Name: Krishna Kumar Dey
	Roll:201601046
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*defining data structure of MOVIE*/
typedef struct movie
{
	int movieID;		/*: <int> - a Unique Movie Identifier - [100, 2000]*/
	char mname[16];		/*: <char> - it can hold a maximum of 16 characters*/
	int likes;			/*: <int> - size [50, 10000] – likes of the people*/
	int year;			/*: <int> - year of release of the movie*/
	float rating;		/*: <float> - [1, 10] – rating of the movie*/
	float budget;		/*: <float> - [10.0, 20.00] – making cost of the movie(in crores)*/
	float revenue;		/*: <float> - total box office collection made by the movie in the range - [1.0, 1000.0] (amount in crores)*/
	int time; 			/*: <int> – [20.0, 180.0] – running time in minutes*/
}MOVIE;

/*Creating data structure HEAP*/
typedef struct heap
{
	MOVIE movie;
	struct heap *left,*right,*parent;
}HEAP;

/*Creating structure for Linked List*/
typedef struct Linked
{
	struct Linked *next;
	HEAP *heap;
}Linked;
Linked *head1=NULL;
char mname1[][100]={
				{"Zanzeer"},
				{"Amar akabar"},
				{"King No 1"},
				{"Mugle Ajjam"},
				{"Pyar ka Punch"},
				{"Sucide Squad"},
				{"Hello Brother"},
				{"Om Shanti Om"},
				{"Logan"}
			};
int year1[100]={1990,1980,2003,1965,2003,2016,1995,2009,2017};
int h=0,k=0,o=1,n;
HEAP *head=NULL;

/*heapification*/
void heapification(HEAP *temp)
{
	HEAP *X,*m;
	X=temp->parent;
	if(X==head)
	{
		if(X->movie.time<temp->movie.time)
		{
			if(X->left==temp)
			{
				m=temp->left;
				temp->left=X;
				X->left=m;
				X->parent=temp;
				if(X->left!=NULL)
					X->left->parent=X;
				m=temp->right;
				temp->right=X->right;
				if(temp->right!=NULL)
					temp->right->parent=temp;
				X->right=m;
				if(X->right!=NULL)
					X->right->parent=X;
				temp->parent=NULL;
				head=temp;
			}
			else
			{
				m=temp->right;
				temp->right=X;
				X->right=m;
				X->parent=temp;
				if(X->right!=NULL)
					X->right->parent=X;
				m=temp->left;
				temp->left=X->left;
				if(temp->left!=NULL)
					temp->left->parent=temp;
				X->left=m;
				if(X->left!=NULL)
					X->left->parent=X;
				temp->parent=NULL;
				head=temp;
			}
		}
	}
	else
	{
		if(X->movie.time<temp->movie.time)
		{
			if(X->left==temp)
			{
				m=temp->left;
				temp->left=X;
				X->left=m;
				temp->parent=X->parent;
				X->parent=temp;
				if(X->left!=NULL)
					X->left->parent=X;
				m=temp->right;
				temp->right=X->right;
				if(temp->right!=NULL)
					temp->right->parent=temp;
				X->right=m;
				if(X->right!=NULL)
					X->right->parent=X;
				if(temp->parent->left==X)
					temp->parent->left=temp;
				else
					temp->parent->right=temp;
			}
			else
			{
				m=temp->right;
				temp->right=X;
				X->right=m;
				temp->parent=X->parent;
				X->parent=temp;
				if(X->right!=NULL)
					X->right->parent=X;
				m=temp->left;
				temp->left=X->left;
				if(temp->left!=NULL)
					temp->left->parent=temp;
				X->left=m;
				if(X->left!=NULL)
					X->left->parent=X;
				if(temp->parent->left==X)
					temp->parent->left=temp;
				else
					temp->parent->right=temp;
			}
			heapification(temp);
		}
	}
}


/*creating HEAP through LEVEL ORDER traversal*/
void creating(HEAP *root,HEAP *temp,int i)
{
	if(head==NULL)
	{
		head=temp;
		temp->parent=NULL;
		return;
	}
	else
	{
		
		if(i==h-1 && root->left==NULL)
		{
			root->left=temp;
			temp->parent=root;
			o=0;
			heapification(temp);			
			return;
		}
		else if(i==h-1 && root->right==NULL)
		{
			root->right=temp;
			temp->parent=root;
			o=0;
			heapification(temp);
			return;
		}
		else if(i<h)
		{
			creating(root->left,temp,i+1);
			if(o==1)
				creating(root->right,temp,i+1);
		}
	}
}

/*FOR HEIGHT AND CALLING THE FUNCTION FOR CREATING HEAP*/
void creatingheap(HEAP *temp)
{
	int i=0;
	k++; /*NO OF NODES CREATED*/
	if((2*(pow(2,h)-1)+1)<k)
	{
		h++;  					/*current HEIGHT*/
	}
	creating(head,temp,i);
	o=1;
	
}


/*Inserting Movie details*/
HEAP *createMovieDataset(HEAP *heap, int n)
{
	int i,x;
	for(i=0;i<n;i++)
	{
		heap=(HEAP *)malloc(sizeof(HEAP));
		heap->movie.movieID=(rand()%1901)+100;
		x=rand()%9;
		strcpy(heap->movie.mname,mname1[x]);
		heap->movie.likes=(rand()%9951)+50;
		heap->movie.year=year1[x];
		heap->movie.rating=(rand()%1000)/100.0+1;
		heap->movie.budget=(rand()%1000)/100.0+10;
		heap->movie.revenue=(rand()%100000)/100.0+1;
		heap->movie.time=rand()%161+20;
		heap->left=NULL;
		heap->right=NULL;
		creatingheap(heap);
	}
	return head;
}

/*printing Movie Details*/
void printMovieDetails(HEAP *movie)
{
	if(movie==NULL)
		return;
	printMovieDetails(movie->left);
	printf("ID: %d  NAME: '%s'  LIKES: %d  YEAR: %d ",movie->movie.movieID,movie->movie.mname,movie->movie.likes,movie->movie.year);
	printf("RATING: %0.3f  BUDGET: %0.3f  REVENUE: %0.3f  TIME: %d\n",movie->movie.rating,movie->movie.budget,movie->movie.revenue,movie->movie.time);
	printMovieDetails(movie->right);
}

/*level order Traversal*/
void levelordertraversal(HEAP* movie, int level)
{
    if(movie==NULL)
        return;
    if(level==1)
    {
    	printf("ID: %d  NAME: '%s'  LIKES: %d  YEAR: %d ",movie->movie.movieID,movie->movie.mname,movie->movie.likes,movie->movie.year);
		printf("RATING: %0.3f  BUDGET: %0.3f  REVENUE: %0.3f  TIME: %d\n",movie->movie.rating,movie->movie.budget,movie->movie.revenue,movie->movie.time);
	}
    else if(level > 1)
    {
        levelordertraversal(movie->left, level-1);
        levelordertraversal(movie->right, level-1);
    }
}

/*performing BFS*/
void performBreadthFirstSearch(HEAP *heap)
{
	int i;
    for(i=1; i<=h+1; i++)
        levelordertraversal(heap, i);
}


/*creating linked list*/
void creatinglinkedlist(HEAP *movie)
{
	Linked *a=(Linked *)malloc(sizeof(Linked));
	if(head1==NULL)
	{
		head1=a;
		head1->heap=movie;
		head1->next=NULL;
	}
	else
	{
		Linked *b=head1;
		while(b->next!=NULL)
		{
			b=b->next;
		}
		b->next=a;
		a->heap=movie;
		a->next=NULL;
	}
}

/*sending the adress to create linked list*/
void inserting(HEAP* movie, int level)
{
	if(movie==NULL)
        return;
    if(level==1)
    {	
    	creatinglinkedlist(movie);
    }
    else if(level > 1)
    {
       	inserting(movie->left, level-1);
        inserting(movie->right, level-1);
    }

}


/*SORTING THE LINKED LIST*/
void sortinglinkedlist()
{
	HEAP *tem;
	Linked *a1,*a=head1;
	for (;a!=NULL;a=a->next)
	{
		for (a1=a->next;a1!=NULL;a1=a1->next)
		{
			if(a->heap->movie.time<a1->heap->movie.time)
			{
				tem=a->heap;
				a->heap=a1->heap;
				a1->heap=tem;
			}
		}
	}
}

/*PRINTING THE SORTED LINKED LIST*/
void printinglinkedlist()
{
	Linked *a=head1;
	while(a!=NULL)
	{
		printf("ID: %d  NAME: '%s'  LIKES: %d  YEAR: %d ",a->heap->movie.movieID,a->heap->movie.mname,a->heap->movie.likes,a->heap->movie.year);
		printf("RATING: %0.3f  BUDGET: %0.3f  REVENUE: %0.3f  TIME: %d\n",a->heap->movie.rating,a->heap->movie.budget,a->heap->movie.revenue,a->heap->movie.time);
		a=a->next;
	}
}


/*converting to sorted Linked list*/
void convertHeapToSortedLinkedList(HEAP *heap)
{
	int i;
    for(i=1; i<=h+1; i++)
        inserting(heap, i);
    sortinglinkedlist();
    printinglinkedlist();
}




/*main function*/
int main(int argc,char *argv[])
{
	time_t t;
	srand((unsigned)time(&t));
	n=(argc>1)?atoi(argv[1]):20;
	HEAP *root=NULL;

	/*Create a heap with n MOVIES.*/
	root=createMovieDataset(root,n);

	/*printing MOVIE details after creating */
	printf("------------------print the details of each item after creating(INORDER TRAVERSAL)------------------------------------------------------\n\n");
	printMovieDetails(root);

	/*PERFORMING BFS*/
	printf("\n----------------breadth first search and printing the details of the movie visited each time along with their levels information.-----\n\n");
	performBreadthFirstSearch(root);

	/*Converting Heap To Sorted LinkedList*/
	printf("\n----------------to convert the heap into the linked list. Linked list are organized in a specific order.------------------------------\n\n");
	convertHeapToSortedLinkedList(root);

	
	return 0;
}