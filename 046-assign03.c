#include<stdio.h>
#include<string.h>
char A[6000];
//sorting
int srting(char A[],char B[])
{
	int a,b,n,i,r=0;
	a=strlen(A);
	b=strlen(B);
	if(a>b)
		n=a;
	else
		n=b;
	for(i=0;i<n;i++)
	{
		if(A[i]>B[i])
		{
			r=1;
			break;
		}
		else if(A[i]<B[i])
		{
			break;
		}
	}
	return r;
}

//ending with "an"
void printing(char A[])
{
	int l=strlen(A);
	if(A[l-1]=='n' && A[l-2]=='a')
		printf("%s\n",A);
}

//appearance of letter 'R'
void R(char A[])
{
	int n,i,t=0;
	n=strlen(A);
	for(i=0;i<n;i++)
	{
		if(A[i]=='R')
			t=1;
	}
	if(t)
		printf("%s\n",A);
}

//printing 3-grams

int grams(char A[])
{
	int n,i,x,j,a=0;
	n=strlen(A);
	for(i=0;i<n-3;i++)
	{
		j=i;
		for(x=0;x<3;x++)
		{
			if(A[j]==' ')
				j++;
			printf("%c",A[j]);
			j++;
		}
		a++;
		printf("\n");
	}
	return a;
}

//longest sub string
void longest(char A[],int a,int b,char B[])
{
	int i,j=0;
	char temp[100];
	for(i=0;i<strlen(A)-b;i++)
	{
		if(A[i+a]!=A[i+b]) 
			break;
		else
		{
			if(i>0 && A[i+a]<A[i-1+a])
				break;
			if(A[i+a]!=A[i-1+a]+1)
				break;
			temp[j]=A[i+a];
			j++;
		}
	}
	temp[j]=0;
	if(strlen(B)<strlen(temp))
		strcpy(B,temp);
}

//4grams And permutation
void grams4(char A[])
{
	int i,j,n;
	n=strlen(A);
	char temp[10];
	for(i=0;i<n-4;i++)
	{
		for(j=0;j<4;j++)
		{
			temp[j]=A[i+j];
		}
		temp[j]=0;
		//permutation(temp,0,4);
	}
}

int main()
{
	char A[10][100]={"Raguvanshi",
				"M Radhakrishnan",
				"Pauline Haddow",
				"Sunil Chandran",
				"Uma Gopinath",
				"Soma Raju",
				"T V Gopala Krishnan",
				"Sudha Raghunath",
				"Rajarshi Pal",
				"Karthikeyan"};
	int i,j=0,z,n;
	char swap[100];
	//Q1
	for(i=0;i<10;i++)
	{
		printf("%s\n",A[i]);
		if(strlen(A[j])<=strlen(A[i]))
			j=i;
	}
	
	printf("\n%s\n\n",A[j]);
	
	//Q2---------------------------------------------------------------------------------------------------------------------------------------

	for(i=0;i<9;i++)
	{
		for(j=i;j<10;j++)
		{
			z=srting(A[i],A[j]);
			if(z==1)
			{
				strcpy(swap,A[i]);
				strcpy(A[i],A[j]);
				strcpy(A[j],swap);
			}
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%s\n",A[i]);
	}	
	
	printf("\n\n");
	
	for(i=0;i<10;i++)
	{
		printing(A[i]);
	}
	
	printf("\n\n");
	
	
	for(i=0;i<10;i++)
	{
		R(A[i]);
	}
	printf("\n\n");
	
	
	//Q3-------------------------------------------------------------------------------------
	j=0;
	for(i=0;i<10;i++)
	{
		n=grams(A[i]);
		j+=n;
		printf("\n");
	}
	
	printf("%d\n\n",j);
	
	//Q4--------------------------------------------------------------------------------------
	char C[100]="mnopqrstuv";
	grams4(C);
	//Q5---------------------------------------------------------------------------------------
	char B[100]="mnoarswtdefgharamnopyqrrstuvwxystuvwxyxwzrwqtuvwxz";
	char D[100]="";
	n=strlen(B);
	for(i=0;i<n;i++)
	{
		z=i;
		for(j=i+1;j<n;j++)
		{
			if(B[z]==B[j] && B[z+1]==B[j+1] && B[z]+1==B[z+1])
			{
				longest(B,z,j,D);
			}
		}
	}
	printf("%s\n",D);
	return 0;
}
