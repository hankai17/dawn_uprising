#include <iostream>
#include <vector>
#include <string.h>

int max_square(std::vector<std::vector<int>> matrix) {
  /**
    dp[i][j]表示以第i行第j列为右下角所能构成的最大正方形边长, 则递推式为: 
    dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
   **/
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

// max increase subseq
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

int test()
{
    std::vector<int> v = { 10,9,2,5,3,7,101,18 };
    std::cout << max_increase_subseq(v) << std::endl;
    return 0;
}

int main()
{
    test();
    return 0;
}
