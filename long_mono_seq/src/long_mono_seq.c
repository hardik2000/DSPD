/*
 ============================================================================
 Name        : long_mono_seq.c
 Author      : Hardik & Suyash
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n,i,temp,j,x;
	scanf("%d",&n);
	int a[n],value[n],count[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		value[i]=-1;
		count[i]=1;
	}
	i=1;
	while(i<n)
	{
		j=i-1;
		temp=i;
		while(j>=0)
		{
			if(a[j]<a[i])
			{
				if(value[j]>=value[temp])
				{
					temp=j;
					x=j;
				}
			}
			j--;
		}
		value[i]=x;
		i++;
	}
	i=0;
	while(i<n)
	{
		j=i-1;
		temp=i;
		x=0;
		while(j>=0)
		{
			if(a[j]<a[i])
			{
				if(count[j]>=count[temp])
				{
					temp=j;
					x=count[j];
				}
			}
			j--;
		}
		count[i]+=x;
		i++;
	}
	/*for(i=0;i<n;i++)
	{
		printf("%d	%d	%d\n",a[i],value[i],count[i]);
	}*/
	i=1;x=count[0];temp=0;
	while(i<n)
	{
		if(count[i]>x)
		{
			temp=i;
			x=count[i];
		}
		i++;
	}
	//printf("%d",temp);
	while(temp>=0)
	{
		printf("%d ",a[temp]);
		temp=value[temp];
	}










	return 0;
}
