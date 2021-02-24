#include <iostream>
#include <vector>
#include <map>
//#include <hash_map>
#include <queue> // pq default big heap

struct cmp {
    bool operator()(const std::pair<int, int> &lhs, 
            const std::pair<int, int> &rhs) {
        return lhs.second > rhs.second;
    }                          
};                          

//priority_queue <int,vector<int>,greater<int> > q; //升序队列，小顶堆
//priority_queue <int,vector<int>,less<int> >q; //降序队列，大顶堆
//greater和less是std实现的两个仿函数

std::vector<int> topKFrequent(std::vector<int> &nums, int k) 
{
    std::vector<int> ret;
    if (k < 1 || nums.size() < k) return ret;

    std::map<int, int> m;
    for (int i = 0; i < nums.size(); i++) {
        if (m.find(nums[i]) == m.end()) {
            m[nums[i]] = 1;
        } else {
            m[nums[i]]++;
        }
    }

    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>, cmp> pq;

    for (auto iter = m.begin(); iter != m.end(); iter++) {
        if (pq.size() < k) {
            pq.push(*iter); // <1, 1> <2, 2>
            std::cout << "push it->first: " << iter->first << ", " 
                    << iter->second << std::endl;
        } else {
            std::pair<int, int> tmp = pq.top(); // <1, 1> <2, 2>
            if (iter->second > tmp.second) {
                pq.pop();
                pq.push(*iter);         
            }
        }
    }

    if (pq.size() < k) {
        return ret;
    }

    while (!pq.empty()) {
        ret.push_back(pq.top().first);
        pq.pop();
    }
    for (int i = 0; i < ret.size(); i++) {
        std::cout << ret[i] << " ";
    }
    return ret;
}

bool cmp(const vector<int>& a,const vector<int>& b){
        if(a[0] == b[0])
            return a[1]<b[1];
        return a[0]>b[0];
}
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> res;
        sort(people.begin(),people.end(),cmp);
        for(int i=0;i<people.size();i++){
            if(people[i][1]>=res.size())
                res.push_back(people[i]);
            else{
                res.insert(res.begin()+people[i][1],people[i]);
            }
        }
        return res;

    }
};

/**
大佬给出的一维数组动态规划有点懵逼。
这里先给出二维数组的动态规划，然后给出转化为一维数组的方法。理解起来相信非常容易。
所以这里会给出三个版本的代码：
二维数组动态规划
一维数组动态规划“二维转为一维的中间过程”
一维数组动态规划“最终版”
**/
// d(i, s) : 是否存在：nums区间[0, i] 中取一些元素，使其和为s
// d(i, s) = d(i-1, s){不取nums[i]} || d(i-1, s-nums[i]){取nums[i]}
// max(i) = nums.size()-1
// max(s) = sum(nums)/2
刚开始动态规划不太理解，后来发现：
我们求dp第i行的时候dp[i][?]，我们只需要知道dp的i-1行即可dp[i-1][?]。
也就是说，按照这个依赖关系，一直往下递推，只要得到第0行即可。
/*而第0行非常容易求。dp[0][s] = true当且仅当nums[0]==s*/
//图解：
//     s0 s1 s2 ...              ...sum
// i-1 [  {s-nums[i]}  ...       s    ]
//   i [               ...       s    ]
//dp[i][s] = dp[i-1][s] || dp[i-1][s-nums[i]]
//这里要保证下标i-1>=0，所以第0行可以单独计算。
//计算方法：i==0时，s用j遍历[0, sum(nums)]区间
//发现nums[0]==s[j]，则dp[0][j]=true;
class Solution {
public:
  bool canPartition(vector<int>& nums) {
    int sum = 0;
    for(int e : nums) sum += e;
    if(sum & 1) return false;//奇数显然不符合条件
    vector<vector<bool>> d(nums.size(), vector<bool>((sum>>=1)+1, false));//sum/=2
    for(int i = 0 ; i < nums.size() ; i++){
      for(int s = 0 ; s <= sum ; s++){//s range [0, sum(nums)>>1]
        if(!i) d[i][s] = (nums[i]==s);//i==0要单独求{ nums[0]一个元素和为s }
        else d[i][s] = d[i-1][s] || (s-nums[i]>=0 ? d[i-1][s-nums[i]] : false);
      }
    }
    return d[nums.size()-1][sum];//[0,nums.size()-1]区间和为sum
  }
};
优化版本：
上面看到，我们求解dp第i行dp[i][?]的时候，只需要知道第i-1行dp[i-1][?]的值即可。
也就是说，我们没必要开这么大的二维数组空间，直接开一个一维数组空间保存前一行的值就ok了。
下面给出二维转一维的中间过程的代码。在最后会给出清晰的最终代码
class Solution {
public:
  bool canPartition(vector<int>& nums) {
    int sum = 0;
    for(int e : nums) sum += e;
    if(sum & 1) return false;
    vector<bool> d((sum>>=1)+1, false);//sum/=2
    for(int i = 0 ; i < nums.size() ; i++){
      for(int s = sum ; s >= 0 ; s--/*int s = 0 ; s <= sum ; s++*/){//从后往前，因为前面的元素我们已经求过了(i>0时确实已经求过了，i==0时我们求一遍即可，下面的代码也确实给出了i==0的情况)，可以直接用
        if(!i) d/*[i]*/[s] = (nums[i]==s);//i==0要单独求{ nums[0]一个元素和为s }
        else d/*[i]*/[s] = d/*[i-1]*/[s] || (s-nums[i]>=0 ? d/*[i-1]*/[s-nums[i]] : false);
      }
    }
    return d/*[nums.size()-1]*/[sum];//[0,nums.size()-1]区间和为sum
  }
};
/*最后，这里给出最简的一维数组动态规划代码*/
class Solution {
public:
  bool canPartition(vector<int>& nums) {
    int sum = 0;
    for(int e : nums) sum += e;
    if(sum & 1) return false;
    vector<bool> d((sum>>=1)+1, false);//sum/=2
    for(int i = 0 ; i < nums.size() ; i++){
      for(int s = sum ; s >= nums[i] ; s--){//从后往前，因为前面的元素我们已经求过了(i>0时确实已经求过了，i==0时我们求一遍即可，下面的代码也确实给出了i==0的情况)，可以直接用
        if(!i) d[s] = (nums[i]==s);//i==0要单独求{ nums[0]一个元素和为s }
        else d[s] = d[s] || d[s-nums[i]];
      }
    }
    return d[sum];
  }
};

// 12packet ??


int test()
{
    std::vector<int> v = { 2, 2, 3, 3, 3, 1, 4, 4, 4, 4};
    topKFrequent(v, 2);
    return 0;
}

int main()
{
    test();
    return 0;
}
