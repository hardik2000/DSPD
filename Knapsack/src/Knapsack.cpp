//============================================================================
// Name        : Knapsack.cpp
// Author      : Hardik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<math.h>
using namespace std;

typedef struct Items
{
	int weight;
	int value;
}Item;
int knapsack(Item items[], int W,int size);
int knapsack(Item items[], int W, int i,int size);


// Overloaded recursive function
int knapsack(Item items[], int W, int i,int size)
{
	// If we've gone through all the items,
	// return
	if (i == size)
		return 0;
	// If the item is too big to fill the
	// remaining space, skip it
	if (W - items[i].weight < 0)
		return knapsack(items, W, i+1,size);
	// Find the maximum of including and not
	// including the current item
	return max( knapsack(items, W - items[i].weight, i+1,size)+ items[i].value,knapsack(items, W, i+1,size));
}

// Naive brute force solution. Recursively
// include or exclude each item to try every
// possible combination
int knapsack(Item items[], int W,int size)
{

	return knapsack(items, W, 0, size);
}


int main()
{









	return 0;
}
