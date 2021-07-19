// 3. 无重复字符的最长子串
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1) return s.size();
        int i = 0;
        int len = 0;
        map<int, int> m;
        int res = 0;
        for (int j = 0; j < s.size(); j++) {
            if (m.count(s[j]) && m[s[j]] >= i) {
                i = m[s[j]] + 1;
                len = j - i + 1;
            } else {
                len++;
            }
            m[s[j]] = j;
            res = max(res, len);
        }
       
        return res;
    }
};

// 5. 最长回文子串
class Solution {
public:
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
};

// 12. 整数转罗马数字
class Solution {
public:
    string intToRoman(int num) {
        vector<int> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> reps = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string res;
        for (int i = 0; i < 13; i++) {
            while (num >= values[i]) {
                num -= values[i];
                res += reps[i];
            }
        }
        return res;
    }
};

// 13. 罗马数字转整数
int romanToInt(char * s){
    if (s == NULL) return 0;
    int ret = 0;
    while (*s) {
        switch (*s++) {
            case 'I': ret += (*s == 'V' || *s == 'X') ? -1 : 1; break;
            case 'X': ret += (*s == 'L' || *s == 'C') ? -10 : 10; break;
            case 'C': ret += (*s == 'D' || *s == 'M') ? -100 : 100; break;
        case 'M': ret += 1000; break;
        case 'V': ret += 5; break;
        case 'L': ret += 50; break;
        case 'D': ret += 500; break;
        default: return 0;
        }
    }
    return ret;
}

// 14. 最长公共前缀
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        if (strs.size() == 1) return strs[0];

        for (int i = 0; i < strs[0].size(); i++) {
            char ch = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] != ch || i == strs[j].size()) {
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};

// 17. 电话号码的字母组合
class Solution {
public:
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
};

// 20. 有效的括号
class Solution {
public:
    bool isValid(string s) {
        if (s.size() == 0) return false;
        stack<char> sta;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
                if (sta.empty()) {
                    return false;
                } else {
                    if (sta.top() == '(' && s[i] == ')') {
                        sta.pop();
                    } else if (sta.top() == '[' && s[i] == ']') {
                        sta.pop();
                    } else if (sta.top() == '{' && s[i] == '}') {
                        sta.pop();
                    } else {
                        return false;
                    }
                }
            } else {
                sta.push(s[i]);
            }
        }
        return sta.empty();
    }
};

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

// 28. 实现 strStr()
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle == "") return 0;
        for (int i = 0; i < haystack.size(); i++) {
            if (haystack[i] == needle[0]) {
                if (i + needle.size() - 1 < haystack.size()) {
                    if (haystack.substr(i, needle.size()) == needle) {
                        return i;
                    }
                }
            }
        }
        return -1;
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

// 38. 外观数列
class Solution {
public:

    vector<pair<int, char>> compose_str(string str) {
        vector<pair<int, char>> res;
        int count = 1;

        for (int i = 1; i < str.size(); i++) {
            if (str[i] == str[i - 1]) {
                count++;
            } else {
                res.push_back(make_pair(count, str[i - 1]));
                count = 1;
            }
        }
        res.push_back(make_pair(count, str[str.size() - 1]));
        return res;
    }

    string countAndSay(int n) {
        if (n == 1) return "1";
        string str = "1";
       
        for (int i = 1; i < n; i++) {
            vector<pair<int, char>> res = compose_str(str);

            string tmp;
            for (int j = 0; j < res.size(); j++) {
                tmp += (to_string(res[j].first) + string(1, res[j].second));
            }
            str = tmp;
        }
        return str;
    }
};

// 49. 字母异位词分组
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        map<string, vector<string>> m;

        for (int i = 0; i < strs.size(); i++) {
            string tmp = strs[i];
            sort(tmp.begin(), tmp.end());
            m[tmp].push_back(strs[i]);
        }

        for (auto it = m.begin(); it != m.end(); it++) {
            res.push_back(it->second);
        }
        return res;
    }
};

// 58. 最后一个单词的长度
class Solution {
public:
    int lengthOfLastWord(string s) {
        if (s.size() == 0) return 0;
        int word_len = 0;
        int word_begin = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == ' ' && word_begin) {
                return word_len;
            } else if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z') {
                word_len++;
                word_begin = 1;
            }
        }
        return word_len;
    }
};

// 67. 二进制求和
class Solution {
public:

    int add_char(char a, char b, char op, char &res) {
        if (a == '1' && b == '1') {
            res = op;
            return 1;
        } else if (a == '0' && b == '0') {
            res = op;
            return 0;
        } 
        if (op == '0') {
            res = '1';
            return 0;
        } 
            res = '0';
            return 1;
    }

    string addBinary(string a, string b) {
        //string res(max(a.size(), b.size()) + 1, 0);
        vector<char> res;
        int i = a.size() - 1;
        int j = b.size() - 1;
        char op = 0;
        char c;
        int ret = 0;

        while (i >= 0 && j >= 0) {
            ret = add_char(a[i], b[j], ret == 0 ? '0' : '1', c);
            res.push_back(c);
            i--;
            j--;
        }

        while (i < 0 && j >= 0) {
            ret = add_char('0', b[j], ret == 0 ? '0' : '1', c);
            res.push_back(c);
            j--;
        }

        while (j < 0 && i >= 0) {
            ret = add_char(a[i], '0', ret == 0 ? '0' : '1', c);
            res.push_back(c);
            i--;
        }
        if (ret == 1) {
            res.push_back('1');
        }

        string tmp(res.size(), 0);
        int idx = 0;
        for (int i = res.size() - 1; i >= 0; idx++, i--) {
            tmp[idx] = res[i];
        }
        return tmp;
    }
};

// 71. 简化路径
class Solution {
public:
    bool dir_is_vaild(string dir) {
        if (dir == "/" || dir == "/.") {
            return false;
        }
        return true;
    }

    string simplifyPath(string path) {
        if (path.empty()) return path;
        stack<string> sta;
        path += "/";

        int b = 0;

        for (int i = 0; i < path.size(); i++) {
            if (i > 0 && path[i] == '/') {
                string dir = path.substr(b, i - b);
                if (dir_is_vaild(dir)) {
                    if (dir == "/..") {
                        if (!sta.empty()) {
                            sta.pop();
                        }
                    } else {
                         sta.push(dir);
                    }
                }
                b = i;
            }
        }

        string str;
        while (!sta.empty()) {
            str = sta.top() + str;
            sta.pop();
        }
        
        return str == "" ? "/" : str;
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

// 76. 最小覆盖子串
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> m, ori;
        int l = 0;
        int r = 0;
        for (char c : t) {
            ori[c]++;
        }

        int vaild = 0;
        int m_len = INT_MAX;
        int start = 0;

        while (r < s.size()) {
            // 确保窗口满足
            char c = s[r];
            r++;

            if (ori.count(c)) {
                m[c]++;
                if (m[c] == ori[c]) {
                    vaild++;
                }
            }
            // l++ 记录最小窗口 直到不满足则r++ 循环
            while (vaild == ori.size()) {
                if (r - l < m_len) {
                    start = l;
                    m_len = r - l;
                }
                char f = s[l];
                l++;
                if (ori.count(f)) {
                    if (m[f] == ori[f]) {
                        vaild--;
                    }
                    m[f]--;
                }
            }
        }
        return m_len == INT_MAX ? "" : s.substr(start, m_len);
    }
};

// 125. 验证回文串
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.size() <= 1) return true;
        int l = 0;
        int r = s.size() - 1;
        while (l <= r) {
            while (l < r && !isalnum(s[l])) l++;
            while (l < r && !isalnum(s[r])) r--;
            if (tolower(s[l]) != tolower(s[r])) return false;
            l++;
            r--;
        }
        return true;
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

// 171. Excel表列序号
int titleToNumber(char * columnTitle){
    char* s = columnTitle;
    if (s == NULL) return 0;
    int ret = 0;
    while (*s) {
        ret = ret * 26 + (*s - 'A' + 1);
        s++;
    }
    return ret;
}

// 208. 实现 Trie (前缀树)
class Trie {
public:
    Trie* link[26] = {nullptr};
    bool  is_end = false;
    /** Initialize your data structure here. */
    Trie() {
        
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->link[c - 'a'] == nullptr) {
                node->link[c - 'a'] = new Trie();
            }
            node = node->link[c - 'a'];
        }
        node->is_end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->link[c - 'a'] == nullptr) return false;
            node = node->link[c - 'a'];
        }
        return node->is_end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            if (node->link[c - 'a'] == nullptr) return false;
            node = node->link[c - 'a'];
        }
        return true;
    }
};

// 301. 删除无效的括号
class Solution {
public:
    bool is_vaild(string s) {
        stack<char> sta;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                sta.push('(');
            } else if (s[i] == ')') {
                if (sta.empty()) {
                    return false;
                }
                sta.pop();
            }
        }
        return sta.empty();
    }

    vector<string> removeInvalidParentheses(string s) {
        queue<string> q;
        set<string> visited;
        q.push(s);
        visited.insert(s);
        bool found = false;
        vector<string> res;

        while (!q.empty()) {
            for (int i = q.size() - 1; i >= 0; i--) {
                string tmp = q.front();
                q.pop();
                if (is_vaild(tmp)) {
                    found = true;
                    res.push_back(tmp);
                    //continue;
                }

                for (int i = 0; i < tmp.size(); i++) {
                    if (tmp[i] != '(' && tmp[i] != ')') {
                        continue;
                    }
                    string new_str = tmp.substr(0, i) + tmp.substr(i + 1);
                    if (visited.find(new_str) != visited.end()) {
                        continue;
                    }
                    visited.insert(new_str);
                    q.push(new_str);
                }
            }
            if (found) {
                return res;
            }
        }
        return res;
    }
};

// 394. 字符串解码
class Solution {
public:
    string decodeString(string s) {
        string str;
        stack<pair<string, int>> sta;
        int multi = 1; int c = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                multi = multi * 10 * (c);
                multi += s[i] - '0';
                c = 1;
            } else if (s[i] == '[') {
                sta.push(pair(str, multi));
                str = "";
                multi = 1;
                c = 0;
            } else if (s[i] == ']') {
                auto it = sta.top();
                sta.pop();
                string tmp;
                for (int i = 0; i < it.second; i++) {
                    tmp += str;
                }
                str = it.first + tmp;
                multi = 1;
                c = 0;
            } else {
                str += s[i];
            }
        }
        return str;
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

