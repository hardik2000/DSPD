#include<stdio.h>
#include"safe.h"
int safe(int board[][8],int row,int col,int N)
{
	int i,j;
	for(i=row-1;i>=0;i--)
	{
		if(board[i][col]==1)
		{
			return 0;
		}
	}
	for(i=row-1,j=col-1;i>=0 && j>=0;i--,j--)
	{
		if(board[i][j]==1)
		{
			return 0;
		}
	}
	for(i=row-1,j=col+1;i>=0 && j<N;i--,j++)
	{
		if(board[i][j]==1)
		{
			return 0;
		}
	}
	return 1;
}

