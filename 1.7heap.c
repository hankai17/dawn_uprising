#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>

#define MAX 20

void print_array(int arr[], int len){
	for (int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void my_swap(int arr[],int i,int j){

	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;

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
			my_swap(arr, index, max_idx);
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
		my_swap(arr, 0, i);
		heap_adjust(arr, 0, i);
	}
}

/*----------------------------------------------------------------get min K*/
#define K 5

void insert_heap(int arr[], int val, int idx)
{
    arr[idx] = val;
    while (idx != 0) {
        int p = (idx - 1) / 2;
        if (arr[p] < arr[idx]) {
            my_swap(arr, p, idx);
            idx = p;
        } else {
            break;
        }
    }
}

void get_min_K_num(int arr[], int len)
{
    int *heap = (int*)malloc(sizeof(int) * K);
    for (int i = 0; i < K; i++) {
        heap[i] = arr[i];
        insert_heap(heap, arr[i], i); 
    }

    for (int i = K; i < len; i++) {
        if (arr[i] < heap[0]) {
            heap[0] = arr[i];
            //heap_adjust(heap, 0, K - 1);
            heap_adjust(heap, 0, K);
        }
    }

    for (int i = 0; i < K; i++) {
        std::cout << heap[i] << " ";
    }
    std::cout << std::endl;
}

/*----------------------------------------------------------------get min K*/

int main()
{
	int arr[MAX];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % MAX;
	}
	print_array(arr, MAX);
	heap_sort(arr, MAX);
	print_array(arr, MAX);

    get_min_K_num(arr, MAX);
	return 0;
}
