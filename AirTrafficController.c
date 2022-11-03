#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#include<string.h>

#define BAYFULL 10



typedef struct
{
    int day,month,year,hour,min;
}TIME_T;

struct node
{
    char flight_id[11];
    
    TIME_T arvltm,dprttm;
    struct node * link;
};

typedef struct node * NODEPTR;

NODEPTR fnRegister();
bool rnwyoccupied(int *);
void fnDelete(NODEPTR,NODEPTR);
NODEPTR fnInsertArrivalNodeOrder(NODEPTR ,NODEPTR );
NODEPTR fnInsertDepartureNodeOrder(NODEPTR ,NODEPTR );
bool fnArrivalConditionLessThan(NODEPTR ,NODEPTR );
bool fnDepartureConditionLessThan(NODEPTR ,NODEPTR );
NODEPTR fnGetNode();
NODEPTR fnGetArrivalTime(NODEPTR);
NODEPTR fnGetDepartureTime(NODEPTR);
NODEPTR fnSearchId(NODEPTR,char[]);
void fnDisplayTime(TIME_T);
bool FnBayFull(int);
void fnGetTime(int *,int *);
void fnDisplayInfo(NODEPTR);
bool fnInvalidDates(TIME_T);

int main()
{
        NODEPTR temp,takeoff=NULL,land=NULL;
        int ch,rnwy1,rnwy2,bay=0;
        char id[11];
        for(;;)
        {
            printf("\n1.Registration\t2.Take off\t3.Landing\t4.Display list and exit\n");
            printf("\nEnter your choice:");
            scanf("%d",&ch);
            switch(ch)
            {
                case 1: temp=fnRegister();
                        land=fnInsertArrivalNodeOrder(temp,land);
                        takeoff=fnInsertDepartureNodeOrder(temp,takeoff);
                        break;
                case 2: if(!rnwyoccupied(&rnwy1))
                        {
                            printf("\nEnter your unique id\n");
                            getchar();
                            scanf("%s",id);
                            temp=fnSearchId(takeoff,id);
                            if(temp==NULL)
                                break;
                            printf("\nYou are permitted to take off from runway 1\n");
                            fnDelete(temp,takeoff);
                            bay--;
                        }
                        else if(!rnwyoccupied(&rnwy2))
                        {
                            printf("\nEnter your unique id\n");
                            getchar();
                            scanf("%s",id);
                            temp=fnSearchId(takeoff,id);
                            if(temp==NULL)
                                break;
                            printf("\nYou are permitted to take off from runway 2\n");
                            fnDelete(temp,takeoff);
                            bay--;
                        }
                        else
                            printf("\nSorry,but you will have to wait for ten minutes so that we can arrange for you\n");

                        break;
                case 3: if(!rnwyoccupied(&rnwy1)&&!FnBayFull(bay))
                        {
                            printf("\nEnter your unique id\n");
                            getchar();
                            scanf("%s",id);
                            temp=fnSearchId(takeoff,id);
                            if(temp==NULL)
                                break;
                            printf("\nYou are permitted to use runway 1 for landing\n");
                            fnDelete(temp,land);
                            bay++;
                        }
                        else if(!rnwyoccupied(&rnwy2)&&!FnBayFull(bay))
                        {
                            printf("\nEnter your unique id\n");
                            getchar();
                            scanf("%s",id);
                            temp=fnSearchId(takeoff,id);
                            if(temp==NULL)
                                break;
                            printf("\nYou are permitted to use runway 2 for landing\n");
                            fnDelete(temp,land);
                            bay++;
                        }
                        else
                            printf("\nSorry,but you will have to wait for ten minutes so that we can arrange for you\n");
                            break;
                case 4: fnDisplayInfo(land);
                        printf("\n\nExiting...\n\n");
                        exit(0);
                        break;

                default:printf("\nInvalid choice,re enter the choice\n");
            }
        }

        return 0;
}
void fnDisplayInfo(NODEPTR land)
{
     printf("\nThe flights that have been registered are:\n");
     if(land==NULL)
     {
         printf("\nList currently empty,nothing to display\n");
         return;
     }
    NODEPTR cur;

    cur=land;

    while(cur!=NULL)
    {
        printf("\nFlight id: %s\n",cur->flight_id);
        printf("\nArrival time:");
        fnDisplayTime(cur->arvltm);
        printf("\nDeparture time:");
        fnDisplayTime(cur->dprttm);

        cur=cur->link;
    }
}

bool FnBayFull(int bay)
{
    if(bay==BAYFULL)
        return true;
    else
        return false;
}


NODEPTR fnRegister()
{
    NODEPTR flight;
    flight=fnGetNode();
    flight->link=NULL;
    printf("\nEnter your unique id\n");
    getchar();
    scanf("%s",flight->flight_id);

    flight=fnGetArrivalTime(flight);
    while(fnInvalidDates(flight->arvltm))
    {
        printf("\nInvalid arrival time,please re enter\n");
        flight=fnGetArrivalTime(flight);
    }

    flight=fnGetDepartureTime(flight);
    while(fnInvalidDates(flight->dprttm))
     {
        printf("\nInvalid departure time,please re enter\n");
        flight=fnGetDepartureTime(flight);

    }
    printf("\nYou have successfully registered.\nYou will be considered and we will try our best to make arrangements for it\n");
    return flight;
}




NODEPTR fnInsertArrivalNodeOrder(NODEPTR temp,NODEPTR land)
{
    NODEPTR prev,cur;
    if(land ==NULL)
    {
        return temp;
    }
    if(fnArrivalConditionLessThan(temp,land))
    {
            temp->link=land;
            return temp;
    }

    prev=NULL;
    cur=land;
    while(cur!=NULL && !fnArrivalConditionLessThan(temp,cur))
    {
        prev=cur;
        cur=cur->link;
    }
    prev->link=temp;
    temp->link=cur;
    return land;
}

NODEPTR fnGetArrivalTime(NODEPTR flight)
{
    printf("\nEnter your arrival time\n");
    printf("\nDay:");
    scanf("%d",&flight->arvltm.day);
    printf("\nMonth:");
    scanf("%d",&flight->arvltm.month);
    printf("\nYear:");
    scanf("%d",&flight->arvltm.year);
    printf("\nHour:");
    scanf("%d",&flight->arvltm.hour);
    printf("\nMinute:");
    scanf("%d",&flight->arvltm.min);
    return flight;
}
NODEPTR fnGetDepartureTime(NODEPTR flight)
{
    printf("\nEnter your departure time\n");
    printf("\nDay:");
    scanf("%d",&flight->dprttm.day);
    printf("\nMonth:");
    scanf("%d",&flight->dprttm.month);
    printf("\nYear:");
    scanf("%d",&flight->dprttm.year);
    printf("\nHour:");
    scanf("%d",&flight->dprttm.hour);
    printf("\nMinute:");
    scanf("%d",&flight->dprttm.min);
    return flight;
}

NODEPTR fnInsertDepartureNodeOrder(NODEPTR temp,NODEPTR takeoff)
{
    NODEPTR prev,cur;

    if(takeoff ==NULL)
    {
        return temp;
    }
    if(fnDepartureConditionLessThan(temp,takeoff))
    {
        temp->link=takeoff;
        return temp;

    }
    prev=NULL;
    cur=takeoff;
    while(cur!=NULL && !fnDepartureConditionLessThan(temp,cur))
    {
        prev=cur;
        cur=cur->link;
    }
    prev->link=temp;
    temp->link=cur;
    return takeoff;
}

bool rnwyoccupied(int* r)
{
    printf("The runway is occupied? Enter 0 or 1\n");
    scanf("%d",r);
    if(*r!=0 &&*r!=1)
    {
        printf("\nInvalid Input. Please Re-enter If ");
        rnwyoccupied(r);
    }
    if(*r==0)
        return false;
    else
        return true;
}




bool fnArrivalConditionLessThan(NODEPTR temp,NODEPTR cur)
{
    if((temp->arvltm.year <= cur->arvltm.year)&&(temp->arvltm.month <= cur->arvltm.month)&&(temp->arvltm.day <= cur->arvltm.day))
    {
        if((temp->arvltm.hour <= cur->arvltm.hour)&&(temp->arvltm.min < cur->arvltm.min))
        {
            return true;
        }
    }
    return false;
}

bool fnDepartureConditionLessThan(NODEPTR temp,NODEPTR cur)
{
    if((temp->dprttm.year <= cur->dprttm.year)&&(temp->dprttm.month <= cur->dprttm.month)&&(temp->dprttm.day <= cur->dprttm.day))
    {
        if((temp->dprttm.hour <= cur->dprttm.hour)&&(temp->dprttm.min <= cur->dprttm.min))
        {
            return true;
        }
    }
    return false;
}

bool fnInvalidDates(TIME_T t)
{
        if(t.day>31||t.day<1||t.month<1||t.month>12||t.hour<0||t.hour>23||t.min<0||t.min>60)
            return true;
        return false;
}

NODEPTR fnGetNode()
{
    NODEPTR temp;
    temp=(NODEPTR)malloc(sizeof(struct node));
    if(temp==NULL)
    {
        printf("\nFailed to allocate memory\n");
        return NULL;
    }
    return temp;
}


 NODEPTR fnSearchId(NODEPTR first,char id[])
 {
     if(first==NULL)
     {
         printf("\nList empty,cannot search\n");
         return NULL;
     }

     if(strcmp(first->flight_id,id)==0)
        return first;
     NODEPTR prev,cur;
     prev=NULL;
     cur=first;
     while(cur!=NULL&&strcmp(cur->flight_id,id)!=0)
     {
         prev=cur;
         cur=cur->link;
     }
     if(cur==NULL)
     {
         printf("\nFlight not found in the list,please re enter your id\n");
         return NULL;
     }
     return cur;
 }
 void fnDelete(NODEPTR temp,NODEPTR first)
 {
     NODEPTR prev,cur;
     if(temp==first)
      {
           cur=first->link;
           first=cur;
           free(cur);
      }
      if(temp==first->link)
      {

          prev=first->link;
          cur=prev->link;
          first->link=cur;
          free(cur);
      }

 }

 void fnDisplayTime(TIME_T time)
 {
        printf("\n%2d/%2d/%d\t%2d:%2d\n",time.day,time.month,time.year,time.hour,time.min);
        return;
 }

