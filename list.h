#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
typedef struct date{
    int day;
    int month;
    int year;
}date;

typedef struct friend{
      char name[70];
      date Dob;
}friend;

//this is for Linkedlist node  
typedef struct List{
    struct friend info;
    struct List *next;

}List;

typedef struct ContiguousList{
       struct friend *array;
       int OccupiedIndex;
       int bufferSize;
}ContiguousList;
//functions for linked list 

List *addfriendAtfront(List *,struct friend);
List *addfriendAtLast(List *,struct friend);
List *addFriendAtBetween(List *,int,struct friend);
List *Remove_Friend_From_Front(List*);
List *Remove_Friend_From_Last(List*);
List *Remove_Friend_From_Between(List*,int);

//functions for arrays

void sortContigiousList(ContiguousList **);
bool InsertInContigiousList(ContiguousList** , struct friend);
void pop(ContiguousList**,struct friend);
void ResizeContigiousList(ContiguousList**);
#endif