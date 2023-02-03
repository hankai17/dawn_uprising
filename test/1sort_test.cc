#include <iostream>

#define MAX 10

void printArray(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void bubbleSort(int arr[], int len)
{

}

void insertSort(int arr[], int len)
{

}

void selectSort(int arr[], int len)
{

}

void mergeSort(int arr[], int start, int end, int tmpSpace[])
{

}

void quickSort(int arr[], int start, int end)
{

}

void heapSort(int arr[], int len)
{

}

int bsearch(int arr[], int len, int value)
{

}

int main()
{
	int arr[MAX];
	int tmp_arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}
	printArray(arr, MAX);

    return 0;
}

// TIME ELAPSE: 20230203 
