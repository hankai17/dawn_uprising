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

// ((aa(())((
bool isvalid(std::string s) {
    int count = 0;
    for (char c : s) {
        if (c == '(') count++;
        else if (c == ')') {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

/*
p: )(() ((() ()() ()((
p1: (() )() )() )((
p2: (() (() (() (((
*/
std::vector<std::string> removeInvalidParentheses(std::string s) {
    std::vector<std::string> ans;
    std::queue<std::string> q;
    q.push(s);
    std::unordered_set<std::string> visited;
    visited.insert(s);
    bool found = false;

    while (!q.empty()) {
        for (int i = q.size(); i > 0; i--) {
            std::string temp = q.front();
            q.pop();
            if (isvalid(temp)) {
                found = true;
                std::cout << "ans: " << temp << std::endl;
                ans.push_back(temp);
            }

            for (int i = 0; i < temp.size(); i++) {
                if (temp[i] != '(' && temp[i] != ')')
                    continue;
                std::string str = temp.substr(0, i) + temp.substr(i + 1);
                std::cout << str << std::endl;
                if (!visited.count(str)) {
                    q.push(str);
                    visited.insert(str);
                }
            }
        }
        if(found) break;
    }
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << std::endl;
    }
    return ans;
}

int test()
{
    std::vector<int> v = { 10,9,2,18,100 };
    //std::cout << max_increase_subseq(v) << std::endl;
    //std::cout << robot_max(v) << std::endl;
    std::string s = "123456";
    std::cout << s.substr(2) << std::endl;
    //std::cout << s.substr(0, 0) + s.substr(0, 3) << std::endl;
    removeInvalidParentheses("()(()");
    return 0;
}

int main()
{
    test();
    return 0;
}
