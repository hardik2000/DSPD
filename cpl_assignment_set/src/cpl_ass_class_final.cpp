//============================================================================
// Name        : cpl_assignment_set.cpp
// Author      : Hardik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#define MAX  5
using namespace std;
typedef enum{FAILURE,SUCCESS}status_code;

typedef struct Node_tag // structure definition to store words in set
{
	string str;
	struct Node_tag *next;
}Node;

Node *CreateNode(string str)	//creates new link list with user given string
{
	Node* ptr;
	ptr=(Node*)malloc(sizeof(Node));
	ptr->next=NULL;
	ptr->str=str;
	return ptr;
}

Node *InsertNode(Node *head,string str)		//insertion at start in O(1)
{
	Node *ptr;
	ptr = CreateNode(str);
	ptr->next=head;
	head=ptr;
	return head;
}

status_code DeleteNode(Node **head, string str)   //searches for string and delete it if it exist
{
    status_code sc = FAILURE;
    Node *lptr,*prev,*curr;
    lptr=*head;
    if(lptr!=NULL)
    {
    	prev = NULL;
    	curr = lptr;
    	bool found = false;
    	while(curr!=NULL && !found)
    	{
    		if(str.compare(curr->str)==0)
    		{
    			sc = SUCCESS;
    			found = true;
    			if(prev==NULL)
    			{
    				lptr=lptr->next;
    				//free(curr);
    			}
    			else
    			{
    				prev->next = curr->next;
    				//free(curr);
    			}
    		}
            else
            {
            	prev = curr;
            	curr = curr->next;
            }
    	}
    }
    *head=lptr;
    return sc;
}
void PrintList(Node *head)    //print the data of the link list
{
    Node *lptr = head;
    cout<<"\n";
    while(lptr!=NULL)
    {
        cout<<lptr->str;
        cout<<"\n";
        lptr = lptr->next;
    }
}

int HashFunction(string str)	//hash function s[0]+s[1]*x+s[2]*x*x+......
{
	int retval=0;
	int p = 31;
	long long int p_pow = 1L;
	for(int i=0;i<(int)str.length();i++)
	{
		retval = (retval + ((str[i] - '0' + 1) * p_pow) % MAX ) % MAX;
		p_pow = (p_pow * p) % MAX;
	}
	return retval;
}



class Set
{
	public:
		Node *list[MAX];
		int size;

		bool is_element_of(string x)   //checks whether the value of x is in Set S
		{
			bool retval = false;
			if(this!=NULL)
			{
				int index = HashFunction(x);
				Node *lptr = this->list[index];
				while(lptr!=NULL && !retval)
				{
					if(x.compare(lptr->str) == 0)
						retval = true;
					lptr = lptr->next;
				}
			}
			else
			{
				cout<<"INITIALISE SET\n";
			}
		    return retval;
		}
		bool is_empty_set()       //checks whether the set S is empty
		{
			bool retval = true;
		    if(this!=NULL)
		    {
				for(int i=0;i<MAX && retval;i++)
				{
					if(this->list[i] != NULL)
						retval = false;
				}
		    }
		    else
		    {
		    	cout<<"INITIALISE SET\n";
		    }
		    return retval;
		}

		int cardinality()		//returns the number of elements in S
		{
			int retval=0;
			if(this!=NULL)
			{
				retval=this->size;
			}
			else
			{
				cout<<"INITIALISE SET\n";
				retval=-1;
			}
			return retval;
		}

		Node *enumerate()     //returns a list containing the elements of S in some arbitrary order
		{
			Node *lptr = NULL;
			if(this!=NULL)
			{
				Node *iptr;
				for(int i=0;i<MAX;i++)
				{
					iptr = this->list[i];
					while(iptr!=NULL)
					{
						lptr = InsertNode(lptr,iptr->str);
						iptr = iptr->next;
					}
				}
			}
			else
			{
				cout<<"INITIALISE SET\n";
			}
			return lptr;

		}

		void Init_Set()       //initializes set
		{
		    for(int i=0;i<MAX;i++)
		    {
		        this->list[i] = NULL;
		    }
		    this->size = 0;
		}

		void add(string x)    //adds the element x to S,if it is not present already
		{
			if(this!=NULL)
			{
				int index;
				if(!this->is_element_of(x))
				{
					index = HashFunction(x);
					this->list[index] = InsertNode(this->list[index], x);
					this->size += 1;
				}
			}
			else
			{
				cout<<"INITIALISE SET\n";
			}
		}

		void remove(string x)     //removes a string x from set S,if it is present
		{
			if(this!=NULL)
			{	int index;
				index = HashFunction(x);
				status_code sc = DeleteNode(&(this->list[index]),x);
				if(sc == SUCCESS)
					this->size -= 1;
			}
			else
			{
				cout<<"INITIALISE SET\n";
			}
		}
		Set* union_set(Set* T)    //returns the union of set S and T
		{
			Set* temp=new Set();
			for(int i=0;i<MAX;i++)
		    {
		        Node *lptr = this->list[i];
		        while(lptr!=NULL)
		        {
		            temp->add(lptr->str);
		            lptr = lptr->next;
		        }
		    }
			for(int i=0;i<MAX;i++)
		    {
		        Node *lptr = T->list[i];
		        while(lptr!=NULL)
		        {
		            temp->add(lptr->str);
		            lptr = lptr->next;
		        }
		    }
		    return temp;
		}

		Set* intersection(Set* T)    //returns the intersection of two sets
		{
		    Set* temp=new Set();
		    temp->Init_Set();
		    for(int i=0;i<MAX;i++)
		    {
		        Node *lptr = this->list[i];
		        while(lptr!=NULL)
		        {
		            if(T->is_element_of(lptr->str))
		            {
		                temp->add(lptr->str);
		            }
		            lptr = lptr->next;
		        }
		    }
		    return temp;
		}

		Set* difference(Set* T)   //returns the difference of set S and T
		{
			Set* temp=new Set();
			for(int i=0;i<MAX;i++)
		    {
		        Node *lptr = this->list[i];
		        while(lptr!=NULL)
		        {
		            temp->add(lptr->str);
		            lptr = lptr->next;
		        }
		    }
			for(int i=0;i<MAX;i++)
		    {
		        Node *lptr = T->list[i];
		        while(lptr!=NULL)
		        {
		            temp->remove(lptr->str);
		            lptr = lptr->next;
		        }
		    }
		    return temp;
		}

		bool subset(Set* T)      //a predicate that tests whether the set S is a subset of set T
		{
		    bool retval = true;
		    Node *lptr;
		    if(this->size > T->size)
		        retval = false;
		    else
		    {
		        for(int i=0;i<MAX && retval;i++)
		        {
		            lptr = this->list[i];
		            while(lptr!=NULL && retval)
		            {
		                if(!T->is_element_of(lptr->str))
		                    retval = false;
		                lptr = lptr->next;
		            }
		        }
		    }
		    return retval;
		}

		void DisplaySet()    //displays the whole set
		{
		    for(int i=0;i<MAX;i++)
		    {
		    	cout<<i;
		    	cout<<")";
		        Node *lptr = this->list[i];
		        while(lptr!=NULL)
		        {
		            cout<<lptr->str<<"->";
		            lptr = lptr->next;
		        }
		        cout<<"\n";
		    }
		    cout<<"size:"<<this->size<<"\n";
		}

};


Set* create()           //creates a new,initially empty set structure
{
	Set* S =new Set();
	S->Init_Set();
	return S;
}

Set* build(string s[],int n)       //given an array of strings, a set is built from those elements
{
    Set* S;
    S=create();
    for(int i=0;i<n;i++)
    {
         S->add(s[i]);
    }
    return S;
}


int main()
{
	Set *S,*T;
	S=NULL;
	T=NULL;
	int opt;
	string ch,input;
	do
	{
		cout<<"Select option :\n";
		cout<<"0)create set\n";
		cout<<"1)checks whether the value x is in the set.\n";
		cout<<"2)checks whether the set is empty.\n";
		cout<<"3)know the number of elements.\n";
		cout<<"4)enumerate the set.\n";
		cout<<"5)creates a set structure with values x1,x2,…,\n";
		cout<<"6)adds the element x to set,if it is not present already\n";
		cout<<"7)removes the element x from set, if it is present\n";
		cout<<"8)Union\n";
		cout<<"9)Intersection\n";
		cout<<"10)difference\n";
		cout<<"11)Subset\n";
		cout<<"12)Display whole set\n";
		cin>>opt;
		switch(opt)
		{
			case 0:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					S=create();
				}
				else
				{
					T=create();
				}
				break;
			}
			case 1:
			{
				printf("ENTER THE STRING TO CHECK:\n");
				string x;
				cin>>x;
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					if(S->is_element_of(x))
					{
						cout<<x+" IS ELEMENT OF THE SET \n";
					}
					else
					{
						cout<<x+" IS NOT THE ELEMENT OF THE SET \n";
					}
				}
				else
				{
					if(T->is_element_of(x))
					{
						cout<<x+" IS ELEMENT OF THE SET \n";
					}
					else
					{
						cout<<x+" IS NOT THE ELEMENT OF THE SET \n";
					}
				}
				break;
			}
			case 2:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					if(S->is_empty_set())
					{
						cout<<"THE SET IS EMPTY\n";
					}
					else
					{
						cout<<"THE SET IS NOT EMPTY\n";
					}
				}
				else
				{

					if(T->is_empty_set())
					{
						cout<<"THE SET IS EMPTY\n";
					}
					else
					{
						cout<<"THE SET IS NOT EMPTY\n";
					}
				}
				break;
			}
			case 3:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					cout<<"SIZE OF THE SET IS :	";
					cout<<S->cardinality();
					cout<<"\n";
				}
				else
				{
					cout<<"SIZE OF THE SET IS :	";
					cout<<T->cardinality();
					cout<<"\n";
				}
				break;
			}
			case 4:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					Node *lptr;
					lptr=S->enumerate();
					cout<<"THE ELEMENTS OF SET ARE:\n";
					if(lptr!=NULL)
					{
						PrintList(lptr);
					}
					else
					{
						cout<<"NO ELEMENT EXIST\n";
					}
				}
				else
				{
					Node *lptr;
					lptr=T->enumerate();
					cout<<"THE ELEMENTS OF SET ARE:\n";
					if(lptr!=NULL)
					{
						PrintList(lptr);
					}
					else
					{
						cout<<"NO ELEMENT EXIST\n";
					}
				}

				break;
			}
			case 5:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					int x;
					cout<<"ENTER THE NO OF STRING U WANT TO ENTER\n";
					cin>>x;
					string str[x];
					cout<<"ENTER THE STRINGS U WANT TO ENTER:";
					for(int i=0;i<x;i++)
					{
						cin>>str[i];
					}
					S=build(str,x);
					cout<<"SET CREATED S WITH NEW VALUE\nUSE ENUMERATE OPTION TO KNOW THE CONTENT\n";
				}
				else
				{
					int x;
					cout<<"ENTER THE NO OF STRING U WANT TO ENTER\n";
					cin>>x;
					string str[x];
					cout<<"ENTER THE STRINGS U WANT TO ENTER:";
					for(int i=0;i<x;i++)
					{
						cin>>str[i];
					}
					T=build(str,x);
					cout<<"SET CREATED T WITH NEW VALUE\nUSE ENUMERATE OPTION TO KNOW THE CONTENT\n";
				}

				break;
			}
			case 6:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					string str;
					cout<<"ENTER THE STRINGS U WANT TO ENTER:";
					cin>>str;
					S->add(str);
					cout<<"ELEMENT ADDED\n";
				}
				else
				{
					string str;
					cout<<"ENTER THE STRINGS U WANT TO ENTER:";
					cin>>str;
					T->add(str);
					cout<<"ELEMENT ADDED\n";
				}
				break;
			}
			case 7:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					string str;
					cout<<"ENTER THE STRINGS U WANT TO ENTER:";
					cin>>str;
					S->remove(str);
					cout<<"ELEMENT DELETED\n";

				}
				else
				{
					string str;
					cout<<"ENTER THE STRINGS U WANT TO ENTER:";
					cin>>str;
					T->remove(str);
					cout<<"ELEMENT DELETED\n";
				}
				break;
			}
			case 8:
			{
				if(S==NULL || T==NULL)
				{
					cout<<"INITIALISE SET'S\n";
				}
				else
				{
					Set* temp=S->union_set(T);
					Node *lptr;
					lptr=temp->enumerate();
					cout<<"THE ELEMENTS OF SET ARE:\n";
					if(lptr!=NULL)
					{
						PrintList(lptr);
					}
					else
					{
						cout<<"NO ELEMENT EXIST\n";
					}
				}
				break;
			}
			case 9:
			{
				if(S==NULL || T==NULL)
				{
					cout<<"INITIALISE SET'S\n";
				}
				else
				{
					Set* temp=S->intersection(T);
					Node *lptr;
					lptr=temp->enumerate();
					cout<<"THE ELEMENTS OF SET ARE:\n";
					if(lptr!=NULL)
					{
						PrintList(lptr);
					}
					else
					{
						cout<<"NO ELEMENT EXIST\n";
					}
				}
				break;
			}
			case 10:
			{
				if(S==NULL || T==NULL)
				{
					cout<<"INITIALISE SET'S\n";
				}
				else
				{
					Set* temp=S->difference(T);
					Node *lptr;
					lptr=temp->enumerate();
					cout<<"THE ELEMENTS OF SET ARE:\n";
					if(lptr!=NULL)
					{
						PrintList(lptr);
					}
					else
					{
						cout<<"NO ELEMENT EXIST\n";
					}
				}
				break;
			}
			case 11:
			{
				if(S==NULL || T==NULL)
				{
					cout<<"INITIALISE SET'S\n";
				}
				else
				{	if(S->subset(T))
						cout<<"SET S IS THE SUBSET OF SET T\n";
					else
						cout<<"SET S IS NOT THE SUBSET OF SET T\n";
				}
				break;
			}
			case 12:
			{
				cout<<"IN WHICH SET U WANT TO CHECK(S/T)\n";
				cin>>input;
				if(!input.compare("S") || !input.compare("s"))
				{
					if(S!=NULL)
					{
						S->DisplaySet();
					}
					else
					{
						cout<<"INITIALISE SET S\n";
					}
				}
				else
				{
					if(T!=NULL)
					{
						T->DisplaySet();
					}
					else
					{
						cout<<"INITIALISE SET T\n";
					}
				}
				break;
			}
			default:
			{
				cout<<"!!!!!!INVALID ENTRY----ENTER AGAIN!!!!!!\n";
			}

		}
		cout<<"DO YOU WANT TO CONTINUE(Y/N)\n";
		cin>>ch;
	}while(!ch.compare("Y") || !ch.compare("y"));


	return 0;
}
