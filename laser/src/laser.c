/*
 ============================================================================
 Name        : laser.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef enum{false,true} bool;

typedef struct Point
{
	long long int x;
	long long int y;
}Point;


int main(void)
{
    int t=0;
	long long int n,q;
	scanf("%d",&t);
	while(t-->0)
	{
		scanf("%lld%lld",&n,&q);
		struct Point p[n];
		long long int x[n];
		x[0]=0;
		for(int i=1;i<n;i++)
		{
			x[i]=1;
		}
		long long int max=0;
		for(int i=0;i<n;i++)
		{
			p[i].x=i+1;
			scanf("%lld",&p[i].y);
			if(p[i].y>max)
			{
			    max=p[i].y;
			}
		}
    //    long long int y[max];
        long long int *y;
        y=(long long int *)malloc(sizeof(long long int)*max);
		for(int i=0;i<max;i++)
		{
			y[i]=0;
		}

		for(int i=0;i<n-1;i++)
		{
			if(p[i].y<p[i+1].y)
			{
				for(int k=p[i].y;k<p[i+1].y;k++)
				{
					y[k]++;
				}
			}
			else
			{
				for(int k=p[i].y;k>p[i+1].y;k--)
				{
					y[k]++;
				}
			}

		}
		y[p[n-1].y]++;

		for(int i=0;i<q;i++)
		{
			struct Point q,r;
			scanf("%lld%lld%lld",&q.x,&r.x,&q.y);
			r.y=q.y;
			long long int countx=0,county=0;
			for(int i=q.x+1;i<=r.x;i++)
			{
				if(x[i-1]==1)
				{
					countx++;
				}
			}

			county=y[q.y];
			if(countx<county)
			{
				printf("%lld\n",countx);
			}
			else
			{
				printf("%lld\n",county);

			}


		}
	   	free(y);
	}









	return 0;
}

