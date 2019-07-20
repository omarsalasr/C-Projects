#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//enum for boolean
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
//debug mode
boolean debugMode;
//struct with party size, name, waiting status, and pointer to the next node
typedef struct NODE{
    int partySize;
    char *partyName;
    boolean in_restaurant;
    struct NODE* next;
}Node;

/* forward definition of functions */
void clearToEoln();
int getPosInt();
char* getName();
//Action functions prototypes
void doAdd(Node** head);
void doCallAhead(Node** head);
void doWaiting(Node** head);
void doRetrieve(Node** head);
void doList(Node* head);
void doDisplay(Node* head);
//List function prototypes
void addToList(Node** head, int size, char *name, boolean checkedIn);
boolean doesNameExist(Node** head, char *name);
void updateStatus(Node** head, char *name);
char* retrieveAndRemove(Node** head, int size);
int countGroupsAhead(Node* head, char *name);
void displayGroupSizeAhead(Node* head, char *name);
void displayListInformation(Node* head);