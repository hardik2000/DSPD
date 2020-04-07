/*
 ============================================================================
 Name        : Determinent.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int Determinent(int a[][3],int r,int c,int M,int N);
int main(void)
{

	int a[3][3];
	int M=3,N=3;
	printf("Enter the value of the matrix:\n");
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}

	printf("%d	is the Determinent",Determinent(a,-1,-1,M,N));
	return 0;
}
int Determinent(int a[][3],int r,int c,int M,int N)
{
	int ans=0;
	int i,j;
	if(r+1 == M-2)
	{
		ans=( a[(r+1)%3][(c+1)%3]*a[(r+2)%3][(c+2)%3] )-( a[(r+1)%3][(c+2)%3]*a[(r+2)%3][(c+1)%3] );
	}
	else
	{
		i=r+1;
		for(j=0;j<N;j++)
		{

			if(j!=c && j>c)
			{
				ans= ans+ a[i][j] * Determinent(a,i,j,M,N);
			}
		}
	}
	return(ans);
}
