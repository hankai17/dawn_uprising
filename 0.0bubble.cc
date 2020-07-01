#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10

void printArray(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void bubbleSort(int arr[], int len) {
    if (len <= 1) return;
 	for (int i = 0; i < len; ++i) {
 		int flag = 0;
 		for (int j = 0; j < len - i - 1; ++j) {
 			if (arr[j] > arr[j+1]) {
 				int tmp = arr[j];
 				arr[j] = arr[j+1];
 				arr[j+1] = tmp;

 				flag = 1; // 表示有数据交换
 			}
 		}
 		if (!flag) break; // 没有数据交换，提前退出
 	}
}

int main(){
	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}

	printArray(arr, MAX);
    bubbleSort(arr, MAX);
	printArray(arr, MAX);

	system("pause");
	return EXIT_SUCCESS;
}
