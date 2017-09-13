#include<iostream>
#include<stack>

void stack_reorder(std::stack<int>& s) {
  std::stack<int> stack_tmp;
  while(!s.empty()) {
    int cur = s.top();
    s.pop();
    while(!stack_tmp.empty() && stack_tmp.top() < cur) {
      int tmp = stack_tmp.top();
      s.push(tmp);
      stack_tmp.pop();
    }
    stack_tmp.push(cur);
  }

  while(!stack_tmp.empty()) {
    int tmp = stack_tmp.top();
    s.push(tmp);
    stack_tmp.pop();
  }

  return;
}

int main()
{
  std::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(100);
  s.push(4);
  s.push(5);
  stack_reorder(s);
  while(!s.empty()) {
    std::cout<<s.top()<<std::endl;
    s.pop();
  }
  return 0;
}
