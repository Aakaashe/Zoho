#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure for holding data for single seat
typedef struct seatHolder
{
    char seatName;
    int bookingStatus,bookingID,mealStatus,seatAmount;
}Seat;

int main()
{
    char line[2][30],flight_name[20]="",fname[20];
    int i=0,left[2],right[2],middle[2],row[2]={0},temp=0;   // seperation
    int lineiter=0,len=0,id=1,businessBaseRate=2000,economyBaseRate=1000,amount=0,ch;

    //File pointer for accessing File (Flight File)
    FILE *fptr = NULL;
    printf("Enter Flight Name: ");
    scanf("%s",fname);
    printf("\n");
    strcat(flight_name,fname);
    strcat(flight_name,".txt");
    fptr=fopen(flight_name,"r");

    while(fgets(line[lineiter], 50, fptr))      //traversing  file line by line
	{
        len=strlen(line[lineiter]);
        // finding Left,Middle,Right Seat Counts from file
        for(i=0;line[lineiter][i]!='{';i++);
        left[lineiter]=line[lineiter][i+1]-'0';
        for(i=i+1;line[lineiter][i]!=',';i++);
        middle[lineiter]=line[lineiter][i+1]-'0';
        for(i=i+1;line[lineiter][i]!=',';i++);
        right[lineiter]=line[lineiter][i+1]-'0';
        for(temp=0,i=i+2;line[lineiter][i];i++)
        {
            if(line[lineiter][i]>='0'&& line[lineiter][i]<='9')
            {
                temp=line[lineiter][i]-'0';
                row[lineiter]=(row[lineiter]*10)+temp;
            }
        }
        lineiter++;
    }

    //Creating Seat based Structure for Economy and Business Class
    Seat businessSeater[row[0]][left[0]+middle[0]+right[0]];
    Seat economySeater[row[1]][left[1]+middle[1]+right[1]];

    for(i=0;i<row[0];i++)
    {
        for(int j=0;j<(left[0]+middle[0]+right[0]);j++)
        {
            businessSeater[i][j].bookingStatus=0;
            businessSeater[i][j].bookingID=0;
            businessSeater[i][j].mealStatus=0;
            if(j<left[0])
            {
                if(j==0)
                    businessSeater[i][j].seatName='W';
                else if((j+1==left[0]))
                    businessSeater[i][j].seatName='A';
                else
                    businessSeater[i][j].seatName='M';
            }
            else if(j>=left[0] && j<(left[0]+middle[0]))
            {
                if(j==left[0] || j+1==left[0]+middle[0])
                    businessSeater[i][j].seatName='A';
                else
                    businessSeater[i][j].seatName='M';
            }
            else
            {
                if(j+1==(left[0]+middle[0]+right[0]))
                    businessSeater[i][j].seatName='W';
                else if(j==left[0]+middle[0])
                    businessSeater[i][j].seatName='A';
                else
                    businessSeater[i][j].seatName='M';
            }
        }
    }

    for(i=0;i<row[1];i++)
    {
        for(int j=0;j<(left[1]+middle[1]+right[1]);j++)
        {
            economySeater[i][j].bookingStatus=0;
            economySeater[i][j].bookingID=0;
            economySeater[i][j].mealStatus=0;
            if(j<left[1])
            {
                if(j==0)
                    economySeater[i][j].seatName='W';
                else if((j+1==left[1]))
                    economySeater[i][j].seatName='A';
                else
                    economySeater[i][j].seatName='M';
            }
            else if(j>=left[1] && j<(left[1]+middle[1]))
            {
                    if(j==left[1] || j+1==left[1]+middle[1])
                    economySeater[i][j].seatName='A';
                else
                    economySeater[i][j].seatName='M';
            }
            else
            {
                if(j+1==(left[1]+middle[1]+right[1]))
                    economySeater[i][j].seatName='W';
                else if(j==left[1]+middle[1])
                    economySeater[i][j].seatName='A';
                else
                    economySeater[i][j].seatName='M';
            }
        }
    }

    //Choices for User
    do
    {
        int seatrow,seatcol,noOfSeats,flightClass,meal,tempid=0,temprow,tempcol,tempclass,tempnum=0;
        char col,tempchar,tempcolchar,tempidstring[20];
        printf("Enter your choice \n1.Booking\n2.Canceling\n3.Available Seats\n4.Meals Ordered Seats\n5.Individual and Flight Summary\n6.Exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:     // Booking a Ticket
            printf("Do you need Meals (Press 1 for Yes and 2 for NO): ");
            scanf("%d",&meal);
            printf("\n");
            printf("Press 1 for Business or 2 for Economy: ");
            scanf("%d",&flightClass);
            printf("\n");
            printf("Enter Number of Seats: ");
            scanf("%d",&noOfSeats);
            printf("\n");
            for(int k=0;k<noOfSeats;k++)
            {
                printf("Enter Seat Number: ");
                scanf("%d%c%c",&seatrow,&tempchar,&col);
                printf("\n");
                seatcol=col-65;
                seatrow-=1;
                if(flightClass==1)
                {
                    if(seatcol<0 || seatcol>=(left[0]+middle[0]+right[0]) || seatrow<0 || seatrow>=row[0])
                    {
                        printf("There is No Such Seat! Please Choose Another Seat!!!\n");
                        k-=1;
                    }
                    else if(businessSeater[seatrow][seatcol].bookingStatus==0)
                    {
                        businessSeater[seatrow][seatcol].bookingStatus=1;
                        businessSeater[seatrow][seatcol].bookingID=id;
                        //printf("%d ",businessSeater[seatrow][seatcol].bookingID);
                        //id++;
                        amount+=businessBaseRate;
                        businessSeater[seatrow][seatcol].seatAmount=businessBaseRate;
                        businessBaseRate+=200;
                        if(businessSeater[seatrow][seatcol].seatName=='W'||businessSeater[seatrow][seatcol].seatName=='A')
                        {
                            amount+=100;
                            businessSeater[seatrow][seatcol].seatAmount+=100;
                        }

                    }
                    else
                    {
                        printf("Already Booked! Please Choose Another Seat!!!\n");
                        k-=1;
                    }
                    if(meal==1)
                    {
                        businessSeater[seatrow][seatcol].mealStatus=1;
                        amount+=200;
                    }
                }
                else
                {
                    if(seatcol<0 || seatcol>=(left[1]+middle[1]+right[1]) || seatrow<0 || seatrow>=row[1])
                    {
                        printf("There is No Such Seat! Please Choose Another Seat!!!\n");
                        k-=1;
                    }
                    else if(economySeater[seatrow][seatcol].bookingStatus==0)
                    {
                        economySeater[seatrow][seatcol].bookingStatus=1;
                        economySeater[seatrow][seatcol].bookingID=id;
                        //id++;
                        amount+=economyBaseRate;
                        economySeater[seatrow][seatcol].seatAmount=economyBaseRate;
                        economyBaseRate+=100;
                        if(economySeater[seatrow][seatcol].seatName=='W'||economySeater[seatrow][seatcol].seatName=='A')
                        {
                            amount+=100;
                            economySeater[seatrow][seatcol].seatAmount+=100;
                        }
                    }
                    else
                    {
                        printf("Already Booked! Please Choose Another Seat!!!\n");
                        k-=1;
                    }
                    if(meal==1)
                    {
                        economySeater[seatrow][seatcol].mealStatus=1;
                        amount+=200;
                    }
                }
            }
            printf("Booking ID: %s_%.4d\n",fname,id);
            printf("Amount to be paid: %d\n",amount);
            amount=0;
            id++;
            break;

        case 2:     // Canceling  a Ticket
            printf("Press 1 for Business or 2 for Economy: ");
            scanf("%d",&tempclass);
            printf("Enter the Booking ID: ");
            scanf("%s",tempidstring);
            for(i=0;tempidstring[i]!='_';i++);
            for(tempid=0,i=i+1;tempidstring[i];i++)
            {
                if(tempidstring[i]>='0'&&tempidstring[i]<='9')
                {
                    tempnum=tempidstring[i]-'0';
                    tempid=(tempid*10)+tempnum;
                }
            }
            //printf("%d",tempid);
            printf("\n");
            printf("Enter the Seat Number: ");
            scanf("%d%c%c",&temprow,&tempchar,&tempcolchar);
            tempcol=tempcolchar-65;
            temprow--;
            if(tempclass==1)
            {
                if(tempcol<0 || tempcol>=(left[0]+middle[0]+right[0]) || temprow<0 || temprow>=row[0]|| businessSeater[temprow][tempcol].bookingID!=tempid)
                    printf("Enter Valid Information!!!\n");
                else
                {
                    printf("Amount to be Refunded: %d\n\n",businessSeater[temprow][tempcol].seatAmount-200);
                    businessSeater[temprow][tempcol].bookingID=0;
                    businessSeater[temprow][tempcol].bookingStatus=0;
                    businessSeater[temprow][tempcol].mealStatus=0;
                    businessSeater[temprow][tempcol].seatAmount=0;
                }

            }
            else if(tempclass==2)
            {
                if(tempcol<0 || tempcol>=(left[1]+middle[1]+right[1]) || temprow<0 || temprow>=row[1]|| economySeater[temprow][tempcol].bookingID!=tempid)
                    printf("Enter Valid Information!!!\n");
                else
                {
                    printf("Amount to be Refunded: %d\n\n",economySeater[temprow][tempcol].seatAmount-200);
                    economySeater[temprow][tempcol].bookingID=0;
                    economySeater[temprow][tempcol].bookingStatus=0;
                    economySeater[temprow][tempcol].mealStatus=0;
                    economySeater[temprow][tempcol].seatAmount=0;
                }
            }
            break;
        case 3:
            printf("Available Seats: \n");
            printf("Business Class\n");
            for(i=0;i<row[0];i++,printf("\n"))
                for(int j=0;j<(left[0]+middle[0]+right[0]);j++)
                    if(businessSeater[i][j].bookingStatus==0)
                        printf("%.2d_%c ",i+1,j+65);
                    else
                        printf("     ");
            printf("\nEconomy Class\n");
            for(i=0;i<row[1];i++,printf("\n"))
                for(int j=0;j<(left[1]+middle[1]+right[1]);j++)
                    if(economySeater[i][j].bookingStatus==0)
                        printf("%.2d_%c ",i+1,j+65);
                    else
                        printf("     ");
            printf("\n");
            break;
        case 4:
            printf("Meals Booked Seats: \n");
            printf("Business Class\n");
            for(i=0;i<row[0];i++,printf("\n"))
                for(int j=0;j<(left[0]+middle[0]+right[0]);j++)
                    if(businessSeater[i][j].mealStatus==1)
                        printf("%.2d_%c ",i+1,j+65);
                    else
                        printf("    ");
            printf("\nEconomy Class\n");
            for(i=0;i<row[1];i++)
                for(int j=0;j<(left[1]+middle[1]+right[1]);j++)
                    if(economySeater[i][j].mealStatus==1)
                        printf("%.2d_%c ",i+1,j+65);
                    else
                        printf("    ");
            printf("\n");
            break;
        case 5:
            printf("Enter your Booking ID: ");
            scanf("%s",&tempidstring);
            for(i=0;tempidstring[i]!='_';i++);
            for(tempid=0,i=i+1;tempidstring[i];i++)
            {
                if(tempidstring[i]>='0'&&tempidstring[i]<='9')
                {
                    tempnum=tempidstring[i]-'0';
                    tempid=(tempid*10)+tempnum;
                }
            }
            //printf("%d",tempid);
            printf("\nBusiness Class : ");
            for(i=0;i<row[0];i++)
                for(int j=0;j<(left[0]+middle[0]+right[0]);j++)
                    if(businessSeater[i][j].bookingID==tempid)
                        printf("%d_%c ",i+1,j+65);
            printf("\nEconomy Class : ");
            for(i=0;i<row[1];i++)
                for(int j=0;j<(left[1]+middle[1]+right[1]);j++)
                    if(economySeater[i][j].bookingID==tempid)
                        printf("%d_%c ",i+1,j+65);
            printf("\nFlight Name : %s\n\n",fname);
            break;
        }
    }while(ch>0&&ch<6);

    return 0;
}
