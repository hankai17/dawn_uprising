#include <iostream>
#include <vector>
#include <climits>
#include <string.h>

// dp[0][j] = dp[0][j - cur_val] + 1;
// dp[i][j] = std::min(dp[i-1][j], dp[i][j-cur_val] + 1);
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

    for (int i = 1; i < n; i++) {
        int tmp = max;
        for (int j = 1; j <= aim; j++) {
            if (j - arr[i] >= 0 && dp[i][j - arr[i]] != max) {
                tmp = dp[i][j - arr[i]] + 1;
            }
            dp[i][j] = std::min(tmp, dp[i -1][j]);
        }
    }
    return dp[n - 1][aim] != max ? dp[n - 1][aim] : -1;
}

// dp[i] = std::min(dp[i], dp[i - cur_coin] + 1)
int min_coin1(std::vector<int> coins, int aim)
{
    std::vector<int> dp(aim + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= aim; i++) {
        for (int j = 0; j < coins.size(); j++) {
            if (i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coins[j]] + 1); // dp[i] 是上一个相当于dp[i-1][j]
            }
        }
    }
    return dp[aim] > aim ? -1 : dp[aim]; 
}

// dp[i] = std::min(dp[i], dp[i - cur_idx^2] + 1)
int min_num_squares(int aim)
{
    std::vector<int> dp(aim + 1, INT_MAX);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= aim; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (j * j <= i && dp[i - j*j] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - j*j] + 1);
            }
        } 
    }
    return dp[aim] > aim ? -1 : dp[aim];
}

int test()
{
    int arr[] = { 5, 2, 3 };
    std::cout << "5 2 3 compose 20 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 20) << std::endl;
    std::cout << "5 2 3 compose 10 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 10) << std::endl;
    std::cout << "5 2 3 compose 2 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 2) << std::endl;
    std::cout << "5 2 3 compose 6 min coin: " << min_coin(arr, sizeof(arr)/sizeof(arr[0]), 6) << std::endl;

    std::vector<int> v = { 2};
    std::cout << min_coin1(v, 3) << std::endl;

    std::cout << min_num_squares(8) << std::endl;
    return 0;
}

int main()
{
    test();
    return 0;
}

