/*
 ============================================================================
 Name        : int_links.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define Itemtype int
struct Node
{
	Itemtype data;
	struct Node *next;

};
typedef enum{FAILURE,SUCCESS} status_code;

struct Node * CreateNode(Itemtype data )
{
	struct Node *ptr;
	ptr=(struct Node *)malloc(sizeof(struct Node));
	ptr->data=data;
	ptr->next=NULL;
	return ptr;
}

void Traverse(struct Node *lptr)
{
	struct Node *ptr;
	ptr=lptr;
	while(ptr !=NULL)
	{
		printf("%d",ptr->data);
		ptr=ptr->next;
	}
}

struct Node * Takeno(struct Node * lptr)
{
	struct Node  *ptr;
	ptr=NULL;
	printf("Enter the no (digit by digit) and enter -1 for stop");
	int a;
	do
	{
		scanf("%d",&a);
		ptr=CreateNode(a);
		if(a!=-1)
		{
			ptr->next=lptr;
			lptr=ptr;
		}
	}while(a!=-1);
	return lptr;
}
struct Node * Reverse(struct Node *lptr)
{
	if(lptr==NULL || lptr->next==NULL)
	{
		return lptr;
	}
	struct Node * head=Reverse(lptr->next);

	lptr->next->next=lptr;

	lptr->next=NULL;
	return head;
}
struct Node* Add(struct Node* first, struct Node* second)
{
    struct Node* res = NULL;
    struct Node *temp, *prev = NULL;
    int carry = 0, sum;

    while (first != NULL || second != NULL)
    {
        sum = carry + (first? first->data: 0) + (second? second->data: 0);


        carry = (sum >= 10)? 1 : 0;

        sum = sum % 10;

        temp = CreateNode(sum);

        if(res == NULL)
            res = temp;
        else
            prev->next = temp;

        prev  = temp;

        if (first) first = first->next;
        if (second) second = second->next;
    }

    if (carry > 0)
      temp->next = CreateNode(carry);

    return res;
}
struct Node * Sub(struct Node * a,struct Node * b)
{
	int diff,borrow=0;
	struct Node *ptr,*sub=NULL;
	ptr=NULL;
	sub=NULL;
	while(a!=NULL && b!=NULL)
	{
		diff = (a->data-borrow-b->data);
		if(diff<0)
		{
			diff = diff+10;
			borrow=1;
		}
		else
		{
			borrow=0;
		}
		a=a->next;
		b=b->next;
		ptr=CreateNode(diff);
		ptr->next=sub;
		sub=ptr;
	}
	while(a!=NULL)
	{
		diff = a->data-borrow;
		if(diff<0)
		{
			diff = diff+10;
			borrow=1;
		}
		else
		{
			borrow=0;
		}
		a=a->next;
		ptr=CreateNode(diff);
		ptr->next=sub;
		sub=ptr;
	}

	return sub;
}
struct Node * Dcr(struct Node * a)
{
	struct Node * ptr;
	ptr=CreateNode(1);
	a=Sub(a,ptr);




	return a;
}
struct Node * Inr(struct Node * a)
{
	struct Node * ptr;
	ptr=CreateNode(1);
	a=Add(a,ptr);



	return a;
}
int main(void)
{
	struct Node *no1,*no2,*sum,*sub,*inrno1,*inrno2,*dcrno1,*dcrno2;
	printf("***First no entered should be bigger than SECOND no***\n\n");
	no1=NULL;
	no2=NULL;

	printf("Enter the first no\n");
	no1=Takeno(no1);
	printf("Enter the second no\n");
	no2=Takeno(no2);


	sum=Add(no1,no2);
	sub=Sub(no1,no2);
	inrno1=Inr(no1);
	inrno2=Inr(no2);
	dcrno1=Dcr(no1);
	dcrno2=Dcr(no2);


	printf("the no1 entered is:\n");
	Traverse(Reverse(no1));
	printf("\n");
	printf("the no2 entered is1:\n");
	Traverse(Reverse(no2));
	printf("\n");
	printf("SUM OF NO IS:\n");
	Traverse(Reverse(sum));
	printf("\nSUB OF NO IS:\n");
	Traverse(Reverse(sub));

	printf("\nINCREMENT OF NO1 IS:\n");
	Traverse(Reverse(inrno1));
	printf("\nINCREMENT OF NO2 IS:\n");
	Traverse(Reverse(inrno2));

	printf("\nDECREMENT OF NO1 IS:\n");
	Traverse((dcrno1));
	printf("\nDECREMENT OF NO2 IS:\n");
	Traverse((dcrno2));


	return 0;
}
