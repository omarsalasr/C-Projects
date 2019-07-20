#include "head.h"
//adds a group to the list with given information
void addToList(Node** head, int size, char* name, boolean checkedIn){
  if(doesNameExist(head, name)){
    //There is a party with the same name
    printf("Party name %s already exists", (*head)->partyName);
    return;
  }
  //creates a new node for traversing and for allocation
  Node* travel = *head;
  Node* temp = (Node*) malloc(sizeof(Node));
  temp->partyName = name;
  temp->partySize = size;
  temp->in_restaurant = checkedIn;
  temp->next = NULL;
  if(*head == NULL){//empty waiting list
    *head = temp;
    return;
  }
  while(travel->next != NULL){//add it to the end of the list
    travel = travel->next;
  }
  travel->next = temp;
}
//function that checks for duplicate names
boolean doesNameExist(Node** head, char *name){
  Node* travel = *head;
  while(travel != NULL){
    if(strcmp(travel->partyName, name) == 0)//found a group with the same name
      return TRUE;
    travel = travel->next;
  }
  return FALSE;
}
//updates the call in status to check in
void updateStatus(Node** head, char *name){
  if(doesNameExist(head, name)){
    Node* travel = *head;
    while(strcmp(travel->partyName, name) != 0){//traverses until it finds the list
      if(debugMode)
        printf("DebugMode---\nSize: %-2d  Satus: %-10s  Name: %-15s\n------------\n", travel->partySize, travel->in_restaurant ? "Checked In" : "Called In", travel->partyName);
      travel = travel->next;
    }
    if(travel->in_restaurant == FALSE){//checks if they called in
      travel->in_restaurant = TRUE;
      return;
    }
  }
  //They are already checked in
  printf("Group %s is already checked in", name);
}
//function that removes the first group with correct size
char* retrieveAndRemove(Node** head, int size){
    Node *temp;
    Node *travel = *head;
    char* name;
    if(travel->partySize == size){//beginning of the list
      if(countGroupsAhead(*head,travel->partyName) == 1){//single node
        name = travel->partyName;
        free (*head);
        *head = NULL;
      }else{//more than 1 node in the list
        temp = travel;
        travel = travel->next;
        name = travel->partyName;
        *head = travel;
        free (temp);
      }
    }else{//not at the begnning of the list
      while(travel->next->partySize != size){//finds the group
        if(debugMode)
          printf("DebugMode---\nSize: %-2d  Satus: %-10s  Name: %-15s\n------------\n", travel->partySize, travel->in_restaurant ? "Checked In" : "Called In", travel->partyName);
        travel = travel->next;
      }
      if(travel->next->next == NULL){//end of the list
        name = travel->partyName;
        free (travel->next);
        travel->next = NULL;
      }else{//somewhere in the middle of the list
        temp = travel->next;
        travel->next = travel->next->next;
        name = temp->partyName;
        free (temp);
      }
    }
  return name; 
}
//returns the number of groups ahead of a certain group
int countGroupsAhead(Node* head, char *name){
  int counter = 0;
  if(doesNameExist(&head, name))
    while(head != NULL){//goes through the whole list
      if(strcmp(head->partyName, name) == 0)
        return counter;
      counter++;
      head = head->next;
    }
  return counter;
}
//function that displays the groups ahead of a specific group
void displayGroupSizeAhead(Node* head, char *name){
  int position = countGroupsAhead(head, name);//gest the number of groups in front
  int counter = 1;
  if(position == 0){//first group
    printf("You are the next group of size %d that will be seated\n", head->partySize);
  }
  if(doesNameExist(&head, name)){
    printf("There are %d groups ahead of you\n", position);
    while(head != NULL){//goes through the whole list
      if(strcmp(head->partyName, name) == 0)
        return;
      //displays the groups ahead
      printf("Group Number: %-2d  Size: %-2d  Satus: %-10s  Name: %-10s\n",counter, head->partySize, head->in_restaurant ? "Checked In" : "Called In", head->partyName);
      counter++;
      head = head->next;
    }
  }
}
//displays all the current groups
void displayListInformation(Node* head){
    while(head != NULL){
      printf("Size: %-2d  Satus: %-10s  Name: %-15s\n", head->partySize, head->in_restaurant ? "Checked In" : "Called In", head->partyName);
      head = head->next;
    }
    printf("\n");
}