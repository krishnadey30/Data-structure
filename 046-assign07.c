/*NAME:KRISHNA KUMAR DEY
ROLL NO:201601046
BATCH:A
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//creating structure BTNODE
typedef struct BTNODE
{
	int proID;
	int rank;
	int level;
	float cost;
	float discount;
	float scost;
	struct BTNODE *left;
	struct BTNODE *right;
}BTNODE; 	
BTNODE *A[1000], *mini;
int n,c=0;
float min,a=0.0;


//GENERATING BINARY TREE
BTNODE *genBinaryTree(BTNODE *btnode, int n)
{
	int i,p;
	
	BTNODE *a,*b;
	time_t t;
	srand((unsigned)time(&t));
	for(i=0;i<n;i++)
	{
		btnode=(BTNODE *)malloc(sizeof(BTNODE));
		btnode->proID=(rand()%9000)+1000;
		btnode->rank=(rand()%9000)+1;
		btnode->cost=(rand()%4000)/10.0+99.0;
		btnode->discount=(rand()%30000)/10000.0+2.0;
		btnode->left=NULL;
		btnode->right=NULL;
		A[i]=btnode;//STORING THE ADDRESS OF NODES IN ARRAY 'A' 
	}
	i=0,p=1;
	a=A[i];
	a->level=i;
	while(p!=n)
	{
		a=A[i];
		b=A[p];
		b->level=(a->level)+1;
		a->left=b;//ASSIGNING IN LEFT HALF
		p++;
		if(p==n)
			break;
		b=A[p];
		b->level=(a->level)+1;
		a->right=b;// ASSIGNING IN RIGHT HALF
		i++;
		p++;
	}
	return A[0];
}


//PRINTRING THROUGH INORDER TRAVERSAL
void printElements(BTNODE *btnode)
{
	if(btnode==NULL)
		return;
	printElements(btnode->left);
	printf("%d %d %d %0.2f %0.2f\n",btnode->proID,btnode->rank,btnode->level,btnode->cost,btnode->discount);
	printElements(btnode->right);
}

//printing those values in between 129.0 to 399.95
void RangeSearchByCost(BTNODE *item, float scost)
{
	//printf("%f\n",scost );
	if(scost>=129.0 && scost<=399.95)
	{
		printf("%d %d %d %0.2f %0.2f \n",item->proID,item->rank,item->level,item->cost,scost);
	}
}

//to check which values are inbetween 129.0-399.95
void inbet(BTNODE *btnode)
{
	if(btnode==NULL)
		return;
	inbet(btnode->left);
	btnode->scost=btnode->cost-(btnode->discount*btnode->cost)/100;
	RangeSearchByCost(btnode,btnode->scost);
	inbet(btnode->right);

}

//to search min cost
void SearchMinCost(BTNODE *btnode) 
{
	if(btnode==NULL)
		return;
	SearchMinCost(btnode->left);
	if(btnode->cost<=min && btnode->cost>a)
	{
		min=btnode->cost;
		mini=btnode;
	}
	SearchMinCost(btnode->right);
}

//funtion to store whose level is not to be deleted
void noofnodes(BTNODE *btnode, int level,BTNODE *array[])
{
	if(btnode==NULL)
		return;
	noofnodes(btnode->left,level,array);
	if(btnode->level!=level)
	{
		array[c]=btnode;
		//printf("%d\n",btnode->level );
		c++;
	}
	noofnodes(btnode->right,level,array);
}

//derefrencing 
void makingnull()
{	
	int i=0;
	for(i=0;i<n;i++)
	{
		A[i]->left=NULL;
		A[i]->right=NULL;
	}
}

//deleting level
BTNODE *deleteElements(BTNODE *btnode, int level)
{
	BTNODE *array[1000],*a,*b;
	noofnodes(btnode,level,array);
	int i=0;
	int p=1;
	//printf("%d\n",c );
	makingnull();
	while(p!=c)
	{
		a=array[i];
		//printf("%d ",a->level);
		b=array[p];
		a->left=b;//ASSIGNING IN LEFT HALF
		p++;
		if(p==c)
			break;
		b=array[p];
		a->right=b;// ASSIGNING IN RIGHT HALF
		i++;
		p++;
	}
	return array[0];
}


//main function
int main(int args, char const *argv[])
{
	int i,level;
	if(argv[1]==NULL)
		n=4;
	else
		n=atoi(argv[1]);
	level=(args>2)?atoi(argv[2]):0;
	BTNODE *btnode,*item;
	btnode=genBinaryTree(btnode,n);
	printf("------------------------------------------------generatingtree---------------------------------------\n");
	printElements(btnode);
	printf("\n");
	printf("-----------------RangeSearchByCost---------------------------------------------------------------------\n");
	inbet(btnode);
	printf("------------------------min cost and second min--------------------------------------------\n");
	min=btnode->cost;
	printf("\n");
	SearchMinCost(btnode);
	printf("%d %d %d %0.2f\n",mini->proID,mini->rank,mini->level,mini->cost);
	a=min;
	min=0.0;
	mini=btnode;
	SearchMinCost(btnode);
	printf("%d %d %d %0.2f\n",mini->proID,mini->rank,mini->level,mini->cost);
	printf("\n");
	btnode=deleteElements(btnode,level);
	printf("-------------------printing after deleting level-----------------------------------------------------\n");
	printElements(btnode);
	0
	return 0;
}
