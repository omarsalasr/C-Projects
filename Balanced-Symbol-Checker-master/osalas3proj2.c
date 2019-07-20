#include <stdio.h>
#include <stdlib.h>
//C booleans
#define TRUE 1
#define FALSE 0
//DebubMode
int debugMode;
//Stack structure
typedef struct stackStruct{
	char* dArr;//pointer to dynamic array
	int sizeArr;//array size
	int top;//current spot at the top of the stack
} Stack;

//Prototype functions
int isOpeningSymbol(char c);
int isClosingSymbol(char c);
char getClosingMatch(char c);
char getOpenMatch(char c);
void initStack(Stack* st);
int isEmpty(Stack* st);
void push(Stack* st, char value);
void incrArray(Stack* st);
void pop(Stack* st);
int getTop(Stack* st);
void resetStack(Stack* st);


int main(int argc, char** argv){
	int i, j;
	int balanced = TRUE;//boolean for balanced expression
	debugMode = FALSE;//debug mode
	char input[302];//store input
	Stack stk;
	for (i = 0; i < argc; ++i){//checks for -d flag
		if('-' == argv[i][0] && 'd' == argv[i][1]){
			debugMode = TRUE;
			printf("Debug Mode enabled\n");
		}
	}
	//initialize stack
	initStack(&stk);
	while(TRUE){
		//get input
		fgets(input, 302, stdin);
		j = 0;
		//exits the loop with q
		if(input[0] == 'q' || input[0] == 'Q')
			break;
		//loop until the end of the expression is reached
		while(input[j] != '\0'){
			//checks if it's an open symbol
			if(isOpeningSymbol(input[j])){
				push(&stk, input[j]);//add to stack
				if(debugMode == TRUE)
					printf("The char %c was pushed.\n", getTop(&stk));
			}
			//checks if it's a closing symbol
			else if(isClosingSymbol(input[j])){
				//matches the top of the stack
				if(getOpenMatch(input[j]) == getTop(&stk)){
					if(debugMode == TRUE)
						printf("The char %c was popped.\n", getTop(&stk));
					//pops the top
					pop(&stk);
				//doesn't match and the stack isn't empty
				}else if(getOpenMatch(input[j]) != getTop(&stk) && isEmpty(&stk) == FALSE){
					for(i = 0; i < j; ++i)
						printf(" ");
					printf("^ Expecting %c\n", getClosingMatch(getTop(&stk)));
					balanced = FALSE;
					break;
				//doesn't match and the top is empty
				}else{
					for(i = 0; i < j; ++i)
						printf(" ");
					printf("^ Missing %c\n", getOpenMatch(input[j]));
					balanced = FALSE;
					break;
				}
			}
			//reached the end
			if(input[j] == '\n'){
				input[j] = '\0';
				//checks if the stack is empty
				if(isEmpty(&stk) == FALSE){
					for(i = 0; i < j; ++i)
						printf(" ");
					printf(" ^ Missing %c\n", getClosingMatch(getTop(&stk)));
					balanced = FALSE;
				}
			}
			j++;
		}
		//balanced expression
		if(balanced == TRUE){
			printf("Expression is balanced\n");
		}
		balanced = TRUE;
		//resets the stack for the next expression
		resetStack(&stk);
	}
	return 0;
}
//checks if its an open symbol
int isOpeningSymbol(char c){
	if(c == '{' || c == '(' || c == '[' || c == '<')
		return TRUE;
	else
		return FALSE;
}
//checks if its a closing symbol
int isClosingSymbol(char c){
	if(c == '}' || c == ')' || c == ']' || c == '>')
		return TRUE;
	else
		return FALSE;
}
//returns the matching symbol for an open symbol
char getClosingMatch(char c){
	if(c == '(')
		return ')';
	else if(c == '{')
		return '}';
	else if(c == '[')
		return ']';
	else if(c == '<')
		return '>';
	return '?';
}
//returns the matching symbol for a closed symbol
char getOpenMatch(char c){
	if(c == ')')
		return '(';
	else if(c == '}')
		return '{';
	else if(c == ']')
		return '[';
	else if(c == '>')
		return '<';
	return '?';
}
//initializes the stack
void initStack(Stack* st){
	st->sizeArr = 2;
	//allocates an array for 2 integers
	st->dArr = (char*) malloc(sizeof(char) * st->sizeArr);
	st->top = 0;
}
//checks if the stack is empty
int isEmpty(Stack* st){
	if(st->top == 0)
		return TRUE;
	else
		return FALSE;
}
//inserts an item on top of the stack
void push(Stack* st, char value){
	//checks if there is enough space in the array
	if(st->sizeArr == st->top){
		incrArray(st);
	}
	st->dArr[st->top] = value;
	st->top = st->top + 1;
}
//increases the size of the array
void incrArray(Stack* st){
	int i;
	//double the current size
	st->sizeArr = st->sizeArr * 2;
	//allocates memory for the new size
	char* temp = (char*) malloc(sizeof(char) * st->sizeArr);
	//coppies the content from old array
	for(i = 0; i < st->sizeArr/2; ++i)
		temp[i] = st->dArr[i];
	if(debugMode == TRUE)
		printf("Growing the Array from size %d to size %d and coppied %d elements.\n", st->sizeArr/2, st->sizeArr, st->sizeArr/2);
	//frees old memory and points to the new array
	free (st->dArr);
	st->dArr = temp;
}
//removes the item at the top of the stack
void pop(Stack* st){
	st->top = st->top - 1;
}
//retuns the top value of the stack
int getTop(Stack* st){
	return st->dArr[st->top - 1];
}
//resets the stack by emptying it and initializes it
void resetStack(Stack* st){
	free (st->dArr);
	initStack(st);
}
