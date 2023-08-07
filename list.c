#include "list.h"
#include <string.h>
#include <stdlib.h>
/*
    Linkedlist functions are :
    1. addfriendAtfront()
    2. addfriendAtLast()
    3. Remove_Friend_From_Front()
    4. Remove_Friend_From_Last()
    5. create()

    create() :- it is a primary function which creates a linkedlist node
    this function is not for user 
    
*/
// it creates a list node 
List *create(struct friend f){
    List *newinfo = (List*)malloc(sizeof(List));
   strcpy(newinfo->info.name ,f.name);
    newinfo->info.Dob.day = f.Dob.day;
    newinfo->info.Dob.month = f.Dob.month;
    newinfo->info.Dob.year = f.Dob.year;
    newinfo->next = NULL;
    return newinfo;
}
// function is use to add friend at first of list
List *addfriendAtfront(List *head,struct friend f){
     if(head == NULL){
        head = create(f);
        return head;
     }
    List *node = create(f);
    node->next = head;
    head = node;
    return head;
}
List*addfriendAtLast(List * head, struct friend f){
       // this is for when list is empty
        if(head == NULL){
        head = create(f);
        return head;
     }
     List *head1 = head;
     while(head1->next != NULL){
          head1 = head1->next;
     }
     head1->next = create(f);
     return head;
}
struct friend getFromFront(List *head)
{
     return head->info;
}
struct friend getFromBack(List *head)
{
     while(head->next != NULL)
        head = head->next;
     return head->info; 
}
struct friend getFromBetween(List *head , int pos)
{
     int i = 1;
     while(i < pos && head != NULL)
     {
          head = head->next;
          i++;
     }
     return head->info;
}
// this function is use to remove friend from the front of list
List *Remove_Friend_From_Front(List *head){
     List *head1 = head;
     if(head1 == NULL)
        return head1;
     head = head->next;
     free(head1);
     return head;
}
// this function removes friend infomation from back of the list
List *Remove_Friend_From_Last(List* head)
{
     List *start = head;
     List *prev = NULL;
     while(start->next != NULL)
     {
         prev = start;
         start = start->next;
     }
     prev->next = NULL;
     free(start);
     return head;
}

List *Remove_Friend_From_Between(List*head,int pos){
        int i = 1;
       List *start = head;
       List *deleteNode = NULL;
     while(i < pos-1 && start->next != NULL){

          start = start->next;
          i++;
     }
     if ((pos < 2 || i < pos-1) && start->next == NULL)
     {
         printf("Invalid position !\n");
         return head;
     }
     deleteNode = start->next;
     start->next = deleteNode->next;
     free(deleteNode);
     return head;
}
//this function is add at the between of the list
List* addFriendAtBetween(List *head , int pos, struct friend f, bool *flag)
{
     int i = 1;
     List *start = head;
     List *newFriend = NULL;
     while(i < pos-1  && start->next != NULL){
          start = start->next;
          i++;
     }
     if(pos < 2 || (i < pos-1 && start->next == NULL)){
          printf("position is invalid \n");
          return head;
     }
     newFriend = create(f);
     newFriend->next = start->next;
     start->next = newFriend;
     *flag = true;
     return head;
}

/*array functions*/

//this function sorts the contigious list on the basis of birthdays
void sortContigiousList(ContiguousList**list)
{
     int i,j,day;
     struct friend key;
     int n = (*list)->OccupiedIndex+1;
     for(i = 1; i < n; ++i)
     {
          key = (*list)->array[i];
          day = key.Dob.day;
          for(j = i-1; j >= 0 && day < (*list)->array[j].Dob.day; --j){
               (*list)->array[j+1] = (*list)->array[j];
          }
          (*list)->array[j+1] = key;
     }
}

//this functions insert an element in a sorted Contigious list
bool InsertInContigiousList(ContiguousList**list, struct friend f)
{
     if((*list)->OccupiedIndex == (*list)->bufferSize-1)
            return false;
     int day = f.Dob.day,i=(*list)->OccupiedIndex++;
     
     for(i; i >= 0 && f.Dob.day < (*list)->array[i].Dob.day; --i){
          (*list)->array[i+1] = (*list)->array[i];
     }
     (*list)->array[i+1] = f;
     return true; 
}

bool pop(ContiguousList **list ,struct friend f)
{
    int midindex=-1 , l=0,r = (*list)->OccupiedIndex-1;
    int n = (*list)->OccupiedIndex+1;

    //finding the actual position of friend in Contigious list
    while (l<=r)
    {
        midindex = (l+r)/2;
          if(strcmp((*list)->array[midindex].name,f.name) == 0 && f.Dob.day == (*list)->array[midindex].Dob.day 
          && f.Dob.year == (*list)->array[midindex].Dob.year){
                  break;
          }
          else if(f.Dob.day < (*list)->array[midindex].Dob.day){
                r = midindex -1;
          }
          else
             l = midindex + 1;
    }
    if(l > r)
        return false;
     //check if mid index is the last index of Contiguous list
     if(midindex == (*list)->OccupiedIndex)
     {
          (*list)->OccupiedIndex--;
          return false;
     }
     //deleteing the element
    for(int i = midindex; i < n-1; ++i)
    {
        (*list)->array[i] = (*list)->array[i+1];
    }
    (*list)->OccupiedIndex--;
    return true;
}

void ResizeContigiousList(ContiguousList **list)
{
     //double the buffer size 
     (*list)->bufferSize *= 2;
     
     struct friend *newBlock = NULL;

     //allocating the new block and copying the contents of previous block
     newBlock = (struct friend*)malloc((*list)->bufferSize*sizeof(struct friend));
     for(int i = 0; i < (*list)->OccupiedIndex+1; ++i)
          newBlock[i] = (*list)->array[i];

     //deallocating the previous block
     free((*list)->array);
     (*list)->array = newBlock;
}