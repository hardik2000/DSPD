/*
 ============================================================================
 Name        : sum_min.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style

 3 100 1 1
65 100 100 1
100 90 10 1
100 100 1 8
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int min_sum(int a[][4],int r,int c,int n)
{
	int temp=0,m,q;
	if(r==n-1 && c==n-1)
	{
		temp=a[r][c];

	}
	else if(r==n-1)
	{
		temp=a[r][c]+min_sum(a,r,c+1,n);

	}
	else if(c==n-1)
	{
		temp=a[r][c]+min_sum(a,r+1,c,n);

	}
	else
	{
		temp=a[r][c];

		m=min_sum(a,r,c+1,n);
		q=min_sum(a,r+1,c,n);
		if(m<q)
		{
			printf("%d ",a[r][c]);
			temp=temp+m;
		}
		else
		{
			printf("%d ",a[r][c]);
			temp=temp+q;
		}
	}


	return temp;
}

int main(void)
{
	int a[4][4],i,j;
	printf("Enter the matrics:\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	int sum;
	printf("\n");
	sum=min_sum(a,0,0,4);
	printf("\nTHE MIN SUM IS =%d\n",sum);
	return 0;
}
