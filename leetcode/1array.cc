// 1. 两数之和
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (m.count(target - nums[i])) {
                res.push_back(m[target - nums[i]]);
                res.push_back(i);
                return res;
            } else {
                m[nums[i]] = i;
            }
        }
        res.push_back(-1);
        res.push_back(-1);
        return res;
    }
};

// 11. 盛最多水的容器
class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = INT_MIN;
        int l = 0;
        int r = height.size() - 1;

        while (l < r) {
            area = max(area, min(height[l], height[r]) * (r - l));
            if (height[l] > height[r]) {
                r--;
            } else {
                l++;
            }
        }
        return area;
    }
};

// 15. 三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int cur;
        for (int i = 0; i < nums.size(); i++) {
            if ((cur = nums[i]) > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int l = i + 1;
            int r = nums.size() - 1;
            while (l < r) {
                if (nums[l] + nums[r] + cur < 0) {
                    l++;
                } else if (nums[l] + nums[r] + cur > 0) {
                    r--;
                } else {
                    res.push_back(vector<int> {cur, nums[l], nums[r]});
                    l++; 
                    r--;
                    while (l < r && nums[l] == nums[l - 1]) l++; 
                    while (l < r && nums[r] == nums[r + 1]) r--;
                }
            }
        }
        return res;
    }
};

// 16. 最接近的三数之和  
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int cur;
        
        int min_sum = nums[0] + nums[1] + nums[2]; // int min_sum = INT_MAX; 溢出
      
        for (int i = 0; i < nums.size() - 2; i++) { // 也可写成 i < nums.size()
            cur = nums[i];
            int l = i + 1;
            int r = nums.size() - 1;
            if (i > 0 && nums[i] == nums[i - 1]) continue; // 12ms -> 4ms

            while (l < r) {
                int sum = cur + nums[l] + nums[r];
                if (abs(sum - target) < abs(min_sum - target)) {
                    min_sum = sum;
                }
                if (sum > target) {
                    r--;
                } else if (sum < target) {
                    l++;
                } else {
                    return target;
                }
            }
        }
        
        return min_sum;
    }
};

// 18. 四数之和
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) { // 一下子反应出来需要哪些变量 i j l r
        vector<vector<int>> res;
        if (nums.size() == 0) return res;
        sort(nums.begin(), nums.end());
        int cur;
        for (int i = 0; i < nums.size(); i++) {
            cur = nums[i];
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int new_target = target - cur;
            for (int j = i + 1; j < nums.size(); j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue; // 坑了一把
                int new_target1 = new_target - nums[j];
                int l = j + 1;  
                int r = nums.size() - 1;
                while (l < r) {
                    if (nums[l] + nums[r] < new_target1) {
                        l++;
                    } else if (nums[l] + nums[r] > new_target1) {
                        r--;
                    } else {
                        res.push_back(vector<int> {cur, nums[j], nums[l], nums[r]});
                        l++; 
                        r--;
                        while (l < r && nums[l] == nums[l - 1]) l++; 
                        while (l < r && nums[r] == nums[r + 1]) r--;
                    }
                }

            }
        }
        return res;
    }
};

// 26. 删除有序数组中的重复项 
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int i = 0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[i] != nums[j]) {
                nums[++i] = nums[j];
            }
        }
        return ++i;
    }
};

// 27. 移除元素
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    int k = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
    }
};

// 31. 下一个排列
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = 0;
        for (i = nums.size() - 1; i > 0; i--) {
            if (nums[i - 1] < nums[i]) {
                int min_idx = i;
                for (int j = i; j < nums.size(); j++) {
                    if (nums[j] < nums[min_idx] && nums[j] > nums[i - 1]) {
                        min_idx = j;
                    }
                }
                swap(nums[i - 1], nums[min_idx]);
                break;
            }
        }
        sort(nums.begin() + i, nums.end());
    }
};

// 33. 搜索旋转排序数组
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < nums[r]) { //右边有序
                if (nums[mid] < target && target <= nums[r]) { // if (nums[mid] < target) {  在有序的一端做严格的判断
                    l = mid + 1;
                } else { // 进入无序态
                    r = mid - 1;
                }
            } else {
                if (nums[l] <= target && target < nums[mid]) { // if (target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        return -1;
    }
};

// 34. 在排序数组中查找元素的第一个和最后一个位置
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {        
        int l = 0;
        int r = nums.size() - 1;

        vector<int> res;
        int b = -1;
        int e = -1;
        
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > target) {
                r = mid - 1;
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
                b = mid;
                r = mid - 1;
            }
        }

        l = 0;
        r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > target) {
                r = mid - 1;
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
                e = mid;
                l = mid + 1;
            }
        }
        
        res.push_back(b);
        res.push_back(e);
        return res;
    }
};

// 35. 搜索插入位置
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};

// 39. 组合总和 // nums = [2 3 6 7] target = 7 resu = [[2 2 3][7]]
class Solution {
public:
    vector<vector<int>> res;
    
    void dfs(vector<int>& candidates, int target, vector<int> &track, int start) {
        if (target < 0) return;
        if (target == 0) {
            res.push_back(track);
            return;
        }
        for (int i = start; i < candidates.size(); i++) { // 允许重复 但不允许有顺序区别
            track.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], track, i); /// 注意这里传的是i 意思是数组中的每个元素可以用无数次
                                                               /// 如果传i+1则 数组中每个元素只能用一次
            track.pop_back();
        }
    }
    

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> track;
        dfs(candidates, target, track, 0);
        //dfs(candidates, target, track); //超时
        return res;
    }
    
};

// 40. 组合总和 II // nums = [1 1 2 5 6 7 10] target = 8 resu = [[1 7] [1 2 5] [2 6] [1 1 6]]
class Solution {
public:
    vector<vector<int>> res;
    void dfs(vector<int>& candidates, int target, vector<int> &track, int start) {
        if (target < 0) return;
        if (target == 0) {
            res.push_back(track);
            return;
        }
       
        for (int i = start; i < candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i - 1]) { // 1) 手动去重
                continue;
            }
            track.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], track, i + 1); // 0) 不允许重复
            track.pop_back();
        }
    }


    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> track;
        sort(candidates.begin(), candidates.end()); // 1) 手动去重
        dfs(candidates, target, track, 0);
        return res;
    }
};

// 41. 缺失的第一个正数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if (nums.size() == 0) return 1;
        vector<int> dp(nums.size() + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] >= 1 && nums[i] < dp.size()) {
                dp[nums[i]] = 1;
            }
        }
        for (int i = 0; i < dp.size(); i++) {
            if (dp[i] == 0) {
                return i;
            }
        }
        return dp.size();
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
        vector<int> dp(nums.size(), INT_MAX);
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

// 46. 全排列
class Solution {
public:
    vector<vector<int>> res;

    void dfs(vector<int>& nums, vector<int>& visited, vector<int> track) {
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] == 1) {
                continue;
            }

            visited[i] = 1;
            track.push_back(nums[i]);
            dfs(nums, visited, track);

            track.pop_back();
            visited[i] = 0;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> track;
        vector<int> visited(nums.size(), 0);
        dfs(nums, visited, track);
        return res;
    }

};

// 47. 全排列 II
class Solution {
public:
    vector<vector<int>> res;
    #if 0
    vector<int> temp;vector<vector<int>> res;
    void dfs(vector<int>& nums,int n,vector<int>& vis)
    {
        if(n==nums.size()) {res.push_back(temp);return;}
        
        for(int i=0;i<nums.size();i++)
            if(vis[i]==0)
            {
                if(i>0 && nums[i]==nums[i-1] && vis[i-1]!=0) continue;
                temp.push_back(nums[i]);
                vis[i]=1;
                dfs(nums,n+1,vis);
                vis[i]=0;
                temp.pop_back();
            }
    }
   
    #endif

    void dfs(vector<int>& nums, vector<int>& visited, vector<int> track) {
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] == 1) {
                continue;
            }
            if (i > 0 && nums[i] == nums[i - 1] && visited[i - 1] == 1) {
                continue;
            }
            visited[i] = 1;
            track.push_back(nums[i]);
            dfs(nums, visited, track);

            track.pop_back();
            visited[i] = 0;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> track;
        vector<int> visited(nums.size(), 0);
        sort(nums.begin(), nums.end());
        dfs(nums, visited, track);
        return res;
    }
}

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

// 48. 旋转图像 
class Solution {
public:
    void rota(vector<vector<int>>& matrix, int lu_i, int lu_j, 
            int rd_i, int rd_j) {
        for (int i = 0; i < rd_i - lu_i; i++) {
            int tmp = matrix[lu_i][lu_j + i];
            matrix[lu_i][lu_j + i] = matrix[rd_i - i][lu_j];
            matrix[rd_i - i][lu_j] = matrix[rd_i][rd_j - i];
            matrix[rd_i][rd_j - i] = matrix[lu_i + i][rd_j];
            matrix[lu_i + i][rd_j] = tmp;
        }
    }

    void rotate(vector<vector<int>>& matrix) {
        int lu_i = 0;
        int lu_j = 0;
        int rd_i = matrix.size() - 1;
        int rd_j = matrix.size() - 1;

        while (lu_i < rd_i) {
            rota(matrix, lu_i, lu_j, rd_i, rd_j);
            lu_i++; lu_j++;
            rd_i--; rd_j--;
        }
    }
};

// 54. 螺旋矩阵
class Solution {
public:
    vector<int> res;
    
    void spiral_print(vector<vector<int>>& matrix, int lu_i, int lu_j,
                     int rd_i, int rd_j) {
        if (lu_i == rd_i) {
            while (lu_j <= rd_j) {
                res.push_back(matrix[lu_i][lu_j++]);
            }
            return;
        }
        if (lu_j == rd_j) {
            while (lu_i <= rd_i) {
                res.push_back(matrix[lu_i++][rd_j]);
            }
            return;
        }
        
        int i = lu_i;
        int j = lu_j;
        while (j < rd_j) {
            res.push_back(matrix[lu_i][j]);
            j++;
        }
        
        while (i < rd_i) {
            res.push_back(matrix[i][rd_j]);
            i++;
        }
        
        while (j > lu_j) {
            res.push_back(matrix[rd_i][j]);
            j--;
        }
        
        while (i > lu_i) {
            res.push_back(matrix[i][lu_j]);
            i--;
        }
        
    }
    
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int lu_i = 0;
        int lu_j = 0;
        int rd_i = matrix.size() - 1;
        int rd_j = matrix[0].size() - 1;
        
        while (lu_i <= rd_i && lu_j <= rd_j) {
            spiral_print(matrix, lu_j, lu_j, rd_i, rd_j);
            lu_i++; lu_j++;
            rd_i--; rd_j--;
        }
        return res;
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

// 56. 合并区间
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size(); i++) {
            if (res.empty()) {
                res.push_back(intervals[i]);
            } else {
                if (intervals[i][0] <= res.back()[1]) {
                    res.back()[1] = max(res.back()[1], intervals[i][1]);
                } else {
                    res.push_back(intervals[i]);
                }
            }
        }
        return res;
    }
};

// 57. 插入区间
class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) {
            intervals.push_back(newInterval);
            return intervals;
        }
        intervals.emplace_back(newInterval);

        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size(); i++) {
            if (res.empty()) {
                res.push_back(intervals[i]);
            } else {
                if (intervals[i][0] <= res.back()[1]) {
                    res.back()[1] = max(res.back()[1], intervals[i][1]);
                } else {
                    res.push_back(intervals[i]);
                }
            }
        }
        return res;

    }
};

// 59. 螺旋矩阵 II
class Solution {
public:
    int count1 = 1;

    void spiral_print(vector<vector<int>>& matrix, int lu_i, int lu_j,
                     int rd_i, int rd_j) {
        if (lu_i == rd_i) {
            matrix[lu_i][lu_j] = count1;
        }

        int i = lu_i;
        int j = lu_j;
        while (j < rd_j) {
            matrix[lu_i][j] = count1++;
            j++;
        }
        
        while (i < rd_i) {
            matrix[i][rd_j] = count1++;
            i++;
        }
        
        while (j > lu_j) {
            matrix[rd_i][j] = count1++;
            j--;
        }
        
        while (i > lu_i) {
            matrix[i][lu_j] = count1++;
            i--;
        }
        
    }
    
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int lu_i = 0;
        int lu_j = 0;
        int rd_i = n - 1;
        int rd_j = n - 1;

        while (lu_i <= rd_i && lu_j <= rd_j) {
            spiral_print(res, lu_j, lu_j, rd_i, rd_j);
            lu_i++; lu_j++;
            rd_i--; rd_j--;
        }
        
        return res;
    }
};

// 63. 不同路径 II
class Solution {
public:

/*
我说句题外话，就是何时使用【回溯】，何时使用【动态规划】，用大白话说，就是：

首先看取值范围，递归回溯一维数组，100就是深度的极限了（何况本题是100²） 2.如果是求走迷宫的【路径】，必然是回溯；如果是走迷宫的【路径的条数】，必然是dp--------(这个竟然屡试不爽！！！！)
*/
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
        #if 1
        for (int i = 0; i < obstacleGrid[0].size(); i++) {
            if (obstacleGrid[0][i] == 1) {
                break;
            }
            dp[0][i] = 1;
        }

        for (int i = 0; i < obstacleGrid.size(); i++) {
            if (obstacleGrid[i][0] == 1) {
                break;
            }
            dp[i][0] = 1;
        }

        for (int i = 1; i < obstacleGrid.size(); i++) {
            for (int j = 1; j < obstacleGrid[0].size(); j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                    continue;
                }

                if (obstacleGrid[i - 1][j] == 1 && obstacleGrid[i][j - 1] == 1) {
                    dp[i][j] = 0;
                }
                if (obstacleGrid[i - 1][j] == 1 && obstacleGrid[i][j - 1] == 0) {
                    dp[i][j] = dp[i][j - 1];
                }
                if (obstacleGrid[i - 1][j] == 0 && obstacleGrid[i][j - 1] == 1) {
                    dp[i][j] = dp[i - 1][j];
                }
                if (obstacleGrid[i - 1][j] == 0 && obstacleGrid[i][j - 1] == 0) {
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                }
            }
        }
        #else

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
        #endif

        return dp[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
    }
};

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

// 66. 加一
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        int op = 0;
        res.push_back((digits[digits.size() - 1] + 1) % 10);
        op = (digits[digits.size() - 1] + 1) / 10;

        for (int i = digits.size() - 2; i >= 0; i--) {
            res.push_back((digits[i] + op) % 10);
            op = (digits[i] + op) / 10;
        }

        if (op == 1) {
            res.push_back(1);
        }
        vector<int> tmp;
        for (int i = res.size() - 1; i >= 0; i--) {
            tmp.push_back(res[i]);
        }
        return tmp;
    }
};

// 73. 矩阵置零
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int i_f = 0;
        int j_f = 0;
        int len1 = matrix.size();
        int len2 = matrix[0].size();

        for (int i = 0; i < len1; i++) {
            if (matrix[i][0] == 0) {
                i_f = 1;
            }
        }

        for (int i = 0; i < len2; i++) {
            if (matrix[0][i] == 0) {
                j_f = 1;
            }
        }

        for (int i = 1; i < len1; i++) {
            for (int j = 1; j < len2; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < len1; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 0; j < len2; j++) {
                    matrix[i][j] = 0;
                }
            }
        }

        for (int j = 1; j < len2; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 0; i < len1; i++) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (j_f) {
            for (int i = 0; i < len2; i++) {
                matrix[0][i] = 0;
            }
        }

        if (i_f) {
            for (int j = 0; j < len1; j++) {
                matrix[j][0] = 0;
            }
        }
    }
};

// 74. 搜索二维矩阵
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0;
        int j = matrix[0].size() - 1;

        while (i < matrix.size() && j >= 0) {
            if (matrix[i][j] == target) {
                return true;
            } else if (matrix[i][j] > target) {
                j--;
            } else {
                i++;
            }
        }
        return false;
    }
};

// 75. 颜色分类
class Solution {
public:
    void quic_sort(vector<int>& nums, int i, int j) {
        int start = i;
        int end = j;
        
        if (i < j) {
            int base = nums[i];
            while (i < j) {
                while (i < j && nums[j] > base) {
                    j--;
                }
                if (i < j) {
                    nums[i] = nums[j];
                    i++;
                }
                while (i < j && nums[i] < base) {
                    i++;
                }
                if (i < j) {
                    nums[j] = nums[i];
                    j--;
                }
            }
            nums[i] = base;
            quic_sort(nums, start, i - 1);
            quic_sort(nums, i + 1, end);
        }
    }

    void sortColors(vector<int>& nums) {
        int s = nums.size();
        if (s <= 0) return;
        quic_sort(nums, 0, s - 1);
    }
};

// 77. 组合
class Solution {
public:
#if 1
    vector<vector<int>> res;

    void dfs(vector<int> &vec, int start, vector<int> track, int k) {
        if (track.size() == k) {
            res.push_back(track);
            return;
        }

        for (int i = start; i < vec.size(); i++) {  // 是start 非start+1
            track.push_back(vec[i]);
            dfs(vec, i + 1, track, k);
            track.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<int> vec;
        vector<int> track;
        for (int i = 1; i <= n; i++) {
            vec.push_back(i);
        }
        dfs(vec, 0, track, k);
        return res;
    }
#else
    vector<vector<int>> res;
    vector<int> temp;
    void dfs(vector<int>& temp,int n,int k,int start) {
        if(temp.size()==k){
            res.push_back(temp);
            return;
        }
        for(int i=start+1;i<=n;i++){
            temp.push_back(i);
            dfs(temp,n,k,i);
            temp.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        dfs(temp,n,k,0);
        return res;
    }
#endif
};

// 78. 子集
class Solution {
public:
#if 0
    vector<vector<int>> subsets(vector<int>& nums) {
       vector<vector<int>> res={{}};
    for (int i = 0; i < nums.size(); i++) {
        int len = res.size();
        for (int j = 0; j < len; j++) {
            vector<int> temp = res[j]; //取出1个旧的子集
            temp.push_back(nums[i]); //加入新的元素，组成1个新子集
            res.push_back(temp); //更新解集
        }
    };
    return res;
    }
#else
    vector<vector<int>> res;
    void dfs(vector<int> &nums, vector<int> &track, int idx) {
        for (int i = idx; i < nums.size(); i++) {
            track.push_back(nums[i]);
            res.push_back(track);
            dfs(nums, track, i + 1);
            track.pop_back();
        }
        return;
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> track;
        res.push_back({});
        dfs(nums, track, 0);
        return res;
    }

#endif    
};

// 79. 单词搜索
class Solution {
public:

    bool dfs(vector<vector<char>>& board, string &word, 
            int size, int i, int j, vector<vector<int>> &visited) {
        if (size == word.size()) {
            return true;
        }

        if (i < 0 || i > board.size() - 1 ||
            j < 0 || j > board[0].size() - 1 ||
            board[i][j] != word[size]) {
                return false;
        }

        // board[i][j] == word[size] 本dfs值相等
        if (visited[i][j] == 0) {
            visited[i][j] = 1;
            if (dfs(board, word, size + 1, i + 1, j, visited) ||
                    dfs(board, word, size + 1, i, j + 1, visited) ||
                    dfs(board, word, size + 1, i - 1, j, visited) ||
                    dfs(board, word, size + 1, i, j - 1, visited)) {
                return true;
            }
            visited[i][j] = 0;
        }
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || word.empty()) {
            return false;
        }
        vector<vector<int>> f(board.size(), vector<int>(board[0].size(), 0));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (dfs(board, word, 0, i, j, f)) {
                    return true;
                }
            }
        }
        return false;
    }
};

// 80. 删除有序数组中的重复项 II
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) return 0;
        int i = 0;
        int j = 1;
        int flag = 1;

        while (j < nums.size()) {
            if (nums[i] != nums[j] || flag == 2) {
                nums[++i] = nums[j];
                j++;
                flag = 1;
            } else {
                i++;
                j++;
                flag += 1;
            }
        }
        return i + 1;
    }
};

// 81. 搜索旋转排序数组 II
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            while(l<r&&nums[l]==nums[l+1]) ++l;
            while(l<r&&nums[r]==nums[r-1]) --r;
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return true;
            else if (nums[mid] < nums[r]) { //右边有序
                if (nums[mid] < target && target <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            } else {
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        return false;
    }
};

// 84. 柱状图中最大的矩形
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> s;
        int maxArea = 0;
        for (int i = 0; i<heights.size(); i++) {
            while (!s.empty() && heights[i] < heights[s.top()]) {
                int top= s.top();
                s.pop();
                maxArea = max(maxArea, 
                        heights[top] * (s.empty() ? i : (i - s.top() -1))
                        );
            }
            s.push(i);
        }
        return maxArea;
    }
};

// 88. 合并两个有序数组
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int last = m + n - 1;
        while (n) {
            if (m == 0 || nums1[m - 1] <= nums2[n - 1]) {
                n--;
                nums1[last] = nums2[n];
                last--;
            } else {
                m--;
                nums1[last] = nums1[m];
                last--;
            }
        }
    }
};

// 105. 从前序与中序遍历序列构造二叉树
class Solution {
public:
    TreeNode* pre_in(vector<int>& pre, int pi, int pj, vector<int>& in, int ni, int nj, map<int,int> &in_map) {
        if (pi > pj || ni > nj) return NULL;
        TreeNode* root = new TreeNode;
        root->val = pre[pi];

        auto it = in_map.find(root->val);
        int idx = it->second;

        root->left = pre_in(pre, pi + 1, idx - ni + pi, in, ni, idx - 1, in_map);
        root->right = pre_in(pre, pi + idx - ni + 1, pj, in, idx + 1, nj, in_map);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0 || inorder.size() == 0) return nullptr;
        map<int, int> in_map;
        for (int i = 0; i < inorder.size(); i++) {
            in_map.insert(make_pair(inorder[i], i));
        }
        return pre_in(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, in_map);
    }
};

// 106. 从中序与后序遍历序列构造二叉树
class Solution {
public:
    TreeNode* compose_tree(vector<int>& in, int ni, int nj, vector<int>& po, int pi, int pj, map<int, int>& in_map) {
        if (ni > nj || pi > pj) return nullptr;
        TreeNode* new_node = new TreeNode;
        new_node->val = po[pj];

        auto iter = in_map.find(new_node->val);
        int idx = iter->second; 

        new_node->left = compose_tree(in, ni, idx - 1, po, pi, pi + (idx - ni) - 1, in_map);
        new_node->right = compose_tree(in, idx + 1, nj, po, pi + (idx - ni), pj - 1, in_map);
        return new_node;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0 || postorder.size() == 0) return nullptr;
        map<int, int> in_map;
        for (int i = 0; i < inorder.size(); i++) {
            in_map.insert(make_pair(inorder[i], i));
        }
        return compose_tree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1, in_map);
    }
};

// 108. 将有序数组转换为二叉搜索树
class Solution {
public:
    TreeNode* compose_tree(vector<int> &nums, int l, int r) {
        if (l > r) return NULL;
        int mid = l + (r - l) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = compose_tree(nums, l, mid - 1);
        root->right = compose_tree(nums, mid + 1, r);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return compose_tree(nums, 0, nums.size() - 1);
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
                res[i][j] = res[i-1][j-1]+res[i-1][j]; //利用杨辉三角的形式 第n行第k个数等于 第n行第k-1和k个数的和
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

// 128. 最长连续序列
class Solution {
public:
    int merge(map<int, int>& m, int less, int more) {
        int left = less - m[less] + 1;
        int right = more + m[more] - 1;
        int len = right - left + 1;
        m[left] = len;
        m[right] = len;
        return len;
    }

    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int ret = 1;
        map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (!m.count(nums[i])) {
                m.insert(make_pair(nums[i], 1));
                if (m.count(nums[i] - 1)) {
                    ret = max(ret, merge(m, nums[i] - 1, nums[i]));
                }
                if (m.count(nums[i] + 1)) {
                    ret = max(ret, merge(m, nums[i], nums[i] + 1));
                }
            }
        }
        return ret;
    }
};

// 130. 被围绕的区域
class Solution {
public:
    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i >= 0 && j >= 0 && i < board.size() && j < board[0].size() && board[i][j] == 'O') {
            board[i][j] = '1';
            dfs(board, i + 1, j);
            dfs(board, i - 1, j);
            dfs(board, i, j + 1);
            dfs(board, i, j - 1);
        }
    }
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0) return;
        int len1 = board.size();
        int len2 = board[0].size();
        for (int i = 0; i < len1; i++) {
            dfs(board, i, 0);
            dfs(board, i, len2 - 1);
        }
        for (int i = 0; i < len2 - 1; i++) {
            dfs(board, 0, i);
            dfs(board, len1 - 1, i);
        }

        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                if (board[i][j] == '1') board[i][j] = 'O';
                else {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

// 134. 加油站
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int rest = 0, run = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i){
        run += (gas[i] - cost[i]);
        rest += (gas[i] - cost[i]);
        if (run < 0){
            start = i + 1;
            run = 0;
        }
    }
    return rest < 0 ? -1: start;
    }
};

// 136. 只出现一次的数字
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        //return accumulate(nums.begin(),nums.end(),0,bit_xor());
        int a = 0;
        for (int i = 0; i < nums.size(); i++) {
            a = a ^ nums[i];
        }
        return a;
    }
};

// 150. 逆波兰表达式求值
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> numbers;
        for(int i = 0 ; i < tokens.size() ;++i){
            if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"){
                int res;
                int n2 = numbers.top();
                numbers.pop();
                int n1 = numbers.top();
                numbers.pop();
                
                if(tokens[i] == "+")
                   res = n1 + n2;
                else if(tokens[i] == "-")
                   res = n1 - n2;
                else if(tokens[i] == "/")
                   res = n1 / n2;
                else
                   res = n1 * n2;
                numbers.push(res);
            }else{
                numbers.push(stoi(tokens[i]));
            } 
        }
        return numbers.top();
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

// 162. 寻找峰值
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
    }
};

// 169. 多数元素
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int entry = nums[0];

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == entry) {
                count++;    
            } else {
                count--;
            }
            if (count == 0) {
                entry = nums[i];
                count++;
            }
        }
        return entry;
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

// 200. 岛屿数量
class Solution {
public:

    void infect(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() ||
            j < 0 || j >= grid[0].size() ||
            grid[i][j] != '1') {
                    return;
        }
        grid[i][j] = '2';
        infect(grid, i + 1, j);
        infect(grid, i - 1, j);
        infect(grid, i, j + 1);
        infect(grid, i, j - 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        int island_num = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    infect(grid, i, j);
                    island_num++;
                }
            }
        }
        return island_num;
    }
};

// 215. 数组中的第K个最大元素
class Solution {
public:

    int quick(vector<int>& nums, int start, int end, int k) {
        int i = start;
        int j = end;
        int base = nums[start];
        if (i < j) {
            while (i < j) {
                while (i < j && nums[j] < base) {
                    j--;
                }
                if (i < j) {
                    nums[i] = nums[j];
                    i++;
                }
                while (i < j && nums[i] > base) {
                    i++;
                }
                if (i < j) {
                    nums[j] = nums[i];
                    j--;
                }
            }
            nums[i] = base;
            if (i == k - 1) {
                return base;
            } else if (i > k - 1) {
                return quick(nums, start, i - 1, k);
            } else {
                return quick(nums, i + 1, end, k);
            }
        }
        return nums[i];
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quick(nums, 0, nums.size() - 1, k);
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

// 238. 除自身以外数组的乘积
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> tmp_vec;
        tmp_vec.resize(nums.size());
        int multi = 1;
        for (int i = 1; i < nums.size(); i++) {
            multi *= nums[i - 1];
            tmp_vec[i] = multi;
        }
       
        int tmp = nums[nums.size() - 1];
        for (int j = nums.size() - 2; j >= 1; j--) {
            tmp_vec[j] *= tmp;
            tmp *= nums[j];
        }
        tmp_vec[0] = tmp;
        return tmp_vec;
    }
};

// 239. 滑动窗口最大值
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> s;
        vector<int> v;
        for (int i = 0; i < nums.size(); i++) {
            while (!s.empty() && nums[s.back()] < nums[i]) {
                s.pop_back();
            }
            s.push_back(i);

            if (i - s.front() >= k) {
                s.pop_front();
            }
            if (i >= k - 1) {
                 v.push_back(nums[s.front()]);
            }
           
        }
        return v;
    }
};

// 240. 搜索二维矩阵 II
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0;
        int j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0) {
                if (matrix[i][j] > target) {
                    j--;
                } else if (matrix[i][j] < target) {
                    i++;
                } else {
                    return true;
                }
        }
        return false;
    }
};

// 283. 移动零
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nums[j] = nums[i];
                j++;
            }
        }
        for (int i = j; i < nums.size(); i++) {
            nums[i] = 0;
        }
    }
};

// 287. 寻找重复数
int findDuplicate(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 1) return -1;
    int walk = nums[0];
    int run = nums[nums[0]];
    while (walk != run) {
        walk = nums[walk];
        run = nums[nums[run]];
    }

    int tmp = nums[0];
    while (tmp != nums[walk]) {
        tmp = nums[tmp];
        walk = nums[walk];
    }
    return tmp;
}

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

// 347. 前 K 个高频元素
struct cmp {
    bool operator()(const pair<int, int>& l,
            const pair<int, int>& r) {
        return l.second > r.second;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> m;
        //priority_queue<pair<int, int>> pq;
        priority_queue<pair<int, int>,
            vector<pair<int, int>>, cmp> pq;

        vector<int> res;

        for (int i = 0; i < nums.size(); i++) {
            auto it = m.find(nums[i]);
            if (it == m.end()) {
                m.insert(pair(nums[i], 1));
            } else {
                it->second++;
            }
        }

        for (auto it = m.begin(); it != m.end(); it++) {
            if (pq.size() < k) {
                pq.push(pair(it->first, it->second));
            } else {
                if (pq.top().second < it->second) {
                    pq.pop();
                    pq.push(pair(it->first, it->second));
                }
            }
        }

        res.resize(pq.size());
        while (!pq.empty()) {
            res[--k] = pq.top().first;
            pq.pop();
        }
        return res;
    }
};

// 406. 根据身高重建队列
bool cmp(const vector<int> &l, const vector<int> &r) {
    if (l[0] == r[0]) {
        return l[1] < r[1];
    }
    return l[0] > r[0];
}

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> res;
        // res.resize(people.size());
        for (int i = 0; i < people.size(); i++) {
            if (people[i][1] >= res.size()) {
                res.push_back(people[i]);
            } else {
                res.insert(res.begin() + people[i][1], people[i]);
            }
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

// 448. 找到所有数组中消失的数字
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
         for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i + 1 &&
              nums[nums[i] - 1] != nums[i]) {
                int tmp = nums[i];
                nums[i] = nums[nums[i] - 1];
                nums[tmp - 1] = tmp;
            }
        }
        std::vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (i + 1 != nums[i]) {
                //res.push_back(nums[i]);
                res.push_back(i + 1);
            }
        }
        return res;
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

// 560. 和为K的子数组
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0, res = 0;
        unordered_map<int, int> cul;
        cul[0] = 1;
        for (auto &m : nums) {
            sum += m;
            res += cul[sum - k];
            ++cul[sum];
        }
        return res;
    }
};

// 581. 最短无序连续子数组
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int min = nums[nums.size() - 1];
        int left_idx = -1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] > min) {
                left_idx = i;
            } else {
                min = nums[i];
            }
        }
        if (left_idx == -1) return 0;

        int max = nums[0];
        int right_idx = -1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < max) {
                right_idx = i;
            } else {
                max = nums[i];
            }
        }
        return right_idx - left_idx + 1;

    }
};


