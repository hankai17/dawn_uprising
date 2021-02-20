#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>

#define MAX 10

void printArray(int arr[], int len){
	for (int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// istart      iend/mid jstart        end/jend

//合并两个有序序列
void Merge(int arr[], int start, int end, int mid, int tempSpace[]){
	int iStart = start;
	int iEnd = mid;
	int jStart = mid + 1;
	int jEnd = end;
	int length = 0;

	while (iStart <= iEnd && jStart <= jEnd) { // 合并两个数组 插入到新tem数组中
		if (arr[iStart] < arr[jStart]) {
			tempSpace[length] = arr[iStart];
			iStart++;
		} else {
			tempSpace[length] = arr[jStart];
			jStart++;
		}
		length++;
	}

	//两个序列中有一个还有剩余元素
	while (iStart <= iEnd) {
		tempSpace[length] = arr[iStart];
		iStart++;
		length++;
	}

	while (jStart <= jEnd) {
		tempSpace[length] = arr[jStart];
		jStart++;
		length++;
	}

	//覆盖原空间的数据
	for (int i = 0; i < length; i++) {
		arr[start + i] = tempSpace[i];
	}
}

//归并排序
void MergeSort(int arr[],int start,int end,int tempSpace[]){

	if (start == end){
		return;
	}

	int mid = (start + end) / 2;
	//拆分左半部分
	MergeSort(arr, start, mid, tempSpace);
	//拆分右半部分
	MergeSort(arr, mid + 1, end, tempSpace);
	//拆分完了 合并有序序列
	Merge(arr, start, end, mid, tempSpace);
}

void my_swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// failed eg: [1 3 5] [2 4 6] how to merge arr only use a tmp value ? 
void my_merge(int arr[], int left_idx, int right_idx, int len)
{
    int i = 0;
    int j = 0;
    
    std::cout << "left_idx: " << left_idx <<
      " right_idx: " << right_idx << std::endl;
    while (i < len && j < len) {
        if (arr[left_idx] > arr[right_idx]) {
            my_swap(arr, left_idx, right_idx);
            left_idx++;
            i++;
        } else {
            left_idx++;
            j++;
        }
    }
}

void merge_sort(int arr[], int len)
{
    if (arr == NULL || len == 1) return;
    int cur = 0;
    for (int i = 1; i < len;) {
        while (cur < len) {
            int left = cur;
            int right = cur + i;
            cur = right + i;
            my_merge(arr, left, right, i);
        }
        i = i << 1;
	    printArray(arr, MAX);
    }
}

int main(){

	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}

	//排序前
	printArray(arr, MAX);
	//冒泡排序
	int tempSpace[MAX];
	//MergeSort(arr, 0, MAX - 1, tempSpace);
    merge_sort(arr, MAX);
	//排序后
	printArray(arr, MAX);


	system("pause");
	return EXIT_SUCCESS;
}

