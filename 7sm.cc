#include <string>
#include <iostream>
#include <stack>

using namespace std;

string decode_string(string s) 
{
   string str;
   stack<pair<string, int>> sta;
   int multi = 1; int c = 0;

   for (int i = 0; i < s.size(); i++) {
       if (s[i] >= '0' && s[i] <= '9') {
           multi = multi * 10 * (c);
           multi += s[i] - '0';
           c = 1;
       } else if (s[i] == '[') {
           sta.push(std::make_pair(str, multi));
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

void test()
{
  std::cout << decode_string("10[hello]") << std::endl;
}

int main()
{
    test();
    return 0;
}
