/*
 ============================================================================
 Name        : DSPD_LINKEDLIST.c
 Author      : Hardik
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

#define compact_spot 60
#define large_spot 40

int N_RECORD=74;

typedef struct Node_parking_Spot
{
	char Parking_level;
	char Dedicated_wing;
	int type;
	int location;

}parking_spot;

struct Node_Parking
{
	char Parking_level;
	char Dedicated_wing;
	int no_of_compact_spot;
	int no_of_large_spot;
	int *status_compact_spot;
	int *status_large_spot;

	struct Node_Parking * next;

};


struct Node_Vehicle
{
	int type;							//can have only two values(2 for two wheelers and 4 for 4 wheelers)
	char no[15];
	int alloc;
	parking_spot spot;
	struct Node_Vehicle *next;
};


struct Node_Flat
{
	char wing_id[2];
	int flat_id;
	int no_of_two_wheelers;
	int no_of_four_wheelers;
	struct Node_Vehicle * vehicle;
	struct Node_Flat *next;
};

//void Read_Details_Console()
//{
//	struct Node_Flat flat;
//	char flag[3];
//	FILE *fptr = fopen("data_flat.txt", "w");
//	if (fptr == NULL)
//	{
//		printf("Could not open file");
//	}
//	else
//	{
//		do
//		{
//			printf("PLEASE ENTER THE FOLLOWING DETAILS OF THE FLATS :\n");
//			fflush(stdin);
//
//			printf("WING-ID (A/B/C) :");
//			scanf("%s",flat.wing_id);
//			fprintf(fptr,"%s\n",flat.wing_id);
//
//			printf("\nFLAT-ID :");
//			scanf("%d",&flat.flat_id);
//			fprintf(fptr,"%d\n",flat.flat_id);
//
//			printf("\nNO OF TWO WHEELERS :");
//			scanf("%d",&flat.no_of_two_wheelers);
//			fprintf(fptr,"%d\n",flat.no_of_two_wheelers);
//
//			printf("\nNO OF FOUR WHEELERS :");
//			scanf("%d",&flat.no_of_four_wheelers);
//			fprintf(fptr,"%d\n",flat.no_of_four_wheelers);
//			flat.vehicle=(struct Node_Vehicle *)malloc(sizeof(struct Node_Vehicle));
//
//			for(int i=0;i<(flat.no_of_two_wheelers);i++)
//			{
//				printf("\nPLEASE ENTER YOUR TWO WHEELER VEHICLE DETAILS %d :\n",i+1);
//				printf("TYPE : %d",2);
//				flat.vehicle->type=2;
//				fprintf(fptr,"%d\n",flat.vehicle->type);
//				printf("\nNUMBER :");
//				scanf("%s",flat.vehicle->no);
//				fprintf(fptr,"%s\n",flat.vehicle->no);
//				flat.vehicle->next=NULL;
//			}
//			for(int i=0;i<(flat.no_of_four_wheelers);i++)
//			{
//				printf("\nPLEASE ENTER YOUR FOUR WHEELER VEHICLE DETAILS %d :\n",i+1);
//				printf("TYPE : %d",4);
//				flat.vehicle->type=4;
//				fprintf(fptr,"%d\n",flat.vehicle->type);
//				printf("\nNUMBER :");
//				scanf("%s",flat.vehicle->no);
//				fprintf(fptr,"%s\n",flat.vehicle->no);
//				flat.vehicle->next=NULL;
//			}
//			N_RECORD++;
//			printf("DO YOU WANT TO ENTER MORE RECORDS (Y/N) : \n");
//			scanf("%s",flag);
//			fflush(stdin);
//		}while(!strcmp(flag,"Y") || !strcmp(flag,"y"));
//
//		printf("THANKS FOR ENTERING DATA YOUR WORK IS IMPORTANT \n");
//	}
//	fclose(fptr);
//
//
//}
struct Node_Flat * Read_Details_File()
{
	struct Node_Flat *Flat_Head,*Flat_Last,*flat;
	Flat_Head=NULL;
	Flat_Last=NULL;
	struct Node_Vehicle *temp_vehicle;


	FILE *fptr = fopen("data_flat.txt", "r");
	if (fptr == NULL)
	{
		printf("NO SUCH FILE EXIST :");
	}
	else
	{
		for(int j=0;j<N_RECORD;j++)
		{
			flat=(struct Node_Flat *)malloc(sizeof(struct Node_Flat));
			fscanf(fptr,"%s",flat->wing_id);

			fscanf(fptr,"%d",&flat->flat_id);

			fscanf(fptr,"%d",&flat->no_of_two_wheelers);

			fscanf(fptr,"%d",&flat->no_of_four_wheelers);

			flat->next=NULL;
			flat->vehicle=NULL;

			for(int i=0;i<(flat->no_of_two_wheelers);i++)
			{
				temp_vehicle=(struct Node_Vehicle *)malloc(sizeof(struct Node_Vehicle));
				fscanf(fptr,"%d",&temp_vehicle->type);
				fscanf(fptr,"%s",temp_vehicle->no);
				temp_vehicle->next=flat->vehicle;
				flat->vehicle=temp_vehicle;
				temp_vehicle->alloc=0;
			}

			for(int i=0;i<(flat->no_of_four_wheelers);i++)
			{
				temp_vehicle=(struct Node_Vehicle *)malloc(sizeof(struct Node_Vehicle));
				fscanf(fptr,"%d",&temp_vehicle->type);

				fscanf(fptr,"%s",temp_vehicle->no);

				temp_vehicle->next=flat->vehicle;
				flat->vehicle=temp_vehicle;
				temp_vehicle->alloc=0;

			}

			if(j==0)
			{
				Flat_Head=flat;
				Flat_Last=flat;
				flat->next=NULL;
			}
			else
			{
				Flat_Last->next=flat;
				Flat_Last=flat;
			}
		}

	}
	fclose(fptr);

	return Flat_Head;

}
struct Node_Parking * Initialise(struct Node_Parking *parking_head)
{
	struct Node_Parking *temp;
	temp=(struct Node_Parking *)malloc(sizeof(struct Node_Parking));
	temp->Parking_level='C';
	temp->Dedicated_wing='C';
	temp->no_of_compact_spot=compact_spot;
	temp->no_of_large_spot=large_spot;
	temp->status_compact_spot=(int *)malloc(sizeof(int)*compact_spot);
	for(int i=0;i<compact_spot;i++)
	{
		temp->status_compact_spot[i]=0;
	}
	temp->status_large_spot=(int *)malloc(sizeof(int)*large_spot);
	for(int i=0;i<large_spot;i++)
	{
		temp->status_large_spot[i]=0;
	}
	temp->next=parking_head;
	parking_head=temp;


	temp=(struct Node_Parking *)malloc(sizeof(struct Node_Parking));
	temp->Parking_level='B';
	temp->Dedicated_wing='B';
	temp->no_of_compact_spot=compact_spot;
	temp->no_of_large_spot=large_spot;
	temp->status_compact_spot=(int *)malloc(sizeof(int)*compact_spot);
	for(int i=0;i<compact_spot;i++)
	{
		temp->status_compact_spot[i]=0;
	}
	temp->status_large_spot=(int *)malloc(sizeof(int)*large_spot);
	for(int i=0;i<large_spot;i++)
	{
		temp->status_large_spot[i]=0;
	}
	temp->next=parking_head;
	parking_head=temp;

	temp=(struct Node_Parking *)malloc(sizeof(struct Node_Parking));
	temp->Parking_level='A';
	temp->Dedicated_wing='A';
	temp->no_of_compact_spot=compact_spot;
	temp->no_of_large_spot=large_spot;
	temp->status_compact_spot=(int *)malloc(sizeof(int)*compact_spot);
	for(int i=0;i<compact_spot;i++)
	{
		temp->status_compact_spot[i]=0;
	}
	temp->status_large_spot=(int *)malloc(sizeof(int)*large_spot);
	for(int i=0;i<large_spot;i++)
	{
		temp->status_large_spot[i]=0;
	}
	temp->next=parking_head;
	parking_head=temp;

	parking_head->next->next->next=parking_head;

	return parking_head;
}
struct Node_Parking * reset_status(struct Node_Parking * parking_lot)
{
	struct Node_Parking * temp_parking;
	temp_parking=parking_lot;
	do
	{
		for(int i=0;i<compact_spot;i++)
		{
			temp_parking->status_compact_spot[i]=0;
		}
		for(int i=0;i<large_spot;i++)
		{
				temp_parking->status_large_spot[i]=0;
		}
		temp_parking=temp_parking->next;

	}while(temp_parking!=parking_lot);
	return parking_lot;
}

struct Node_Flat * Map_Flat_VehicleNo_Parkingspot(struct Node_Parking *Parking_Lot,struct Node_Flat *Flat_Details)
{
	struct Node_Parking *temp_parking;
	struct Node_Flat *temp_flat;
	struct Node_Vehicle *temp_vehicle;
	temp_parking=Parking_Lot;
	temp_flat=Flat_Details;
	//int done=0;
	while(temp_flat!=NULL)
	{
		if(!strcmp(temp_flat->wing_id,"A"))
		{
			temp_parking=Parking_Lot;
		}
		else if(!strcmp(temp_flat->wing_id,"B"))
		{
			temp_parking=Parking_Lot->next;
		}
		else if (!strcmp(temp_flat->wing_id,"C"))
		{
			temp_parking=Parking_Lot->next->next;
		}

		temp_vehicle=temp_flat->vehicle;
		int car;
		car=0;
		while(temp_vehicle!=NULL)
		{
			if(temp_vehicle->type==2)
			{
				int flag=0;
				for(int i=0;i<compact_spot && flag==0;i++)
				{
					if(temp_parking->status_compact_spot[i]==0)
					{
						temp_parking->status_compact_spot[i]=1;
						flag=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;
					}
				}
				if(flag==0)
				{
					for(int i=0;i<compact_spot && flag==0;i++)
					{
						if(temp_parking->next->status_compact_spot[i]==0)
						{
							temp_parking->next->status_compact_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=2;
							temp_vehicle->alloc=1;
						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<compact_spot && flag==0;i++)
					{
						if(temp_parking->next->next->status_compact_spot[i]==0)
						{
							temp_parking->next->next->status_compact_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=2;
							temp_vehicle->alloc=1;
						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<large_spot && flag==0;i++)
					{
						if(temp_parking->status_large_spot[i]==0)
						{
							temp_parking->status_large_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;

						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<large_spot && flag==0;i++)
					{
						if(temp_parking->next->status_large_spot[i]==0)
						{
							temp_parking->next->status_large_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;

						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<large_spot && flag==0;i++)
					{
						if(temp_parking->next->next->status_large_spot[i]==0)
						{
							temp_parking->next->next->status_large_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;

						}
					}
				}
			}
			else if(temp_vehicle->type==4)
			{
				int flag=0;
				if(car==0)
				{
					for(int i=0;i<large_spot && flag==0;i++)
					{
						if(temp_parking->status_large_spot[i]==0)
						{
							temp_parking->status_large_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;
							car=1;
						}
					}
				}
				if(flag==0)
				{
					//temp_parking=temp_parking->next;
					for(int i=0;i<large_spot && flag==0;i++)
					{
						if(temp_parking->next->status_large_spot[i]==0)
						{
							temp_parking->next->status_large_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;
							if(car==0)
							{
								car=1;
							}
						}
					}
				}
				if(flag==0)
				{
				//	temp_parking=temp_parking->next;
					for(int i=0;i<large_spot && flag==0;i++)
					{
						if(temp_parking->next->next->status_large_spot[i]==0)
						{
							temp_parking->next->next->status_large_spot[i]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;
							if(car==0)
							{
								car=1;
							}
						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<compact_spot-1 && flag==0;i++)
					{
						if(temp_parking->status_compact_spot[i]==0  && temp_parking->status_compact_spot[i+1]==0)
						{
							temp_parking->status_compact_spot[i]=1;
							temp_parking->status_compact_spot[i+1]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=2;
							temp_vehicle->alloc=1;
							if(car==0)
							{
								car=1;
							}
						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<compact_spot-1 && flag==0;i++)
					{
						if(temp_parking->next->status_compact_spot[i]==0 && temp_parking->next->status_compact_spot[i+1]==0)
						{
							temp_parking->next->status_compact_spot[i]=1;
							temp_parking->next->status_compact_spot[i+1]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=2;
							temp_vehicle->alloc=1;
							if(car==0)
							{
								car=1;
							}
						}
					}
				}
				if(flag==0)
				{
					for(int i=0;i<compact_spot-1 && flag==0;i++)
					{
						if(temp_parking->next->next->status_compact_spot[i]==0 && temp_parking->next->next->status_compact_spot[i+1]==0)
						{
							temp_parking->next->next->status_compact_spot[i]=1;
							temp_parking->next->next->status_compact_spot[i+1]=1;
							flag=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=2;
							temp_vehicle->alloc=1;
							if(car==0)
							{
								car=1;
							}
						}
					}
				}

			}
			temp_vehicle=temp_vehicle->next;
		}

		temp_flat=temp_flat->next;
	}


	return Flat_Details;
}


struct Node_Parking * Park_Vehicle(struct Node_Parking *Parking_Lot,struct Node_Flat *Flat_Details)
{
	char no[15];
	char owner[10];
	int type=-1;
	parking_spot spot;
	spot.Dedicated_wing='Z';
	spot.Parking_level='Z';
	spot.location=-1;
	spot.type=-1;
	printf("PLEASE ENTER THE NUMBER OF VEHICLE TO PARK : \n");
	scanf("%s",no);

	struct Node_Flat *temp_flat;
	struct Node_Vehicle *temp_vehicle;
	struct Node_Parking *temp_parking;
	temp_flat=Flat_Details;
	int found=0,flag=0;
	while(temp_flat!=NULL && flag==0)
	{
		temp_vehicle=temp_flat->vehicle;
		while(temp_vehicle!=NULL && flag==0)
		{
			if(!strcmp(temp_vehicle->no,no))
			{
					flag=1;
			}
			if(flag==0)
			{
				temp_vehicle=temp_vehicle->next;
			}
		}
		if(flag==0)
		{
			temp_flat=temp_flat->next;
		}

	}
	//if(flag)
	//temp_vehicle contains found vehicle
	//temp_flat contains found flat
	//else
	//temp_vehicle=NULL;
	//temp_flat==NULL;
	if(flag==1)
	{
		found=0;
		strcpy(owner,"insider");
		//if(check whether found spot is empty or not if not empty then found another spot

		//temp_vehicle->spot.Parking_level,temp_vehicle->spot.type,temp_vehicle->spot.location;
		type=temp_vehicle->type;
		temp_parking=Parking_Lot;

		//printf("%c %c %c\n",temp_parking->Parking_level,temp_parking->next->Parking_level,temp_parking->next->next->Parking_level);
		if(temp_parking->Parking_level==temp_vehicle->spot.Parking_level)
		{

			if(type==2)
			{
				if(temp_vehicle->spot.type==2)
				{
					if(temp_parking->status_compact_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_compact_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=2;
						spot.location=temp_vehicle->spot.location;
					}
				}
				else
				{
					if(temp_parking->status_large_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_large_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=4;
						spot.location=temp_vehicle->spot.location;
					}
				}
			}
			else
			{
				if(temp_vehicle->spot.type==2)
				{
					if(temp_parking->status_compact_spot[temp_vehicle->spot.location-1]==0 && temp_parking->status_compact_spot[temp_vehicle->spot.location]==0)
					{
						temp_parking->status_compact_spot[temp_vehicle->spot.location-1]=1;
						temp_parking->status_compact_spot[temp_vehicle->spot.location]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=2;
						spot.location=temp_vehicle->spot.location;
					}
				}
				else
				{
					if(temp_parking->status_large_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_large_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=4;
						spot.location=temp_vehicle->spot.location;
					}
				}
			}


		}
		else if(temp_parking->next->Parking_level==temp_vehicle->spot.Parking_level)
		{

			if(type==2)
			{
				if(temp_vehicle->spot.type==2)
				{
					if(temp_parking->status_compact_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_compact_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=2;
						spot.location=temp_vehicle->spot.location;
					}
				}
				else
				{
					if(temp_parking->status_large_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_large_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=4;
						spot.location=temp_vehicle->spot.location;
					}
				}
			}
			else
			{
				if(temp_vehicle->spot.type==2)
				{
					if(temp_parking->status_compact_spot[temp_vehicle->spot.location-1]==0 && temp_parking->status_compact_spot[temp_vehicle->spot.location]==0)
					{
						temp_parking->status_compact_spot[temp_vehicle->spot.location-1]=1;
						temp_parking->status_compact_spot[temp_vehicle->spot.location]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=2;
						spot.location=temp_vehicle->spot.location;
					}
				}
				else
				{
					if(temp_parking->status_large_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_large_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=4;
						spot.location=temp_vehicle->spot.location;
					}
				}
			}


		}
		else if(temp_parking->next->next->Parking_level==temp_vehicle->spot.Parking_level)
		{

			if(type==2)
			{
				if(temp_vehicle->spot.type==2)
				{
					if(temp_parking->status_compact_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_compact_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=2;
						spot.location=temp_vehicle->spot.location;
					}
				}
				else
				{
					if(temp_parking->status_large_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_large_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=4;
						spot.location=temp_vehicle->spot.location;
					}
				}
			}
			else
			{
				if(temp_vehicle->spot.type==2)
				{
					if(temp_parking->status_compact_spot[temp_vehicle->spot.location-1]==0 && temp_parking->status_compact_spot[temp_vehicle->spot.location]==0)
					{
						temp_parking->status_compact_spot[temp_vehicle->spot.location-1]=1;
						temp_parking->status_compact_spot[temp_vehicle->spot.location]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=2;
						spot.location=temp_vehicle->spot.location;
					}
				}
				else
				{
					if(temp_parking->status_large_spot[temp_vehicle->spot.location-1]==0)
					{
						temp_parking->status_large_spot[temp_vehicle->spot.location-1]=1;
						found=1;
						spot.Parking_level=temp_vehicle->spot.Parking_level;
						spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
						spot.type=4;
						spot.location=temp_vehicle->spot.location;
					}
				}
			}



		}
		if(found==1)
		{	printf("ALLOCATED PARKING SPACE IS : \n");
			printf("PARKING LEVEL : %c\nPARKING SPOT TYPE: %d\nPARKING SPOT NO: %d\n",spot.Parking_level,spot.type,spot.location);
			//writting record in file
				FILE *fp = fopen("record.txt", "a");
				if (fp == NULL)
				{
					printf("NO SUCH FILE EXIST :");
				}
				else
				{
					time_t t;   // not a primitive datatype
					time(&t);

					fprintf(fp,"%s\n",owner);
					fprintf(fp,"%s",ctime(&t));
					fprintf(fp,"%s\n","IN");
					fprintf(fp,"%s\n",no);
					fprintf(fp,"%d\n",type);
					fprintf(fp,"%c\n",spot.Parking_level);
					fprintf(fp,"%d\n",spot.type);
					fprintf(fp,"%d\n",spot.location);

				}
				fclose(fp);


		}
		else
		{
			found=0;
			//if allocated parking space is not empty for insider vehicle temp_vehicle   && temp_flat
			if(!strcmp(temp_flat->wing_id,"A"))
			{
				temp_parking=Parking_Lot;
			}
			else if(!strcmp(temp_flat->wing_id,"B"))
			{
				temp_parking=Parking_Lot->next;
			}
			else if (!strcmp(temp_flat->wing_id,"C"))
			{
				temp_parking=Parking_Lot->next->next;
			}

			if(temp_vehicle->type==2)
			{
				for(int i=0;i<compact_spot && found==0;i++)
				{
					if(temp_parking->status_compact_spot[i]==0)
					{
						temp_parking->status_compact_spot[i]=1;
						found=1;
						spot.Dedicated_wing=temp_parking->Dedicated_wing;
						spot.Parking_level=temp_parking->Parking_level;
						spot.location=i+1;
						spot.type=2;

					}
				}
				if(found==0)
				{
					for(int i=0;i<compact_spot && found==0;i++)
					{
						if(temp_parking->next->status_compact_spot[i]==0)
						{
							temp_parking->next->status_compact_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->Dedicated_wing;
							spot.Parking_level=temp_parking->Parking_level;
							spot.location=i+1;
							spot.type=2;

						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<compact_spot && found==0;i++)
					{
						if(temp_parking->next->next->status_compact_spot[i]==0)
						{
							temp_parking->next->next->status_compact_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							spot.Parking_level=temp_parking->Parking_level;
							spot.location=i+1;
							spot.type=2;

						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<large_spot && found==0;i++)
					{
						if(temp_parking->status_large_spot[i]==0)
						{
							temp_parking->status_large_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->Dedicated_wing;
							spot.Parking_level=temp_parking->Parking_level;
							spot.location=i+1;
							spot.type=4;

						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<large_spot && found==0;i++)
					{
						if(temp_parking->next->status_large_spot[i]==0)
						{
							temp_parking->next->status_large_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							spot.Parking_level=temp_parking->next->Parking_level;
							spot.location=i+1;
							spot.type=4;
						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<large_spot && found==0;i++)
					{
						if(temp_parking->next->next->status_large_spot[i]==0)
						{
							temp_parking->next->next->status_large_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							spot.Parking_level=temp_parking->next->next->Parking_level;
							spot.location=i+1;
							spot.type=4;
						}
					}
				}
			}
			else if(temp_vehicle->type==4)
			{
				if(found==0)
				{
					for(int i=0;i<large_spot && found==0;i++)
					{
						if(temp_parking->status_large_spot[i]==0)
						{
							temp_parking->status_large_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->Dedicated_wing;
							spot.Parking_level=temp_parking->Parking_level;
							spot.location=i+1;
							spot.type=4;
						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<large_spot && found==0;i++)
					{
						if(temp_parking->next->status_large_spot[i]==0)
						{
							temp_parking->next->status_large_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							spot.Parking_level=temp_parking->next->Parking_level;
							spot.location=i+1;
							spot.type=4;
						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<large_spot && found==0;i++)
					{
						if(temp_parking->next->next->status_large_spot[i]==0)
						{
							temp_parking->next->next->status_large_spot[i]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							spot.Parking_level=temp_parking->next->next->Parking_level;
							spot.location=i+1;
							spot.type=4;

						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<compact_spot-1 && found==0;i++)
					{
						if(temp_parking->status_compact_spot[i]==0  && temp_parking->status_compact_spot[i+1]==0)
						{
							temp_parking->status_compact_spot[i]=1;
							temp_parking->status_compact_spot[i+1]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->Dedicated_wing;
							spot.Parking_level=temp_parking->Parking_level;
							spot.location=i+1;
							spot.type=2;
													}
					}
				}
				if(found==0)
				{
					for(int i=0;i<compact_spot-1 && found==0;i++)
					{
						if(temp_parking->next->status_compact_spot[i]==0 && temp_parking->next->status_compact_spot[i+1]==0)
						{
							temp_parking->next->status_compact_spot[i]=1;
							temp_parking->next->status_compact_spot[i+1]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
							spot.Parking_level=temp_parking->next->Parking_level;
							spot.location=i+1;
							spot.type=2;

						}
					}
				}
				if(found==0)
				{
					for(int i=0;i<compact_spot-1 && found==0;i++)
					{
						if(temp_parking->next->next->status_compact_spot[i]==0 && temp_parking->next->next->status_compact_spot[i+1]==0)
						{
							temp_parking->next->next->status_compact_spot[i]=1;
							temp_parking->next->next->status_compact_spot[i+1]=1;
							found=1;
							spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							spot.Parking_level=temp_parking->Parking_level;
							spot.location=i+1;
							spot.type=2;
						}
					}
				}
			}
			if(found==1)
			{

				printf("ALLOCATED PARKING SPACE IS : \n");
				printf("PARKING LEVEL : %c\nPARKING SPOT TYPE: %d\nPARKING SPOT NO: %d\n",spot.Parking_level,spot.type,spot.location);
				//writting record in file
					FILE *fp = fopen("record.txt", "a");
					if (fp == NULL)
					{
						printf("NO SUCH FILE EXIST :");
					}
					else
					{
						time_t t;   // not a primitive datatype
						time(&t);

						fprintf(fp,"%s\n",owner);
						fprintf(fp,"%s",ctime(&t));
						fprintf(fp,"%s\n","IN");
						fprintf(fp,"%s\n",no);
						fprintf(fp,"%d\n",type);
						fprintf(fp,"%c\n",spot.Parking_level);
						fprintf(fp,"%d\n",spot.type);
						fprintf(fp,"%d\n",spot.location);

					}
					fclose(fp);

			}
			else
			{
				printf("!!!!!!!!!!!!!!!  NO SAPACE LEFT !!!!!!!!!!!!!!!!!!1111\n");

			}
		}
	}
	else
	{
		found=0;
		strcpy(owner,"visitor");
		//search for a parking spot in 1 then 2 then 3
		//printf("%s",owner);
		//if vehicle is of outsider temp_vehicle && spot
//				fprintf(fp,"%c\n",spot.Parking_level);
//					fprintf(fp,"%d\n",spot.type);
//					fprintf(fp,"%d\n",spot.location);

		printf("GUEST VEHICLE DETECTED :\n");
		printf("GUEST PLEASE ENTER THE TYPE OF VEHICLE :(2/4)\n");
		do
		{
			scanf("%d",&type);
			if(!(type==2 || type==4))
			{
				printf("!!!!!!!!!!!!!!! INVALID OPTION ENTERED PLEASE ENTER AGAIN !!!!!!!!!!!!!!!!\n");
			}
		}while(!(type==2 || type==4));
		temp_parking=Parking_Lot;
		temp_vehicle=(struct Node_Vehicle *)malloc(sizeof(struct Node_Vehicle));

		if(type==2)
		{	if(found==0)
			{
				for(int i=0;i<compact_spot && found==0;i++)
				{
					if(temp_parking->status_compact_spot[i]==0)
					{
						temp_parking->status_compact_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;
					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<compact_spot && found==0;i++)
				{
					if(temp_parking->next->status_compact_spot[i]==0)
					{
						temp_parking->next->status_compact_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;
					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<compact_spot && found==0;i++)
				{
					if(temp_parking->next->next->status_compact_spot[i]==0)
					{
						temp_parking->next->next->status_compact_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;
					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<large_spot && found==0;i++)
				{
					if(temp_parking->status_large_spot[i]==0)
					{
						temp_parking->status_large_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=4;
						temp_vehicle->alloc=1;

					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<large_spot && found==0;i++)
				{
					if(temp_parking->next->status_large_spot[i]==0)
					{
						temp_parking->next->status_large_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=4;
						temp_vehicle->alloc=1;

					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<large_spot && found==0;i++)
				{
					if(temp_parking->next->next->status_large_spot[i]==0)
					{
						temp_parking->next->next->status_large_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->next->next->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=4;
						temp_vehicle->alloc=1;

					}
				}
			}
		}
		else if(type==4)
		{
			if(found==0)
			{
				for(int i=0;i<large_spot && found==0;i++)
				{
					if(temp_parking->status_large_spot[i]==0)
					{
						temp_parking->status_large_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=4;
						temp_vehicle->alloc=1;
					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<large_spot && found==0;i++)
				{
					if(temp_parking->next->status_large_spot[i]==0)
					{
						temp_parking->next->status_large_spot[i]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=4;
						temp_vehicle->alloc=1;

					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<large_spot && found==0;i++)
				{
						if(temp_parking->next->next->status_large_spot[i]==0)
						{
							temp_parking->next->next->status_large_spot[i]=1;
							found=1;
							temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
							temp_vehicle->spot.Parking_level=temp_parking->next->next->Parking_level;
							temp_vehicle->spot.location=i+1;
							temp_vehicle->spot.type=4;
							temp_vehicle->alloc=1;

						}
				}
			}
			if(found==0)
			{
				for(int i=0;i<compact_spot-1 && found==0;i++)
				{
					if(temp_parking->status_compact_spot[i]==0  && temp_parking->status_compact_spot[i+1]==0)
					{
						temp_parking->status_compact_spot[i]=1;
						temp_parking->status_compact_spot[i+1]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;

					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<compact_spot-1 && found==0;i++)
				{
					if(temp_parking->next->status_compact_spot[i]==0 && temp_parking->next->status_compact_spot[i+1]==0)
					{
						temp_parking->next->status_compact_spot[i]=1;
						temp_parking->next->status_compact_spot[i+1]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->next->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;

					}
				}
			}
			if(found==0)
			{
				for(int i=0;i<compact_spot-1 && found==0;i++)
				{
					if(temp_parking->next->next->status_compact_spot[i]==0 && temp_parking->next->next->status_compact_spot[i+1]==0)
					{
						temp_parking->next->next->status_compact_spot[i]=1;
						temp_parking->next->next->status_compact_spot[i+1]=1;
						found=1;
						temp_vehicle->spot.Dedicated_wing=temp_parking->next->next->Dedicated_wing;
						temp_vehicle->spot.Parking_level=temp_parking->Parking_level;
						temp_vehicle->spot.location=i+1;
						temp_vehicle->spot.type=2;
						temp_vehicle->alloc=1;
					}
				}
			}
		}
		if(found==1)
		{
			spot.Parking_level=temp_vehicle->spot.Parking_level;
			spot.Dedicated_wing=temp_vehicle->spot.Dedicated_wing;
			spot.type=temp_vehicle->spot.type;
			spot.location=temp_vehicle->spot.location;

			printf("ALLOCATED PARKING SPACE IS : \n");
			printf("PARKING LEVEL : %c\nPARKING SPOT TYPE: %d\nPARKING SPOT NO: %d\n",spot.Parking_level,spot.type,spot.location);
			//writting record in file
			FILE *fp = fopen("record.txt", "a");
			if (fp == NULL)
			{
				printf("NO SUCH FILE EXIST :");
			}
			else
			{

				time_t t;   // not a primitive datatype
				time(&t);

				fprintf(fp,"%s\n",owner);
				fprintf(fp,"%s",ctime(&t));
				fprintf(fp,"%s\n","IN");
				fprintf(fp,"%s\n",no);
				fprintf(fp,"%d\n",type);
				fprintf(fp,"%c\n",spot.Parking_level);
				fprintf(fp,"%d\n",spot.type);
				fprintf(fp,"%d\n",spot.location);

			}
				fclose(fp);

		}
		else
		{
			printf("!!!!!!!!!!!!!!!!!!!!! NO SPACE FOUND !!!!!!!!!!!!!!!!!!\n");
		}
	}

	return Parking_Lot;
}

void Display_Visitor()
{
	char owner[10],no[15],parking_level[2],time[5][10],status[5];
	int type,spot_type,location;
	FILE *fp = fopen("record.txt", "r");
	if (fp == NULL)
	{
		printf("NO SUCH FILE EXIST :");
	}
	else
	{
		while(fscanf(fp,"%s",owner)==1)
		{
			fscanf(fp,"%s%s%s%s%s",time[0],time[1],time[2],time[3],time[4]);
			fscanf(fp,"%s",status);
			fscanf(fp,"%s",no);
			fscanf(fp,"%d",&type);
			fscanf(fp,"%s",parking_level);
			fscanf(fp,"%d",&spot_type);
			fscanf(fp,"%d",&location);
			if(!strcmp(owner,"visitor"))
			{
				printf("OWNER : %s\n",owner);
				printf("Date & TIME : %s %s %s %s %s\n",time[0],time[1],time[2],time[3],time[4]);

				printf("VEHICLE NUMBER :%s\nVEHICLE TYPE:%d\nPARKING LEVEL:%s\n",no,type,parking_level);
				printf("SPOT TYPE :%d\nLOCATION:%d\n\n",spot_type,location);

			}
		}

	}
	fclose(fp);

}

int main(void)
{
	struct Node_Flat *Flat_Details;
	struct Node_Parking *Parking_Lot;
	Parking_Lot=NULL;
	Flat_Details=NULL;

	//                                function to read details from console
	//Read_Details_Console();

	//								function to read details from file
	Flat_Details=Read_Details_File();

	//								function to create the parking lot doublee link list array
	Parking_Lot=Initialise(Parking_Lot);


	//                              function to allocate the parking lot
	Flat_Details=Map_Flat_VehicleNo_Parkingspot(Parking_Lot,Flat_Details);


	//								function to reset parking lot function
	Parking_Lot=reset_status(Parking_Lot);

	char ans[2];
	int ch=-1,flag=0;
	do
	{
		flag=0;
		printf("DO YOU WANT TO SEE ALL THE ALLOCATED PARKING SLOTS : PRESS 1\n");
		printf("DO YOU WANT TO PARK A VEHICLE : PRESS 2\n");
		printf("DO YOU WANT TO SEE THE RECORDS FOR ALL THE VISITORS : PRESS 3\n");

		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					{
						struct Node_Flat *flat;
						struct Node_Vehicle *temp_vehicle;

						flat=Flat_Details;
						while(flat!=NULL)
						{
							printf("%s %d %d% d\n",flat->wing_id,flat->flat_id,flat->no_of_two_wheelers,flat->no_of_four_wheelers);
							temp_vehicle=flat->vehicle;
							while(temp_vehicle!=NULL)
							{
								printf("%d ",temp_vehicle->type);
								printf("%s ",temp_vehicle->no);
								printf("%c ",temp_vehicle->spot.Dedicated_wing);
								printf("%c ",temp_vehicle->spot.Parking_level);
								printf("%d ",temp_vehicle->spot.type);
								printf("%d ",temp_vehicle->spot.location);
								printf("\n");

								temp_vehicle=temp_vehicle->next;
							}
							printf("\n");
							flat=flat->next;
						}

						break;
					}
			case 2:
					{
						Parking_Lot=Park_Vehicle(Parking_Lot,Flat_Details);

						break;
					}
			case 3:
					{
						Display_Visitor();
						break;
					}
			default:
					{
						printf("!!!!!!!!!!!!!!!!!! INVALID ENTRY ENTER AGAIN !!!!!!!!!!!!!!!!!!\n");
						flag=1;
					}
		}
		if(flag==0)
		{
			do
			{
				printf("DO YOU WANT TO CONTINUE (Y/N) ??????????\n\n");
				scanf("%s",ans);
			}while(!(!strcmp(ans,"Y") || !strcmp(ans,"y") || !strcmp(ans,"N") || !strcmp(ans,"n")));
		}


	}while(!strcmp(ans,"Y") || !strcmp(ans,"y") || flag==1);

	printf("!!!THANKS FOR USING OUR SOFTWARE!!!\n");

	return 0;
}
