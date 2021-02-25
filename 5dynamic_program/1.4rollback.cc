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
int test()
{
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
