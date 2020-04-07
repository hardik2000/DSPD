/*
 ============================================================================
 Name        : queen.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include"safe.h"
#define N 8
int nqueen(int board[][N],int row,int col);

int main(void)
{
	int i=1,j,k,flag=0;
	int board[N][N];
//	for(j=0; j<N ;j++)
//	{
//		for(k=0; k<N ;k++)
//		{
//			board[j][k]=0;
//		}
//	}
	for(i=0;i<N;i++)
	{
		for(j=0; j<N ;j++)
		{
			for(k=0; k<N ;k++)
			{
				board[j][k]=0;
			}
		}
		board[0][i]=1;
		if(nqueen(board,1,i))
		{
			//print(board,N);
			flag=1;
			for(j=N-1; j>=0 ;j--)
			{
				for(k=0; k<N ;k++)
				{
					printf("%d ",board[j][k]);
				}
				printf("\n");
			}
			printf("\n");
		}
		board[0][i]=0;
	}
	if(flag==0)
	{
		printf("no such thing possible:\n");
	}
	return 0;
}
int nqueen(int board[][N],int row,int col)
{
	int j=1,flag=0;
	if(row==N)
	{
		return 1;
	}
	else
	{
		for(j=0; j<N  && flag==0;j++)
		{
			if(safe(board,row,j,N))
			{
				board[row][j]=1;
				flag=nqueen(board,row+1,j);
				if(flag==0)
				{
					board[row][j]=0;
				}
			}

		}
		if(flag==0 && j==N)
		{
			return 0;
		}

	}
}
