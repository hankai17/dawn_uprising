#include<iostream>
#include<stack>

//画个图 自己模拟一下应该可以提取出逻辑
void stack_reorder(std::stack<int>& s) {
  std::stack<int> stack_tmp;
  int cur;

    if(stack_tmp.empty())  
      stack_tmp.push(s.top());
    cur = s.top();

  while(!s.empty()) {
    //if
    cur = s.top();
    std::cout<<cur<<std::endl;
    while(cur < stack_tmp.top()) {
      stack_tmp.push(cur);
      s.pop();
      cur = s.top();
    }

    while(!stack_tmp.empty()) {
      int tmp = stack_tmp.top();
      if (tmp > cur) {
        break;
      }
      s.push(tmp);
      std::cout<<"tmp = "<<tmp<<std::endl;
      stack_tmp.pop();
    } 

    stack_tmp.push(cur);
  }

  while(!stack_tmp.empty()) {
    std::cout<<stack_tmp.top()<<std::endl;
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

  return 0;
}
