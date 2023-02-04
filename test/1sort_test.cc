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
    for (int i = 0; i < len; i++) {
        int flag = 0;
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                flag = 1;
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
        if (!flag) break;
    }
}

void insertSort(int arr[], int len)
{
    for (int i = 1; i < len; i++) {
        if (arr[i] < arr[i - 1]) {
            int j = i - 1;
#if 0
            int tmp = arr[i];
            for (; j >= 0; j--) {
                if (arr[j] > tmp) {
                    arr[j + 1] = arr[j];
                    if (j == 0) {
                        arr[0] = tmp;
                    }
                } else {
                    arr[j + 1] = tmp;
                    break;
                }
            }
#else
            int tmp = arr[i];
            for (; j >= 0 && arr[j] > tmp; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = tmp;
#endif
        }
    }
}

void selectSort(int arr[], int len)
{
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] > arr[j]) {
                int tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

static void merge(int arr[], int start, int mid, int end, int tmpSpace[])
{
    int is = start;
    int ie = mid;
    int js = mid + 1;
    int je = end;
    int len = 0;
    while (is <= ie && js <= je) {
        if (arr[is] < arr[js]) {
            tmpSpace[len++] = arr[is++];
        } else {
            tmpSpace[len++] = arr[js++];
        }
    }
    while (is <= ie) {
        tmpSpace[len++] = arr[is++];
    }
    while (js <= je) {
        tmpSpace[len++] = arr[js++];
    }
    for (int i = 0; i < len; i++) {
        arr[start + i] = tmpSpace[i];
    }
}

void mergeSort(int arr[], int start, int end, int tmpSpace[])
{
    if (start == end) return;
    int m = start + (end - start) / 2;
    mergeSort(arr, start, m, tmpSpace);
    mergeSort(arr, m + 1, end, tmpSpace);
    merge(arr, start, m, end, tmpSpace);
}

void quickSort(int arr[], int start, int end)
{
    int i = start;
    int j = end;
    if (i < j) {
        int base = arr[i];
        while (i < j) {
            while (i < j && arr[j] > base) {
                j--;
            }
            if (i < j) {
                arr[i] = arr[j];
                i++;
            }
            while (i < j && arr[i] < base) {
                i++;
            }
            if (i < j) {
                arr[j] = arr[i];
                j--;
            }
        }
        arr[i] = base;
        quickSort(arr, start, i - 1);
        quickSort(arr, i + 1, end);
    }
}

static void myswap(int arr[], int i, int j)
{
    int tmp = arr[j];
    arr[j] = arr[i];
    arr[i] = tmp;
}

static void heap_adjust(int arr[], int idx, int len)
{
    int l = idx * 2 + 1;
    int r = idx * 2 + 2;
    int max_idx = idx;
    //if (r < len) {
    if (idx < len / 2) {
        if (l < len && arr[max_idx] < arr[l]) {
            max_idx = l;
        }
        if (r < len && arr[max_idx] < arr[r]) {
            max_idx = r;
        }
        if (max_idx != idx) {
            myswap(arr, idx, max_idx);
            heap_adjust(arr, max_idx, len);
        }
    }
}

void heapSort(int arr[], int len)
{
    int m = len / 2 + 1;
    for (int i = m; i >= 0 ; i--) {
        heap_adjust(arr, i, len);
    }
    for (int i = 0; i < len; i++) {
        myswap(arr, 0, len - i - 1);
        heap_adjust(arr, 0, len - i - 1);
    }
}

int bsearch(int arr[], int len, int value)
{
    int l = 0;
    int r = len - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == value) {
            std::cout << "found" << std::endl;
            return 1;
        } else if (arr[m] < value) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    std::cout << "not found" << std::endl;
    return 0;
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
    //bubbleSort(arr, MAX);
    //insertSort(arr, MAX);
    //selectSort(arr, MAX);
    //mergeSort(arr, 0, MAX - 1, tmp_arr);
    //quickSort(arr, 0, MAX - 1);
    heapSort(arr, MAX);
    //bsearch(arr, MAX, 5);
	printArray(arr, MAX);

    return 0;
}

// TIME ELAPSE: 20230203 
// TIME ELAPSE: 20230204 39min 
