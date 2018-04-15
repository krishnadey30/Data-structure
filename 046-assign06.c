/*
Name:Krishna Kumar Dey
Roll No:201601046
Modified at:
*/
#include <stdio.h>//defing input output library
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
typedef struct 
{
	int proID;
	char name[50];
	int type;
	char make[100];
	float mrp;
	float discount;
	float charges;
	float starrate;
 	struct ITEM *next;
}ITEM;


ITEM *head=NULL;
ITEM *insertItem(ITEM *item)
{
 	ITEM *a;
	item->next=NULL;
	if(head==NULL)
	{
		head=item;
	}
	else
	{
		a=head;
		while(a->next!=NULL)
		{
			a=a->next;
		}
		a->next=item;

	}
	return head;
}
ITEM *genDataset(FILE *fp)
{
	int i,j;
	char A[20],BI[20],C[20],D[20],E[20],F[20],G[20],H[20],c;
	ITEM *B;
	//B=(ITEM *) malloc(sizeof(ITEM));
	ITEM *a;
	for(i=0;i<12;i++)
	{
		B=(ITEM *) malloc(sizeof(ITEM));
		fscanf(fp,"%[^,]%c%[^,]%c%[^,]%c%[^,]%c%[^,]%c%[^,]%c%[^,]%c%[^,]%c",A,&c,BI,&c,C,&c,D,&c,E,&c,F,&c,G,&c,H,&c);
		B->proID=atoi(A);
		strcpy(B->name,BI);
		B->type=atoi(C);
		strcpy(B->make,D);
		B->mrp=atof(E);
		B->discount=atof(F);
		B->charges=atof(G);
		B->starrate=atof(H);
		//printf("%d,%s,%d,%s,%f,%f,%f,%f\n",B->proID,B->name,B->type,B->make,B->mrp,B->discount,B->charges,B->starrate);
		a=insertItem(B);
	}
	
	return a;
}
void printItems(ITEM *item)
{
	ITEM *a,P;
	a=item;
	//printf("%d\n",a );
	while(a!=NULL)
	{
		P=*a;
		printf("%d,%s,%d,%s,%f,%f,%f,%f\n",P.proID,P.name,P.type,P.make,P.mrp,P.discount,P.charges,P.starrate);
		a=a->next;
		//printf("%s\n",a );
	}
}
void printItems(ITEM *item);
void SearchLowPrice(ITEM *item);
ITEM *modifyDiscount(ITEM *item, float off);
void deleteItemByID(ITEM *item, int proID);
int main(int argc, char const *argv[])
{
	ITEM *item;
    FILE *fp;

    fp = (argc > 1) ? fopen(argv[1], "r+") : fopen("inputdata.txt", "r+");
    item = genDataset(fp);
    fclose(fp);
   // printf("%d %d\n",head,item );
    printItems(item);
    
    /*char *product = "Nikon";
    printf("\nPRODUCT: %s", product);
    
    //SearchItemByMake(item, product);
    
    SearchLowPrice(item);
    
    float off = -0.5f;       // you could change the sign to give additional discount
    item = modifyDiscount(item, off);
    
    int proID = 75242;
    deleteItemByID(item, proID);*/
        
    return 0;
}
