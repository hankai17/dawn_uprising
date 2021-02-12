
// 十个二分九个错
// 唐纳德·克努特（Donald E.Knuth）在《计算机程序设计艺术》的第 3 卷《排序和查找》中
// 说到：“尽管第一个二分查找算法于 1946 年出现，然而第一个完全正确的二分查找算法实
// 现直到 1962 年才出现。

int bsearch(int a[], int n, int value) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {         // 注意1
	int mid = (low + high) / 2; // 注意2 两者之和可能会溢出 可以改成low+(high-low)/2  高效点low+((high-low)>>1)
	if (a[mid] == value) {
	  return mid;
	} else if (a[mid] < value) {
	  low = mid + 1;            // 注意3
	} else {
	  high = mid - 1;
	}
  }
  return -1;
}

// 查找序列中(序列中有重复元素)第一个值等于给定值的元素
int bsearch(int[] a, int n, int value) {
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

int bsearch(int[] a, int n, int value) { // 效果与上一样
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

// 查找最后一个值等于给定值的元素
int bsearch(int[] a, int n, int value) {
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
int bsearch(int[] a, int n, int value) {
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
int bsearch(int[] a, int n, int value) {
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
    return left;
}

