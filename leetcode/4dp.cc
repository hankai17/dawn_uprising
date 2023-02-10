// 5. 最长回文子串
string longestPalindrome(string s) {
        if (s.size() == 0) return "";
        int l = 0;
        int r = 0;

        //for (int i = 0; i < s.size() - 1; i++) {
            for (int i = 0; i < s.size(); i++) {
            int l1 = i;
            int r1 = i;
            int l2 = i;
            int r2 = i + 1;

            while (l1 >= 0 && r1 < s.size() && s[l1] == s[r1]) {
                l1--; r1++;
            }
            while (l2 >= 0 && r2 < s.size() && s[l2] == s[r2]) {
                l2--; r2++;
            }

            if (r1 - l1 - 1 > r - l + 1) {
                l = l1 + 1;
                r = r1 - 1;
            }
            if (r2 - l2 - 1 > r - l + 1) {
                l = l2 + 1;
                r = r2 - 1;
            }
        }
        return s.substr(l, r - l + 1);
    }

// 22. 括号生成
class Solution {
public:
    vector<string> res;

    void dfs(string track, int n, int l, int r) {
        if (r > l || l > n) return;
        if (l == n && l == r) res.push_back(track);

        dfs(track + '(', n, l + 1, r);
        dfs(track + ')', n, l, r + 1);
    }

    vector<string> generateParenthesis(int n) {
        dfs("", n, 0, 0);
        return res;
    }
};

// 32. 最长有效括号
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0;
        vector<int> dp(s.size(), 0);

        for (int i = 1; i < s.size(); i++) {
            if (s[i] == ')') {
                int pre = i - dp[i - 1] - 1;
                if (pre >= 0 && s[pre] == '(') {
                    dp[i] = dp[i - 1] + 2;
                    if (pre > 0) {
                        dp[i] += dp[pre - 1];
                    }
                }
            }
        }
        int res = dp[0];
        
        for (int i = 1; i < dp.size(); i++) {
            res = max(res, dp[i]);
        }
        return res;
    }
};

// 42. 接雨水
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> s;
        int sum = 0;

        for (int i = 0; i < height.size(); i++) {
            while (!s.empty() && height[s.top()] < height[i]) {
                int top_tmp = s.top();
                s.pop();
                if (s.empty()) break;

                int h = min(height[i], height[s.top()]) - height[top_tmp];
                sum += h * (i - s.top() - 1);
            }
            s.push(i);
        }
        return sum;
    }
};

// 45. 跳跃游戏 II
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), INT_MAX); // dp[i]: 到i位置需要跳跃的最小次数
        dp[0] = 0;

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= i; j++) {
                if (j + nums[j] >= i) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[nums.size() - 1];
    }
};

// 53. 最大子序和
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int max_sum = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            max_sum = max(sum, max_sum);
            if (sum < 0) {
                sum = 0;
            }
        }
        return max_sum;
    }
};

// 55. 跳跃游戏
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 0) return true;
        int cur = nums[0];
        int i = 1;
        for (; cur != 0 && i < nums.size(); i++) {
            cur--;
            cur = max(cur, nums[i]);
        }
        return i == nums.size();
    }
};

// 62. 不同路径
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }

// 63. 不同路径 II
      vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
      for (int i = 0; i < obstacleGrid.size(); i++) {
            for (int j = 0; j < obstacleGrid[0].size(); j++) {
                if (obstacleGrid[i][j] == 1) {
                    continue;
                }
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];

// 64. 最小路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> sum(grid.size(), vector<int>(grid[0].size(), 0));
        sum[0][0] = grid[0][0];
        for (int i = 1; i < grid.size(); i++) {
            sum[i][0] = sum[i - 1][0] + grid[i][0];
        }
        for (int i = 1; i < grid[0].size(); i++) {
            sum[0][i] = sum[0][i - 1] + grid[0][i];
        }

        for (int i = 1; i < grid.size(); i++) {
            for (int j = 1; j < grid[0].size(); j++) {
                sum[i][j] = min(
                    sum[i - 1][j],
                    sum[i][j - 1]
                ) + grid[i][j];
            }
        }
        return sum[grid.size() - 1][grid[0].size() - 1];
    }
};

// 70. 爬楼梯
class Solution {
public:
    int climbStairs(int n) {
        /*
        if (n <= 0) return 0;
        if (n <= 2) return n;
        return climbStairs(n - 2) + climbStairs(n - 1);
        */
        if (n <= 0) return 0;
        if (n <= 2) return n;
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 2] + dp[i - 1];
        }
        return dp[n];
    }
};

// 72. 编辑距离
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1)); //dp[i][j] 从word[0-i] 变成word[0-j] 需要的步数

        for (int m = 0; m <= len1; m++) {
            dp[m][0] = m;
        }

        for (int m = 0; m <= len2; m++) {
            dp[0][m] = m;
        }

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                }
            }
        }
        return dp[len1][len2];
    }
};

// 95. 不同的二叉搜索树 II
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n) return generate(1, n);
        else return vector<TreeNode*> {};
    }

    vector<TreeNode*> generate(int left, int right) {
        vector<TreeNode*> res;
        if (left > right) {
            res.push_back(nullptr);
            return res;
        }

        for (int i = left; i <= right; i++) {
            vector<TreeNode*> left_nodes = generate(left, i - 1);
            vector<TreeNode*> right_nodes = generate(i + 1, right);
            for (TreeNode *left_node : left_nodes) {
                for (TreeNode *right_node : right_nodes) {
                    TreeNode *t = new TreeNode(i);
                    t->left = left_node;
                    t->right = right_node;
                    res.push_back(t);
                }
            }
        }
        return res;
    }
};

// 96. 不同的二叉搜索树
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};

// 118. 杨辉三角
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);   //定义一个numRows行的二维数组
        for(int i =0; i<numRows; i++)
        {
            res[i].resize(i+1, 1);
            for(int j=1; j<i; j++)
            {
                res[i][j] = res[i-1][j-1]+res[i-1][j]; //利用杨辉三角的形式 第n行第k个数等于 第n-1行第k-1和k个数的和
            }
        }
        return res;
    }
};

// 121. 买卖股票的最佳时机
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        #if 0
        vector<int> dp(prices.size(), 0);

        // dp[i] = std::max(dp[i] - prices[0-i])
        int tmp = 0;
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (prices[j] < prices[i]) {
                    tmp = max(tmp, prices[i] - prices[j]);
                }
            }
        }
        return tmp;
        #else
        if (prices.size() <= 1) return 0;
        int min_input = prices[0];
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            min_input = min(min_input, prices[i]);
            res = max(res, prices[i] - min_input);
        }
        return res;
        #endif
    }
};

// 122. 买卖股票的最佳时机 II
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;      
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i - 1]) {
                res += prices[i] - prices[i - 1];
            }
        }
        return res;
    }
};

// 131. 分割回文串
class Solution {
public:
    vector<vector<string>> res;
    vector<string> tmp;

    bool is_pa(string s) {
        int i = 0;
        int j = s.size() - 1;
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++; j--;
        }
        return true;
    }

    void dfs(string s, int l, int r) {
        if (l > r) {
            res.push_back(tmp);
            return;
        }

        for (int i = 1; i <= r - l + 1; i++) {
            if (is_pa(s.substr(l, i))) {
                tmp.push_back(s.substr(l, i));
                dfs(s, l + i, r);
                tmp.pop_back();
            }
        }
    }


    vector<vector<string>> partition(string s) {
        dfs(s, 0, s.size() - 1);
        return res;
    }
};

// 152. 乘积最大子数组
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max = nums[0];
        int min = nums[0];
        int res = nums[0];
        int max_end = 0;
        int min_end = 0;
        for (int i = 1; i < nums.size(); i++) {
            max_end = max * nums[i];
            min_end = min * nums[i];
            max = std::max(std::max(max_end, min_end),
            nums[i]);
            min = std::min(std::min(max_end, min_end),
            nums[i]);
            res = std::max(res, max);
        }
        return res;
    }
};

// 198. 打家劫舍
class Solution {
public:
    int rob(vector<int>& arr) {
        if (arr.size() == 0) return 0;
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
};

// 221. 最大正方形
class Solution {
public:
    bool is_one(vector<vector<char>>& matrix, int r, int c, int k) {
        int all_row = matrix.size();
        int all_col = matrix[0].size();
        if (r >= all_row || c >= all_col) return false;
        if (r + k > all_row || c + k > all_col) return false;
        for (int i = r; i <= r + k - 1; i++) {
            for (int j = c; j <= c + k - 1; j++) {
                if (matrix[i][j] != '1') {
                    return false;
                }
            }
        }
        return true;
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        int res = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                for (int k = 1; k <= std::min(matrix.size() - i, matrix[0].size() - j); k++) {
                     if (is_one(matrix, i, j, k)) {
                        res = std::max(k * k, res);
                     } 
                }
            }
        }
        return res;
    }
};

// 279. 完全平方数
class Solution {
public:
    int numSquares(int n) {
        if (n == 1) return 1;
        vector<int> dp(n + 1, INT_MAX);
        dp [0] = 0;
        dp [1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j*j <= i; j++) {
                if (i >= j*j && dp[i - j*j] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - j*j] + 1);
                }
            }
        }
        return dp[n] > n ? -1 : dp[n];
    }
};

// 300. 最长递增子序列
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) return 1;
        std::vector<int> dp;
         dp.resize(nums.size());

    for (int i = 0; i < nums.size(); i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
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
};

// 322. 零钱兑换
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount]; 
    }
};

// 337. 打家劫舍 III
class Solution {
public:
    int try_rob(TreeNode* root) {
        if (!root) return 0;
        int res1 = 0;
        res1 += root->val;
        if (root->left) {
            res1 += (try_rob(root->left->right) + try_rob(root->left->left));
        }
        if (root->right) {
            res1 += (try_rob(root->right->left) + try_rob(root->right->right));
        }

        int res2 = 0;
        res2 += (try_rob(root->left) + try_rob(root->right));
        
        int res = max(res1, res2);
        return res; 
    }

    int rob(TreeNode* root) {
        return try_rob(root);
    }
};

// 338. 比特位计数
class Solution {
public:
    int count_one_bits(int n)
    {
        int count = 0;
        while (n)
        {
            n = n & (n - 1);
            count++;
        }
        return count;
    }

    vector<int> countBits(int num) {
        vector<int> res;
        res.resize(num + 1);
        for (int i = 0; i <= num; i++) {
            res[i] = count_one_bits(i);
        }
        return res;
    }
};

// 416. 分割等和子集
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (sum % 2 != 0) return 0;
        std::vector<std::vector<int>> dp(nums.size(),
            std::vector<int>(sum / 2 + 1, 0));

        for (int i = 0; i < nums.size(); i++) {
            for (int j = 1; j <= sum / 2; j++) {
                if (!i) {
                    dp[0][j] = nums[0] == j ? 1 : 0;
                } else {
                    if (j >= nums[i]) {
                        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
                    } else {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
            }
        }
        return dp[nums.size() - 1][sum / 2];
    }
};

// 494. 目标和
class Solution {
public:
    // sum(P) = (target + sum(nums)) / 2
    int findTargetSumWays(vector<int>& nums, int S) {
    // 转化成nums中和为(sum + S) / 2的子序列个数
    // dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]]
    // dp[j] = dp[j] + dp[j - nums[i]]
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) sum += nums[i];
    if (S > sum || S < -sum || (sum + S) % 2 == 1) return 0;
    int len = (sum + S) / 2;
    int *dp = new int[len + 1];
    memset(dp, 0x0, sizeof(int) * (len+1));
    dp[0] = 1;

    for (int i = 0; i < nums.size(); i++) {
        for (int j = len; j >= nums[i]; j--) {
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp[len];

    }
};

// 647. 回文子串
class Solution {
public:
    int countSubstrings(string s) {
        /*
        int n = s.size();
        int res = n;
        for (int i = 1; i < n; i++) {
            int l = i, r = i - 1;
            while (--l >= 0 && ++r < n && s[l] == s[r]) res++;
            l = i; r = i;
            while (--l >= 0 && ++r < n && s[l] == s[r]) res++;
        }
        */
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            int l = i, r = i;
            while (l >= 0 && r < n && s[l] == s[r]) {
                res++;
                l--;
                r++;
            }
            
            l = i; r = i + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                res++;
                l--;
                r++;
            }
            
        }
        return res;
    }
};



