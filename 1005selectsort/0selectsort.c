#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 10

void printArray(int* arr, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void myswap(int* arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

//Ñ¡ÔñÅÅÐò ÉýÐò
void select_sort(int arr[],int len) {
  for (int i = 0; i < len; i++) {
    int min = i;
    for (int j = i; j < len; j++) {
      if (arr[j] < arr[min]) {
        min = j;
      }
    }
    if (min != i) {
      myswap(arr, min, i);
    }
  }
}

int main()
{
  int arr[MAX];
  srand((unsigned int)time(NULL));
  for (int i = 0; i < MAX; i++) {
    arr[i] = rand() % MAX;
  }
  printArray(arr, MAX);
  select_sort(arr, MAX);
  printArray(arr, MAX);
  return EXIT_SUCCESS;
}
