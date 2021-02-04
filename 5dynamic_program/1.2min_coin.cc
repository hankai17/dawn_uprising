#include <iostream>
#include <string.h>

int min_coin(int arr[], int coin_obj, int aim)
{
    if (arr == NULL || coin_obj == 0 || aim < 0) return -1;
    int n = coin_obj;
    int max = 0x7FFFFFFF;
    int dp[n][aim + 1];
    memset(dp, 0x0, sizeof(dp));

    for (int i = 1; i < aim + 1; i++) {
        dp[0][i] = max; 
        if (i - arr[0] >= 0 && dp[0][i - arr[0]] != max) {
            dp[0][i] = dp[0][i - arr[0]] + 1;         
        }
    }
    /*
    for (int i = 0; i < coin_obj; i++) {
        for (int j = 0; j < aim + 1; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */

    for (int i = 1; i < n; i++) {
        int tmp = max;
        for (int j = 1; j < aim + 1; j++) {
            if (j - arr[i] >= 0 && dp[i][j - arr[i]] != max) {
                tmp = dp[i][j - arr[i]] + 1;
            }
            dp[i][j] = std::min(tmp, dp[i -1][j]);
        }
    }
    return dp[n - 1][aim] != max ? dp[n - 1][aim] : -1;
}

int main()
{
    int arr[] = { 5, 2, 3 };
    std::cout << "5 2 3 compose 20 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 20) << std::endl;
    std::cout << "5 2 3 compose 10 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 10) << std::endl;
    std::cout << "5 2 3 compose 2 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 2) << std::endl;
    std::cout << "5 2 3 compose 6 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 6) << std::endl;
    return 0;
}
