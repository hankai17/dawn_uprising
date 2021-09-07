#include<iostream>
#include<string>
using namespace std;

int main()
{
    string a = "abc";
    string b = "deabc";
    string str_m;

    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            string tmp = a.substr(i, j - i + 1);
            if (int(b.find(tmp)) < 0) {
                break;
            } else if (str_m.size() < tmp.size()) {
                str_m = tmp;
            }
        }
    }
    cout << str_m << endl;
    return 0;
}
