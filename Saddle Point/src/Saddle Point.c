/*
 ============================================================================
 Name        : Saddle.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#define N 5
#define M 5
void Saddlepoint(int a[][M],int n);
int main(void)
{
	int n,i,j;
	int a[N][M];
	printf("Enter the size of the matrix:\n");
	scanf("%d",&n);
	printf("Enter the matrics:\n");

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	Saddlepoint(a,n);



	return 0;
}
void Saddlepoint(int a[][M],int n)
{
	int i,j,pos,max,flag,gflag=1;
	for(i=0;i<n;i++)
	{
		pos=0;
		for(j=1;j<n;j++)
		{
			if(a[i][j]<a[i][pos])
			{
				pos=j;
			}
		}
		max=a[i][pos];
		flag=1;
		for(j=0;j<n;j++)
		{
			if(a[j][pos]>max)
			{
				flag=0;
			}

		}
		if(flag==1)
		{
			printf("%d is a saddle point:",a[i][pos]);
			gflag=0;
		}

	}
	if(gflag==1)
	{
			printf("There does not exist aany saddle point");
	}

}
