/*NAME: KRISHNA KUMAR DEY
ROLL:201601046
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
typedef struct BSTREE
{
	int nID;				/*Node Identifier - [1, 2000]*/
	char proname[16]; 		/* it can hold a maximum of 16 characters*/
	int size;	 			/*size [480, 3375] – measured in square feet*/
	float nbeds;	 		/*[1, 5] - increment can be in steps of 0.5*/
	float base;				/*[2499.0, 4850.0] – base price per square feet*/
	float charges;			/*represents percentage of the base ranging from [2.14, 8.23]*/
	int ptype;				/*ranges in {0, 1, 2}: 0 – basement parking;1- covered parking; and 2 – open parking*/
	struct BSTREE *left,*right;
}BSTREE;
BSTREE *root=NULL,*ARRAY[100];
char proname1[][100]={
				{"abcd"},
				{"abcde"},
				{"avgsxg"},
				{"akjhaa"},
				{"kajgajvga"},
				{"jdasfzaya"},
				{"javdsgfrasdt"},
			};
int n;
void createbinarytree(BSTREE *bstree,BSTREE *temp)
{
	if(root==NULL)
	{
		root=bstree;
		return;
	}
	if(bstree->size<temp->size)
	{
		if(temp->left==NULL)
		{
			temp->left=bstree;
			return;
		}
		else
			createbinarytree(bstree,temp->left);
	}
	else
	{
		if(temp->right==NULL)
		{
			temp->right=bstree;
			return;
		}
		else
			createbinarytree(bstree,temp->right);
	}
}
BSTREE *genFlatsDataset (BSTREE *bstree, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		bstree=(BSTREE *)malloc(sizeof(BSTREE));
		bstree->nID=(rand()%2000)+1;
		strcpy(bstree->proname,proname1[rand()%7]);
		bstree->size=(rand()%2996)+480;
		bstree->nbeds=((rand()%9)+2)/2.0;
		bstree->base=(rand()%23520)/10.0+2499.0;
		bstree->charges=((rand()%610)+214)/100.0;
		bstree->ptype=rand()%3;
		bstree->left=NULL;
		bstree->right=NULL;
		ARRAY[i]=bstree;
		createbinarytree(bstree,root);
	}
	return root;
}

void printFlatDetails(BSTREE *bstree)
{
	if(bstree==NULL)
		return;
	printFlatDetails(bstree->left);
	printf("ID: %d NAME: %s SIZE: %d  BEDS: %0.2f ",bstree->nID,bstree->proname,bstree->size,bstree->nbeds);
	printf("BASE: %0.3f  CHARGES: %0.3f  PARKING: %d\n",bstree->base,bstree->charges,bstree->ptype);
	printFlatDetails(bstree->right);
}

void FindFlatsByNBeds(BSTREE *bstree, float n)
{
	if(bstree==NULL)
		return;
	FindFlatsByNBeds(bstree->left,n);
	if(bstree->nbeds==n)
	{
		printf("ID: %d NAME: %s SIZE: %d  BEDS: %0.2f ",bstree->nID,bstree->proname,bstree->size,bstree->nbeds);
		printf("BASE: %0.3f  CHARGES: %0.3f  PARKING: %d\n",bstree->base,bstree->charges,bstree->ptype);
	}
	FindFlatsByNBeds(bstree->right,n);
}

void ModifyParking(BSTREE *bstree, int oldPark, int newpark)
{
	if(bstree==NULL)
		return;
	ModifyParking(bstree->left,oldPark,newpark);
	if(bstree->ptype==oldPark)
	{
		bstree->ptype=newpark;
	}
	ModifyParking(bstree->right,oldPark,newpark);

}
void makingnull()
{	
	int i;
	for(i=0;i<n;i++)
	{
		ARRAY[i]->left=NULL;
		ARRAY[i]->right=NULL;
	}
}

BSTREE *BalanceBST(BSTREE *bstree)
{
	int i=0,p=1;
	makingnull();
	BSTREE *a,*b;
	a=ARRAY[i];
	while(p!=n)
	{
		a=ARRAY[i];
		b=ARRAY[p];
		a->left=b;//ASSIGNING IN LEFT HALF
		p++;
		if(p==n)
			break;
		b=ARRAY[p];
		a->right=b;// ASSIGNING IN RIGHT HALF
		i++;
		p++;
	}
	return ARRAY[0];
}
int c=0;
BSTREE *array[100];
void makingnull1()
{	
	int i;
	for(i=0;i<c;i++)
	{
		array[i]->left=NULL;
		array[i]->right=NULL;
	}
}
void noofnodes(BSTREE *btnode, int min,int max)
{
	if(btnode==NULL)
		return;
	noofnodes(btnode->left,min,max);
	if(btnode->charges>min && btnode->charges<max)
	{
		array[c]=btnode;
		//printf("%d\n",btnode->level );
		c++;
	}
	noofnodes(btnode->right,min,max);
}
BSTREE *deleteElements(BSTREE *bstree, int min, int max)
{
	noofnodes(bstree,min,max);
	int i=0,p=1;
	makingnull1();
	BSTREE *a,*b;
	a=array[i];
	while(p!=c)
	{
		a=array[i];
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
int main(int argc,char *argv[])
{
	time_t t;
	srand((unsigned)time(&t));(rand()%9000)+1000;
	n=(argc>1)?atoi(argv[1]):20;
	BSTREE *bstree;
	bstree=genFlatsDataset(bstree,n);		/*generating BINARY TREE */

	/*--------------------printing the TREE after creating----------------------------- */
	printf("\n");
	printFlatDetails(bstree);

	/*-----------------to search and print the details of the flats by specific number of bedrooms---*/
	float a=((rand()%9)+2)/2.0;
	printf("\n");
	printf("----------------------------to search and print the details of the flats by specific number of bedrooms-%0.1f-------------\n",a);
	FindFlatsByNBeds(bstree,a);
	int newpark=rand()%3;
	int oldPark=rand()%3;
	printf("\n");
	printf("--------------------printing the TREE after updating from %d to %d----------------------------\n",oldPark,newpark);
	ModifyParking(bstree,oldPark,newpark);
	/*--------------------printing the TREE after updating----------------------------- */
	printFlatDetails(bstree);
	printf("\n");
	printf("----------------------------printing tree after making it complete binary tree-------------\n");
	bstree=BalanceBST(bstree);
	printFlatDetails(bstree);
	printf("\n");
	float min=((rand()%610)+214)/100.0;
	float max=min+1.0;
	bstree=deleteElements(bstree,min,max);
	printFlatDetails(bstree);
	printf("---------------------");
	printf("\n");

	return 0;
}