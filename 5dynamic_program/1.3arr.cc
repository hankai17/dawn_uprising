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

int test()
{

}

int main()
{
    test();
    return 0;
}
