#include "head.h"

void doAdd (Node** head){
/* get group size from input */
  int size = getPosInt();
  if (size < 1){
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }
  /* get group name from input */
  char *name = getName();
  if (NULL == name){
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }
  printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);
  
  // add code to perform this operation here
  addToList(head,size,name, TRUE);//adds a checked in group
}

void doCallAhead (Node** head){
  /* get group size from input */
  int size = getPosInt();
  if (size < 1){
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  /* get group name from input */
  char *name = getName();
  if (NULL == name){
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }
  printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
  
  // add code to perform this operation here
  addToList(head,size,name, FALSE);//adds a group that called in
}

void doWaiting (Node** head){
  /* get group name from input */
  char *name = getName();
  if (NULL == name){
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
  }
  printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);

  // add code to perform this operation here
  updateStatus(head,name);//updates the status of a call in group
}

void doRetrieve (Node ** head){
  /* get table size from input */
  int size = getPosInt();
  if (size < 1){
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
  }
  clearToEoln();
  printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

  // add code to perform this operation here
  retrieveAndRemove(head,size);//retreives the group with the correct size
}

void doList (Node* head){
  /* get group name from input */
  char *name = getName();
  if (NULL == name){
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
  }
  printf ("Group \"%s\" is behind the following groups\n", name);

  // add code to perform this operation here
  displayGroupSizeAhead(head,name);//displays the groups ahead a specific group
}
 
void doDisplay (Node* head){
  clearToEoln();
  printf ("Display information about all groups\n");

  // add code to perform this operation here
  displayListInformation(head);//displays all the groups waiting
}