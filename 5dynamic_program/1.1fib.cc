#include <iostream>
#include <string.h>

long long fibonacci(int n)
{
    //return n <= 2 ? n : fibonacci(n - 1) + fibonacci(n - 2); // 30day can generate new
    return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2); // 60day can generate new
}

// https://www.cnblogs.com/zkfopen/p/11245857.html
// https://blog.csdn.net/zyw0101/article/details/80542988
// https://www.mobibrw.com/2020/23429

long long fibonacci1(int n)
{
    if (n <= 2) {
        return 1;
    }
    long long f1 = 1;
    long long f2 = 1;
    long long f3 = 0;

    for (int i = 3; i < n; i++) {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }
    return f3;
}

/*------------------------------------------------------ N STEP SKIP 1/2 */

// 1 2 3 4 ==> 1 2 3 5
int n_method(int n)
{
    return n <= 2 ? n : n_method(n - 2) + n_method(n - 1);
}

/*------------------------------------------------------ N STEP SKIP 1/2 */

/*------------------------------------------------------ MIN PATH SUM */

#define K 3
int min_path_sum(int arr[][K], int n)
{
    if (n == 0) return 0;
    int arr_sum[n][K];
    memset(&arr_sum, 0x0, sizeof(int) * n * K);
    arr_sum[0][0] = arr[0][0];

    for (int i = 1; i < n; i++) {
        arr_sum[i][0] = arr[i][0] + arr_sum[i - 1][0];
    }
    for (int i = 1; i < K; i++) {
        arr_sum[0][i] = arr[0][i] + arr_sum[0][i - 1];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < K; j++) {
            arr_sum[i][j] = std::min(arr_sum[i - 1][j], arr_sum[i][j - 1]) + arr[i][j];
        }
    }
    return arr_sum[n - 1][K - 1];
}

/*------------------------------------------------------ MIN PATH SUM */

void test()
{
    for (int i = 1; i < 5; i++) {
        std::cout << fibonacci(i) << std::endl;
    }

    int arr[][K] = { {1, 3, 1}, {1, 5, 1}, {4, 2, 1} };
    std::cout << min_path_sum(arr, sizeof(arr)/sizeof(arr[0])) << std::endl;

    return;
}

int main()
{
    test();
    return 0;
}
