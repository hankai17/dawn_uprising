#define _CRT_SECURE_NO_WARNINGS
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

//  2      4         5               1
//              arr[i - 1]       arr[i]
//                                temp
//                   j
//

void InsertSort(int arr[], int len) {
	for (int i = 1; i < len; i++) {
		if (arr[i] < arr[i - 1]) {
			int temp = arr[i];
			int j = i - 1;
			for (; j >= 0 && temp < arr[j]; j--) { // 遍历有序的部分 选择一个位置插入
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}
}


int main(){
	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}

	//ÅÅÐòÇ°
	printArray(arr, MAX);
	InsertSort(arr, MAX);
	printArray(arr, MAX);
	return 0;
}
