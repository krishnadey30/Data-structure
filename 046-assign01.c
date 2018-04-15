#include<stdio.h>
#include<math.h>

//sum of first 20 prime numbers in [1,500]
void primesum()
{
	int i,j,sum=0,count,count1=0;
	for(i=2;i<=500;i++)
	{
		count=0;
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			{
				count++;
			}
		}
		if(count==0)
		{
			sum+=i;
			count1++;
			//printf("%d %d\n",i,count1);
		}
		if(count1>=20)
		{
			break;
		}
	}
	printf("%d\n",sum);
}


//all the integers divisible by 3 but not by 2 in [1,50]
void divi()
{
	int i;
	for(i=2;i<=50;i++)
	{
		if(i%3==0 && i%2!=0)
		{
			printf("%d\n",i);
		}
	}
}


//non-zero factors of any positive integer in [60,200]
void factors()
{

	int i,j;
	for(i=60;i<=200;i++)
	{	
		printf("%d>",i);	
		for(j=1;j<=i;j++)
		{
			if(i%j==0)
			{
				printf("%d ",j);
			}
		}
		printf("\n");
	}
}
/*void factor()
{
	int i,j,k;
	for(k=0;k<5;k++)
	{
		i=rand()%140+60;
		printf("%d-",i);
		for(j=1;j<=i;j++)
		{
			if(i%j==0)
			{
				printf("%d ",j);
			}
		}
		printf("\n");
	}
	
} 
*/

//no of odd digits in a given number
void countodd(int n)
{	
	int j,count=0;
	while(n>0)
	{
		j=n%10;
		n=n/10;
		if(j%2!=0)
		{	
			count++;
		}
	}
	printf("%d\n",count);
}

//febonacci sequence
void fibon()
{
	long long int j=1,sum=1,k=1;
	printf("1 1 ");
	while(k<80)
	{
		sum=sum+k;
		j=j+k;
		k=j-k;
		j=j-k;
		k=k+j;
		if(k<80)
		printf("%lld ",k);
		
	}
	printf("\n%lld \n",sum);
}


//x=y^2+z^2
void bonus()
{
	int i,j,k,A[500]={0};
	for(i=0;i<=22;i++)
	{
		for(j=0;j<=22;j++)
		{
			k=pow(i,2)+pow(j,2);
			if(k>500)
			{
				continue;
			}
			if(A[k]==0)
			{
				printf("%d\n",k);
			}
			
			A[k]=1;
		}
	}
}

//main function
int main()
{	
	int n;
	scanf("%d",&n);
	primesum();
	printf("\n");
	divi();
	printf("\n");
	factors();
	printf("\n");
	countodd(n);
	printf("\n");
	//factor();
	fibon();
	printf("\n");
	bonus();
	return 0;
}

//roll_no:201601046
//name:Krishna Kumar Dey

