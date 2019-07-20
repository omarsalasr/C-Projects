#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Boolean values in C
#define TRUE 1
#define FALSE 0
//boolean for debugmode
int debugMode;
//linked list stack
typedef struct stackStruct{
  //x and y
  int x,y;
  //pointer to the next intem in the stack
  struct stackStruct* next;
} Stack;
//maze structure
typedef struct mazeStruct
{
  //dynamic double array
 char** arr;
 //sizes
 int xsize, ysize;
 //starting point
 int xstart, ystart;
 //ending point
 int xend, yend;
} maze;
//prototypes
Stack* initStack(int x, int y);
int isEmpty(Stack *hd);
Stack* push(Stack *hd, int x, int y);
Stack* pop(Stack *hd);
Stack* getTop(Stack *hd);
Stack* reset(Stack *hd);
void printMaze(maze m1);
void printPath(Stack *hd);

int main (int argc, char **argv)
{
  maze m1;
  Stack* st;
  int xpos, ypos;
  int i,j;
  int txtIndex = -1;//keeps track of where the file name is
  int numFiles = 0;//keeps tracak of the number of files

  FILE *src;
  //loops that iterate through the arguments
  for(i = 0; i < argc; i++){
    //checks for -d flag
    if('-' == argv[i][0] && 'd' == argv[i][1]){
      debugMode = TRUE;
      printf("Debug Mode enabled\n");
      continue;
    }
    //iterates through each char array
    for(j = 0; j < strlen(argv[i]); j++)
      //checks for the string that ends with .txt
      if('.' == argv[i][j] && 't' == argv[i][j+1] && 'x' == argv[i][j+2] && 't' == argv[i][j+3]){
        if(debugMode)
          printf("Files Found in Arguments\n");
        if(numFiles == 0){//condition to check if there is only 1 file in the args
          txtIndex = i;
        }
        numFiles++;
      }
  }
  //checks if there was no input file name found
  if(txtIndex == -1){
    printf("Usage: %s <input file name>\n", argv[0]);
    exit(-1);
  }else if(numFiles != 1){//exit if there are more than 1 file
    printf("There are too many files, please input only one.\n");
    exit(-1);
  }

  /* Try to open the input file. */
  if ( ( src = fopen( argv[txtIndex], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[txtIndex] );
    exit(-1);
  }

  //loops until a valid size is found
  while(TRUE){
    fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
    if(m1.xsize > 0 && m1.ysize > 0){
      break;
    }
    printf("Invalid Input: Out of Range\n");
  }
  //loops until a valid start position is found
  while(TRUE){
    fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
    if(m1.xstart > 0 && m1.xstart <= m1.xsize && m1.ystart > 0 && m1.ystart <= m1.ysize){
      break;
    }
    printf("Invalid Input: Out of Range\n");
  }
  //loops until a valid ending position is found
  while(TRUE){
    fscanf (src, "%d %d", &m1.xend, &m1.yend);
    if(m1.xend > 0 && m1.xend <= m1.xsize && m1.yend > 0 && m1.yend <= m1.ysize){
      break;
    }
    printf("Invalid Input: Maze sizes must be greater than 0\n");
  }
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);
  //allocates memory for the 2D array used for the maze output
  m1.arr = (char**)malloc(sizeof(char*) * (m1.xsize+2));
  for(int i = 0; i < m1.xsize+2; i++){
    m1.arr[i] = (char*)malloc(sizeof(char) * (m1.ysize+2));
  }
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';

  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
      //checks if there is an invalud input for start and end
      if(xpos == m1.xstart && ypos == m1.ystart){
        printf("Invalid Input: Blocking Start Position\n");
        continue;
      }else if(xpos == m1.xend && ypos == m1.yend){
        printf("Invalid Input: Blocking Ending Position\n");
        continue;
      }
     m1.arr[xpos][ypos] = '*';
    }

  //prints intial maze
  printMaze(m1);
  //initializes the stack
  st = initStack(m1.xstart, m1.ystart);
  //sets ending position to unvisited
  m1.arr[m1.xend][m1.yend] = '.';
  do {
    //marks the spot as visited
    m1.arr[st->x][st->y] = '$';
    //condition to check if there is a solution
    if(st->x == m1.xend && st->y == m1.yend){
      printf("There exists a solution\n*Path Sequence:*\n");
      printPath(st);
      printf("*End Sequence*\n");
      break;
    }else if(m1.arr[st->x][st->y+1] == '.'){//check right
      st = push(st, st->x, st->y+1);
    }else if(m1.arr[st->x+1][st->y] == '.'){//check down
      st = push(st, st->x+1, st->y);
    }else if(m1.arr[st->x][st->y-1] == '.'){//check left
      st = push(st, st->x, st->y-1);
    }else if(m1.arr[st->x-1][st->y] == '.'){//check up
      st = push(st, st->x-1, st->y);
    }else{
      //pop if there is valid move
      st = pop(st);
      //check popped all of the items for no solution
      if(st->next == NULL){
        printf("This maze has no solution\n");
        break;
      }
    }
  }while(isEmpty);
  //outputs the maze when in debug mode
  if(debugMode){
    m1.arr[m1.xstart][m1.ystart] = 's';
    m1.arr[m1.xend][m1.yend] = 'e';
    printMaze(m1);
  }
  //resets the stack for future use
  st = reset(st);
  return 0;
}
//prints the path in reverse order from the stalk with recurssion
void printPath(Stack *hd){
  if(hd == NULL){
    return;
  }
  printPath(hd->next);
  printf("(%d,%d)\n", hd->x,hd->y);
}
//prints the maze
void printMaze(maze m1){
  int i,j;
  for (i = 0; i < m1.xsize+2; i++){
    for (j = 0; j < m1.ysize+2; j++)
      printf ("%c", m1.arr[i][j]);
    printf("\n");
   }
}
//initializes a stack
Stack* initStack(int x, int y){
  Stack* temp = (Stack*) malloc(sizeof(Stack));//allocates memory for a new item
  temp->x = x;
  temp->y = y;
  temp->next = NULL;
  return temp;
}
//function that checks if the stack is empty
int isEmpty(Stack *hd){
  if(hd->next == NULL)
    return FALSE;
  else
    return TRUE;
}
//adds an item to the top of the stack
Stack* push(Stack *hd, int x, int y){
  Stack* temp = (Stack*) malloc(sizeof(Stack));//allocates memory for a new item
  temp->x = x;
  temp->y = y;
  temp->next = hd;
  if(debugMode)
    printf("Pushed: %d,%d\n", temp->x, temp->y);
  return temp;
}
//removes the top element in the stalk
Stack* pop(Stack *hd){
  if(debugMode)
    printf("Popped: %d,%d\n", hd->x, hd->y);
  Stack *temp = hd;
  hd = hd->next;
  free (temp);//frees the item for no memory leak
  return hd;
}
//returns the top item in the stack
Stack* getTop(Stack *hd){
  return hd;
}
//reset function
Stack* reset(Stack *hd){
  Stack *temp;
  while(hd != NULL){
    temp = hd;
    hd = hd->next;
    free (temp);//frees every item
  }
  return hd;
}
