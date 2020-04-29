/*
 ============================================================================
 Name        : COIN_PROBLEM.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 2147483647
typedef enum{FAILURE,SUCCESS}status_code;

// Bottom up dynamic programming solution.
// Iteratively compute number of coins for
// larger and larger amounts of change
int makeChange(int c,int coins[],int n)
{
	int cache[c + 1];
	for(int i=0;i<=c;i++)
		cache[i]=0;
	for (int i = 1; i <= c; i++)
	{
		int minCoins = MAX;
		// Try removing each coin from the total
		// and see which requires the fewest
		// extra coins
		for (int j=0;j<n;j++)
		{
			if (i - coins[j] >= 0)
			{
				int currCoins = cache[i-coins[j]] + 1;
				if (currCoins < minCoins)
				{
					minCoins = currCoins;
				}
			}
		}
		cache[i] = minCoins;
	}
	return cache[c];
}
status_code display_coins(int c,int coins[],int n,int fig[])
{
	status_code status=FAILURE;

	for(int i=n-1;i>=0 && status==FAILURE;i--)
	{
		int count=(int)(c/coins[i]);
		if(count!=0)
		{	if((count*coins[i])==c)
			{
				status=SUCCESS;
			}
			else
			{
				for(;count>=0 && status==FAILURE;count--)
				{
					status=display_coins( c-(count*coins[i]) ,coins,n-1,fig);
				}
				if(status==SUCCESS)
				{
					count++;
				}
			}
			if(status==SUCCESS)
				fig[i]=count;
		}
	}
	return status;
}




int main(void)
{
	int n;
	printf("ENTER THE DIMENSIONS OF COIN AVAILABALE\n");
	scanf("%d",&n);
	int coins[n];
	int fig[n];
	for(int i=0;i<n;i++)
			fig[i]=0;

	printf("ENTER THE COINS DIMENSIONIN INCREASING ORDER\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&coins[i]);
	}
	int money;
	printf("ENTER THE COIN TO GET CHANGE\n");
	scanf("%d",&money);
	printf("MINIMUM COINS REQUIRED ARE:%d\n\n",makeChange(money,coins,n));

	if(display_coins(money,coins,n,fig))
	{
		for(int i=0;i<n;i++)
		{
			printf("%d----%d\n",coins[i],fig[i]);
		}
	}
	else
	{
		printf("NOT POSSIBLE\n");
	}


	return 0;
}
