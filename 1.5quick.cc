#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 10
#define Index 2

void printArray(int arr[], int len){
	for (int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//快速排序
void QuickSort(int arr[],int start, int end) {
	int i = start;
	int j = end;
	//取基准数
	int target = arr[start];
	if (i < j) {
		while (i < j) {
			//从右向左找比基准数大的
			while (i < j && arr[j] < target) {
				j--;
			}
			if (i < j) {
				arr[i] = arr[j];
				i++;
			}

			//从左向右找比基准数小的
			while (i < j && arr[i] > target) {
				i++;
			}
			if (i < j) {
				arr[j] = arr[i];
				j--;
			}
		}
		
		//i的位置就是基准数最合适的位置
		arr[i] = target;
        printf("--->\n");
	    printArray(arr, MAX);
        printf("<---\n");

		//快速排序左半部分
		QuickSort(arr, start, i - 1);
		//快速排序有半部分
		QuickSort(arr, i + 1, end);
	}
}

// 找第Index大的元素 的时间复杂度是 O(n)
void QuickSort1(int arr[],int start, int end) {
	int i = start;
	int j = end;
	//取基准数
	int target = arr[start];
	if (i < j) {
		while (i < j) {
			//从右向左找比基准数大的
			while (i < j && arr[j] < target) {
				j--;
			}
			if (i < j) {
				arr[i] = arr[j];
				i++;
			}

			//从左向右找比基准数小的
			while (i < j && arr[i] > target) {
				i++;
			}
			if (i < j) {
				arr[j] = arr[i];
				j--;
			}
		}
		
		//i的位置就是基准数最合适的位置
		arr[i] = target;
        if (i == Index) {
            printf("ok index[%d]: %d\n", Index, arr[i]);
            return;
        }
        if (i < Index) {
		    //快速排序左半部分
		    QuickSort(arr, start, i - 1);
        } else {
		    //快速排序有半部分
		    QuickSort(arr, i + 1, end);
        }
	}
}

void my_quick(int arr[], int start, int end, int k)
{
    int i = start; 
    int j = end;
    int base = arr[start];
    if (i < j) {
        while (i < j) {
            while (i < j && base > arr[j]) {
                j--;
            }
            if (i < j) {
                arr[i] = arr[j];
                i++;
            }
            while (i < j && base < arr[i]) {
                i++;
            }
            if (i < j) {
                arr[j] = arr[i];
                j--;
            }
        }
        arr[i] = base;
        if (i == k) {
            printf("k: %d\n", base);
            return;
        } else if (i > k) {
            my_quick(arr, start, i - 1, k);
        } else {
            my_quick(arr, i + 1, end, k);
        }
    } else {
            printf("k: %d\n", base);
            return;
    }
}

int main(){
	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}

	printArray(arr, MAX);
	//QuickSort(arr, 0, MAX - 1);
	//QuickSort1(arr, 0, MAX - 1);
    int k = 2;
    my_quick(arr, 0, MAX - 1, k - 1);

	printArray(arr, MAX);

	return EXIT_SUCCESS;
}

