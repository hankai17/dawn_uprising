#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <string.h>
#include <unordered_set>

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

how to make sure the least p
while (!q.empty()) {                                                                                              
    for (int i = q.size(); i > 0; i--) {
        // pop a string
        // pick up one char every time                                                                            
    }   
    if(found) break;                                                                                              
}   
*/
std::vector<std::string> removeInvalidParentheses(std::string s) 
{
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

#if 0
std::vector<std::vector<int>> subsets(std::vector<int> &nums) 
{
    std::vector<std::vector<int>> res={{}};
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
std::vector<std::vector<int>> res;

void dfs(int index, std::vector<int> &track, std::vector<int>& nums)
{
    if (index == nums.size()) return;
    track.push_back(nums[index]);
    res.push_back(track);
    dfs(index+1,track,nums);//包含当前元素
    track.pop_back();
    dfs(index+1,track,nums);//不包含
    return;
}

std::vector<std::vector<int>> subsets(std::vector<int>& nums) 
{
    //对于每个元素，两个选择，包含，不包含
    std::vector<int> track;
    res.push_back({}); //直接把空集先放入，不然后面会多次放入空集
    dfs(0, track, nums);
    return res;
}
#endif

#if 0
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

map<char,string> m={{'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},  {'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}};
vector<string> res;

void dfs(string digits, string track) {
    if (digits.size() == 0) {
        res.push_back(track);
    } else {
        char num = digits[0];
        string letter = m[num];
        for (int i = 0; i < letter.size(); i++) {
            track.push_back(letter[i]);
            dfs(digits.substr(1), track);
            track.pop_back();
        }
    }
}

vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return res;
    string track;
    dfs(digits, track);
    return res;
}
#endif

int test()
{
    std::string s = "123456";
    int i = 1;
    std::cout << s.substr(0, i) + s.substr(i + 1) << std::endl;
    //removeInvalidParentheses("()())()");
    return 0;
}

int main()
{
    test();
    return 0;
}
