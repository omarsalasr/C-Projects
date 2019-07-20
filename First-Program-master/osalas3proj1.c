#include <stdio.h>
#include <stdlib.h>

//prototype functions
void arrayCopy (int fromArray[], int toArray[], int size);
void myFavoriteSort (int arr[], int size);
int linSearch (int arr[], int size, int target, int* numComparisons);
int binSearch (int arr[], int size, int target, int* numComparisons);
void printArr(int array[], int size);

int main(){
	//dynamic unsorted array
	int *darrUns;
 	int size = 100;
	//counter to check how many inputs there are
	int counter = 0;
	//number of comparisons before the target was found/not found
	int *numComparisons;
	int val, target, tarPosition;
	//allocate memory in the heap for the initial array
 	darrUns = (int *) malloc(size * sizeof(int));

	//output and input
	printf("Please input a list of values: ");
	scanf("%d", &val);

	//continue getting input until user inputs -999
	while(val != -999){
		//condition that checks if the array is full
		if (counter == size){
			//doubles the size of the array when it's filled
			int *temp;
			temp = (int* ) malloc(size*2*sizeof(int));
			arrayCopy(darrUns, temp, size);
			free(darrUns);
			darrUns = temp;
			size *= 2;
		}
		//stores the input and gets more input
		darrUns[counter] = val;
		counter++;
		scanf("%d", &val);
	}
	//makes the size the length of the input elements in the array
	size = counter;
	//new array to store sorted inputs
	int *darrSor;
	darrSor = (int *) malloc(counter * sizeof(int));
	arrayCopy(darrUns, darrSor, size);
	//sorts one array
	myFavoriteSort(darrSor, size);

	//print arrays
	printf("\nUnsorted Array:\n");
	printArr(darrUns,size);
	printf("Sorted Array:\n");
	printArr(darrSor, size);

	//user input for searching
	printf("\nPlease enter the number(s) you seek: ");
	scanf("%d", &target);
	//gets all the numbers the user wants to look for until they input -999
	while(target != -999){
		printf("\nNumber you seek: %d\n", target);
		//gets the target position for linear search
		tarPosition = linSearch(darrUns, size, target, numComparisons);
		if(tarPosition != -1){
			printf("Linear Search compared %d times and found your nunmber in position %d for unsorted array.\n", *numComparisons, tarPosition);
			//gets the target position for the binary search
			tarPosition = binSearch(darrSor, size, target, numComparisons);
			printf("Binary Search compared %d times and found your nunmber in position %d for sorted array.\n", *numComparisons, tarPosition);
		}else{
			printf("Sorry, but the number you seek doesn't exist\nLinear Search compared %d times.\n", *numComparisons);
			tarPosition = binSearch(darrSor, size, target, numComparisons);
			printf("Binary Search compared %d times.\n", *numComparisons);
		}
		scanf("%d", &target);
	}
	return 0;
}
//function that prints the array
void printArr(int array[], int size){
	for(int i = 0; i < size; ++i){
		printf("%d\t", array[i]);
	}
	printf("\n");
}

//function that copies the content from one array to another
void arrayCopy (int fromArray[], int toArray[], int size){
	for(int i = 0; i < size; ++i){
		toArray[i] = fromArray[i];
	}
}

//function for selection sort
void myFavoriteSort (int arr[], int size){
	int index, temp, i, j;
	//loops through each element
	for(i = 0; i < size - 1; ++i){
		index = i;
		//loops through the current i element and compares beyond that value
		for(j = i + 1; j < size; ++j){
			if(arr[index] > arr[j]){
				index = j;
			}
		}
		//swaps the intial value with the next spot
		if(index != i){
			temp = arr[i];
			arr[i] = arr[index];
			arr[index] = temp;
		}
	}
}
//function for the linear search algorithm
int linSearch (int arr[], int size, int target, int* numComparisons){
	int i;
	*numComparisons = 0;
	//loops through the array and tries to find the target
	for(i = 0; i < size; ++i){
		*numComparisons = *numComparisons + 1;
		if(arr[i] == target){
			return i;
		}
	}
	//target not found
	return -1;
}
//function for the binary search algorithm
int binSearch (int arr[], int size, int target, int* numComparisons){
	//sets the first, middle, and last index
	int first = 0;
	int last = size-1;
	int mid = (first + last)/2;
	*numComparisons = 0;
	//loops through and tries to find the target
	while(first <= last){
		*numComparisons = *numComparisons + 1;
		if(arr[mid] == target){
			return mid;
		}
		else if(arr[mid] < target){
			first = mid + 1;
		}
		else{
			last = mid - 1;
		}
		mid = (first + last)/2;
	}
	//if the number isn't found, then return -1
	return -1;
}
