#include<stdio.h>
#include<stdlib.h>
typedef struct library
{
	int I;
	int N;
	int T;
	int M;
	int *ID;
	int reg;
	int rank;
}lib;

void merge(int arr[], int l, int m, int r,int Score[],int size)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (Score[L[i]] > Score[R[j]])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r,int Score[],int size)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m,Score,size);
        mergeSort(arr, m+1, r,Score,size);

        merge(arr, l, m, r,Score,size);
    }
}




void main()
{
	int B,L,D;
	FILE * fp;
    fp = fopen("a_example.txt", "r");

    fscanf(fp,"%d%d%d",&B,&L,&D);
	lib LIB[L];
    int Score[B],i,j;
	for(i=0;i<B;i++)
	{
		fscanf(fp,"%d",&Score[i]);
	}
	for(i=0;i<L;i++)
	{
		LIB[i].I=i;
		fscanf(fp,"%d%d%d",&LIB[i].N,&LIB[i].T,&LIB[i].M);
		LIB[i].ID=(int *)malloc(sizeof(int)*LIB[i].N);
		for(j=0;j<LIB[i].N;j++)
		{
			fscanf(fp,"%d",&LIB[i].ID[j]);
		}
		mergeSort(LIB[i].ID,0,LIB[i].N-1,Score,LIB[i].N);
//		for(int k=0;k<LIB[i].N;k++)
//		{
//			printf("%d ",LIB[i].ID[k]);
//		}
//		printf("\n");
	}
	for(i=0;i<L;i++)
	{
		int days=D;
		days=days-LIB[i].T;
		int sc,m=0,k=0;
		while(days>0 && m<LIB[i].N)
		{
			k=0;
			while(k<LIB[i].M && m<LIB[i].N)
			{
				sc+=Score[LIB[i].ID[m]];
				m++;k++;

			}
			days--;
		}
		LIB[i].reg=sc;
	}
	lib temp;
	for(i=0;i<L;i++)
	{
		temp=LIB[i];
		j=i-1;
		while(j>=0 && LIB[j].reg<temp.reg)
		{
			LIB[j+1]=LIB[j];
			j--;
		}
		LIB[j+1]=temp;
	}
	FILE *fo;
	fo = fopen("temp.txt", "w");

	fprintf(fo,"%d \n",L);
	for(i=0;i<L;i++)
	{
		fprintf(fo,"%d %d \n",LIB[i].I,LIB[i].N);
		for(j=0;j<LIB[i].N;j++)
		{
			fprintf(fo,"%d \n",LIB[i].ID[j]);
		}
		fprintf(fo,"\n");

	}






	//	int count=0;i=0;
//	while(D>0 && i<L)
//	{
//		D=D-LIB[i].T;
//		if(D>0)
//		{
//			days=D;m=0;
//			//fprintf(fo,"%d %d \n",LIB[i].I,LIB[i].N);
//			while(days>0 && m<LIB[i].N)
//			{
//				k=0;
//				while(k<LIB[i].M && m<LIB[i].N)
//				{
//					if(Score[LIB[i].ID[m]]!=-1)
//					{
//						Score[LIB[i].ID[m]]=-1;
//`
//						};
//					m++;k++;
//
//				}
//				days--;
//			}
//
//			printf("\n");
//		}
//		i++;
//		count++;
//	}
//
//
//
//


	fclose(fo);

	fclose(fp);


}
