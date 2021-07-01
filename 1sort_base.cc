#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 10

void printArray(int arr[], int len) {
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

//合并两个有序序列
// istart      iend/mid jstart        end/jend
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

void MergeSort(int arr[],int start,int end,int tempSpace[]){

	if (start == end){
		return;
	}

	int mid = (start + end) / 2;
	MergeSort(arr, start, mid, tempSpace);
	MergeSort(arr, mid + 1, end, tempSpace);
	Merge(arr, start, end, mid, tempSpace);
}

void QuickSort(int arr[],int start, int end) {
	int i = start;
	int j = end;
	//取基准数
	if (i < j) {
	    int target = arr[start];
		while (i < j) {
			//从右向左找比基准数大的
			while (i < j && arr[j] > target) {
				j--;
			}
			if (i < j) {
				arr[i] = arr[j];
				i++;
			}

			//从左向右找比基准数小的
			while (i < j && arr[i] < target) {
				i++;
			}
			if (i < j) {
				arr[j] = arr[i];
				j--;
			}
		}
		
		//i的位置就是基准数最合适的位置
		arr[i] = target;

		//快速排序左半部分
		QuickSort(arr, start, i - 1);
		//快速排序有半部分
		QuickSort(arr, i + 1, end);
	}
}

// adjust index's all child
void heap_adjust(int arr[], int index, int len)
{
	int lidx = index * 2 + 1;
	int ridx = index * 2 + 2;
	int max_idx = index;

	if (index < len / 2) {
		if (lidx < len && arr[lidx] > arr[max_idx]) {
			max_idx = lidx;
		}

		if (ridx < len && arr[ridx] > arr[max_idx]) {
			max_idx = ridx;
		}

		if (max_idx != index) {
			myswap(arr, index, max_idx);
			heap_adjust(arr, max_idx, len);
		}
	}
}

void heap_sort(int arr[], int len)
{
	for (int i = len / 2 - 1; i >= 0; i--) {
		heap_adjust(arr, i, len);
	}

	for (int i = len - 1; i >= 0; i--) {
		myswap(arr, 0, i);
		heap_adjust(arr, 0, i);
	}
}

int bsearch(int a[], int n, int value) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (a[mid] == value) {
      return mid;
    } else if (a[mid] < value) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// 查找序列中(序列中有重复元素)第一个值等于给定值的元素
int bsearch_first(int a[], int n, int value) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (a[mid] >= value) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  if (low < n && a[low]==value) return low;
  else return -1;
}

int bsearch_first1(int a[], int n, int value) { // same as up
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (a[mid] > value) {
      high = mid - 1;
    } else if (a[mid] < value) {
      low = mid + 1;
    } else {
      if ((mid == 0) || (a[mid - 1] != value)) return mid;
      else high = mid - 1;
    }
  }
  return -1;
}

int bsearch_last(int a[], int n, int value) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (a[mid] > value) {
      high = mid - 1;
    } else if (a[mid] < value) {
      low = mid + 1;
    } else {
      if ((mid == n - 1) || (a[mid + 1] != value)) return mid;
      else low = mid + 1;
    }
  }
  return -1;
}

// 查找第一个大于等于给定值的元素 3，4，6，7，10。如果查找第一个大于等于5的元素 就是6
int bsearch_first_bigthan(int a[], int n, int value) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (a[mid] >= value) {
      if ((mid == 0) || (a[mid - 1] < value)) return mid;
      else high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

// 查找最后一个小于等于给定值的元素 3，5，6，8，9，10。最后一个小于等于7的元素就是6
int bsearch_last_lessthan(int a[], int n, int value) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (a[mid] > value) {
      high = mid - 1;
    } else {
      if ((mid == n - 1) || (a[mid + 1] > value)) return mid;
      else low = mid + 1;
    }
  }
  return -1;
}

int get_partional_min(int arr[], int len)
{
  if (arr == NULL || len == 0) return -1;
  if (len == 1 || arr[0] < arr[1]) return 0;
  if (arr[len - 1] < arr[len - 2]) return arr[len - 1];
  int l = 1;
  int r = len - 2;
  int mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (arr[mid] > arr[mid - 1]) {
      r = mid - 1;
    } else if (arr[mid] > arr[mid + 1]) {
      l = mid + 1;
    } else {
      return mid;
    }
  }
  return l;
}


int main(){
	int arr[MAX];
	int tmp_arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}

	printArray(arr, MAX);
    //bubbleSort(arr, MAX);
    //InsertSort(arr, MAX);
    //select_sort(arr, MAX);
    //MergeSort(arr, 0, MAX - 1, tmp_arr);
    //QuickSort(arr, 0, MAX - 1);
    heap_sort(arr, MAX);
	printArray(arr, MAX);

	return 0;
}
