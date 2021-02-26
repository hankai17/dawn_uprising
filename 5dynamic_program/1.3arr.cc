#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <string.h>
#include <unordered_set>

/*
int max_square(std::vector<std::vector<int>> matrix) {
    dp[i][j]表示以第i行第j列为右下角所能构成的最大正方形边长, 则递推式为: 
    dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
  int m = matrix.size();
  if (m < 1) return 0;

  int n = matrix[0].size();
  int max = 0;

  int dp[m+1][n+1];
  memset(&dp, 0x0, sizeof(dp));

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (matrix[i-1][j-1] == '1') {
        dp[i][j] = 1 + std::min(
              dp[i-1][j-1], 
              std::min(dp[i-1][j], dp[i][j-1])
            );
        max = std::max(max, dp[i][j]); 
      }
    }
  }
  return max * max;
}
*/

// dp[i] = std::max(dp[i], dp[idx_smal_i&val_saml_i] + 1)
int max_increase_subseq(std::vector<int> arr)
{
    if (arr.size() <= 1) return 1;
    std::vector<int> dp;
    dp.resize(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < dp.size(); i++) {
        res = std::max(res, dp[i]);
    }
    return res;
}

// dp[i] = std::max(dp[i - 1], arr[i] + dp[i - 2]);
int robot_max(std::vector<int> arr)
{
    if (arr.size() == 1) return arr[0]; 
    if (arr.size() == 2) {
       return arr[0] > arr[1] ? arr[0] : arr[1]; 
    }
    std::vector<int> dp; 
    dp.resize(arr.size());
    dp[0] = arr[0];
    dp[1] = arr[0] > arr[1] ? arr[0] : arr[1]; 

    for (int i = 2; i < arr.size(); i++) {
        dp[i] = std::max(dp[i - 1], arr[i] + dp[i - 2]);
    }
    return dp[arr.size() - 1];
}

// 随机选几个不重复数最终能合成sum * 1/2 
// dp[i][j] = dp[i - 1][j] || dp[i - 1][j - cur_val] (与换钱问题不同, 隐含条件是必须用一个)
int can_partion(std::vector<int> &v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    if (sum % 2 != 0) return 0;
    std::vector<std::vector<int>> dp(v.size(), 
          std::vector<int>(sum / 2 + 1, 0));

    for (int i = 0; i < v.size(); i++) {
        for (int j = 1; j <= sum / 2; j++) {
            if (!i) {
                dp[0][j] = v[0] == j ? 1 : 0;
            } else {
                if (j >= v[i]) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - v[i]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    return dp[v.size() - 1][sum / 2];
}

// dp[i][j] = std::max(dp[i - 1][j], dp[i -1][j - cur_val] + v)
int zero_one_pack()
{
    int w[] = {2,2,6,5,4};
    int v[] = {6,3,5,4,6};
    int c = 10;
    //int x[] = new int[5];
    //x[0] = 1;
    std::vector<std::vector<int>> dp = {5, std::vector<int>(11, 0)};

    for (int j = 1; j <= c; j++) {
        if (j >= w[0]) {
            dp[0][j] = v[0];
        }
    }

    for (int i = 1; i < 5; i++) {
        for (int j = 1; j <= c; j++) {
            if (j < w[i]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = std::max(dp[i-1][j-w[i]] + v[i], dp[i-1][j]);
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int test()
{
    //std::vector<int> v = { 10,9,2,18,100 };
    std::vector<int> v = { 1, 5, 11, 5};
    //std::cout << max_increase_subseq(v) << std::endl;
    //std::cout << robot_max(v) << std::endl;
    std::cout << can_partion(v) << std::endl;
    zero_one_pack();
    return 0;
}

int main()
{
    test();
    return 0;
}
